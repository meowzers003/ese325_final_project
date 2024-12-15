int ledA = 6;
int sensorPin = A5;
int sensorValue;
int interval = 100;  // ms
int mode = 0;   // 0 for normal mode, 1 for alarm mode
int threshold = 400;
int start_check = 0;
int light_detect = 0;

unsigned long start_time = 0; //start of detection
unsigned long end_time = 0; //end of detection
unsigned long indicator_time = 0; //amount of time LED is on for after detecting light

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(ledA, OUTPUT);
  pinMode(sensorPin, OUTPUT);
  Serial.begin(19200);
}
 
// the loop routine runs over and over again forever:
void loop() {
  if (mode == 0) {  // no emitting
    digitalWrite(ledA, LOW);
    digitalWrite(sensorPin, LOW);
  }
  else {
    if((light_detect == 1) && (start_check == 1)){
      digitalWrite(ledA, HIGH);  // emitting
      digitalWrite(sensorPin, LOW);
      delay(indicator_time);
      Serial.print("light detected for: ");
      Serial.println(indicator_time);
      light_detect = 0;
      start_time = 0;
      end_time = 0;
      start_check = 0;
    }

    digitalWrite(ledA, LOW);
    digitalWrite(sensorPin, LOW);
  }
  delay(interval);
 
  digitalWrite(ledA, LOW);  // charging
  digitalWrite(sensorPin, HIGH);
  delay(interval/2);
 
  pinMode(sensorPin, INPUT);  // discharging
  delay(interval/2);
  sensorValue = analogRead(sensorPin);  // value after certain time
  Serial.print("value: ");
  Serial.println(sensorValue);
 
  if (sensorValue < threshold){ //light detected
    mode = 0;
    if((!start_check)){
      start_check = 1; //start time count
      start_time = millis();
    } 
  }  // quick discharging (detected light)
  else{
    mode = 0;
    if(start_check && (light_detect == 0)){
      end_time = millis();
      indicator_time = end_time - start_time;
      mode = 1;      // slow discharging
      light_detect = 1;
    }
  } 
 
  pinMode(sensorPin, OUTPUT);
 
}
