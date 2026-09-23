# Wiring Guide

The sample Arduino sketch is configured for a standard 16x2 LCD using the `LiquidCrystal` library.

## LCD Connections

| LCD Signal | Arduino UNO Pin |
|---|---:|
| RS | 12 |
| Enable | 11 |
| D4 | 5 |
| D5 | 4 |
| D6 | 3 |
| D7 | 2 |

Power, ground, contrast, and backlight connections depend on your LCD module.

## Button Connections

| Button | Arduino UNO Pin |
|---|---:|
| Hit | 8 |
| Stand | 9 |

The sketch uses `INPUT_PULLUP`, so each button should connect between its Arduino input pin and GND.

## Important

These pin assignments are placeholders for a typical configuration. Update the constants near the top of `Arduino_Blackjack.ino` to match the wiring used in your actual project.
