#ifndef FILTER
#define FILTER
#include <source.h>
#include <sink.h>
#include <image.h>
#include <typeinfo>
#include <string.h>

class Filter : public Source, public Sink{
public:
  Filter(){image = new Image(this);}
  virtual void Execute() = 0;
  virtual void Update();
};

class Shrinker : public Filter
{
public:
  Shrinker() : Filter()
  {
    name = "Shrinker";
  };
  virtual void Execute();
};


class LRCombine : public Filter
{
public:
  LRCombine() : Filter()
  {
    name = "LRCombine";
    };
  virtual void Execute();
};

class TBCombine : public Filter
{
public:
  TBCombine() : Filter()
  {
    name = "TBCombine";
  };
  virtual void Execute();
};


class Blender : public Filter
{
private:
  double *factor;
public:
  Blender() : Filter()
  {
    factor = NULL;
    name = "Blender";
  };
  ~Blender()
  {
    delete factor;
  };
  void SetFactor(double f)
  {
    if (factor == NULL){
      factor = new double; 
    }
    *factor = f;}
  virtual void Execute();
};

class Mirror : public Filter
{

public:
  Mirror() : Filter(){
    name = "Mirror";
  };
  virtual void Execute();
};


class Rotate : public Filter{
public:
  Rotate() : Filter()
  {
    name = "Rotate";
  };
  virtual void Execute();
};

class Subtract : public Filter{
public:
  Subtract() : Filter()
  {
    name = "Subtract";
  };
  virtual void Execute();
};

class Color : public Source
{
public:
  Color(int width, int height, unsigned char R, unsigned char G, unsigned char B);
  virtual void Execute();
  virtual void Update();
private:
  int R;
  int G;
  int B;
};

class Grayscale : public Filter{
public:
  Grayscale() : Filter()
  {
    name = "Grayscale";
  };
  virtual void Execute();
};

class Blur : public Filter{
public:
  Blur() : Filter()
  {
    name = "Blur";
  };
  virtual void Execute();
};



class CheckSum : public Sink
{
public:
  CheckSum() : Sink(){};
  void OutputCheckSum(const char filename[]);
};

#endif
