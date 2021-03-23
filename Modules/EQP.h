#ifndef EQP_H
#define EQP_H
#include "mbed.h"
#include "RA8875.h"

class EQP {
    
    public:
    
    /** Constructor */
    EQP() {};
    
    /** Destructor */
    ~EQP() {};
    
    
    
    void drawScreenEQP(Adafruit_RA8875 &lcd);
    void printDataOneEQP(Adafruit_RA8875 &lcd);
    void updateDataEQP(Adafruit_RA8875 &lcd, int data[16]);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
     private:

    
};


#endif