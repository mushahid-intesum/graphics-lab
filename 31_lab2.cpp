#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
#include <stdlib.h>
#include <stdio.h>

#define Width 640
#define Height 480

int ymax = Height/2;
int ymin = -Height/2;
int xmax = Width/2;
int xmin = -Width/2;

double dx = 20;
double dy = 20;
int r = 10;

double a = 0,b = 0;
 
static int slices = 16;
static int stacks = 16;
#define LINE_COUNT 10
 
int lineCoords[LINE_COUNT][4];
 
int generateRandX() {
    return (rand() % 640) - 320;
}
 
int generateRandY() {
    return (rand() % 480) - 240;
}
 
void generateLines() {
    for (int i = 0; i < LINE_COUNT; i++) {
        lineCoords[i][0] = generateRandX();
        lineCoords[i][1] = generateRandY();
        lineCoords[i][2] = generateRandX();
        lineCoords[i][3] = generateRandY();
    }
}
 
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
 
int findZone (int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    if (dx >= 0 and dy >= 0)
    {
        if (dx >= dy)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if (dx < 0 and dy >= 0)
    {
        if (-dx >= dy)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }
    else if (dx < 0 and dy < 0)
    {
        if (-dx >= -dy)
        {
             return 4;
        }
        else
        {
             return 5;
        }
    }
    else
    {
        if (dx >= -dy)
        {
           return 7;
        }
        else
        {
            return 6;
        }
    }
}
 
void drawPixel(double x, double y)
{
    glVertex2f(x, y);
}
 
 
void draw8way(double x, double y){
    drawPixel(x+a, y+b);
    drawPixel(y+a, x+b);
    drawPixel(-y+a, x+b);
    drawPixel(-x+a, y+b);
    drawPixel(-x+a, -y+b);
    drawPixel(-y+a, -x+b);
    drawPixel(y+a, -x+b);
    drawPixel(x+a, -y+b);
}
 
 
void drawCircle1(int r){
    double x0 = 0;
    double y0 = r;
    int d = 5 - 4*r;
    draw8way(x0, y0);
    while(x0 < y0){
        if(d < 0){
            d += ((2*x0 + 3) * 4);
            x0++;
        }else{
            d += ((2*x0 - 2*y0 + 5) * 4);
            x0++;
            y0--;
        }
        draw8way(x0, y0);
    }
}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-Width/2, 0);
    glVertex2i(Width/2, 0);
    glVertex2i(0, -Height/2);
    glVertex2i(0, Height/2);
    glEnd();
 
    glPointSize(2);
    glBegin(GL_POINTS);
    // int x = 10;
    // int y = 10;

    drawCircle1(r);

    a += dx;
    b += dy;

    if(b + r > ymax)
        dy *= -1.0;

    if(a + r > xmax)
        dx *= -1.0;
    
    if(a - r < xmin)
        dx *= -1.0;

    if(b - r < ymin)
        dy *= -1.0;

    // printf("%d %d\n", x, y);
    glEnd();
 
    glutSwapBuffers();
}
 
static void idle(void)
{
    glutPostRedisplay();
}
 
// Program entry point
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(Width,Height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    generateLines();
    glutCreateWindow("Experiment 02");
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}