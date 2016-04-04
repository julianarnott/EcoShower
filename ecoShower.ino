// Eco-Shower Arduino code
// Julian Arnott & James Arnott 2014
//
// We're using the DS18B20 temperature sensor mounted on the hot water pipe for the shower to trigger a 20 minute timer.
// Once the timer has run its course, it switches the relays that cut the power to the shower pump. 
// While the temperature of the pipe exceeds the trigger temperature, the relays will stay switched 
//
// Could add pots so parent can adjust the switching temperature and the shower time.
// switching temperature between 20 and 80 degrees use A0 (pin 23)
// shower time between 5 and 40 minutes use A1 (pin 24)
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3 // Data wire is plugged into pin 3 on the Arduino
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses: http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
DeviceAddress Thermometer = { 0x28, 0x16, 0xA3, 0x84, 0x04, 0x00, 0x00, 0xC3 };
float tempC;
int ledRED = 5; // pin D5 for the led1
int ledGREEN = 6; // pin D6 for the led2
int relay1 = 7; // pin D7 for the relay1
int relay2 = 8; // pin D8 for the relay2
int tempPot = 0; // connect the 10K A taper (linear) temperature potentiometer to Analog input A0
int timePot = 1; // connect the 10K A taper timer (linear) potentiometer to Analog input A1
int temperature_set;
int temperature_read;
int time_set;
int time_read;
int hasBeenSet = 0;
int delaytimer = 0;
void setup(void)
{
 analogReference(EXTERNAL); // Tell Arduino to use the Aref pin for the Analog voltage, (5v)
 Serial.begin(9600); // start serial port
 sensors.begin(); // Start up the library
 sensors.setResolution(Thermometer, 10); // set the resolution to 10 bit (good enough?)
 pinMode(ledRED, OUTPUT); // set the red led pin (5) as an output
 pinMode(ledGREEN, OUTPUT); // set the green led pin (6) as an output
 pinMode(relay1, OUTPUT); // set the relay pin (7) as an output
 pinMode(relay2, OUTPUT); // set the relay pin (8) as an output

 digitalWrite(ledRED, LOW);
 digitalWrite(ledGREEN, LOW);
 digitalWrite(relay1, LOW);
 digitalWrite(relay2, LOW);

 temperature_read = analogRead(tempPot);
 temperature_set = map(temperature_read, 0, 1023, 20, 80); // min temp 20 Degrees C - max temp 80 Degrees
 time_read = analogRead(timePot);
 time_set = map(time_read, 0, 1023, 5, 40); // min time 5 minutes - max time 40 minutes
}
void loop(void)
{ 
 //get temperature
 Serial.println("starting 6 second delay");
 delay(6000); // 6 seconds
 Serial.print("Getting temperature...\n\r");
 sensors.requestTemperatures();
 Serial.print("temperature is: ");
 printTemperature(Thermometer);
 // note that the controls for the relay are reversed. ie: LOW is on and HIGH is off
 // this is because it is inverted on the relay board
 Serial.print("temp setting: ");
 Serial.println(temperature_set);
 Serial.print("time setting: ");
 Serial.println(time_set);
 if (tempC > temperature_set){
 Serial.println("**** Temp over set limit ****");
 if (hasBeenSet < 1){
 Serial.println("starting set delay");
 digitalWrite(ledGREEN, HIGH); // green led to show that the timer is about to start
 while (delaytimer < time_set){
 Serial.print("delay timer: ");Serial.print(delaytimer);Serial.print(" time_set: ");Serial.println(time_set);
 delay(60000); 
 delaytimer = ++delaytimer; 
 }
 delaytimer = 0;
 hasBeenSet = ++hasBeenSet; // don't want to start the delay all over again - it's going to take ages for the pipe to cool as it is
 Serial.println("Turn relay on"); // under normal operation, the relay is not powered, so turning it on will cut the power to the pump
 digitalWrite(relay1, HIGH);
 digitalWrite(relay2, HIGH);
 digitalWrite(ledRED, HIGH); // red led to show we've cut power to the pump
 digitalWrite(ledGREEN, LOW); // can reset the green now
 }
 }else{
 Serial.println("**** Temp under set limit ****");
 // back to normal operation
 // activate relay now 
 Serial.println("Turn relay off");
 digitalWrite(relay1, LOW);
 digitalWrite(relay2, LOW);
 digitalWrite(ledRED, LOW);
 digitalWrite(ledGREEN, LOW);
 // now need to check the temperature again and wait untill it falls below the threshold - so go back to beginning
 // the slow cooling of the water in the pipe should give sufficient delay here (in practice when the threshold is set to 40 degrees, the pipe takes 23 minutes to cool)
 // start the whole process all over again
 hasBeenSet = 0;
 }
 Serial.println("**************************************");
}
void printTemperature(DeviceAddress deviceAddress)
{
 tempC = sensors.getTempC(deviceAddress);
 if (tempC == -127.00) {
 Serial.print("Error getting temperature");
 } else {
 Serial.print("C: ");
 Serial.println(tempC);
 }
}
