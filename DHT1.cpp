#include "DHT1.h"

#define TIMEOUT 700    //320 is 80 microseconds

//PUBLIC//

//gonna give relative humidity 
int DHT1::readRHumidity(uint8_t pin){

    int result= readPin(pin);

    if(result!=0){
        return result;
    }

    relhumidity= bits[0]+(bits[1]*0.1);
    return relhumidity;
}

//give absolute humidity in normal air saturation vapor pressure 
int DHT1::readAHumidity(uint8_t pin){

    int result= readPin(pin);

    if(result!=0){
        return result;
    }

    relhumidity= bits[0]+(bits[1]*0.1);
    temperature= bits[2]+(bits[3]*0.1);

    //need to write this lol
    abshumidity= (relhumidity* 1.91)/(461.5/temperature * 100);
    return abshumidity;
}
//gonna give temperature
int DHT1::readTemperature(uint8_t pin){

    int result= readPin(pin);

    if(result!=0){
        return result;
    }

    temperature= bits[2]+(bits[3]*0.1);
    return temperature;
}

//PRIVATE//////



//return 2 means it ha sbeen timed out
//return 1 means checksum error 
//return 0 means everything is good :)
int DHT1 :: readPin (uint8_t pin){

    //clear buffer to recieve data
    for(int i=0; i<5; i++){
        bits[i]=0;
    }
    //send low signal and then send high signal to let DHT11 know we are ready to recieve date
    pinMode(pin, OUTPUT);
    digitalWrite(pin,HIGH);
    digitalWrite(pin, LOW);
    delayMicroseconds(20);
    digitalWrite(pin,HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    int low_eighty= 0;
    int high_eighty= 0;
    //wait for DHT11 to send low signal for 80 microseconds
    while(digitalRead(pin)== LOW){
        if(low_eighty++== TIMEOUT){
            return 2;
        }
    }
 //wait for DHT11 to send high signal for 80 microseconds
    while(digitalRead(pin)== HIGH){
        if(high_eighty++== TIMEOUT){
            return 2;
        }
    }
// populate all 40 bits of data
int bitcnt=7;
int indexcnt=0;
for(int j=0; j<40; j++){
    while(digitalRead(pin)==LOW){}
    unsigned long time = micros(); //time right now
    while(digitalRead(pin)==HIGH){}

    if(time- micros()> 40){
      bits[indexcnt]= (1<< bitcnt);
      bitcnt--;
    }else{
         bits[indexcnt]= (0<< bitcnt);
      bitcnt--;
    }
    if(bitcnt<0){
        bitcnt=7;
        indexcnt++;
    }
}

if(bits[0]+bits[1]+bits[2]+bits[3]!= bits[5]){
    return -1;
}

return 0;
}
