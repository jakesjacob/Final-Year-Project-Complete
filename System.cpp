#include "System.h"


///// System parameters /////


DigitalIn   INT(PTA2);




//----------- Registers of the slave ---------------------------------------------------------------
enum {
    // Add or remove registers and your good to go...
    // The first register starts at address 0

    // DATA SET 1 FOR HC DEVICES (PIRECL) DataArray_1
    _STATE0,_STATE1,_STATE2,_STATE3,_STATE4,_STATE5,_STATE6,_STATE7,_STATE8,_STATE9,_STATE10,
    // DATA SET 2 FOR HC DEVICES (PIRECL) DataArray_2
    _STATE11,_STATE12,_STATE13,_STATE14,_STATE15,_STATE16,_STATE17,_STATE18,_STATE19,_STATE20,_STATE21,
    // DATA SET 3 FOR HC DEVICES (PIRECL) DataArray_3
    _STATE22,_STATE23,_STATE24,_STATE25,_STATE26,_STATE27,_STATE28,_STATE29,_STATE30,_STATE31,_STATE32,


    // DATA SET 1 FOR ASH DEVICES DataArray_4
    _STATE33,_STATE34,_STATE35,_STATE36,_STATE37,_STATE38,_STATE39,_STATE40,
    // DATA SET 2 FOR ASH DEVICES DataArray_5
    _STATE41,_STATE42,_STATE43,_STATE44,_STATE45,_STATE46,_STATE47,_STATE48,
    // DATA SET 3 FOR ASH DEVICES DataArray_6
    _STATE49,_STATE50,_STATE51,_STATE52,_STATE53,_STATE54,_STATE55,_STATE56,


    // DATA SET 1 FOR FLAME DEVICES DataArray_7
    _STATE57,_STATE58,_STATE59,_STATE60,_STATE61,_STATE62,_STATE63,_STATE64,_STATE65,
    // DATA SET 2 FOR FLAME DEVICES DataArray_8
    _STATE66,_STATE67,_STATE68,_STATE69,_STATE70,_STATE71,_STATE72,_STATE73,_STATE74,
    // DATA SET 3 FOR FLAME DEVICES DataArray_9
    _STATE75,_STATE76,_STATE77,_STATE78,_STATE79,_STATE80,_STATE81,_STATE82,_STATE83,


    // DATA SET 1 FOR HS DEVICES (GTX) DataArray_10
    _STATE84,_STATE85,_STATE86,_STATE87,_STATE88,_STATE89,_STATE90,_STATE91,_STATE92,_STATE93,_STATE94,
    // DATA SET 2 FOR HS DEVICES (GTX) DataArray_11
    _STATE95,_STATE96,_STATE97,_STATE98,_STATE99,_STATE100,_STATE101,_STATE102,_STATE103,_STATE104,_STATE105,
    // DATA SET 3 FOR HS DEVICES (GTX) DataArray_12
    _STATE106,_STATE107,_STATE108,_STATE109,_STATE110,_STATE111,_STATE112,_STATE113,_STATE114,_STATE115,_STATE116,


    // DATA SET 1 FOR APOLLO DEVICES (ash connections) DataArray_13
    _STATE117,_STATE118,_STATE119,_STATE120,_STATE121,_STATE122,_STATE123,_STATE124,
    // DATA SET 2 FOR APOLLO DEVICES DataArray_14
    _STATE125,_STATE126,_STATE127,_STATE128,_STATE129,_STATE130,_STATE131,_STATE132,
    // DATA SET 3 FOR APOLLO DEVICES DataArray_15
    _STATE133,_STATE134,_STATE135,_STATE136,_STATE137,_STATE138,_STATE139,_STATE140,

    // DATA SET 2 FOR EQP DatArray_16
    _STATE141,_STATE142,_STATE143,_STATE144,_STATE145,_STATE146,_STATE147,_STATE148,_STATE149,_STATE150,_STATE151,_STATE152,_STATE153,_STATE154,_STATE155,_STATE156,

    // CONNECTION TEST VALUE
    _STATE157,
    
    // SOUNDER TEST VALUE
    _STATE158,_STATE159,


    TOTAL_ERRORS, // leave this one
    TOTAL_REGS_SIZE // total number of registers for function 3 and 16 share the same register array
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
//--------------------------------------------------------------------------------------------------





















/////////////// SYSTEM START ///////////////////////////////////////////////////////////////////////////////////

void System::SysInit(void)
{

    slave.modbus_configure(9600, 1, TOTAL_REGS_SIZE, 0);
    lcd.begin(RA8875_800x480);
    lcd.displayOn(true);
    lcd.GPIOX(true);      // Enable lcd - display enable tied to GPIOX
    lcd.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
    lcd.PWM1out(255);
    lcd.fillScreen(BLACK);
    lcd.touchEnable(true);

    for(int i=0; i<HOW_MANY_HC; i++) {
        Hc[i].startTicker();
    }
    for(int i=0; i<HOW_MANY_HS; i++) {
        Hs[i].startTicker();
    }

    /* Render some text! */
    lcd.textEnlarge(3);
    lcd.textWritePro(10,30,WHITE,0,"Hello, Jacob! ");
    lcd.textEnlarge(1.2);
    lcd.textWritePro(10,150,WHITE,0, "Get that 1st!!!");
    lcd.textWritePro(10, 450, GREEN, 0, "Testing 1.. 2");
    wait(1);
    clearScreen();
}




void System::clearScreen(void)
{
    lcd.fillScreen(BLACK);
    lcd.graphicsMode();
    lcd.rectHelper(0,0,800,480,WHITE,1);
    lcd.rectHelper(5,5,794,474,BLACK,1);
}




void System::startScreen(void)
{
    lcd.textEnlarge(3);
    lcd.textWritePro(40,30,WHITE,0,"ELEC3875 FINAL PROJECT");
    lcd.textWritePro(40,380,WHITE,0,"JACOB HORGAN-201061845");
    lcd.textEnlarge(1);
    lcd.textWritePro(280,225, WHITE,0,"NO CONNECTION...    ");
    slave.modbus_update(holdingRegs);
    //while(1){
    //slave.modbus_update(holdingRegs);
    //if (holdingRegs[_STATE157] >0){
    //    break;
    //}
    //}
        clearScreen();
        lcd.textEnlarge(3);
        lcd.textWritePro(40,30,WHITE,0,"ELEC3875 FINAL PROJECT");
        lcd.textWritePro(40,380,WHITE,0,"JACOB HORGAN-201061845");
        lcd.textWritePro(320,205, WHITE,0,"PRESS");
        while(1) {
            if (enterPressed()) {
                break;
            }
        }
    
    mainMenu();
}


///////////////// END OF SYSTEM START //////////////////////////////////////////////////////////////////



///////////////// SCREEN CHOICES //////////////////////////////////////////////////////////////////////

void System::mainMenu(void)
{
    clearScreen();
    lcd.textEnlarge(3);
    lcd.rectHelper(0,0,800,125,WHITE,1);
    lcd.rectHelper(5,5,794,121,BLACK,1);
    lcd.textWritePro(45,30,WHITE,0,"FIRE AND GAS DETECTION");

    lcd.textEnlarge(1);
    lcd.boxDraw(215,150,370,110,10,GREY,LGREY); //EQP BOX
    lcd.textWritePro(285,190,MAGENTA,LGREY,"EQP CONTROLLER");

    lcd.boxDraw(20,280,175,175,10,GREY,LGREY); //BOX ONE
    lcd.textWritePro(58,300,MAGENTA,LGREY,"PIRECL");
    lcd.textWritePro(50,340,MAGENTA,LGREY,"DEVICES");

    lcd.boxDraw(215,280,175,175,10,GREY,LGREY); //BOX TWO
    lcd.textWritePro(245,300,MAGENTA,LGREY,"GTX3000");
    lcd.textWritePro(245,340,MAGENTA,LGREY,"DEVICES");

    lcd.boxDraw(410,280,175,175,10,GREY,LGREY); //BOX THREE
    lcd.textWritePro(455,300,MAGENTA,LGREY,"X3301");
    lcd.textWritePro(440,340,MAGENTA,LGREY,"DEVICES");

    lcd.boxDraw(605,280,175,175,10,GREY,LGREY); //BOX FOUR
    lcd.textWritePro(665,300,MAGENTA,LGREY,"ASH");
    lcd.textWritePro(635,340,MAGENTA,LGREY,"DEVICES");


    int state = 0;
    while (state == 0) {
        state = buttonPress();
        slave.modbus_update(holdingRegs);
    }
    switch(state) {

        case 1:
            clearScreen();
            HCscreen();
            break;

        case 2:
            clearScreen();
            HSscreen();
            break;

        case 3:
            clearScreen();
            FLAMEscreen();
            break;

        case 4:
            clearScreen();
            ASHscreen();
            break;

        case 5:
            clearScreen();
            EQPscreen();
            break;
    }
}


int pageNum = 1;




//==============================================================================
//---------------------------HC SCREEN-----------------------------------------
//==============================================================================


void System::HCscreen(void)
{

    int homeFlag = 0;
    if (pageNum > HOW_MANY_HC) {
        pageNum = 1;
    }

    switch (pageNum) {
        //---------PAGE 1--------------
        case 1:
            Hc[0].drawScreenHC(lcd, pageNum);
            Hc[0].printDataOneHC(lcd);
            while(1) {
                Hc[0].updateGraphHC(lcd);
                slave.modbus_update(holdingRegs);
                int DataArray_1[11] = {holdingRegs[_STATE0], holdingRegs[_STATE1], holdingRegs[_STATE2], holdingRegs[_STATE3], holdingRegs[_STATE4], holdingRegs[_STATE5], holdingRegs[_STATE6], holdingRegs[_STATE7], holdingRegs[_STATE8], holdingRegs[_STATE9], holdingRegs[_STATE10]};
                Hc[0].updateDataHC(lcd, DataArray_1);

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }

            break;

        //----------PAGE 2--------------
        case 2:
            Hc[1].drawScreenHC(lcd, pageNum);
            Hc[1].printDataOneHC(lcd);
            while(1) {
                Hc[1].updateGraphHC(lcd);
                slave.modbus_update(holdingRegs);
                int DataArray_2[11] = {holdingRegs[_STATE11], holdingRegs[_STATE12], holdingRegs[_STATE13], holdingRegs[_STATE14], holdingRegs[_STATE15], holdingRegs[_STATE16], holdingRegs[_STATE17], holdingRegs[_STATE18], holdingRegs[_STATE19], holdingRegs[_STATE20], holdingRegs[_STATE21]};
                Hc[1].updateDataHC(lcd, DataArray_2);

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }


            break;

        //----------PAGE 3 -------------------
        case 3:
            Hc[2].drawScreenHC(lcd, pageNum);
            Hc[2].printDataOneHC(lcd);
            while(1) {
                Hc[2].updateGraphHC(lcd);
                slave.modbus_update(holdingRegs);
                int DataArray_3[11] = {holdingRegs[_STATE22], holdingRegs[_STATE23], holdingRegs[_STATE24], holdingRegs[_STATE25], holdingRegs[_STATE26], holdingRegs[_STATE27], holdingRegs[_STATE28], holdingRegs[_STATE29], holdingRegs[_STATE30], holdingRegs[_STATE31], holdingRegs[_STATE32]};
                Hc[2].updateDataHC(lcd, DataArray_3);

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }

            break;
    }

    if (homeFlag == 1) {
        mainMenu();
    }

}

//==============================================================================
//----------------------------ASH SCREEN----------------------------------------
//==============================================================================

void System::ASHscreen(void)
{

    int homeFlag = 0;
    if (pageNum > HOW_MANY_ASH) {
        pageNum = 1;
    }

    switch (pageNum) {
        //---------PAGE 1--------------
        case 1:
            Ash[0].drawScreenASH(lcd, pageNum);
            Ash[0].printDataOneASH(lcd);
            while(1) {
                slave.modbus_update(holdingRegs);
                int DataArray_4[8] = {holdingRegs[_STATE33], holdingRegs[_STATE34], holdingRegs[_STATE35], holdingRegs[_STATE36], holdingRegs[_STATE37], holdingRegs[_STATE38], holdingRegs[_STATE39], holdingRegs[_STATE40]};
                int DataArray_13[7] = {holdingRegs[_STATE117], holdingRegs[_STATE118], holdingRegs[_STATE119], holdingRegs[_STATE120], holdingRegs[_STATE121], holdingRegs[_STATE122], holdingRegs[_STATE123]};
                Ash[0].updateDataASH(lcd, DataArray_4);
                Ash[0].updateData2ASH(lcd, DataArray_13);

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }

            break;

        //----------PAGE 2--------------
        case 2:
            Ash[1].drawScreenASH(lcd, pageNum);
            Ash[1].printDataOneASH(lcd);
            while(1) {
                slave.modbus_update(holdingRegs);
                int DataArray_5[8] = {holdingRegs[_STATE41], holdingRegs[_STATE42], holdingRegs[_STATE43], holdingRegs[_STATE44], holdingRegs[_STATE45], holdingRegs[_STATE46], holdingRegs[_STATE47], holdingRegs[_STATE48]};
                int DataArray_14[7] = {holdingRegs[_STATE124], holdingRegs[_STATE125], holdingRegs[_STATE126], holdingRegs[_STATE127], holdingRegs[_STATE128], holdingRegs[_STATE129], holdingRegs[_STATE130]};
                Ash[1].updateDataASH(lcd, DataArray_5);
                Ash[1].updateData2ASH(lcd, DataArray_14);

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }


            break;

        //----------PAGE 3 -------------------
        case 3:
            Ash[2].drawScreenASH(lcd, pageNum);
            Ash[2].printDataOneASH(lcd);
            while(1) {
                slave.modbus_update(holdingRegs);
                int DataArray_6[8] = {holdingRegs[_STATE49], holdingRegs[_STATE50], holdingRegs[_STATE51], holdingRegs[_STATE52], holdingRegs[_STATE53], holdingRegs[_STATE54], holdingRegs[_STATE55], holdingRegs[_STATE56]};
                int DataArray_15[7] = {holdingRegs[_STATE131], holdingRegs[_STATE132], holdingRegs[_STATE133], holdingRegs[_STATE134], holdingRegs[_STATE135], holdingRegs[_STATE136], holdingRegs[_STATE137]};
                Ash[2].updateDataASH(lcd, DataArray_6);
                Ash[2].updateData2ASH(lcd, DataArray_15);

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }

            break;
    }

    if (homeFlag == 1) {
        mainMenu();
    }

}






//==============================================================================
//----------------------------FLAME SCREEN--------------------------------------
//==============================================================================


void System::FLAMEscreen(void)
{

    int homeFlag = 0;

    while (homeFlag == 0) {
        if (pageNum > HOW_MANY_FLAME) {
            pageNum = 1;
        }

        switch (pageNum) {
            //---------PAGE 1--------------
            case 1:
                Flame[0].drawScreenFLAME(lcd, pageNum);
                Flame[0].printDataOneFLAME(lcd);
                while(1) {
                    slave.modbus_update(holdingRegs);
                    int DataArray_7[9] = {holdingRegs[_STATE57], holdingRegs[_STATE58], holdingRegs[_STATE59], holdingRegs[_STATE60], holdingRegs[_STATE61], holdingRegs[_STATE62], holdingRegs[_STATE63], holdingRegs[_STATE64], holdingRegs[_STATE65]};
                    Flame[0].updateDataFLAME(lcd, DataArray_7);

                    if (backPressed()) {
                        homeFlag = 1;
                        break;
                    }
                    if (nextPressed()) {
                        pageNum = pageNum++;
                        break;
                    }
                    if (previousPressed()) {
                        pageNum = pageNum--;
                        break;
                    }
                }

                break;

            //----------PAGE 2--------------
            case 2:
                Flame[1].drawScreenFLAME(lcd, pageNum);
                Flame[1].printDataOneFLAME(lcd);
                while(1) {
                    slave.modbus_update(holdingRegs);
                    int DataArray_8[9] = {holdingRegs[_STATE65], holdingRegs[_STATE66], holdingRegs[_STATE67], holdingRegs[_STATE68], holdingRegs[_STATE69], holdingRegs[_STATE70], holdingRegs[_STATE71], holdingRegs[_STATE72], holdingRegs[_STATE73]};
                    Flame[1].updateDataFLAME(lcd, DataArray_8);

                    if (backPressed()) {
                        homeFlag = 1;
                        break;
                    }
                    if (EqpPressed()) {
                        pageNum = pageNum++;
                        break;
                    }
                    if (previousPressed()) {
                        pageNum = pageNum--;
                        break;
                    }
                }


                break;

            //----------PAGE 3 -------------------
            case 3:
                Flame[2].drawScreenFLAME(lcd, pageNum);
                Flame[2].printDataOneFLAME(lcd);
                while(1) {
                    slave.modbus_update(holdingRegs);
                    int DataArray_9[9] = {holdingRegs[_STATE74], holdingRegs[_STATE75], holdingRegs[_STATE76], holdingRegs[_STATE77], holdingRegs[_STATE78], holdingRegs[_STATE79], holdingRegs[_STATE80], holdingRegs[_STATE81], holdingRegs[_STATE82]};
                    Flame[2].updateDataFLAME(lcd, DataArray_9);

                    if (backPressed()) {
                        homeFlag = 1;
                        break;
                    }
                    if (nextPressed()) {
                        pageNum = pageNum++;
                        break;
                    }
                    if (previousPressed()) {
                        pageNum = pageNum--;
                        break;
                    }
                }

                break;
        }

        //if (homeFlag == 1) {
        //mainMenu();
        //break;
    }

}



//==============================================================================
//------------------------ HS SCREEN--------------------------------------------
//==============================================================================

void System::HSscreen(void)
{

    int homeFlag = 0;
    if (pageNum > HOW_MANY_HS) {
        pageNum = 1;
    }

    switch (pageNum) {
        //---------PAGE 1--------------
        case 1:
            Hs[0].drawScreenHS(lcd, pageNum);
            Hs[0].printDataOneHS(lcd);
            while(1) {
                Hs[0].updateGraphHS(lcd);
                slave.modbus_update(holdingRegs);
                int DataArray_10[11] = {holdingRegs[_STATE84], holdingRegs[_STATE85], holdingRegs[_STATE86], holdingRegs[_STATE87], holdingRegs[_STATE88], holdingRegs[_STATE89], holdingRegs[_STATE90], holdingRegs[_STATE91], holdingRegs[_STATE92], holdingRegs[_STATE93], holdingRegs[_STATE94]};
                Hs[0].updateDataHS(lcd, DataArray_10);
                
                    if (backPressed()) {
                        homeFlag = 1;
                        break;
                    }
                    if (nextPressed()) {
                        pageNum = pageNum++;
                        break;
                    }
                    if (previousPressed()) {
                        pageNum = pageNum--;
                        break;
                    }
                

            }

            if (homeFlag == 1) {
        break;
    }

        //----------PAGE 2--------------
        case 2:
            Hs[1].drawScreenHS(lcd, pageNum);
            Hs[1].printDataOneHS(lcd);
            while(1) {
                Hs[1].updateGraphHS(lcd);
                slave.modbus_update(holdingRegs);
                int DataArray_11[11] = {holdingRegs[_STATE95], holdingRegs[_STATE96], holdingRegs[_STATE97], holdingRegs[_STATE98], holdingRegs[_STATE99], holdingRegs[_STATE100], holdingRegs[_STATE101], holdingRegs[_STATE102], holdingRegs[_STATE103], holdingRegs[_STATE104], holdingRegs[_STATE105]};
                Hs[1].updateDataHS(lcd, DataArray_11);
                
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }


           if (homeFlag == 1) {
        break;
    }

        //----------PAGE 3 --------------
        case 3:
            Hs[2].drawScreenHS(lcd, pageNum);
            Hs[2].printDataOneHS(lcd);
            while(1) {
                Hs[2].updateGraphHS(lcd);
                slave.modbus_update(holdingRegs);
                int DataArray_12[11] = {holdingRegs[_STATE106], holdingRegs[_STATE107], holdingRegs[_STATE108], holdingRegs[_STATE109], holdingRegs[_STATE110], holdingRegs[_STATE111], holdingRegs[_STATE112], holdingRegs[_STATE113], holdingRegs[_STATE114], holdingRegs[_STATE115], holdingRegs[_STATE115]};
                Hs[2].updateDataHS(lcd, DataArray_12);
                
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                

                if (backPressed()) {
                    homeFlag = 1;
                    break;
                }
                if (nextPressed()) {
                    pageNum = pageNum++;
                    break;
                }
                if (previousPressed()) {
                    pageNum = pageNum--;
                    break;
                }
            }
            if (homeFlag == 1) {
        break;
    }

            //break;
    }

    if (homeFlag == 1) {
        mainMenu();
    }

}




//==============================================================================
//------------------------ EQP SCREEN--------------------------------------------
//==============================================================================

void System::EQPscreen(void)
{

    Eqp.drawScreenEQP(lcd);
    Eqp.printDataOneEQP(lcd);

    while(1) {
        slave.modbus_update(holdingRegs);
        holdingRegs[_STATE158] = 1;
        int DataArray_16[16] = {holdingRegs[_STATE141], holdingRegs[_STATE142], holdingRegs[_STATE143], holdingRegs[_STATE144], holdingRegs[_STATE145], holdingRegs[_STATE146], holdingRegs[_STATE147], holdingRegs[_STATE148], holdingRegs[_STATE149], holdingRegs[_STATE150], holdingRegs[_STATE151], holdingRegs[_STATE152], holdingRegs[_STATE153], holdingRegs[_STATE154], holdingRegs[_STATE155], holdingRegs[_STATE156]};
        Eqp.updateDataEQP(lcd, DataArray_16);
        if (backPressed()) {
            break;
        }
    }
    mainMenu();
}


///////////// END OF SCREEN CHOICES ////////////////////////////////////////////////////////



//////////// BUTTON PRESSES //////////////////////////////////////////////////////////////////

bool System::enterPressed(void)
{
    bool _ret = false;

    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            //printf("x = %d \n",tx);
            //printf("y = %d \n",ty);
            if (tx > 400 && tx < 600 && ty > 450 && ty < 620) {
                _ret = true;

            }
        }
    }
    return _ret;
}


bool System::EqpPressed(void)
{
    bool _ret = false;

    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            //printf("x = %d \n",tx);
            //printf("y = %d \n",ty);
            if (tx > 400 && tx < 600 && ty > 450 && ty < 620) {
                _ret = true;

            }
        }
    }
    return _ret;
}



bool System::backPressed(void)
{
    bool _ret = false;
    float xScale = 1024.0F/lcd.width();
    float yScale = 1024.0F/lcd.height();
    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            if (tx/xScale < 125 && ty/yScale < 125) {
                _ret = true;

            }
        }
    }
    return _ret;
}



bool System::boxOne(void)
{
    bool _ret = false;
    float xScale = 1024.0F/lcd.width();
    float yScale = 1024.0F/lcd.height();
    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            if ((tx/xScale > 20 && ty/yScale > 280)&&
                    ( tx/xScale < 195 && ty/yScale < 455)) {
                _ret = true;

            }
        }
    }
    return _ret;
}




bool System::boxTwo(void)
{
    bool _ret = false;
    float xScale = 1024.0F/lcd.width();
    float yScale = 1024.0F/lcd.height();
    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            //printf("x = %d \n",tx);
            //printf("y = %d \n",ty);
            if ((tx/xScale > 215 && ty/yScale > 280)&&
                    ( tx/xScale < 390 && ty/yScale < 455)) {
                _ret = true;

            }
        }
    }
    return _ret;
}



bool System::boxThree(void)
{
    bool _ret = false;
    float xScale = 1024.0F/lcd.width();
    float yScale = 1024.0F/lcd.height();
    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            if ((tx/xScale > 410 && ty/yScale > 280)&&
                    ( tx/xScale < 585 && ty/yScale < 455)) {
                _ret = true;

            }
        }
    }
    return _ret;
}




bool System::boxFour(void)
{
    //printf("button press4");
    bool _ret = false;
    float xScale = 1024.0F/lcd.width();
    float yScale = 1024.0F/lcd.height();
    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            if ((tx/xScale > 605 && ty/yScale > 280)&&
                    ( tx/xScale < 780 && ty/yScale < 455)) {
                //printf("button press4");
                _ret = true;

            }
        }
    }
    return _ret;
}



bool System::nextPressed(void)
{
    bool _ret = false;
    float xScale = 1024.0F/lcd.width();
    float yScale = 1024.0F/lcd.height();
    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            //printf("x = %d \n",tx);
            //printf("y = %d \n",ty);
            if (tx/xScale > 700 && ty/yScale < 120) {
                _ret = true;
                //printf("next");

            }
        }
    }
    return _ret;
}



bool System::previousPressed(void)
{

    bool _ret = false;
    float xScale = 1024.0F/lcd.width();
    float yScale = 1024.0F/lcd.height();
    if (INT == !1);
    {
        if (lcd.touched()) {
            lcd.touchRead(&tx, &ty);
            //printf("x = %d \n",tx);
            //printf("y = %d \n",ty);
            if (tx/xScale > 600 && tx/xScale < 700 && ty/yScale < 120) {
                _ret = true;
                //printf("previsous");
            }
        }
    }
    return _ret;
}

//////////// END OF BUTTON PRESSES ////////////////////////////////////////////////////////////////






int System::buttonPress(void)
{
    int i = 0;

    if (boxOne()) {
        i=1;
    }
    if (boxTwo()) {
        i=2;
    }

    if (boxThree()) {
        i=3;
    }

    if (boxFour()) {
        i=4;
    }

    if (EqpPressed()) {
        i=5;
    }
    return i;
}


int System::buttonPress2(void)
{
    int i = 0;

    if (backPressed()) {
        i=1;
    }
    if (nextPressed()) {
        i=2;
    }
    if (previousPressed()) {
        i=3;
    }
    return i;
}