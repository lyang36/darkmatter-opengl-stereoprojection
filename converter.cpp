#include "types.h"
#include "converter.h"
#include <cmath>
#include <iostream>

using namespace std;


CircleConverter::CircleConverter(){
    radius = 32;
    f0 = 1.83e-12;
    dr = PI/720;
    quadratic = NULL;
}


void CircleConverter::setPart(Particles * part){
    this->part = part;
}

vector<Point> * CircleConverter::getList(){
    return &pointList;
}


void CircleConverter::setRadius(REAL r){
    radius = r;
}

void CircleConverter::setPos(REAL * vpos, REAL * opos){
    (this->vpos)[0] = vpos[0];
    (this->vpos)[1] = vpos[1];
    (this->vpos)[2] = vpos[2];
    (this->opos)[0] = opos[0];
    (this->opos)[1] = opos[1];
    (this->opos)[2] = opos[2];
}

void CircleConverter::getangle(){
    REAL rv, rx;
    rv =  sqrt(vpos[0]*vpos[0]+
               vpos[1]*vpos[1]+
               vpos[2]*vpos[2]);
    for(int i=0; i<3; i++){
        vpos[i] = vpos[i]/rv;
    }
    //ro =  sqrt(opos[0]*opos[0]+
    //           opos[1]*opos[1]+
    //           opos[2]*opos[2]);
    x = part->xpos - opos[0];
    y = part->ypos - opos[1];
    z = part->zpos - opos[2];
    

    
    rx = sqrt(x*x + y*y +z*z);
    distance = rx;
    x = x/rx;
    y = y/rx;
    z = z/rx;
    
    //cout<<"vpos " << vpos[0] << " " << vpos[1] << " " << vpos[2] << " "<<vpos[3] << endl;
    //cout<<"opos " << opos[0] << " " << opos[1] << " " << opos[2] << " "<<opos[3] << endl;
    //cout<<"x y z" << x<< " " << y << " " << z<<" " <<endl;
    
    REAL costheta = x*vpos[0]+y*vpos[1]+z*vpos[2];
    theta = acos(costheta);
    //cout << "costheta " << costheta << endl;
    //REAL sintheta = sqrt(1 - costheta * costheta);
    REAL rho = (sqrt(x*x+y*y));
    REAL sinphi = y/rho;
    //REAL cosphi = x/rho;
    phi = asin(sinphi);
    if(x>0 && y>0){
    
    }else if(x>0 && y<0){
        phi = 2*PI + phi;
    }else if(x<0){
        phi = PI - phi;
    }
    
    flux = part->density * part->mass / (4.0 * PI * distance * distance);
    angularradius = (part->hsmooth) / distance;
    //cout << "dis " << distance <<
    //" angularradius "<< angularradius << endl;
    //cout << "flux " << flux << endl;
                
}
                
void CircleConverter::setf0(REAL f0){
    this->f0 = f0;
}

//void CircleConverter::setProfile(REAL (*p)(REAL, REAL)){
//    profile = p;                
//}

REAL CircleConverter::profile(REAL r, REAL r0){
    return exp(-r*r/r0/r0);
}
                
                
void CircleConverter::stereCircle(REAL theta, REAL phi, REAL dr, 
                 REAL &xc, REAL &yc, REAL &pr ){
    REAL sintpr = sin(theta + dr);
    REAL costpr = cos(theta + dr);
    REAL sintmr = sin(theta - dr);
    REAL costmr = cos(theta - dr);
    pr = -(sintpr/(1-costpr) - sintmr/(1-costmr))/2;
    REAL prho = (sintpr/(1-costpr) + sintmr/(1-costmr))/2;
    xc = prho * cos(phi);
    yc = prho * sin(phi);
}//project a circle
                
void CircleConverter::setQuadratic(REAL * q){
    quadratic = q;                
}
                
REAL CircleConverter::vz(REAL r){
    REAL r0 = radius;
    REAL d;
    REAL a = quadratic[0];
    REAL b = quadratic[1];
    REAL c = quadratic[2];
    
    d= (-b * r  - sqrt(b*b *r*r - 
                          4 * a * c * r*r + 
                       4 * c *r0*r0))/(2 * c * r );
    return d;
}
                
REAL CircleConverter::alpha(REAL flux){
    REAL trans = exp(-flux / f0);
    return 1 - trans;
                    
}
                
bool CircleConverter::convert_lower(){
    //cout << (*part).mass << " " << part->density << " "
    //<< part->hsmooth << " " << part->xpos << " "
    //<< part->ypos << " " << part->zpos << endl;
    
    getangle();
    //cout << "theta " << theta << endl;
    if(theta < PI/2) {
        pointList.clear();
        return false; //upsphere  
    }
    REAL rr = 0;
    REAL pr = 0;        //projected r
    REAL pxc, pyc;      //projected xc and yc
    REAL factor = 0;
    //REAL flux = 0;
    REAL zz = 0;
    REAL al = 0;
    Point tempoint;
    
    while (rr < angularradius) {
        factor= profile(rr, angularradius) - profile(rr + dr, angularradius);
        al = alpha(flux * factor);
        rr = rr+dr;
        stereCircle(theta, phi, rr, pxc, pyc, pr);
        zz = vz(pr * radius);
        tempoint.pos[0] = pxc * radius;
        tempoint.pos[1] = pyc * radius;
        tempoint.pos[2] = zz;
        tempoint.color[0] = 0;
        tempoint.color[1] = 0;
        tempoint.color[2] = 0;
        tempoint.color[3] = al;
        pointList.push_back(tempoint);
    }
    return true;        //lower shpere
    
}

bool CircleConverter::convert_upper(){
}