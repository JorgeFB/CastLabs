// CastLabs.cpp By Jorge Feliu Barros
// Contact information : jorge.feliubarros@gmail.com / +1 305 978 9736

#pragma comment(lib, "urlmon.lib")

#include <iostream>
#include <fstream>
#include <string> 
#include <urlmon.h>

#include "mp4Parser.h"

using namespace std;

int main()
{
	Box* pCurrentBox = new Box;
	char nextFourBytesTemp[HEADER_SIZE+1] = {'\0'};
	char nextFourBytes[2*HEADER_SIZE+1] = {'\0'};
	unsigned int iterator = 0;
	ifstream mp4File;
	
	//Download input the file
	//Defining Source
	string fileURL = MP4_URL;
	wstring wFileURL;
	wFileURL.assign(fileURL.begin(), fileURL.end());
	LPCTSTR lpcURL = wFileURL.c_str();
	//Defining Destination
	string destination = "text0.mp4";
	wstring wDestination;
	wDestination.assign(destination.begin(), destination.end());
	LPCTSTR lpcDestination = wDestination.c_str();
	// Download request
	if (URLDownloadToFile(NULL, lpcURL, lpcDestination, 0, NULL) != S_OK)
	{
		printf("[ERROR] Failed when downloading file %s\n", MP4_URL);
		delete pCurrentBox;
		return -1;
	}
		
	printf("Successfully loaded file %s\n", MP4_URL);

	//Open the file
	mp4File.open("text0.mp4", ios::binary);
		
	// Going over the file
	while (mp4File.good())
	{
		//Get Box Size
		mp4File.get(nextFourBytesTemp, HEADER_SIZE+1);
		sprintf_s(nextFourBytes, sizeof(nextFourBytes), "%02x%02x%02x%02x"
			, (unsigned char)nextFourBytesTemp[0]
			, (unsigned char)nextFourBytesTemp[1]
			, (unsigned char)nextFourBytesTemp[2]
			, (unsigned char)nextFourBytesTemp[3]
		);
		pCurrentBox->size = hexadecimalToDecimal(nextFourBytes);

		//Get Box Type
		mp4File.get(nextFourBytesTemp, HEADER_SIZE+1);
		strncpy_s(pCurrentBox->type, nextFourBytesTemp, HEADER_SIZE+1);

		//Print result
		printf("Found box of type %s and size %d\n", pCurrentBox->type, pCurrentBox->size);
		if (!strcmp(pCurrentBox->type, MDAT_TYPE))
		{
			printf("Content of mdat box is:\n");
			iterator = 0;
			while (mp4File.good() && iterator < pCurrentBox->size) {
				printf("%c", mp4File.get());
				iterator++;
			}
		}

		//Jumping to the next box
		if (   !strcmp(pCurrentBox->type, MFHD_TYPE)
			|| !strcmp(pCurrentBox->type, TFHD_TYPE)
			|| !strcmp(pCurrentBox->type, TRUN_TYPE)
			|| !strcmp(pCurrentBox->type, TRUN_TYPE)
			|| !strcmp(pCurrentBox->type, UUID_TYPE)
			|| !strcmp(pCurrentBox->type, MDAT_TYPE)
			)
		{
			//Use size value to move
			iterator = 0;
			while (mp4File.good() && iterator < (pCurrentBox->size-2*HEADER_SIZE)) 
			{
				mp4File.get();
				iterator++;
			}
		}
		else { /*MOOF or TRAF : next box comes right after */}
	}
	printf("Thank you!\n");
	mp4File.close();
	delete pCurrentBox;
}
