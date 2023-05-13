// improved and unified serial communication by Robo Durden :-)

#include "gd32f1x0.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/commsSteering.h"
#include "../Inc/setup.h"
#include "../Inc/config.h"
#include "../Inc/defines.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#pragma pack(1)

// Only master communicates with steerin device
#ifdef MASTER
//#define USART_STEER_TX_BYTES 2   // Transmit byte count including start '/' and stop character '\n'
#define USART_STEER_RX_BYTES 7   // Receive byte count including start '/' and stop character '\n'

extern uint8_t usartSteer_COM_rx_buf[USART_STEER_COM_RX_BUFFERSIZE];
//static uint8_t aReceiveBuffer[USART_STEER_RX_BYTES];
static int16_t iReceivePos = 0;	

extern int32_t steer;
extern int32_t speed;

extern float batteryVoltage; 							// global variable for battery voltage
extern float currentDC; 									// global variable for current dc
extern float realSpeed; 									// global variable for real Speed
extern DataSlave oDataSlave;

typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;		//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   int16_t  iSpeed;
   int16_t  iSteer;
   uint16_t checksum;
} SerialServer2Hover;

static uint8_t aReceiveBuffer[sizeof(SerialServer2Hover)];

#define START_FRAME         0xABCD       // [-] Start frme definition for reliable serial communication
typedef struct{				// ´#pragma pack(1)´ needed to get correct sizeof()
   uint16_t cStart;
   int16_t iSpeedL;		// 100* km/h
   int16_t iSpeedR;		// 100* km/h
   uint16_t iVolt;		// 100* V
   int16_t iAmpL;			// 100* A
   int16_t iAmpR;			// 100* A
   uint16_t checksum;
} SerialHover2Server;



//static uint8_t aDebug[sizeof(SerialServer2Hover)];


// Send frame to steer device
void SendSteerDevice(void)
{
	// Ask for steer input
	SerialHover2Server oData;
	oData.cStart = START_FRAME;
	oData.iVolt = (uint16_t)	(batteryVoltage * 100);
	oData.iAmpL = (int16_t) 	(currentDC * 100);
	oData.iAmpR = (int16_t) 	(oDataSlave.currentDC * 100);
	oData.iSpeedL = (int16_t) (realSpeed * 100);
	oData.iSpeedR = (int16_t) (oDataSlave.realSpeed * 100);
/*	
	oData.iVolt = aDebug[0];
	oData.iAmpL = aDebug[1];
	oData.iAmpR = aDebug[2];
	oData.iSpeedL = aDebug[3];
	oData.iSpeedR = (int16_t) sizeof(SerialServer2Hover);	// speed
*/
	
	// oDataSlave.wState;

	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)

	SendBuffer(USART_STEER_COM, (uint8_t*) &oData, sizeof(oData));
	
	//oDataSlave.wState = 11;
}

extern uint32_t steerCounter;								// Steer counter for setting update rate


// Update USART steer input
// static int16_t iReceivePos = -1;		// if >= 0 incoming bytes are recorded until message size reached
void UpdateUSARTSteerInput(void)
{
	uint8_t cRead = usartSteer_COM_rx_buf[0];
	if (cRead == '/')	// Start character is captured, start record
	{
		iReceivePos = 0;
	}

	if (iReceivePos >= 0)		// data reading has begun
	{
		aReceiveBuffer[iReceivePos++] = cRead;
		if (iReceivePos == sizeof(SerialServer2Hover))
		{
			iReceivePos = -1;
			SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
				
			//memcpy(aDebug,aReceiveBuffer,sizeof(SerialServer2Hover));
			
			//if (1)
			if (pData->checksum == CalcCRC(aReceiveBuffer, sizeof(SerialServer2Hover) - 2))	//  first bytes except crc
			{
				//DEBUG_LedSet(SET) // 		(steerCounter%2) < 1
				#ifndef TEST_SPEED	// only use received uart command if NOT in TEST_SPEED mode
					speed = pData->iSpeed;
					steer = pData->iSteer;
				#endif
				//if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function

				ResetTimeout();	// Reset the pwm timout to avoid stopping motors
			}
		}
	}
}

// Update USART steer input
void UpdateUSARTSteerInputNew(void)	// get rid of this stupid struct __attribute__((packed, aligned(1))) "bug" by not using uint8_t in struct
{
	uint8_t cRead = aReceiveBuffer[iReceivePos] = usartSteer_COM_rx_buf[0];
	switch (iReceivePos)
	{
	case 0:	// waiting for first byte of cStart
		if (cRead == (START_FRAME >> 8)	)	
		{
			iReceivePos++;
			DEBUG_LedSet(RESET)
		}
		break;
	case 1:	// expecting second byte of START_FRAME
		if (cRead == (START_FRAME & 0xff)	)	
		{
			iReceivePos++;	// next reading data from 2 on
		}
		else
			iReceivePos--;	// back to 0
		break;
	default:	// data reading has begun
		if (iReceivePos < sizeof(SerialServer2Hover))
			iReceivePos++;	// not yet finished reading
		else
		{
			iReceivePos = 0;	// reading finished, reset iReceivePos for next transmission
			SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
				
			if (1)	// disable checksum for testing ONLY !
			//if (pData->checksum == CalcCRC(aReceiveBuffer, sizeof(SerialServer2Hover) - 2))	//  first bytes except crc
			{
				DEBUG_LedSet(SET) // 		(steerCounter%2) < 1
				#ifndef TEST_SPEED	// only use received uart command if NOT in TEST_SPEED mode
					speed = pData->iSpeed;
					steer = pData->iSteer;
				#endif
				if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function

				ResetTimeout();	// Reset the pwm timout to avoid stopping motors
			}
		}
	}
}

#endif
