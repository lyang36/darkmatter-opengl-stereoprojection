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
#include "Parameter.h"
#include "datareader.h"
//#include "Skymap.h"

using namespace std;

int main(){
    Parameter params;
    params.readParameter();
    DataReader reader(params.DATAFILE);
    Particles part;
    reader.setBuf(10);
    reader.open();
    while(reader.hasNext()){
        reader.readParticle(&part);
        cout << part.mass << " " << part.density << " "
            << part.hsmooth << " " << part.xpos << " "
        << part.ypos << " " << part.zpos << endl;
    }
    reader.close();
    
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
