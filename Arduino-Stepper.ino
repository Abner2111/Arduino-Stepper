int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
const int stepsPerRotation = 512;
const int stepperdelay = 1000;


void write(int a, int b, int c, int d){
  digitalWrite(IN1,a);
  digitalWrite(IN2,b);
  digitalWrite(IN3,c);
  digitalWrite(IN4,d);
}

//CW step
void onestep(){
  write(1,0,0,0);
  delayMicroseconds(stepperdelay);
  write(1,1,0,0);
  delayMicroseconds(stepperdelay);
  write(0,1,0,0);
  delayMicroseconds(stepperdelay);
  write(0,1,1,0);
  delayMicroseconds(stepperdelay);
  write(0,0,1,0);
  delayMicroseconds(stepperdelay);
  write(0,0,1,1);
  delayMicroseconds(stepperdelay);
  write(0,0,0,1);
  delayMicroseconds(stepperdelay);
  write(1,0,0,1);
  delayMicroseconds(stepperdelay);
}

//ACW step
void negonestep(){
  write(0,0,0,1);
  delayMicroseconds(stepperdelay);
  write(0,0,1,1);
  delayMicroseconds(stepperdelay);
  write(0,0,1,0);
  delayMicroseconds(stepperdelay);
  write(0,1,1,0);
  delayMicroseconds(stepperdelay);
  write(0,1,0,0);
  delayMicroseconds(stepperdelay);
  write(1,1,0,0);
  delayMicroseconds(stepperdelay);
  write(1,0,0,0);
  delayMicroseconds(stepperdelay);
  write(1,0,0,1);
  delayMicroseconds(stepperdelay);
}

//CW turn
void step(int number_of_steps){
  int i;
  i=0;
  while(i<number_of_steps){
    onestep();
    i++;
  }
}

//ACW turn
void negstep(int number_of_steps){
  int i;
  i=0;
  while(i<number_of_steps){
    negonestep();
    i++;
  }
}
void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop(){
  step(stepsPerRotation);
  delay(1000);

  negstep(stepsPerRotation);
  delay(1000);
}