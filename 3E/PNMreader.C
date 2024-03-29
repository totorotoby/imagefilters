#include <string.h>
#include <PNMreader.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

PNMreader::PNMreader(char *f)
{
  image = new Image(this);
  filename = new char[strlen(f) + 1];
  strcpy(filename, f);
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
      printf("Unable to open file \"%s\"", filename);
    }
  
  fscanf(f_in, "%s\n%d %d\n%d\n", magic_num, &width, &height, &max_val);
  
  if (strcmp(magic_num,"P6") != 0)
    {
      printf("This program won't work since the file being read in isn't a pnm.\n");
      exit(1);
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
  updated = 1;
  image -> Update();
}
