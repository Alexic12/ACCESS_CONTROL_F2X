#include "ethernet_comms.h"

CONFIG_ERROR();


#define MAX_BUFFER_SIZE 64
uint8_t receivedData[MAX_BUFFER_SIZE];
uint8_t receivedSize = 0;
Reader R;
EthernetClient client; // Create client instance
IPAddress ip(192, 168, 1, 177); 
IPAddress reader_ip(192, 168, 1, 65);//.9 para simulador TCP en PC .65 para reader en LAN 
uint16_t reader_port = 27011;

byte EthernetComms::mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
uint16_t EthernetComms::port = 80;


void EthernetComms::conn_init(){
    
    Ethernet.begin(mac, ip);
    delay(1000);
    Serial.println("Connected to LAN Network!");
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
    
}

void EthernetComms::connect_reader(){

     // Connect to TCP server
    if (client.connect(reader_ip, reader_port)) {
        Serial.println("Connected to reader!");
     } else {
        Serial.println("Connection to reader failed");
     }

    
    
}

void EthernetComms::disconnect(){

    
    
}

void EthernetComms::receive(){

    while(1){
            if (client.available()) {
        Serial.println("reader response available: ");

        // Clear the receivedSize for each new message
        receivedSize = 0;

        while(client.available()) {
            char c = client.read();

            // Check if buffer is not full
            if (receivedSize < MAX_BUFFER_SIZE) {
                receivedData[receivedSize++] = c;
            } else {
                Serial.println("Warning: Buffer full, some bytes might be lost!");
                break;  // exit the loop if buffer is full to prevent overflow
            }

            Serial.print("0x");
            Serial.print(c, HEX);
            Serial.print(" ");
        }
        Serial.println(" ");
        // After reading all available data, pass it to the interpreter
        R.interpretResponse(receivedData, receivedSize);
        break;
        }
    }


    
}


void EthernetComms::send(byte* array, uint16_t dataLength){

    //uint16_t dataLength = sizeof(array);
    Serial.println("Sending array to reader: ");
    for(int i = 0; i < dataLength; i++) {
        Serial.print("0x");
        Serial.print(array[i], HEX);
        Serial.print(" ");
    }
    Serial.println(" ");
    client.write(array, dataLength);
    
}

void EthernetComms::request(request_type_t req, const char* data, bool& res){
    

    
}

