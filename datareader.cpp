#include <string>
#include <iostream>
#include "datareader.h"

using namespace std;

DataReader::DataReader(string path){
    filePath = path;
    memBuffer = 1000000;
    memCursor = 0;
    readCursor = 0;
    partNumbers = 0;
    memParts = 0;
    buffer = NULL;
}

DataReader::DataReader(){
    DataReader("");
}

void DataReader::setPath(string path){
    filePath = path;
}

//open the file and load buffer
bool DataReader::open(){
    readCursor = 0;
    if(buffer != NULL){
        //free buffer
        free(buffer);
    }
    memCursor = 0;
    memParts = 0;
    buffer = new Particles[memBuffer];
    dataInputFile.open(filePath.c_str(), ios::binary);
    dataInputFile.read((char*)&partNumbers, sizeof(int));
    cout << "Particles: " << partNumbers << endl;
    cout << "Load to buffer ... " << endl;
    loadBuffer();
    return dataInputFile.is_open();
}

void DataReader::loadBuffer(){
    int resParts = partNumbers - (readCursor - memCursor + memParts);
    if(resParts > memBuffer){
        //setup new readCursor
        readCursor = readCursor - memCursor + memParts;
        memCursor = 0;
        memParts = memBuffer;
        
        //load buffer
        dataInputFile.read((char *) buffer, sizeof(Particles) * memParts);
    }else{
        //setup new readCursor
        readCursor = readCursor - memCursor + memParts;
        memCursor = 0;
        memParts = resParts;
        
        //cout << memParts << endl;
        //load buffer
        dataInputFile.read((char *) buffer, sizeof(Particles) * memParts);
    }
    
}

bool DataReader::isOpen(){
    return dataInputFile.is_open();
}

void DataReader::setBuf(unsigned int mem){
    if(buffer != NULL){
        //free buffer
        free(buffer);
    }
    memCursor = 0;
    memParts = 0;
    memBuffer = mem;
}

bool DataReader::hasNext(){
    if(readCursor < partNumbers)
        return true;
    else
        return false;
}

bool DataReader::readParticle(Particles * part){
    if(memCursor == memBuffer){
        //cout << "load buffer\n";
        loadBuffer();
    }
    if(hasNext()){
        part->mass = buffer[memCursor].mass;
        part->density = buffer[memCursor].density;
        part->hsmooth = buffer[memCursor].hsmooth;
        part->xpos = buffer[memCursor].xpos;
        part->ypos = buffer[memCursor].ypos;
        part->zpos = buffer[memCursor].zpos;
        readCursor ++; //move the cursor
        memCursor ++;  //move the cursor
    }else{
        return false;
    }
    return true;
}

void DataReader::close(){
    if(buffer != NULL)
        free(buffer);
    buffer = NULL;
    dataInputFile.close();
}


Particles * DataReader::getBuf(){
    return buffer;
}

unsigned int DataReader::getBufSize(){
    return memParts;
}
