/*Define some types*/
/*Lin Yang (Forrest)*/

#ifndef __LY__TYPES__
#define __LY__TYPES__

#define REAL double
#define Real REAL
//48 bytes
struct Particles{
    REAL mass;
    REAL density;
    REAL hsmooth;
    REAL xpos;
    REAL ypos;
    REAL zpos;
};

//a flux circle on the projection plane
//20 bytes
struct Circle{
    int radius;
    int xc;
    int yc;
    REAL flux;
};
#endif
