#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
namespace libyuv {
extern "C" {
#endif


typedef struct 
{
  int w,h,a,bx,by;

  unsigned char *data;
}Char; 

typedef struct 
{
  int w,h,l;
  char *name;
  Char *all;
}Chars; 

typedef struct 
{
  int w,h,x0,y0;
  unsigned char *data;
}Word; 

//int WidthR=160, HeightR=90;


#ifdef __cplusplus
}  // extern "C"
}  // namespace libyuv
#endif