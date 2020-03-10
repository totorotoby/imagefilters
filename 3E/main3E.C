#include <PNMreader.h>
#include <PNMwriter.h>
#include <filter.h>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

Image *compare_output(Image *w, Image *t)
{
  
  if (w->Height() != t->Height())
    {
    cout << "The heights are miss matched with truth: "
	 << t->Height() << "\nMy output: " << w->Height() << endl;
    }
  if (w->Width() != t->Width())
    {
    cout << "The Widths are miss matched with truth: "
	 << t-> Width() << "\nMy output: " << w->Width() << endl;
    }
  
  Image *error = new Image();
  error -> ResetSize(t->Height(), t->Width());
  error -> setMaxVal(t->Max_Val());
  Pixel *to_show = new Pixel[error->Height() * error->Width()];

  Pixel *writer_data = w->Data();
  Pixel *truth_data = t->Data();

  int index;
  cout << "Height is: " << error->Height() << endl;
  cout << "Width is: " << error->Width() << endl;
  for (int i = 0 ; i < error->Height() ; i++)
    {
      for (int j = 0 ; j < error->Width() ; j++)
	{
	  index = i *t->Width() + j;
	  if (truth_data[index].compare(writer_data[index]))
	    {
	      to_show[index] = truth_data[index];
	    }
	  else
	    {
	      cout << "differs at: " << i <<", " << j << " " << endl;
	      cout << "R: (" << (int) truth_data[index].R <<", " << (int)  writer_data[index].R << ")" << endl;
	      cout << "G: (" << (int) truth_data[index].G <<", " << (int)  writer_data[index].G << ")" << endl;
	      cout << "B: (" <<(int) truth_data[index].B <<", " << (int)  writer_data[index].B << ")\n\n" << endl;
	      to_show[index].R = 248; 
	      to_show[index].G = 24;
	      to_show[index].B = 148;
	    }
	}
    }
  
  error->setData(to_show);

  return error;

}

void write_to_file(char *filename, Image *img)
{

 FILE *f_out = fopen(filename, "w");
 fprintf(f_out, "P6\n%d %d\n%d\n", img->Width(), img->Height(), img->Max_Val());
 
 for (int i = 0 ; i < img->Height()*img->Width() ; i++)
   {
     fprintf(f_out, "%c", img->Data()[i].R);
     fprintf(f_out, "%c", img->Data()[i].G);
     fprintf(f_out, "%c", img->Data()[i].B);
   }

}

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);
    PNMwriter writer;
    Shrinker shrinker1;
    Shrinker shrinker2;
    LRCombine lrcombine1;
    LRCombine lrcombine2;
    TBCombine tbcombine1;
    TBCombine tbcombine2;
    Blender  blender;
    blender.SetFactor(0.795);

    shrinker1.SetInput(reader.GetOutput());

    lrcombine1.SetInput(shrinker1.GetOutput());
    lrcombine1.SetInput2(shrinker1.GetOutput());

    tbcombine1.SetInput(lrcombine1.GetOutput());
    tbcombine1.SetInput2(lrcombine1.GetOutput());

    shrinker2.SetInput(tbcombine1.GetOutput());

    lrcombine2.SetInput(shrinker2.GetOutput());
    lrcombine2.SetInput2(shrinker1.GetOutput());

    tbcombine2.SetInput(lrcombine2.GetOutput());
    tbcombine2.SetInput2(lrcombine1.GetOutput());

    blender.SetInput(tbcombine2.GetOutput());
    blender.SetInput2(reader.GetOutput());

    writer.SetInput(blender.GetOutput());

    blender.GetOutput()->Update();
    writer.Write(argv[2]);

    // doing comparison things
    
    PNMreader hanks(argv[3]);
    hanks.Execute();
    Image *compared = compare_output(blender.GetOutput(), hanks.GetOutput());
    write_to_file(argv[4], compared);

    
}
