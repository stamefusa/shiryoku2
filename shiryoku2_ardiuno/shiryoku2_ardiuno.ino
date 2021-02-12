#include <Servo.h>

#define SPIN_01 5
#define SPIN_05 4
#define SPIN_10 3
#define SPIN_20 2

#define LPIN_01 7
#define LPIN_02 8
#define LPIN_03 9
#define LPIN_04 10
#define LPIN_05 11

Servo s01, s05, s10, s20;

unsigned long start_time = 0;

boolean is_recognizing = false;

String pre_key = "";

String target = "";

int servo_deg[4][8] = {
  {180, 135, 90, 45, 5, 999, 999, 999},
  {90, 45, 5, 999, 999, 999, 180, 135},
  {45, 5, 999, 999, 999, 180, 135, 90},
  {999, 999, 180, 135, 90, 45, 5, 999}
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10); // SerialでのString受信のタイムアウト設定（ms）

  // LEDピン初期化
  pinMode(LPIN_01, OUTPUT);
  pinMode(LPIN_02, OUTPUT);
  pinMode(LPIN_03, OUTPUT);
  pinMode(LPIN_04, OUTPUT);
  pinMode(LPIN_05, OUTPUT);

  // サーボピン初期化
  s01.attach(SPIN_01);
  s05.attach(SPIN_05);
  s10.attach(SPIN_10);
  s20.attach(SPIN_20);
  // サーボ初期位置
  initServo();
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
      ledOn();
      // 動かすサーボ決定
      target = chooseServo(key);
      Serial.println(target);
    }

    // サーボを動かす
    driveServo(key, target);

    // 連続で同じランドルト環が選ばれたときの処理
    if (key == "a" || key == "b" || key == "c" || key == "d") {
      pre_key = key;
    }
  }

  // 音声認識開始から10秒経過したらリセット
  if (is_recognizing == true && millis() - start_time > 10000) {
    // LED消灯
    ledOff();
    // サーボを戻す
    initServo();

    start_time = millis();
    is_recognizing = false;
    pre_key = "";
    Serial.println("RESET.");
  }

  delay(100);
}

void initServo() {
  s01.write(90); // 右
  s05.write(90); // 上
  s10.write(90); // 左上
  s20.write(90); // 下
}

void ledOn() {
  digitalWrite(LPIN_01, HIGH);
  digitalWrite(LPIN_02, HIGH);
  digitalWrite(LPIN_03, HIGH);
  digitalWrite(LPIN_04, HIGH);
  digitalWrite(LPIN_05, HIGH);
}

void ledOff() {
  digitalWrite(LPIN_01, LOW);
  digitalWrite(LPIN_02, LOW);
  digitalWrite(LPIN_03, LOW);
  digitalWrite(LPIN_04, LOW);
  digitalWrite(LPIN_05, LOW);
}

String chooseServo(String key) {
  if (key == "a") {
    return "s01";
  } else if (key == "b") {
    return "s05";
  } else if (key == "c") {
    return "s10";
  } else {
    return "s20";
  }
}

void driveServo(String key, String target) {
  if (key == "a" || key == "b" || key == "c" || key == "d") {
    return;
  }
  int deg_key = key.toInt();
  if (deg_key < 0 || deg_key > 7) {
    return;
  }
  Serial.println(deg_key);

  if (target == "s01" && servo_deg[0][deg_key] != 999) {
    s01.write(servo_deg[0][deg_key]);
  } else if (target == "s05" && servo_deg[1][deg_key] != 999) {
    s05.write(servo_deg[1][deg_key]);
  } else if (target == "s10" && servo_deg[2][deg_key] != 999) {
    s10.write(servo_deg[2][deg_key]);
  } else if (target == "s20" && servo_deg[3][deg_key] != 999) {
    s20.write(servo_deg[3][deg_key]);
  }
}
