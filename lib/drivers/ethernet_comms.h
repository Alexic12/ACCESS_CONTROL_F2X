#ifndef _ETHERNET_COMMS_H
#define _ETHERNET_COMMS_H

#include <Arduino.h>
#include "error.h"
#include "NativeEthernet.h"
#include "reader.h"


class EthernetComms{

    public:
        typedef enum{
            ID_REQ,
            ALIVE_REQ,
            PING_REQ,
            ACCES_REQ,
            INIT_REQ

        }request_type_t;
        typedef enum{
            OK,
            NO_CONN,
            NO_ID,
            TIMEOUT

        }conn_res_t;

        static err_t conn_init();
        static err_t connect_reader();
        static err_t disconnect();
        static err_t request(request_type_t req, const char* data, bool& res);
        static err_t receive();
        static err_t send(byte* array, uint16_t dataLength);


    private:

        static uint16_t port;
        static byte mac[];



};
#endif