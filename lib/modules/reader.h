#ifndef _READER_H
#define _READER_H

#include <Arduino.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "error.h"
#include "../drivers/ethernet_comms.h"
#include "reader_def.h"


class Reader{

    public:

        typedef enum{
            ACCESS_GRANTED,
            ACCESS_DENIED,
            ACCESS_PENDING
        }access_res_t;

        typedef enum{
            ANTENNA_1,
            ANTENNA_2,
            ANTENNA_3
        }antenna_t;
        
        static err_t send_id(antenna_t ant, unsigned char tag[], access_res_t& res);
        static uint16_t crc16(const uint8_t *data, size_t length);
        static void create_command_frame(uint8_t adr, uint8_t cmd, const uint8_t* data, size_t dataLength, uint8_t* frame);
        static void send_cmd_s(uint8_t cmd);




    private:
        static unsigned char clear_buffer[5];
        static unsigned char antena_1[12];
        static unsigned char antena_2[12];
        static unsigned char antena_3[7];


};
#endif