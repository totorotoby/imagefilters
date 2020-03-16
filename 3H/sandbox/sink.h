#include<image.h>
#include <cstddef>
#ifndef SINK
#define SINK

class Sink
{
 protected:
  Image *img1;
  Image *img2;
 public:
  Sink(){
    img1 = NULL;
    img2 = NULL;
  }
  void SetInput(Image *to_set);
  void SetInput2(Image *to_set);
};

#endif
