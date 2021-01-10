const int SW = 8;
const int LED = 13;
int state = 0;
int preState = 0;
boolean buttonState = false;
int speaker = 9;
int BEAT = 1000;
int mi = 330;
int so = 392;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(SW, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(SW);
  if(state && !(preState)){
    if(buttonState){
      buttonState = false;
    }else{
      buttonState = true;
    }
    Serial.println(buttonState ? "true" : "false");
    delay(10);
  }
  preState = state;

  if(buttonState){
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }

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
