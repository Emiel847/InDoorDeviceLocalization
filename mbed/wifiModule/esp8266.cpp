#include "esp8266.h"

esp8266::esp8266(PinName rst, PinName en, Serial* ptrSerial):_rstWifi(rst),_enWifi(en)
{
    _serial = ptrSerial;

    if( _serial != NULL)
    {
        _parser = new ATCmdParser(_serial);
        
        if(_parser != NULL)
        {
            _parser->debug_on( 0 );
            _parser->set_delimiter( "\r\n" );

            //set wifi rst pin high
            _rstWifi = 1;
        }
        else
        {
            printf("Error (esp8266): Can not link ATcmd.\n\r");
        }
    }
    else
    {
        printf("Error (esp8266): Can not link UART.\n\r");
    }
}

int esp8266::scan(void)
{
    //disable wifi module 
    this->WIFI_module(ENABLE);

    //sent AT request
    printf("Send AT command...\n\r");
    _parser->send(SSID);

    // Get chars from serial buffer with the parser...
    char buffer[BUFFER_SIZE];
    int i = 0;
    bool isOk = false;
    while(!isOk)
    {
        buffer[i] = (char)_parser->getc();
        if(buffer[i] == 'K')
        {
            isOk = true; 
        }
        i++;
    }

    //disable wifi module
    this->WIFI_module(DISABLE);

    //remove bad chars from begin of the string
    int i_find = 0;
    bool ready = false;
    char *p = buffer;
    while (ready == false)
    {
        //find start of string...
        if (buffer[i_find] == '+' && buffer[i_find+1] == 'C' && buffer[i_find+2] == 'W')
        {
            ready = true;
            i = i - i_find;
            strcpy(buffer, p + i_find);
        }
        else if(i_find >= BUFFER_SIZE)
        {
            //nothing found, continue code... nothing happend...
            ready = true; 
        }
        else
        {
            i_find++;
        }
    }

    //split the buffer
    int size = 0;
    tokens = so.split(buffer, ',', &size);

    //find the best AP by signal strength
    int max = -1000;
    int AP = 0;
    if(tokens != NULL)
    {
        for (int k = 0; k < (size-1)/6; k++)
        {
            int tempSignal = so.ConvertToInt(tokens[2 + (6*k)]);
            if(max < tempSignal)
            {
                max = tempSignal;
                AP = k;
            }
        }
    }

    if(max != -1000)
    {
        so.removeChar(tokens[3 + (6*AP)],'"');
        printf("=> %d mdB, MAC: %s\n\r", max,tokens[3 + (6*AP)]);
        for(int device = 0; device < NUMBER_OF_MACS; device++)
        {
            //find the location of the AP
            if(strcmp(macs[device],tokens[3 + (6*AP)]) == 0)
            {
                printf("Location ID: %s\n\r",location[device]);

                //importent => free() tokens!
                // first free each row
                for(int x = 0; x < size; x++)
                {
                    free(tokens[x]);
                }
                // second free the top
                free(tokens);
                // return index of table...
                return device;
            }
        }
        
        //////
        //at this point no device where found... 
        //////
        //importent => free() tokens!
        // first free each row
        for(int x = 0; x < size; x++)
        {
            free(tokens[x]);
        }
        // second free the top
        free(tokens);
        return -1;
    }


}

void esp8266::WIFI_module(bool isEnable)
{
    if(isEnable)
    {
        _enWifi = 1;
        printf("waiting for wifi ready...\n");
        wait(delay_time);
        printf("wifi is ready...\n");
    }
    else
    {
        _enWifi = 0;
    } 
}