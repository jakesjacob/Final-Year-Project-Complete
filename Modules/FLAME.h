#ifndef FLAME_H
#define FLAME_H
#include "mbed.h"
#include "RA8875.h"

class FLAME {
    
    public:
    
    /** Constructor */
    FLAME() {};
    
    /** Destructor */
    ~FLAME() {};
    
    
    void drawScreenFLAME(Adafruit_RA8875 &lcd, char _pageNum);
    void printDataOneFLAME(Adafruit_RA8875 &lcd);
    void updateDataFLAME(Adafruit_RA8875 &lcd, int data1[9]);

    
    
    
    
    
    
     private:
     
    

    
};


#endif