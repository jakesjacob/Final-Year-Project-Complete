#include "EQP.h"

int EQP_y;

void EQP::drawScreenEQP(Adafruit_RA8875 &lcd)
{
    // Title of device...........make this into the string of name from modbus??
    lcd.textEnlarge(3);
    lcd.textWritePro(110,20, WHITE,0, "EQP CONTROLLER");
    
    //big boxes
    lcd.boxDraw(10,100,386,369,10,GREY,BLACK); //draw graph box
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
    
    
    //Lines across the first box between data
    lcd.drawLine(19,117,391,117,GREY),lcd.drawLine(19,118,391,118,GREY);
    lcd.drawLine(19,147,391,147,GREY),lcd.drawLine(19,148,391,148,GREY);
    lcd.drawLine(19,177,391,177,GREY),lcd.drawLine(19,178,391,178,GREY);
    lcd.drawLine(19,207,391,207,GREY),lcd.drawLine(19,208,391,208,GREY);
    lcd.drawLine(19,237,391,237,GREY),lcd.drawLine(19,238,391,238,GREY);
    lcd.drawLine(19,267,391,267,GREY),lcd.drawLine(19,268,391,268,GREY);
    lcd.drawLine(19,297,391,297,GREY),lcd.drawLine(19,298,391,298,GREY);
    lcd.drawLine(19,327,391,327,GREY),lcd.drawLine(19,328,391,328,GREY);
    lcd.drawLine(19,357,391,357,GREY),lcd.drawLine(19,358,391,358,GREY);
    lcd.drawLine(19,387,391,387,GREY),lcd.drawLine(19,388,391,388,GREY);
    lcd.drawLine(19,417,391,417,GREY),lcd.drawLine(19,418,391,418,GREY);
    lcd.drawLine(19,447,391,447,GREY),lcd.drawLine(19,448,391,448,GREY);
    
    //Line vertically down the middle of second box
    lcd.drawLine(597,117,597,447,GREY);
    lcd.drawLine(598,117,598,447,GREY);
    
    //Line vertically down the middle of first box
    lcd.drawLine(203,117,203,447,GREY);
    lcd.drawLine(204,117,204,447,GREY);
    
    //Home button
    lcd.boxDraw(10,10,85,85,10,GREY,BLACK);
    lcd.rectHelper(33,50,72,78,WHITE,1);
    lcd.fillTriangle(27,50,78,50,52,25,WHITE);
    

}





void EQP::printDataOneEQP(Adafruit_RA8875 &lcd) {
    lcd.textEnlarge(0.5);
    lcd.textWritePro(430,125, WHITE,BLACK, "TROUBLE             ");
    lcd.textWritePro(430,155, WHITE,BLACK, "FIRE ALARM          ");
    lcd.textWritePro(430,185, WHITE,BLACK, "LOW GAS ALARM       ");
    lcd.textWritePro(430,215, WHITE,BLACK, "HIGH GAS ALARM      ");
    lcd.textWritePro(430,245, WHITE,BLACK, "SOUNDERS SILENCED   ");
    lcd.textWritePro(430,275, WHITE,BLACK, "CONTROLLER FAULT    ");
    lcd.textWritePro(430,305, WHITE,BLACK, "LON FAULT           ");
    lcd.textWritePro(430,335, WHITE,BLACK, "PORT 1 BAUD RATE    ");
    
    lcd.textWritePro(36,125, WHITE,BLACK, "BATTERY FAULT       ");
    lcd.textWritePro(36,155, WHITE,BLACK, "UPS FAULT           ");
    lcd.textWritePro(36,185, WHITE,BLACK, "GROUND FAULT        ");
    lcd.textWritePro(36,215, WHITE,BLACK, "24 VDC HEALTHY      ");
    lcd.textWritePro(36,245, WHITE,BLACK, "GAS DAMPER CLOSING  ");
    lcd.textWritePro(36,275, WHITE,BLACK, "GAS DAMPER CLOSED   ");
    lcd.textWritePro(36,305, WHITE,BLACK, "GAS DAMPER OPEN   ");
    lcd.textWritePro(36,335, WHITE,BLACK, "EXTRACT FANS ACTIVE ");
 
}


void EQP::updateDataEQP(Adafruit_RA8875 &lcd, int data[16]) {
     
     //char buffer1[32];
     //sprintf(buffer1, "% BPS", data[8]);
     lcd.textWritePro(610,335, WHITE,BLACK, " 9600 BPS"); //Process variabe
     
    for (int i = 0; i < 7; i++){
        if (i == 0){
            EQP_y = 125;
        }
        if (data[i] == 0){
            lcd.textWritePro(625,EQP_y, GREEN,BLACK, "FALSE");
        } else {
            lcd.textWritePro(625,EQP_y, RED,BLACK, "TRUE   ");
        }
        EQP_y = EQP_y + 30;
    }
    
    for (int i = 8; i < 11; i++){
        if (i == 8){
            EQP_y = 125;
        }
        if (data[i] == 0){
            lcd.textWritePro(231,EQP_y, GREEN,BLACK, "FALSE");
        } else {
            lcd.textWritePro(231,EQP_y, RED,BLACK, "TRUE   ");
        }
        EQP_y = EQP_y + 30;
    }
    
    for (int i = 11; i < 16; i++){
        if (i == 11){
            EQP_y = 215;
        }
        if (data[i] == 0){
            lcd.textWritePro(231,EQP_y, GREEN,BLACK, "FALSE");
        } else {
            lcd.textWritePro(231,EQP_y, MAGENTA,BLACK, "TRUE   ");
        }
        EQP_y = EQP_y + 30;
    }
}