#include <BluetoothSerial.h>
#include <ESP32Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo claw;

BluetoothSerial SerialBT;

//angles
int ang1;
int ang2;
int ang3;
int ang4;

//raw data
int d1;
int d2;
int d3;
int d4;

void setup() {
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	base.setPeriodHertz(50);

  Serial.begin(115200);
  SerialBT.begin("Robotic-Arm-IITD-RC");
  
  base.attach(15, 600, 2400);
  shoulder.attach(13, 600, 2400);
  elbow.attach(4, 600, 2400);
  claw.attach(16, 600, 2400);
}

void loop() {
  if (SerialBT.available()) {
    byte data[4]; //buffer size
    
    // Read the data sent from the Android app
    int bytesRead = SerialBT.readBytes(data, sizeof(data));
    
    // Assuming the data contains integers (4 bytes each)
    int raw = *((int*)&data[0]);
    
    d1 = floor(raw/1000000);
    raw = raw%1000000;
    d2 = floor(raw/10000);
    raw = raw%10000;
    d3 = floor(raw/100);
    d4 = raw%100;

    ang1 = map(d1, 0, 99, 0, 180);
    ang2 = map(d2, 0, 99, 0, 180);
    ang3 = map(d3, 0, 99, 0, 180);
    ang4 = map(d4, 0, 99, 0, 180);

    Serial.print(ang1);
    Serial.print(" ");
    Serial.print(ang2);
    Serial.print(" ");
    Serial.print(ang3);
    Serial.print(" ");
    Serial.println(ang4);

    base.write(ang1);
    shoulder.write(ang2);
    elbow.write(ang3);
    claw.write(ang4);
      
  }
}
