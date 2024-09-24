/*
  Arduino UNO/NANO Selftest V0.3

  Read internally each port value while change the output configutation 
  (floating, pull-up, output low, output high) and try to determine if 
  the port is working properly or if it is damaged.

  Created 23 Sep 2024
  by Simón Plata
  Modified 24 Sep 2024
  by Simón Plata
  
  This code is in the public domain.
*/

void setup() {
  int8_t i;
  int8_t d;
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // print out the version
  Serial.print("Arduino UNO / NANO self test v0.3\n");
  // if you're seing this text is because the serial port is working properly
  Serial.print("Serial Port OK\n");
  // print out the header
  Serial.print("\n");
  Serial.print("PIN I L H\n");
  
  for(i = 2; i <= 19; i++) {
    if(i < 10) { // print out the pin name for D2 to D9
      Serial.print("D");
      Serial.print(i);
      Serial.print("  ");
    }
    else if(i < 14) { // print out the pin name for D10 to D13
      Serial.print("D");
      Serial.print(i);
      Serial.print(" ");
    }
    else { // print out the pin name for A0 to A5
      Serial.print("A");
      Serial.print(i - 14);
      Serial.print("  ");
    }
    // Test for floating Input
    digitalWrite(i, LOW);
    pinMode(i, OUTPUT);
    delay(10);
    pinMode(i, INPUT);
    // read the input value:
    d = digitalRead(i);
    if(d == 0) {
      // 0---
      // Test for Pull-Up Input
      digitalWrite(i, HIGH);
      pinMode(i, INPUT_PULLUP);
      // read the input value:
      d = digitalRead(i);
      if(d == 1) {
        // 01--
        // Input is Ok
        Serial.print("* ");
        // Test for Output Low
        digitalWrite(i, LOW);
        pinMode(i, OUTPUT);
        // read the input value:
        d = digitalRead(i);
        if(d == 0) {
          // 010-
          // Output Low Side is Ok
          Serial.print("* ");
          // Test for Output High
          digitalWrite(i, HIGH);
          // read the input value:
          d = digitalRead(i);
          if(d == 1) {
            // 0101
            pinMode(i, INPUT);
            // Output High Side is Ok
            Serial.print("* ");
            // Test Passed
            Serial.print("PORT is OK\n");
          }
          else {
            // 0100
            pinMode(i, INPUT);
            // Output High Side Damage
            Serial.print("x ");
            // Test Failed
            Serial.print("PORT Output is Damaged\n");
          }
        }
        else {
          // 011-
          pinMode(i, INPUT);
          // Output Low Side Damage
          Serial.print("x ? ");
          // Test Failed
          Serial.print("PORT Output is Damaged\n");
        }
      }
      else {
        // 00--
        // Pin probably Stuck at Low
        // Test for output low
        digitalWrite(i, LOW);
        pinMode(i, OUTPUT);
        // read the input value:
        d = digitalRead(i);
        if(d == 0) {
          // 000-
          // Output Low Side Damaged?
          // Test for Output High
          digitalWrite(i, HIGH);
          // read the input value:
          d = digitalRead(i);
          if(d == 1) {
            // 0001
            pinMode(i, INPUT);
            // Output High Side Ok
            Serial.print("* ? * ");
            // Test Passed with problems
            Serial.print("PORT is OK - But Pulled-Down\n");
          }
          else {
            // 0000
            pinMode(i, INPUT);
            // Output High Side Damage or Input Damage
            Serial.print("? ? ? ");
            // Test failed
            Serial.print("PORT Input or Output is Damaged\n");
          }
        }
        else {
          // 001-
          pinMode(i, INPUT);
          // Output Low Side Damage
          Serial.print("* x ? ");
          // Test failed
          Serial.print("PORT Output is Damaged\n");
        }
      }
    }
    else {
      // 1---
      // Probably Stuck at high
      // Input ?
      // Test for Output Low
      digitalWrite(i, LOW);
      pinMode(i, OUTPUT);
      // read the input value:
      d = digitalRead(i);
      if(d == 0) {
        // 1X0-
        // Output Low Side Ok - Input Ok
        Serial.print("* * ");
        // Test for Output High
        digitalWrite(i, HIGH);
        d = digitalRead(i);
        if(d == 1) {
          // 1X01
          pinMode(i, INPUT);
          // Output High Side Ok
          Serial.print("? ");
          // Test Passed
          Serial.print("PORT is OK - But Pulled-Up\n");
        }
        else {
          // 1X00
          pinMode(i, INPUT);
          // Output High Side Damage
          Serial.print("x ");
          // Test Failed
          Serial.print("PORT Output is Damaged\n");
        }
      }
      else {
        // 1X1-
        pinMode(i, INPUT);
        // Output Low Side Damaged - Input ??
        // Output Low Side Damage or Input Damage
        Serial.print("? ? ? ");
        // Test failed
        Serial.print("PORT Input or Output is Damaged\n");
      }
    }
  }

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
