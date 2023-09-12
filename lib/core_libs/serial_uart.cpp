#include "serial_uart.h"

EthernetComms ET;

void Serial_uart::put_c(char c, void* extra_arg) {
    ((Print*)extra_arg)->print(c);
}


int Serial_uart::printf(Print& serial, const char* format, ...) {
    va_list va;
    va_start(va, format);
    const int ret = vfctprintf(put_c, &serial, format, va);
    return ret;
}

int Serial_uart::printlnf(Print& serial, const char* format, ...) {
    va_list va;
    va_start(va, format);
    const int ret = vfctprintf(put_c, &serial, format, va);
    serial.println();
    return ret;
}


void Serial_uart::ReadSerial(){
    uint8_t index = 0;
    char buff[100];
    if(Serial.available()>0){
        while(Serial.available()>0){
            char c = Serial.read();
            if(c != '\n'){
                buff[index] = c;
                index++;

            }else if(c == '\n'){
                buff[index] = '\0';
                index = 0;
                InterpretSerialCMD(buff);
            }


        }
    }




}

void Serial_uart::InterpretSerialCMD(char* buff){
    // Assuming buff contains a valid C-style string terminated by '\0'

    // If the command is "READ_TAG"
    if (strcmp(buff, "READ_TAG") == 0) {
        // Implement the action for the READ_TAG command


        handleReadTag();
    } 
    // If the command is "CLEAR_TAG_INV"
    else if (strcmp(buff, "CLEAR_TAG_INV") == 0) {
        // Implement the action for the CLEAR_TAG_INV command
        handleClearTagInv();
    } 
    // If the command is "SEND_TAG_REQ"
    else if (strcmp(buff, "SEND_TAG_REQ") == 0) {
        // Implement the action for the SEND_TAG_REQ command
        handleSendTagReq();
    } 
    else {
        // If the received command is not recognized, you can print an error or handle it appropriately
        Serial.println("Unrecognized command.");
    }



}

void Serial_uart::handleReadTag() {
    // Implementation for the READ_TAG command
    Serial.println("Executing READ_TAG command.");
    // Your actual handling code here...
    Serial.print("Array size");
    byte read_all[] = {0x04, 0x00, 0x0f, 0xa5, 0xa2};
    Serial.println(sizeof(read_all));
    ET.send(read_all, sizeof(read_all));
    ET.receive();
    
}

void Serial_uart::handleClearTagInv() {
    // Implementation for the CLEAR_TAG_INV command
    Serial.println("Executing CLEAR_TAG_INV command.");
    // Your actual handling code here...
}

void Serial_uart::handleSendTagReq() {
    // Implementation for the SEND_TAG_REQ command
    Serial.println("Executing SEND_TAG_REQ command.");
    // Your actual handling code here...
}



