#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define Width 512
#define Height 512

#define Z0 255, 0, 0
#define Z1 0, 255, 0
#define Z2 0, 0, 255
#define Z3 255, 255, 0
#define Z4 255, 0, 255
#define Z5 0, 255, 255
#define Z6 5, 5, 5
#define Z7 100, 100, 100

static void reshape(int width, int height);
static void display(void);
static void idle(void);
void myInit();

static void drawAxis(void);
int findZoneNumber(int x0, int y0, int x1, int y1);
void drawPixel(int x, int y, int zone);
void drawLine(int x0, int y0, int x1, int y1);
void drawLine0(int x0, int y0, int x1, int y1, int zone);

void drawPixel(int x, int y, int zone)
{
    switch (zone)
    {
    case 0:
        glColor3ub(255, 0, 0);
        glVertex2i(x, y);
        break;
    case 1:
        glColor3ub(0, 255, 0);
        glVertex2i(y, x);
        break;
    case 2:
        glColor3ub(0, 0, 255);
        glVertex2i(-y, x);
        break;
    case 3:
        glColor3ub(255, 0, 255);
        glVertex2i(-x, y);
        break;
    case 4:
        glColor3ub(255, 255, 0);
        glVertex2i(-x, -y);
        break;
    case 5:
        glColor3ub(0, 255, 255);
        glVertex2i(-y, -x);
        break;
    case 6:
        glColor3ub(255, 255, 255);
        glVertex2i(y, -x);
        break;
    case 7:
        glColor3ub(128, 128, 0);
        glVertex2i(x, -y);
        break;
    }
}

void drawLine0(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delE = 2 * dy, delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0, y = y0;

    while (x <= x1)
    {
        drawPixel(x, y, zone);
        if (d < 0)
        {
            d += delE;
            x++;
        }

        else
        {
            d += delNE;
            x++;
            y++;
        }
    }
}

void drawLine(int x0, int y0, int x1, int y1)
{
    int zone = findZoneNumber(x0, y0, x1, y1);

    switch (zone)
    {
    case 0:
        drawLine0(x0, y0, x1, y1, zone);
        break;
    case 1:
        drawLine0(y0, x0, y1, x1, zone);
        break;
    case 2:
        drawLine0(y0, -x0, y1, -x1, zone);
        break;
    case 3:
        drawLine0(-x0, y0, -x1, y1, zone);
        break;
    case 4:
        drawLine0(-x0, -y0, -x1, -y1, zone);
        break;
    case 5:
        drawLine0(-y0, -x0, -y1, -x1, zone);
        break;
    case 6:
        drawLine0(-y0, x0, -y1, x1, zone);
        break;
    case 7:
        drawLine0(x0, -y0, x1, -y1, zone);
        break;
    }
}

int findZoneNumber(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    if (abs(dx) >= abs(dy))
    {
        if (dx >= 0 && dy >= 0)
        {
            return 0;
        }

        if (dx >= 0 && dy < 0)
        {
            return 7;
        }

        if (dx < 0 && dy >= 0)
        {
            return 3;
        }

        if (dx < 0 && dy < 0)
        {
            return 4;
        }
    }

    else
    {
        if (dx >= 0 && dy >= 0)
        {
            return 1;
        }

        if (dx >= 0 && dy < 0)
        {
            return 6;
        }

        if (dx < 0 && dy >= 0)
        {
            return 2;
        }

        if (dx < 0 && dy < 0)
        {
            return 5;
        }
    }
    return 0;
}

static void reshape(int width, int height)
{
    // const int ar = (int) width / (int) height;
    glViewport(0, 0, width, height);
    // project = array, jetate display = oitao array
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    // glOrtho(-Width/2, Width/2 ,  -Height/2, Height/2, -1, 1);
    glOrtho(-Width / 2, Width / 2, -Height / 2, Height / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void drawAxis(void)
{
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glBegin(GL_LINES);

    glVertex2i(-Width / 2, 0);
    glVertex2i(Width / 2, 0);
    glVertex2i(0, Height / 2);
    glVertex2i(0, -Height / 2);

    glEnd();
    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxis();
    glPushMatrix();
    glBegin(GL_POINTS);
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    int r = 200;

    for(int i = 0;i<360;i++)
    {
        x1 = (int)r * cos(i);
        y1 = (int)r * sin(i);
        drawLine(0,0,x1,y1);
    }

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

void myInit()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GlutShapes");
    myInit();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}