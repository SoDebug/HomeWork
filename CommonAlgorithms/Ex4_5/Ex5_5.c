/** Program to design an FIR **/

#include "math.h"

float hd[51];	/* 理想的冲击响应系数序列 */
float h[51];	/* 加窗后的冲击响应系数序列 */
float w[51];	/* 窗函数的离散值序列 */
float db[300];  /* 幅度响应数组（对数值）� */
float pi;		/* 圆周率pi */
float wc;		/* (截止频率/pi) */
int n;			/* 窗函数序列的长度，也是加窗后的响应序列的长度 */
int m;			/* 选择参数(1-5):选择不同的窗函数 */
int l;			/* l>>n */
float im,re;
float a,b,p,wf,d;
float x[300];
float y[300];
int k,i;

main()
{
   	  /* 参数初始化 */
      for(i=0;i<51;i++)
      {		
      	hd[i]=0;
      	h[i]=0;
      	w[i]=0;
      }

	  for(i=0;i<300;i++)
      {		
      	db[i]=0;
      }
            
      m=3;     
      n=21;    /* n<=51, 为奇数 */
      wc=0.2;  /* wc=0.10-0.90 */
      l=300;   
      a=(n-1)/2;
      pi=4.0*atan(1.0);
//new	  
	  for(i=0;i<300;i++){
		x[i]=sin(pi*(wc/4)*i)+sin(pi*(wc*4)*i);
		y[i]=0;
	  }

      for(i=0;i<n;i++)
      {	/* 理想矩形函数（频域）的时域形式 */	
         if(i==a)
            hd[i]=wc;
         else
         {
            b=i-a;
            hd[i]=sin(pi*b*wc)/(pi*b);
         }
      }

      switch(m)  /* 根据m的值选择不同的窗函数 */
      {
		
		/* m=1时用矩形窗 */
         case 1:    			
            for(i=0;i<n;i++)
            w[i]=1.0;  			
         break;
         
         
		/* m=2时用三角窗(巴特莱特窗) */
         case 2:   				
            for(i=0;i<n;i++)
            {
               if(i>=a)
               w[i]=2.0-2.0*i/(n-1);
               else
               w[i]=2.0*i/(n-1);
            }
         break;


		/* m=3时用汉宁窗 */
         case 3:   			
            for(i=0;i<n;i++)
              w[i]=0.5*(1.0-cos(2.0*pi*i/(n-1)));
            break;


		/* m=4时用汉明窗 */
         case 4:
            for(i=0;i<n;i++)
              w[i]=0.54-0.46*cos(2.0*pi*(float)i/(n-1));
            break;


		/* m=5时用布莱克曼窗 */
         case 5:
            for(i=0;i<n;i++)
              w[i]=0.42-0.5*cos(2.0*pi*i/(n-1))+0.08*cos(4.0*pi*i/(n-1));
         break;
      }


      for(i=0;i<n;i++)
         h[i]=hd[i]*w[i];  /* 对理想冲击响应加窗（时域相乘） */

//new
	  for(i=0;i<300;i++){
		for(k=0;k<n;k++){
			if((i-k)<0) break;
			y[i]+=h[k]*x[i-k];
		}
	  }
      p=pi/l;

      
      /* 对加窗后的响应序列进行傅里叶变换，观察其幅频响应 */
      for(k=0;k<=l-1;k++)
      {
         wf=(pi*k)/l;
         re=0.0;
         im=0.0;
         
         for(i=0;i<n;i++)
         {
            re=re+h[i]*cos((float)i*wf);
            im=im+h[i]*sin((float)i*wf);
         }
         
         d=sqrt(pow(re,2)+pow(im,2)); /*求模(幅度)*/
         db[k]=20.0*log10(d);         /*转换为对数表示形式*/
      }
}

