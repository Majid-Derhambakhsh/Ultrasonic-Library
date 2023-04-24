/*
------------------------------------------------------------------------------
~ File   : ultrasonic.h
~ Author : Majid Derhambakhsh
~ Version: V0.0.0
~ Created: 12/20/2021 09:00:00 AM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    

~ Changes    :    
                  
------------------------------------------------------------------------------
*/

#ifndef __ULTRASONIC_H_
#define __ULTRASONIC_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>

#include "ultrasonic_conf.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ----------------------------- Time ----------------------------- */
/* ..... Microsecond ..... */
#define ULTRASONIC_ECHO_RANGE_TIME_MAX_US    18000UL
#define ULTRASONIC_ECHO_NOT_DETECTED_TIME_US 35000UL

/* ---------------------------- Public ---------------------------- */
/* ---------------------- Define by compiler ---------------------- */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef enum // Scan Status TypeDef
{
	
	ULTRASONIC_SCAN_STARTED = 0,
	ULTRASONIC_SCAN_ENDED   = 1
	
}Ultrasonic_ScanTypeDef;

typedef enum // Object Detection Status TypeDef
{
	
	ULTRASONIC_OBJ_NOT_DETECTED = 0,
	ULTRASONIC_OBJ_DETECTED     = 1
	
}Ultrasonic_OBJStatusTypeDef;

typedef struct /* Ultrasonic Type */
{
	
	struct
	{
		
		uint16_t EchoPulseStartTick;
		uint16_t EchoPulseEndTick;
		uint16_t EchoPulseTime;
		
	}SignalData;
	
	volatile Ultrasonic_ScanTypeDef      ScanEnded;
	volatile Ultrasonic_OBJStatusTypeDef ObjectDetected;
	
	float DistanceCM;
	float DistanceINCH;
	
}Ultrasonic_TypeDef;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
 * Function: Ultrasonic_GetScanStatus
 * ---------------------------
 * Get scan status of ultrasonic
 *
 * Param  : 
 *         Ultrasonic  : Pointer to Ultrasonic module type
 *         
 * Returns: 
 *         Scan Status : ULTRASONIC_SCAN_STARTED/ULTRASONIC_SCAN_ENDED
 *         
 * Example: 
 *         Ultrasonic_ScanTypeDef Status;
 *
 *         Ultrasonic_TypeDef Sensor;
 *
 *         Status = Ultrasonic_GetScanStatus(&Sensor);
 *         ...
 *         
 */
Ultrasonic_ScanTypeDef Ultrasonic_GetScanStatus(Ultrasonic_TypeDef *Ultrasonic);

/*
 * Function: Ultrasonic_GetObjectStatus
 * ---------------------------
 * Get scan status of ultrasonic
 *
 * Param  : 
 *         Ultrasonic  : Pointer to Ultrasonic module type
 *         
 * Returns: 
 *         Scan Status : ULTRASONIC_OBJ_NOT_DETECTED/ULTRASONIC_OBJ_DETECTED
 *         
 * Example: 
 *         Ultrasonic_OBJStatusTypeDef ObjectStatus;
 *
 *         Ultrasonic_TypeDef Sensor;
 *
 *         ObjectStatus = Ultrasonic_GetObjectStatus(&Sensor);
 *         ...
 *         
 */
Ultrasonic_OBJStatusTypeDef Ultrasonic_GetObjectStatus(Ultrasonic_TypeDef *Ultrasonic);

/*
 * Function: Ultrasonic_GetDistance
 * ---------------------------
 * Get distance in CM/INCH
 *
 * Param  : 
 *         Ultrasonic  : Pointer to Ultrasonic module type
 *         DistanceCM  : Pointer to get CM Distance
 *         DistanceINCH: Pointer to get INCH Distance
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         float distanceCM   = 0;
 *         float distanceINCH = 0;
 *
 *         Ultrasonic_TypeDef Sensor;
 *
 *         Ultrasonic_GetDistance(&Sensor, &distanceCM, &distanceINCH);
 *         ...
 *         
 */
void Ultrasonic_GetDistance(Ultrasonic_TypeDef *Ultrasonic, float *DistanceCM, float *DistanceINCH);

/* ::::: ISR Handling ::::: */
/*
 * Function: Ultrasonic_ISRHandle_Rising
 * ------------------------------
 * Handling received signal on rising edge
 *
 * Param  : 
 *         Ultrasonic: Pointer to Ultrasonic module type
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         Ultrasonic_TypeDef Sensor;
 *
 *         void GPIO_ISR_RisingEdge()
 *         {
 *           Ultrasonic_ISRHandle_Rising(&Sensor);
 *           ...
 *         }
 *         ...
 *         
 */
void Ultrasonic_ISRHandle_Rising(Ultrasonic_TypeDef *Ultrasonic);

/*
 * Function: Ultrasonic_ISRHandle_Falling
 * -------------------------------
 * Handling received signal on falling edge
 *
 * Param  : 
 *         Ultrasonic: Pointer to Ultrasonic module type
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         Ultrasonic_TypeDef Sensor;
 *
 *         void GPIO_ISR_FallingEdge()
 *         {
 *           Ultrasonic_ISRHandle_Falling(&Sensor);
 *           ...
 *         }
 *         ...
 *         
 */
void Ultrasonic_ISRHandle_Falling(Ultrasonic_TypeDef *Ultrasonic);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __ULTRASONIC_H_ */
