#include <image.h>
#include <filter.h>
#include <source.h>
#include <sink.h>
#include <PNMreader.h>
#include <PNMwriter.h>
#include <stdio.h>
#include <iostream>
#include <fstream>


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
	      cout << i <<", " << j << " "
		   << "R: (" << (int) truth_data[index].R <<", " << (int)  writer_data[index].R << ")" << endl;
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

  
  Image *to_write = compare_out(argv[0], argv[1]);
  write_to_file(argv[2], to_write);



}
