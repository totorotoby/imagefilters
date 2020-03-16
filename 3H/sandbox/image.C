#include <stdlib.h>
#include <cstring>
#include <image.h>
#include <iostream>
#include <source.h>
#include <logging.h>
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


Image::Image(){
    data = NULL;
    parent = NULL;
    updated = 0;
  };

Image::Image(Source *p)
{
  cerr << "constructing in image" << endl;
  data = NULL;
  updated = 0;
  parent = p;
}
  
Image::Image(Source *p, int h, int w)
{
  data = NULL;
  parent = p;
  height = h;
  width = w;
}

Image::Image(int h, int w)
{
  data = NULL;
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


void Image::setData(Pixel *Data){
  if (data != NULL)
    {
      cerr << "dumb trevor" << endl;
      delete []data;
    }
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
      //cout << "in image going up" << endl;
      parent->Update();
    }
  if (parent->isUpdated() == 1){
    //cout << "in image going down" << endl;
    char msg[128];
    sprintf(msg, "%s: about to execute", parent->SourceName());
    Logger::LogEvent(msg);
    parent->Execute();
    char msg1[128];
    sprintf(msg1, "%s: done executing", parent->SourceName());
    Logger::LogEvent(msg1);
  }
}

