#include<sink.h>

class PNMwriter : public Sink
{
 public:
  PNMwriter(){};
  void Write(char *filename);
  Image *Getimg1(){return img1;}
};
