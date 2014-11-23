
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define WIDTH   860
#define HEIGHT  620

int Px=0,Py=0,Pymax=0,Hmax=0;

unsigned char Image[HEIGHT][WIDTH];
char *FontFileName = "/usr/share/fonts/truetype/tlwg/Sawasdee.ttf";
char *Text;
int WR=160, HR=90, ResolutionFactor= 2; 

FT_Error error;
FT_Library library;
FT_Face face;
FT_GlyphSlot  slot;

void init();
int createText(char);
typedef struct 
{
  int w,h,x,y;
  char *data;
}Char; 
typedef struct 
{
  int w,h;
  char f,t;
  Char *all;
}Chars; 

  Chars chars;
int main(void) {


  chars.w = ResolutionFactor * WR;
  chars.h = ResolutionFactor * HR;
  chars.f = 48;
  chars.t = 127;
  //chars.f=97;
  //chars.t=102;

  int i,d=(chars.t-chars.f);
  printf("%d\n",d);
  Text = malloc(d*sizeof(char));
  init();
  for(i=0;i<d;i++) {
    Text[i] = chars.f+i;
    createText(chars.f+i);
  }
  chars.all = malloc(d*sizeof(Char));
  printf("Pymax = %d; Hmax= %d\n", Pymax,Hmax);

  printf("%s\n", Text);


}
void init() {
  error = FT_Init_FreeType(&library);
  if(error) printf("FT_Init_FreeType error= %d\n",error);
  error = FT_New_Face(library, FontFileName,  0, &face);
  if(error==FT_Err_Unknown_File_Format){
    printf("unknown FT_Err_Unknown_File_Format\n");
  }else if(error){
    printf("error %d\n",error);
  }
  error = FT_Set_Char_Size(
            face,    /* handle to face object           */
            0,       /* char_width in 1/64th of points  */
            16*64,   /* char_height in 1/64th of points */
            chars.w,     /* horizontal device resolution    */
            chars.h );   /* vertical device resolution      */
  if(error) printf("FT_Set_Char_Size error= %d\n",error);
  slot = face->glyph;  /* a small shortcut */
}
int createText(char c){
  FT_UInt  glyph_index;
  glyph_index = FT_Get_Char_Index(face, c);
  error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
  if ( error ) { printf("e  %d",error); return error; } 
  error = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );
  if ( error ) { printf("e1 %d",error); return error; }
  FT_Bitmap* bitmap = &slot->bitmap;
  int i,j;
  FT_Int x0 = slot->bitmap_left, y0 = slot->bitmap_top , w = bitmap->width , h = bitmap->rows ,p = bitmap->pitch;

  Px += slot->advance.x >> 6;
  Py += slot->advance.y >> 6; /* not useful for now */
  // printf("advance.x=%ld;advance.y=%ld\n",slot->advance.x,slot->advance.y );
  // printf("m.width=%ld;m.height=%ld\n",slot->metrics.width,slot->metrics.height);
  // printf("m.horiBearingX=%ld;m.horiBearingY=%ld\n",slot->metrics.horiBearingX,slot->metrics.horiBearingY);
  // printf("m.vertBearingX=%ld;m.vertBearingY=%ld\n",slot->metrics.vertBearingX,slot->metrics.vertBearingY);

  
  if (Pymax < slot->bitmap_top) Pymax=slot->bitmap_top;
  if (Hmax < h-y0 ) Hmax=h-y0;

  printf("c=%c;p=%d    x0=%d;y0=%d    w=%d;h=%d    Px=%d;Py=%d    slot->advance.x=%ld\n",c,p,x0,y0,w,h,Px,Py,slot->advance.x/64  );
  printf("Px + slot->bitmap_left=%d;Py - slot->bitmap_top=%d;\n",Px + slot->bitmap_left,Py - slot->bitmap_top );

  //Px + slot->bitmap_left, Py - slot->bitmap_top


  for ( i=0; i<w*h; i++ )
  {
    // //r |= bitmap->buffer[q * w + p];
    // if(bitmap->buffer[i]==0) 
    //   printf("-");
    // else 
    //   printf("0");
    // //printf("%u-",bitmap->buffer[i]);
    // if ( (i+1)%w==0 ) printf("\n");
  }


printf("\n");
  // for ( i=x0; i<w; i++ )
  // {
  //   for ( j=y0; j<h; j++ )
  //   {
  //     r |= bitmap->buffer[q * w + p];
  //     printf("%u\n",r);
  //   }
  // }
  return 0;
} 

void my_draw_bitmap( FT_Bitmap* bitmap, FT_Int x, FT_Int y)
{
  FT_Int  i, j, p, q;
  FT_Int  x_max = x + bitmap->width;
  FT_Int  y_max = y + bitmap->rows;
  for ( j = y, q = 0; j < y_max; j++, q++ )
  {
    for ( i = x, p = 0; i < x_max; i++, p++ )
    {
      if ( i<0 || j<0 || i>=WIDTH || j>=HEIGHT )  continue;
      Image[j][i] |= bitmap->buffer[q * bitmap->width + p];
      //printf("%d-", Image[j][i]);
      // if(Image[j][i]==0) 

      //   printf("1");
      // else
      //   printf("0");
    }
    //printf("\n");
  }
  printf("x=%d,y=%d,x_max=%d,y_max=%d,x_max-x=%d,y_max-y=%d\n",x,y,x_max,y_max,x_max-x,y_max-y);
  int a=x_max-x,b=y_max-y;
  printf("sizeof(x)=%ld;sizeof(y)=%ld\n",sizeof(a),sizeof(b));
}

  // createText();
  // int i,j,k=0;
  // for(i=0;i<HEIGHT;i++) 
  //   for(j=0;j<WIDTH;j++)
  //     if(Image[i][j]!=0) 
  //       k++;
  // printf("pixels = %d\n",k);
  // printf("\n");
  // unsigned int a=345332;
  // void *b= (void *)&a;
  // unsigned char* c = (unsigned char*) b;
  // char* c0 = (char*) c;


  // printf("a=%p;b=%p;c=%p\n",&a,b,c);
  // printf("a=%lu;b=%lu;c=%lu\n",sizeof(&a),sizeof(b),sizeof(c));
  // printf("a=%d;c0=%s\n",a,c0);
  // printf("c0=%u\n",*(c+0));
  // printf("c0=%u\n",*(c+1));
  //   printf("c0=%u\n",*(c+2));
  // printf("c0=%u\n",*(c+3));
  // unsigned char  cc0=65;
  // printf("c0=%u\n",cc0);