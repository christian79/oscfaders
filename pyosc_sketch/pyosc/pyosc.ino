#include <LiquidCrystal595.h>
LiquidCrystal595 lcd(7,8,9);     // datapin, latchpin, clockpin

int X;
int Y;

byte ledPin1 = 10;
byte ledPin2 = 11;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  lcd.begin(16,2);             // 16 characters, 2 rows
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("hello");
  delay(500);
  lcd.clear();
}

void loop()
{
  if (Serial.available() > 0)
  {
    char syncChar = Serial.read();
    if (syncChar == 'X')
    {
      X = Serial.parseInt();
      lcd.setCursor(0,0);
      lcd.print("x: ");
      lcd.print(X);
      analogWrite(ledPin1, X);
      Serial1.print("X: ");
      Serial1.println(X);
    }
    if (syncChar == 'Y')
    {
      lcd.setCursor(0,1);
      lcd.print("y: ");
      lcd.print(Y);
      analogWrite(ledPin2, Y);
      Serial1.print("Y: ");
      Serial1.println(Y);
    }
    Serial.read();
    lcd.clear();
  }
}
