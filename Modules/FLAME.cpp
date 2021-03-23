#include "FLAME.h"


///// FLAME /////

int FL_y;

void FLAME::drawScreenFLAME(Adafruit_RA8875 &lcd, char _pageNum)
{
    // Title of device...........make this into the string of name from modbus??
    lcd.textEnlarge(3);
    int pageNum = _pageNum;
    switch (pageNum) 
    {
        case 1:
        lcd.textWritePro(110,20, WHITE,0, "X3301_01");
        break;
        
        case 2:
        lcd.textWritePro(110,20, WHITE,0, "X3301_02");
        break;
        
        case 3:
        lcd.textWritePro(110,20, WHITE,0, "X3301_03");
        break;
    }
    
    //big boxes
    lcd.boxDraw(10,100,386,369,10,GREY,ORANGE); //draw graph box
    lcd.boxDraw(404,100,386,369,10,GREY,BLACK); //draw other box box
    
    
    //Lines across the second box between data
    lcd.drawLine(413,117,785,117,GREY),lcd.drawLine(413,118,785,118,GREY);
    lcd.drawLine(413,147,785,147,GREY),lcd.drawLine(413,148,785,148,GREY);
    lcd.drawLine(413,177,785,177,GREY),lcd.drawLine(413,178,785,178,GREY);
    lcd.drawLine(413,207,785,207,GREY),lcd.drawLine(413,208,785,208,GREY);
    lcd.drawLine(413,237,785,237,GREY),lcd.drawLine(413,238,785,238,GREY);
    lcd.drawLine(413,267,785,267,GREY),lcd.drawLine(413,268,785,268,GREY);
    lcd.drawLine(413,297,785,297,GREY),lcd.drawLine(413,298,785,298,GREY);
    lcd.drawLine(413,327,785,327,GREY),lcd.drawLine(413,328,785,328,GREY);
    lcd.drawLine(413,357,785,357,GREY),lcd.drawLine(413,358,785,358,GREY);
    lcd.drawLine(413,387,785,387,GREY),lcd.drawLine(413,388,785,388,GREY);
    lcd.drawLine(413,417,785,417,GREY),lcd.drawLine(413,418,785,418,GREY);
    lcd.drawLine(413,447,785,447,GREY),lcd.drawLine(413,448,785,448,GREY);
    
    //Line vertically down the middle of second box
    lcd.drawLine(597,117,597,447,GREY);
    lcd.drawLine(598,117,598,447,GREY);
    
    //Home button
    lcd.boxDraw(10,10,85,85,10,GREY,BLACK);
    lcd.rectHelper(33,50,72,78,WHITE,1);
    lcd.fillTriangle(27,50,78,50,52,25,WHITE);
    
    //next and back buttons
    lcd.boxDraw(705,10,85,85,10,GREY,BLACK);
    lcd.boxDraw(615,10,85,85,10,GREY,BLACK);
    
    lcd.fillTriangle(740,27,740,77,765,52,WHITE); //right button
    lcd.fillTriangle(665,27,665,77,640,52,WHITE); //left button
}









void FLAME::printDataOneFLAME(Adafruit_RA8875 &lcd) {
    lcd.textEnlarge(0.5);
    lcd.textWritePro(430,125, WHITE,BLACK, "PROCESS VARIABLE    ");
    lcd.textWritePro(430,155, WHITE,BLACK, "SUPPLY VOLTAGE      ");
    lcd.textWritePro(430,185, WHITE,BLACK, "FIRE ALARM          ");
    lcd.textWritePro(430,215, WHITE,BLACK, "QUICK FIRE          ");
    lcd.textWritePro(430,245, WHITE,BLACK, "SUSTAINED FIRE      ");
    lcd.textWritePro(430,275, WHITE,BLACK, "LON A FAULT         ");
    lcd.textWritePro(430,305, WHITE,BLACK, "LON B FAULT         ");
    lcd.textWritePro(430,335, WHITE,BLACK, "FAULT               ");
    lcd.textWritePro(430,365, WHITE,BLACK, "SUPPLY FAULT        ");
}








void FLAME::updateDataFLAME(Adafruit_RA8875 &lcd, int data[9]) {
    
    char buffer1[32];
    char buffer2[32];

    sprintf(buffer1, "%4d", data[0]);
    sprintf(buffer2, "%4d V", data[1]);
    
    lcd.textWritePro(600,125, WHITE,BLACK, buffer1); //Process variabe
    lcd.textWritePro(600,155, WHITE,BLACK, buffer2); //Supply voltage
    
    
    for (int i = 2; i < 9; i++){
        if (i == 2){
            FL_y = 185;
        }
        if (data[i] == 0){
            lcd.textWritePro(625,FL_y, GREEN,BLACK, "FALSE");
        } else {
            lcd.textWritePro(625,FL_y, RED,BLACK, "TRUE    ");
        }
        FL_y = FL_y + 30;
    }
    
    
/*   
char buffer[32];
sprintf( buffer, 
   "%02d/%02d%4d  %02d:%02d:%02d",
   Month, Day, Year, Hour, Minute, Second
);
*/   
    
    }