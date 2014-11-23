
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define WIDTH   860
#define HEIGHT  620

int Px=100,Py=100;
unsigned char Image[HEIGHT][WIDTH];
char *FontFileName = "/usr/share/fonts/truetype/tlwg/Sawasdee.ttf";
char *Text = "AB";


void my_draw_bitmap(FT_Bitmap*,FT_Int,FT_Int);
int createText();

int main(void) {
  createText();
  int i,j,k=0;
  for(i=0;i<HEIGHT;i++) 
    for(j=0;j<WIDTH;j++)
      if(Image[i][j]!=0) 
        k++;
  printf("pixels = %d\n",k);
}

int createText(){
  //"/usr/share/cups/fonts/FreeMono.ttf";
  FT_Error error;
  FT_Library library;
  FT_Face face;

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
            200,     /* horizontal device resolution    */
            300 );   /* vertical device resolution      */
  if(error) printf("FT_Set_Char_Size error= %d\n",error);


  FT_GlyphSlot  slot = face->glyph;  /* a small shortcut */


  int i,num_chars = strlen(Text);
  for ( i = 0; i < num_chars; i++ )
  {
    FT_UInt  glyph_index;
    /* retrieve glyph index from character code */
    glyph_index = FT_Get_Char_Index(face, Text[i]);

    /* load glyph image into the slot (erase previous one) */
    error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
    if ( error )
      continue;  /* ignore errors */

    /* convert to an anti-aliased bitmap */
    error = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );
    if ( error )
      continue;

    /* now, draw to our target surface */
    my_draw_bitmap( &slot->bitmap, Px + slot->bitmap_left, Py - slot->bitmap_top );
    /* increment pen position */
    Px += slot->advance.x >> 6;
    Py += slot->advance.y >> 6; /* not useful for now */
  }
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
      // printf("%d-", image[j][i]);
      if(Image[j][i]==0) 
        printf("-");
      else
        printf("0");
    }
    printf("\n");
  }
  //printf("x=%d,y=%d,x_max=%d,y_max=%d,x_max-x=%d,y_max-y=%d\n",x,y,x_max,y_max,x_max-x,y_max-y);
}
