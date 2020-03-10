#include <stdlib.h>
#include <cstring>
#include <image.h>
#include <iostream>
#include <source.h>

using namespace std;

Pixel::Pixel(){

  R = 0;
  G = 0;
  B = 0;

}


Pixel::Pixel(unsigned char R_in, unsigned char G_in, unsigned char B_in)
{

  R = R_in;
  G = G_in;
  B = B_in;
  
};

int Pixel::compare(Pixel other){

  if (R == other.R && G == other.G && B == other.B)
    return 1;
  else
    return 0;
}


Image::Image(){};

Image::Image(Source *p){
  parent = p;
}
  
Image::Image(int h, int w, int mv, unsigned char *buffer)
{  
  height = h;
  width = w;
  max_val = mv;
  data = new Pixel[width*height];
  
  for (int i = 0 ; i < width*height ; i++)
    {
      data[i].R = 1; //buffer[3*i];
      data[i].G = buffer[3*i+1];
      data[i].B = buffer[3*i+2];
    }
};

Image::Image(int h, int w)
{
  height = h;
  width = w;
}

Image::Image(Image *img)
{

  height = img -> height;
  width = img -> width;
  max_val = img -> max_val;
  
  Pixel *buffer = (Pixel*) malloc(width*height*sizeof(Pixel));
  memcpy(buffer, img -> data, height*width*3);
  
  data = buffer;
};  

void Image::ResetSize(int h, int w)
{
  height = h;
  width = w;
}

void Image::setMaxVal(int maxVal){max_val = maxVal;}

void Image::setData(unsigned char *buffer)
{
  data = new Pixel[width*height];
    
    for (int i = 0 ; i < width*height ; i++)
    {
      data[i].R = buffer[3*i];
      data[i].G = buffer[3*i+1];
      data[i].B = buffer[3*i+2];
    }
}
void Image::setData(Pixel *Data){

  data = new Pixel[width*height];
  data = Data;
  
}

void Image::setParent(Source *p){parent = p;}



int Image::Height(){return height;}
int Image::Width(){return width;}
int Image::Max_Val(){return max_val;}
int Image::isUpdated(){return updated;}
Pixel *Image::Data(){return data;}

void Image::Update(){
  
  if (parent->isUpdated() == 0)
    {
      cout <<"in image update going up" << endl;
      parent->Update();
    }
  if (parent->isUpdated() == 1){
    cout << "in image update going down" << endl;
    parent->Execute();
  }
}

