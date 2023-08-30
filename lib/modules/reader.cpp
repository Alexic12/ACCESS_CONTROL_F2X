#include "reader.h"

CONFIG_ERROR();

//unsigned char Reader::clear_buffer[] = {0x04, 0x00, 0x73, 0x4e, 0x1b};
//unsigned char Reader::antena_1[] = {0x0b, 0x00, 0x01, 0x04, 0x00, 0x00, 0x06, 0x00, 0x80, 0x14, 0xfd, 0xfe};
//unsigned char Reader::antena_2[] = {0x0b, 0x00, 0x01, 0x04, 0x00, 0x00, 0x06, 0x00, 0x81, 0x14, 0x25, 0xe7};
//unsigned char Reader::antena_3[] = {0x53, 0x57, 0x00, 0x03, 0xFF, 0x01, 0x53};


err_t Reader::send_id(antenna_t ant, unsigned char tag[], access_res_t& res) {


    NOERR();
}

uint16_t Reader::crc16(const uint8_t *data, size_t length) {
    uint16_t crc_value = 0xFFFF;
    uint16_t poly = 0x8408;
    for(size_t i = 0; i < length; i++) {
        crc_value = crc_value ^ data[i];
        for(uint8_t j = 0; j < 8; j++) {
            if (crc_value & 0x0001) {
                crc_value = (crc_value >> 1) ^ poly;
            } else {
                crc_value = crc_value >> 1;
            }
        }
    }
    return ~crc_value; // complement the final CRC
}


void Reader::create_command_frame(uint8_t adr, uint8_t cmd, const uint8_t* data, size_t dataLength, uint8_t* frame) {
    // Calculate the Len value
    uint8_t len_value = dataLength + 4;

    // Create the command frame
    frame[0] = len_value;
    frame[1] = adr;
    frame[2] = cmd;
    memcpy(&frame[3], data, dataLength);

    // Calculate the CRC16 value
    uint16_t crc_value = crc16(frame, len_value);
    uint8_t lsb_crc16 = crc_value & 0xFF;
    uint8_t msb_crc16 = (crc_value >> 8) & 0xFF;

    // Append the CRC16 values to the frame
    frame[len_value] = lsb_crc16;
    frame[len_value+1] = msb_crc16;
}

void Reader::send_cmd_s(uint8_t cmd){
    
    uint8_t data[] = {}; // data array
    size_t dataLength = sizeof(data)/sizeof(data[0]);

    // Create frame with enough size
    uint8_t frame[dataLength + 5]; // length of data + 5 (1 for len_value, 1 for adr, 1 for cmd, 2 for CRC)
    create_command_frame(DEV_ADDR, cmd, data, dataLength, frame);

    // Print the frame
    for(int i = 0; i < dataLength + 5; i++) {
        Serial.print(frame[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    delay(1000); // Delay for 1 second


}
