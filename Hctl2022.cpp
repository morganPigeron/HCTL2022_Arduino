#include <Arduino.h>
#include "Hctl2022.h"

//hardcoded arduino port used
#define SET_PORT DDRD
#define READ_PORT PIND

Hctl2022::Hctl2022(int oe, int sel1, int sel2) 
{
    // 8 bits bus from hctl2022
    SET_PORT = B00000000; // set pin 7,6,5,4,3,2,1,0 as input

    // enable
    pinMode(oe, OUTPUT);
    _oe = oe;

    // byte selector
    pinMode(sel1, OUTPUT);
    pinMode(sel2, OUTPUT);
    _sel1 = sel1;
    _sel2 = sel2;    
}

void Hctl2022::getMsb()
{
    _hi_old = READ_PORT;
    _hi_new = READ_PORT;

    if (_hi_old == _hi_new)
    {
        _result_hi = _hi_new;
        return;
    }
    else
    {
        get2nd();
    }
}

void Hctl2022::get3rd()
{
    _3rd_old = READ_PORT;
    _3rd_new = READ_PORT;

    if (_3rd_old == _3rd_new)
    {
        _result_3rd = _3rd_new;
        return;
    }
    else
    {
        get2nd();
    }
}

void Hctl2022::get2nd()
{
    _2nd_old = READ_PORT;
    _2nd_new = READ_PORT;

    if (_2nd_old == _2nd_new)
    {
        _result_2nd = _2nd_new;
        return;
    }
    else
    {
        get2nd();
    }
}

void Hctl2022::getLsb()
{
    _lo_old = READ_PORT;
    _lo_new = READ_PORT;

    if (_lo_old == _lo_new)
    {
        _result_lo = _lo_new;
        return;
    }
    else
    {
        getLsb();
    }
}

unsigned long Hctl2022::hctlRead()
{
    _result = 0;
    _temp = 0;
    unsigned long previousMillis = 0; 
    unsigned long currentMillis = 0; 
    
    digitalWrite(_oe, HIGH); // disable oe

    // delay 25ms
    previousMillis = millis();
    do 
    {
        currentMillis = millis();
    }while(currentMillis - previousMillis >= 25);

    // select MSB
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel2, HIGH);
    digitalWrite(_oe, LOW);

    getMsb();

    // select 2nd byte
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel2, HIGH);

    get2nd();
    
    // select 3rd byte
    digitalWrite(_sel1, LOW);
    digitalWrite(_sel2, LOW);

    get3rd();

    // select LSB
    digitalWrite(_sel1, HIGH);
    digitalWrite(_sel2, LOW);

    getLsb();

    digitalWrite(_oe, LOW);// enable oe

    // delay 25ms *************************maybe not mandatory
    previousMillis = millis();
    do
    {
        currentMillis = millis();
    }while(currentMillis - previousMillis >= 25);

    return 0;
}

void Hctl2022::hctlDebug()
{
    Serial.print("DEBUG HCTL");
    Serial.print(" | MSB: " + _result_hi);
    Serial.print(" | 3rd: " + _result_3rd);
    Serial.print(" | 2nd: " + _result_2nd);
    Serial.print(" | LSB: " + _result_lo);
    Serial.print(" | result: " + _result); 
} 
    
