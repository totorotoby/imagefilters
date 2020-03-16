
#include<source.h>

class PNMreader : public Source
{
private:
  char *filename;
public:
  PNMreader(char *f);
  ~PNMreader();
  virtual void Execute();
  Image *GetOutput(){return image;}
  virtual void Update();
};
