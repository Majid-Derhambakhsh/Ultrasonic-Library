# Ultrasonic-Library
Ultrasonic module library for any type of microcontroller

### Version : 0.0.0

- #### Type : Embedded Software.

- #### Support : Any type of microcontroller

- #### Program Language : C

- #### Properties :

### Initialization and de-initialization functions:
```c++
- None 
```  

### Operation functions:
```c++  
Ultrasonic_ScanTypeDef Ultrasonic_GetScanStatus(Ultrasonic_TypeDef *Ultrasonic);
Ultrasonic_OBJStatusTypeDef Ultrasonic_GetObjectStatus(Ultrasonic_TypeDef *Ultrasonic);
void Ultrasonic_GetDistance(Ultrasonic_TypeDef *Ultrasonic, float *DistanceCM, float *DistanceINCH);

/* ::::: ISR Handling ::::: */
void Ultrasonic_ISRHandle_Rising(Ultrasonic_TypeDef *Ultrasonic);
void Ultrasonic_ISRHandle_Falling(Ultrasonic_TypeDef *Ultrasonic);

``` 
### Macros:
```c++  
- None 
``` 

## How to use this library

### The Ultrasonic library can be used as follows:
#### 1.  Add .h and source file in project.      
#### 2.  Initialize a timer (16bit or 32bit) with 1MHz frequency and add GetTick function in 'ultrasonic_conf.h', for example:
```c++  
/* ~~~~~~~~~~~~~~~ Include files ~~~~~~~~~~~~~~~ */
/* Timer header */
#include "timer.h"

/* ~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~ Microsecond Timer ~~~~~~~~ */
#define __UltrasonicTimer_GetTick()   Timer1_GetTick()
```  
#### 3.  Initialize a External Interrupt in Rising/Falling edge mode    
#### 4.  Add ISR Handle functions in the External Interrupt Routine, for example:  
```c++  
Ultrasonic_TypeDef Sensor;

void GPIO_ISR_RisingEdge()
{
    Ultrasonic_ISRHandle_Rising(&Sensor);
}

void GPIO_ISR_FallingEdge()
{
    Ultrasonic_ISRHandle_Falling(&Sensor);
}
```  
#### 5.  Using operation methods, for example:  
#### Example 1:  
```c++  
#include <timer.h>
#include <stdio.h>
#include <ultrasonic.h>

Ultrasonic_TypeDef Sensor;

void GPIO_ISR_RisingEdge()
{
    Ultrasonic_ISRHandle_Rising(&Sensor);
}

void GPIO_ISR_FallingEdge()
{
    Ultrasonic_ISRHandle_Falling(&Sensor);
}

int main(void)
{
    float distanceCM   = 0;
    float distanceINCH = 0;
    
    char msg[20] = {0};
	
    while (1) 
    {
        Ultrasonic_GetDistance(&Sensor, &distanceCM, &distanceINCH);
        HAL_Delay(100);
	
        sprintf(msg ,"Distance:%fcm, %finch\r\n", distanceCM, distanceINCH);
        HAL_UART_Transmit(&huart6, (uint8_t *)msg, strlen(msg), 100);
    }
}
   
``` 

## Test Performed:
- [x] SRF05  
- [x] SRF04  
- [x] US-026  

#### Developer: Majid Derhambakhsh
