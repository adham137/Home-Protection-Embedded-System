#include "..\MCAL\GPIO.h"
#include "..\tm4c123gh6pm.h"
#include "..\Types.h"
#include "..\bitwise_operations.h"
#include <stdint.h>
#include "..\MCAL\gptm.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


void setup();

int calculateNumOfFlashes(const char *binaryString);
void Arduino_send_message(const char *binaryString);
void transmitFlashes(int numFlashes);