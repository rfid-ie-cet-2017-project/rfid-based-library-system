#include "serialr.h"
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
HANDLE hComm0;
char  ComPortName0[] = "\\\\.\\COM3";

BOOL  Status0;                          // Status of the various operations
DWORD dwEventMask0;                     // Event mask to trigger
char  TempChar0;                        // Temperory Character
// Buffer Containing Rxed Data
DWORD NoBytesRead0 = 0;                     // Bytes read by ReadFile()
int i0 = 0;



void initr()
{
    /*------------------------------------ Setting timeouts0 --------------------------------------------------*/



    hComm0 = CreateFile( ComPortName0,                  // Name of the Port to be Opened
		                        GENERIC_READ | GENERIC_WRITE, // Read/Write Access
								0,                            // No Sharing, ports cant be shared
								NULL,                         // No Security
							    OPEN_EXISTING,                // Open existing port only
		                        0,                            // Non Overlapped I/O
		                        NULL);                        // Null for Comm Devices

			if (hComm0 == INVALID_HANDLE_VALUE)
				printf("\n    Error! - rfid Port %s can't be opened\n", ComPortName0);

			DCB dcbSerialParams = { 0 };                         // Initializing DCB structure
			dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

			Status0 = GetCommState(hComm0, &dcbSerialParams);      //retreives  the current settings

			if (Status0 == FALSE)
				printf("\n    Error! in rfid GetCommState()");

			dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 115200
			dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
			dcbSerialParams.StopBits = 0; //ONE5STOPBITS;    // Setting StopBits = 0
			dcbSerialParams.Parity = NOPARITY;        // Setting Parity = None

			Status0 = SetCommState(hComm0, &dcbSerialParams);  //Configuring the port according to settings in DCB

			if (Status0 == FALSE)
				{
					printf("\n    Error! in rfid Setting DCB Structure");
				}






			//------------------------------------ Setting Receive Mask ----------------------------------------------

			// extra part start --------------------------------------------------------------------------------------------
			if (!SetCommMask(hComm0, EV_RXCHAR))
                printf("\n\n    Error! in rfid Setting CommMask");      // Error setting communications event mask

 COMMTIMEOUTS timeouts0 = { 0 };
			timeouts0.ReadIntervalTimeout         = 50;
			timeouts0.ReadTotalTimeoutConstant    = 50;
			timeouts0.ReadTotalTimeoutMultiplier  = 10;
			timeouts0.WriteTotalTimeoutConstant   = 50;
			timeouts0.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm0, &timeouts0) == FALSE)
				printf("\n\n    Error! in Setting Time Outs");

}







void serialr(char SerialBuffer0[12])
{
    int k;
    char SerialBuffer1[12];

    start:
    i0 = 0;
    TempChar0='\0';

                if (WaitCommEvent(hComm0, &dwEventMask0, NULL))
                {

                    do
                    {
                        if (ReadFile(hComm0, &TempChar0, 1, &NoBytesRead0, NULL))
                        {
                            // A byte has been read; process it.
                            SerialBuffer1[i0] = TempChar0;
                            i0++;

                        }

                    } while (NoBytesRead0==1&&i0<12);
                }

                if(strncmp(SerialBuffer1, SerialBuffer0, 12) == 0 || SerialBuffer1[0] == '\0')
                {
                    for(k = 0; k < 12; k++)
                        SerialBuffer1[k] = '\0';
                    goto start;
                }
                else
                {
                    strncpy(SerialBuffer0, SerialBuffer1, 12);
                }

}
