#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
#include <stdlib.h>
#include <stdio.h>
 
 
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
            printf("GREEN\n");
            return 0;
        }
        else
        {printf("SKYBLUE\n");
            return 1;
        }
    }
    else if (dx < 0 and dy >= 0)
    {
        if (-dx >= dy)
        {
            printf("YELLOW");
            return 3;
        }
        else
        {
           printf("PURPLE\n");
            return 2;
        }
    }
    else if (dx < 0 and dy < 0)
    {
        if (-dx >= -dy)
        {
             printf("RED\n");
             return 4;
        }
        else
        {
             printf("BLUE\n");
             return 5;
        }
    }
    else
    {
        if (dx >= -dy)
        {
           printf("PINK\n"); return 7;
        }
        else
        {
            printf("WHITE\n");
             return 6;
        }
    }
}
 
void drawPixel(int x, int y)
{
    glVertex2i(x, y);
}
 
 
void draw8way(int x, int y){
    drawPixel(x, y);
    drawPixel(y, x);
    drawPixel(-y, x);
    drawPixel(-x, y);
    drawPixel(-x, -y);
    drawPixel(-y, -x);
    drawPixel(y, -x);
    drawPixel(x, -y);
}
 
 
void drawCircle1(int r){
    int x = 0, y = r;
    int d = 5- 4*r;
    draw8way(x, y);
    while(x < y){
        if(d < 0){
            d += (2*x + 3) *4;
            x++;
        }else{
            d += (2*x - 2*y + 5) * 4;
            x++;
            y--;
        }
        draw8way(x, y);
    }
}
 
 
int x_0, x_1, y_0, y_1;
 
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);
    glEnd();
 
    glPointSize(2);
    glBegin(GL_POINTS);
//    for (int i = 0; i < LINE_COUNT; i++) {
//        printf("%d %d %d %d\n", lineCoords[i][0], lineCoords[i][1], lineCoords[i][2], lineCoords[i][3]);
//        glColor3d(0,0,1);
//        glVertex2i(lineCoords[i][0], lineCoords[i][1]);
//        glColor3d(1,0,0);
//        glVertex2i(lineCoords[i][2], lineCoords[i][3]);
//        glColor3d(1,1,1);
//        drawLine(lineCoords[i][0], lineCoords[i][1], lineCoords[i][2], lineCoords[i][3]);
//    }
    drawCircle1(50);
 
    glEnd();
 
//    glPointSize(10);
//    glBegin(GL_POINTS);
//    for (int i = 0; i < LINE_COUNT; i++) {
//        glColor3d(0,0,1);
//        glVertex2i(lineCoords[i][0], lineCoords[i][1]);
//        glColor3d(1,0,0);
//        glVertex2i(lineCoords[i][2], lineCoords[i][3]);
//        glColor3d(1,1,1);
//    }
//    glEnd();
 
    glutSwapBuffers();
}
 
 
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;
 
    case '+':
        slices++;
        stacks++;
        break;
 
    case '-':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
        }
        break;
    }
 
    glutPostRedisplay();
}
 
static void idle(void)
{
    glutPostRedisplay();
}
 
// Program entry point
 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    generateLines();
    glutCreateWindow("Experiment 01");
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
 
    glutMainLoop();
 
    return EXIT_SUCCESS;
}
// g++ Draw8way.cpp -o Draw8way -lglut -lGLU -lGL