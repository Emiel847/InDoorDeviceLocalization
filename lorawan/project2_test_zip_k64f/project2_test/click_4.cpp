#include "mbed.h"
#include "click_4.h"



void click_4::setReceive(){
    RCV=true;
};

/*
*constructor 
*/
click_4::click_4(PinName Indicate, PinName wake, PinName tx, PinName rx, int baudRate, PinName reset ):NDATA_INDICATE(Indicate),NWAKE(wake),myuart(tx,rx,baudRate),NRESET(reset){ 
    NDATA_INDICATE.fall(this,&click_4::setReceive);
    RCV=false;
    NWAKE.write(1);
}


/*
*deconstructor
*/
click_4::~click_4(){}



/*
* method to start a session
* this method resets the device and sets the baud rate 
*/
void click_4:: init(){
    
    //set NRST to o to reset 
    NRESET.write(0);
    wait(0.5);
    //set reset back to 1
    NRESET.write(1);
    wait(2);
    
    //call method to set the baud rate
    myuart.baud(115200);
    printf("BaudRate has been set.\r\n");
    
    }


/*
*method to get the EUI of the device: (needed for the loraWan communication)
*/
void click_4::getDevEui(){
    //declare local variables
    char bufferToSend[4];
    int j = 0;  
    char buff[256];
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x36;
    bufferToSend[2]=0x00;
    bufferToSend[3]=0x20; 
    NWAKE.write(0);
    //send
    for(int i=0; i<sizeof(bufferToSend); i++ ){
        myuart.putc(bufferToSend[i]);
    }
    //receive the eui back
     while(NDATA_INDICATE.read());
     while(!NDATA_INDICATE.read()){
         buff[j++] = myuart.getc();
     }
    NWAKE.write(1);
    int temp = j;
    while(j){
        printf("%x\r\n",buff[temp-(j--)]);
    }
    
   
}

void click_4::eeprom_write_cmd(const uint8_t* ptrToData ,uint8_t startAdress, int dataSize){
    //declare local variables
    uint8_t bufferToSend[5+dataSize];
    uint8_t buff[256];
    int sum;
    int k=0;
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x32;
    bufferToSend[2]=(uint8_t)(1+dataSize);
    bufferToSend[3]=0x08;
    for (int i=4; i<4+dataSize; i++){
            bufferToSend[i]= (uint8_t) *(ptrToData+i-4);
        }
    for(int j=0; j<4+dataSize; j++){
        sum=sum+bufferToSend[j];
        }
    printf("cksum: %x\r\n",(uint8_t)-sum);
    bufferToSend[4+dataSize]=(uint8_t)-sum;
    
    NWAKE.write(0);

    //send
    for(int i=0; i<sizeof(bufferToSend); i++ ){
        myuart.putc(bufferToSend[i]);
    }
    
    while(NDATA_INDICATE.read());
    while(!NDATA_INDICATE.read()){
         buff[k++] = myuart.getc();
     }
    NWAKE.write(1);
    int temp = k;
    /*while(k){
        printf("%x\r\n",buff[temp-(k--)]);
    }*/
    }

void click_4::set_app_key(const uint8_t* ptrToData , int dataSize){
    //declare local variables
    uint8_t bufferToSend[4+dataSize];
    uint8_t buff[256];
    int sum;
    int k=0;
    
    bufferToSend[0]=0xAA;
    bufferToSend[1]=0x43;
    bufferToSend[2]=0x10;
    for (int i=3; i<3+dataSize; i++){
            bufferToSend[i]= (uint8_t) *(ptrToData+i-3);
        }
    for(int j=0; j<3+dataSize; j++){
        sum=sum+bufferToSend[j];
        }
    printf("cksum: %x\r\n",(uint8_t)-sum);
    bufferToSend[3+dataSize]=(uint8_t)-sum;
    
    NWAKE.write(0);

    //send
    for(int i=0; i<sizeof(bufferToSend); i++ ){
        myuart.putc(bufferToSend[i]);
    }
    
    while(NDATA_INDICATE.read());
    while(!NDATA_INDICATE.read()){
         buff[k++] = myuart.getc();
     }
    NWAKE.write(1);
    int temp = k;
    while(k){
        printf("%x\r\n",buff[temp-(k--)]);
    }
    }
    
/*
* method to end a session
*/
void click_4::close(){
    NWAKE.write(1);
    printf("End of session, NWAKE is set to 1\r\n");
    }