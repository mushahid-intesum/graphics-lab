#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define Width 840
#define Height 680

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

float a = 100;
float l = 300;
float d = 100;

float d_decrement = 10;
float l_decrement = 10;

float theta_x = 0.0;
float theta_y = 0.0;
float theta_z = 0.0;

int ymax = Height / 2 - 1;
int ymin = -Height / 2;
int xmax = Width / 2 - 1;
int xmin = -Width / 2;
int top = 8;
int bottom = 4;
int right_ = 2;
int left_ = 1;

vector<vector<float>> p3d;
vector<vector<float>> p2d;

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
int findZoneNumber(float x0, float y0, float x1, float y1);
void drawPixel(float x, float y, int zone);
void drawLine(float x0, float y0, float x1, float y1);
void drawLine0(float x0, float y0, float x1, float y1, int zone);
void drawGrid(void);
void clipLineCyrusBeak(int x0, int y0, int x1, int y1);
Point find_t(Point p0, Point p1, float t);

void make3DPoints(float a);
void projectTo2DPoints(float l, float d);
void drawCube(void);
void specialKey(int key, int x, int y);

float PI = 3.1416;

void specialKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1:
            d += d_decrement;
            glutPostRedisplay();
            break;
        case GLUT_KEY_F2:
            d -= d_decrement;
            glutPostRedisplay();
            break;

        case GLUT_KEY_F3:
            l += l_decrement;
            glutPostRedisplay();
            break;
        case GLUT_KEY_F4:
            l -= l_decrement;
            glutPostRedisplay();
            break;

        case GLUT_KEY_UP:
            theta_x += (PI / float(180));
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            theta_x -= (PI / float(180));
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            theta_y += (PI / float(180));
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            theta_y -= (PI / float(180));
            glutPostRedisplay();
            break;

        case GLUT_KEY_F5:
            theta_z += (PI / float(180));
            glutPostRedisplay();
            break;
        case GLUT_KEY_F6:
            theta_z -= (PI / float(180));
            glutPostRedisplay();
            break;
    }
}

void make3DPoints(float a)
{
    p3d.push_back({-a, -a, a});
    p3d.push_back({a, -a, a});
    p3d.push_back({a, a, a});
    p3d.push_back({-a, a, a});
    p3d.push_back({-a, -a, -a});
    p3d.push_back({a, -a, -a});
    p3d.push_back({a, a, -a});
    p3d.push_back({-a, a, -a});
}

void projectTo2DPoints(float l, float d)
{
    for (int i = 0; i < 8; i++)
    {
        float x = p3d[i][0];
        float y = p3d[i][1];
        float z = p3d[i][2];
        
        float xp, yp, zp;

        // z axis
        xp = x * cos(theta_z) + y * sin(theta_z);
        yp = -x * sin(theta_z) + y * cos(theta_z);
        x = xp;
        y = yp;

        // x axis
        yp = y * cos(theta_x) + z * sin(theta_x);
        zp = -y * sin(theta_x) + z * cos(theta_x);
        y = yp;
        z = zp;

        // y axis
        xp = x * cos(theta_y) + z * sin(theta_y);
        zp = -x * sin(theta_y) + z * cos(theta_y);
        x = xp;
        z = zp;

        z -= (l + d);
        x = x / (-z / d);
        y = y / (-z / d);
        // z = z / (-z / d);

        cout << theta_x << " " << theta_y << " " << theta_z << endl;
        p2d.push_back({x, y, z});
    }
}

void drawCube(void)
{
    float x0, y0, x1, y1;
    for(int i = 0;i<4;i++)
    {
        x0 = p2d[i%4][0];
        y0 = p2d[i%4][1];
        x1 = p2d[(i+1)%4][0];
        y1 = p2d[(i+1)%4][1];

        drawLine(x0, y0, x1, y1);

        x0 = p2d[i%4 + 4][0];
        y0 = p2d[i%4 + 4][1];
        x1 = p2d[(i+1)%4 + 4][0];
        y1 = p2d[(i+1)%4 + 4][1];

        drawLine(x0, y0, x1, y1);

        x0 = p2d[i%4][0];
        y0 = p2d[i%4][1];
        x1 = p2d[i%4 + 4][0];
        y1 = p2d[i%4 + 4][1];

        drawLine(x0, y0, x1, y1);
    }

    p2d.clear();
    p3d.clear();
}

Point find_t(Point p0, Point p1, float t)
{
    return Point((int)(p0.x + t * (p1.x - p0.x)), (int)(p0.y + t * (p1.y - p0.y)));
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

void drawPixel(float x, float y, int zone)
{
    switch (zone)
    {
    case 0:

        glVertex2f(x, y);
        break;
    case 1:

        glVertex2f(y, x);
        break;
    case 2:

        glVertex2f(-y, x);
        break;
    case 3:

        glVertex2f(-x, y);
        break;
    case 4:

        glVertex2f(-x, -y);
        break;
    case 5:

        glVertex2f(-y, -x);
        break;
    case 6:

        glVertex2f(y, -x);
        break;
    case 7:

        glVertex2f(x, -y);
        break;
    }
}

void drawLine0(float x0, float y0, float x1, float y1, int zone)
{
    float dx = x1 - x0, dy = y1 - y0;

    float delE = 2 * dy, delNE = 2 * (dy - dx);
    float d = 2 * dy - dx;
    float x = x0, y = y0;

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

void drawLine(float x0, float y0, float x1, float y1)
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

int findZoneNumber(float x0, float y0, float x1, float y1)
{
    float dx = x1 - x0;
    float dy = y1 - y0;

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
    // drawGrid();
    drawAxis();
    glPushMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    make3DPoints(a);
    projectTo2DPoints(l, d);
    drawCube();

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
    glutSpecialFunc(specialKey);
    myInit();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}