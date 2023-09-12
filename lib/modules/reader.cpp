#include "reader.h"

CONFIG_ERROR();
#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL  0x8408

//unsigned char Reader::clear_buffer[] = {0x04, 0x00, 0x73, 0x4e, 0x1b};
//unsigned char Reader::antena_1[] = {0x0b, 0x00, 0x01, 0x04, 0x00, 0x00, 0x06, 0x00, 0x80, 0x14, 0xfd, 0xfe};
//unsigned char Reader::antena_2[] = {0x0b, 0x00, 0x01, 0x04, 0x00, 0x00, 0x06, 0x00, 0x81, 0x14, 0x25, 0xe7};
//unsigned char Reader::antena_3[] = {0x53, 0x57, 0x00, 0x03, 0xFF, 0x01, 0x53};


void Reader::send_id(antenna_t ant, unsigned char tag[], access_res_t& res) {


    
}

uint16_t Reader::crc16(const uint8_t *data, size_t length) {
    uint16_t crc_value = 0xFFFF;
    const uint16_t poly = 0x8408;
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
    return crc_value; // complement the final CRC
}


uint16_t Reader::uiCrc16Cal(unsigned char const  * pucY, unsigned char ucX)
{
	unsigned char ucI,ucJ;
	unsigned short int  uiCrcValue = PRESET_VALUE;
   	for(ucI = 0; ucI < ucX; ucI++)
	   {
		   uiCrcValue = uiCrcValue ^ *(pucY + ucI);
	  	   for(ucJ = 0; ucJ < 8; ucJ++)
	   	  {
		 	if(uiCrcValue & 0x0001)
		   	{
		    	uiCrcValue = (uiCrcValue >> 1) ^ POLYNOMIAL;
		   	}
		 	else
		   	{
		    	uiCrcValue = (uiCrcValue >> 1);
		   	}
		}
 	}
    return uiCrcValue;
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
    //uint16_t crc_value = crc16(frame, len_value); 
    uint16_t crc_value = uiCrc16Cal(frame, len_value);
    Serial.print("Hex CRC: ");
    Serial.println(crc_value, HEX);
    Serial.print("Binary CRC: ");
    Serial.println(crc_value, BIN);
    uint8_t lsb_crc16 = crc_value & 0xFF;
    uint8_t msb_crc16 = (crc_value >> 8) & 0xFF;

    // Append the CRC16 values to the frame
    Serial.print("Binary LSB: ");
    Serial.println(lsb_crc16, BIN);

    Serial.print("Binary MSB: ");
    Serial.println(msb_crc16, BIN);

    frame[len_value] = lsb_crc16;
    frame[len_value+1] = msb_crc16;
}

void Reader::send_cmd_s(uint8_t cmd){
    
    uint8_t data[] = {}; // data array
    size_t dataLength = sizeof(data)/sizeof(data[0]);

    // Create frame with enough size
    uint8_t frame[dataLength + 5]; // length of data + 5 (1 for len_value, 1 for adr, 1 for cmd, 2 for CRC)
    Serial.print("DATA_LEN: 0x");
    Serial.println(dataLength, HEX);
    
    Serial.print("DEV_ADDR: 0x");
    Serial.println(DEV_ADDR, HEX);

    Serial.print("CMD: 0x");
    Serial.println(cmd, HEX);

    if(dataLength > 0){
        Serial.print("DATA: ");
    }
    for(size_t i = 0; i < dataLength; i++) {
        Serial.print("0x");
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    create_command_frame(DEV_ADDR, cmd, data, dataLength, frame);

    // Print the frame
    Serial.print("FRAME: ");
    for(size_t i = 0; i < dataLength + 5; i++) {
        Serial.print("0x");
        Serial.print(frame[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    delay(1000); // Delay for 1 second


}

void Reader::interpretStatusCode(uint8_t status_code){

    /*
    if (size < 6) {
        // The data received is less than the minimum expected size.
        Serial.println("Invalid data received");
        return;
    }

    uint8_t statusCode = data[3];  // The status code is at the fourth byte (index 3)

*/
    Serial.print("Status code response: ");
    Serial.print("0x");
    Serial.println(status_code, HEX);
    Serial.println("");
    Serial.print("Status response from reader: ");
    
    switch (status_code) {
        case OPERATION_SUCCEED:
            Serial.println("Operation Succeed");
            break;
        case INVENTORY_SUCCEED:
            Serial.println("Inventory Succeed");
            break;
        case INVENTORY_TIMEOUT:
            Serial.println("Inventory Timeout");
            break;
        case FURTHER_DATA_WAITING:
            Serial.println("Further Data Waiting");
            break;
        case READER_MEMORY_FULL:
            Serial.println("Reader Memory Full");
            break;
        case ACCESS_PASSWORD_ERROR:
            Serial.println("Access Password Error");
            break;
        case TAG_KILLING_FAILED:
            Serial.println("Tag Killing Failed");
            break;
        case ALL_ZERO_KILL_PASSWORD_FAIL:
            Serial.println("All Zero Kill Password Fail");
            break;
        case COMMAND_NOT_SUPPORTED:
            Serial.println("Command Not Supported");
            break;
        case ALL_ZERO_ACCESS_PASSWORD_FAIL:
            Serial.println("All Zero Access Password Fail");
            break;
        case READ_PROTECTION_FAILED:
            Serial.println("Read Protection Failed");
            break;
        case UNLOCK_TAG_FAILED:
            Serial.println("Unlock Tag Failed");
            break;
        case WRITE_OPERATION_FAILED:
            Serial.println("Write Operation Failed");
            break;
        case LOCK_OPERATION_FAILED_6B:
            Serial.println("Lock Operation Failed (6B)");
            break;
        case LOCK_OPERATION_FAILED_ALREADY_LOCKED:
            Serial.println("Lock Operation Failed (Already Locked)");
            break;
        case STORE_PARAMETER_FAILED:
            Serial.println("Store Parameter Failed");
            break;
        case RF_POWER_ADJUST_FAILED:
            Serial.println("RF Power Adjust Failed");
            break;
        case INVENTORY_6B_SUCCEED:
            Serial.println("Inventory (6B) Succeed");
            break;
        case INVENTORY_6B_TIMEOUT:
            Serial.println("Inventory (6B) Timeout");
            break;
        case FURTHER_DATA_6B_WAITING:
            Serial.println("Further Data (6B) Waiting");
            break;
        case READER_MEMORY_6B_FULL:
            Serial.println("Reader Memory (6B) Full");
            break;
        case ALL_ZERO_ACCESS_OR_FUNCTION_NOT_SUPPORTED:
            Serial.println("All Zero Access or Function Not Supported");
            break;
        case TAG_CUSTOMISED_COMMAND_FAILED:
            Serial.println("Tag Customised Command Failed");
            break;
        case STATISTIC_DATA_PACKET:
            Serial.println("Statistic Data Packet");
            break;
        case HEARTBEAT_PACKET:
            Serial.println("Heartbeat Packet");
            break;
        case ANTENNA_CONNECTION_FAILURE:
            Serial.println("Antenna Connection Failure");
            break;
        case COMMAND_EXECUTION_ERROR:
            Serial.println("Command Execution Error");
            break;
        case OPERATION_FAILED_POOR_COMMUNICATION:
            Serial.println("Operation Failed due to Poor Communication");
            break;
        case NO_OPERATABLE_TAGS:
            Serial.println("No Operatable Tags");
            break;
        case TAG_ERROR_CODE_RETURNED:
            Serial.println("Tag Error Code Returned");
            break;
        case COMMAND_LENGTH_ERROR:
            Serial.println("Command Length Error");
            break;
        case ILLEGAL_COMMAND:
            Serial.println("Illegal Command");
            break;
        case PARAMETER_ERROR:
            Serial.println("Parameter Error");
            break;
        default:
            Serial.println("Unknown status code");
    }



}

void Reader::interpretResponse(uint8_t* data, uint8_t size) {
        // Ensure the size is at least 19 bytes (based on your description)
        if (size < 19) {
            //Serial.println("Invalid data size.");

            // Print command confirmation
            Serial.print("Command Confirmation: 0x");
            Serial.println(data[2], HEX);

            Serial.print("Status Response: ");
            interpretStatusCode(data[3]);

            return;
        }

        // Print command confirmation
        Serial.print("Command Confirmation: 0x");
        Serial.println(data[2], HEX);

        // Interpret and print status response
        Serial.print("Status Response: ");
        interpretStatusCode(data[3]);

        // Interpret and print antenna
        Serial.print("Antenna: ");
        interpretAntenna(data[4]);

        // Print constant byte
        Serial.print("Constant Byte: 0x");
        Serial.println(data[5], HEX);

        // Extract and print EPC-ID
        Serial.print("EPC Length: ");
        Serial.println(data[6]);
        Serial.print("EPC-ID: ");
        for (int i = 7; i < 7 + data[6]; i++) {
            Serial.print("0x");
            Serial.print(data[i], HEX);
            if (i != 6 + data[6]) {
                Serial.print(" ");
            }
        }
        Serial.println();

        // Extract and print RSSI
        Serial.print("RSSI: 0x");
        Serial.println(data[7 + data[6]], HEX);
    } 


    void Reader::interpretAntenna(uint8_t antennaCode) {
        switch (antennaCode) {
            case 0x01:
                Serial.println("Antenna 1");
                break;
            case 0x02:
                Serial.println("Antenna 2");
                break;
            case 0x04:
                Serial.println("Antenna 3");
                break;
            case 0x08:
                Serial.println("Antenna 4");
                break;
            default:
                Serial.println("Unknown antenna code");
        }
    }