#include "Arduino.h"
#include "IPLIB.h"
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_INA219.h>

File myFile0; //init the rtc and sd card libraries
RTC_DS1307 rtc0;
Adafruit_INA219 ina219;

ip IP2;
//miso 50 mosi 51 sck 52
//private
#pragma region interupts
//functions hooked to interrupt pins
void ip::SecondCountUp()
{
  _SecCounter++;
  if (_SecCounter >= _maxCount)
  {
    _SecCounter = 0;
  }
  Serial.print("SecontInt  ");
  Serial.println(_SecCounter);
}
void ip::FlowCountUp() { _flowCounter++; }
#pragma endregion

//public
#pragma region pinSet

void ip::pins::set_value::CS1(int x)
{
  _CS1 = x;
  pinMode(_CS1, OUTPUT);
}
void ip::pins::set_value::SQW(int x)
{
  _SQW = x;
  pinMode(_SQW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_SQW), SecondCountUp, FALLING);
}
void ip::pins::set_value::FlowSens(int a)
{
  _flowSensPin = a;
  pinMode(_flowSensPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_flowSensPin), FlowCountUp, FALLING);
}
void ip::pins::set_value::mosfet24v::ch0(int a)
{
  _mosfet24[0] = a;
  pinMode(_mosfet24[0], OUTPUT);
}
void ip::pins::set_value::mosfet24v::ch1(int a)
{
  _mosfet24[1] = a;
  pinMode(_mosfet24[1], OUTPUT);
}
void ip::pins::set_value::mosfet24v::ch2(int a)
{
  _mosfet24[2] = a;
  pinMode(_mosfet24[2], OUTPUT);
}
void ip::pins::set_value::mosfet24v::ch3(int a)
{
  _mosfet24[3] = a;
  pinMode(_mosfet24[3], OUTPUT);
}
void ip::pins::set_value::mSens(int x)
{
  _mSens = x;
}

#pragma endregion
#pragma region pinGet

int ip::pins::get_value::CS1()
{
  return _CS1;
}
int ip::pins::get_value::mosfet24v::ch0() { return _mosfet24[0]; }
int ip::pins::get_value::mosfet24v::ch1() { return _mosfet24[1]; }
int ip::pins::get_value::mosfet24v::ch2() { return _mosfet24[2]; }
int ip::pins::get_value::mosfet24v::ch3() { return _mosfet24[3]; }
int ip::pins::get_value::SQW() { return _SQW; }
int ip::pins::get_value::FlowSens() { return _flowSensPin; }
int ip::pins::get_value::mSens() { return _mSens; }

#pragma endregion
#pragma region init

void ip::initialisation::Ser()
{
  Serial.begin(9600);
  //delay(1000);
  while (!Serial)
  // {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }
  Serial.println("Serial port initialised");
}
void ip::initialisation::Sd()
{
  Serial.print("Initializing SD card...");
  SD.remove("log2.csv");
  if (!SD.begin(_CS1))
  { //check if sd card has initialised
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
  myFile0 = SD.open("log.csv", FILE_WRITE); //open the file

  if (myFile0)
  {                                                                                              // test if file opened
    myFile0.println("Year;Month;Day;Hour;Minute;Second;Lamp1;Lamp2;Lamp3;Pomp;Volume;Moisture;Voltage(V);Current(A);Power(W)"); //prints to file;
    myFile0.close();                                                                             //close file
  }
  else
  {
    Serial.println("error opening test.csv"); //error
  }
}
void ip::initialisation::Rtc()
{
  //rtc0.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc0.adjust(DateTime(2021, 11, 4, 11, 32, 6));
  rtc0.writeSqwPinMode(DS1307_SquareWave1HZ);
}
void ip::initialisation::cvSens(){
  Serial.println("init cvsensor");
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  Serial.println("Measuring voltage and current with INA219 ...");
}

#pragma endregion
#pragma region test

void ip::Tester::Sd()
{
  myFile0 = SD.open("test.txt", FILE_WRITE); // create file to write

  if (myFile0)
  { // test if file opened
    Serial.print("Writing to test.txt...");
    myFile0.println("SD card succesfully initialised"); //prints to file;
    myFile0.close();                                    //close file
    Serial.println("done.");
  }
  else
  {
    Serial.println("error opening test.txt"); //error
  }

  myFile0 = SD.open("test.txt"); //set var to read file

  if (myFile0)
  { //test if file opened
    Serial.println("test.txt:");
    while (myFile0.available())
    {
      Serial.write(myFile0.read()); //read whole file
    }
    myFile0.close();
  }
  else
  {
    Serial.println("error opening test.txt"); //error
  }
  SD.remove("test.txt"); //deletes the test file
}
void ip::Tester::Rtc()
{
  if (!rtc0.begin())
  { //see if rtc is connected
    Serial.println("no rtc found");
    while (1)
      ;
  }
  if (!rtc0.isrunning())
  { //check if it is running
    Serial.println("rtc not running");
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); code to set time on the rtc
    //rtc.adjust(DateTime(2021, 11, 4, 11, 32, 6));
  }
  Serial.print("RTC succesfully initialised");
}

#pragma endregion
#pragma region sdcard

void ip::sdCard::Print()
{

  if (sdCard::tuc == _SecCounter)
  {                                          //check if code should run
    sdCard::tuc = sdCard::ttc + _SecCounter; //code to calculate the next time the code should run
    if (sdCard::tuc >= _maxCount)
    {                                        //check if the next time is withing the max count
      sdCard::tuc = sdCard::tuc - _maxCount; //calculate the time
    }
    Serial.println("writing to buffer");
    DateTime now = rtc0.now(); //put all data in the buffer with layout
    Serial.println(flow::volume, 6);
    sprintf(sdCard::buffer, "%d;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%d;%s;%s;%s",
            now.year(), //list of data put in buffer
            now.month(),
            now.day(),
            now.hour(),
            now.minute(),
            now.second(),
            digitalRead(_mosfet24[0]) ? "on" : "off",
            digitalRead(_mosfet24[1]) ? "on" : "off",
            digitalRead(_mosfet24[2]) ? "on" : "off",
            digitalRead(_mosfet24[3]) ? "on" : "off",
            flow::volumestr,
            MoistSensor::humidity,
            cvSens::VoltageStr,
            cvSens::CurrentStr,
            cvSens::PowerStr);
    myFile0 = SD.open("log.csv", FILE_WRITE); //open the file

    if (myFile0)
    {                                  // test if file opened
      myFile0.println(sdCard::buffer); //prints to file;
      Serial.println(sdCard::buffer);
      myFile0.close(); //close file
    }
    else
    {
      Serial.println("error opening test.csv"); //error
    }
  }
}

void ip::sdCard::PrintSer()
{

  if (sdCard::tuctemp == _SecCounter)
  {                                                  //check if code should run
    sdCard::tuctemp = sdCard::ttctemp + _SecCounter; //code to calculate the next time the code should run
    if (sdCard::tuctemp >= _maxCount)
    {                                                //check if the next time is withing the max count
      sdCard::tuctemp = sdCard::tuctemp - _maxCount; //calculate the time
    }
    DateTime now = rtc0.now(); //put all data in the buffer with layout
     sprintf(sdCard::buffertemp, "%d;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%d",
            now.year(), //list of data put in buffer
            now.month(),
            now.day(),
            now.hour(),
            now.minute(),
            now.second(),
            digitalRead(_mosfet24[0]) ? "on" : "off",
            digitalRead(_mosfet24[1]) ? "on" : "off",
            digitalRead(_mosfet24[2]) ? "on" : "off",
            digitalRead(_mosfet24[3]) ? "on" : "off",
            flow::volumestr,
            MoistSensor::humidity);
    Serial.println(sdCard::buffertemp);
    Serial.println();
  }
}
void ip::sdCard::setters::TTC1(int a) { sdCard::ttctemp = a; }

#pragma endregion
#pragma region mosfet

void ip::mosfet::turnon::ch0()
{
  digitalWrite(_mosfet24[0], HIGH); /*Serial.println("turning on mosfet 0");*/
}
void ip::mosfet::turnon::ch1() { digitalWrite(_mosfet24[1], HIGH); /*Serial.println("turning on mosfet 1");*/ }
void ip::mosfet::turnon::ch2() { digitalWrite(_mosfet24[2], HIGH); /*Serial.println("turning on mosfet 2");*/ }
void ip::mosfet::turnon::ch3() { digitalWrite(_mosfet24[3], HIGH); /*Serial.println("turning on mosfet 3");*/ }

void ip::mosfet::turnoff::ch0() { digitalWrite(_mosfet24[0], LOW); /*Serial.println("turning off mosfet 0");*/ }
void ip::mosfet::turnoff::ch1() { digitalWrite(_mosfet24[1], LOW); /*Serial.println("turning off mosfet 1");*/ }
void ip::mosfet::turnoff::ch2() { digitalWrite(_mosfet24[2], LOW); /*Serial.println("turning off mosfet 2");*/ }
void ip::mosfet::turnoff::ch3() { digitalWrite(_mosfet24[3], LOW); /*Serial.println("turning off mosfet 3");*/ }

#pragma endregion
#pragma region flow

float ip::flow::flowCalc()
{ // call every second:

  if (flow::tuc1 == _SecCounter)
  {
    flow::tuc1 = flow::ttc1 + _SecCounter;
    if (flow::tuc1 >= _maxCount)
    {
      flow::tuc1 = flow::tuc1 - _maxCount;
    }
    flow::volume += float(_flowCounter) / float(98 * 60); //98default + 60 min to sec
    dtostrf(flow::volume, 2, 6, flow::volumestr);
    _flowCounter = 0; //reset the counter every second
  }
}
void ip::flow::Pump()
{ //redo code better !!!!! brol
  if (flow::tuc2 == _SecCounter)
  {
    flow::tuc2 = flow::ttc1 + _SecCounter;
    if (flow::tuc2 >= _maxCount)
    {
      flow::tuc2 = flow::tuc2 - _maxCount;
    }
    if (ip::MoistSensor::dHumidity > -10)
    {                                   //test if humidity is too high
      digitalWrite(_mosfet24[3], HIGH); //turn off pump
    }
    if (ip::MoistSensor::dHumidity < 10)
    {                                  //test if humidity is too low
      flow::volume = 0;                //turn filled volume to 0
      digitalWrite(_mosfet24[3], LOW); //turn on pump
    }
  }
}
void ip::flow::setters::TTC1(int a) { flow::ttc1 = a; }
void ip::flow::setters::TTC2(int a) { flow::ttc2 = a; }

#pragma endregion
#pragma region moist

int ip::MoistSensor::SetHumidity()
{
  MoistSensor::_sensorVal = analogRead(_mSens);                                                       //set sensor value to read data
  MoistSensor::humidity = map(MoistSensor::_sensorVal, MoistSensor::_dry, MoistSensor::_wet, 0, 100); //map the value to 0-100
  MoistSensor::dHumidity = MoistSensor::_threshold - MoistSensor::humidity;                           //calculates the difference
  return MoistSensor::dHumidity;
}
bool ip::MoistSensor::isWet() { return MoistSensor::_threshold < MoistSensor::humidity; } //tells if wet
void ip::MoistSensor::setters::dry(int a) { MoistSensor::_dry = a; }
void ip::MoistSensor::setters::wet(int a) { MoistSensor::_wet = a; }
void ip::MoistSensor::setters::treshold(int a) { MoistSensor::_threshold = a; }

#pragma endregion
#pragma region lamps

void ip::lamps::Auto()
{ //lamps
  if (lamps::tuc1 == _SecCounter)
  {
    lamps::tuc1 = (round(lamps::dtc1 * lamps::ttc1) + _SecCounter);
    if (lamps::tuc1 >= _maxCount)
    {
      lamps::tuc1 = lamps::tuc1 - _maxCount;
    }
    lamps::dtc1 = 1 - lamps::dtc1;
    digitalRead(IP2.Pin.GetValue.Mosfet.ch0()) ? IP2.Mosfet.Off.ch0() : IP2.Mosfet.On.ch0();
  }

  if (lamps::tuc2 == _SecCounter)
  {
    lamps::tuc2 = (round(lamps::dtc2 * lamps::ttc2) + _SecCounter);
    if (lamps::tuc2 >= _maxCount)
    {
      lamps::tuc2 = lamps::tuc2 - _maxCount;
    }
    lamps::dtc2 = 1 - lamps::dtc2;
    digitalRead(IP2.Pin.GetValue.Mosfet.ch1()) ? IP2.Mosfet.Off.ch1() : IP2.Mosfet.On.ch1();
  }

  if (lamps::tuc3 == _SecCounter)
  {
    lamps::tuc3 = (round(lamps::dtc3 * lamps::ttc3) + _SecCounter);
    if (lamps::tuc3 >= _maxCount)
    {
      lamps::tuc3 = lamps::tuc3 - _maxCount;
    }
    lamps::dtc3 = 1 - lamps::dtc3;
    digitalRead(IP2.Pin.GetValue.Mosfet.ch2()) ? IP2.Mosfet.Off.ch2() : IP2.Mosfet.On.ch2();
  }
}
void ip::lamps::setters::TTC1(int a) { lamps::ttc1 = a; }
void ip::lamps::setters::TTC2(int a) { lamps::ttc2 = a; }
void ip::lamps::setters::TTC3(int a) { lamps::ttc3 = a; }
void ip::lamps::setters::DTC1(float a) { lamps::dtc1 = a; }
void ip::lamps::setters::DTC2(float a) { lamps::dtc2 = a; }
void ip::lamps::setters::DTC3(float a) { lamps::dtc3 = a; }

#pragma endregion
#pragma region Current
void ip::cvSens::Calc(){
  if (cvSens::tuc == _SecCounter)
  {
    cvSens::tuc = cvSens::ttc + _SecCounter;
    if (cvSens::tuc >= _maxCount)
    {
      cvSens::tuc = cvSens::tuc - _maxCount;
    }
  Serial.println("cvsensor calculating");
  cvSens::Current = ina219.getCurrent_mA() / 1000;
  cvSens::Voltage = ina219.getBusVoltage_V();
  cvSens::Power = ina219.getPower_mW() / 1000;

  dtostrf(cvSens::Current, 2, 2, cvSens::CurrentStr);
  dtostrf(cvSens::Voltage, 2, 2, cvSens::VoltageStr);
  dtostrf(cvSens::Power, 2, 2, cvSens::PowerStr);

  // Serial.println(cvSens::Current);
  // Serial.println(cvSens::CurrentStr);
  }
}
void ip::cvSens::setters::TTC(int a){ cvSens::ttc = a; }
#pragma endregion

#pragma region initializers
//initializers
ip::ip(){};

ip::pins::pins()
{
  SetValue.CS1(53);
  SetValue.SQW(2);
  SetValue.FlowSens(3);
  SetValue.Mosfet.ch0(13);
  SetValue.Mosfet.ch1(12);
  SetValue.Mosfet.ch2(11);
  SetValue.Mosfet.ch3(10);
  SetValue.mSens(A0);
};
ip::pins::set_value::set_value(){};
ip::pins::get_value::get_value(){};
ip::pins::set_value::mosfet24v::mosfet24v(){};
ip::pins::get_value::mosfet24v::mosfet24v(){};

ip::initialisation::initialisation(){};

ip::Tester::Tester(){};

ip::MoistSensor::MoistSensor()
{
  _sensorVal;
  humidity;
}

ip::lamps::lamps(){};
ip::lamps::setters::setters(){};
#pragma endregion