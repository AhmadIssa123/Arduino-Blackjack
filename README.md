# Arduino Blackjack Game

An interactive Blackjack game built with an Arduino UNO, LCD display, and physical button inputs. The project combines embedded programming with hardware integration to create a simple player-vs-CPU card game.

## Features

- Player vs. CPU Blackjack gameplay
- Physical **Hit** and **Stand** button controls
- LCD-based game feedback
- Random card generation
- Automatic hand scoring
- Ace handling
- Dealer decision logic
- Round reset and replay support
- Embedded C/C++ implementation for Arduino

## Hardware

- Arduino UNO
- 16x2 LCD display
- 2 push buttons
- Breadboard
- Jumper wires
- Resistors as needed
- USB cable / power source

> The exact pin assignments can be changed in the Arduino sketch to match your wiring.

## Repository Structure

```text
Arduino_Blackjack/
├── README.md
├── src/
│   └── Arduino_Blackjack.ino
├── docs/
│   ├── HOW_IT_WORKS.md
│   └── WIRING_GUIDE.md
└── images/
    └── README.md
```

## How It Works

1. The player begins with two cards.
2. The CPU/dealer also receives cards.
3. The LCD displays the player's score and available action.
4. Press **Hit** to draw another card.
5. Press **Stand** to end the player's turn.
6. The dealer automatically draws until reaching the configured stand threshold.
7. The program compares both hands and displays the result.
8. The game resets for another round.

## Software

The game is programmed in Arduino C/C++ and uses the standard `LiquidCrystal` library.

## Running the Project

1. Install the Arduino IDE.
2. Connect an Arduino UNO.
3. Open `src/Arduino_Blackjack.ino`.
4. Update the LCD and button pin definitions if your wiring is different.
5. Select **Arduino UNO** as the board.
6. Compile and upload the sketch.
7. Use the Hit and Stand buttons to play.

## Engineering Concepts Demonstrated

- Embedded systems programming
- Digital input handling
- Hardware-software integration
- State-based program design
- Random number generation
- Conditional logic
- User-interface design
- System testing and debugging

## Future Improvements

- Add betting/chip functionality
- Add multiple rounds and win tracking
- Add card suits and rank display
- Add sound effects with a buzzer
- Add a larger graphical display
- Add persistent score storage
- Improve dealer and game-state animations

## Author

Ahmad Issa  
Electrical & Computer Engineering  
University of Memphis
