#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void tga(uint8_t *k,int width, int height) {
  for (int i=0;i<54;i++)
    k++;
  uint8_t pixels[width * height * 3];
  uint8_t tga[18] = {0};
  uint8_t *p;
  size_t x, y;

  p = pixels;
  for (x = 0; x < (width*height*3); x=x+3) {
      p[x] = *k++;
      p[x+1] = *k++;
      p[x+2] = *k++;
  }
  tga[2] = 2;

  tga[12] = width & 0xFF;
  tga[13] = (width >> 8) & 0xFF;
  tga[14] = height & 0xFF;
  tga[15] = (height >> 8) & 0xFF;
  tga[16] = 24;
  FILE *fp = fopen("targa.tga","wb");
  fwrite(tga, sizeof(tga), 1, fp);
  fwrite(pixels, sizeof(pixels), 1, fp);
  fclose(fp);
}

int main(int argc, char *argv[])
{
    if(argc<2)
      return 0;
    FILE *fp;
    int i,s;
    uint8_t* k = malloc(sizeof(uint8_t)*4);
    fp = fopen(argv[1],"r");
    fseek(fp,0L,SEEK_END);
    s = ftell(fp);
    rewind(fp);
    k = realloc(k,s*sizeof(uint8_t));
    fread(k,s,sizeof(uint8_t),fp);
    fclose(fp);
    char b = (char)k[0],m = (char)k[1];
    if (b != 'B' && b != 'M')
	    return 0;
    printf("%c%c \n",b,m);
    uint16_t w = k[18];
    w = (k[19]<<8) | w;
    uint16_t h = k[22];
    h = (k[23]<<8) | h;


    tga(k,(int)w,(int)h);
    free(k);
    printf("\n");
    return 0;
}
