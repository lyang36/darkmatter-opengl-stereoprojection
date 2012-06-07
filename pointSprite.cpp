#ifdef __APPLE__   
#include <GLUT/glut.h>  
#else
#define
#include <GL/glut.h>
#endif
#include <stdlib.h>  
#include <stdio.h>  
#include <iostream>
#include "pointSprite.h"


using namespace std;


DataReader * globalReader;
CircleConverter * globalConverter;


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_POINT_SPRITE);
    
    //Tell OGL to replace the coordinates upon drawing.
    glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
    
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    glBegin(GL_POINTS);
    globalReader->open();
    cout<<"open.."<<endl;
    while(globalReader->hasNext()){
        //cout << "ok" << endl;
        Particles part;
        globalReader->readParticle(&part);
        globalConverter->setPart(&part);
        
        //cout << part.mass << " " << part.density << " "
        //<< part.hsmooth << " " << part.xpos << " "
        //<< part.ypos << " " << part.zpos << endl;
        
        vector<Point> * vv;
        globalConverter->convert_lower();
        vv = globalConverter->getList();
        for(int i=0; i<(vv->size()); i++){
            //cout<<i<<endl;
            //(*vv)[i].color[4] = 1.0;
            //(*vv)[i].color[1] = 1.0;
            glColor4dv((*vv)[i].color);
            (*vv)[i].pos[2] =  (*vv)[i].pos[2];
            //(*vv)[i].pos[1] = (*vv)[i].pos[2];
            glVertex3dv((*vv)[i].pos);
            
            /*cout << "xc: " << (*vv)[i].pos[0] << " yc: "
            << (*vv)[i].pos[1] << " zc: " << (*vv)[i].pos[2] <<
            " color1: " << (*vv)[i].color[0] << " color2: " << (*vv)[i].color[1] 
            << " color3: " << (*vv)[i].color[2] << " color4: " << (*vv)[i].color[3]<< endl ;*/
        }
    }
    globalReader->close();
    
/*    glColor4f( 1.0, 
              0.0, 
              0.0, 
              1.0f );
    glVertex3f(-2.0, -1.0, -3.0); 
    glVertex3f(1.0, -1.0, -4.0);  
    glVertex3f(-2.0, 1.0, -8.0);  
    glVertex3f(-3.0, -2.0, -13.0); 
    glVertex3f(3.0, -2.0, -9.0);
    for (int i=0; i<2000; i++) {
        glVertex3f(-1.0+i/2000.0, 4.0, -i);
    }
    glVertex3f(1.0, 1.0, -1.0); 
    glVertex3f(1.0, 1.0, -2.0); 
    glVertex3f(1.0, 1.0, -3.0); 
    glVertex3f(1.0, 1.0, -4.0); 
    glVertex3f(1.0, 1.0, -5.0); */
    glEnd();  
    glFlush();  
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_TEXTURE_2D); 

}

void reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    //gluPerspective(60.0, 1.0, 1.0, 30.0);  
    glOrtho(-100, 100, -100, 100, 4000, -4000.0);
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();     
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {  
        case 27:  
            exit(0);  
            break;  
        default:  
            break;  
    }  
}


void pointSprite::openglInit(){
    //set up background to be black
    glClearColor (0.0, 0.0, 0.0, 0.0);      
    loadImage();  
    
    //get point size range
    glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes); 
    
    //set point to be transparent
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);              
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  
    
    //generate the texture
    glGenTextures(1, &texName);  
    glBindTexture(GL_TEXTURE_2D, texName);          

    //setup texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    
    
    //generate the image texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,   
                 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);  

    
    //Enable point sprites and set params for points.
    glEnable(GL_POINT_SPRITE_ARB);
    float q1[] =  { quadratic[0], quadratic[1], quadratic[2] };
    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, q1 );
    glPointParameterfARB( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f );
    
    //Tell it the max and min sizes we can use using our pre-filled array.
    glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, sizes[0] );
    glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, sizes[1] );
    
    
    //Set the size of the points.
    glPointSize(pointsize);
    
    //Turn off depth masking so particles in front will not occlude particles behind them.
    glDepthMask(GL_FALSE);
    
    glBindTexture(GL_TEXTURE_2D, texName);  

}

pointSprite::pointSprite(){
    quadratic[0]= 1.0;
    quadratic[1] = 0.0;
    quadratic[2] = 0.01;
    pointsize = 32.0f;
    converter.setRadius(pointsize);
    converter.setQuadratic(quadratic);
}

void pointSprite::loadImage(){
    
    int i, j, c, a;  
    
    for (i = 0; i < checkImageHeight; i++) {  
        for (j = 0; j < checkImageWidth; j++) {  
            if(((i-checkImageHeight/2)*(i-checkImageHeight/2) +
                (j-checkImageWidth/2)*(j-checkImageWidth/2)) < 16*16)
            {c = 255; a =255;         //black image
            }
            else
            {c = 0; a =0;} 
            checkImage[i][j][0] = (GLubyte) c;  
            checkImage[i][j][1] = (GLubyte) c;  
            checkImage[i][j][2] = (GLubyte) c;  
            checkImage[i][j][3] = (GLubyte) a;  
        }  
    }  
}

void pointSprite::startDisplay(int argc, char** argv){
    //loadImage();| GLUT_DEPTH
    globalConverter = &converter;
    globalReader = &reader;
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(1200, 600);  
    glutInitWindowPosition(100, 100);  
    glutCreateWindow(argv[0]);  
    openglInit();  
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);  
    glutKeyboardFunc(keyboard); 
    display();
    glutMainLoop();
}

