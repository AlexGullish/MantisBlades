
#include <ESP32Servo.h>


#define SERVO_1_PIN 18
#define SERVO_2_PIN 19

#define JOYSTICK_X 34
#define JOYSTICK_Y 35
#define JOYSTICK_SW 25


Servo servo1;
Servo servo2;


const int SERVO_1_HOME = 90;
const int SERVO_2_HOME = 90;


const int DEADZONE = 700;
const int ADC_CENTER = 2048;

bool buttonPressed = false;
bool lastButtonState = HIGH;



void setup() {
  Serial.begin(115200);

  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  analogReadResolution(12);

  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);

  servo1.attach(SERVO_1_PIN, 1000, 2000);
  servo2.attach(SERVO_2_PIN, 1000, 2000);

  servo1.write(SERVO_1_HOME);
  servo2.write(SERVO_2_HOME);

}



void readJoystick() {
  int x = analogRead(JOYSTICK_X);
  int y = analogRead(JOYSTICK_Y);

  Serial.print("X: ");
  Serial.print(x);

  Serial.print(" | Y: ");
  Serial.println(y);
}


void readButton() {
  bool currentState = digitalRead(JOYSTICK_SW);

  if (currentState == LOW && lastButtonState == HIGH) {
    buttonPressed = !buttonPressed;

    Serial.println(
      buttonPressed ? "SYSTEM ACTIVE" : "SYSTEM IDLE"
    );
  }

  lastButtonState = currentState;
}



void loop() {
  readJoystick();
  readButton();

  delay(100);
}
