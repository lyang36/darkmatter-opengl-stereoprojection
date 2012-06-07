/* GPU rendering the darkmatter all skymap. Using stereographic projection */
/* Classes:
 * Parameter: read parameter from configure.ini. 
 * Including the units infomation, datafile path etc.
 * Kernel.cu: the GPU files
 * Skymap: dealwith all other stuffes
 *
*/
#include <string>
#include <iostream>
#include <vector>
#include "types.h"
#include "Parameter.h"
#include "datareader.h"
#include "converter.h"
#include "pointSprite.h"

//#include "Skymap.h"

using namespace std;

int main(int argc, char** argv){
    Parameter params;
    params.readParameter();
    
    pointSprite sprite;
    sprite.reader.setPath(params.DATAFILE);
    REAL opos[] = {params.oposx, params.oposy, params.oposz};
    REAL vpos[] = {params.vposx, params.vposy, params.vposz};
    sprite.converter.setPos(vpos, opos);
    sprite.startDisplay(argc, argv);
    
/*     DataReader reader(params.DATAFILE);
    Particles part;
    reader.setBuf(10);
    reader.open();
    CircleConverter converter;
    REAL q[] ={1.0, 0.0, 1.0};
    converter.setQuadratic(q);
    
   while(reader.hasNext()){
        reader.readParticle(&part);
        cout << part.mass << " " << part.density << " "
            << part.hsmooth << " " << part.xpos << " "
        << part.ypos << " " << part.zpos << endl;
    }
    
    cout << part.mass << " " << part.density << " "
    << part.hsmooth << " " << part.xpos << " "
    << part.ypos << " " << part.zpos << endl;
    
    part.ypos = 0.4;
    part.xpos = 0.3;
    converter.setPart(&part);
    REAL opos[] = {params.oposx, params.oposy, params.oposz};
    REAL vpos[] = {params.vposx, params.vposy, params.vposz};
    converter.setPos(vpos,opos);
    converter.convert_lower();
    vector<Point> * vv;
    vv = converter.getList();
    for(int i=0; i<(vv->size()); i++){
        cout << "xc: " << (*vv)[i].pos[0] << " yc: "
        << (*vv)[i].pos[1] << " zc: " << (*vv)[i].pos[2] <<
        " color1: " << (*vv)[i].color[0] << " color2: " << (*vv)[i].color[1] 
        << " color3: " << (*vv)[i].color[2] << " color4: " << (*vv)[i].color[3]<< endl ;
    }
 
    reader.close();
 */
    /*cout << "CPU_MEM " << params.CPU_MEM << endl;
    cout << "FLUXFACTOR " << params.FLUXFACTOR << endl;
    cout << "GRAPHSIZE " << params.GRAPHSIZE << endl;
    cout << "DATAFILE " << params.DATAFILE << endl;
    cout << "OPOSX " << params.oposx << endl;
    cout << "OPOSY " << params.oposy << endl;
    cout << "OPOSZ " << params.oposz << endl;
    cout << "VPOSX " << params.vposx << endl;
    cout << "VPOSY " << params.vposy << endl;
    cout << "VPOSZ " << params.vposz << endl;
    cout << "TEST " << params.TEST << endl;*/ 
    //Skymap skymap(&params);
    //skymap.getMap();
    
    cout << "ok" << endl;
    return 0;    
}
