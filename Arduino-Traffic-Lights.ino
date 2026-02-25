int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7; 
int g = 8; 

int dp = 12;

int green = 9;
int red = 10;
int button = 11;
int buzzer = 13;

int d1 = A0;  //digts(1-4)
int d2 = A1;
int d3 = A2;
int d4 = A3;

int digits [4] = {0,0,1,0};

enum State { IDLE, WARNING_BLINK, COUNTDOWN_RED, GREEN_BLINK };
State currentState = IDLE;
State lastState = IDLE;

unsigned long lastTick = 0;
const unsigned long interval = 1000;

unsigned long stateStartTime = 0; 
unsigned long lastBlinkTime = 0;
unsigned long lastBeepTime = 0;
bool blinkState = false;
bool buzzerState = false;

const unsigned long slowwarn = 500;
const unsigned long fastwarn = 250;

const unsigned long beeptime = 750;

const unsigned long redwarning = 3000;
const unsigned long countdown = 7000;
const unsigned long greenblink = 3000;

int lastButtonState = LOW;

bool buzzerOn = false;
unsigned long buzzerOnTime = 0;
const unsigned long beepLength = 100;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>  //for the lcd display

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:

 pinMode (a, OUTPUT);
 pinMode (b, OUTPUT);
 pinMode (c, OUTPUT);
 pinMode (d, OUTPUT);
 pinMode (e, OUTPUT);
 pinMode (f, OUTPUT);
 pinMode (g, OUTPUT);
 pinMode (dp, OUTPUT);

 pinMode (d1, OUTPUT);
 pinMode (d2, OUTPUT);
 pinMode (d3, OUTPUT);
 pinMode (d4, OUTPUT);

 pinMode (red, OUTPUT);
 pinMode (green, OUTPUT);
 pinMode (buzzer, OUTPUT);
 pinMode (button, INPUT_PULLUP);  //resistor

 digitalWrite (green, LOW);
 digitalWrite (red, HIGH);
 digitalWrite (buzzer, LOW);

 lcd.init();
 lcd.backlight();
 lcd.clear();
}

void decrementNumber() {  //Countdown Logic
digits [3]--;

if (digits[3] < 0) {
digits[3] = 9;
digits[2]--;

 if (digits[2] < 0) {
  digits[2] = 9;
  digits[1]--;

   if (digits[1] < 0) {
    digits[1] = 9;
    digits[0]--; 

     if (digits[0] < 0) {

      digits[0] = 0;
      digits[1] = 0;
      digits[2] = 0;
      digits[3] = 0;
     }
    }
   }
  }
 }

void allSegmentsOff() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, HIGH);
}

void show0 () { 
  digitalWrite (a, LOW);
  digitalWrite (b, LOW);
  digitalWrite (c, LOW);
  digitalWrite (d, LOW);
  digitalWrite (e, LOW);
  digitalWrite (f, LOW);
  digitalWrite (g, HIGH);
  digitalWrite (dp, HIGH);
}

void digitsoff () {
  digitalWrite (d1, LOW);
  digitalWrite (d2, LOW);
  digitalWrite (d3, LOW);
  digitalWrite (d4, LOW);
}

void showDigits(int n) {
allSegmentsOff();

switch (n) {
  case 0:
  digitalWrite (a, LOW);
  digitalWrite (b, LOW);
  digitalWrite (c, LOW);
  digitalWrite (d, LOW);
  digitalWrite (e, LOW);
  digitalWrite (f, LOW);
  break;

  case 1:
  digitalWrite (b, LOW);
  digitalWrite (c, LOW);
  break;

  case 2:
  digitalWrite (a, LOW);
  digitalWrite (b, LOW);
  digitalWrite (d, LOW);
  digitalWrite (e, LOW);
  digitalWrite (g, LOW);
  break;

  case 3:
  digitalWrite (a, LOW);
  digitalWrite (b, LOW);
  digitalWrite (d, LOW);
  digitalWrite (c, LOW);
  digitalWrite (g, LOW);
  break;

  case 4:
  digitalWrite (f, LOW);
  digitalWrite (b, LOW);
  digitalWrite (c, LOW);
  digitalWrite (g, LOW);
  break;

  case 5:
  digitalWrite (f, LOW);
  digitalWrite (d, LOW);
  digitalWrite (a, LOW);
  digitalWrite (c, LOW);
  digitalWrite (g, LOW);
  break;

  case 6: 
  digitalWrite (f, LOW);
  digitalWrite (d, LOW);
  digitalWrite (a, LOW);
  digitalWrite (c, LOW);
  digitalWrite (e, LOW);
  digitalWrite (g, LOW);
  break;

  case 7:
  digitalWrite (a, LOW);
  digitalWrite (b, LOW);
  digitalWrite (c, LOW);
  break;

  case 8:
  digitalWrite (b, LOW);
  digitalWrite (f, LOW);
  digitalWrite (d, LOW);
  digitalWrite (a, LOW);
  digitalWrite (c, LOW);
  digitalWrite (e, LOW);
  digitalWrite (g, LOW);
  break;

  case 9: 
  digitalWrite (f, LOW);
  digitalWrite (d, LOW);
  digitalWrite (a, LOW);
  digitalWrite (c, LOW);
  digitalWrite (b, LOW);
  digitalWrite (g, LOW);
  break;
}
}

void updateLCDtime() {  //Timer on LCD
  lcd.setCursor (0,1);
  lcd.print ("TIME:  ");
  
  lcd.print (digits[0]);
  lcd.print (digits[1]);
  lcd.print (":");
  lcd.print (digits[2]);
  lcd.print (digits[3]);
  lcd.print ("     ");
}

void updateLCDState() {
  lcd.clear();

  switch (currentState) {
    case IDLE:
      lcd.setCursor(0,0);
      lcd.print("DON'T WALK");
      lcd.setCursor(0,1);
      lcd.print("Press Button");
      break;

    case WARNING_BLINK:
      lcd.setCursor(0,0);
      lcd.print("WAIT...");
      lcd.setCursor(0,1);
      lcd.print("Get Ready");
      break;

    case COUNTDOWN_RED:
      lcd.setCursor(0,0);
      lcd.print("WALK");
      lcd.setCursor(0,1);
      lcd.print("TIME: ");
      break;

    case GREEN_BLINK:
      lcd.setCursor(0,0);
      lcd.print("HURRY UP!");
      lcd.setCursor(0,1);
      lcd.print("TIME: ");
      break;
  }
}

void loop() {

  int buttonState = digitalRead (button);
  if (currentState == IDLE && buttonState == LOW) {
    
    digits[0] = 0;
    digits[1] = 0;
    digits[2] = 1;
    digits[3] = 0;

  currentState = WARNING_BLINK; 
  stateStartTime = millis();
  lastBlinkTime = millis();
  
  digitalWrite (red, HIGH);
  digitalWrite (green, LOW);
  digitalWrite (buzzer, LOW);
  }

unsigned long now = millis();

switch (currentState) { 

  case IDLE:  //stable red light
  lcd.setCursor (0,0);
  lcd.print ("DON'T WALK                ");  //spaces to clear out the empty space
  lcd.setCursor (0,1);
  lcd.print ("PRESS BUTTON              ");
  break;

  case WARNING_BLINK: { //red light blinks
    lcd.setCursor(0,0);
    lcd.print("WAIT...           ");
    lcd.setCursor(0,1);
    lcd.print ("GET READY        ");

  unsigned long elapsed = now - stateStartTime;
  unsigned long blinkInterval = (elapsed < redwarning / 2) ? slowwarn:fastwarn;

  if (now - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = now;
    blinkState = !blinkState;
    digitalWrite (red, blinkState ? HIGH : LOW);
  }
  if (elapsed >= redwarning) {
    currentState = COUNTDOWN_RED;
    stateStartTime = now;
    lastBeepTime = now;

    digits[0] = 0;
    digits[1] = 0;
    digits[2] = 1;
    digits[3] = 0;

    digitalWrite (red, LOW);
    digitalWrite (green, HIGH);
    digitalWrite (buzzer, LOW);
  }
  break;
}

case COUNTDOWN_RED: {  //green light turns on. countdown begins
  lcd.setCursor (0,0);
  lcd.print ("WALK                 ");  

 if (now - lastBeepTime >= beeptime) {
  lastBeepTime = now;
  buzzerOn = true;
  buzzerOnTime = now;
  digitalWrite (buzzer, HIGH);
 }

 if (buzzerOn && now - buzzerOnTime >= beepLength) {
  buzzerOn = false;
  digitalWrite (buzzer, LOW);
 }

 if (now - lastTick >= interval) {
  lastTick = now;
  decrementNumber();
  updateLCDtime();
 }

 if (now - stateStartTime >= countdown) {
  currentState = GREEN_BLINK;
  stateStartTime = now;
  lastBlinkTime = now;
  blinkState = false;
 }
break;
}

case GREEN_BLINK: {  //green light about to turn off. starts blinking.
  lcd.setCursor (0,0);
  lcd.print ("HURRY UP!           ");

 if (now - lastBeepTime >= beeptime) {
  lastBeepTime = now;
  buzzerOn = true;
  buzzerOnTime = now;
  digitalWrite (buzzer, HIGH);
 }

 if (buzzerOn && now - buzzerOnTime >= beepLength) {
  buzzerOn = false;
  digitalWrite (buzzer, LOW);
 }

  if (now - lastBlinkTime >= 250) {
    lastBlinkTime = now;
    blinkState = !blinkState;
    digitalWrite (green, blinkState ? HIGH : LOW);
  }
  if (now - lastTick >= interval) {
  lastTick = now;
  decrementNumber();
  updateLCDtime();
  }

  if (now - stateStartTime >= greenblink) {
    currentState = IDLE;
    
    digitalWrite (green, LOW);
    digitalWrite (red, HIGH);
    digitalWrite (buzzer, LOW);

    digits[0] = 0;
    digits[1] = 0;
    digits[2] = 0;
    digits[3] = 0;

  if (currentState != lastState) {
  lastState = currentState;
  updateLCDState();  
}
  }
  break;
 }
}

  digitsoff();  //multiplexing. important for the 7 segment display
  showDigits(digits[0]);
  digitalWrite(d1, HIGH);
  delay(2);

  digitsoff();
  showDigits(digits[1]);
  digitalWrite(d2, HIGH);
  delay(2);

  digitsoff();
  showDigits(digits[2]);
  digitalWrite(d3, HIGH);
  delay (2);

  digitsoff();
  showDigits(digits[3]);
  digitalWrite(d4, HIGH);
  delay (2);
}