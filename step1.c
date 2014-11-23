
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H



int main(void) {
	const char *FontFileName = "/usr/share/cups/fonts/FreeMono.ttf";
	FT_Error error;
	FT_Library library;
	FT_Face face,face0;
	
	FILE *FontFilePointer = fopen(FontFileName, "r");
	fseek(FontFilePointer, 0L, SEEK_END);
	long FontFileSize = ftell(FontFilePointer);
	fseek(FontFilePointer, 0L, SEEK_SET);
	printf("%ld\n",FontFileSize );
    
    FT_Byte *buffer; 
    fread(buffer, 1, FontFileSize, FontFilePointer);

	error = FT_Init_FreeType(&library);
	if(error) printf("FT_Init_FreeType error= %d\n",error);
	error = FT_New_Face(library, FontFileName,	0, &face);
	if(error==FT_Err_Unknown_File_Format){
		printf("unknown FT_Err_Unknown_File_Format\n");
	}else if(error){
		printf("error %d\n",error);
	}
	//printf("face->size=%ld\n",face->size );
	printf("face->num_faces=%ld\n",face->num_faces );
	printf("face->num_glyphs=%ld\n",face->num_glyphs );

	error = FT_Set_Char_Size(
            face,    /* handle to face object           */
            0,       /* char_width in 1/64th of points  */
            16*64,   /* char_height in 1/64th of points */
            300,     /* horizontal device resolution    */
            300 );   /* vertical device resolution      */
    

    error = FT_Set_Pixel_Sizes(
            face,   /* handle to face object */
            0,      /* pixel_width           */
            16 );   /* pixel_height          */
  	glyph_index = FT_Get_Char_Index( face,  "U+1F028" );




  	
	// error=FT_New_Memory_Face(library,buffer,FontFileSize,0,&face);
	// if(error) printf("FT_Init_FreeType error= %d\n",error);
	// printf("face->num_faces=%ld\n",face->num_faces );
	// printf("face->num_glyphs=%ld\n",face->num_glyphs );
	printf("end\n" );

	return 0;
}


