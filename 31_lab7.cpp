#include <bits/stdc++.h>
#include <GL/glut.h>
#define Width 600
#define Height 400
using namespace std;


// Function to load a bitmap image
void loadBMP(string filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    char header[54];    
    file.read(header, 54);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = 3 * width * height;
    char* data = new char[imageSize];
    file.read(data, imageSize);

    // Set up texture mapping
    glMatrixMode(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D); //generate the texture data from the pixel data
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    // Display the texture on a quad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    loadBMP("doggie.bmp");
}


// Function to load a bitmap image
void loadBMP2(string filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    char header[54];    
    file.read(header, 54);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = 3 * width * height;
    char* data = new char[imageSize];
    file.read(data, imageSize);

    for (int i = 0; i < imageSize; i++) {
        data[i] = 255 - data[i];
    }

    // Set up texture mapping
    glMatrixMode(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D); 
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    // Display the texture on a quad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

// Display function
void display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    loadBMP2("doggie.bmp");
}

double get_h(double r, double g, double b)
{
    // R, G, B values are divided by 255
    // to change the range from 0..255 to 0..1
    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;
 
    // h, s, v = hue, saturation, value
    double cmax = max(r, max(g, b)); // maximum of r, g, b
    double cmin = min(r, min(g, b)); // minimum of r, g, b
    double diff = cmax - cmin; // diff of cmax and cmin.
    double h = -1, s = -1;
 
    // if cmax and cmax are equal then h = 0
    if (cmax == cmin)
        h = 0;
 
    // if cmax equal r then compute h
    else if (cmax == r)
        h = fmod(60 * ((g - b) / diff) + 360, 360);
 
    // if cmax equal g then compute h
    else if (cmax == g)
        h = fmod(60 * ((b - r) / diff) + 120, 360);
 
    // if cmax equal b then compute h
    else if (cmax == b)
        h = fmod(60 * ((r - g) / diff) + 240, 360);
 
    return h;
}


// Function to load a bitmap image
void loadBMP3(string filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    char header[54];    
    file.read(header, 54);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = 3 * width * height;
    char* data = new char[imageSize];
    file.read(data, imageSize);

    for (int i = 0; i < imageSize; i += 3) {
        auto h = get_h(data[i], data[i + 1], data[i + 2]);
        data[i] = data[i + 1] = data[i + 2] = h;
    }

    // Set up texture mapping
    glMatrixMode(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D); //generate the texture data from the pixel data
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    // Display the texture on a quad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

// Display function
void display3() {
    glClear(GL_COLOR_BUFFER_BIT);
    loadBMP3("doggie.bmp");
}

double get_s(double r, double g, double b)
{
 
    // R, G, B values are divided by 255
    // to change the range from 0..255 to 0..1
    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;
 
    // h, s, v = hue, saturation, value
    double cmax = max(r, max(g, b)); // maximum of r, g, b
    double cmin = min(r, min(g, b)); // minimum of r, g, b
    double diff = cmax - cmin; // diff of cmax and cmin.
    double h = -1, s = -1;
 
    // if cmax and cmax are equal then h = 0
    if (cmax == cmin)
        h = 0;
 
    // if cmax equal r then compute h
    else if (cmax == r)
        h = fmod(60 * ((g - b) / diff) + 360, 360);
 
    // if cmax equal g then compute h
    else if (cmax == g)
        h = fmod(60 * ((b - r) / diff) + 120, 360);
 
    // if cmax equal b then compute h
    else if (cmax == b)
        h = fmod(60 * ((r - g) / diff) + 240, 360);
 
    // if cmax equal zero
    if (cmax == 0)
        s = 0;
    else
        s = (diff / cmax) * 100;
    return s;
}


// Function to load a bitmap image
void loadBMP4(string filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    char header[54];    
    file.read(header, 54);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = 3 * width * height;
    char* data = new char[imageSize];
    file.read(data, imageSize);

    for (int i = 0; i < imageSize; i += 3) {
        auto s = get_s(data[i], data[i + 1], data[i + 2]);
        data[i] = data[i + 1] = data[i + 2] = s;
    }

    // Set up texture mapping
    glMatrixMode(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D); //generate the texture data from the pixel data
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    // Display the texture on a quad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

// Display function
void display4() {
    glClear(GL_COLOR_BUFFER_BIT);
    loadBMP4("doggie.bmp");
}


double get_v(double r, double g, double b)
{
 
    // R, G, B values are divided by 255
    // to change the range from 0..255 to 0..1
    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;
 
    // h, s, v = hue, saturation, value
    double cmax = max(r, max(g, b)); // maximum of r, g, b
    double cmin = min(r, min(g, b)); // minimum of r, g, b
    double diff = cmax - cmin; // diff of cmax and cmin.
    double h = -1, s = -1;
 
    // if cmax and cmax are equal then h = 0
    if (cmax == cmin)
        h = 0;
 
    // if cmax equal r then compute h
    else if (cmax == r)
        h = fmod(60 * ((g - b) / diff) + 360, 360);
 
    // if cmax equal g then compute h
    else if (cmax == g)
        h = fmod(60 * ((b - r) / diff) + 120, 360);
 
    // if cmax equal b then compute h
    else if (cmax == b)
        h = fmod(60 * ((r - g) / diff) + 240, 360);
 
    // if cmax equal zero
    if (cmax == 0)
        s = 0;
    else
        s = (diff / cmax) * 100;
 
    // compute v
    double v = cmax * 100;
    return v;
}

// Function to load a bitmap image
void loadBMP5(string filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return;
    }

    char header[54];    
    file.read(header, 54);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int imageSize = 3 * width * height;
    char* data = new char[imageSize];
    file.read(data, imageSize);

    for (int i = 0; i < imageSize; i += 3) {
        auto s = get_v(data[i], data[i + 1], data[i + 2]);
        data[i] = data[i + 1] = data[i + 2] = s;
    }

    // Set up texture mapping
    glMatrixMode(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D); //generate the texture data from the pixel data
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    // Display the texture on a quad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

// Display function
void display5() {
    glClear(GL_COLOR_BUFFER_BIT);
    loadBMP5("doggie.bmp");
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Original Image");
    glutDisplayFunc(display);

    glutCreateWindow("Inverted Image");
    glutDisplayFunc(display2);

    glutCreateWindow("Image by h");
    glutDisplayFunc(display3);

    glutCreateWindow("Image by s");
    glutDisplayFunc(display4);

    glutCreateWindow("Image by v");
    glutDisplayFunc(display5);

    glutMainLoop();
    return 0;
}
