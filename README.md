# Current functions list
All function parts must be spaced using a .  
## Pin related functions  
When not used, pins will be automatically set to the default values specified [here](/docs/readme.md)  

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
- Rtc  Not added yet
## Tester functions
These functions are not required but test if the modules are working correctly
### Function
- Test
### SubFunction list
- Sd
- Rtc
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
## MSensor
These functions interract with the moisture sensor
example MSensor.SetHumidity();
### Function
- MSensor
### SubFunction List
- SetHumidity
- isWet
## Lamps
this function controls the lamps
### Function
- Lamps
### SubFunction list
- Auto
