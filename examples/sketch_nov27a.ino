#include <IPLIB.h>

ip IP;

 
void setup(){
  IP.Pin.SetValue.CS1(23);
  IP.Pin.SetValue.Mosfet.ch0(33);
  
  IP.Sd.SetValue.TTC1(5);
  
  IP.Flow.SetValue.TTC1(2);
  IP.Flow.SetValue.TTC2(3);
  
  IP.MSensor.SetValue.dry(180);
  IP.MSensor.SetValue.wet(600);
  IP.MSensor.SetValue.treshold(50);
  
  IP.Lamps.SetValue.TTC1(10);
  IP.Lamps.SetValue.DTC1(0.8);
  
  IP.Init.Ser();
  IP.Init.Sd();
  IP.Init.Rtc();
  
  IP.Test.Sd();
  IP.Test.Rtc();
}
void loop(){
  IP.MSensor.SetHumidity();
  IP.Flow.flowCalc();
  IP.Sd.Print();
  IP.Flow.Pump();
  IP.Lamps.Auto();
}
