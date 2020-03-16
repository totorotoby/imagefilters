#ifndef SOURCE
#define SOURCE

#include <image.h>
#include <cstddef>

using namespace std;

class Source
{
 protected:
  Image *image = NULL;
  int updated = 0;
  char* name;
 public:
  Source()
  {
    image = NULL;
    updated = 0;
  };
  virtual void Execute() = 0;
  virtual void Update() = 0;
  Image* GetOutput();
  int isUpdated(){return updated;}
  char *SourceName(){return name;}
};

#endif
