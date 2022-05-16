/** Program to design an FIR **/

#include "math.h"

float hd[51];	/* ����ĳ����Ӧϵ������ */
float h[51];	/* �Ӵ���ĳ����Ӧϵ������ */
float w[51];	/* ����������ɢֵ���� */
float db[300];  /* ������Ӧ���飨����ֵ��� */
float pi;		/* Բ����pi */
float wc;		/* (��ֹƵ��/pi) */
int n;			/* ���������еĳ��ȣ�Ҳ�ǼӴ������Ӧ���еĳ��� */
int m;			/* ѡ�����(1-5):ѡ��ͬ�Ĵ����� */
int l;			/* l>>n */
float im,re;
float a,b,p,wf,d;
float x[300];
float y[300];
int k,i;

main()
{
   	  /* ������ʼ�� */
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
      n=21;    /* n<=51, Ϊ���� */
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
      {	/* ������κ�����Ƶ�򣩵�ʱ����ʽ */	
         if(i==a)
            hd[i]=wc;
         else
         {
            b=i-a;
            hd[i]=sin(pi*b*wc)/(pi*b);
         }
      }

      switch(m)  /* ����m��ֵѡ��ͬ�Ĵ����� */
      {
		
		/* m=1ʱ�þ��δ� */
         case 1:    			
            for(i=0;i<n;i++)
            w[i]=1.0;  			
         break;
         
         
		/* m=2ʱ�����Ǵ�(�������ش�) */
         case 2:   				
            for(i=0;i<n;i++)
            {
               if(i>=a)
               w[i]=2.0-2.0*i/(n-1);
               else
               w[i]=2.0*i/(n-1);
            }
         break;


		/* m=3ʱ�ú����� */
         case 3:   			
            for(i=0;i<n;i++)
              w[i]=0.5*(1.0-cos(2.0*pi*i/(n-1)));
            break;


		/* m=4ʱ�ú����� */
         case 4:
            for(i=0;i<n;i++)
              w[i]=0.54-0.46*cos(2.0*pi*(float)i/(n-1));
            break;


		/* m=5ʱ�ò��������� */
         case 5:
            for(i=0;i<n;i++)
              w[i]=0.42-0.5*cos(2.0*pi*i/(n-1))+0.08*cos(4.0*pi*i/(n-1));
         break;
      }


      for(i=0;i<n;i++)
         h[i]=hd[i]*w[i];  /* ����������Ӧ�Ӵ���ʱ����ˣ� */

//new
	  for(i=0;i<300;i++){
		for(k=0;k<n;k++){
			if((i-k)<0) break;
			y[i]+=h[k]*x[i-k];
		}
	  }
      p=pi/l;

      
      /* �ԼӴ������Ӧ���н��и���Ҷ�任���۲����Ƶ��Ӧ */
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
         
         d=sqrt(pow(re,2)+pow(im,2)); /*��ģ(����)*/
         db[k]=20.0*log10(d);         /*ת��Ϊ������ʾ��ʽ*/
      }
}

