/*OPENGL functions in this head file*/
#ifndef __LY__POINT_SPRITE__
#define __LY__POINT_SPRITE__

#ifdef __APPLE__  
#include <GLUT/glut.h>  
#else
#define
#include <GL/glut.h>
#endif

#include "datareader.h"
#include "converter.h"
#include "types.h"
//define a global dataReader
#define checkImageWidth 32  
#define checkImageHeight 32  

//the following globalObject is initiated in main()
//DataReader globalReader;    //this is used by display function.
//CircleConverter globalConverter;  //a global converter
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

class pointSprite{
private:
    GLfloat sizes[2];
    GLuint texName;  
    GLubyte checkImage[checkImageHeight][checkImageWidth][4];  
    double quadratic[3];//={1.0, 0.0, 0.01}
    REAL pointsize; //32.0f?
    void openglInit();  //opengl initialization
    void loadImage();
    
public:
    DataReader reader;
    CircleConverter converter;
    pointSprite();
    void startDisplay(int argc, char** argv);
};
#endif