#include <Servo.h>

Servo s1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10); // SerialでのString受信のタイムアウト設定（ms）

  pinMode(13, OUTPUT);

  s1.attach(6);
  s1.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String key = Serial.readStringUntil(';');
    key.trim();
    //Serial.print("receive : ");
    Serial.println(key);

    if (key == "a") {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }

    if (key == "0") {
      Serial.println("servo 0");
      s1.write(5);
    } else if (key == "1") {
      Serial.println("servo 180");
      s1.write(180);
    } else if (key == "2") {
      Serial.println("servo 90");
      s1.write(90);
    }
  }

 delay(100);
}
