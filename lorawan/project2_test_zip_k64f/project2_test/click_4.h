#include "mbed.h"

class click_4{
    
   
     
    public:
        click_4(PinName, PinName, PinName, PinName, int, PinName);
        ~click_4();
        void init();
        void close();
        void getDevEui();
        void setReceive();
        void eeprom_write_cmd(const uint8_t*, uint8_t, int);
        void set_app_key(const uint8_t*, int);
        
        
        /*
        *methods to make
        *join_cmd    3
        *join_ind    4
        *(eeprom read cmd?)
        *tx msg cmd
        */
        
     private:
     InterruptIn NDATA_INDICATE;
     Serial myuart;
     DigitalOut NWAKE;
     DigitalOut NRESET;
     bool RCV;
    };
