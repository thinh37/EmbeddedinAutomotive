/*
 * File:   main.c
 * Author: microdigisoft.com
 *
 */
#include <xc.h>
#include "config.h"
#include "LCD.h"
#define _XTAL_FREQ 20000000

#define CLK RB0
#define MOSI RB1
#define MISO RB2
#define SS RB3 

char dataTrans = 'z';
char dataTemp = 'z';
char dataReceive;
void config(){
    TRISB0 = 1;
    TRISB1 = 1;
    TRISB2 = 0;
    TRISB3 = 1;
}
void SpiSlave(){
    while(SS == 1);
    while(CLK == 0);
    char temp;
    for(int i=0;i<8;){
        if(CLK == 1){
             temp=dataTrans & (char)0x80;
             if(temp == (char)0x80){
                    MISO = 1;
             }
             else{
                    MISO = 0;
             }
             dataTrans = dataTrans <<1;
            dataReceive=dataReceive<<1;
            while(CLK==1){
                dataReceive=dataReceive | MOSI;
            }
        }
        else {
            i++;
            while(CLK==0);
        }
    }
}

int main()
{  
    LCD__Config();
    LCD_Init(0x4E);
    config();
    while(1){
    SpiSlave();
    
    LCD_Set_Cursor(1, 1);
    LCD_Write_Char(dataReceive);
    if(dataTemp== 'a')  dataTemp = 'z';
	else dataTemp--;
    dataTrans=dataTemp;
    }
    return 0;
}







  

    