#include<image.h>
#include <cstddef>
#ifndef SINK
#define SINK

class Sink
{
 protected:
  Image *img1 = NULL;
  Image *img2 = NULL;
 public:
  void SetInput(Image *to_set);
  void SetInput2(Image *to_set);
};

#endif
