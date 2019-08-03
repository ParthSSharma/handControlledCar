#include<Wire.h>
#include<SoftwareSerial.h>

int lmpin1 = 4;
int lmpin2 = 5;
int rmpin1 = 6;
int rmpin2 = 7;

long accelX, accelY, accelZ;
double gForceX, gForceY, gForceZ;

SoftwareSerial mySerial(10, 11);

void setup() {
  mySerial.begin(38400);
  pinMode(lmpin1, OUTPUT);
  pinMode(lmpin2, OUTPUT);
  pinMode(rmpin1, OUTPUT);
  pinMode(rmpin2, OUTPUT);
}

void loop() {
  if(mySerial.available() > 0){
    String discard = mySerial.readStringUntil(';');
    mySerial.read();
    String first  = mySerial.readStringUntil(',');
    mySerial.read();
    String second = mySerial.readStringUntil(',');
    mySerial.read();
    String third  = mySerial.readStringUntil(';');
    mySerial.read();
    accelX = first.toInt();
    accelY = second.toInt();
    accelZ = third.toInt();
    gForceX = accelX/16384.0;
    gForceY = accelY/16384.0;
    gForceZ = accelZ/16384.0;
    if(gForceZ > 0.8){
      analogWrite(lmpin1, 0);
      analogWrite(lmpin2, 0);
      analogWrite(rmpin1, 0);
      analogWrite(rmpin2, 0);
    }
    if((gForceY < -0.4) && (gForceZ < 0.8)){
      analogWrite(lmpin1, 127);
      analogWrite(lmpin2, 0);
      analogWrite(rmpin1, 127);
      analogWrite(rmpin2, 0);
    }
    if(0.4 < gForceY){
      analogWrite(lmpin1, 0);
      analogWrite(lmpin2, 127);
      analogWrite(rmpin1, 0);
      analogWrite(rmpin2, 127);
    }
    if(gForceX > 0.3){
      analogWrite(lmpin1, 0);
      analogWrite(lmpin2, 127);
      analogWrite(rmpin1, 127);
      analogWrite(rmpin2, 0);
    }
    if(-0.25 > gForceX){
      analogWrite(lmpin1, 127);
      analogWrite(lmpin2, 0);
      analogWrite(rmpin1, 0);
      analogWrite(rmpin2, 127);
    }
  }
}
