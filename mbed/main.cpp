#include "mbed.h"
#include "click_4.h"
#include "esp8266.h"

#define VERSION "v3.1"
#define DEFAULT_BAUD_RATE   115200

Serial *_serial;
ATCmdParser *_parser;
click_4 *c4;
esp8266 *wifi;

DigitalOut led(LED1);

int init(void);

//reset ticker
bool needReset = true;
Ticker rst_ticker;
void rst_func() {
  //reset module
    if(needReset == true)
    {
        NVIC_SystemReset();
    }
}

int main()
{  
    //print the version of the device
    printf("Device location version %s\n\r",VERSION);
    
    if(init() < 0)
    {
        printf("Error: something whent rong in init function.\n\r");
        return -1;
    }


    while(1)
    {
        led = 1;
        printf("Scan command wifi...\n\r");
        int tableIndex = wifi->scan();
        
        led = 0;
        
        uint8_t message[2];
        
        if( tableIndex < 0) // not found or a error...
        {
            message[0] = 0xFF;
            message[1] = 0xFF;
        }
        else
        {
            message[0]=location[tableIndex][0] - 48;
            message[1]=(location[tableIndex][2] - 48) + (10 * (location[tableIndex][1] - 48));
        }
        
        printf("Message for LoRa -> %d %d \n\r", message[0], message[1]);
        
        printf("send with LoRa...\n\r");
        needReset = false;
        
        //call method to initialize the click4 module and the uart
        //this method also lets the device join the lorawan network using OTAA
        c4->initialize(AppEUI, sizeof(AppEUI), AppKey, sizeof(AppKey));
        //call method to send a message to the TTN 
        c4->sendData(message, sizeof(message));
        //call method to reset lorawan module uart
        c4->close();
        
        //reset the module :/ ...
        NVIC_SystemReset();
        break;
    }
    
    return 0; //OKE
}

int init(void)
{
    //start reset ticker
    rst_ticker.attach(&rst_func, 10.0);

    
    //objects
    _serial = new Serial(D1, D0, DEFAULT_BAUD_RATE);
    c4 = new click_4(D3, D9, A2, _serial);
    wifi = new esp8266(A3, D10, _serial);
    
    if( _serial == NULL)
    {
        printf("Error: Can not link UART.\n\r");
        return -1;
    }
    
    if( c4 == NULL)
    {
        printf("ERROR: Could not link click_4.\n\r");
        return -1;
    } 
    
    if(wifi == NULL)
    {
        printf("ERROR: Could not link esp8266.\n\r");
        return -1;
    }
    
    return 0; //OKE

}