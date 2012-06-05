/* DataReader
 * Read data from the data file
 * set up a data file path
 * open it
 * use it untill done
 * Lin Yang 06/05/2012
 */
#include "types.h"
#include <string>
#include <fstream>

using namespace std;
class DataReader{
private:
    unsigned int partNumbers;//particle numbers in the file
    string filePath;//file path
    unsigned int readCursor; //the read Cursor of the file
    bool isopen_d;  //is open?
    unsigned int memBuffer;  //how many particles should be load in the buffer
                    //default 10^6
    unsigned int memCursor;  //reading from the memory cursor
    unsigned int memParts;   //particles in membuffer
    Particles * buffer; //particle buffer
    ifstream dataInputFile;//input stream    
    void loadBuffer();      //load buffer
public:
    DataReader(string path); //set path
    bool open();    //open the file and load the buffer
    bool isOpen();  //check is open?
    void setBuf(unsigned int mem);    //set up the buffer
    bool hasNext(); //whether the data is over?
    bool readParticle(Particles * part);   //read a particle from the file
    void close();
};

