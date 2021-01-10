int speaker = 9;
int BEAT = 1000;
int mi = 330;
int so = 392;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  char c = 0;
  // put your main code here, to run repeatedly:
  noTone(speaker);
  if(Serial.available() > 0){
    c = Serial.read();
    if(c == '0'){
      tone(speaker, mi);
      delay(100);
      tone(speaker, so);
      delay(100);
      tone(speaker, 0);
      noTone(speaker);
    }else if(c == '1'){
      digitalWrite(speaker, HIGH);
      tone(speaker, so);
      delay(100);
      tone(speaker, mi);
      delay(100);
      tone(speaker, 0);
      noTone(speaker);
    }
  }
}
