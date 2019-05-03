const int ledPin = 4;
const int buzz = 5;
int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
      
 
void setup()
{
  pinMode(buzz, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
}
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");

 if(temperatureF > 38)
 {  
  digitalWrite(buzz, HIGH);

  digitalWrite(ledPin, HIGH);
  
  delay(1000);
  }
  else 
  {
    digitalWrite(buzz, LOW);

    digitalWrite(ledPin, LOW);
    
    delay(1000);
    } 
 delay(1000);                                     
}
