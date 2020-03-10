#ifndef FILTER
#define FILTER

#include <source.h>
#include <sink.h>
#include <image.h>

class Filter : public Source, public Sink{
public:
  Filter(){image = new Image(this);}
  virtual void Execute() = 0;
  virtual void Update();
};

class Shrinker : public Filter
{
public:
  Shrinker() : Filter(){};
  virtual void Execute();
};


class LRCombine : public Filter
{
public:
  LRCombine() : Filter(){};
  virtual void Execute();
};

class TBCombine : public Filter
{
public:
  TBCombine() : Filter(){};
  virtual void Execute();
};


class Blender : public Filter
{
private:
  float factor;
public:
  Blender() : Filter(){}
  void SetFactor(float f){factor = f;}
  virtual void Execute();
};


class Mirror : public Filter
{

public:
  Mirror() : Filter(){}
  virtual void Execute();


};




#endif
