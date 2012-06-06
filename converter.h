/*Converter
 *Convert to list of circles, used to draw point sprites
 */
#include "types.h"
#include <vector>


#ifndef __LY_CIRCLE_CONVERTER__
#define __LY_CIRCLE_CONVERTER__

using namespace std;

class CircleConverter{
private:
    REAL radius;                //the plane size
    Particles * part;
    vector<Point>  pointList;   //the list of points
    REAL opos[3];
    REAL vpos[3];               //vpos must be normalized
    //REAL costheta;
    //REAL sintheta;
    //REAL sinphi;
    //REAL cosphi;
    REAL theta;
    REAL phi;
    REAL x, y, z;               //normalized x, y and z
    void getangle();
    REAL f0;                    //constant for normalize f0
    REAL dr ;                   //the steps for drawling a circle
    REAL angularradius;
    REAL distance;              //distance of the particle
    
    REAL flux;
    //REAL (*profile)(REAL r, REAL r0);//profile function
    //REAL (*vz)(REAL r);         //get the z coordinate for the opengl point sprite
    REAL profile(REAL r, REAL r0);
    REAL vz(REAL r);
    REAL alpha(REAL flux);
    
    REAL * quadratic;          //the parameter in GL_POINT_DISTANCE_ATTENUATION_ARB
    
    
    void stereCircle(REAL theta, REAL phi, REAL dr, 
                     REAL &xc, REAL &yc, REAL &pr ); //project a circle
public:
    CircleConverter();
    bool convert_lower();   //upsphere
    bool convert_upper();   //lowersphere
    void setPart(Particles *part);
    vector<Point> * getList();
    void setRadius(REAL r);
    void setPos(REAL * vpos, REAL * opos);
    void setf0(REAL f0);
    void setQuadratic(REAL * q);
    //void setProfile(REAL (*p)(REAL, REAL));
    
};

#endif