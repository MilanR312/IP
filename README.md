# Current functions list
All function parts must be spaced using a .
When not used, values will be automatically set to the default values specified [here](/docs/readme.md)  
## Pin related functions  
Functions to interract with the pins

example: Pin.SetValue.Mosfet.ch0(10);
### Function
- Pin
### SubFunction list
- SetValue
- GetValue
### Pin list
- CS1
- SQW
- FlowSens
- mSens
- Mosfet
  - ch0
  - ch1
  - ch2
  - ch3
 
## initialisation functions
If the required initialisation function is not used then the module shall not be enabled  
example: Init.Ser();
### Function
- Init
### SubFunction list
- Ser
- Sd
- cvSens

## Tester functions
These functions are not required but test if the modules are working correctly
example Test.Sd();
### Function
- Test
### SubFunction list
- Sd
- Rtc

## SdCard functions
These functions are used to print to the sd card
example: Sd.PrintSer();
### Function
- Sd
### SubFunction list
- Print
- PrintSer
- SetValue
  - TTC1

## Mosfet functions
These functions can be used to control the 4 output pins
example: Mosfet.Off.ch3();
### Function
- Mosfet
### SubFunction list
- On
- Off
### Function Variables
- ch0
- ch1
- ch2
- ch3

## Fluid related functions
These functions control the modules that are in contact with water
example: Flow.flowCalc
### Function
- Flow
### SubFunction List
- flowCalc
- Pump
- SetValue
  - TTC1
  - TTC2

## MSensor
These functions interract with the moisture sensor
example MSensor.SetHumidity();
### Function
- MSensor
### SubFunction List
- SetHumidity
- isWet
- SetValue
  - dry
  - wet
  - treshold
 
## Lamps
this function controls the lamps
example Lamps.SetValue.TTC1(60);
### Function
- Lamps
### SubFunction list
- Auto
- SetValue
  - TTC1
  - TTC2
  - TTC3
  - DTC1
  - DTC2
  - DTC3
## cvSensor
these functions control the current and voltage sensor
example CVSens:Calc();
### Functions
- CVSens
### subFunction list
- Calc
- SetValue
  - TTC
