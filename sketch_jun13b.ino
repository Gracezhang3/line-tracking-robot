#include <Adafruit_MotorShield.h>
#include <hp_BH1750.h>

#define MOTOR_A_TERMINAL 1
#define MOTOR_B_TERMINAL 2
#define MOTOR_C_TERMINAL 3
#define MOTOR_D_TERMINAL 4

#define IR_PIN_1 A0
#define IR_PIN_2 A1
#define IR_PIN_3 A2
#define IR_PIN_4 A4

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *MOTOR_A = AFMS.getMotor(MOTOR_A_TERMINAL);
Adafruit_DCMotor *MOTOR_B = AFMS.getMotor(MOTOR_B_TERMINAL);
Adafruit_DCMotor *MOTOR_C = AFMS.getMotor(MOTOR_C_TERMINAL);
Adafruit_DCMotor *MOTOR_D = AFMS.getMotor(MOTOR_D_TERMINAL);

hp_BH1750 lightSensor;
int light = 0;
int lux = 0;  

void setup() {
  // put your setup code here, to run once:
  AFMS.begin();

  // Serial.begin(9600);

  lightSensor.begin(BH1750_TO_GROUND);

  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);
  pinMode(IR_PIN_3, INPUT);
  pinMode(IR_PIN_4, INPUT);

  MOTOR_A->setSpeed(0);
  MOTOR_A->run(RELEASE);

  MOTOR_B->setSpeed(0);
  MOTOR_B->run(RELEASE);

  MOTOR_C->setSpeed(0);
  MOTOR_C->run(RELEASE);

  MOTOR_D->setSpeed(0);
  MOTOR_D->run(RELEASE);
}

void loop() {
  lightSensor.start();
  
   // Read the value from the IR sensor
  int SEN_1 = digitalRead(IR_PIN_1);
  int SEN_2 = digitalRead(IR_PIN_2);
  int SEN_3 = digitalRead(IR_PIN_3);
  int SEN_4 = digitalRead(IR_PIN_4);

  // Read the vale from the light sensor

  // Serial.println(lux);
  // Serial.println(lux);

  if (light == 0 ) {
    lux = lightSensor.getLux();
  }

  // if ((light == 0 || light == 1) && lux > 2000) {
  //   if (light = 0){
  //     light = 1;
  //   }
  //   else if (light = 1){
  //     light = 1;
  //   }
  // }
 
  if (light == 0 && lux > 2000) {
    light = 1;
  }
  

  if (SEN_1 == 0 && SEN_2 == 0 && light == 1) {
    moveForward();
  }

  else if (SEN_1 == 0 && SEN_2 == 1 && light == 1) {
    //Serial.println("Black detected");
    rotateMotorsCounterClockwise();
  }

  else if (SEN_1 == 1 && SEN_2 == 0 && light == 1) {
    //Serial.println("White detected!");
    rotateMotorsClockwise();
  }

  else if (SEN_1 == SEN_2 && light == 1){
    moveForward();
  }

  // else if (SEN_1 == 0 && SEN_2 == 0 && SEN_3 == 0 && SEN_4 == 0){
  // lux = lightSensor.getLux();
  // Serial.println(lux);
  //   if (lux > 1000) {
  //   stop();
  //   }
  // }
}


  void moveForward(){
  MOTOR_A->setSpeed(255);
  MOTOR_A->run(FORWARD);

  MOTOR_B->setSpeed(255);
  MOTOR_B->run(FORWARD);

  MOTOR_C->setSpeed(255);
  MOTOR_C->run(FORWARD);

  MOTOR_D->setSpeed(255);
  MOTOR_D->run(FORWARD);
}

void stop() {
  MOTOR_A->setSpeed(0);
  MOTOR_B->setSpeed(0);
  MOTOR_C->setSpeed(0);
  MOTOR_D->setSpeed(0);
  MOTOR_A->run(FORWARD);
  MOTOR_B->run(FORWARD);
  MOTOR_C->run(FORWARD);
  MOTOR_D->run(FORWARD);
}

void rotateMotorsClockwise() {
  MOTOR_A->setSpeed(30);
  MOTOR_D->setSpeed(20);
  MOTOR_A->run(BACKWARD);
  MOTOR_D->run(BACKWARD);

  MOTOR_B->setSpeed(250);
  MOTOR_C->setSpeed(250);
  MOTOR_B->run(FORWARD);
  MOTOR_C->run(FORWARD);
}

void rotateMotorsCounterClockwise() {
  MOTOR_B->setSpeed(30);
  MOTOR_C->setSpeed(20);
  MOTOR_B->run(BACKWARD);
  MOTOR_C->run(BACKWARD);

  MOTOR_A->setSpeed(250);
  MOTOR_D->setSpeed(250);
  MOTOR_A->run(FORWARD);
  MOTOR_D->run(FORWARD);
}
