#include "SimpleModbusSlave.h"

//----------- Enable pin -------------------------
DigitalOut   TxEnablePin(PTB9);



//----------- FUNCTION TO CONFIGURE THE TYPE OF MODBUS CONNECTION ------------//

void Slave::modbus_configure(long _baud, unsigned int _slaveID, unsigned int _holdingRegsSize, unsigned char _lowLatency)
{
    slaveID = _slaveID;
    baud = _baud;
    MBPort.baud(baud);
    TxEnablePin = 0;
    pc.printf("baud == %d\n", baud);
    pc.printf("Slave ID == %d\n", slaveID);


    // Modbus states that a baud rate higher than 19200 must use a fixed 750 us
    // for inter character time out and 1.75 ms for a frame delay.
    // For baud rates below 19200 the timeing is more critical and has to be calculated.
    // E.g. 9600 baud in a 10 bit packet is 960 characters per second
    // In milliseconds this will be 960characters per 1000ms. So for 1 character
    // 1000ms/960characters is 1.04167ms per character and finaly modbus states an
    // intercharacter must be 1.5T or 1.5 times longer than a normal character and thus
    // 1.5T = 1.04167ms * 1.5 = 1.5625ms. A frame delay is 3.5T.
    // Added experimental low latency delays. This makes the implementation
    // non-standard but practically it works with all major modbus master implementations.


    if (baud > 19200) {
        T1_5 = 750;
        T3_5 = 1750;
    } else {
        T1_5 = 15000000/baud; // 1T * 1.5 = T1.5
        T3_5 = 35000000/baud; // 1T * 3.5 = T3.5
    }


    holdingRegsSize = _holdingRegsSize - 1; //minus the error register
    pc.printf("Holding reg size == %d\n", holdingRegsSize);

    errorCount = 0; // initialize errorCount
}


//------------------ FUNCTION TO READ ANY INCOMING PACKETS -----------------//

unsigned int Slave::modbus_update(unsigned int *holdingRegs)
{
    unsigned char buffer = 0;
    unsigned char overflow = 0;
    //flushSerialBuffer();
    
    if (MBPort.readable()) { // is there something to check?
        unsigned char overflowFlag = 0;
        buffer = 0;

        while (MBPort.readable()) {
            if (overflowFlag)
                MBPort.getc();
            else {
                if (buffer == BUFFER_SIZE)
                    overflowFlag = 1;

                frame[buffer] = MBPort.getc();
                buffer++;
            }
            wait_us(1140); //1718us intercharacter for MODPOLL //1140us for PLC
        }
        
        
        
         //Code for FUNCTION 3----------------------
        /*
        if (frame[0] == 16 || 4) {
            for (int i =buffer; i>=2; i--) {
            frame[i] = frame[i-1]; // shifts the array values to the right by 1
        }
            frame[0] = 1;
            frame[1] = 16;
        }
        */
             //-----------------------------------
        
        //if (frame[0] == 1 && frame[1] == 16) {
            
        
        for (unsigned char i = 0; i < buffer; i++) {
            //pc.printf("Frame == %d\n", frame[i]);
        }
        if (overflow)
            return errorCount++;

        // The minimum request packet is 8 bytes for function 3 & 16
        if (buffer > 6) {
            unsigned char id = frame[0];
            //pc.printf("ID recieved == %d\n", id);
            //pc.printf("MBED ID == %d\n", slaveID);

            broadcastFlag = 0;

            if (id == 0)
                broadcastFlag = 1;

            if (id == slaveID || broadcastFlag) { // if the recieved ID matches the slaveID or broadcasting id (0), continue
                //pc.printf("ID matched\n");
                unsigned int crc = ((frame[buffer - 2] << 8) | frame[buffer - 1]); // combine the crc Low & High bytes
                if (calculateCRC(buffer - 2) == crc) { // if the calculated crc matches the recieved crc continue
                    pc.printf("CRC correct\n");
                    function = frame[1];
                    unsigned int startingAddress = ((frame[2] << 8) | frame[3]); // combine the starting address bytes
                    unsigned int no_of_registers = ((frame[4] << 8) | frame[5]); // combine the number of register bytes
                    unsigned int maxData = startingAddress + no_of_registers;
                    unsigned char index;
                    unsigned char address;
                    unsigned int crc16;

                    //pc.printf("Starting Address == %d\n", startingAddress);
                    //pc.printf("Holding Regs Size == %d\n", holdingRegsSize);

                    // broadcasting is not supported for function 3
                    if (!broadcastFlag && (function == 3)) {
                        //pc.printf("Function 3 attempt\n");
                        if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS
                            if (maxData <= holdingRegsSize) { // check exception 3 ILLEGAL DATA VALUE
                                unsigned char noOfBytes = no_of_registers * 2;
                                unsigned char responseFrameSize = 5 + noOfBytes; // ID, function, noOfBytes, (dataLo + dataHi) * number of registers, crcLo, crcHi
                                frame[0] = slaveID;
                                frame[1] = function;
                                frame[2] = noOfBytes;
                                address = 3; // PDU starts at the 4th byte
                                unsigned int temp;

                                for (index = startingAddress; index < maxData; index++) {
                                    temp = holdingRegs[index];
                                    frame[address] = temp >> 8; // split the register into 2 bytes
                                    address++;
                                    frame[address] = temp & 0xFF;
                                    address++;
                                }

                                crc16 = calculateCRC(responseFrameSize - 2);
                                frame[responseFrameSize - 2] = crc16 >> 8; // split crc into 2 bytes
                                frame[responseFrameSize - 1] = crc16 & 0xFF;
                                sendPacket(responseFrameSize);
                                //pc.printf("responseFrameSize == %d\n", responseFrameSize);
                                pc.printf("Function 3 packet attempt done\n");
                            } else {
                                exceptionResponse(3); // exception 3 ILLEGAL DATA VALUE
                                pc.printf("Illegal data value\n");
                            }
                        } else {
                            exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
                            pc.printf("Illegal data address\n");
                        }
                    } else if (function == 6) {
                        if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS
                            unsigned int startingAddress = ((frame[2] << 8) | frame[3]);
                            unsigned int regStatus = ((frame[4] << 8) | frame[5]);
                            unsigned char responseFrameSize = 8;

                            holdingRegs[startingAddress] = regStatus;

                            crc16 = calculateCRC(responseFrameSize - 2);
                            frame[responseFrameSize - 2] = crc16 >> 8; // split crc into 2 bytes
                            frame[responseFrameSize - 1] = crc16 & 0xFF;
                            sendPacket(responseFrameSize);
                        } else {
                            exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
                            pc.printf("Illegal data address\n");
                        }
                    } else if (function == 16) {
                        // check if the recieved number of bytes matches the calculated bytes minus the request bytes
                        // id + function + (2 * address bytes) + (2 * no of register bytes) + byte count + (2 * CRC bytes) = 9 bytes
                        if (frame[6] == (buffer - 9)) {
                            if (startingAddress < holdingRegsSize) { // check exception 2 ILLEGAL DATA ADDRESS
                                if (maxData <= holdingRegsSize) { // check exception 3 ILLEGAL DATA VALUE
                                    address = 7; // start at the 8th byte in the frame

                                    for (index = startingAddress; index < maxData; index++) {
                                        holdingRegs[index] = ((frame[address] << 8) | frame[address + 1]);
                                        address += 2;
                                    }

                                    // only the first 6 bytes are used for CRC calculation
                                    crc16 = calculateCRC(6);
                                    frame[6] = crc16 >> 8; // split crc into 2 bytes
                                    frame[7] = crc16 & 0xFF;

                                    // a function 16 response is an echo of the first 6 bytes from the request + 2 crc bytes
                                    if (!broadcastFlag) // don't respond if it's a broadcast message
                                        sendPacket(8);
                                } else
                                    exceptionResponse(3); // exception 3 ILLEGAL DATA VALUE
                            } else
                                exceptionResponse(2); // exception 2 ILLEGAL DATA ADDRESS
                        } else {
                            errorCount++; // corrupted packet
                            pc.printf("Corrupted packet\n");
                            //flushSerialBuffer();
                            //wait_us(T3_5);
                        }
                    } else
                        exceptionResponse(1); // exception 1 ILLEGAL FUNCTION
                } else { // checksum failed
                    errorCount++;
                    //pc.printf("Checksum failed\n");
                    //flushSerialBuffer();
                    //wait_us(T3_5);
                }
            } // incorrect id
        } else if (buffer > 0 && buffer < 8) {
            errorCount++; // corrupted packet
            pc.printf("Corrupted packet 2\n");
            //flushSerialBuffer();
            //wait_us(T3_5);
        }

        return errorCount;
    }
    //flushSerialBuffer();
    //wait_us(4010);
}
//}





//------------- FUCNTION FOR ERROR CHECKING ------------------//

unsigned int Slave::calculateCRC(unsigned char bufferSize)
{
    unsigned int temp, temp2, flag;
    temp = 0xFFFF;
    for (unsigned char i = 0; i < bufferSize; i++) {
        temp = temp ^ frame[i];
        for (unsigned char j = 1; j <= 8; j++) {
            flag = temp & 0x0001;
            temp >>= 1;
            if (flag)
                temp ^= 0xA001;
        }
    }
    // Reverse byte order.
    temp2 = temp >> 8;
    temp = (temp << 8) | temp2;
    temp &= 0xFFFF;
    return temp; // the returned value is already swopped - crcLo byte is first & crcHi byte is last
}



//---------- FUNCTION TO FLUSH THE BUFFER ---------------//

void Slave::flushSerialBuffer(void)
{
    char char1 = 0;
    while (MBPort.readable()) {
        char1 = MBPort.getc();
    }
    //wait_us(4010);
    return;
}



//----------------- FUNCTION TO SEND A PACKET ---------------//

void Slave::sendPacket(unsigned char bufferSize)
{
    //pc.printf("Packet Attempt\n");
    TxEnablePin = 1;

    for (unsigned char i = 0; i < bufferSize; i++) {
        MBPort.putc(frame[i]);
        wait_us(1718); //1718us intercharacter
    }
    //flushSerialBuffer();
    flushSerialBuffer();
    // allow a frame delay to indicate end of transmission
    wait_us(3990); //4010us
    TxEnablePin = 0;
    //for (unsigned char i = 0; i < bufferSize; i++) {
            //pc.printf("Frame == %d\n", frame[i]);
      //  }
    //wait_ms(100);
    
    
    
}






void Slave::exceptionResponse(unsigned char exception)
{
    errorCount++; // each call to exceptionResponse() will increment the errorCount
    if (!broadcastFlag) { // don't respond if its a broadcast message
        frame[0] = slaveID;
        frame[1] = (function | 0x80); // set the MSB bit high, informs the master of an exception
        frame[2] = exception;
        unsigned int crc16 = calculateCRC(3); // ID, function + 0x80, exception code == 3 bytes
        frame[3] = crc16 >> 8;
        frame[4] = crc16 & 0xFF;
        sendPacket(5); // exception response is always 5 bytes ID, function + 0x80, exception code, 2 bytes crc
    }
}






