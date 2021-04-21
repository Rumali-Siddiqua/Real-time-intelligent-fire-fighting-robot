#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <Servo.h>
Servo myservo;


float get_temperature(int pin) {
  float voltage = analogRead(pin);
  float temperature = voltage * 10 * (5.0 / 1024);
  return temperature;
}


int motor = 10;
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 13;
int temp = A0;
int smoke = A1;
int buzz = A2;
float tempC = 0;
float tempF = 0;
int smokeRead;
char Reading;
int Ladder = 0;
int k = 0;


void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(motor, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(temp, INPUT);
  pinMode(smoke, INPUT);
  pinMode(buzz, OUTPUT);
}


void loop() {
  if (Serial.available()) {
    Reading = Serial.read();
    switch (Reading) {
      
      case 'F':
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        lcd.setCursor(0, 1);
        lcd.print("     FORWARD    ");
        break;
      
      case 'B':
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("    BACKWARD    ");
        break;
      
      case 'L':
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        lcd.setCursor(0, 1);
        lcd.print("   LEFT TURN    ");
        break;
      
      case 'R':
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        lcd.setCursor(0, 1);
        lcd.print("  RIGHT TURN   ");
        break;
      
      case 'U':
        myservo.write(Ladder);
        Ladder = Ladder + 1;
        lcd.setCursor(0, 1);
        lcd.print("   LADDER UP    ");
        if (Ladder == 160) {
          lcd.setCursor(0, 1);
          lcd.print("   DEAD END     ");
          break;
        }
        break;
      
      case 'D':
        myservo.write(Ladder);
        Ladder = Ladder - 1;
        lcd.setCursor(0, 1);
        lcd.print("   LADDER DOWN  ");
        if (Ladder == 20) {
          lcd.setCursor(0, 1);
          lcd.print("   DEAD END     ");
          break;
        }
        break;
      
      case 'M':
        if (Ladder >= 90) {
          digitalWrite(motor, HIGH);
          lcd.setCursor(0, 1);
          lcd.print("  WATER COMING  ");
        }
        break;
      
      case 'S':
        digitalWrite(motor, LOW);
        lcd.setCursor(0, 1);
        lcd.print(" WATER STOPPED  ");
        break;
      
      case 'H':
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        break;
      
      default:
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  BRACU Savior  ");
        lcd.setCursor(0, 1);
        lcd.print("            ");
    }
  }
  
  else {
    smokeRead = analogRead(A1);
    if (smokeRead >= 105) {
      analogWrite(buzz, 200);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" FIRE FIRE FIRE ");
      delay(1000);
      analogWrite(buzz, 0);
    }
    else {
      tempC = get_temperature(temp);
      tempF = (tempC * (9 / 5)) + 32;
      if (k <= 30) {
        if (k <= 20) {
          if (k <= 10) {
            lcd.setCursor(0, 0);
            lcd.print("  BRACU Savior  ");
            k++;
          }
          else {
            lcd.setCursor(0, 0);
            lcd.print("Temp: ");
            lcd.print (tempC, 1); lcd.print(" "); lcd.print("C    ");
            k++;

          }
        }
        else {
          lcd.setCursor(0, 0);
          lcd.print("  BRACU Savior  ");
          k++;
        }
      }

      else {
        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print (tempF, 1); lcd.print(" "); lcd.print("F    ");
        k++;
        if (k == 40) {
          k = 0;
        }
      }
    }
  }
}

