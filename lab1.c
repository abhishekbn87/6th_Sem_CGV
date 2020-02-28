
# include <stdio.h>
# include <stdlib.h>
# include <GL/glut.h>
# include <string.h>

typedef GLfloat point[3];

void drawText(float,float,char *);
void dynamicDraw(float,float,int);

point v[] = { {-1.0,-0.5,0.0},
	      {1.0,-0.5,0.0},
	      {0.0,1.0,0.0},
	      {0.0,0.0,1.0}};

GLfloat color[4][3]={{1.0,0.0,0.0},
		      {0.0,1.0,0.3},
		      {1.0,0.0,1.0},
		      {1.0,1.0,0.0}};
	   
int n;

void triangle (point a,point b,point c)
{
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

void tetra (point a,point b,point c,point d)
{
	glColor3fv(color[0]);
	triangle(a,b,c);
	glColor3fv(color[1]);
	triangle(a,c,d);
	glColor3fv(color[2]);
	triangle(a,d,b);
	glColor3fv(color[3]);
	triangle(b,d,c);
}

void divideTetra (point a,point b,point c,point d,int n)
{
	point mid[6];
	int j;
	if(n>0)
	{
		for(j=0;j<3;j++)
		{
			mid[0][j]=(a[j]+b[j])/2.0;
			mid[1][j]=(a[j]+c[j])/2.0;
			mid[2][j]=(a[j]+d[j])/2.0;
			mid[3][j]=(c[j]+b[j])/2.0;
			mid[4][j]=(c[j]+d[j])/2.0;
			mid[5][j]=(b[j]+d[j])/2.0;
			
		}
		divideTetra(a,mid[0],mid[1],mid[2],n-1);
		divideTetra(mid[0],b,mid[3],mid[5],n-1);
		divideTetra(mid[1],mid[3],c,mid[4],n-1);
		divideTetra(mid[2],mid[5],mid[4],d,n-1);
	}
	else
		tetra(a,b,c,d);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
	divideTetra(v[0],v[1],v[2],v[3],n);
	glColor3f(1.0,1.0,1.0);
	drawText(-0.2,-0.65,"3D Sierpinski Gasket");
	drawText(0.5,0.9,"Abhishek Koushik B N ");
	drawText(0.5,0.8,"USN:1BI17CS005");
	drawText(0.5,0.7,"Batch : A1 ");	
	dynamicDraw(-0.2,-0.75,n);
	glFlush();
}

void myReshape (int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-1.0,1.0,-1.0*(GLfloat)h/(GLfloat)w,1.0*(GLfloat)h/(GLfloat)w,-1.0,1.0);
	else
		glOrtho(-1.0*(GLfloat)w/(GLfloat)h,1.0*(GLfloat)w/(GLfloat)h,-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void drawText(float x,float y,char *s)
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;s[i]!='\0';i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
	}
}

void dynamicDraw(float x,float y,int n)
{	
	printf("Called\n");	
	char s[10];
	int i;	
	
	sprintf(s,"%d",n);
	char result[30] = "Number of divisions = ";
	strcat(result,s);
	glRasterPos2f(x,y);	
	for(i=0;result[i]!='\0';i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,result[i]);
		//printf("%s",result[i]);
	}
		
}	

int main (int argc,char **argv)
{
	printf("Enter the number of subdivisions: ");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("3D Sierpinkski Gasket");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

	
	
