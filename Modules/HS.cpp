#include "HS.h"


///// ASH /////

int HS_Ypoints[11] = {417,417,417,417,417,417,417,417,417,417,417};
int HS_Xpoints[11] = {53,73,93,113,133,153,173,193,213,233,253};
volatile int HS_g_timer_flag = 0;
int HS_y;


void HS::drawScreenHS(Adafruit_RA8875 &lcd, char _pageNum)
{
    // Title of device...........make this into the string of name from modbus??
    lcd.textEnlarge(3);
    int pageNum = _pageNum;
    lcd.textEnlarge(3);
    switch (pageNum) 
    {
        case 1:
        lcd.textWritePro(110,20, WHITE,0, "GTX3000-HS_01");
        break;
        
        case 2:
        lcd.textWritePro(110,20, WHITE,0, "GTX3000-HS_02");
        break;
        
        case 3:
        lcd.textWritePro(110,20, WHITE,0, "GTX3000-HS_03");
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
    
    //Graph title
    lcd.textEnlarge(0.5);
    lcd.textWritePro(40,125, WHITE,ORANGE, "Graph displaying Hydrogen Sulphide PPM");

    //drawing the Y graph axis
    lcd.rectHelper(50,217,53,420,WHITE,1);
    lcd.textEnlarge(0.5);
    lcd.textWritePro(30,185,WHITE,ORANGE, "PPM");
    lcd.textWritePro(30,210,WHITE,ORANGE, "50");
    lcd.textWritePro(30,250,WHITE,ORANGE, "40");
    lcd.textWritePro(30,290,WHITE,ORANGE, "30");
    lcd.textWritePro(30,330,WHITE,ORANGE, "20");
    lcd.textWritePro(30,370,WHITE,ORANGE, "10");
    lcd.textWritePro(35,410,WHITE,ORANGE, "0");

    //drawing the X graph axis
    lcd.rectHelper(50,417,253,420,WHITE,1);
    lcd.textWritePro(47,423,WHITE,ORANGE, "0");
    lcd.textWritePro(87,423,WHITE,ORANGE, "1");
    lcd.textWritePro(127,423,WHITE,ORANGE, "2");
    lcd.textWritePro(167,423,WHITE,ORANGE, "3");
    lcd.textWritePro(207,423,WHITE,ORANGE, "4");
    lcd.textWritePro(247,423,WHITE,ORANGE, "5");
    lcd.textWritePro(127,440,WHITE,ORANGE, "TIME(s)");
    
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




void HS::updateGraphHS(Adafruit_RA8875 &lcd)
{

    //printf("graph attempt");
    if (HS_g_timer_flag) {
        HS_g_timer_flag = 0; // reset the flag
        


        for (int i =10; i>=1; i--) {
            HS_Ypoints[i] = HS_Ypoints[i-1]; // shifts the array values to the right by 1
            //printf("shifting");
        }

        //HS_Ypoints[0] = rand()%(417-217+1)+217; // adds a random value into new section


        //boxDraw(10,10,459,459,10,GREY,ORANGE); //refresh the screen before drtaweing new lines
        lcd.rectHelper(54,216,254,416,ORANGE,1);

        lcd.drawLine(HS_Xpoints[9], HS_Ypoints[9], HS_Xpoints[10], HS_Ypoints[10], WHITE);
        lcd.drawLine(HS_Xpoints[8], HS_Ypoints[8], HS_Xpoints[9], HS_Ypoints[9], WHITE);
        lcd.drawLine(HS_Xpoints[7], HS_Ypoints[7], HS_Xpoints[8], HS_Ypoints[8], WHITE);
        lcd.drawLine(HS_Xpoints[6], HS_Ypoints[6], HS_Xpoints[7], HS_Ypoints[7], WHITE);
        lcd.drawLine(HS_Xpoints[5], HS_Ypoints[5], HS_Xpoints[6], HS_Ypoints[6], WHITE);
        lcd.drawLine(HS_Xpoints[4], HS_Ypoints[4], HS_Xpoints[5], HS_Ypoints[5], WHITE);
        lcd.drawLine(HS_Xpoints[3], HS_Ypoints[3], HS_Xpoints[4], HS_Ypoints[4], WHITE);
        lcd.drawLine(HS_Xpoints[2], HS_Ypoints[2], HS_Xpoints[3], HS_Ypoints[3], WHITE);
        lcd.drawLine(HS_Xpoints[1], HS_Ypoints[1], HS_Xpoints[2], HS_Ypoints[2], WHITE);
        lcd.drawLine(HS_Xpoints[0], HS_Ypoints[0], HS_Xpoints[1], HS_Ypoints[1], WHITE);

        //printf("y 5 = %d", HS_Ypoints[5]);

    }
}



void HS::printDataOneHS(Adafruit_RA8875 &lcd) {
    lcd.textEnlarge(0.5);
    lcd.textWritePro(430,125, WHITE,BLACK, "PROCESS VARIABLE    ");
    lcd.textWritePro(430,155, WHITE,BLACK, "SUPPLY VOLTAGE      ");
    lcd.textWritePro(430,185, WHITE,BLACK, "HIGH ALARM SET POINT");
    lcd.textWritePro(430,215, WHITE,BLACK, "LOW ALARM SET POINT ");
    lcd.textWritePro(430,245, WHITE,BLACK, "HIGH ALARM ACTIVE   ");
    lcd.textWritePro(430,275, WHITE,BLACK, "LOW ALARM ACTIVE    ");
    lcd.textWritePro(430,305, WHITE,BLACK, "FAULT               ");
    lcd.textWritePro(430,335, WHITE,BLACK, "SENSOR FAULT        ");
    lcd.textWritePro(430,365, WHITE,BLACK, "VOLTAGE FAULT       ");
    lcd.textWritePro(430,395, WHITE,BLACK, "LON A FAULT         ");
    lcd.textWritePro(430,425, WHITE,BLACK, "LON B FAULT         ");
}




void HS::updateDataHS(Adafruit_RA8875 &lcd, int data[11]) {
    
    char buffer1[32];
    char buffer2[32];
    char buffer3[32];
    char buffer4[32];

    sprintf(buffer1, "%4d", data[0]);
    sprintf(buffer2, "%4d V", data[1]);
    sprintf(buffer3, "%4d PPM", data[2]);
    sprintf(buffer4, "%4d PPM", data[3]);
    
    lcd.textWritePro(600,125, WHITE,BLACK, buffer1); //Process variabe
    lcd.textWritePro(600,155, WHITE,BLACK, buffer2); //Supply voltage
    lcd.textWritePro(600,185, WHITE,BLACK, buffer3); //High set point
    lcd.textWritePro(600,215, WHITE,BLACK, buffer4); //Low set point
    
    int HSscaledValue = data[0]*4;
    if (HSscaledValue > 200){
        HSscaledValue = 200;
        }
    
    HS_Ypoints[0] = 417 - HSscaledValue;;
    
    
    for (int i = 4; i < 11; i++){
        if (i == 4){
            HS_y = 245;
        }
        if (data[i] == 0){
            lcd.textWritePro(625,HS_y, GREEN,BLACK, "FALSE");
        } else {
            lcd.textWritePro(625,HS_y, RED,BLACK, "TRUE     ");
        }
        HS_y = HS_y + 30;
    }
    
    
/*   
char buffer[32];
sprintf( buffer, 
   "%02d/%02d%4d  %02d:%02d:%02d",
   Month, Day, Year, Hour, Minute, Second
);
*/   
    
    }











void HS::startTicker(void)
{
    ticker.attach(callback(this, &HS::timer_isr), 0.5); // attach ticker 0.5 - ( 1/2 second fire rate )
}


void HS::timer_isr(void)
{
    HS_g_timer_flag = 1;   /// set flag in ISR
}