# include <source.h>
# include <sink.h>
# include <iostream>
# include <filter.h>
# include <logging.h>
# include <string>
using namespace std;

void Filter::Update(){
  
  updated = 1;

  if (img1 != NULL)
    {
      char msg[128];
      sprintf(msg, "%s: about to update input1", SourceName());
      Logger::LogEvent(msg);
      img1 -> Update();
      char msg1[128];
      sprintf(msg1, "%s: done updating input1", SourceName());
      Logger::LogEvent(msg1);
    }

  if (img2 != NULL)
    {
      char msg[128];
      sprintf(msg, "%s: about to update input2", SourceName());
      Logger::LogEvent(msg);
      img2 -> Update();
      char msg1[128];
      sprintf(msg1, "%s: done updating input2", SourceName());
      Logger::LogEvent(msg1);
    }
}

void Shrinker::Execute(){

  if (img1 == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): No input image was ever set",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  
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
      char msg[1024];
      sprintf(msg, "(%s): Must have two input images to combine",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

  if (img1 -> Height() != img2 -> Height())
    {
      char msg[1024];
      sprintf(msg, "(%s): Heights must match: %d %d",
	      SourceName(), img1 -> Height(), img2 -> Height());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  
  image->ResetSize(img1->Height(), img1->Width() + img2->Width());
  image->setMaxVal(img1->Max_Val());
  int img2_count = 0;
  
  Pixel *to_input = new Pixel[image->Height()*image->Width()];
  
    for (int i = 0 ; i < image->Height() ; i++)
      {
	for (int j = 0 ; j < image->Width() ; j++)
	  {
	    if (j < img1 -> Width())
	      {
		to_input[i*image->Width() + j] = img1->Data()[i * img1 -> Width() + j];
	      }
	    else
	      {
		to_input[i*image->Width() + j] = img2->Data()[img2_count];
		img2_count++;
	      }
	  }
      }
    
    image->setData(to_input);
}


void TBCombine::Execute(){

  if (img1 == NULL || img2 == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): Must have two input images to combine",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  
  if (img1 -> Width() != img2 -> Width())
    {
      char msg[1024];
      sprintf(msg, "(%s): Widths must match: %d %d",
	      SourceName(), img1 -> Width(), img2 -> Width());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  
  image->ResetSize(img1->Height() + img2->Height(), img1->Width());
  
  image->setMaxVal(img1->Max_Val());
  
    Pixel *to_input = new Pixel[image->Height()*image->Width()];

    int img2_count = 0;
    
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
		to_input[i*image->Width() + j] = img2->Data()[img2_count];
		img2_count++;
	      }
	  }
      }
    image->setData(to_input);
}


void Blender::Execute()
{
  if (factor == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): factor needs to be set.",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  if (*factor < 0 || 1 < *factor)
    {
      char msg[1024];
      sprintf(msg, "(%s): factor must be between 0 and 1: %f",
	      SourceName(), *factor);
      DataFlowException e(SourceName(), msg);
      throw e;
    }

  if (img1 -> Width() != img2 -> Width())
    {
      char msg[1024];
      sprintf(msg, "(%s): Widths must match: %d %d",
	      SourceName(), img1 -> Width(), img2 -> Width());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

  if (img1 -> Height() != img2 -> Height())
    {
      char msg[1024];
      sprintf(msg, "(%s): Heights must match: %d %d",
	      SourceName(), img1 -> Height(), img2 -> Height());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  
  int index;
  int red = 0;
  int green = 0;
  int blue = 0;
  image->ResetSize(img1->Height(), img1->Width());
  image->setMaxVal(255);
  
  Pixel *to_input = new Pixel[image->Height()*image->Width()];
  
  for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	  {
	    index = i * image->Width() + j;
	    red = img1->Data()[index].R * (*factor) + img2->Data()[index].R * (1-*factor);
	    green = img1->Data()[index].G * (*factor) + img2->Data()[index].G * (1-*factor);
	    blue = img1->Data()[index].B * (*factor) + img2->Data()[index].B * (1-*factor);
	    to_input[index].R = red;
	    to_input[index].G = green;
	    to_input[index].B = blue;
	  }
    }
  image->setData(to_input);
}


void Mirror::Execute()
{

  if (img1 == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): No input image was ever set",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

  
  int index;
  image->ResetSize(img1->Height(), img1->Width());
  image->setMaxVal(img1->Max_Val());
  
  Pixel *to_input = new Pixel[image->Height()*image->Width()];
  
  for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	  {
	    index = i * image->Width() + j;
	    to_input[index] = img1->Data()[i * img1-> Width()
					   + ((img1->Width() - 1) - j)];
	  }
    }
  image->setData(to_input);
}


void Rotate::Execute()
{

  if (img1 == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): No input image was ever set",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

  int in_index;
  int out_index;
  image->ResetSize(img1->Width(), img1->Height());
  image->setMaxVal(img1->Max_Val());

  Pixel *to_input = new Pixel[image->Height() * image->Width()];

    for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	  {

	    
	    in_index = i * image->Width() + j;
	    
	    out_index = ((image->Width()-1) - j) * image->Height() + i;

	    
	    to_input[in_index] = img1->Data()[out_index];
	  }
    }
  image->setData(to_input);
}


void Subtract::Execute()
{

    if (img1 == NULL || img2 == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): Must have two input images to subtract",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

    if (img1 -> Height() != img2 -> Height())
    {
      char msg[1024];
      sprintf(msg, "(%s): Heights must match: %d %d",
	      SourceName(), img1 -> Height(), img2 -> Height());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

    if (img1 -> Width() != img2 -> Width())
    {
      char msg[1024];
      sprintf(msg, "(%s): Widths must match: %d %d",
	      SourceName(), img1 -> Width(), img2 -> Width());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

    int max_val = 0;
    int index;
    int temp;
    image->ResetSize(img1->Height(), img1->Width());
    Pixel *to_input = new Pixel[image->Height() * image->Width()];

    for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	{
	  index = i * image->Width() + j;
	  if(img1->Data()[index].R > img2->Data()[index].R)
	    {
	      temp = img1->Data()[index].R - img2->Data()[index].R;
	      if (temp > max_val)
		max_val = temp;
	    to_input[index].R = temp;
	    }

	  if(img1->Data()[index].G > img2->Data()[index].G)
	    {
	      temp = img1->Data()[index].G - img2->Data()[index].G;
	      if (temp > max_val)
		max_val = temp;
	    to_input[index].G = temp;
	    }

	  if(img1->Data()[index].B > img2->Data()[index].B)
	    {
	      temp = img1->Data()[index].B - img2->Data()[index].B;
	      if (temp > max_val)
		max_val = temp;
	    to_input[index].B = temp;
	    }
	}
    }
    image->setMaxVal(max_val);
    image->setData(to_input);
}

Color::Color(int width, int height, unsigned char R_in, unsigned char G_in, unsigned char B_in) : Source(){

  image = new Image(this, height, width);
  R = R_in;
  G = G_in;
  B = B_in;
  
}

void Color::Execute()
{
  name = "Color";
  Pixel *to_input = new Pixel[image->Height() * image->Width()];

  int index;
  for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	{
	  index = i * image->Width() + j;
	  to_input[index].R = R;
	  to_input[index].G = G;
	  to_input[index].B = B;
	}
    }
  
  image->setMaxVal(255);
  image->setData(to_input);
}

void Color::Update()
{
  updated = 1;
  Execute();
}

void Grayscale::Execute()
{
  if (img1 == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): No input image was ever set",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }

  
  int index;
  image->ResetSize(img1->Height(), img1->Width());
  image->setMaxVal(img1->Max_Val());
  
  Pixel *to_input = new Pixel[image->Height()*image->Width()];
  
  for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	  {
	    index = i * image->Width() + j;
	    to_input[index].R = (img1->Data()[index].R)/5 +
	      (img1->Data()[index].G)/2 +
	      (img1->Data()[index].B)/4;
	    to_input[index].G = (img1->Data()[index].R)/5 +
	      (img1->Data()[index].G)/2 +
	      (img1->Data()[index].B)/4;
	    to_input[index].B = (img1->Data()[index].R)/5 +
	      (img1->Data()[index].G)/2 +
	      (img1->Data()[index].B)/4;
	  }
    }
  image->setData(to_input);
}

void Blur::Execute()
{

  if (img1 == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): No input image was ever set",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  
  int index;
  int row_d;
  int row_u;
  image->ResetSize(img1->Height(), img1->Width());
  image->setMaxVal(img1->Max_Val());
  
  Pixel *to_input = new Pixel[image->Height()*image->Width()];
  Pixel *data = img1->Data();
  for (int i = 0 ; i < image->Height() ; i++)
    {
      for (int j = 0 ; j < image->Width() ; j++)
	{
	  index = i * image->Width() + j;
	  row_d = (i-1) * image->Width() + j;
	  row_u = (i+1) * image->Width() + j;
	  if( i == 0 || j == 0 || i == image->Height() - 1 || j == image->Width()-1)
	    to_input[index] = data[index];
	  else
	    {
	      to_input[index].R =
		(data[index - 1].R)/8 +
		(data[index+1].R)/8 +
		(data[row_d].R)/8 +
		(data[row_d - 1].R)/8 +
		(data[row_d + 1].R)/8 +
		(data[row_u].R)/8 +
		(data[row_u - 1].R)/8 +
		(data[row_u + 1].R)/8;
	      to_input[index].G =
		(data[index - 1].G)/8 +
		(data[index+1].G)/8 +
		(data[row_d].G)/8 +
		(data[row_d - 1].G)/8 +
		(data[row_d + 1].G)/8 +
		(data[row_u].G)/8 +
		(data[row_u - 1].G)/8 +
		(data[row_u + 1].G)/8;
	      to_input[index].B =
		(data[index - 1].B)/8 +
		(data[index+1].B)/8 +
		(data[row_d].B)/8 +
		(data[row_d - 1].B)/8 +
		(data[row_d + 1].B)/8 +
		(data[row_u].B)/8 +
		(data[row_u - 1].B)/8 +
		(data[row_u + 1].B)/8;
	    }
	}
    }
  
  image->setData(to_input);
}

void CheckSum::OutputCheckSum(const char filename[])
{
  int index;
  unsigned char r_tot = 0;
  unsigned char b_tot = 0;
  unsigned char g_tot = 0;

  for (int i = 0 ; i < img1->Height() ; i++)
    {
      for (int j = 0 ; j < img1->Width() ; j++)
	{
	  index = i * img1->Width() + j;
	  r_tot += img1->Data()[index].R;
	  g_tot += img1->Data()[index].G;
	  b_tot += img1->Data()[index].B;
	}
    }
  
  FILE *check_out = fopen(filename, "w");
  fprintf(check_out, "CHECKSUM: %d, %d, %d\n", r_tot, g_tot, b_tot);
  fclose(check_out);
}
