#include <Servo.h>

Servo servo;

void setup()
{
  servo.attach(2);
}


int dir = 1;
int pos = 0;
void loop()
{
  servo.write(pos);
  if ((pos > 180) || (pos < 0))
  {
    dir = !dir;
  }
  if (dir)
  {
    pos++;
  }
  else
  {
    pos--;
  }
  delay(50);
}
