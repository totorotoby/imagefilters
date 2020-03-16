#include <stdio.h>
#include <PNMwriter.h>
#include <iostream>
#include <fstream>

using namespace std;

void PNMwriter::Write(char *filename){

  FILE *f_out = fopen(filename, "w");
  fprintf(f_out, "P6\n%d %d\n%d\n", img1->Width(), img1->Height(), img1->Max_Val());

  int num_pix = img1->Width() * img1->Height();
  Pixel *data = img1->Data();
  for (int i = 0  ; i < num_pix ; i ++)
    {
      fprintf(f_out, "%c", data[i].R);
      fprintf(f_out, "%c", data[i].G);
      fprintf(f_out, "%c", data[i].B);
    }
  fclose(f_out);
}
