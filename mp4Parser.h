// mp4Parser.h: By Jorge Feliu Barros
// Contact information : jorge.feliubarros@gmail.com / +1 305 978 9736

#pragma once

#define HEADER_SIZE 4

#define MOOF_TYPE "moof"
#define MFHD_TYPE "mfhd"
#define TRAF_TYPE "traf"
#define TFHD_TYPE "tfhd"
#define TRUN_TYPE "trun"
#define UUID_TYPE "uuid"
#define MDAT_TYPE "mdat"

#define MP4_URL "http://demo.castlabs.com/tmp/text0.mp4"

//Function to convert from ascii to hex-string
int hexadecimalToDecimal(char hexVal[HEADER_SIZE+1])
{
	int len = strlen(hexVal);
	int base = 1;
	int dec_val = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		if (hexVal[i] >= '0' && hexVal[i] <= '9')
		{
			dec_val += (hexVal[i] - 48) * base;
			base = base * 16;
		}
		else if (toupper(hexVal[i]) >= 'A' && toupper(hexVal[i]) <= 'F')
		{
			dec_val += (toupper(hexVal[i]) - 55) * base;
			base = base * 16;
		}
	}
	return dec_val;
}

//Box object
class Box {
public:
	unsigned int size = 0;
	char type[HEADER_SIZE + 1] = {'\0'};

};

