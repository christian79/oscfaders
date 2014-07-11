int X;
int Y;

void setup()
{
  Serial1.begin(115200); 
}

void loop()
{
  if (Serial.available() > 0)
  {
    char syncChar = Serial.read();
    if (syncChar == 'X')
    {
      X = Serial.parseInt();
      Serial.print("X: ");
      Serial.println(X);
    }
    if (syncChar == 'Y')
    {
      Y = Serial.parseInt();
      Serial.print("Y: ");
      Serial.println(Y);
    }
    Serial.read();
  }
}
