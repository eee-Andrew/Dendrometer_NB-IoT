#include <DFRobot_SIM7000.h>
#include <SoftwareSerial.h>
#include <ATcommands.h>
#include <LowPower.h>
//
#define ENCODER_PIN1 3
#define ENCODER_PIN2 6
//
int counter = 0;
volatile int encoderStateDATA1;
volatile int previousStateDATA1;
String encoder_direction = "";
volatile bool encoderChanged = false;

#define PIN_TX 7
#define PIN_RX 8
SoftwareSerial mySerial(PIN_RX, PIN_TX);
DFRobot_SIM7000 sim7000(&mySerial);

void setup() {
  pinMode(ENCODER_PIN1, INPUT);
  pinMode(ENCODER_PIN2, INPUT);
  previousStateDATA1 = digitalRead(ENCODER_PIN1);

  Serial.begin(9600);
  mySerial.begin(19200);

  //interrupt when ENCODER_PIN1 will change state
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN1), handleEncoderChange, CHANGE);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);  // Sleep until interrupt

}

void loop() {
  if (encoderChanged) {
    Serial.println("Turn ON SIM7000......");  //used for debugging starts here
  if (sim7000.turnON()) {
    Serial.println("Turn ON !");
  }

  Serial.println("Set baud rate......");
  while (1) {
    if (sim7000.setBaudRate(19200)) {
      Serial.println("Set baud rate:19200");
      break;
    } else {
      Serial.println("Failed to set baud rate");
      delay(1000);
    }
  }                                       //used for debugging ends here

  mySerial.begin(19200);
  ATserial("AT+CGACT=1", 2000); // PDP Context Activate 
  delay(2000);
  ATserial("AT+CREG=1", 2000); // Enable network registration
  delay(2000);
  ATserial("AT+CGATT=1", 2000);
  delay(2000);
  ATserial("AT+CNACT=1,em", 2000);
  delay(2000);
  ATserial("AT+SMCONF=URL,91.121.93.94,1883", 2000); // url , port
  delay(2000);
  ATserial("AT+SMCONN", 2000); // connect to a MQTT Broker
  delay(2000);

    Serial.print("Direction: ");
    Serial.print(encoder_direction);
    Serial.print(" Current value: ");
    Serial.println(counter);

    ATserial("AT+SMPUB=treemeterData,5,1,1", 2000);
    ATserial(counter, 2000);
    delay(3000);  //delay to let AT+SMPUB command run smoothly
    encoderChanged = false;  // Reset the flag
    // Put the microcontroller to sleep to save power
    ATserial("AT+CIPSHUT", 2000); //close DPD  
    ATserial("AT+CPOWD=1", 2000); //close network reg
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);  // Sleep until interrupt

  }  
}

void handleEncoderChange() {
  encoderStateDATA1 = digitalRead(ENCODER_PIN1);

  if (encoderStateDATA1 != previousStateDATA1) {
    if (digitalRead(ENCODER_PIN2) != encoderStateDATA1) {
      counter++;
      encoder_direction = "CCW"; // counter-clockwise
    } else {
      counter--;
      encoder_direction = "CW"; // clockwise
    }
    encoderChanged = true;  // Set the flag to indicate a change
    previousStateDATA1 = encoderStateDATA1;
  }
}

String ATserial(const char *toSend, unsigned long milliseconds) {
}
