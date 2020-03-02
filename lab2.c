# include <stdio.h>
# include <GL/glut.h>

int x1,x2,Y1,y2;

void init()
{
	glClearColor(0.0,0.5,0.3,1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,500);
}

void drawPixel(int x,int y)
{
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void drawLine(int x1,int x2,int y1,int y2)
{
	int dx,dy,incx,incy,inc1,inc2,i,d,x,y;
	dx = x2-x1;
	dy = y2-y1;
	if(dx<0) dx = -dx;
	if(dy<0) dy = -dy;
	incx = 1;incy=1;
	if(x2<x1) incx = -1;
	if(y2<y1) incy = -1;
	x=x1;
	y=y1;
	if(dx>dy)
	{
		drawPixel(x,y);
		d = 2*dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for(i=0;i<dx;i++)
		{
			if(d>=0)
			{
				y+=incy;
				d+=inc1;
			}
			else
				d+=inc2;
			x+=incx;
			drawPixel(x,y);
			
		}
	}
	else
	{
		drawPixel(x,y);
		d = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for(i=0;i<dy;i++)
		{
			if(d>=0)
			{
				x+=incx;
				d+=inc1;
			}
			else
				d+=inc2;
			y+=incy;
			drawPixel(x,y);
		}
	}
}

void drawText(float x,float y,char *s)
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;s[i]!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[i]);
}

void display()
{
	char start[30],end[30];	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	drawLine(x1,x2,Y1,y2);
	glColor3f(1.0,1.0,1.0);
	drawText(400,400,"1BI17CS005");
	drawText(400,380,"Abhishek Koushik B N");
	drawText(400,360,"Batch:A1");\
	drawText(100,150,"Bresenham's Line Drawing Algorithm");
	sprintf(start,"(%d,%d)",x1,Y1);
	sprintf(end,"(%d,%d)",x2,y2);
	drawText(x1-5,Y1-5,start);
	drawText(x2+3,y2,end);
	glFlush();
}

int main( int argc, char **argv)
{
	printf("Enter the co-ordinates ");
	scanf("%d%d%d%d",&x1,&x2,&Y1,&y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Bresenham's Algorithm");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
	return 0;
}	  
