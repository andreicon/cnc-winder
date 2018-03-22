// declare pins

// MOTOR 2 = winder
// MOTOR 1 = guide

#define COMMAND_STOP 's'
#define COMMAND_START 'w'
#define COMMAND_LEFT_GUIDE 'a'
#define COMMAND_RIGHT_GUIDE 'd'
#define COMMAND_START_GUIDE 'q'
#define COMMAND_STOP_GUIDE 'e'

#define COMMAND_SPEED_UP_GUIDE 'p'
#define COMMAND_SLOW_DOWN_GUIDE  'o'

#define COMMAND_SPEED_UP_WINDER  'l'
#define COMMAND_SLOW_DOWN_WINDER 'k'


const int enable1 = 8;
const int dir1 = 2;
const int step1 = 3;

const int enable2 = 9;
const int dir2 = 4;
const int step2 = 5;

const int enable3 = 1;
const int dir3 = 7;
const int step3 = 6;

// set initial State for all pins
int enable1State = HIGH;
int dir1State = LOW;
int step1State = LOW;

int enable2State = HIGH;
int dir2State = LOW;
int step2State = LOW;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

int interval1 = 25000;
int interval2 = 8000;

void speedup_guide() {
  if (interval1 > 8000) {
    interval1 = interval1 - 100;
    Serial.print("rpm winder ");
    Serial.println(interval1); 
  }
}
void slowdown_guide() {
  if (interval1 < 80000) {
    interval1 = interval1 + 100;
    Serial.print("rpm guide ");
    Serial.println(interval1);
  }
}
void speedup_winder() {
  if (interval2 > 1000) {
    interval2 = interval2 - 100;
    Serial.print("rpm winder ");
    Serial.println(interval2);
  }
}
void slowdown_winder() {
  if (interval2 < 10000) {
    interval2 = interval2 + 100;
    Serial.print("rpm winder ");
    Serial.println(interval2);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  
  pinMode(step1, OUTPUT);
  pinMode(step2, OUTPUT);
    
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    char data = (char)Serial.read();
    switch(data) {
      case COMMAND_STOP:
        enable1State = HIGH;
        enable2State = HIGH;
        Serial.println("COMMAND_STOP");
      break;
      case COMMAND_START:
        enable1State = LOW;
        enable2State = LOW;
        Serial.println("COMMAND_START");
      break;
        case COMMAND_LEFT_GUIDE:
        dir1State = HIGH;
        Serial.println("COMMAND_LEFT_GUIDE");
      break;
        case COMMAND_RIGHT_GUIDE:
        dir1State = LOW;
        Serial.println("COMMAND_RIGHT_GUIDE");
      break;
        case COMMAND_START_GUIDE:
        enable1State = LOW;
        Serial.println("COMMAND_START_GUIDE");
      break;
        case COMMAND_STOP_GUIDE:
        enable1State = HIGH;
        Serial.println("COMMAND_STOP_GUIDE");
      break;

      case COMMAND_SPEED_UP_GUIDE:
        speedup_guide();
        Serial.println("COMMAND_SPEED_UP_GUIDE");
      break;
        case COMMAND_SLOW_DOWN_GUIDE:
        slowdown_guide();
      Serial.println("COMMAND_SLOW_DOWN_GUIDE");
      break;

      case COMMAND_SPEED_UP_WINDER:
        speedup_winder();
        Serial.println("COMMAND_SPEED_UP_WINDER");
      break;
      case COMMAND_SLOW_DOWN_WINDER:
        slowdown_winder();
        Serial.println("COMMAND_SLOW_DOWN_WINDER");
      break;
    }
  }
  
  unsigned long currentMillis = micros();

  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;

    if (step1State == LOW) {
      step1State = HIGH;
    } else {
      step1State = LOW;
    }
    digitalWrite(enable1, enable1State);
    digitalWrite(step1, step1State);
    digitalWrite(dir1, dir1State);
  }

  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;
    if (step2State == LOW) {
      step2State = HIGH;
    } else {
      step2State = LOW;
    }
    digitalWrite(enable2, enable2State);
    digitalWrite(step2, step2State);
    digitalWrite(dir2, dir2State);
  }

}
