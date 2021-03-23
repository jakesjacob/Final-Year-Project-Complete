#ifndef System_H
#define System_H
#include "mbed.h"
#include "RA8875.h"
#include "ASH.h"
#include "HC.h"
#include "HS.h"
#include "FLAME.h"
#include "EQP.h"
#include "SimpleModbusSlave.h"



#define HOW_MANY_ASH        3       //Define the number of ASH modules in the system        
#define HOW_MANY_HC         3       //Define the number of PIRECL modules in the system     (Flam gas)
#define HOW_MANY_HS         3       //Define the number of GTX modules in the system        (Toxic gas)
#define HOW_MANY_FLAME      3       //Define the number of X3301 modules in the system      (Flame detector)




#define MOSI    PTD2
#define MISO    PTD3
#define SCLK    PTD1
#define CS      PTD0
#define RST     PTA0





class System {
    
    
Adafruit_RA8875 lcd;
    
    public:
    
    /** Constructor */
    System(): lcd(MOSI, MISO, SCLK, CS, RST){};
    
    /** Destructor */
    ~System() {};
    
    
    
    ASH     Ash[HOW_MANY_ASH];
    HC      Hc[HOW_MANY_HC];
    HS      Hs[HOW_MANY_HS];
    FLAME   Flame[HOW_MANY_FLAME];
    EQP     Eqp;
    
    
    
    void SysInit(void);
    void clearScreen(void);
    void startScreen(void);
    void mainMenu(void);
    void HCscreen(void);
    void ASHscreen(void);
    void FLAMEscreen(void);
    void HSscreen(void);
    void EQPscreen(void);
    
    bool backPressed(void);
    bool enterPressed(void);
    bool boxOne(void);
    bool boxTwo(void);
    bool boxThree(void);
    bool boxFour(void);
    bool nextPressed(void);
    bool previousPressed(void);
    bool EqpPressed(void);
    int buttonPress(void);
    int buttonPress2(void);
    
    
    bool INT;
    float xScale;
    float yScale;
    uint16_t tx, ty;
    
    
    
    
    
    
    
    
    
    
    
    
     private:
     
     Slave slave;
    

    
};


#endif