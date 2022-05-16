/** Program to design an FIR **/

#include "math.h"

float hd[51];	/* ÀíÏëµÄ³å»÷ÏìÓ¦ÏµÊýÐòÁÐ */
float h[51];	/* ¼Ó´°ºóµÄ³å»÷ÏìÓ¦ÏµÊýÐòÁÐ */
float w[51];	/* ´°º¯ÊýµÄÀëÉ¢ÖµÐòÁÐ */
float db[300];  /* ·ù¶ÈÏìÓ¦Êý×é£¨¶ÔÊýÖµ£©£ */
float pi;		/* Ô²ÖÜÂÊpi */
float wc;		/* (½ØÖ¹ÆµÂÊ/pi) */
int n;			/* ´°º¯ÊýÐòÁÐµÄ³¤¶È£¬Ò²ÊÇ¼Ó´°ºóµÄÏìÓ¦ÐòÁÐµÄ³¤¶È */
int m;			/* Ñ¡Ôñ²ÎÊý(1-5):Ñ¡Ôñ²»Í¬µÄ´°º¯Êý */
int l;			/* l>>n */
float im,re;
float a,b,p,wf,d;
float x[300];
float y[300];
int k,i;

main()
{
   	  /* ²ÎÊý³õÊ¼»¯ */
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
      n=21;    /* n<=51, ÎªÆæÊý */
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
      {	/* ÀíÏë¾ØÐÎº¯Êý£¨ÆµÓò£©µÄÊ±ÓòÐÎÊ½ */	
         if(i==a)
            hd[i]=wc;
         else
         {
            b=i-a;
            hd[i]=sin(pi*b*wc)/(pi*b);
         }
      }

      switch(m)  /* ¸ù¾ÝmµÄÖµÑ¡Ôñ²»Í¬µÄ´°º¯Êý */
      {
		
		/* m=1Ê±ÓÃ¾ØÐÎ´° */
         case 1:    			
            for(i=0;i<n;i++)
            w[i]=1.0;  			
         break;
         
         
		/* m=2Ê±ÓÃÈý½Ç´°(°ÍÌØÀ³ÌØ´°) */
         case 2:   				
            for(i=0;i<n;i++)
            {
               if(i>=a)
               w[i]=2.0-2.0*i/(n-1);
               else
               w[i]=2.0*i/(n-1);
            }
         break;


		/* m=3Ê±ÓÃººÄþ´° */
         case 3:   			
            for(i=0;i<n;i++)
              w[i]=0.5*(1.0-cos(2.0*pi*i/(n-1)));
            break;


		/* m=4Ê±ÓÃººÃ÷´° */
         case 4:
            for(i=0;i<n;i++)
              w[i]=0.54-0.46*cos(2.0*pi*(float)i/(n-1));
            break;


		/* m=5Ê±ÓÃ²¼À³¿ËÂü´° */
         case 5:
            for(i=0;i<n;i++)
              w[i]=0.42-0.5*cos(2.0*pi*i/(n-1))+0.08*cos(4.0*pi*i/(n-1));
         break;
      }


      for(i=0;i<n;i++)
         h[i]=hd[i]*w[i];  /* ¶ÔÀíÏë³å»÷ÏìÓ¦¼Ó´°£¨Ê±ÓòÏà³Ë£© */

//new
	  for(i=0;i<300;i++){
		for(k=0;k<n;k++){
			if((i-k)<0) break;
			y[i]+=h[k]*x[i-k];
		}
	  }
      p=pi/l;

      
      /* ¶Ô¼Ó´°ºóµÄÏìÓ¦ÐòÁÐ½øÐÐ¸µÀïÒ¶±ä»»£¬¹Û²ìÆä·ùÆµÏìÓ¦ */
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
         
         d=sqrt(pow(re,2)+pow(im,2)); /*ÇóÄ£(·ù¶È)*/
         db[k]=20.0*log10(d);         /*×ª»»Îª¶ÔÊý±íÊ¾ÐÎÊ½*/
      }
}

