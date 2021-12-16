#ifndef IPLIB_h
#define IPLIB_h

#include "Arduino.h"

class ip{
    private:
        //pins
        inline static int _CS1;//53 
        inline static int _mosfet24[4];//3456
        inline static int _SQW; // 2
        inline static int _flowSensPin; // 3
        inline static int _mSens; //A0
        //statics
        static const int _maxCount = 10000;
        //counters
        inline static unsigned int _SecCounter = 0;
        inline static int _flowCounter = 0;
        //interrupts
        static void SecondCountUp();
        static void FlowCountUp();
        
    public:
    ip();//constructor
        class pins{//class for all pin related functions
            public:
                pins();//constructor
                class set_value{//class used for initialising pins
                    public:
                        set_value();//constructor
                        void CS1(int x);
                        void SQW(int a);
                        void FlowSens(int x);
                        void mSens(int a);
                        class mosfet24v{//sub class for the 4 mosfets
                            public:
                                mosfet24v();//constructor
                                void ch0(int a);
                                void ch1(int a);
                                void ch2(int a);
                                void ch3(int a);
                        };
                        mosfet24v Mosfet;//initialise the mosfet subclass
                };
                class get_value{//class used to get the pin number
                    public:
                        get_value();//constructor
                        int CS1();
                        int SQW();
                        int FlowSens();
                        int mSens();
                        class mosfet24v{//subclass for the 4 mosfets
                            public:
                                mosfet24v();
                                int ch0();
                                int ch1();
                                int ch2();
                                int ch3();
                        };
                        mosfet24v Mosfet;//initialise the mosfet subclass
                };
            set_value SetValue;//initialise the Setter and Getter functions
            get_value GetValue;
        };
        class initialisation{//class used to initialise hardware
            public:
                initialisation();//constructor
                void Ser();//initialise serial data
                void Sd();//initialise the sd card
                void Rtc();
                void cvSens();
        };
        class Tester{//class used to test if hardware is found and initialised
            public:
                Tester();//constructor
                void Sd();//test sd card
                void Rtc();//test real time clock
        };
        class sdCard{//class used for all sd card related functions
            private:
                inline static char buffer[150];//buffer for easier printing
                inline static int ttc = 1;//var used to indicate every how many seconds the script will run
                int tuc = 0; //storage for rerun calculation
                inline static int ttctemp = 1;
                int tuctemp = 0;
                inline static char buffertemp[150];
            public:
                void Print();//print all current data
                void PrintSer();

                class setters{
                    public:
                        void TTC1(int a);
                };
                setters SetValue;
        };
        class mosfet{//class used for all mosfet related functions
            public:
                class turnon{//subclass to turn on mosfets
                    public:
                        void ch0();
                        void ch1();
                        void ch2();
                        void ch3();
                };
                class turnoff{//subclass to turn off mosfets
                    public:
                        void ch0();
                        void ch1();
                        void ch2();
                        void ch3();
                };
                turnon On;//initialise the subclasses
                turnoff Off;
        };
        class flow{//class used for all fluid related functions
            private:
                inline static int ttc1 = 1;//var used to indicate every how many seconds the script will run
                int tuc1 = 0;///storage for rerun calculations
                inline static int ttc2 = 1;
                int tuc2 = 0;
            public:
                inline static float volume = 0; //volume filled during current fill cycle
                inline static char volumestr[10];
                float flowCalc();//calculates the volume of water during current cycle
                void Pump();//logic control of pump

                class setters{
                    public:
                        void TTC1(int a);
                        void TTC2(int a);
                };
                setters SetValue;

        };
        class MoistSensor{//class used for all moisture sensor related functions
            private:
                inline static int _dry = 600; //initialise the map function using
                inline static int _wet = 180; //the max en min
                inline static int _threshold = 70; //wet-dry treshold
                inline static int _sensorVal;//incoming sensor value

            public:
                inline static int humidity = 0;//measured humidity
                inline static int dHumidity = 0;//difference of humidity and treshold, positive = too low
                MoistSensor();//constructor
                int SetHumidity();//calculates the current humidity
                bool isWet();//wet or dry
                class setters{
                    public:
                        void dry(int a);
                        void wet(int a);
                        void treshold(int a);
                };
                setters SetValue;
        };
        class lamps{//class used for all lamp related functions
            private:
                inline static int ttc1 = 120;//on and off time for lamp 1
                inline static int ttc2 = 120;//on and off time for lamp 2
                inline static int ttc3 = 240;//on and off time for lamp 3
                inline static float dtc1 = 0.50;
                inline static float dtc2 = 0.50;
                inline static float dtc3 = 0.50;
                int tuc1;//calc vars
                int tuc2;
                int tuc3;
            public:
                lamps();
                void Auto();//auto changes lamps based on on and off time
                class setters{
                    public:
                        setters();
                        void TTC1(int a);
                        void TTC2(int a);
                        void TTC3(int a);
                        void DTC1(float a);
                        void DTC2(float a);
                        void DTC3(float a);
                };
                setters SetValue;
        };
        class cvSens{
            private:
                inline static float Voltage = 0;
                inline static float Current = 0;
                inline static float Power = 0;
                int tuc = 0;
                inline static int ttc = 1;
            public:
                inline static char VoltageStr[10] = "noValue";
                inline static char CurrentStr[10] = "noValue";
                inline static char PowerStr[10] = "noValue";
                void Calc();

                class setters{
                    public:
                        void TTC(int a);
                };
                setters SetValue;
        };
    pins Pin;//initialisation
    initialisation Init;
    Tester Test;
    sdCard Sd;
    mosfet Mosfet;
    flow Flow;
    MoistSensor MSensor;
    lamps Lamps;
    cvSens CVSens;
};


#endif