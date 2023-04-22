/*
------------------------------------------------------------------------------
~ File   : ultrasonic.c
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

#include "ultrasonic.h"

/* ~~~~~~~~~~~~~~~~~~~~~ Global variables ~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~ */
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
Ultrasonic_ScanTypeDef Ultrasonic_GetScanStatus(Ultrasonic_TypeDef *Ultrasonic)
{
	return Ultrasonic->ScanEnded;
}

/*
 * Function: Ultrasonic_OBJStatusTypeDef
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
Ultrasonic_OBJStatusTypeDef Ultrasonic_GetObjectStatus(Ultrasonic_TypeDef *Ultrasonic)
{
	return Ultrasonic->ObjectDetected;
}

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
void Ultrasonic_GetDistance(Ultrasonic_TypeDef *Ultrasonic, float *DistanceCM, float *DistanceINCH)
{
	*DistanceCM   = Ultrasonic->DistanceCM;
	*DistanceINCH = Ultrasonic->DistanceINCH;
}

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
void Ultrasonic_ISRHandle_Rising(Ultrasonic_TypeDef *Ultrasonic)
{
	Ultrasonic->SignalData.EchoPulseStartTick = __UltrasonicTimer_GetTick();
}

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
void Ultrasonic_ISRHandle_Falling(Ultrasonic_TypeDef *Ultrasonic)
{
	
	Ultrasonic->SignalData.EchoPulseEndTick = __UltrasonicTimer_GetTick();

	if (Ultrasonic->SignalData.EchoPulseEndTick > Ultrasonic->SignalData.EchoPulseStartTick)
	{
		Ultrasonic->SignalData.EchoPulseTime = Ultrasonic->SignalData.EchoPulseEndTick - Ultrasonic->SignalData.EchoPulseStartTick;
	}
	else
	{
		Ultrasonic->SignalData.EchoPulseTime = (UINT16_MAX - Ultrasonic->SignalData.EchoPulseStartTick) + Ultrasonic->SignalData.EchoPulseEndTick;
	}

	if (Ultrasonic->SignalData.EchoPulseTime <= ULTRASONIC_ECHO_RANGE_TIME_MAX_US)
	{
		
		Ultrasonic->DistanceCM   = Ultrasonic->SignalData.EchoPulseTime / 58.0F;
		Ultrasonic->DistanceINCH = Ultrasonic->SignalData.EchoPulseTime / 148.0F;
		
		Ultrasonic->ObjectDetected = ULTRASONIC_OBJ_DETECTED;
		
	}
	else if (Ultrasonic->SignalData.EchoPulseTime >= ULTRASONIC_ECHO_NOT_DETECTED_TIME_US)
	{
		Ultrasonic->ObjectDetected = ULTRASONIC_OBJ_NOT_DETECTED;
	}

	Ultrasonic->ScanEnded = ULTRASONIC_SCAN_ENDED;
	
}
