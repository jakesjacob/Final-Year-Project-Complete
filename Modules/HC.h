#ifndef HC_H
#define HC_H
#include "mbed.h"
#include "RA8875.h"

class HC {
    
    
    public:
    
    /** Constructor */
    HC() {};
    
    /** Destructor */
    ~HC() {};
    
    
    
    void drawScreenHC(Adafruit_RA8875 &lcd, char _pageNum);
    void updateGraphHC(Adafruit_RA8875 &lcd);
    void printDataOneHC(Adafruit_RA8875 &lcd);
    void updateDataHC(Adafruit_RA8875 &lcd, int data1[11]);
    
    void startTicker(void);
    void timer_isr(void);
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
     private:
     
     Ticker ticker;
     volatile int g_timer_flag;
    

    
};


#endif