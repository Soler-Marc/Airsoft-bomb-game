#include <Keypad.h>
#include <LiquidCrystal.h>
//www.brilliantlyeasy.com/
#include <ctype.h>
char* secretCode = "1819";
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
// Define the keymaps.  The blank spot (lower left) is the space character.

char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};


byte rowPins[ROWS] = {6, 5, 4, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, A4, A5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int pos = 0;
int right = 0;
int minutes = 0; //start min
int seconds = 30;//start seconds
int seconds2 = 2;//start seconds
int seconds3 = 30;//start seconds
int seconds4 = 1;//start seconds
int mil = 0;//start mil
int mil2 = 0;//start mil
int mil3 = 0;//start mil
int mil4 = 0;//start mil
int pushButtonG = A2;
int pushButtonR = A1;
int pushButtonB = A0;
int pushButtonY = A3;

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //<--removed- Different LCD manufacture
LiquidCrystal lcd(11, 12, 7, 8, 9, 10);//Pin Code for Arduino SainSmart LCD 1602 KeyPad

void setup() {

  Serial.begin(9600);
  pinMode(pushButtonG, INPUT);
  pinMode(pushButtonR, INPUT);
  pinMode(pushButtonB, INPUT);
  pinMode(pushButtonY, INPUT);
  lcd.begin(16, 2);
  lcd.print(" Insert CODE");
}

void loop() {
  int buttonStateG = LOW;
  int buttonStateR = LOW;
  int buttonStateB = LOW;
  int buttonStateY = LOW;
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    if (key == '*' || key == '#') {
      pos = 0;
      right = 0;
      setLocked(0);
      Serial.println("Door locked");
    } else if (key == secretCode[pos]) {
      pos++;
      right++;
    } else {
      pos++;
    }

    if (pos == 4) {
      if (right == pos) {
        setLocked(2);

        lcd.begin(16, 2);
        lcd.print(" DETONATION  IN ");

        // lcd.scrollDisplayLeft();
        // wait a bit:
        delay(150);

        while (minutes > 0 || seconds > 0 || mil >= 0) {

          lcd.setCursor(4, 2);

          (minutes < 10) ? lcd.print("0") : NULL;
          lcd.print(minutes);
          lcd.print(":");
          (seconds < 10) ? lcd.print("0") : NULL;
          lcd.print(seconds);
          lcd.print(":");
          (mil < 10) ? lcd.print("0") : NULL;
          lcd.print(mil);
          lcd.display();
          stepDown();
          delay(10);
          while (buttonStateG == LOW && buttonStateR == LOW && buttonStateB == LOW && buttonStateY == LOW ) {

            buttonStateG = digitalRead(pushButtonG);
            buttonStateR = digitalRead(pushButtonR);
            buttonStateB = digitalRead(pushButtonB);
            buttonStateY = digitalRead(pushButtonY);

            lcd.setCursor(4, 2);

            (minutes < 10) ? lcd.print("0") : NULL;
            lcd.print(minutes);
            lcd.print(":");
            (seconds < 10) ? lcd.print("0") : NULL;
            lcd.print(seconds);
            lcd.print(":");
            (mil < 10) ? lcd.print("0") : NULL;
            lcd.print(mil);
            lcd.display();
            stepDown();
            delay(10);
          }
          if (buttonStateG == HIGH) {



            while (true) {}
            // print out the state of the button:
          } else if (buttonStateR == HIGH ) {

            lcd.begin(16, 2);
            lcd.print(" DETONATION  IN ");
            delay(150);

            while (minutes > 0 || seconds > 0 || mil3 >= 0) {

              lcd.setCursor(4, 2);

              (minutes < 10) ? lcd.print("0") : NULL;
              lcd.print(minutes);
              lcd.print(":");
              (seconds < 10) ? lcd.print("0") : NULL;
              lcd.print(seconds + seconds3);
              lcd.print(":");
              (mil3 < 10) ? lcd.print("0") : NULL;
              lcd.print(mil3);
              lcd.display();
              stepDown3();
              delay(10);
            }
          } else if  (buttonStateB == HIGH) {
            while(true){
            
             lcd.begin(16, 2);
            lcd.print(" TERRORIST WIN");
              
            }
          } else if (buttonStateY == HIGH) {
            lcd.begin(16, 2);
            lcd.print(" DETONATION  IN ");

            // lcd.scrollDisplayLeft();
            // wait a bit:
            delay(150);

            while (minutes > 0 || seconds4 > 0 || mil4 >= 0) {

              lcd.setCursor(4, 2);

              (minutes < 10) ? lcd.print("0") : NULL;
              lcd.print(minutes);
              lcd.print(":");
              (seconds4 < 10) ? lcd.print("0") : NULL;
              lcd.print(seconds4);
              lcd.print(":");
              (mil4 < 10) ? lcd.print("0") : NULL;
              lcd.print(mil4);
              lcd.display();
              stepDown4();
              delay(10);
            }
          }
        }

      } else {
        setLocked(1);
        while (minutes > 0 || seconds2 > 0 || mil2 >= 0) {

          lcd.setCursor(4, 2);

          (minutes < 10) ? lcd.print("0") : NULL;
          lcd.print(minutes);
          lcd.print(":");
          (seconds2 < 10) ? lcd.print("0") : NULL;
          lcd.print(seconds2);
          lcd.print(":");
          (mil2 < 10) ? lcd.print("0") : NULL;
          lcd.print(mil2);
          lcd.display();
          stepDown2();
          delay(10);
        }
      }
    }

  }



}

void stepDown() {
  if (mil > 0) {
    mil -= 1;
  } else {
    if (seconds > 0) {
      mil = 99;
      seconds -= 1;
    } else {
      if (minutes > 0) {
        mil = 99;
        seconds = 59;
        minutes -= 1;
      } else {
        trigger();
      }
    }
  }
}

void trigger() {
  lcd.clear(); // clears the screen and buffer
  lcd.setCursor(3, 1); // set timer position on lcd for end.

  lcd.println("BYE BYE!");
  delay(1000);

  lcd.display();
}
void setLocked(int state) {
  if (state == 0) {

    Serial.println("Door waiting");
  } else if (state == 1) {

    Serial.println("Door alarm");
  }  else {

    Serial.println("Door opened!");
  }
}
void stepDown2() {
  if (mil2 > 0) {
    mil2 -= 1;
  } else {
    if (seconds2 > 0) {
      mil2 = 99;
      seconds2 -= 1;
    } else {
      if (minutes > 0) {
        mil2 = 99;
        seconds2 = 59;
        minutes -= 1;
      } else {
        trigger2();
      }
    }
  }
}

void trigger2() {
  lcd.clear(); // clears the screen and buffer
  lcd.setCursor(3, 1); // set timer position on lcd for end.

  lcd.println("BYE BYE!");
  delay(1000);

  lcd.display();
}
void stepDown3() {
  if (mil3 > 0) {
    mil3 -= 1;
  } else {
    if (seconds3 > 0) {
      mil3 = 99;
      seconds3 -= 1;
    } else {
      if (minutes > 0) {
        mil3 = 99;
        seconds3 = 59;
        minutes -= 1;
      } else {
        trigger3();
      }
    }
  }
}

void trigger3() {
  lcd.clear(); // clears the screen and buffer
  lcd.setCursor(3, 1); // set timer position on lcd for end.

  lcd.println("BYE BYE!");
  delay(1000);

  lcd.display();
}
void stepDown4() {
  if (mil4 > 0) {
    mil4 -= 1;
  } else {
    if (seconds4 > 0) {
      mil4 = 99;
      seconds4 -= 1;
    } else {
      if (minutes > 0) {
        mil4 = 99;
        seconds4 = 59;
        minutes -= 1;
      } else {
        trigger4();
      }
    }
  }
}

void trigger4() {
  lcd.clear(); // clears the screen and buffer
  lcd.setCursor(3, 1); // set timer position on lcd for end.

  lcd.println("BYE BYE!");
  delay(1000);

  lcd.display();
}
