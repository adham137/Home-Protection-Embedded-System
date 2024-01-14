#include "bluetooth.h"

void bluetooth_init() // Initialize UART5 module for HC-05
{
 uart_init(); 
  
}

int8 bluetooh_read()  //Read data from Rx5 pin of TM4C123
{
  int8 data;
  data = UART5_Reciever();
    return data ;
  
}

void Bluetooth_Write(uint8 data)  // Transmit a character to HC-05 over Tx5 pin 
{
  
  UART5_Transmitter(data);
  
  
}

void Bluetooth_Write_String(int8 *str) // Transmit a string to HC-05 over Tx5 pin 
{
  
  printstring(str);
  
}

void Bluetooth_Send_Message(char msg []){

  int8 str [100] = "";
  
  char m1 [] = "Fire \n";
  char m2 [] = "Door Open \n";
  char m3 [] = "Intrusion \n";
  
  // Concatenate messages
  int i = 0; // iterate on str
  int j = 0; // iterate on m1/m2/m3
  
  //    Concat m1 if necessary
  if (msg[0] == '1'){
  
    for(j=0; j<strlen(m1); j++) str[i++] = m1[j];
  }
  
  //    Concat m2
  if (msg[1] == '1'){
  
    for(j=0; j<strlen(m2); j++) str[i++] = m2[j];
  }
  
  //    Concat m3
  if (msg[2] == '1'){
  
    for(j=0; j<strlen(m3); j++) str[i++] = m3[j];
  }
  
  // Send string to bluetooth
  int8 *ptr = str;
  Bluetooth_Write_String(ptr);
  
}
