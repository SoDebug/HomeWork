#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#define ff(i,j) ip[(long)(i)*lx+j]
#define gg(i,j)	jp[(long)(i)*lx+j]

struct BMP_Head
{
	char	ID[2];
	unsigned FileLength0,FileLength1,FileLength2,FileLength3;
	int		Reserved1;
	int		Reserved2;
	int		Reserved3;
	int		Reserved4;
	unsigned		ImagePosition0,ImagePosition1,ImagePosition2,ImagePosition3;
	unsigned		HeadLength0,HeadLength1,HeadLength2,HeadLength3;
	unsigned		ImageWidth0,ImageWidth1,ImageWidth2,ImageWidth3;
	unsigned		ImageHeight0,ImageHeight1,ImageHeight2,ImageHeight3;	
	int		BitPlane,BitPlane1;
	int		ColorBit,ColorBit1;
	unsigned		CompressMethod0,CompressMethod1,CompressMethod2,CompressMethod3;
	unsigned		ImageLength0,ImageLength1,ImageLength2,ImageLength3;
	unsigned		HorizontalDefinition0,HorizontalDefinition1,HorizontalDefinition2,HorizontalDefinition3;
	unsigned		VerticalDefinition0,VerticalDefinition1,VerticalDefinition2,VerticalDefinition3;
	unsigned		UsedColorNumber0,UsedColorNumber1,UsedColorNumber2,UsedColorNumber3;
	unsigned		ImportantColorNumber0,ImportantColorNumber1,ImportantColorNumber2,ImportantColorNumber3;
	unsigned long	FileLength,ImagePosition,HeadLength,ImageWidth,ImageHeight;
	unsigned long   CompressMethod,ImageLength,HorizontalDefinition,VerticalDefinition,UsedColorNumber,ImportantColorNumber;
}bmp_head;

struct BMP_Palette
{
	unsigned  	paletter[256][4];
}bmp_palette;

unsigned char   *i_img;
unsigned char   *o_img;
unsigned char   *shadow_buf;
unsigned int	palette_size,T;/*origin value=unsigned int	palette_size;*/
unsigned long	img_row,img_col,line_size;

void ReadBMPHeadInfo(filename)
char *filename;
{
	FILE	*fp;
	unsigned int bmphead_size;
	fp = fopen(filename,"rb");
	if(fp == NULL)
	{
		printf("cannot open this file\n");
		exit(0);
	}
	bmphead_size=(sizeof(bmp_head)-22);
	fread(&bmp_head,bmphead_size,1,fp);
	bmp_head.FileLength=bmp_head.FileLength0+bmp_head.FileLength1*0x0100+bmp_head.FileLength2*0x010000+bmp_head.FileLength3*0x01000000;
	bmp_head.ImagePosition=bmp_head.ImagePosition0+bmp_head.ImagePosition1*0x0100+bmp_head.ImagePosition2*0x010000+bmp_head.ImagePosition3*0x01000000;
	bmp_head.HeadLength=bmp_head.HeadLength0+bmp_head.HeadLength1*0x0100+bmp_head.HeadLength2*0x010000+bmp_head.HeadLength3*0x01000000;
	bmp_head.ImageWidth=bmp_head.ImageWidth0+bmp_head.ImageWidth1*0x0100+bmp_head.ImageWidth2*0x010000+bmp_head.ImageWidth3*0x01000000;
	bmp_head.ImageHeight=bmp_head.ImageHeight0+bmp_head.ImageHeight1*0x0100+bmp_head.ImageHeight2*0x010000+bmp_head.ImageHeight3*0x01000000;
	bmp_head.CompressMethod=bmp_head.CompressMethod0+bmp_head.CompressMethod1*0x0100+bmp_head.CompressMethod2*0x010000+bmp_head.CompressMethod3*0x01000000;
	bmp_head.ImageLength=bmp_head.ImageLength0+bmp_head.ImageLength1*0x0100+bmp_head.ImageLength2*0x010000+bmp_head.ImageLength3*0x01000000;
	bmp_head.HorizontalDefinition=bmp_head.HorizontalDefinition0+bmp_head.HorizontalDefinition1*0x0100+bmp_head.HorizontalDefinition2*0x010000+bmp_head.HorizontalDefinition3*0x01000000;
	bmp_head.VerticalDefinition=bmp_head.VerticalDefinition0+bmp_head.VerticalDefinition1*0x0100+bmp_head.VerticalDefinition2*0x010000+bmp_head.VerticalDefinition3*0x01000000;
	bmp_head.UsedColorNumber=bmp_head.UsedColorNumber0+bmp_head.UsedColorNumber1*0x0100+bmp_head.UsedColorNumber2*0x010000+bmp_head.UsedColorNumber3*0x01000000;
	bmp_head.ImportantColorNumber=bmp_head.ImportantColorNumber0+bmp_head.ImportantColorNumber1*0x0100+bmp_head.ImportantColorNumber2*0x010000+bmp_head.ImportantColorNumber3*0x01000000;
	if((bmp_head.ID[0]!='B')&&(bmp_head.ID[1]!='M'))
	{
		printf("this file is not BMP file\n");
		fclose(fp);
		exit(0); 
	}

	palette_size = bmp_head.ImagePosition-(sizeof(bmp_head)-22);
	
	fread(&bmp_palette,1,palette_size,fp);
	img_row = bmp_head.ImageHeight;//16
	img_col = bmp_head.ImageWidth;//15
	line_size = ((bmp_head.ImageWidth*bmp_head.ColorBit+31)/32)*4;
	fclose(fp);
}

void load_data(filename,in_img)
char *filename;
unsigned char *in_img;
{
	FILE *fp;
	int	i;
	unsigned  char *buffer;
	fp = fopen(filename,"rb");
	fseek(fp,bmp_head.ImagePosition,0);
	buffer = in_img;
	for(i=0;i<img_row;i++)
	{
		fread((void *)buffer,line_size,1,fp);
		buffer += line_size;
	}
	fclose(fp);
}

unsigned char *alloc_mem(buffer_size)
unsigned long buffer_size;
{
	unsigned char *mem_ptr;
	if(buffer_size>0x4000) //origin value = 0x2000
	{
		printf("no enough memory");
		exit(0);
	}
	mem_ptr = (unsigned char *)malloc(buffer_size);
	if(mem_ptr == NULL)
	{
		printf("cannot allocate memory\n");
		exit(0);
	}	
	return(mem_ptr);
}

void save_data(filename,buffer)
char *filename;
unsigned char *buffer;
{
	int i;
	FILE *fp;
	fp = fopen(filename,"rb+");
	if(fp == NULL)
		exit(0);
	fseek(fp,bmp_head.ImagePosition,0);	
	for(i=0;i<img_row;i++)
	{
		if(fwrite((void *)buffer,line_size,1,fp)!=1)
			printf("file write error\n");
		buffer+=line_size;
	}
	fclose(fp);
}

void FanSe(ip,jp,lx,ly)
unsigned char *ip,*jp;
unsigned long lx,ly;
{
	unsigned long i,j;
		
	for(i=0;i<ly;i++)
		for(j=0;j<lx;j++)
		{
			gg(i,j)=0;
		}
	T = 128;	/*origin value= */
	for(i=0;i<ly;i++)
		for(j=0;j<lx;j++)
		{
			if(ff(i,j)>=T)	/*origin value= */
			{				/*origin value= */
				gg(i,j)=255;/*origin value= */
			}				/*origin value= */
			/*deleted gg(i,j)=256-1-ff(i,j);*/
			else{			/*origin value= */
				gg(i,j)=0;	/*origin value= */
			}				/*origin value= */
		}	
}


