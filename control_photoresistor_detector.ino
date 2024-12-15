/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */
   

//Constants
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin=9;       // Led pin at Arduino pin 9

unsigned long threshold = 650;
//Variables
int value;				  // Store value from photoresistor (0-1023)

unsigned long start_time = 0; //start of detection
unsigned long end_time = 0; //end of detection
unsigned long indicator_time = 0; //amount of time LED is on for after detecting light
 

void setup(){

 pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)

  Serial.begin(19200);

}

void loop(){
  start_time = 0;
  end_time = 0;
  indicator_time = 0;
  value = analogRead(pResistor);
  Serial.print("value: ");
  Serial.println(value); //voltage detected increases as LED
  if (value > threshold){
    Serial.print("Light detected: ");
    start_time = millis(); //get start time
    while(value > threshold){ // keep looping until no longer detecting light 
      value = analogRead(pResistor);
    } 
    end_time = millis();
    indicator_time = end_time - start_time;
    Serial.println(indicator_time); 
    digitalWrite(ledPin, HIGH);  //Turn led on
    delay(indicator_time);
    digitalWrite(ledPin, LOW);  //Turn led on
  }
  else{
    digitalWrite(ledPin, LOW); //Turn led off
  }

  delay(100); //Small delay
}