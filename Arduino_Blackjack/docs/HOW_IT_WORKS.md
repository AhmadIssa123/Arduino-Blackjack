# How the Game Works

## Game Flow

The Arduino controls the game using three main states:

1. **Player Turn**
   - The player begins with two randomly generated cards.
   - The player may press **Hit** to receive another card.
   - The player may press **Stand** to end the turn.
   - If the player's score exceeds 21, the player busts.

2. **Dealer Turn**
   - The dealer automatically draws cards while its score is below 17.
   - Once the dealer reaches 17 or higher, it stops drawing.

3. **Round Over**
   - The Arduino compares the player and dealer scores.
   - The LCD displays the winner.
   - A new round starts automatically.

## Card Values

- Number cards use their normal values.
- Jack, Queen, and King count as 10.
- Ace begins as 11.
- If the hand would exceed 21, an Ace can be reduced from 11 to 1.

## Software Structure

The sketch separates the project into functions for:

- Random card generation
- Card-value conversion
- Hand scoring
- Player card draws
- Dealer card draws
- LCD updates
- Button handling
- Dealer logic
- Winner determination
- Round resets

This structure makes the code easier to test, modify, and expand.
