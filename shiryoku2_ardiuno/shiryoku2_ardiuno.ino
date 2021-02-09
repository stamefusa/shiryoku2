#include <Servo.h>

#define SPIN_01 6
#define SPIN_05 7
#define SPIN_10 8
#define SPIN_20 9

Servo s01, s05, s10, s20, target_s;

unsigned long start_time = 0;

boolean is_recognizing = false;

String pre_key = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10); // SerialでのString受信のタイムアウト設定（ms）

  pinMode(13, OUTPUT);

  s01.attach(SPIN_01);
  s05.attach(SPIN_05);
  s10.attach(SPIN_10);
  s20.attach(SPIN_20);
  s01.write(90);
  s05.write(90);
  s10.write(90);
  s20.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String key = Serial.readStringUntil(';');
    key.trim();
    Serial.println(key);

    if (pre_key != key && (key == "a" || key == "b" || key == "c" || key == "d")) {
      Serial.println("START.");
      // 音声認識開始
      start_time = millis();
      is_recognizing = true;
      // LED点灯
      // TODO あとでピン番号直して複数いけるように修正
      digitalWrite(13, HIGH);
      // 動かすサーボ決定
      target_s = chooseServo(key);
    }

    // サーボを動かす
    servo(key, target_s);

    // 連続で同じランドルト環が選ばれたときの処理
    if (key == "a" || key == "b" || key == "c" || key == "d") {
      pre_key = key;
    }
  }

  // 音声認識開始から10秒経過したらリセット
  if (is_recognizing == true && millis() - start_time > 10000) {
    // LED消灯
    // TODO あとでピン番号直して複数いけるように修正
    digitalWrite(13, LOW);
    // サーボを戻す
    servo("2", s01);
    servo("2", s05);
    servo("2", s10);
    servo("2", s20);

    start_time = millis();
    is_recognizing = false;
    pre_key = "";
    Serial.println("RESET.");
  }

  delay(100);
}

Servo chooseServo(String key) {
  if (key == "a") {
    return s01;
  } else if (key == "b") {
    return s05;
  } else if (key == "c") {
    return s10;
  } else {
    return s20;
  }
}

void servo(String key, Servo s) {
  if (key == "0") {
    s.write(10);
  } else if (key == "1") {
    s.write(45);
  } else if (key == "2") {
    s.write(90);
  } else if (key == "3") {
    s.write(135);
  } else if (key == "4") {
    s.write(180);
  }
}
