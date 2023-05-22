#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>

#endif
#include <stdlib.h>
#define Width 1020
#define Height 780
//#define type int
#include<bits/stdc++.h>
using namespace std;

static int slices = 16;
static int stacks = 16;
double efp[15],bes[15];

struct point
{
    int x;
    int y;
};

struct line
{
    point p1;
    point p2;
};

struct circle
{
    int r;
    int cx;
    int cy;
};

struct ellipse
{
    int a;
    int b;
    int cx;
    int cy;
};

point givenPoints[1000];
circle circles[1000];
ellipse ellipses[1000];
int n;

void generatePoints(int n)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-300, 300); // define the range
    for(int i = 0; i< 2 * n; i++)
    {
         int x = distr(gen);
         int y = distr(gen);
         givenPoints[i].x = x;
         givenPoints[i].y = y;
         i++;
    }
}

void generateCircleParameters(int n)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-200, 200); // define the range
    int ind = 0;
    for(int i = 0; i < n; i++)
    {
         int r = distr(gen);
         r = max(r, -r);
         int cx = distr(gen);
         int cy = distr(gen);
         circles[i].r = r;
         circles[i].cx = cx;
         circles[i].cy = cy;
    }
}

void generateEllipseParameters(int n)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(-200, 200); // define the range
    int ind = 0;
    for(int i = 0; i < n; i++)
    {
         int a = distr(gen);
         a = max(a, -a);
         int b = distr(gen);
         b = max(b, -b);
         int cx = distr(gen);
         int cy = distr(gen);
         ellipses[i].a = a;
         ellipses[i].b = b;
         ellipses[i].cx = cx;
         ellipses[i].cy = cy;
    }
}



struct arr
{
    int a[1000];
    int sizee;
};

int powerReturn(string str)
{
    if(str[0] == '.')
        return -1;
    int power = 0;
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == '-')
            continue;
        if(str[i] == '.')
            return power - 1;
        power++;
    }
    return power - 1;
}

int turnStringtoNumber(string str)
{
    int num = 0;
    bool negFlag = false;
    int poweree = powerReturn(str);
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == '-')
        {
            negFlag = true;
            continue;
        }
        if(str[i] == '.')
            continue;
        num = num + (str[i] - '0') * pow(10, poweree);
        poweree--;
    }
    if(negFlag)
        return -num;
    return num;
}

arr getNumbersfromLine(string str)
{
    string temp;
    int ind = 0;
    arr nums;
    nums.sizee = 0;
    for(int i = 0; i < str.size(); i++)
    {
        if((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-')
        {
            while((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-')
            {
                temp += str[i++];
            }
            nums.a[ind++] = turnStringtoNumber(temp);
            nums.sizee++;
            temp = "";
        }
    }
    return nums;
}

point getPointfromLine(string str)
{
    point p;
    arr nums = getNumbersfromLine(str);
    p.x = nums.a[0];
    p.y = nums.a[1];
    return p;
}

line getTwoPoints(string str)
{
    arr nums = getNumbersfromLine(str);
    line l1;
    cout << nums.a[0] << " " << nums.a[1] << " " << nums.a[2] << " " << nums.a[3] << endl;
    l1.p1.x = nums.a[0];
    l1.p1.y = nums.a[1];
    l1.p2.x = nums.a[2];
    l1.p2.y = nums.a[3];

    return l1;
}




static void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2-1, -Height/2, Height/2-1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int detZone(int x0, int y0, int x1, int y1)
{
    int dx = x1-x0;
    int dy = y1-y0;
    if(abs(dx) >= abs(dy))
    {
        if(dx >= 0 and dy >= 0)
            return 0;
        else if(dx >= 0 and dy < 0)
            return 7;
        else if(dx < 0 and dy < 0)
            return 4;
        return 3;
    }
    else
    {
        if(dx >= 0 and dy >= 0)
            return 1;
        else if(dx >= 0 and dy < 0)
            return 6;
        else if(dx < 0 and dy < 0)
            return 5;
        return 2;
    }
}

pair<int, int> anyzone_to_zone0(int x, int y, int zone)
{
    switch(zone)
    {
        case 0:
            return make_pair(x, y);
            break;
        case 1:
            return make_pair(y,x);
            break;
        case 2:
            return make_pair(y,-x);
            break;
        case 3:
            return make_pair(-x, y);
            break;
        case 4:
            return make_pair(-x, -y);
            break;
        case 5:
            return make_pair(-y, -x);
            break;
        case 6:
            return make_pair(-y, x);
            break;
        case 7:
            return make_pair(x, -y);
            break;
        default:
            break;
    }
}

pair<int, int> zone0_to_anyzone(int x, int y, int zone)
{
    switch(zone)
    {
        case 0:
            return make_pair(x, y);
            break;
        case 1:
            return make_pair(y,x);
            break;
        case 2:
            return make_pair(-y,x);
            break;
        case 3:
            return make_pair(-x, y);
            break;
        case 4:
            return make_pair(-x, -y);
            break;
        case 5:
            return make_pair(-y, -x);
            break;
        case 6:
            return make_pair(y, -x);
            break;
        case 7:
            return make_pair(x, -y);
            break;
        default:
            break;
    }
}

void drawPixel(int x, int y, int zone)
{
    glPointSize(2);
    glPushMatrix();
    glBegin(GL_POINTS);
    switch(zone)
    {
        case 0:
            glColor3ub(100, 100, 100);
            break;
        case 1:
            glColor3ub(255, 0, 0);
            break;
        case 2:
            glColor3ub(0, 255, 0);
            break;
        case 3:
            glColor3ub(0, 0, 255);
            break;
        case 4:
            glColor3ub(85, 255, 255);
            break;
        case 5:
            glColor3ub(255, 0, 255);
            break;
        case 6:
            glColor3ub(255, 100, 100);
            break;
        case 7:
            glColor3ub(255, 255, 255);
            break;
        default:
            break;
    }
    glVertex2i(x, y);
}

void convert_drawLine0(int x0, int y0, int x1, int y1)
{
    int zone = detZone(x0, y0, x1, y1);
    switch(zone)
    {
        case 0:
            glColor3ub(100, 100, 100);
            break;
        case 1:
            glColor3ub(255, 0, 0);
            break;
        case 2:
            glColor3ub(0, 255, 0);
            break;
        case 3:
            glColor3ub(0, 0, 255);
            break;
        case 4:
            glColor3ub(85, 255, 255);
            break;
        case 5:
            glColor3ub(255, 0, 255);
            break;
        case 6:
            glColor3ub(255, 100, 100);
            break;
        case 7:
            glColor3ub(255, 255, 255);
            break;
        default:
            break;
    }

    pair<int, int> convertedPoint0 = anyzone_to_zone0(x0, y0, zone);
    pair<int, int> convertedPoint1 = anyzone_to_zone0(x1, y1, zone);

    int zx0 = convertedPoint0.first;
    int zy0 = convertedPoint0.second;
    int zx1 = convertedPoint1.first;
    int zy1 = convertedPoint1.second;

    int dy = zy1 - zy0;
    int dx = zx1 - zx0;

    int x = zx0;
    int y = zy0;

    pair<int, int> backConvertedPoint = zone0_to_anyzone(x, y, zone);
    drawPixel(backConvertedPoint.first, backConvertedPoint.second, zone);
    int delE = 2 * dy;
    int delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;

    for(int i = 0; i < abs(dx); i++)
    {
        x++;
        if(d < 0)
            d += delE;
        else
        {
            d += delNE;
            y++;
        }
        backConvertedPoint = zone0_to_anyzone(x , y, zone);
        drawPixel(backConvertedPoint.first, backConvertedPoint.second, zone);
    }
    glEnd();
    glPopMatrix();
}

void drawLine0(int x0, int y0, int x1, int y1)
{
    int dy = y1-y0;
    int dx = x1-x0;
    int delE = 2 * dy;
    int delNE = 2 * (dy - dx);
    int d = 2 * dy - dx;
    int x = x0; int y = y0;
    drawPixel(x, y, 0);
    for(int i = 0; i < abs(dx); i++)
    {
        x++;
        if(d < 0)
            d += delE;
        else
        {
            d += delNE;
            y++;
        }
        drawPixel(x, y, 0);
    }
}

void drawLine1(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    int delN = -2 * dx, delNE = 2 * (dy - dx);
    int d = dy - 2 * dx;
    int x = x0, y = y0;
    drawPixel(x0, y0, 1);

    while (y < y1)
    {
        if (d < 0)
        { // delNE
            d += delNE;
            x++;
            y++;
        }
        else
        { // delN
            d += delN;
            y++;
        }
        drawPixel(x, y, 1);
    }
}

void drawLine2(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    int delN = -2 * dx, delNW = 2 * (-dx - dy);
    int d = -dy - 2 * dx;
    int x = x0, y = y0;
    drawPixel(x0, y0, 2);

    while (y < y1)
    {
        if (d >= 0)
        { // delNW
            d += delNW;
            x--;
            y++;
        }
        else
        { // delN
            d += delN;
            y++;
        }
        drawPixel(x, y, 2);
    }
}

void drawLine3(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    int delW = -2 * dy, delNW = 2 * (-dx - dy);
    int d = -2 * dy - dx;
    int x = x0, y = y0;
    drawPixel(x0, y0, 3);
    while (x > x1)
    {
        if (d < 0)
        { // delNW
            d += delNW;
            x--;
            y++;
        }
        else
        { // delW
            d += delW;
            x--;
        }
        drawPixel(x, y, 3);
    }
}

void drawLine4(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    int delW = -2 * dy, delSW = 2 * (dx - dy);
    int d = -2 * dy + dx;
    int x = x0, y = y0;
    drawPixel(x0, y0, 4);

    while (x > x1)
    {
        if (d < 0)
        { // delW
            d += delW;
            x--;
        }
        else
        { // delSW
            d += delSW;
            x--;
            y--;
        }
        drawPixel(x, y, 4);
    }
}

void drawLine5(int x0, int y0, int x1, int y1)
{
    // printf("Zone 5\n");
    // printf("\tx\ty\td\tdelS/delSW\n");

    int dx = x1 - x0, dy = y1 - y0;
    int delS = 2 * dx, delSW = 2 * (dx - dy);
    int d = 2 * dx - dy;
    int x = x0, y = y0;
    // printf("\t%d\t%d\t%d\t%s\n", x, y, d, d < 0 ? "delSW" : "delS");

    drawPixel(x0, y0, 5);

    while (y > y1)
    {
        if (d < 0)
        { // delSW
            d += delSW;
            x--;
            y--;
        }
        else
        { // delS
            d += delS;
            y--;
        }
        // printf("\t%d\t%d\t%d\t%s\n", x, y, d, d < 0 ? "delSW" : "delS");

        drawPixel(x, y, 5);
    }
}

void drawLine6(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    int delS = 2 * dx, delSE = 2 * (dx + dy);
    int d = 2 * dx + dy;
    int x = x0, y = y0;
    drawPixel(x0, y0, 6);

    while (y > y1)
    {
        if (d < 0)
        { // delS
            d += delS;
            y--;
        }
        else
        { // delSE
            d += delSE;
            x++;
            y--;
        }
        drawPixel(x, y, 6);
    }
}

void drawLine7(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    int delE = 2 * dy, delSE = 2 * (dx + dy);
    int d = 2 * dy + dx;
    int x = x0, y = y0;
    drawPixel(x0, y0, 7);

    while (x < x1)
    {
        if (d >= 0)
        { // delE
            d += delE;
            x++;
        }
        else
        { // delSE
            d += delSE;
            x++;
            y--;
        }
        drawPixel(x, y, 7);
    }
}

void drawLine(int x0, int y0, int x1, int y1)
{
    int zone = detZone(x0, y0, x1, y1);
    switch(zone)
    {
        case 0:
            drawLine0(x0, y0, x1, y1);
            break;
        case 1:
            drawLine1(x0, y0, x1, y1);
            break;
        case 2:
            drawLine2(x0, y0, x1, y1);
            break;
        case 3:
            drawLine3(x0, y0, x1, y1);
            break;
        case 4:
            drawLine4(x0, y0, x1, y1);
            break;
        case 5:
            drawLine5(x0, y0, x1, y1);
            break;
        case 6:
            drawLine6(x0, y0, x1, y1);
            break;
        case 7:
            drawLine7(x0, y0, x1, y1);
            break;
        default:
            break;
    }
    glEnd();
    glPopMatrix();
}

void draw8way(int x, int y, int cx, int cy)
{
    for(int i = 0; i < 8; i++)
    {
        pair<int, int> p = zone0_to_anyzone(x, y, i);
        drawPixel(p.first + cx, p.second + cy, i);
    }
}

void drawCircle(int r, int cx, int cy)
{
    drawPixel(cx, cy, 1);
    int x = 0;
    int y = r;
    int d = 5-4*r;
    draw8way(x, y, cx, cy);
    while(x < y)
    {
        if(d < 0)
            d += 4 * (2 * x + 3);
        else
        {
             d += 4 * (2 * x - 2 * y + 5);
             y--;
        }
        x++;
        draw8way(x, y, cx, cy);
    }
    glEnd();
    glPopMatrix();
}

void draw4way(int x, int y, int cx, int cy)
{
    /*drawPixel(x+cx, y+cy, detZone(0, 0, x , y));
    drawPixel(-x+cx, y+cy, detZone(0, 0, -x,y));
    drawPixel(x+cx, -y+cy, detZone(0, 0, x,-y));
    drawPixel(-x+cx, -y+cy, detZone(0,0,-x,-y));*/
    drawPixel(x+cx, y+cy, 1);
    drawPixel(-x+cx, y+cy, 1);
    drawPixel(x+cx, -y+cy, 1);
    drawPixel(-x+cx, -y+cy, 1);
}

void drawEllipse(int a, int b, int cx, int cy)
{
    drawPixel(cx, cy, 1);
    int x = 0;
    int y = b;
    int d = 4 * (b * b - a * a * b) + a * a;
    while((2 * b * b * (x + 1)) < (2 * a * a * y - a * a))
    {
        if(d < 0)
        {
            d += 4 * b * b * (2 * x + 3);
        }
        else
        {
            d += 4 * (b * b * (2 * x + 3) + 2 * a * a * (1 - y));
            y--;
        }
        x++;
        draw4way(x, y, cx, cy);
    }

    d = 4*b*b*(x*x + x) + b*b + 4*a*a*(y*y - 2*y + 1 - b*b);
    while(y > 0)
    {
        if(d < 0)
        {
            d += 4 * (2*b*b*(x+1) + a*a*(3-2*y));
            x++;
        }
        else
        {
            d += 4*a*a*(3 - 2*y);
        }
        y--;
        draw4way(x, y, cx, cy);
    }
    glEnd();
    glPopMatrix();
}





/* GLUT callback Handlers */


static void display(void)
{

    //cout << n << endl;
    glClear(GL_COLOR_BUFFER_BIT);
    //line
    glPointSize(1);
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2i(-Width/2, 0);
    glVertex2i(Width/2, 0);
    glVertex2i(0, -Height/2);
    glVertex2i(0, Height/2);

    glEnd();
    glPopMatrix();
    int flag = 4;

    switch (flag)
    {
        case 0:
        {

            int x0 = -6;
            int y0 = -2;
            int x1 = -3;
            int y1 = -5;
            drawLine(x0, y0, x1, y1);
            break;
        }

        case 1:
        {
            for(int i = 0; i < 2 * n; i +=2)
            {
                int x0 = givenPoints[i].x;
                int y0 = givenPoints[i].y;
                int x1 = givenPoints[i+1].x;
                int y1 = givenPoints[i+1].y;
                //cout << "*" << endl;
                //cout << givenPoints[i].x << " " << givenPoints[i].y << " " << givenPoints[i+1].x << " " << givenPoints[i+1].y << endl;
                convert_drawLine0(x0, y0, x1, y1);
                //drawLine(x0, y0, x1, y1);
            }
            break;
        }

        case 2:
        {
            int x0 = 0;
            int y0 = 0;
            int x1, y1;
            double pi = acos(-1.0);
            double r = 200;
            for(double i = 0; i < 2*pi; i += (2*pi)/360)
            {
                x1 = r * cos(i);
                y1 = r * sin(i);
                drawLine(x0, y0, x1, y1);
            }
            break;
        }

        case 3:
        {
            int genFlag = 1;
            if(genFlag == 0)
            {
                drawCircle(200, 30, 50);
            }
            else
            {
                for(int i = 0; i < n; i++)
                {
                    drawCircle(circles[i].r, circles[i].cx, circles[i].cy);
                }
            }
            break;
        }

        case 4:
        {

            int genFlag = 1;
            if(genFlag == 0)
            {
                drawEllipse(200, 130, 0, 0);
            }
            else
            {
                for(int i = 0; i < n; i++)
                {
                    drawEllipse(ellipses[i].a, ellipses[i].b, ellipses[i].cx, ellipses[i].cy);
                }
            }
            break;
        }

        default:
            break;

    }

    glutSwapBuffers();
}


void myInit(void){
    glClearColor(0,0,0,1);
    glEnable(GL_COLOR_MATERIAL);
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    int flag = 0;
    int shapeFlag = 2;
    n = 3;
    switch(flag)
    {
        case 0:
        {
            switch(shapeFlag)
            {
                case 0:
                {
                    generatePoints(n);
                    break;
                }
                case 1:
                {
                    generateCircleParameters(n);
                    break;
                }
                case 2:
                {
                    generateEllipseParameters(n);
                    break;
                }
                default:
                    break;

            }
        }
        case 1:
        {
            ifstream inFile;
            if(flag == 1)
                inFile.open("E:/Project/testgr/points.txt");
            else
                inFile.open("E:/Project/testgr/lines.txt");
            if(!inFile.is_open())
                cout << "File is not open" << endl;

            int ind = 0;
            bool isFirstitr = true;
            if(flag == 1)
            {
                while(!inFile.eof())
                {
                    string str;
                    getline(inFile, str);
                    cout << str << endl;
                    /*if(isFirstitr)
                    {
                        int temp = turnStringtoNumber(str);
                        isFirstitr = false;
                        continue;
                    }*/
                    point temp = getPointfromLine(str);
                    givenPoints[ind].x = temp.x;
                    givenPoints[ind].y = temp.y;
                    ind++;
                }
                n = ind/2;
            }
            else
            {
                while(!inFile.eof())
                {
                    string str;
                    getline(inFile, str);
                    //cout << str << endl;
                    /*if(isFirstitr)
                    {
                        int temp = turnStringtoNumber(str);
                        isFirstitr = false;
                        continue;
                    }*/
                    line temp = getTwoPoints(str);
                    //cout << temp.p1.x << endl;
                    givenPoints[ind].x = temp.p1.x;
                    givenPoints[ind].y = temp.p1.y;
                    givenPoints[ind+1].x = temp.p2.x;
                    givenPoints[ind+1].y = temp.p2.y;
                    ind += 2;
                }
                for(int i = 0; i < ind; i++)
                    //cout << givenPoints[i].x << " " << givenPoints[i].y << endl;
                n = ind/2;
            }
        }
    }

    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("GLUT Shapes");
    myInit();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;



}
