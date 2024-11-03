### Arduino Morse Code Translator with LCD Display
This project implements a Morse code translator using an Arduino, a push button, an LED, and a LiquidCrystal display. The user can input Morse code through short and long button presses, which are translated into text and displayed on the LCD. The LED provides visual feedback for button presses and resets.

![Demonstration](https://i.imgur.com/713IuTp.gif)


### Features
Morse Code Input: Users can enter Morse code using a single button. Short presses represent dots, and long presses represent dashes.
Real-time Display: The translated text is displayed in real time on a 16x2 LCD.
Feedback Mechanism: An LED flashes to indicate button presses, resets, and other status updates.
Queue Mechanism: A queue system is implemented to eliminate erroneous inputs from static or accidental button presses.
Reset Functionality: Users can reset the input state and clear the display with a prolonged button press.

### Components Used
Arduino (e.g., Arduino Uno),
16x2 LiquidCrystal LCD,
Push button,
LED (with appropriate resistor),
Potentiometer,
Breadboard and jumper wires

### How to Use
Wiring: Connect the LCD, button, and LED to the appropriate pins on the Arduino as defined in the code.
Upload the Code: Load the provided code into the Arduino IDE and upload it to your Arduino board.
Input Morse Code: Use the button to input Morse code:
Short press: Dot (·)
Long press: Dash (−)
Extra long press: Reset
View Output: The translated text will appear on the LCD screen. The LED will flash for visual feedback.

![Build](https://i.imgur.com/f6VLHug.png)

