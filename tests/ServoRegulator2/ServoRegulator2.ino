#include <Servo.h>

Servo servo;

void setup()
{
  servo.attach(3);
  Serial.begin(9600);
}


int dir = 1;
int pos = 0;


void velocity(int n){
  int done = 0;
  while(true){
    if ((pos > 180) || (pos < 0))
    {
      if (done){
        break;
      }
      dir = !dir;
      done = 1;
    }
    if (dir)
    {
      pos+= n;
    }
    else
    {
      pos-= n;
    }
    servo.write(pos);
    Serial.println("Servo Position (variable): "+ String(pos));
    Serial.println("Servo Position (library): "+ String(servo.read() ) );
    //Serial.print("");
    delay(50);
  }
}



void loop()
{
  int n_max = 20;
  for(int i=1; i<n_max; i+=1){
    velocity(i);
    Serial.print("Step size: ");
    Serial.println(i);
  }
}
