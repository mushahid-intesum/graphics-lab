#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

#define Width 640
#define Height 480

float ymax = Height / 2;
float ymin = -Height / 2;
float xmax = Width / 2;
float xmin = -Width / 2;
float dx = 20;
float dy = 0.1;
float a = 200, b = 100;
bool isBouncing = false;
bool isDecrease = true;

float c = a * a + b * b;

float r = a;

float center_x = 0, center_y = 0;
float start_y = center_y;

static int slices = 16;
static int stacks = 16;
#define LINE_COUNT 10

int lineCoords[LINE_COUNT][4];

int generateRandX()
{
    return (rand() % 640) - 320;
}

int generateRandY()
{
    return (rand() % 480) - 240;
}

void generateLines()
{
    for (int i = 0; i < LINE_COUNT; i++)
    {
        lineCoords[i][0] = generateRandX();
        lineCoords[i][1] = generateRandY();
        lineCoords[i][2] = generateRandX();
        lineCoords[i][3] = generateRandY();
    }
}

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int findZone(float x0, float y0, float x1, float y1)
{
    float dx = x1 - x0, dy = y1 - y0;
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

void drawPixel(float x, float y)
{
    glVertex2f(x, y);
}

void draw8way(float x, float y)
{
    drawPixel(x + center_x, y + center_y);
    drawPixel(y + center_x, x + center_y);
    drawPixel(-y + center_x, x + center_y);
    drawPixel(-x + center_x, y + center_y);
    drawPixel(-x + center_x, -y + center_y);
    drawPixel(-y + center_x, -x + center_y);
    drawPixel(y + center_x, -x + center_y);
    drawPixel(x + center_x, -y + center_y);
}

void draw4way(float x, float y, float cx, float cy)
{
    /*drawPixel(x+cx, y+cy, detZone(0, 0, x , y));
    drawPixel(-x+cx, y+cy, detZone(0, 0, -x,y));
    drawPixel(x+cx, -y+cy, detZone(0, 0, x,-y));
    drawPixel(-x+cx, -y+cy, detZone(0,0,-x,-y));*/
    drawPixel(x + cx, y + cy);
    drawPixel(-x + cx, y + cy);
    drawPixel(x + cx, -y + cy);
    drawPixel(-x + cx, -y + cy);
}

void drawCircle1(int r)
{
    int x0 = 0;
    int y0 = r;
    int d = 5 - 4 * r;
    draw8way(x0, y0);
    while (x0 < y0)
    {
        if (d < 0)
        {
            d += ((2 * x0 + 3) * 4);
            x0++;
        }
        else
        {
            d += ((2 * x0 - 2 * y0 + 5) * 4);
            x0++;
            y0--;
        }
        draw8way(x0, y0);
    }
}

void drawEllipse(float a, float b, float cx, float cy)
{
    drawPixel(cx, cy);
    float x = a;
    float y = 0;
    float d = 4 * (b * b + 2 * a * b * b) + a * a;
    while ((4 * b * b * (x + 1)) > (a * a * (4*y + 2)))
    {
        // printf("1\n");
        // cout << x << " " << y << endl;

        if (d < 0)
        {
            d += 4 * b * b * (2 * x + 3);
            
        }
        else
        {
            d += 4 * (b * b * (2 * x + 3) + 2 * a * a * (1 + y));
            x--;
        }
        y++;
        draw4way(x, y, cx, cy);
    }
    // printf("out of 1\n");

    // d = 4 * b * b * (x * x + x) + b * b + 4 * a * a * (y * y - 2 * y + 1 - b * b);
    while (x > 0)
    {
        // printf("%d\n", x);
        if (d < 0)
        {
            d += 4 * (2 * b * b * (1 - x) + a * a * (3 + 2 * y));  
            x--;
            y++;
        }
        else
        {
            d += 4 * a * a * (3 + 2 * y);
            x--;
        }
        draw4way(x, y, cx, cy);
    }
    glEnd();
    glPopMatrix();
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2i(-Width / 2, 0);
    glVertex2i(Width / 2, 0);
    glVertex2i(0, -Height / 2);
    glVertex2i(0, Height / 2);
    glEnd();

    // char po;
    // scanf("%c", &po);

    glPointSize(2);
    glBegin(GL_POINTS);

    // float g = 0.1;
    // float decrement_rate = 0.3;
    // int iter = 3500;
    // int limit = 25;

    // printf("ellipse\n");
    drawEllipse(a, b, center_x, center_y);

    // if (b == r)
    // {
    //     a = r;
    //     b = r;
    //     isBouncing = false;
    //     isDecrease = true;
    // }

    // if (!isBouncing)
    // {
    //     center_y -= dy;
    //     dy += g;
    //     if (center_y + b + 5 - ymax > 0.1)
    //     {
    //         dy *= -1.0;
    //         g *= -1.0;
    //     }

    //     if (center_y - r -ymin <= 0.1)
    //     {
    //         dy *= -1.0;
    //         g *= -1.0;
    //         isBouncing = true;
    //         for (int i = 0; i < 2; i++)
    //         {
    //             float newb = b - decrement_rate;
    //             // b -= decrement_rate;
    //             a = sqrt(c - newb * newb);
    //             float diff = abs(newb - b);
    //             center_y -= diff;
    //             b = newb;
    //         }
    //     }

    //     if (center_y - start_y  > 0.1)
    //     {
    //         dy *= -1.0;
    //         g *= -1.0;
    //     }
    // }

    // else
    // {
    //     if (b - limit > 0.1 && isDecrease)
    //     {
    //         float newb = b - decrement_rate;
    //         a = sqrt(c - newb * newb);
    //         float diff = abs(newb - b);
    //         center_y -= diff;

    //         b = newb;
    //     }

    //     if (b <= limit)
    //         isDecrease = false;

    //     if (!isDecrease)
    //     {
    //         float newb = b + decrement_rate;
    //         a = sqrt(c - newb * newb);
    //         float diff = abs(newb - b);
    //         center_y += diff;

    //         b = newb;
    //     }

    // }

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
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    generateLines();
    glutCreateWindow("Experiment 02");

    glutReshapeFunc(resize);

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}