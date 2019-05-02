#include "mbed.h"

class click_4{

    public:
        click_4(PinName, PinName, PinName, PinName, int, PinName);  //ok
        ~click_4();
        void init();  //ok
        void close(); //ok
        void getDevEui();  //ok 
        void eeprom_write_cmd(const uint8_t*, uint8_t, int); // ok?
        void set_app_key(const uint8_t*, int);  //ok
        void eeprom_read_cmd(uint8_t, uint8_t); //ok
        void set_next_dr_cmd(uint8_t); //ok 
        void reset();  //ok
        void join_cmd(uint8_t);  //ok
        void tx_msg_cmd(uint8_t*, uint8_t, uint8_t, uint8_t); //to test
      
        
     private:
     InterruptIn NDATA_INDICATE;
     Serial myuart;
     DigitalOut NWAKE;
     DigitalOut NRESET;
     char buff[256];
     int j;
     void send(uint8_t*,int);   //ok
     void receive();  //ok
     uint8_t calculateCks(uint8_t*, int);  //ok
     void reset_cmd();//to test
     void factory_reset_cmd();//to test
    };
