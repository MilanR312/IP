# Default values
## Default pin values
### Non changable pins
- miso 50
- mosi 51
- sck  52
### Changeable to interrupt enabled pins
- SQW  2
- FlowSens 3
### changable to any analog pins
- mSens  A0
### Changable to any pin
- Mosfet.ch0 13
- Mosfet.ch1 12
- Mosfet.ch2 11
- Mosfet.ch3 10
- CS1  53
## Default Variables
### SdCard
- TTC1 = 1 cyclus time for printing to sd card in seconds
### flow
- TTC1 = 1 cyclus time for calculating the flow in seconds
- TTC2 = 1 cyclus time for controling the pump in seconds
### MSensor
- dry = 600 analog value for dry soil (range 0-1023)
- wet = 180 analog value for wet soil (range 0-1023)
- treshold = 70 wet/dry treshold (in %)
### Lamps
- TTC1 = 120 cyclus time for lamp 1
- TTC2 = 120 cyclus time for lamp 2
- TTC3 = 240 cyclus time for lamp 3
- DTC1 = 0.50 duty cycle for lamp 1
- DTC2 = 0.50 duty cycle for lamp 2
- DTC3 = 0.50 duty cycle for lamp 3
### cvSens
- TTC = 1 cyclus time for measuring the cv
