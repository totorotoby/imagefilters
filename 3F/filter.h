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
    char s_name[128] = "Shrinker";
    name = new char[strlen(s_name) + 1];
    strcpy(name, s_name);
  };
  virtual void Execute();
};


class LRCombine : public Filter
{
public:
  LRCombine() : Filter()
  {
    char s_name[128] = "LRCombine";
    name = new char[strlen(s_name) + 1];
    strcpy(name, s_name);
    };
  virtual void Execute();
};

class TBCombine : public Filter
{
public:
  TBCombine() : Filter()
  {
    char s_name[128] = "TBCombine";
    name = new char[strlen(s_name) + 1];
    strcpy(name, s_name);
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
    char s_name[128] = "Blender";
    name = new char[strlen(s_name) + 1];
    strcpy(name, s_name);
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
    char s_name[128] = "Mirror";
    name = new char[strlen(s_name) + 1];
    strcpy(name, s_name);
  };
  virtual void Execute();
};

#endif
