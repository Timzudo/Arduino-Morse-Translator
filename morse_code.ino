#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buttonPin = 7;     
const int ledPin = 13;


unsigned long startMillis = 0; 
const long holdTime = 1000; 


int currentInput = 0;
unsigned long notPressingMillis = 0;
bool notPressedLong = LOW;

//Queue to eliminate inputs from static and miss clicks
bool inputQueue[5] = {LOW, LOW, LOW, LOW, LOW};


int currentChar[4] = {0, 0, 0, 0};
int currentCharCounter = 0;

String currentText = "";

struct Character {
  char identifier;
  int values[4];  // Array of Morse code values
};

// Initialize each character with its Morse code representation
Character characters[] = {
    {'A', {1, 2, 0, 0}},
    {'B', {2, 1, 1, 1}},
    {'C', {2, 1, 2, 1}},
    {'D', {2, 1, 1, 0}},
    {'E', {1, 0, 0, 0}},
    {'F', {1, 1, 2, 1}},
    {'G', {2, 2, 1, 0}},
    {'H', {1, 1, 1, 1}},
    {'I', {1, 1, 0, 0}},
    {'J', {1, 2, 2, 2}},
    {'K', {2, 1, 2, 0}},
    {'L', {1, 2, 1, 1}},
    {'M', {2, 2, 0, 0}},
    {'N', {2, 1, 0, 0}},
    {'O', {2, 2, 2, 0}},
    {'P', {1, 2, 2, 1}},
    {'Q', {2, 2, 1, 2}},
    {'R', {1, 2, 1, 0}},
    {'S', {1, 1, 1, 0}},
    {'T', {2, 0, 0, 0}},
    {'U', {1, 1, 2, 0}},
    {'V', {1, 1, 1, 2}},
    {'W', {1, 2, 2, 0}},
    {'X', {2, 1, 1, 2}},
    {'Y', {2, 1, 2, 2}},
    {'Z', {2, 2, 1, 1}},
    {' ', {0, 0, 0, 0}}
};

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);     // initialize the pushbutton pin as an input
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  updateQueue(inputQueue, digitalRead(buttonPin));

  if (digitalRead(buttonPin) == HIGH && checkQueue(inputQueue)) {
    notPressingMillis = millis();
    notPressedLong = LOW;

    if (startMillis == 0) {
      startMillis = millis();
    }

    //Button was pressed for 1 second
    if (millis() - startMillis >= holdTime && currentInput == 0) {
      Serial.println("Button was held for 1 second!");
      flashLight();
      currentInput = 1;
    }

    //Button was pressed for 3 seconds
    if (millis() - startMillis >= holdTime * 3 && currentInput != 2) {
      Serial.println("Button was held for 3 seconds!");
      flashLight();
      currentInput = 2;
    }

    //Reset (Button was pressed for 6 seconds)
    if (millis() - startMillis >= holdTime * 6){
      currentInput = 0;
      notPressingMillis = millis();
      notPressedLong = LOW;
      startMillis = 0;
      for (int i = 0; i < 5; i++) {
        inputQueue[i] = LOW;
      }
      for (int i = 0; i < 4; i++) {
        currentChar[i] = 0;
      }
      currentCharCounter = 0;
      currentText = "";

      Serial.println("Reset");
      flashLight();
      lcd.clear();
    }

  } else {
    startMillis = 0;
    if(currentInput != 0){
      updateCurrentChar(currentText, currentChar, currentCharCounter, currentInput);
      currentInput = 0;
    }
    
    //Button was not pressed for 3 seconds
    if (millis() - notPressingMillis >= holdTime * 3 && notPressedLong == LOW){
      Serial.println("Button was not held for 3 seconds!");
      flashLight();
      notPressedLong = HIGH;
      updateCurrentChar(currentText, currentChar, currentCharCounter, 0);
    }
  }
}

void updateQueue(bool queue[], bool input) {
  for (int i = 0; i < 4; i++) {
    queue[i] = queue[i + 1];
  }
  queue[4] = input;
}

bool checkQueue(bool queue[]) {
  for (int i = 0; i < 4; i++) {
    if (queue[i] != queue[i + 1]) {
      return false;
    }
  }
  return true;
}


void updateCurrentChar(String &currentText, int currentChar[], int &counter, int input) {
  currentChar[counter] = input;

  if (input == 0) {
    for (int i = counter; i < 4; i++) {
      currentChar[i] = 0;
    }
  }

  if (counter == 3) {
    currentText += findChar(currentChar, characters);
    for (int i = 0; i < 4; i++) {
      currentChar[i] = 0;
    }
    counter = 0;
    Serial.println(currentText);
  } else {
    counter++;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentText);
}

char findChar(int currentChar[], Character characters[]) {
  for (int i = 0; i < 27; i++) {
    bool isEqual = true;
    for (int j = 0; j < 4 && isEqual; j++) {
      if (characters[i].values[j] != currentChar[j]) {
        isEqual = false;
      }
    }
    if (isEqual) {
      return characters[i].identifier;
    }
  }
  return '-';
}

void flashLight(){
  digitalWrite(ledPin, HIGH);  
  delay(50);                 
  digitalWrite(ledPin, LOW);
}