void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int num;
  // put your main code here, to run repeatedly:
  if(num = Serial.read() == -1){
    digitalWrite(2, LOW);
    delay(1000);
  }else{
    Serial.println(num);
    digitalWrite(2, HIGH);
    delay(250);
    digitalWrite(2, LOW);
    delay(250);
    digitalWrite(2, HIGH);
    delay(250);
    digitalWrite(2, LOW);
    delay(250);
  }

  digitalWrite(2, LOW);
}
