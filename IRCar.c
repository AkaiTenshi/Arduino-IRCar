#include <IRremote.h>

const int RECV_PIN = 7; //The IR Receiver
//These are standard from the Arduino Motor Shield. For more info read the documentation.
const int motorDirA = 12;
const int motorBrkA = 9;
const int motorPwmA = 3;
//The LED pin
const int lights = 2;
int flag = 0; // To check if the lights are on or off

IRrecv irrecv(RECV_PIN); // Initialize the IR receiver
decode_results results; // This holds the transimitted signal

void setup() {
  Serial.begin(9600); // Start the serial monitor (only used for debugging)
  irrecv.enableIRIn(); // Start the receiver

  // Set the mode for the motor & light pins to output
  pinMode(motorDirA, OUTPUT);
  pinMode(motorBrkA, OUTPUT);
  pinMode(lights, OUTPUT);

}

void loop() {
  // This if loops through the signal values that get sent.
  if(irrecv.decode(&results)){

    Serial.println(results.value, HEX);
    // Signal to go straight
    if(results.value == 0x10EFA05F){
      digitalWrite(motorDirA, HIGH); // Set the direction
      digitalWrite(motorBrkA, LOW); // Disengage the brake
      analogWrite(motorPwmA, 255); // Set the speed
    }

    //Signal to reverse
    if(results.value == 0x10EF00FF){
      digitalWrite(motorDirA, LOW); // Set the direction
      digitalWrite(motorBrkA, LOW); // Disengage the brake
      analogWrite(motorPwmA, 255); // Set the speed
    }

    // Signal to brake
    if(results.value == 0x10EF20DF){
      digitalWrite(motorBrkA, HIGH); // Engage the brakes
    }

    // Signal for the lights
    if(results.value == 0x10EFF807){
      // If the light are on, turn them off
      if(flag == 1){
        digitalWrite(lights, LOW);
        flag = 0;
      // Else turn them on
      }else{
        digitalWrite(lights, HIGH);
        flag = 1;
      }
    }

    // Restart the receiver.
    irrecv.resume();
  }

}
