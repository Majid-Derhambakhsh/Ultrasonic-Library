/*
------------------------------------------------------------------------------
~ File   : ultrasonic_conf.h
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

#ifndef __ULTRASONIC_CONF_H_
#define __ULTRASONIC_CONF_H_

/* ~~~~~~~~~~~~~~~ Include files ~~~~~~~~~~~~~~~ */
/* Timer header */
//#include "timer.h"

/* HAL or MCU header */
//#include <avr/io.h>
//#include "stm32f1xx_hal.h"

/* ~~~~~~~~~~~~~~~~~~ Options ~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~ Microsecond Timer ~~~~~~~~ */
#define __UltrasonicTimer_GetTick()   Timer1_GetTick()

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __ULTRASONIC_CONF_H_ */
