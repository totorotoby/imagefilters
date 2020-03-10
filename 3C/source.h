#ifndef SOURCE
#define SOURCE

#include <image.h>

class Source
{
 protected:
  Image *image;
 public:
  virtual void Execute() = 0;
  Image* GetOutput();
};

#endif
