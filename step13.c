#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
  int w,h;
  unsigned char *data;
}Char; 
typedef struct 
{
  int w,h;
  char f,t;
  Char *all;
}Chars; 

void ReadGlyphs(char* fname,Chars* chars) {
  FILE *finp = fopen(fname, "r");
  fscanf(finp, "%d %d %c %c", &chars->w,&chars->h,&chars->f,&chars->t);
  fgetc(finp);
  int i,d=chars->t-chars->f;
  chars->all = malloc(d*sizeof(Char));
  for(i=0;i<d;i++) 
  {
    fscanf(finp,"%d %d", &chars->all[i].w,&chars->all[i].h);
    int w=chars->all[i].w,h=chars->all[i].h;
    chars->all[i].data = malloc((w*h)*sizeof(unsigned char));
    fgetc(finp);
    fread(chars->all[i].data,sizeof(unsigned char),w*h,finp);
    fgetc(finp);
  }
  fclose(finp);
}
void show(Char* c) {
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

int main(void) {
  Chars chars;
  Read("chars.txt",&chars);
  printf("%d %d %c %c\n", chars.w,chars.h,chars.f,chars.t);
  int i,d=chars.t-chars.f;
  for(i=0;i<d;i++) 
  {
    printf("%d-",i );
    //show(&chars.all[i]);
  }
  printf("\n");
}

