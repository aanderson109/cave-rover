
// Include Libraries
#include "Arduino.h"
#include "SFE_BMP180.h"
#include "DHT.h"


// Pin Definitions
#define DHT_PIN_DATA	2



// Global variables and defines

// object initialization
SFE_BMP180 bmp180;
DHT dht(DHT_PIN_DATA);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    //Initialize I2C device
    bmp180.begin();
    dht.begin();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // BMP180 - Barometric Pressure, Temperature, Altitude Sensor - Test Code
    // Read Altitude from barometric sensor, note that the sensor is 1m accurate
    double bmp180Alt = bmp180.altitude();
    double bmp180Pressure = bmp180.getPressure();
    double bmp180TempC = bmp180.getTemperatureC();     //See also bmp180.getTemperatureF() for Fahrenheit
    Serial.print(F("Altitude: ")); Serial.print(bmp180Alt,1); Serial.print(F(" [m]"));
    Serial.print(F("\tpressure: ")); Serial.print(bmp180Pressure,1); Serial.print(F(" [hPa]"));
    Serial.print(F("\tTemperature: ")); Serial.print(bmp180TempC,1); Serial.println(F(" [°C]"));

    }
    else if(menuOption == '2') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float dhtTempC = dht.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}

char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) BMP180 - Barometric Pressure, Temperature, Altitude Sensor"));
    Serial.println(F("(2) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing BMP180 - Barometric Pressure, Temperature, Altitude Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
