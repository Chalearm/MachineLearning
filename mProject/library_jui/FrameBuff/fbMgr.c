#include <linux/fb.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <math.h>
#define NAMEFILE "j.txt"
#define NAMELENGTH 50
#define TIMEOUT 2
#define NUMSHAPE 2000
#define MAX_SIZE_IMG_X 500
#define MAX_SIZE_IMG_Y 500
#define PI_VALUE 3.1415926535897932384626433832795028841971

struct shapeData
{
    int m_x;
    int m_y;
    char m_type;
    int m_width_r;
    int m_height;
    unsigned char m_r,m_g,m_b;
    float m_startAng;
    float m_stopAng;
};
struct point
{
    int m_x,m_y;
    unsigned long m_color;
};
struct rectShape /* or line*/
{
    int m_x,m_y; /* top-left*/
    int m_width,m_height;
    unsigned long m_color;
};
struct circle
{
    int m_x,m_y; /* origin point*/  
    int m_radius;
    int m_isSolid;
    unsigned long m_color;
};
struct circleArc
{
    int m_x,m_y; /* origin point*/  
    int m_radius;
    float m_startAng;
    float m_stopAng;
    int m_isSolid;
    unsigned long m_color;
};
struct shapeList
{
    char *m_types;  /*
                         -1 is NULL
                          0 is point
                          1 is rect
                          2 is circle
                          3 is line
                          4 is circle arc
                    */
    void **m_objs;
    int m_numList;
    int m_sizeList;
};
struct saveImgHandle
{
    int x,y,width,height,m_ret;
    unsigned int img[MAX_SIZE_IMG_X][MAX_SIZE_IMG_Y];
};

inline uint32_t pixel_color(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo)
{
	return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}

struct renderHandler
{
	struct fb_fix_screeninfo m_finfo;
	struct fb_var_screeninfo m_vinfo;
    int m_fb_fd;
    uint8_t *m_fbp;
    int m_ret;
};
void initSaveImgHandle(struct saveImgHandle *obj,int x,int y,int width,int height);
void savePicture(struct renderHandler *obj,struct saveImgHandle *obj2,const char *fp);
void loadPicture(struct renderHandler *obj,struct saveImgHandle *obj2,const char *fp);
void drawPicture(struct renderHandler *obj,struct saveImgHandle *obj2);
void initialRenderHandle(struct renderHandler *obj);
void destructorRenderHandle(struct renderHandler *obj);
void floodColor(struct renderHandler *obj,unsigned char r,unsigned char g,unsigned char b);
void plotPoint(struct renderHandler *obj,int x,int y,unsigned long colour);
char readFile(FILE **fp,const char *filename,unsigned char *r,unsigned char *g,unsigned char *b,char **savedFile,struct shapeData *obj);

void constructShapeDat(struct shapeData *obj);
void constructCircle(struct circle *obj);
void constructRect(struct rectShape *obj);
void* constructorPoint(void *val);
void constructorPoints(struct point *obj,int numPoint); 
void constructShapeList(struct shapeList *obj,int sizeList);
void destructShapeList(struct shapeList *obj);

void printShapeList(struct shapeList *obj);
void removeEleInShapeListByIndex(struct shapeList *obj,int index);

void drawAllShape(struct renderHandler *obj,struct shapeList *objL);
void drawRect(struct renderHandler *obj,struct rectShape *objr);
void drawCircle(struct renderHandler *obj,struct circle *objc);
void drawCirArc(struct renderHandler *obj,struct circleArc *objca);
void drawPoint(struct renderHandler *obj,struct point *objp);
void drawLine(struct renderHandler *obj,struct rectShape *objr);

void addAShape2List(struct renderHandler *obj,struct shapeList *objSL,struct shapeData *objSD);

int main()
{/* initialize random seed: */
  srand (time(NULL));
    struct shapeList sList; 
    struct shapeData sd;
    char *savedFile =NULL;
    struct saveImgHandle svImg;
    clock_t time1=clock();
    struct renderHandler renderH;
    initialRenderHandle(&renderH);
    char inputCh =0;
    int breakLp=1;
    FILE *fpp=NULL;
    unsigned char cR=0,cG=0,cB=0; 
    struct circle c1;
    constructShapeList(&sList,NUMSHAPE);
    savedFile = malloc(sizeof(char)*NAMELENGTH);
    memset((void*)savedFile,0,NAMELENGTH);
    constructCircle(&c1);
    
    c1.m_x =145;
    c1.m_y =145;
    c1.m_radius =80;
    c1.m_color =pixel_color(0xFF,0xFF,0, &(renderH.m_vinfo));
    constructShapeDat(&sd);
    initSaveImgHandle(&svImg,0,0,MAX_SIZE_IMG_X,MAX_SIZE_IMG_Y);
    while(breakLp)
    {
        if((((float)(clock()-time1))/CLOCKS_PER_SEC) >TIMEOUT)
        {
            time1 = clock();
            inputCh = readFile(&fpp,NAMEFILE,&cR,&cG,&cB,&savedFile,&sd);
        }
        switch(inputCh)
        {
            case '1': 
                floodColor(&renderH,0xFF,0x00,0xFF);
            break;
            case '2': 
                floodColor(&renderH,0xFF,0x00,0x00);
            break;
            case '3':  
                floodColor(&renderH,0x00,0xFF,0x00);
            break;
            case '4':  
                fprintf(stderr,"current Color : R:%02x G:%02x B:%02x\n",cR,cG,cB);
            break;
            case '8':  
                floodColor(&renderH,cR,cG,cB);
            break;
            case '9':  
                savePicture(&renderH,&svImg,savedFile);
            break;
            case 'a':  
                loadPicture(&renderH,&svImg,savedFile);
            break;
            case 'b':  
                drawPicture(&renderH,&svImg);
                drawAllShape(&renderH,&sList);
            break;
            case 'c':  
                drawCircle(&renderH,&c1);
            break;
            case 'e':
                addAShape2List(&renderH,&sList,&sd);
            break;
            case 'f':
                printShapeList(&sList);
            break;
            case 'g':
                removeEleInShapeListByIndex(&sList,sd.m_x);
            break;
            case 'q': 
                fprintf(stderr,"Quit\n");
                breakLp=0;
            break;
        }
        inputCh = '\0';
    }
    free(savedFile);
    /*floor black*/
    int ii=0;
    int kk=0;
    int jj=0;
    int aa=0;
    int bb=0;
    int cc=0;
    for(;;)
    {
        if((((float)(clock()-time1))/CLOCKS_PER_SEC) >0.09)
        {
            time1 = clock();
            ii = rand() % 3;
            jj = rand()%2;
            kk = rand()%5;
            if(jj ==1)
            {
                kk = -kk;
            }
            else
            {
            }
            if(ii ==0)
            {
            aa = (kk+aa)%256;
            }
            else if(ii==1)
            {
            bb = (kk+bb)%256;
            }
            else if(ii==2)
            {
            cc = (kk+cc)%256;
            }
            floodColor(&renderH,aa,bb,cc);
        //printf("%d %d %d %d\n",aa,bb,cc,ii);
        }
    }
    destructShapeList(&sList);
    destructorRenderHandle(&renderH);
	return 0;
}


void constructShapeList(struct shapeList *obj,int sizeList)
{
    int index=0;
    if((obj!=NULL)&&(sizeList>0))
    {
        obj->m_types = (char*)malloc(sizeof(char)*sizeList);    
        obj->m_objs = (void**)malloc(sizeof(void*)*sizeList);
        obj->m_numList =0;
        obj->m_sizeList = sizeList;
        for(index=0;index<sizeList;index++)
        {
            obj->m_types[index] = -1;
            obj->m_objs[index] = NULL; 
        }
    }
    else if(obj!=NULL)
    {
        obj->m_types = NULL;
        obj->m_objs = NULL;
        obj->m_numList = 0;
        obj->m_sizeList = 0;
    }
    else
    {
        /* do nothing */
    }
}

void constructShapeDat(struct shapeData *obj)
{
    if(obj!=NULL)
    {
        obj->m_x =0;
        obj->m_y =0;
        obj->m_type =0;
        obj->m_width_r =0;
        obj->m_height =0;
        obj->m_startAng =0.0;
        obj->m_stopAng =0.0;
    }
    else
    {
        /* do nothing */
    }
}
void destructShapeList(struct shapeList *obj)
{
    int index=0;
    int num =0;
    if(obj!=NULL)
    { 
        if(obj->m_types !=NULL)
        {
            free(obj->m_types);
            obj->m_types =NULL;
        }
        else
        {
            /* do nothing */
        } 
        if(obj->m_objs !=NULL)
        {
            num =obj->m_numList;
            for(index=0;index<num;index++)
            {
                free(obj->m_objs[index]);
            }
            
            free(obj->m_objs);
            obj->m_objs =NULL;
        }
        else
        {
            /* do nothing */
        }
        obj->m_numList=0;
        obj->m_sizeList=0;
    }
    else
    {
        /* do nothing */
    }
}
void constructCircle(struct circle *obj)
{
    if(obj!=NULL)
    {
        obj->m_x =0;
        obj->m_y =0;
        obj->m_radius =0;
        obj->m_isSolid =0;
        obj->m_color = 0xFFFFFFFF;
    }
    else
    {
        /* do nothing */
    }
}
void constructRect(struct rectShape *obj)
{
    if(obj!=NULL)
    {
        obj->m_x =0;
        obj->m_y =0;
        obj->m_width =0;
        obj->m_height =0;
        obj->m_color = 0xFFFFFFFF;
    }
    else
    {
        /* do nothing */
    }
}
void* constructorPoint(void *val)
{
    struct point *obj = (struct point*)val;
    if(obj!=NULL)
    {
        obj->m_x =0;
        obj->m_y =0;
        obj->m_color = 0xFFFFFFFF;
    }
    else
    {
        /* do nothing */
    }
    return NULL;
}

void constructorPoints(struct point *obj,int numPoint)
{
    int index=0;
    if((obj!=NULL)&&(numPoint >0))
    {
        for(index=0;index<numPoint;index++)
        {
            constructorPoint((void*)&obj[index]);
        }
    }
}
 
void initialRenderHandle(struct renderHandler *obj)
{
    int ret =0;
    long screensize;
    if(obj!=NULL)
    {	
        obj->m_fb_fd = open("/dev/fb0",O_RDWR); 
        obj->m_ret = (obj->m_fb_fd>0);
        ret = obj->m_ret;
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        //Get variable screen information
        ioctl(obj->m_fb_fd, FBIOGET_VSCREENINFO, &(obj->m_vinfo));
        obj->m_vinfo.grayscale=0;
        obj->m_vinfo.bits_per_pixel=32;
        ioctl(obj->m_fb_fd, FBIOPUT_VSCREENINFO, &(obj->m_vinfo));
        ioctl(obj->m_fb_fd, FBIOGET_VSCREENINFO, &(obj->m_vinfo));

        ioctl(obj->m_fb_fd, FBIOGET_FSCREENINFO, &(obj->m_finfo));
        
        screensize = obj->m_vinfo.yres_virtual * obj->m_finfo.line_length;
        obj->m_fbp = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, obj->m_fb_fd, (off_t)0);
        obj->m_ret = (obj->m_fbp!=NULL);
    }
    else
    {
        /* do nothing */
    }

}
void destructorRenderHandle(struct renderHandler *obj)
{
    long screensize;
    if(obj==NULL)
    {
        /* do nothing*/
    }
    else if(obj->m_ret ==1)
    {
        close(obj->m_fb_fd);
        screensize = obj->m_vinfo.yres_virtual * obj->m_finfo.line_length;
        munmap (obj->m_fbp, screensize);
    }
    else
    {
        /* do nothing */
    }
}

void floodColor(struct renderHandler *obj,unsigned char r,unsigned char g,unsigned char b)
{

	int x,y;
    if(obj!=NULL)
    {
        for (x=0;x<obj->m_vinfo.xres;x++)
            for (y=0;y<obj->m_vinfo.yres;y++)
            {
                long location = (x+obj->m_vinfo.xoffset) * (obj->m_vinfo.bits_per_pixel/8) + (y+obj->m_vinfo.yoffset) * obj->m_finfo.line_length;
                *((uint32_t*)(obj->m_fbp + location)) = pixel_color(r,g,b, &(obj->m_vinfo));
            }
    }
    else
    {
        /* do nothing */
    }
}

void plotPoint(struct renderHandler *obj,int x,int y,unsigned long colour)
{
    long location =0;
    if(obj!=NULL)
    {
        if((x<obj->m_vinfo.xres)&&(y<obj->m_vinfo.yres))
        {
            location = (x+obj->m_vinfo.xoffset) * (obj->m_vinfo.bits_per_pixel/8) + (y+obj->m_vinfo.yoffset) * obj->m_finfo.line_length;
            *((uint32_t*)(obj->m_fbp + location)) = colour;
        }
    }
    else
    {
        /* do nothing */
    }
}
char readFile(FILE **fp,const char *filename,unsigned char *r,unsigned char *g,unsigned char *b,char **savedFile,struct shapeData *obj)
{
    char ch =0; 
    int tempa,tempb,tempc;
    *fp = fopen(filename,"r");
    if((*fp ==NULL)&&(obj!=NULL))
    {
        *fp=fopen(filename,"w");
        /*cmd R G B filename type x y w(r) h*/
        fprintf(*fp,"0 0 0 0 0 0 0 0 0 0 0 0");        
        fclose(*fp);
    }
    else if( obj!=NULL)
    {
        fscanf(*fp,"%c %d %d %d %s %c %d %d %d %d %f %f",&ch,&tempa,&tempb,&tempc,*savedFile,&(obj->m_type),&(obj->m_x),&(obj->m_y),&(obj->m_width_r),&(obj->m_height),&(obj->m_startAng),&(obj->m_stopAng));
        *r = (unsigned char)tempa;
        *g = (unsigned char)tempb;
        *b = (unsigned char)tempc;
        obj->m_r = *r;
        obj->m_g = *g;
        obj->m_b = *b;
        fclose(*fp);
        *fp=fopen(filename,"w");
        fprintf(*fp,"0 0 0 0 0 0 0 0 0 0 0 0");        
        fclose(*fp);
    }
    return ch;
}

void initSaveImgHandle(struct saveImgHandle *obj,int x,int y,int width,int height)
{
    if(obj!=NULL)
    {
        obj->x =x;
        obj->y =y;
        obj->width =width;
        obj->height =height;
        obj->m_ret =(width>0)&(height>0)&(x>-1)&(y>-1); 
    }
    else
    {
        /* do nothing */
    }
}

void savePicture(struct renderHandler *obj,struct saveImgHandle *obj2,const char *fp)
{
    int width =0;
    int height=0;
    FILE *fpp=NULL;
    if((fp!=NULL)&&(obj!=NULL)&&(obj2!=NULL))
    {
        fpp = fopen(fp,"w");
        width = obj2->x+obj2->width;
        height = obj2->y+obj2->height;
        if(width > obj->m_vinfo.xres)
        {
            width = obj->m_vinfo.xres;
        }
        if(height > obj->m_vinfo.yres)
        {
            height = obj->m_vinfo.yres;
        } 
        int x,y;
        for (y=obj2->y;y<height;y++)
            for (x=obj2->x;x<width;x++)
            {
                long location = (x+obj->m_vinfo.xoffset) * (obj->m_vinfo.bits_per_pixel/8) + (y+obj->m_vinfo.yoffset) * obj->m_finfo.line_length;
                 obj2->img[y][x] = *((uint32_t*)(obj->m_fbp + location));
            }
          fwrite (obj2 , sizeof(struct saveImgHandle), 1, fpp);
          fclose(fpp);
    }
}

void loadPicture(struct renderHandler *obj,struct saveImgHandle *obj2,const char *fp)
{
    int width =0;
    int height=0;
    FILE *fpp=NULL;
    int ret =0;
    if((fp!=NULL)&&(obj!=NULL)&&(obj2!=NULL))
    {
        
        fpp = fopen(fp,"r");
        ret = fread (obj2,1,sizeof(struct saveImgHandle),fpp);
        fclose(fpp);
        if(ret>0)
        {
            drawPicture(obj,obj2);
        }
    }
    else
    {
        /* do nothing */
    }
}

void drawPicture(struct renderHandler *obj,struct saveImgHandle *obj2)
{
    int width =0;
    int height=0;
    int x,y;
    int sizeCpy =0;
    if((obj!=NULL)&&(obj2!=NULL))
    {            
        width = obj2->x+obj2->width;
        height = obj2->y+obj2->height;
       
        if(width > obj->m_vinfo.xres)
        {
            width = obj->m_vinfo.xres;
        }
        if(height > obj->m_vinfo.yres)
        {
            height = obj->m_vinfo.yres;
        } 
        /*
        int x,y;
        for (y=obj2->y;y<height;y++)
            for (x=obj2->x;x<width;x++)
            {
                long location = (x+obj->m_vinfo.xoffset) * (obj->m_vinfo.bits_per_pixel/8) + (y+obj->m_vinfo.yoffset) * obj->m_finfo.line_length;
                *((uint32_t*)(obj->m_fbp + location)) =obj2->img[x][y] ;
            }
            */
         sizeCpy = sizeof(int)*width;
        for (y=obj2->y;y<height;y++)
        {
                 long location = (obj2->x+obj->m_vinfo.xoffset) * (obj->m_vinfo.bits_per_pixel/8) + (y+obj->m_vinfo.yoffset) * obj->m_finfo.line_length;
                 memcpy(((void*)(obj->m_fbp + location)),&(obj2->img[y][obj2->x]),sizeCpy); 
        }
  
    }
    else
    {
        /* do nothing */
    }
}
/*

struct circle
{
    int m_x,m_y;  
    int m_radius;
    int m_isSolid;
    unsigned long m_color;
};

struct shapeList
{
    char *m_types;   
                         -1 is NULL
                          0 is point
                          1 is rect
                          2 is circle
                          3 is line
                          4 is circle arc
                    
    void **m_objs;
    int m_numList;
    int m_sizeList;
*/

void drawAllShape(struct renderHandler *obj,struct shapeList *objL)
{
    int index=0;
    int num=0;
    if((obj!=NULL)&&(objL!=NULL))
    {
        num = objL->m_numList;
        for(index=0;index<num;index++)
        {
            if(objL->m_types[index] == 0)
            {
                drawPoint(obj,(struct point*)(objL->m_objs[index]));
            }
            else if(objL->m_types[index] == 1)  /* rect*/
            {
                drawRect(obj,(struct rectShape*)(objL->m_objs[index]));
            }
            else if(objL->m_types[index] == 2) /* circle*/
            {
                drawCircle(obj,(struct circle*)(objL->m_objs[index]));
            }
            else if(objL->m_types[index] == 3) /* line*/
            {
                drawLine(obj,(struct rectShape*)(objL->m_objs[index]));
            }
            else if(objL->m_types[index] == 4) /* circle arc*/
            {
                drawCirArc(obj,(struct circleArc*)(objL->m_objs[index]));
            }
        }
    }
    else
    {
        /* do nohting */
    }
}
void drawLine(struct renderHandler *obj,struct rectShape *objr)
{
    int t, distance;
    int xerr=0, yerr=0, delta_x, delta_y;
    int incx, incy;
    int startx,starty,endx,endy;
    if((obj!=NULL)&&(objr!=NULL))
    {
        /* compute the distances in both directions */
        startx = objr->m_x;
        starty = objr->m_y;
        endx = objr->m_width;
        endy = objr->m_height;
        delta_x=endx-startx;
        delta_y=endy-starty;
     
        /* Compute the direction of the increment,
           an increment of 0 means either a horizontal or vertical
           line.
        */
        if(delta_x>0) incx=1;
        else if(delta_x==0) incx=0;
        else incx=-1;
     
        if(delta_y>0) incy=1;
        else if(delta_y==0) incy=0;
        else incy=-1;
     
        /* determine which distance is greater */
        delta_x=abs(delta_x);
        delta_y=abs(delta_y);
        if(delta_x>delta_y) distance=delta_x;
        else distance=delta_y;
     
        /* draw the line */
        for(t=0; t<=distance+1; t++) 
        { 
            plotPoint(obj,startx,starty,objr->m_color); 
            xerr+=delta_x;
            yerr+=delta_y;
            if(xerr>distance) {
                xerr-=distance;
                startx+=incx;
            }
            if(yerr>distance) {
                yerr-=distance;
                starty+=incy;
            }
        }
    }
    else
    {
        /* do nothing */
    }
}
void drawPoint(struct renderHandler *obj,struct point *objp)
{    
    plotPoint(obj,objp->m_x,objp->m_y,objp->m_color); 
}
void drawRect(struct renderHandler *obj,struct rectShape *objr)
{
    struct rectShape  objrT[4];
    int index=0;
    if((obj!=NULL)&&(objr!=NULL))
    {
        objrT[0]  = *objr;
        objrT[0].m_width = objr->m_x+objr->m_width;
        objrT[0].m_height = objr->m_y;
        objrT[1]  = *objr;
        objrT[1].m_x = objr->m_x+objr->m_width;
        objrT[1].m_width = objrT[1].m_x;
        objrT[1].m_height = objr->m_y+objr->m_height;
        objrT[2]  = *objr; 
        objrT[2].m_y = objr->m_y+objr->m_height;
        objrT[2].m_width =objr->m_x+objr->m_width;
        objrT[2].m_height = objrT[2].m_y;
        objrT[3]  = *objr;  
        objrT[3].m_width =objr->m_x;
        objrT[3].m_height = objr->m_y+objr->m_height;
        for(index=0;index<4;index++)
        {
            drawLine(obj,&objrT[index]);
        }
    }
    else
    {
        /* do nothing */
    }
}
void drawCircle(struct renderHandler *obj,struct circle *objc)
{
    int x = 0, y =0;
    int x0 = 0, y0 =0;
    int dp = 0;
    int i =0;
    int countPoint=0;
    if((obj!=NULL)&&(objc!=NULL))
    {
        x0 = objc->m_x;
        y0 = objc->m_y;
        y = objc->m_radius;
        dp = 1 - objc->m_radius; 
        do
        {
            if (dp < 0)
                dp = dp + 2 * (++x) + 3;
            else
                dp = dp + 2 * (++x) - 2 * (--y) + 5;
 
            plotPoint(obj,x0 + x, y0 + y,objc->m_color);     //For the 8 octants
            plotPoint(obj,x0 - x, y0 + y,objc->m_color);
            plotPoint(obj,x0 + x, y0 - y,objc->m_color);
            plotPoint(obj,x0 - x, y0 - y,objc->m_color);
            plotPoint(obj,x0 + y, y0 + x,objc->m_color);
            plotPoint(obj,x0 - y, y0 + x,objc->m_color);
            plotPoint(obj,x0 + y, y0 - x,objc->m_color);
            plotPoint(obj,x0 - y, y0 - x,objc->m_color);
            countPoint +=8;
            /*
printf("\n");
printf("%d : (%d,%d)\n",i++,x0 + x, y0 + y); 
printf("%d : (%d,%d)\n",i++,x0 - x, y0 + y); 
printf("%d : (%d,%d)\n",i++,x0 + x, y0 - y); 
printf("%d : (%d,%d)\n",i++,x0 - x, y0 - y); 
printf("%d : (%d,%d)\n",i++,x0 + y, y0 + x); 
printf("%d : (%d,%d)\n",i++,x0 - y, y0 + x); 
printf("%d : (%d,%d)\n",i++,x0 + y, y0 - x); 
printf("%d : (%d,%d)\n",i++,x0 - y, y0 - x); 
i=0;
printf("\n");*/
            
        } while (x < y); 
    }
    else
    
    {
        /* do nothing */
    }
}

void drawCirArc(struct renderHandler *obj,struct circleArc *objca)
{
    int x = 0, y =0;
    int x0 = 0, y0 =0;
    int dp = 0;
    int i =0;
    int countPoint=0; 
    double xVectRight,yVectRight;
    double pi= acos(-1); 
    double xStr,yStr;
    double xStp,yStp;
    double midX,midY;
    if((obj!=NULL)&&(objca!=NULL))
    {
        x0 = objca->m_x;
        y0 = objca->m_y;
        y = objca->m_radius;
        dp = 1 - objca->m_radius;
        /*  gradient vector, the vector of end and start point multiple by rotate -90 degree matrix*/
        xStr =  objca->m_radius*sin(objca->m_startAng*pi/180.0);
        yStr =  (-1)*objca->m_radius*cos(objca->m_startAng*pi/180.0);
        xStp =  objca->m_radius*sin(objca->m_stopAng*pi/180.0);
        yStp =  (-1)*objca->m_radius*cos(objca->m_stopAng*pi/180.0);
        midX = (xStr+xStp)/2;
        midY = (yStr+yStp)/2;
        xVectRight = yStr-yStp;
        yVectRight = xStp-xStr;/*
        printf("start : (%f,%f) , %f\n",xStr,yStr,objca->m_startAng);
        printf("stop : (%f,%f), %f\n",xStp,yStp,objca->m_stopAng);
        printf("xN,yN : (%f,%f)\n",xVectRight,yVectRight);*/ 
        do
        { 
            if (dp < 0)
                dp = dp + 2 * (++x) + 3;
            else
                dp = dp + 2 * (++x) - 2 * (--y) + 5;
            if(((xVectRight*(x-midX))+(yVectRight*(y-midY)))>=0)
            {
                plotPoint(obj,x0 + x, y0 + y,objca->m_color);     //For the 8 octants
                countPoint++;
         //    printf("(%d,%d)\n",x,y);
            }
            if(((xVectRight*(-x-midX))+(yVectRight*(y-midY)))>=0)
            {
                plotPoint(obj,x0 - x, y0 + y,objca->m_color);
                countPoint++;
          //printf("(%d,%d)\n",-x,y);
            }            
            if(((xVectRight*(x-midX))+(yVectRight*(-y-midY)))>=0)
            {
                plotPoint(obj,x0 + x, y0 - y,objca->m_color);
                countPoint++;
          // printf("(%d,%d)\n",x,-y);
            }
            if(((xVectRight*(-x-midX))+(yVectRight*(-y-midY)))>=0)
            {
                plotPoint(obj,x0 - x, y0 - y,objca->m_color);
                countPoint++;
          // printf("(%d,%d)\n",-x,-y);
            }
            if(((xVectRight*(y-midX))+(yVectRight*(x-midY)))>=0)
            {
                plotPoint(obj,x0 + y, y0 + x,objca->m_color);
                countPoint++;
           //  printf("(%d,%d)\n",y,x);
            }
            if(((xVectRight*(-y-midX))+(yVectRight*(x-midY)))>=0)
            {
                plotPoint(obj,x0 - y, y0 + x,objca->m_color);
                countPoint++;
           // printf("(%d,%d)\n",-y,x);
            }
            if(((xVectRight*(y-midX))+(yVectRight*(-x-midY)))>=0)
            {
                plotPoint(obj,x0 + y, y0 - x,objca->m_color);
                countPoint++;
           //  printf("(%d,%d)\n",y,-x);
            }
            if(((xVectRight*(-y-midX))+(yVectRight*(-x-midY)))>=0)
            {
                plotPoint(obj,x0 - y, y0 - x,objca->m_color);
                countPoint++;
        //    printf("(%d,%d)\n",-y,-x);
            } 
        } while (x < y); 
        printf("num point(%.2f,%.2f,%d) : %d\n",objca->m_startAng,objca->m_stopAng,objca->m_radius,countPoint);
        struct rectShape lobj;
        lobj.m_x = x0+xStr;
        lobj.m_y = y0+yStr;
        lobj.m_width =x0+ xStp;
        lobj.m_height =y0+yStp;
        lobj.m_color = objca->m_color;
        drawLine(obj,&lobj);
    }
    else
    
    {
        /* do nothing */
    }
}
/*
struct shapeData
{
    int m_x;
    int m_y;
    char m_type;
    int m_width_r;
    int m_height;
};

struct shapeList
{
    char *m_types;  / 
                         -1 is NULL
                          0 is point
                          1 is rect
                          2 is circle
                          3 is line
                          4 is circle arc
                 
    void **m_objs;
    int m_numList;
    int m_sizeList;
*/
void addAShape2List(struct renderHandler *obj,struct shapeList *objSL,struct shapeData *objSD)
{
    struct circle *pc1 = NULL;
    struct circleArc *pca1=NULL;
    struct point *pp1 =NULL;
    struct rectShape *pr1 =NULL;
    if((obj!=NULL)&&(objSL!=NULL)&&(objSD!=NULL))
    {
        if(objSL->m_numList >= objSL->m_sizeList)
        {
            /* do nothing */
        }
        else if((objSD->m_type =='a')&&(objSD->m_width_r>0)) /*circle */
        {
            pca1 =(struct circleArc*)malloc(sizeof(struct circleArc));
            pca1->m_x =objSD->m_x; 
            pca1->m_y =objSD->m_y; 
            pca1->m_startAng =objSD->m_startAng; 
            pca1->m_stopAng  =objSD->m_stopAng; 
            pca1->m_radius =objSD->m_width_r; 
            pca1->m_color = pixel_color(objSD->m_r,objSD->m_g,objSD->m_b, &(obj->m_vinfo));
            objSL->m_types[objSL->m_numList] = 4;
            objSL->m_objs[objSL->m_numList++] =(void*)pca1;
        }
        else if((objSD->m_type =='c')&&(objSD->m_width_r>0)) /*circle */
        {
            pc1 =(struct circle*)malloc(sizeof(struct circle));
            pc1->m_x =objSD->m_x; 
            pc1->m_y =objSD->m_y; 
            pc1->m_radius =objSD->m_width_r; 
            pc1->m_color = pixel_color(objSD->m_r,objSD->m_g,objSD->m_b, &(obj->m_vinfo));
            objSL->m_types[objSL->m_numList] = 2;
            objSL->m_objs[objSL->m_numList++] =(void*)pc1;
        }
        else if(objSD->m_type =='p')
        {
            pp1 =(struct point*)malloc(sizeof(struct point));
            pp1->m_x =objSD->m_x; 
            pp1->m_y =objSD->m_y; 
            pp1->m_color = pixel_color(objSD->m_r,objSD->m_g,objSD->m_b, &(obj->m_vinfo));
            objSL->m_types[objSL->m_numList] = 0; /*  0 is point  */
            objSL->m_objs[objSL->m_numList++] =(void*)pp1;
        }
        else if((objSD->m_height>0)&&(objSD->m_width_r>0)&&(objSD->m_type =='r'))
        {
            pr1 =(struct rectShape*)malloc(sizeof(struct rectShape));
            pr1->m_x =objSD->m_x; 
            pr1->m_y =objSD->m_y; 
            pr1->m_width =objSD->m_width_r; 
            pr1->m_height =objSD->m_height; 
            pr1->m_color = pixel_color(objSD->m_r,objSD->m_g,objSD->m_b, &(obj->m_vinfo));
            objSL->m_types[objSL->m_numList] = 1; /* rectangle*/
            objSL->m_objs[objSL->m_numList++] =(void*)pr1;
        }
        else if((objSD->m_height>0)&&(objSD->m_width_r>0)&&(objSD->m_type =='l'))
        {
            pr1 =(struct rectShape*)malloc(sizeof(struct rectShape));
            pr1->m_x =objSD->m_x; 
            pr1->m_y =objSD->m_y; 
            pr1->m_width =objSD->m_width_r; 
            pr1->m_height =objSD->m_height; 
            pr1->m_color = pixel_color(objSD->m_r,objSD->m_g,objSD->m_b, &(obj->m_vinfo));
            objSL->m_types[objSL->m_numList] = 3; /* line*/
            objSL->m_objs[objSL->m_numList++] =(void*)pr1;
        }
    }
    else
    {
    
    }
}
/*
    0 is point
  1 is rect
  2 is circle
  3 is line
  4 is circle arc
*/
void printShapeList(struct shapeList *obj)
{    
    struct circle *pc1 = NULL;
    struct circleArc *pca1 = NULL;
    struct point *pp1 =NULL;
    struct rectShape *pr1 =NULL;
    int index=0;
    int num=0;
    char ch=0;
    if(obj!=NULL)
    {
        num = obj->m_numList;
        for(index=0;index<num;index++)
        {  
            if(obj->m_types[index] == 0)/* point*/
            {
                pp1 = (struct point*)obj->m_objs[index];
                printf("i:%d p (%d,%d) c: %08x\n",index,pp1->m_x,pp1->m_y,pp1->m_color);
            }
            else if(obj->m_types[index] == 1) /* rect*/
            {
                pr1 = (struct rectShape*)obj->m_objs[index];
                printf("i:%d r str(%d,%d), w:%d,h:%d c: %08x\n",index,pr1->m_x,pr1->m_y,pr1->m_width,pr1->m_height,pr1->m_color);
            }
            else if(obj->m_types[index] == 2)/* circle*/
            {
                pc1 = (struct circle*)obj->m_objs[index];
                printf("i:%d c (%d,%d) r:%d c: %08x\n",index,pc1->m_x,pc1->m_y,pc1->m_radius,pc1->m_color);
            }
            else if(obj->m_types[index] == 3) /* line*/
            {
                pr1 = (struct rectShape*)obj->m_objs[index];
                printf("i:%d l str(%d,%d), end(%d,%d) c: %08x\n",index,pr1->m_x,pr1->m_y,pr1->m_width,pr1->m_height,pr1->m_color);
            }
            else if(obj->m_types[index] == 4) /* circle arc*/
            {
                pca1 = (struct circleArc*)obj->m_objs[index];
                printf("i:%d c (%d,%d) r:%d  ang:(%f,%f) c: %08x\n",index,pca1->m_x,pca1->m_y,pca1->m_radius,pca1->m_startAng,pca1->m_stopAng,pca1->m_color);
            }
        }
    }
    else
    {
        /* do nothing */
    }
}
void removeEleInShapeListByIndex(struct shapeList *obj,int index)
{
    void *p =NULL;
    if((obj!=NULL)&&(index>=0))
    {
        if(index<obj->m_numList)
        {
            p = obj->m_objs[index];
            if(p!=NULL)
            {
                free(p);
                if((index+1)==obj->m_numList)
                {
                    obj->m_numList--;
                    obj->m_types[index] =-1;
                }
                else
                {
                    obj->m_objs[index] = obj->m_objs[obj->m_numList-1];
                    obj->m_types[index] =obj->m_types[obj->m_numList-1];
                    obj->m_objs[obj->m_numList-1] =NULL;
                    obj->m_types[obj->m_numList-1] =-1;
                    obj->m_numList--;
                }
            }
            else
            {
                /* do nothing */
            }
       }
       else
       {
            /* do nothing*/
       }
    }
    else
    {
        /* do nothing */
    }
}