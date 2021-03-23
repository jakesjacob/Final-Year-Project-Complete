#include "RA8875.h"
#include "System.h"
#include "mbed.h"

Serial pc(USBTX, USBRX); // tx, rxSerial pc(USBTX, USBRX); // tx, rx
System sys;


void setup()
{
    pc.baud(9600);
    pc.printf("RA8875 start\n");
}



int main()
{
    sys.SysInit();
    sys.startScreen();

    while(1){
        //sys.startScreen();
        sys.mainMenu();
    




}










    /*
    lcd.textColor(RA8875_WHITE, RA8875_RED);
    lcd.textWrite(string);
    lcd.textTransparent(RA8875_CYAN);
    lcd.textWrite(string);
    lcd.textTransparent(RA8875_GREEN);
    lcd.textWrite(string);
    lcd.textColor(RA8875_YELLOW, RA8875_CYAN);
    lcd.textWrite(string);
    //lcd.textColor(RA8875_BLACK, RA8875_MAGENTA);
    lcd.textWrite(string);
    */


    //lcd.drawCircle(100, 100, 50, RA8875_RED);
    //lcd.fillCircle(100, 100, 50, RA8875_RED);

    //lcd.fillCircle(200, 200, 50, RA8875_RED);

    
    
}

