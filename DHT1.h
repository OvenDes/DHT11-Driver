//Driver for DHT11 
//header file that defines function to read the sensor with two variable humidty and 
//temperature which is public


//Secret stuff where read function is defined and storage center is defined

#ifndef DHT1_H
#define DHT1_H

#include "Arduino.h" // Arduino core library

class DHT1 {
public:
    int readTemperature(uint8_t pin);  // Reads temperature from the sensor
    int readRHumidity(uint8_t pin);     // Reads relative humidity from the sensor
    int readAHumidity(uint8_y pin);     // gets absolute humidity from sensor
    double relhumidity;                   // Stores relative humidity value
    double abshumidity;                   //stores absolute humdiity value
    double temperature;                // Stores temperature value

private:
    int readPin(uint8_t pin);          // Low-level read function for the sensor
    uint8_t bits[5];                   // Buffer to receive data from sensor
};

#endif