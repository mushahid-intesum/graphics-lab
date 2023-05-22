#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define Width 640
#define Height 480

#define Z0 255, 0, 0
#define Z1 0, 255, 0
#define Z2 0, 0, 255
#define Z3 255, 255, 0
#define Z4 255, 0, 255
#define Z5 0, 255, 255
#define Z6 5, 5, 5
#define Z7 100, 100, 100

int y_bound_max = 100;
int y_bound_min = -100;
int x_bound_max = 100;
int x_bound_min = -100;

int ymax = Height / 2 - 1;
int ymin = -Height / 2;
int xmax = Width / 2 - 1;
int xmin = -Width / 2;
int top = 8;
int bottom = 4;
int right_ = 2;
int left_ = 1;

struct Point
{
    int x;
    int y;

    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }
};

static void reshape(int width, int height);
static void display(void);
static void idle(void);
void myInit();

static void drawAxis(void);
int findZoneNumber(int x0, int y0, int x1, int y1);
void drawPixel(int x, int y, int zone);
void drawLine(int x0, int y0, int x1, int y1);
void drawLine0(int x0, int y0, int x1, int y1, int zone);
void drawGrid(void);
void clipLineCyrusBeak(int x0, int y0, int x1, int y1);
Point find_t(Point p0, Point p1, float t);

Point find_t(Point p0, Point p1, float t)
{
    return Point((int)(p0.x + t * (p1.x - p0.x)), (int)(p0.y + t * (p1.y - p0.y)));
}

void clipLineCyrusBeak(int x0, int y0, int x1, int y1)
{
    float t, te_max = 0.0, tl_min = 1.0;

    float te_x = 0.0, te_y = 0.0;
    float tl_x = 1.0, tl_y = 1.0;
    
    float t_top = (float)(y_bound_max - y0) / (y1 - y0);
    float t_bottom = (float)(y_bound_min- y0) / (y1 - y0);
    float t_right = (float)(x_bound_max - x0) / (x1 - x0);
    float t_left = (float)(x_bound_min - x0) / (x1 - x0);

    if(x1 - x0 > 0)
    {
        tl_x = t_right;
        te_x = t_left;
    }

    else
    {
        tl_x = t_left;
        te_x = t_right;
    }

    if(y1 - y0 > 0)
    {
        tl_y = t_top;
        te_y = t_bottom;
    }

    else
    {
        tl_y = t_bottom;
        te_y = t_top;
    }

    tl_min = min(tl_x, tl_y);
    te_max = max(te_x, te_y);

    if (tl_min <= 1.0 && te_max >= 0.0 && tl_min >= te_max)
    {
        Point p0 = find_t(Point(x0, y0), Point(x1, y1), tl_min);
        Point p1 = find_t(Point(x0, y0), Point(x1, y1), te_max);
        glEnd();
        glPointSize(5);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_POINTS);
        glVertex2i(p0.x, p0.y);
        glVertex2i(p1.x, p1.y);
        glVertex2i(x0, y0);
        glVertex2i(x1, y1);
        glEnd();
        glPointSize(1);

        glBegin(GL_POINTS);
        glColor3f(0.0, 1.0, 0.0);
        drawLine(p0.x, p0.y, p1.x, p1.y);
        glColor3f(0.5, 0.5, 0.5);
        drawLine(x0, y0, p1.x, p1.y);
        glColor3f(0.5, 0.5, 0.5);
        drawLine(p0.x, p0.y, x1, y1);
    }
    else
    {
        cout << "Rejected" << endl;
        glEnd();
        glPointSize(5);
        glColor3f(0.0, 0.0, 255.0);

        glBegin(GL_POINTS);
        glVertex2i(x0, y0);
        glVertex2i(x1, y1);
        glEnd();
        glPointSize(1);
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        drawLine(x0, y0, x1, y1);
    }
}

void drawGrid(void)
{
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_LINES);
    glVertex2i(x_bound_min, ymin);
    glVertex2i(x_bound_min, ymax);
    glVertex2i(x_bound_max, ymin);
    glVertex2i(x_bound_max, ymax);
    glVertex2i(xmin, y_bound_max);
    glVertex2i(xmax, y_bound_max);
    glVertex2i(xmin, y_bound_min);
    glVertex2i(xmax, y_bound_min);

    glEnd();
}

void drawPixel(int x, int y, int zone)
{
    switch (zone)
    {
    case 0:

        glVertex2i(x, y);
        break;
    case 1:

        glVertex2i(y, x);
        break;
    case 2:

        glVertex2i(-y, x);
        break;
    case 3:

        glVertex2i(-x, y);
        break;
    case 4:

        glVertex2i(-x, -y);
        break;
    case 5:

        glVertex2i(-y, -x);
        break;
    case 6:

        glVertex2i(y, -x);
        break;
    case 7:

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
    drawGrid();
    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    int x0 = -150;
    int x1 = 150;
    int y0 = -120;
    int y1 = 120;

    scanf("%d %d %d %d", &x0, &y0, &x1, &y1);

    clipLineCyrusBeak(x0, y0, x1, y1);

    glEnd();
    glFlush();
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