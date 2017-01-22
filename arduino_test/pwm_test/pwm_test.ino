/* RGB Analog Example, Teensyduino Tutorial #2
   http://www.pjrc.com/teensy/tutorial2.html

   This example code is in the public domain.
*/

const int yellowPin = 2;
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

void setup()   {                
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void loop()                     
{
  analogWrite(yellowPin, 40);
  delay(500);
  analogWrite(redPin, 40);
  delay(500);
  analogWrite(greenPin, 40);
  delay(500);
  analogWrite(bluePin, 40);
  delay(500);
  analogWrite(yellowPin, 150);
  delay(500);
  analogWrite(redPin, 150);
  delay(500);
  analogWrite(greenPin, 150);
  delay(500);
  analogWrite(bluePin, 150);
  delay(500);
}

