#ifndef SERIAL_H
#define SERIAL_H
#include <Arduino.h>
#include "../ext_libs/printf.h"
#include "ethernet_comms.h"


class Serial_uart{

    public:
        
        static void put_c(char c, void* extra_arg);
        static int printf(Print& serial, const char* format, ...);
        static int printlnf(Print& serial, const char* format, ...);
        static void ReadSerial();
        static void InterpretSerialCMD(char* buff);


    private:
        static void handleReadTag();
        static void handleClearTagInv();
        static void handleSendTagReq();



};


#endif