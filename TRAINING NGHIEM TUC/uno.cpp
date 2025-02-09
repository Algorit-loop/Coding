// C++ code
//
void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  while (true){
    for (int i = 11; i <= 13; i++){
        digitalWrite(i, HIGH);
        delay(100); // Wait for 100 millisecond(s)
        digitalWrite(i, LOW);
        delay(100); // Wait for 100 millisecond(s)
    }
    for (int i = 13; i >= 11; i--){
        digitalWrite(i, HIGH);
        delay(100); // Wait for 100 millisecond(s)
        digitalWrite(i, LOW);
        delay(100); // Wait for 100 millisecond(s)
    }
  }
}