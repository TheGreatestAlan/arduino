#include <Wire.h>
#include <Servo.h>

Servo myservo;

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
int newpos = 90;
int pos = 0;
int sensitivity = 10;

void setup(){
  myservo.attach(9);
  
  pinMode(13, OUTPUT);
  Serial.begin(9600); //start serial for output
  //initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  //define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  Serial.println("Ready!");
}

void loop(){
}

//callback for received data
void receiveData(int byteCount){

  while(Wire.available()){
    number = Wire.read();
    if(number == 1){
      if(newpos - sensitivity <= 1){
        newpos == 1;
      }else{
        newpos = newpos - sensitivity;
      }
    }
    if(number == 2){
      if(newpos + sensitivity >= 180){
        newpos == 180;
      }else{
        newpos = newpos + sensitivity;
      }
    }
    if(pos != newpos){
      myservo.write(newpos);  
    }
    pos = newpos;
    Wire.write(newpos);
  }
}

//callback for sending data
void sendData(){
  Wire.write(number);
}

