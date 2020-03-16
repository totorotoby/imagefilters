#ifndef SOURCE
#define SOURCE

#include <image.h>
#include <cstddef>
#include <iostream>

using namespace std;

class Source
{
 protected:
  Image *image;
  int updated;
  const char *name;
 public:
  Source()
  {
    image = NULL;
    updated = 0;
  };
  ~Source()
  {
    delete image;
  }
  virtual void Execute() = 0;
  virtual void Update() = 0;
  Image* GetOutput();
  int isUpdated(){return updated;}
  const char *SourceName(){return name;}
};

#endif
