#include <LiquidCrystal.h>

// ----------------------------------------------------
// Arduino Blackjack
// Player vs. CPU / Dealer
// ----------------------------------------------------

// LCD pin configuration.
// Change these values to match your actual wiring.
const int LCD_RS = 12;
const int LCD_EN = 11;
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 2;

// Buttons use INPUT_PULLUP.
// Connect each button between its pin and GND.
const int HIT_BUTTON = 8;
const int STAND_BUTTON = 9;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

enum GameState {
  PLAYER_TURN,
  DEALER_TURN,
  ROUND_OVER
};

GameState gameState = PLAYER_TURN;

int playerCards[12];
int dealerCards[12];
int playerCardCount = 0;
int dealerCardCount = 0;

bool lastHitState = HIGH;
bool lastStandState = HIGH;

unsigned long lastButtonTime = 0;
const unsigned long debounceDelay = 180;

// -------------------- Utility Functions --------------------

int drawCard() {
  // Returns values 1 through 13:
  // Ace = 1, Jack = 11, Queen = 12, King = 13
  return random(1, 14);
}

int cardValue(int card) {
  if (card == 1) return 11;      // Ace initially counts as 11
  if (card >= 10) return 10;     // 10, J, Q, K
  return card;
}

int calculateScore(int cards[], int count) {
  int score = 0;
  int aces = 0;

  for (int i = 0; i < count; i++) {
    score += cardValue(cards[i]);

    if (cards[i] == 1) {
      aces++;
    }
  }

  // Convert Aces from 11 to 1 if the hand would otherwise bust.
  while (score > 21 && aces > 0) {
    score -= 10;
    aces--;
  }

  return score;
}

void addPlayerCard() {
  if (playerCardCount < 12) {
    playerCards[playerCardCount] = drawCard();
    playerCardCount++;
  }
}

void addDealerCard() {
  if (dealerCardCount < 12) {
    dealerCards[dealerCardCount] = drawCard();
    dealerCardCount++;
  }
}

void showPlayerTurn() {
  int score = calculateScore(playerCards, playerCardCount);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your score: ");
  lcd.print(score);

  lcd.setCursor(0, 1);

  if (score < 21) {
    lcd.print("Hit or Stand");
  } else if (score == 21) {
    lcd.print("Blackjack!");
  } else {
    lcd.print("Bust!");
  }
}

void showMessage(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void startRound() {
  playerCardCount = 0;
  dealerCardCount = 0;

  addPlayerCard();
  addPlayerCard();

  addDealerCard();
  addDealerCard();

  gameState = PLAYER_TURN;
  showPlayerTurn();
}

void dealerPlay() {
  int dealerScore = calculateScore(dealerCards, dealerCardCount);

  showMessage("Dealer turn...", "");
  delay(700);

  while (dealerScore < 17) {
    addDealerCard();
    dealerScore = calculateScore(dealerCards, dealerCardCount);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dealer: ");
    lcd.print(dealerScore);
    lcd.setCursor(0, 1);
    lcd.print("Drawing...");
    delay(700);
  }

  gameState = ROUND_OVER;
}

void determineWinner() {
  int playerScore = calculateScore(playerCards, playerCardCount);
  int dealerScore = calculateScore(dealerCards, dealerCardCount);

  lcd.clear();

  if (playerScore > 21) {
    lcd.setCursor(0, 0);
    lcd.print("You busted!");
    lcd.setCursor(0, 1);
    lcd.print("Dealer wins");
  }
  else if (dealerScore > 21) {
    lcd.setCursor(0, 0);
    lcd.print("Dealer busts!");
    lcd.setCursor(0, 1);
    lcd.print("You win!");
  }
  else if (playerScore > dealerScore) {
    lcd.setCursor(0, 0);
    lcd.print("You win!");
    lcd.setCursor(0, 1);
    lcd.print("P:");
    lcd.print(playerScore);
    lcd.print(" D:");
    lcd.print(dealerScore);
  }
  else if (dealerScore > playerScore) {
    lcd.setCursor(0, 0);
    lcd.print("Dealer wins");
    lcd.setCursor(0, 1);
    lcd.print("P:");
    lcd.print(playerScore);
    lcd.print(" D:");
    lcd.print(dealerScore);
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Push / Tie");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(playerScore);
  }

  delay(2500);

  showMessage("New round", "Starting...");
  delay(1000);

  startRound();
}

bool buttonPressed(int pin, bool &lastState) {
  bool currentState = digitalRead(pin);

  if (currentState == LOW &&
      lastState == HIGH &&
      millis() - lastButtonTime > debounceDelay) {
    lastButtonTime = millis();
    lastState = currentState;
    return true;
  }

  lastState = currentState;
  return false;
}

// -------------------- Arduino Setup --------------------

void setup() {
  pinMode(HIT_BUTTON, INPUT_PULLUP);
  pinMode(STAND_BUTTON, INPUT_PULLUP);

  lcd.begin(16, 2);

  // Use a floating analog input to seed randomness.
  randomSeed(analogRead(A0));

  showMessage("Arduino", "Blackjack");
  delay(1500);

  startRound();
}

// -------------------- Main Loop --------------------

void loop() {
  if (gameState == PLAYER_TURN) {
    int playerScore = calculateScore(playerCards, playerCardCount);

    if (playerScore >= 21) {
      if (playerScore == 21) {
        gameState = DEALER_TURN;
      } else {
        gameState = ROUND_OVER;
      }
    }

    if (gameState == PLAYER_TURN &&
        buttonPressed(HIT_BUTTON, lastHitState)) {
      addPlayerCard();
      showPlayerTurn();
    }

    if (gameState == PLAYER_TURN &&
        buttonPressed(STAND_BUTTON, lastStandState)) {
      gameState = DEALER_TURN;
    }
  }

  if (gameState == DEALER_TURN) {
    dealerPlay();
  }

  if (gameState == ROUND_OVER) {
    determineWinner();
  }
}
