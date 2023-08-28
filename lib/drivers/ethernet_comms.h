#ifndef _ETHERNET_COMMS_H
#define _ETHERNET_COMMS_H

#include <Arduino.h>
#include "error.h"


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

        static err_t conn_init(request_type_t req);
        static err_t request(request_type_t req, uint16_t& data);


    private:



};
#endif