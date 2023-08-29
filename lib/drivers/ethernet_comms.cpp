#include "ethernet_comms.h"

CONFIG_ERROR();



EthernetClient client;
IPAddress server(192, 168, 1, 1);

byte EthernetComms::mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
uint16_t EthernetComms::port = 80;


err_t EthernetComms::conn_init(request_type_t req){
    
    Ethernet.begin(mac);
    NOERR();
}

err_t EthernetComms::connect(bool& res){

    res = client.connect(server, port); 
    NOERR();
}

err_t EthernetComms::disconnect(){

    client.stop();
    NOERR();
}

String EthernetComms::receive(){



}

err_t EthernetComms::request(request_type_t req, const char* data, bool& res){
    res = client.write((const uint8_t*) data, strlen(data));

    NOERR();
}

