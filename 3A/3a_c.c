#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int height;
  int width;
  int max_val;
  unsigned char *data;
  
} Image;

/*
void printMatrix(int *m, int height, int width)
{

  for (int i = 0 ; i < height ; i++)
    {
    for (int j = 0 ; j < width ; j++)
      {
	printf("%.2f,", m*(ij));
    }
    printf("\n");
  }
}

*/

Image *ReadImage(char *filename)
{

  FILE *f_in;
  Image *new_image;
  char magic_num[128];
  int width, height, max_val;
  unsigned char *buffer;
 
  //opens file stream
  f_in = fopen(filename, "r");
  
  if (f_in == NULL)
    {
      printf("Unable to open file \"%s\"", filename);
    }
  //read header into variables
  fscanf(f_in, "%s\n%d %d\n%d\n", magic_num, &width, &height, &max_val);
  // copy data new image
  
  if (strcmp(magic_num,"P6") != 0)
    {
      printf("This program won't work since the file being read in isn't a pnm.\n");
      exit(1);
    }

  
  new_image = malloc(sizeof(Image));
  
  new_image -> height = height;
  new_image -> width = width;
  new_image -> max_val = max_val;
  
  /*
  read image pixel by pixel into array.
  each pixel has 3 bytes assosated with it for r ,g ,b
  so we need each row to be 3 times as long, and we will treat pixels in groups of 3 bytes.
  */

  /*   
  Sanity check that height*width*3 is the number of bytes to the end of file.

  long s_len = ftell(f_in);
  fseek(f_in, 0, SEEK_END);
  long e_len = ftell(f_in);
  long length = e_len - s_len;
  fseek(f_in, s_len, SEEK_SET);
  printf("%ld, %d", length, height*width*3);
  */


  buffer = malloc(width*height*3);
  fread(buffer, sizeof(unsigned char), width*height*3, f_in);
  
  new_image -> data = buffer;
  
  /*
  for (int i = 0 ; i < height; i++)
    {
      for (int j = 0 ; j < width*3; j++)
	{
	  printf ("%d, ", buffer[j]);
	}
      printf("\n");
    }

  */

  return new_image;
  
}

void WriteImage(Image *img, char *filename)
{

 FILE *f_out = fopen(filename, "w");
 fprintf(stderr, "hello");
 fprintf(f_out, "P6\n%d %d\n%d\n", img -> width, img -> height, img -> max_val);
 for (int i = 0 ; i < img->height*img->width*3 ; i++)
   {
     fprintf(f_out, "%c", img->data[i]);
   }
}

Image *
YellowDiagonal(Image *input)
{

  int i;
  int j;
  int b_width = input -> width * 3;
  int b_height = input -> height;
  
  for (i = 0 ; i < b_height ; i++)
    {	  
	  //The diagonal is i*width elemenents down
	  //Then since there are 3 times as elements for the width we need to step by 3s
	  input -> data[i*b_width + 3*i] = 255;
	  input -> data[i*b_width+ 3*i +1] = 255;
	  input -> data[i*b_width+ 3*i + 2] = 0;
    }
  
  return input;

}

int main(int argc, char *argv[])
{
  
  if (argc -1 != 2)
    {
      printf("Need both a file to read from and one to write to.\n");
      exit(1);
    }

  char *read_string = argv[1];
  char *write_string = argv[2];
 
  Image *input_img = ReadImage(read_string);
  YellowDiagonal(input_img);
  WriteImage(input_img, write_string);
  
  
}
