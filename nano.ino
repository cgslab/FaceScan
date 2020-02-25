const int Shutter = 0;
const int Focus = 2;
const int Shutter_out = 3;
const int Forcus_out = 4;
const int Light_PL0 = 11;
const int Light_PL90 = 12;
const int Mode_selecter = 5;
const int Mode_Light = 6;
int light_count = 1 ;

void setup() {
  Serial.begin(9600);
  pinMode(Focus, INPUT_PULLUP);
  pinMode(Forcus_out, OUTPUT);
  pinMode(Shutter, INPUT_PULLUP);
  pinMode(Shutter_out, OUTPUT);
  pinMode(Light_PL0, OUTPUT);
  pinMode(Light_PL90, OUTPUT);
  pinMode(Mode_selecter, INPUT_PULLUP);
  pinMode(Mode_Light, INPUT_PULLUP);

  digitalWrite(Forcus_out, LOW);
  digitalWrite(Shutter_out, LOW);
  digitalWrite(Light_PL0, LOW);
  digitalWrite(Light_PL90, LOW);
}

void loop() {
  //ライトの点灯モード
  if (digitalRead(Mode_Light) == LOW) {
    light_count++;
    switch (light_count) {
      case 1:
        digitalWrite(Light_PL0, LOW);
        digitalWrite(Light_PL90, HIGH);
          Serial.println("Light MODE 1");
        break;
      case 2:
        digitalWrite(Light_PL90, LOW);
        digitalWrite(Light_PL0, HIGH);
        Serial.println("Light MODE 2");
        break;
      default:
        digitalWrite(Light_PL0, LOW);
        light_count = 0;
        Serial.println("Light MODE D");
    }
    delay(500);
  }
  // モードチェック
  Serial.println("---------------");
  if (digitalRead(Mode_selecter) == HIGH) {
    // フォーカスチェック
    Serial.println("======================");
    if (digitalRead(Focus) == HIGH) {
      Serial.println("Focus_ON");
      digitalWrite(Forcus_out, HIGH);
      delay(100);
    } else {
      digitalWrite(Forcus_out, LOW);
      Serial.println("Focus_OFF");
    }
    Serial.println("Mode_selecter HIGH");
    // シャッターチェック
    if (digitalRead(Shutter) == LOW) {
      LightShot();
    } else {
      digitalWrite(Light_PL0, LOW);
      digitalWrite(Light_PL90, LOW);
    }
  } else {
    // フォーカスチェック
    Serial.println("======================");
    if (digitalRead(Focus) == LOW) {
      Serial.println("Focus_ON");
      digitalWrite(Forcus_out, HIGH);
      delay(100);
    } else {
      digitalWrite(Forcus_out, LOW);
      Serial.println("Focus_OFF");
    }
    Serial.println("Mode_selecter LOW");
    // シャッターチェック
    if (digitalRead(Shutter) == LOW) {
      Shot();
    } else {
      digitalWrite(Shutter_out, LOW);
    }
  }
}

int LightShot() {
  digitalWrite(Light_PL0, HIGH);
  delay(200);
  Shot();
  digitalWrite(Light_PL0, LOW);
  delay(200);
  digitalWrite(Light_PL90, HIGH);
  delay(200);
  Shot();
  digitalWrite(Light_PL90, LOW);
  delay(500);
}

int Shot() {
  Serial.println("Shot");
  digitalWrite(Shutter_out, HIGH);
  delay(100);
  digitalWrite(Shutter_out, LOW);
  delay(200);
}
