#ifndef ASH_H
#define ASH_H
#include "mbed.h"
#include "RA8875.h"

class ASH {
    
    public:
    
    /** Constructor */
    ASH() {};
    
    /** Destructor */
    ~ASH() {};
    
    
    
    void drawScreenASH(Adafruit_RA8875 &lcd, char _pageNum);
    void printDataOneASH(Adafruit_RA8875 &lcd);
    void updateDataASH(Adafruit_RA8875 &lcd, int data[8]);
    void updateData2ASH(Adafruit_RA8875 &lcd, int data[7]);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
     private:

    
};


#endif