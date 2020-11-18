// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <NewPing.h>

AF_DCMotor leftmotor(4);
AF_DCMotor rightmotor(3);

#define TRIGGER_PIN A0    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN A1       // Arduino pin tied to echo pin on the ultrasonic sensor.1
#define MAX_DISTANCE 200  // Maximum distance we want to pin for (in centimetres). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

boolean prox;
int distance;

void setup() {
   Serial.begin(9600);  // Set up Serial library at 9600 bps

   // Turn on motor
   leftmotor.setSpeed(150);
   rightmotor.setSpeed(150);

   leftmotor.run(RELEASE); // Stop
   rightmotor.run(RELEASE);
   
}

void loop() {
  sensor_read();

  if (prox == false) {        // Obstruction
    leftmotor.run(BACKWARD);
    rightmotor.run(BACKWARD);
    delay(450);
    leftmotor.run(FORWARD);   // Turn right
    rightmotor.run(RELEASE);
    delay(250);
  } else if (prox == true) {  // No obstruction
    leftmotor.run(FORWARD);
    rightmotor.run(FORWARD);
    delay(250);
  }

  delay(250);
}

void sensor_read() {
  distance = sonar.ping_cm();
  Serial.println(distance);
  
  if (distance > 15 or distance == 0){
    Serial.println("No obstruction");
    prox = true;
  } else {
    Serial.println("Obstruction");
    prox = false;
  }
}
