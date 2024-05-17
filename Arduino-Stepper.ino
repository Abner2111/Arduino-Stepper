int IN1z = 13;
int IN2z = 12;
int IN3z = 11;
int IN4z = 10;

int IN1y = 9;
int IN2y = 8;
int IN3y = 7;
int IN4y = 6;

int IN1x = 5;
int IN2x = 4;
int IN3x = 3;
int IN4x = 2;
const int stepsPerRotation = 512;
const int stepperdelay = 1000;


void write(int a, int b, int c, int d, int coord){
  if (coord == 0){
    digitalWrite(IN1x,a);
    digitalWrite(IN2x,b);
    digitalWrite(IN3x,c);
    digitalWrite(IN4x,d);
  } else if (coord == 1) {
    digitalWrite(IN1y,a);
    digitalWrite(IN2y,b);
    digitalWrite(IN3y,c);
    digitalWrite(IN4y,d);
  }
  else if (coord == 2) {
    digitalWrite(IN1z,a);
    digitalWrite(IN2z,b);
    digitalWrite(IN3z,c);
    digitalWrite(IN4z,d);
  }
  
}

//CW step
void onestep(int coord){
  write(1,0,0,0, coord);
  delayMicroseconds(stepperdelay);
  write(1,1,0,0, coord);
  delayMicroseconds(stepperdelay);
  write(0,1,0,0, coord);
  delayMicroseconds(stepperdelay);
  write(0,1,1,0, coord);
  delayMicroseconds(stepperdelay);
  write(0,0,1,0, coord);
  delayMicroseconds(stepperdelay);
  write(0,0,1,1, coord);
  delayMicroseconds(stepperdelay);
  write(0,0,0,1, coord);
  delayMicroseconds(stepperdelay);
  write(1,0,0,1, coord);
  delayMicroseconds(stepperdelay);
}

//ACW step
void negonestep(int coord){
  write(0,0,0,1, coord);
  delayMicroseconds(stepperdelay);
  write(0,0,1,1, coord);
  delayMicroseconds(stepperdelay);
  write(0,0,1,0, coord);
  delayMicroseconds(stepperdelay);
  write(0,1,1,0, coord);
  delayMicroseconds(stepperdelay);
  write(0,1,0,0, coord);
  delayMicroseconds(stepperdelay);
  write(1,1,0,0, coord);
  delayMicroseconds(stepperdelay);
  write(1,0,0,0, coord);
  delayMicroseconds(stepperdelay);
  write(1,0,0,1, coord);
  delayMicroseconds(stepperdelay);
}

//CW turn
void step(int number_of_steps, int coord){
  int i;
  i=0;
  while(i<number_of_steps){
    onestep(coord);
    i++;
  }
}

//ACW turn
void negstep(int number_of_steps, int coord){
  int i;
  i=0;
  while(i<number_of_steps){
    negonestep(coord);
    i++;
  }
}
void setup(){
  pinMode(IN1x, OUTPUT);
  pinMode(IN2x, OUTPUT);
  pinMode(IN3x, OUTPUT);
  pinMode(IN4x, OUTPUT);

  pinMode(IN1y, OUTPUT);
  pinMode(IN2y, OUTPUT);
  pinMode(IN3y, OUTPUT);
  pinMode(IN4y, OUTPUT);

  pinMode(IN1z, OUTPUT);
  pinMode(IN2z, OUTPUT);
  pinMode(IN3z, OUTPUT);
  pinMode(IN4z, OUTPUT);
  delay(5000);
}

void loop(){
  negstep(stepsPerRotation/4, 2);
  step(stepsPerRotation/5, 2);
  for (int i = 0; i<=stepsPerRotation*3.5;i++){
      step(1, 0);
      negstep(1, 1);
  }
  delay(1000);

  for (int i = 0; i<=stepsPerRotation*3.5;i++){
      negstep(1, 0);
      step(1, 1);
  }
  delay(1000);
}