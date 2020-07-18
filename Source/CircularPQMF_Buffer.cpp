/*
  ==============================================================================

    CircularPQMF_Buffer.cpp
   

  ==============================================================================
*/

#include "CircularPQMF_Buffer.h"

CircularPQMF_Buffer::CircularPQMF_Buffer(){
    bufferSize = 0; index = 0; buffer = NULL;
}
CircularPQMF_Buffer::~CircularPQMF_Buffer(){
    if (buffer) {delete [] buffer;} //libera espacio en bytes utilizados anteriormente
}

void CircularPQMF_Buffer::setBufferSize(int size){
    if (buffer) {delete [] buffer;}
    bufferSize = size;
    index = bufferSize - 1;
    buffer = new float[bufferSize]; //buffer es el arreglo
    clear();
}

void CircularPQMF_Buffer::clear(){
    memset(buffer, 0, bufferSize*sizeof(float));
}

void CircularPQMF_Buffer::addSample(float sample){
    buffer[index] = sample;
    if (index == 0){index = bufferSize;}
    index --;
}

float CircularPQMF_Buffer::evaluateBuffer(int indice){
    return buffer[indice];
}

