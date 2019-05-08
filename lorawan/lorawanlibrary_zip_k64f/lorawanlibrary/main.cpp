#include "click_4.h"
#include "mbed.h"

click_4 c4(D3,D9,D1,D0,115200, A2);

// appEUI in little endian order(lsb first)
const uint8_t AppEUI[8] = { 0xB6, 0x99, 0x01, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };

// appKEY in little endian order (lsb first)
const uint8_t AppKey[16] ={ 0xC8, 0x8E, 0x92, 0xE2, 0x18, 0x55, 0x6A, 0x3E, 0x1C, 0x5B, 0xE1, 0xF7, 0x9A, 0xA7, 0x16, 0xEC};


//main method
int main (){
    //create message to en
    uint8_t message[2];
    message[0]=0xAA;
    message[1]=0xFF;
    
    //call method to initialize the click4 module and the uart
    //this method also lets the device join the lorawan network using OTAA
    c4.initialize(AppEUI, sizeof(AppEUI), AppKey, sizeof(AppKey));
    //call method to send a message to the TTN 
    c4.sendData(message, sizeof(message));
    //call method to reset lorawan module uart
    c4.close();
    
    return 0;
} 