#include "I2Cdev.h"
#include "HMC5883L.h"
#include "MPU6050.h"
#include <Wire.h>

HMC5883L mag;
MPU6050 accelgyro;
int16_t mx, my, mz;
int16_t ax, ay, az;
int16_t gx, gy, gz;

const int redPin = 4;
const int greenPin = 5;
const int bluePin = 6;
int time = 5;
float start_angle=0;
float end_angle=0;
int task;
int success = 0;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing I2C devices...");
  mag.initialize();

  Serial.println("Testing device connections...");
  Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");

  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  delay(3000);
}

void loop() { 
  if(time == -1){
    Serial.println("game over");
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
    while(true)
      tone(8,900,10);
  }
  
  
  // put your main code here, to run repeatedly:
  while(time>2){
    mag.getHeading(&mx, &my, &mz);
    if(time == 5){
    //  randomSeed(15);
      unsigned long currentMillis = millis();
      task=(currentMillis+100)%4;
      if(task==0)
        Serial.println("[task1]  shaking!!!!!");
      else if(task==1)
        Serial.println("[task2]   heading to north!!!");
      else if(task==2)
        Serial.println("[task3]   20 degrees!!!");
      else if (task==3)
        Serial.println("[task4]   buttom of!!!");
      float heading = atan2(my, mx);
      if(heading < 0)
        heading += 2 * M_PI;
      start_angle = heading* 180/M_PI;
     // Serial.print("start");
     // Serial.println(start_angle);
    }

    else{
      checksuccess();
      if(success == 1){
        success=0;
        time = 5;
        break;
      } 
    }

//    float heading = atan2(my, mx);
//      if(heading < 0)
//        heading += 2 * M_PI;
//      int angle = heading* 180/M_PI;
//      Serial.print("angle : ");
//      Serial.println(angle);
    
    Serial.println(time);
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
    time--;
    delay(1000);
  }
  
  while(time<=2){
    // mag.getHeading(&mx, &my, &mz);
    if(time==0){
      time=-1;
      break;
    }

    checksuccess();
    if(success == 1){
        success=0;
        time = 5;
        break;
    }
    Serial.println(time);
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
    time--;
    tone(8,900,10);
    delay(300);
    tone(8,900,10);
    delay(700);
  // (0,255,255)-> red (0,0,255)-> green
  }
  
}

void checksuccess(){
  mag.getHeading(&mx, &my, &mz);
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float heading_end = atan2(my, mx);
  if(heading_end < 0)
    heading_end += 2 * M_PI;
  end_angle = heading_end* 180/M_PI;
  Serial.print("end_angle = ");
  Serial.println(end_angle);
//  Serial.print("az = ");
//  Serial.println(az);
  //Serial.println(task);
  if(task == 0)
    Serial.println(sqrt(pow(ax,2)+pow(ay,2)+pow(az,2)));
    if(sqrt(pow(ax,2)+pow(ay,2)+pow(az,2)) >16500 ){
      Serial.println("shaking success");
      Serial.println("");
      success=1;
    }
  if(task == 1)
    if(end_angle>330||end_angle<30){
      Serial.println("north success");
      Serial.println("");
      success=1;
    }     
  if(task == 2) //350 8
    if( (end_angle-start_angle > 20 && end_angle-start_angle <340 ) || ( start_angle-end_angle >20 && start_angle-end_angle < 340 )){
      Serial.println("angle>20 success");
      Serial.println("");
      success=1;
    }
  if(task == 3){
//    Serial.println("in 3");
    if(az<3000){
      Serial.println("bottom of MPU success");
      Serial.println("");
      success=1;
    }
  }
    
}

