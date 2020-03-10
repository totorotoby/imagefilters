#ifndef IMAGE
#define IMAGE
#include <cstddef>

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
  Pixel *data = NULL;
  Source *parent = NULL;
  int updated = 0;
  
public:
  Image();
  Image(Source *p);
  Image(int h, int w, int mv, unsigned char *d);
  Image(int h, int w);
  Image(Image *img);
  void ResetSize(int h, int w);
  void setMaxVal(int maxVal);
  void setData(unsigned char *buffer);
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
