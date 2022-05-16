#include "stdio.h"
extern unsigned char *i_img;
extern unsigned char *o_img;
extern unsigned char *shadow_buf;
extern unsigned int	palette_size;
extern unsigned long	img_row,img_col,line_size;
main()
{
	char filename[40];
	printf("Please input BMPimage filename[*.bmp]:\n");
	scanf("%s",filename);
	ReadBMPHeadInfo(filename);
	printf("opened\n");		
	i_img = (unsigned char *)alloc_mem(img_row*line_size);
	load_data(filename,i_img);
	o_img = (unsigned char *)alloc_mem(img_row*line_size);
	FanSe(i_img,o_img,line_size,img_row);
	save_data(filename,o_img);
	free(i_img);
	free(o_img);
	printf("zz\n");
}

