#ifndef _ETHERNET_COMMS_H
#define _ETHERNET_COMMS_H

#include <Arduino.h>
#include "error.h"
#include "NativeEthernet.h"
#include "../modules/reader.h"



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

        static void conn_init();
        static void connect_reader();
        static void disconnect();
        static void request(request_type_t req, const char* data, bool& res);
        static void receive();
        static void send(byte* array, uint16_t dataLength);


    private:

        static uint16_t port;
        static byte mac[];



};
#endif