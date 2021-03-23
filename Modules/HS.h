#ifndef HS_H
#define HS_H
#include "mbed.h"
#include "RA8875.h"

class HS {
    
    public:
    
    /** Constructor */
    HS() {};
    
    /** Destructor */
    ~HS() {};
    
    
    void drawScreenHS(Adafruit_RA8875 &lcd, char _pageNum);
    void updateGraphHS(Adafruit_RA8875 &lcd);
    void printDataOneHS(Adafruit_RA8875 &lcd);
    void updateDataHS(Adafruit_RA8875 &lcd, int data1[11]);
    
    void startTicker(void);
    void timer_isr(void);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
     private:
     
     Ticker ticker;
     volatile int HS_g_timer_flag;
    

    
};


#endif