# include <stdio.h>
# include <math.h>
# include <GL/glut.h>

GLfloat triangle[3][3] = {{-100,0,100},{100,300,100},{1,1,1}};
GLfloat rotatemap[3][3] = {{0},{0},{0}};
GLfloat result[3][3] = {{0},{0},{0}};
GLfloat x=0,y=0;
float angle;

void multiply()
{
	int i,j,k;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			result[i][j] = 0;
			for(k=0;k<3;k++)
				result[i][j] += rotatemap[i][k]*triangle[k][j];
		}
}
void rotate()
{
	GLfloat m,n;
	angle = (angle*3.14)/180;
	m = x*(1-cos(angle))+y*sin(angle);
	n = y*(1-cos(angle))-x*sin(angle);
	rotatemap[0][0] = cos(angle);
	rotatemap[0][1] = -sin(angle);
	rotatemap[0][2] = m;
	rotatemap[1][0] = sin(angle);
	rotatemap[1][1] = cos(angle);
	rotatemap[1][2] = n;
	rotatemap[2][0] = 0;
	rotatemap[2][1] = 0;
	rotatemap[2][2] = 1;
	multiply();
}

void draw (GLfloat v[3][3], GLfloat c[3])
{
	glColor3fv(c);
	glBegin(GL_LINE_LOOP);
	glVertex2f(v[0][0],v[1][0]);
	glVertex2f(v[0][1],v[1][1]);
	glVertex2f(v[0][2],v[1][2]);
	glEnd();
}
void drawText(float x,float y,char *s)
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;s[i]!='\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,s[i]);
}

void display()
{
	char point1[50],point2[50],point3[50],theta[50];	
	int i,j,flag=0;
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat color1[3] = {1.0,0.0,0.0};
	GLfloat color2[3] = {0.5,1.0,0.0};
	sprintf(point1,"(%.1f,%.1f)-B",triangle[0][0],triangle[1][0]);
	sprintf(point2,"(%.1f,%.1f)-A",triangle[0][1],triangle[1][1]);
	sprintf(point3,"(%.1f,%.1f)-C",triangle[0][2],triangle[1][2]);
	draw(triangle,color1);
	draw(result,color2);
	glColor3f(0.0,0.0,0.0);
	drawText(triangle[0][0]-15,triangle[1][0]-15,point1);
	drawText(triangle[0][1],triangle[1][1]+15,point2);
	drawText(triangle[0][2],triangle[1][2]-10,point3);
	sprintf(point1,"(%.1f,%.1f)-B",result[0][0],result[1][0]);
	sprintf(point2,"(%.1f,%.1f)-A",result[0][1],result[1][1]);
	sprintf(point3,"(%.1f,%.1f)-C",result[0][2],result[1][2]);
	drawText(result[0][0]-15,result[1][0]-15,point1);
	drawText(result[0][1],result[1][1]+15,point2);
	drawText(result[0][2],result[1][2]-10,point3);
	drawText(0,0,"Abhishek Koushik B N");
	drawText(0,-15,"1BI17CS005");
	drawText(0,-30,"2D Triangle Rotation");

	sprintf(theta,"Rotation angle = %.0f",angle);
	drawText(0,-45,theta);
	glFlush();
}

void init()
{
	glLineWidth(2);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-499,499,-499,499);
	angle = angle*180/3.14;
}

int main(int argc,char **argv)
{
	int choice;
	printf("Enter the choice: \n\t 1. Rotation about the origin\n\t 2. Rotation about a fixed point: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: printf("Enter the rotation angle(degrees): ");
			scanf("%f",&angle);
			rotate();
			break;
		case 2: printf("Enter the fixed point: ");
			scanf("%f%f",&x,&y);
			printf("Enter the rotation angle(degrees): ");
			scanf("%f",&angle);
			rotate();
			break;
	}
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("Rotation");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}




