# include <source.h>
# include <sink.h>
# include <iostream>
# include <filter.h>
using namespace std;

void Filter::Update(){
  
  updated = 1;

  if (img1 != NULL)
    {
      cout << "in filter update going up" << endl;
      img1 -> Update();
    }

  if (img2 != NULL)
    {
      img2 -> Update();
    }
}

void Shrinker::Execute(){

  int input_height = img1->Height();
  int input_width = img1->Width();
  int max_val = img1->Max_Val();
  int output_height = input_height/2;
  int output_width = input_width/2;
  
  image->ResetSize(output_height, output_width);
  image->setMaxVal(max_val);
  
  Pixel *to_input = new Pixel[output_height*output_width];
  
  for (int i = 0 ; i < output_height ; i++)
      {
	for (int j = 0 ; j < output_width ; j++)
	  {
	    to_input[i*output_width + j] = img1->Data()[2*i*input_width + j*2];
	  }
      }
  image->setData(to_input);
}


void LRCombine::Execute(){

  if (img1 == NULL || img2 == NULL)
    {
      cout << "Need to Images to Combine" << endl;
      exit(0);
    }
  
    image->ResetSize(img1->Height(), img1->Width()*2);
    image->setMaxVal(img1->Max_Val());
    
    Pixel *to_input = new Pixel[image->Height()*image->Width()];
    
    for (int i = 0 ; i < image->Height() ; i++)
      {
	for (int j = 0 ; j < image->Width() ; j++)
	  {
	    if (j < img1 -> Width())
	      {
		to_input[i*image->Width() + j] = img1->Data()[i*img1->Width() + j];
	      }
	    else
	      {
		to_input[i*image->Width() + j] = img2->Data()[i*img2->Width()
							      + (j - img2->Width())];
	      }
	  }
      }
    
    image->setData(to_input);
    
}


void TBCombine::Execute(){

  if (img1 == NULL || img2 == NULL)
    {
      cout << "Need to Images to Combine" << endl;
      exit(0);
    }
  
  image->ResetSize(img1->Height()*2, img1->Width());
  
  image->setMaxVal(img1->Max_Val());
  
    Pixel *to_input = new Pixel[image->Height()*image->Width()];
    
    for (int i = 0 ; i < image->Height() ; i++)
      {
	for (int j = 0 ; j < image->Width() ; j++)
	  {
	    if (i < img1 -> Height())
	      {
		to_input[i*image->Width() + j] = img1->Data()[i*img1->Width() + j];
	      }
	    else
	      {
		to_input[i*image->Width() + j] = img2->Data()[i*img2->Width()
							      -(img2->Height()*img2->Width())
							      + j];
	      }
	  }
      }
    image->setData(to_input);
}


void Blender::Execute()
{
  
  int index;
  image->ResetSize(img1->Height(), img1->Width());
  image->setMaxVal(img1->Max_Val());
  
  int max_value = 0;
  Pixel *to_input = new Pixel[image->Height()*image->Width()];
  
  for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	  {
	    index = i * image->Width() + j;
	    int red = img1->Data()[index].R * factor + img2->Data()[index].R * (1-factor);
	    int green = img1->Data()[index].G * factor + img2->Data()[index].G * (1-factor);
	    int blue = img1->Data()[index].B * factor + img2->Data()[index].B * (1-factor);
	    
	    if (red > max_value){max_value = red;}
	    if (red > max_value){max_value = green;}
	    if (red > max_value){max_value = blue;}
	    
	    to_input[index].R = red;
	    to_input[index].G = green;
	    to_input[index].B = blue;
	  }
    }
  image->setMaxVal(img1->Max_Val());
  image->setData(to_input);
}


void Mirror:Execute()
{

  int index;
  image->ResetSize(img1->Height(), img1->Width());
  image->setMaxVal(img1->Max_Val());
  
  Pixel *to_input = new Pixel[image->Height()*image->Width()];
  
  for (int j = 0 ; j < image->Width() ; j++)
    {
      for (int i = 0 ; i < image->Height() ; i++)
	  {
	    index = i * image->Width() + j;
	    to_input[index] = img1->Data()[image->Width() - index];
	  }
    }
  image->setData(to_input);
  
}
