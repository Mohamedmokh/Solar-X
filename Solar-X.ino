#include <Servo.h>

Servo motor;

int servoPin = 9;
int ledPin = 7;
int buttonPin = 2;
int lightPin = A0;

int lightLimit = 500;

int angle = 0;
int direction = 1;
int speedServo = 30;

int ledCounter = 0;
bool ledState = LOW;

bool stopped = false;
int lastButton = HIGH;

void setup() {
  motor.attach(servoPin);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  motor.write(0);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int button = digitalRead(buttonPin);

  if (lastButton == HIGH && button == LOW) {
    stopped = !stopped;

    if (stopped == false) {
      digitalWrite(ledPin, LOW);

      while (angle > 0) {
        angle--;
        motor.write(angle);
        delay(speedServo);
      }

      direction = 1;
    }

    delay(300);
  }

  lastButton = button;

  if (stopped == true) {
    digitalWrite(ledPin, LOW);
    return;
  }

  int lightValue = analogRead(lightPin);

  if (lightValue < lightLimit) {
    angle = angle + direction;

    if (angle >= 180) {
      angle = 180;
      direction = -1;
    }

    if (angle <= 0) {
      angle = 0;
      direction = 1;
    }

    motor.write(angle);

    ledCounter++;

    if (ledCounter >= 6) {
      ledCounter = 0;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }

    delay(speedServo);
  } 
  else {
    digitalWrite(ledPin, LOW);
    ledState = LOW;
    ledCounter = 0;

    if (angle > 0) {
      angle--;
      motor.write(angle);
      delay(speedServo);
    }
  }
}