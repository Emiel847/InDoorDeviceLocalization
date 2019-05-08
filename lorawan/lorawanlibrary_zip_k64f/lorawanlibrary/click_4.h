#include "mbed.h"

class click_4{

    public:
    
        click_4(PinName, PinName, PinName, PinName, int, PinName); 
        ~click_4();
        void initialize(const uint8_t*,int,const uint8_t*, int); 
        void sendData(uint8_t*,int);
        void close(); 
        
     private:
     
     //variables
     InterruptIn NDATA_INDICATE;
     Serial myuart;
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
