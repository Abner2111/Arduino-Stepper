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

int calibrated = 18;
int right      = 19;
int up         = 20;
int left       = 21;
int down       = 22;

const int stepsPerRotation = 512;
const int stepperdelay = 1000;

int prevCalibrated = 0;
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
  write(0,0,0,0, coord);
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
  write(0,0,0,0, coord);
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
  
  pinMode(calibrated, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);

  delay(500);
}

void loop(){
  if (prevCalibrated != digitalRead(calibrated)){
    if(digitalRead(calibrated)){
      negstep(stepsPerRotation/6, 2);
      step(stepsPerRotation/6+5, 2);
    }
    prevCalibrated = digitalRead(calibrated);
  }
  else if(digitalRead(calibrated)){
    
    for (int i = 0; i<=stepsPerRotation*3.5;i++){
        if (!digitalRead(calibrated)){
          break;
        }
        negstep(1, 1);
        step(1, 0);
        
        
    }
    delay(1000);

    for (int i = 0; i<=stepsPerRotation*3.5;i++){
        if (!digitalRead(calibrated)){
          break;
        }
        step(1, 1);
        negstep(1, 0);
        
        
    }
    delay(1000);
  } else {
    digitalWrite(IN1z,0);
    digitalWrite(IN2z,0);
    digitalWrite(IN3z,0);
    digitalWrite(IN4z,0);
    if(digitalRead(up)){
      step(1,1);
    } else if(digitalRead(down)) {
      negstep(1,1);
    } if(digitalRead(right)) {
      step(1,0);
    } else if(digitalRead(left)) {
      negstep(1,0);
    }
  }
  
}