#define bounce 20
const int interuptxA = 2;
const int interuptxB = 4;
const int interuptyA = 3;
const int interuptyB = 5;
volatile int x = 0;
volatile int y = 0;
const int dist = 500;
int xAstate, xBstate, yAstate, yBstate;
int xdist = 0, ydist = 0;
bool mat[20][20] = {0};
void Count_pulse_x () {
  xAstate = digitalRead(interuptxA);
  xBstate = digitalRead(interuptxB);
  if (xBstate == xAstate)
    x--;
  else if (xBstate != xAstate)
    x++;
  if (x >= dist)
  {
    xdist = xdist + 1;
    x = 0;
  }
  else if (x <= (-1*dist))
  {
    xdist = xdist - 1;
    x = 0;
  }
}

void Count_pulse_y () {
  yAstate = digitalRead(interuptyA);
  yBstate = digitalRead(interuptyB);
  if (yBstate == yAstate)
    y--;
  else if (yBstate != yAstate)
    y++;
  if (y >= dist)
  {
    ydist = ydist + 1;
    y = 0;
  }
  else if (y <= (-1*dist))
  {
    ydist = ydist - 1;
    y = 0;
  }
}

/*void calc()
{
  if (x >= dist)
  {
    xdist = xdist + 1;
    x = 0;
  }
  else if (x <= (-1*dist))
  {
    xdist = xdist - 1;
    x = 0;
  }
  if (y >= dist)
  {
    ydist = ydist + 1;
    y = 0;
  }
  else if (y <= (-1*dist))
  {
    ydist = ydist - 1;
    y = 0;
  }
}*/

void maping(int xpoint, int ypoint)
{
  xpoint = xpoint + 10;
  ypoint = (-1*ypoint) + 10;
  if(xpoint<20 && xpoint>=0 && ypoint<20 && ypoint>=0)
  {
    mat[ypoint][xpoint]=1;
  }
  /*Serial.print("[2J");
  Serial.print("[H");*/
  for(int i=0;i<20;i++)
  {
    for(int j=0;j<20;j++)
    {
      Serial.print(mat[i][j]);
    }
    Serial.println();
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  pinMode(interuptxA, INPUT);
  digitalWrite(interuptxA, HIGH);
  pinMode(interuptxB, INPUT);
  digitalWrite(interuptxB, HIGH);
  pinMode(interuptyA, INPUT);
  digitalWrite(interuptyA, HIGH);
  pinMode(interuptyB, INPUT);
  digitalWrite(interuptyB, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
 
//  for(int i=0;i<20;i++)
//  {
//    for(int j=0;j<20;j++)
//    {
//      mat[i][j]=0;
//      Serial.println("hi");
//    }
//  }
  
  attachInterrupt(digitalPinToInterrupt(interuptxA), Count_pulse_x, RISING);
  attachInterrupt(digitalPinToInterrupt(interuptyA), Count_pulse_y, RISING);
  
  maping(0,0);
  Serial.println("Setup executed");
}

void loop() {
  //calc();
  Serial.print("pulse_count x:");
  Serial.print('\t');
  Serial.print(x);
  Serial.print("pulse_count y:");
  Serial.print('\t');
  Serial.print(y);
  Serial.print('\t');
  Serial.print("dist: ");
  Serial.print(xdist);
  Serial.print('\t');
  Serial.print(ydist);
  Serial.println();
  maping(xdist,ydist);
}
