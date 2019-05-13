#include "mbed.h"

// appEUI in little endian order(lsb first)
const uint8_t AppEUI[8] = { 0xB6, 0x99, 0x01, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };

// appKEY in little endian order (lsb first)
const uint8_t AppKey[16] ={ 0xC8, 0x8E, 0x92, 0xE2, 0x18, 0x55, 0x6A, 0x3E, 0x1C, 0x5B, 0xE1, 0xF7, 0x9A, 0xA7, 0x16, 0xEC};

class click_4{

    public:
    
        click_4(PinName, PinName, PinName, Serial*); 
        ~click_4();
        void initialize(const uint8_t*,int,const uint8_t*, int); 
        void sendData(uint8_t*,int);
        void close(); 
        
     private:
     
     //variables
     InterruptIn NDATA_INDICATE;
     Serial* ptrToSerial;
     DigitalOut NWAKE;
     DigitalOut NRESET;
     char buff[256];
     int j;
     
     //methods
     void init();  
     void getDevEui();  
     void eeprom_write_cmd(const uint8_t*, uint8_t, int); 
     void set_app_key(const uint8_t*, int);  
     void eeprom_read_cmd(uint8_t, uint8_t); 
     void set_next_dr_cmd(uint8_t);
     void reset(); 
     void join_cmd(uint8_t);  
     void tx_msg_cmd(uint8_t*, uint8_t, uint8_t, uint8_t); 
     uint8_t get_activation_status_cmd(); 
     void reset_cmd(); 
     void factory_reset_cmd();
     void send(uint8_t*,int);   
     void receive();  
     uint8_t calculateCks(uint8_t*, int);  

    };
