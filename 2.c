https://www.youtube.com/watch?v=fTjNkbLBEqg
http://www.englisch-hilfen.de/en/exercises_list/alle_grammar.htm
http://www.perfect-english-grammar.com/grammar-exercises.html
http://www.english-4u.de/grammar_exercises.htm
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ft2build.h>
#include "/home/dev/golab/ft/glyphs.h"

#include FT_FREETYPE_H

char *FontFileName = "/usr/share/fonts/truetype/tlwg/Sawasdee.ttf";

FT_Error error;
FT_Library library;
FT_Face face;
FT_GlyphSlot  slot;

int ResolutionFactor= 2; 
Chars chars;


void init();
int createText(char c,Char* cha);
void Write(char* fname,Chars* chars);
void Read(char* fname,Chars* chars);
void show(Char* c);
int main(void) {
  int i;


  chars.w = ResolutionFactor * 160;
  chars.h = ResolutionFactor * 90;
  //chars.name = "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
  chars.name = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  //chars.name = "afg";
  chars.l=strlen(chars.name);
  printf("%d\n",chars.l);
  chars.all = malloc(chars.l*sizeof(Char));
  init();
  for(i=0;i<chars.l;i++) {
    Char cha;
    chars.all[i] = cha;
    createText(chars.name[i],&chars.all[i]);
  }
  for(i=0;i<chars.l;i++) 
    show(&chars.all[i]);
  //Write("chars.txt",&chars);


  // Read("chars.txt",&chars);
  // printf("%d %d %d %s\n", chars.w,chars.h,chars.l,chars.name);
  // for(i=0;i<chars.l;i++) 
  //   show(&chars.all[i]);

  //printf("%s\n", Text);
}

void Write(char* fname,Chars* chars){
  int i;
  FILE *fout = fopen(fname, "w");
  fprintf(fout, "%d %d %d %s\n", chars->w, chars->h, chars->l, chars->name );
  for(i=0;i<chars->l;i++) 
  {
    //printf("%d\n", i);
    int w=chars->all[i].w,h=chars->all[i].h;
    fprintf(fout,"%d %d %d %d %d", w,h, chars->all[i].a, chars->all[i].bx, chars->all[i].by);
    fwrite(chars->all[i].data,sizeof(unsigned char),w*h,fout);
    //fprintf(fout,"\n");
  }
  //fwrite(&chars, sizeof(Chars), 1, fout);
  fclose(fout);
}

void Read(char* fname,Chars* chars) {
  int i;
  FILE *finp = fopen(fname, "r");
  // fscanf(finp, "%d %d %d %s", &chars->w, &chars->h, &chars->l, chars->name);
  fscanf(finp, "%d %d %d ", &chars->w, &chars->h, &chars->l);
  chars->name = (char*) malloc(chars->l * sizeof(char));
  fscanf(finp, "%s\n", chars->name);

  chars->all = (Char*) malloc(chars->l*sizeof(Char));
  for(i = 0 ; i < chars->l ; i++) 
  {
    fscanf(finp,"%d %d %d %d %d", &chars->all[i].w,&chars->all[i].h,&chars->all[i].a,&chars->all[i].bx,&chars->all[i].by);
    int w=chars->all[i].w,h=chars->all[i].h;
    chars->all[i].data = malloc((w*h)*sizeof(unsigned char));
    //fgetc(finp);
    fread(chars->all[i].data,sizeof(unsigned char),w*h,finp);
    //fgetc(finp);
  }
  fclose(finp);
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
int createText(char c,Char* cha){
  FT_UInt  glyph_index;
  glyph_index = FT_Get_Char_Index(face, c);
  error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
  if ( error ) { printf("e  %d",error); return error; } 
  error = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );
  if ( error ) { printf("e1 %d",error); return error; }
  FT_Bitmap* bitmap = &slot->bitmap;
  int i,j;
  FT_Int x0 = slot->bitmap_left, y0 = slot->bitmap_top , w = bitmap->width , h = bitmap->rows ;
  //printf("x0=%d;y0=%d;w=%d;h=%d\n",x0,y0,w,h );
  cha->w=w;
  cha->h=h;
  cha->a = slot->advance.x >> 6;
  cha->bx=x0;
  cha->by=y0;
  cha->data = malloc(w*h*sizeof(unsigned char));
  for ( i=0; i<w*h; i++ ) cha->data[i] = bitmap->buffer[i];
  // {
  //   if(bitmap->buffer[i]==0) 
  //   {
  //     printf("-");
  //   }  
  //   else
  //   {
  //     printf("0");
  //   } 
  //   if ( (i+1)%w==0 ) printf("\n");
  // }
  return 0;
} 

void show(Char* c) {
  printf("a=%d bx=%d by=%d w=%d h=%d\n",c->a,c->bx,c->by,c->w,c->h );
  int i;
  for ( i=0; i<(c->w*c->h); i++ )
  {
    if(c->data[i]==0) 
    {
      printf("-");
    }  
    else
    {
      printf("0");
    } 
    if ( (i+1)%c->w==0 ) printf("\n");
  }
}