#ifndef SimpleModbusSlave_H
#define SimpleModbusSlave_H

#include "mbed.h"

#define TX PTC4
#define RX PTC3
#define UTX USBTX
#define URX USBRX

#define BUFFER_SIZE 128

class Slave {
    
    public:
    
    Slave(): MBPort(TX, RX), pc(UTX, URX) {}; //PTC17 and PTC16 {};
    
    ~Slave() {};
    
    
    void modbus_configure(long _baud, unsigned int _slaveID, unsigned int _holdingRegsSize, unsigned char _lowLatency);
    unsigned int modbus_update(unsigned int *holdingRegs);
    unsigned int calculateCRC(unsigned char bufferSize); 
    void flushSerialBuffer(void);
    void sendPacket(unsigned char bufferSize);
    void exceptionResponse(unsigned char exception);
    
    
    // frame[] is used to recieve and transmit packages. 
    // The maximum serial ring buffer size is 128
    unsigned char frame[BUFFER_SIZE];
    unsigned int holdingRegsSize; // size of the register array 
    unsigned char broadcastFlag;
    unsigned char slaveID;
    unsigned int baud;
    unsigned char function;
    unsigned int errorCount;
    unsigned int T1_5; // inter character time out
    unsigned int T3_5; // frame delay
    unsigned int crc;
    
    
    
    
    private:
    
    Serial MBPort;
    Serial pc;

    
    
    
};

#endif 