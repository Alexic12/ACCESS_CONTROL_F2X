#ifndef _READER_H
#define _READER_H

#include <Arduino.h>
#include "error.h"
#include "ethernet_comms.h"


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





    private:
        static unsigned char clear_buffer[5];
        static unsigned char antena_1[12];
        static unsigned char antena_2[12];
        static unsigned char antena_3[7];


};
#endif