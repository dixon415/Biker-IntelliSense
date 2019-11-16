#include "HC_SR04.h"

double cm = 0.0;
double inches = 0.0;

int trigPin = D4;
int echoPin = D5;

double cm1 = 0.0;
double inches1 = 0.0;

int trigPin1 = D2;
int echoPin1 = D3;

/*
Connect an HC-SR04 Range finder as follows:
Spark   HC-SR04
GND     GND
5V      VCC
D4      Trig
D5      Voltage divider output - see below

Echo --|
       >
       < 470 ohm resistor
       >
       ------ D5 on Spark
       >
       < 470 ohm resistor
       >
GND ---|

Test it using curl like this:
curl https://api.spark.io/v1/devices/<deviceid>/cm?access_token=<accesstoken>

The default usable rangefinder is 10cm to 250cm. Outside of that range -1 is returned as the distance.

You can change this range by supplying two extra parameters to the constructor of minCM and maxCM, like this:

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin, 5.0, 300.0);

*/

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);
HC_SR04 rangefinder1 = HC_SR04(trigPin1, echoPin1);
String a = "";

void setup() 
{
    Spark.variable("cm", &cm, DOUBLE);
    Spark.variable("inches", &inches, DOUBLE);
    Spark.variable("cm1", &cm1, DOUBLE);
    Spark.variable("inches1", &inches1, DOUBLE);
    Serial1.begin(9600);
}

void loop() 
{
    cm = rangefinder.getDistanceCM();
    inches = rangefinder.getDistanceInch();
    /*Serial.print(cm);
    Serial.print(" ,");
    Serial1.print(cm);
    Serial1.print(" ,");*/
    cm1 = rangefinder1.getDistanceCM();
    inches1 = rangefinder1.getDistanceInch();
    String cmStr = String(cm,0);
    String cmStr1 = String(cm1,0);
    //Serial.println(cmStr + ", " + cmStr1);
    Serial1.println(cmStr + ", " + cmStr1);
    delay(1);
    
    a= read();// read the incoming data as string
    Serial1.println(a);
    if(a == "Success")
    {
      
      Serial1.println("Data received successfully");
      delay(1000);
    }
}

String read() {
    String str = "";
    while (Serial1.available()) {
        str += (char) Serial1.read();
        delay(1); //wait for the next byte, if after this nothing has arrived it means the text was not part of the same stream entered by the user
    }
    return str;
}

