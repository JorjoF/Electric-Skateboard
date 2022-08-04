const int ANALOGUE_MIN_X = 90;
const int ANALOGUE_MID_X = 495;
const int ANALOGUE_MAX_X = 920;
const int X_DEADZONE_MIN = ANALOGUE_MID_X - 20;
const int X_DEADZONE_MAX = ANALOGUE_MID_X + 20;
const float EMA_a_X = 0.6;

const int ANALOGUE_MIN_Y = 85;
const int ANALOGUE_MID_Y = 518;
const int ANALOGUE_MAX_Y = 885;
const int Y_DEADZONE_MIN = ANALOGUE_MID_Y - 20;
const int Y_DEADZONE_MAX = ANALOGUE_MID_Y + 20;
const float EMA_a_Y = 0.6;

int valX = 0;
int valY = 0;


int analogX(int pin){
  valX = analogRead(pin);

  
  if(valX < X_DEADZONE_MIN){
    valX = map(valX, ANALOGUE_MIN_X, X_DEADZONE_MIN, -255, 0);
  }else if(valX > X_DEADZONE_MAX){ 
    valX = map(valX, X_DEADZONE_MAX, ANALOGUE_MAX_X, 0, 255);
  }else{ 
    valX = 0;
  }
  
  valX = constrain(valX, -255,255);
  
  return valX;
}
int analogY(int pin){
    valY = analogRead(pin);

  if(valY < Y_DEADZONE_MIN){
    valY = map(valY, ANALOGUE_MIN_Y, Y_DEADZONE_MIN, -255, 0);
  }else if(valY > Y_DEADZONE_MAX){ 
    valY = map(valY, Y_DEADZONE_MAX, ANALOGUE_MAX_Y, 0, 255);
  }else{ 
    valY = 0;
  }
  
  valY = constrain(valY, -255,255);
  
  return valY;
}
