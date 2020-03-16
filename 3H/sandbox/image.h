#ifndef IMAGE
#define IMAGE
#include <cstddef>
#include <iostream>

using namespace std;

class Source;

struct Pixel
{
  unsigned char R, G, B;
  Pixel();
  Pixel(unsigned char R, unsigned char G, unsigned char B);
  int compare(Pixel other);
};

struct Image
{
  
private:
  int height;
  int width;
  int max_val;
  Pixel *data;
  Source *parent;
  int updated;
  
public:
  Image();
  Image(Source *p);
  Image(Source *p, int h, int w);
  Image(int h, int w);
  Image(Image *img);
  ~Image(){
    delete []data;}
  void ResetSize(int h, int w);
  void setMaxVal(int maxVal);
  void setData(Pixel *Data);
  void setParent(Source *p);
  int Height();
  int Width();
  int Max_Val();
  Pixel *Data();
  int isUpdated();
  void Update();
  
};

#endif
