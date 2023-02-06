#ifndef SFE_BMP180_h
#define SFE_BMP180_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SFE_BMP180
{
	public:
		SFE_BMP180(); // base type

		char begin();
		
		char startTemperature(void);

    double getTemperatureC();
    double getTemperatureF();
    
		char getTemperature(double &T);

		char startPressure(char oversampling);

    double getPressure();

		char getPressure(double &P, double &T);

		double sealevel(double P, double A);

		double altitude();//double P);//, double P0);

		char getError(void);

	private:
	
		char readInt(char address, int16_t &value);

		char readUInt(char address, uint16_t &value);

		char readBytes(unsigned char *values, char length);
			
		char writeBytes(unsigned char *values, char length);
			
		int16_t AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
		uint16_t AC4,AC5,AC6; 
		double c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
		char _error;
    double baseline; // baseline pressure

};

#define BMP180_ADDR 0x77 // 7-bit address

#define	BMP180_REG_CONTROL 0xF4
#define	BMP180_REG_RESULT 0xF6

#define	BMP180_COMMAND_TEMPERATURE 0x2E
#define	BMP180_COMMAND_PRESSURE0 0x34
#define	BMP180_COMMAND_PRESSURE1 0x74
#define	BMP180_COMMAND_PRESSURE2 0xB4
#define	BMP180_COMMAND_PRESSURE3 0xF4

#endif
