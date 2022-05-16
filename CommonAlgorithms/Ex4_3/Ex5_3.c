/* Program for FFT */

#include <math.h>
#include <stdio.h>


const float pi=3.1415926;
int N;							/* FFT点数 */
float x_re[300], x_im[300];	 	/* 输入信号序列 */
float y_re[300], y_im[300];		/* 输出频谱序列 */
float w_re, w_im;				/* 蝶形因子 */
int m;							/* 蝶形运算的级数,即Log2(N) */
float t_re, t_im, v_re, v_im;  	/* 临时变量 */
int j,i,k,f,n;   				
int a, b, c;


main()
{ 	
	N=256;

	/* 初始化数据空间 */
	for(i=0; i<300; i++)
	{
		x_re[i]=0;
		x_im[i]=0;
	}
	/* 设定输入信号序列为单边指数函数 */
	/* 考虑到实际衰减很快，因此可以忽略后面大半部分数值 */
/*	for(i=0;i<=N;i++)
	{
		 x_re[i]=2+3*cos(pi*i/32)+1.5*cos(pi*i/4+pi);
		 x_im[i]=0;		
	}*/
/*	三角ú
	for(i=0;i<=N;i++)
	{
	     if((i%64)<32){
	  	   x_re[i]=0.5-1.0/32*(i%32);
		   x_im[i]=0;
		 }	
		 else {
		  x_re[i]=-0.5+1.0/32*(i%32);
		  x_im[i]=0;
	    }	
	}*/
//	鼐形波
	for(i=0;i<=N;i++)
	{
	     if((i+16)%32==0){
	  	   x_re[i]=0;
		   x_im[i]=0;
		 }	
		 if((i+16)%64>0&&(i+16)%64<32){
		  x_re[i]=0.5;
		  x_im[i]=0;
	    }
	    if((i+16)%64>32){
		  x_re[i]=-0.5;
		  x_im[i]=0;
	    }	
	}	
	/* 复制到输出数组 */
	for(i=0; i<300; i++)
	{
		y_re[i]=x_re[i];
		y_im[i]=x_im[i];
	}

	/* 用雷德算法对输入信号序列进行倒序重排 */
  	j=0;
  	for(i=0;i<N;i++)
  	{	
  		if(i<j)
  		{ 
  		  t_re=y_re[j]; 
  		  t_im=y_im[j]; 
  		  y_re[j]=y_re[i]; 
  		  y_im[j]=y_im[i];
  		  y_re[i]=t_re;
		  y_im[i]=t_im;
  		}
  		k=N/2;
  		while((k<=j)&(k>0))
  		{ 
  		  j=j-k; 
  		  k=k/2;
  		}
  		j=j+k;
    }
    
    /* 计算蝶形运算的级数log2(N) */
	f=N;
	for(m=1; (f=f/2)!=1; m++);
	
    
    /*** FFT ***/
    for(n=1; n<=m; n++)
    {   
    	a=1;				/* a=2的n次方 */
    	for(i=0;i<n;i++)
    		a=a*2;
    	
    	b=a/2;
    	
    	v_re=1.0; 			/* 蝶形因子 */
    	v_im=0.0;
    	w_re=cos(pi/b);		
    	w_im=-sin(pi/b);
    	
    	for(j=0;j<b;j++)	/* 蝶形运算 */
    	{
    		for(i=j;i<N;i=i+a)
    		{
    			c=i+b;
   
       			t_re=y_re[c]*v_re-y_im[c]*v_im;
    			t_im=y_re[c]*v_im+y_im[c]*v_re;
    			
    			y_re[c]=y_re[i]-t_re;
    			y_im[c]=y_im[i]-t_im;
    			
    			y_re[i]=y_re[i]+t_re;
    			y_im[i]=y_im[i]+t_im;
    		}
    		
    		t_re=v_re*w_re-v_im*w_im;
    		t_im=v_re*w_im+v_im*w_re;
    		
    		v_re=t_re;
    		v_im=t_im;
    	}
    }
    
}


