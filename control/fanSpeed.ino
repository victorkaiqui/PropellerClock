int pin = 3;    

void setup()  { 
  Serial.begin(9600);
} 

void loop()  { 


  int sensorValue = analogRead(A0);
  int val = map(sensorValue, 0, 1023, 0, 255);
  Serial.println(val);
  analogWrite(pin, val);
  delay(1); 

}