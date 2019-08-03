#include<Wire.h>

double accelX, accelY, accelZ;
int command;

void setup(){
  Serial.begin(9600);
  Wire.begin(); //I2C communication
  setupMPU(); 
}

void loop(){
  recordAccelRegisters();
  printData();
  processData();
  delay(10);
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //I2C address of MPU
  Wire.write(0x6B); //Accessing register 6B, power management
  Wire.write(0b00000000); //Disabling sleep mode
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C); //Setup accel
  Wire.write(0b00000000); //Accel for +/- 2g
  Wire.endTransmission();
}

void recordAccelRegisters(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B); //Starting registors for accel readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request accel registors 3B-40
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //First 2 bytes
  accelY = Wire.read()<<8|Wire.read(); //Middle 2 bytes
  accelZ = Wire.read()<<8|Wire.read(); //Last 2 bytes
  accelX = accelX/16384.0;
  accelY = accelY/16384.0;
  accelZ = accelZ/16384.0;
}

void processData(){
  if(accelY < -0.5 && accelX > -0.4 && accelX < 0.5){
    command = 1;
  }
  else if(accelY > 0.4 && accelX > -0.4 && accelX < 0.5){
    command = 2;
  }
  else if(accelX < -0.5){
    command = 3;
  }
  else if(accelX > 0.6){
    command = 4;
  }
  else{
    command = 0;
  }
}

void printData(){
  Serial.println(command);
}
