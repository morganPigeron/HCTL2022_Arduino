#ifndef Hctl2022_h 
#define hctl2022_h

#include <Arduino.h>

class Hctl2022
{
    public:
        Hctl2022(int,int,int); // constructor
        unsigned long hctlRead(); // read the hctl2022
        void hctlDebug();
  
    private:
        void getMsb(); // get the most significant byte
        void get3rd(); // get the 3rd byte
        void get2nd(); // get the 2nd byte 
        void getLsb(); // get the least significant byte
      
        unsigned long _result;   
        unsigned long _temp;   
        int _oe;
        int _sel1;
        int _sel2;
      
        //intermediary result for read function
        byte _hi_old;
        byte _hi_new;
        byte _result_hi;
      
        byte _2nd_old;
        byte _2nd_new;
        byte _result_2nd;
      
        byte _3rd_old;
        byte _3rd_new;
        byte _result_3rd;
      
        byte _lo_old;
        byte _lo_new;
        byte _result_lo;
};

#endif
