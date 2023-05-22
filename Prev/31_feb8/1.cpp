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

int findZoneNumber(int x0, int y0, int x1, int y1);

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

void drawPixel(int x, int y)
{
    glVertex2i(x,y);
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

void drawLine0(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delE = 2 * dy, delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0, y = y0;

    while (x < x1)
    {
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
        drawPixel(x, y);
    }
}

void drawLine1(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delN = -2 * dx, delNE = 2 * (dy - dx);
    int d = dy - 2 * dx;
    int x = x0, y = y0;
    while (y < y1)
    {
        if (d > 0)
        {
            d += delN;
            y++;
        }

        else
        {
            d += delNE;
            x++;
            y++;
        }
        drawPixel(x, y);
    }
}

void drawLine2(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delN = -2 * dx, delNW = -2 * (dy + dx);
    int d = -2 * dx - dy;
    int x = x0, y = y0;
    while (y < y1)
    {
        if (d < 0)
        {
            d += delN;
            y++;
        }

        else
        {
            d += delNW;
            x--;
            y++;
        }
        drawPixel(x, y);
    }
}

void drawLine3(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delW = -2 * dy, delNW = -2 * (dy + dx);
    int d = -2 * dx + dy;
    int x = x0, y = y0;

    while (x > x1)
    {
        if (d > 0)
        {
            d += delW;
            x--;
        }

        else
        {
            d += delNW;
            x--;
            y++;
        }
        drawPixel(x, y);
    }
}

void drawLine4(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delW = -2 * dy, delSW = -2 * (dy - dx);
    int d = dx - 2 * dy;
    int x = x0, y = y0;

    while (x > x1)
    {
        if (d < 0)
        {
            d += delW;
            x--;
        }

        else
        {
            d += delSW;
            x--;
            y--;
        }
        drawPixel(x, y);
    }
}

void drawLine5(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delS = 2 * dx, delSW = -2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0, y = y0;

    while (y > y1)
    {
        if (d > 0)
        {
            d += delS;
            y--;
        }

        else
        {
            d += delSW;
            x--;
            y--;
        }
        drawPixel(x, y);
    }
}

void drawLine6(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;

    int delS = 2 * dx, delSE = 2 * (dy + dx);
    int d = 2 * dx + dy;
    int x = x0, y = y0;

    while (y > y1)
    {
        if (d < 0)
        {
            d += delS;
            y--;
        }

        else
        {
            d += delSE;
            x++;
            y--;
        }
        drawPixel(x, y);
    }
}

void drawLine7(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0, dy = y1 - y0;
    cout << "zone7outer\n";

    int delE = 2 * dy, delSE = 2 * (dy + dx);
    int d = 2 * dx - dy;
    int x = x0, y = y0;

    while (x < x1)
    {
        cout << "zone7\n";
        if (d > 0)
        {
            d += delE;
            x++;
        }

        else
        {
            d += delSE;
            x++;
            y--;
        }
        drawPixel(x, y);
    }
}

void drawLine()
{
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    int r = 200;

    // glColor3ub(128, 128, 128);
    // glPointSize(200.0);
    // glVertex2i(x0, y0);
    // glColor3ub(69, 69, 69);
    // glVertex2i(x1, y1);

    for(int i = 0;i<360;i++)
    {
        x1 = (int)r * cos(i);
        y1 = (int)r * sin(i);
        int zone = findZoneNumber(x0, y0, x1, y1);
        switch (zone)
        {
            case 0:
                glColor3ub(255, 0, 0);
                drawLine0(x0, y0, x1, y1, 0);
                break;
            case 1:
                glColor3ub(0, 255, 0);
                drawLine1(x0, y0, x1, y1, 1);
                break;
            case 2:
                glColor3ub(0, 0, 255);
                drawLine2(x0, y0, x1, y1, 2);
                break;
            case 3:
                glColor3ub(255, 0, 255);
                drawLine3(x0, y0, x1, y1, 3);
                break;
            case 4:
                glColor3ub(255, 255, 0);
                drawLine4(x0, y0, x1, y1, 4);
                break;
            case 5:
                glColor3ub(0, 255, 255);
                drawLine5(x0, y0, x1, y1, 5);
                break;
            case 6:
                glColor3ub(255, 255, 255);
                drawLine6(x0, y0, x1, y1, 6);
                break;
            case 7:
                glColor3ub(128, 128, 0);
                drawLine7(x0, y0, x1, y1, 7);
                break;
        }
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
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxis();
    // glColor3ub(255, 255, 255);
    glPushMatrix();
    glBegin(GL_POINTS);

    drawLine();

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void draw8Way(int x, int y)
{
    drawPixel(x, y);
    drawPixel(y, x);
    drawPixel(-y, x);
    drawPixel(-x, y);
    drawPixel(-x, -y);
    drawPixel(-y, -x);
    drawPixel(y, -x);
    drawPixel(x, -y);
}

void drawCircle(int r)
{
    int x = 0, y = r;
    int d = 5 - 4*r;
    draw8Way(x,y);

    while(x < y)
    {
        if (d < 0)
        {
            d += (2*x + 3) * 4;
            x++;
        }

        else
        {
            d += (2*x - 2*y + 5) * 4;
            x++;
            y--;
        }

        draw8Way(x, y);
    }
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