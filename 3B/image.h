#ifndef IMAGE
#define IMAGE

struct Pixel
{
  unsigned char R, G, B;
  Pixel(unsigned char R, unsigned char G, unsigned char B);
  int compare(Pixel &other);
};

struct Image
{
  int height;
  int width;
  int max_val;
  Pixel *data;
  Image();
  Image(int h, int w, int mv, Pixel *d);
  Image(Image *img);
  void ResetSize(int h, int w);
};

#endif