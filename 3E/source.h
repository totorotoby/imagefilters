#ifndef SOURCE
#define SOURCE

#include <image.h>
#include <cstddef>

class Source
{
 protected:
  Image *image = NULL;
  int updated = 0;
 public:
  virtual void Execute() = 0;
  virtual void Update() = 0;
  Image* GetOutput();
  int isUpdated(){return updated;}
};

#endif
