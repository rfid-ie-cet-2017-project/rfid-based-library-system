#include "mon.h"
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

HANDLE hComm;
char  ComPortName[] = "\\\\.\\COM4";
BOOL  Status;                          // Status of the various operations
DWORD dwEventMask;                     // Event mask to trigger
char  TempChar;                        // Temperory Character
DWORD NoBytesRead = 0;                     // Bytes read by ReadFile()
DWORD dNoOFBytestoWrite;
DWORD dNoOfBytesWritten;
void initm()
{
    /*------------------------------------ Setting timeouts0 --------------------------------------------------*/



    hComm = CreateFile( ComPortName,                  // Name of the Port to be Opened
		                        GENERIC_READ | GENERIC_WRITE, // Read/Write Access
								0,                            // No Sharing, ports cant be shared
								NULL,                         // No Security
							    OPEN_EXISTING,                // Open existing port only
		                        0,                            // Non Overlapped I/O
		                        NULL);                        // Null for Comm Devices

			if (hComm == INVALID_HANDLE_VALUE)
				printf("\n    Error! - mon Port %s can't be opened\n", ComPortName);

			DCB dcbSerialParams = { 0 };                         // Initializing DCB structure
			dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

			Status = GetCommState(hComm, &dcbSerialParams);      //retreives  the current settings

			if (Status == FALSE)
				printf("\n    Error! in mon GetCommState()");

			dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 115200
			dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
			dcbSerialParams.StopBits = 0; //ONE5STOPBITS;    // Setting StopBits = 0
			dcbSerialParams.Parity = NOPARITY;        // Setting Parity = None

			Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB

			if (Status == FALSE)
				{
					printf("\n    Error! in mon Setting DCB Structure");
				}

			//------------------------------------ Setting Receive Mask ----------------------------------------------

			// extra part start --------------------------------------------------------------------------------------------
			if (!SetCommMask(hComm, EV_RXCHAR))
                printf("\n\n    Error! in mon Setting CommMask");      // Error setting communications event mask

 COMMTIMEOUTS timeouts = { 0 };
			timeouts.ReadIntervalTimeout         = 50;
			timeouts.ReadTotalTimeoutConstant    = 50;
			timeouts.ReadTotalTimeoutMultiplier  = 10;
			timeouts.WriteTotalTimeoutConstant   = 50;
			timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE)
				printf("\n\n    Error! in Setting mon Time Outs");

}

void mon_r(char SerialBuffer)
{
TempChar='\0';

                if (WaitCommEvent(hComm, &dwEventMask, NULL))
                {

                    do
                    {
                        if (ReadFile(hComm, &TempChar, 1, &NoBytesRead, NULL))
                        {
                            SerialBuffer = TempChar;
                        }

                    } while (TempChar=='\0');
                }
}
void mon_w(char data[25])
{
char* lpBuffer = (char*)malloc(25);		       // lpBuffer should be  char or byte array, otherwise write wil fail
strncpy(lpBuffer, data, 25);
dNoOFBytestoWrite = sizeof(data); // Calculating the no of bytes to write into the port

		Status = WriteFile(hComm,               // Handle to the Serialport
						   lpBuffer,            // Data to be written to the port
						   dNoOFBytestoWrite,   // No of bytes to write into the port
						   &dNoOfBytesWritten,  // No of bytes written to the port
						   NULL);

        free(lpBuffer);


}
