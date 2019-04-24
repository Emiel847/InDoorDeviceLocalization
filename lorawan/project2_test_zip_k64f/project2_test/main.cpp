#include "click_4.h"
#include "mbed.h"
/*int sizeOfFrame=5;  //size of frame in bytes

uint8_t tx_buffer[sizeOfFrame];
uint8_t rx_buffer[sizeOfFrame];*/

click_4 c4(D3,D9,D1,D0,115200, A2);

// appEUI in little endian order(lsb first)
const uint8_t AppEUI[8] = {0xAB, 0xB1, 0x01, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };

// appKEY in little endian order (lsb first)
const uint8_t AppKey[16] ={0xAD, 0x90, 0xBC, 0xD3, 0xCC, 0x78, 0xE3, 0x3F, 0x1B, 0x07, 0x56, 0xD5, 0x78, 0x7A, 0x56, 0x07 };

//main method
int main (){
    //call method to start a session
    c4.init();
  
    //call other functions needed to setup the communication and sent the message
    //c4.getDevEui();
    
    //c4.eeprom_write_cmd(AppEUI,0x08,sizeof(AppEUI));
    
    c4.set_app_key(AppKey,sizeof(AppKey));
    
    //call method to end a session
    c4.close();
    return 0;
} 