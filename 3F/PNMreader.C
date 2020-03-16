#include <string.h>
#include <PNMreader.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <logging.h>
using namespace std;

PNMreader::PNMreader(char *f)
{
  image = new Image(this);
  filename = new char[strlen(f) + 1];
  strcpy(filename, f);
  char s_name[128] = "PNMreader";
  name = new char[strlen(s_name) + 1];
  strcpy(name, s_name);
};


PNMreader::~PNMreader()
{
  delete []filename;
}


void PNMreader::Execute()
{
  
  FILE *f_in;
  char magic_num[128];
  int width, height, max_val;
  unsigned char *buffer;
  
  f_in = fopen(filename, "r");
  
  if (f_in == NULL)
    {
      char msg[1024];
      sprintf(msg, "(%s): Cannot find file: %s",
	      SourceName(), filename);
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  
  fscanf(f_in, "%s\n%d %d\n%d\n", magic_num, &width, &height, &max_val);
  
  if (strcmp(magic_num,"P6") != 0)
    {
      char msg[1024];
      sprintf(msg, "(%s): This file is not in PNM format",
	      SourceName());
      DataFlowException e(SourceName(), msg);
      throw e;
    }
  

  buffer = new unsigned char[width*height*3];
  fread(buffer, sizeof(unsigned char), width*height*3, f_in);

  image -> ResetSize(height, width);
  image -> setMaxVal(max_val);
  image -> setData(buffer);
  delete buffer;
  
}
  
void PNMreader::Update()
{
  //cout << "at the top of with PNMreader" << endl;
  updated = 1;
  image -> Update();
}
