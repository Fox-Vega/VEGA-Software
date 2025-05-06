#include <Arduino.h>

class LINE {
    public:
        void Line_Setup();
        void Line_End();
        int Read_Line();
        int Line_Read();
        void Line_buble_sort();

    private:
        #define true 1 //true
        #define false 0 //false
        #define NUMLINES 24 // Number of line sensors
        #define readPin1 A13 // Pin for reading the first line sensor
        #define readPin2 A11 // Pin for reading the second line sensor
        #define readPin3 A9 // Pin for reading the third line sensor
        
        const int selectA = 22;
        const int selectB = 24;
        const int selectC = 26;
        int line_deg;
};