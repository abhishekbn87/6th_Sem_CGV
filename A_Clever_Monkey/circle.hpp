# include <GL/glut.h>
#include <math.h>
class Circle
{
private:
    int depthIndex;
    float color[3];

public:
    void setColor(float r, float g, float b)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
    void draw(int r, float xpos, float ypos, int depthIndex, bool hollow,int startAngle,int endAngle)
    {
        this->depthIndex = depthIndex;
        glPushMatrix();
        glTranslatef(xpos, ypos, 0);
        glColor3fv(color);
        if (!hollow)
            glBegin(GL_POLYGON);
        else
            {
                glPointSize(5);
                glBegin(GL_POINTS);
            }
        for (int i = startAngle; i <= endAngle; i++)
        {
            float x = r * cos((i * 3.142) / 180);
            float y = r * sin((i * 3.142) / 180);
            glVertex3f(x, y, depthIndex);
        }
        glEnd();
        glPopMatrix();
    }
};
