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
    
    uint8_t message[2];
    message[0]=0x01;
    message[1]=0x02;
    
    
    //call method to reste the module
    c4.reset();
    
    //call method to start a session
    c4.init();
  
    //call method to ge the deveui (needed to input into the things network
    //needed to get the dev eui
    //no need to call this anymore
    //c4.getDevEui();
    
    //call method to write the application eui into the eeprom
    //method can't be used anymore when the device has joined the network (needs to be done before the join command)
    ///so shouldn't be called anymore, can still be called but module won't giv an answer back
    //c4.eeprom_write_cmd(AppEUI,0x08,sizeof(AppEUI));
    
    //call method to read from the eeprom, not needed unless you want to check if the app eui is written correctly in the eeprom
    //c4.eeprom_read_cmd(0x08,8); 
    
    //call method to set the application key
    //c4.set_app_key(AppKey,sizeof(AppKey));
    
    //call method to set the next data rate
    //c4.set_next_dr_cmd(5);
    
    //call method to join the network
    //c4.join_cmd(1);
    
    //call method to send a message
    //which port needs to be used??????
    //c4.tx_msg_cmd(message, sizeof(message),0x01,223);
    
    //call method to end a session
    c4.close();
    return 0;
} 