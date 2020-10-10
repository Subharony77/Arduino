int SensorData[8];
int error = 0, diff = 0, intg = 0, last_error = 0, spd = 0, weight = 0;
int kp = 0, ki = 0, kd = 0;
const char SensorPin[8]={2,4,7,8,10,11,12,13};
const char MotorPin[4]={3,5,6,9};
const int min_speed = 150;
int MotorSpeed[4] = {0, 0, 0, 0};
int limit[2] = {-9, 9};
void SensorRead()
{
  error = 0;
  for(int i=0;i<8;i++)
  {
    if(i <= 4) weight = i - 5;
    else weight = i- 4;
    SensorData[i] = digitalRead(SensorPin[i]);
    error = error + (weight * SensorData[i]);
  }
}

void pid()
{
  SensorRead();
  intg = intg + error;
  if(intg > 200) intg = 200;
  else if(intg < -200) intg = -200;
  diff = error - last_error;
  last_error = error;
  spd = (kp * error) + (ki * intg) + (kd * diff);
  motion();
}

void motion()
{
  if(spd >= 0)
  {
    MotorSpeed[0] = min_speed + spd;
  }
  else
  {
    MotorSpeed[2] = min_speed - spd;
  }
  for(int i=0;i<4;i++) analogWrite(MotorPin[i],MotorSpeed[i]); 
}

void move_left()
{
  MotorSpeed[0] = min_speed; 
  MotorSpeed[2] = min_speed;
  for(int i=0;i<4;i++) analogWrite(MotorPin[i],MotorSpeed[i]);
  delay(200);
  MotorSpeed[1] = min_speed;
  MotorSpeed[2] = min_speed;
l1: SensorRead();
    for(int i=0;i<4;i++) analogWrite(MotorPin[i],MotorSpeed[i]);
    if(error < -1) goto l1;  
}

void move_right()
{
  MotorSpeed[0] = min_speed; 
  MotorSpeed[2] = min_speed;
  for(int i=0;i<4;i++) analogWrite(MotorPin[i],MotorSpeed[i]);
  delay(200);
  MotorSpeed[2] = min_speed;
  MotorSpeed[4] = min_speed;
l2: SensorRead();
    for(int i=0;i<4;i++) analogWrite(MotorPin[i],MotorSpeed[i]);
    if(error < 1) goto l2;  
}

void setup() {
  for(int i=0;i<8;i++) pinMode(SensorPin[i],INPUT);
  for(int i=0;i<4;i++) pinMode(MotorPin[i],OUTPUT);
}

void loop() {
  if(error > limit[0] && error < limit[1])
    pid();
  else if(error < limit[0]) move_left();
  else move_right();
}
