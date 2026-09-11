#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 20x4 I2C LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);


// ================================
// VOTE COUNTERS
// ================================

int candidateA = 0;
int candidateB = 0;
int candidateC = 0;
int candidateD = 0;


// ================================
// CANDIDATE NAMES
// ================================

String nameA = "Alice";
String nameB = "Bob";
String nameC = "Carol";
String nameD = "David";


// ================================
// NORMAL VOTING SCREEN
// ================================

void showVotingScreen() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Electronic Voting");

  lcd.setCursor(0, 1);
  lcd.print("A:Alice  B:Bob");

  lcd.setCursor(0, 2);
  lcd.print("C:Carol  D:David");

  lcd.setCursor(0, 3);
  lcd.print("Press a button");
}


// ================================
// WAIT FOR BUTTON RELEASE
// ================================

void waitForRelease(int pin) {

  while (digitalRead(pin) == LOW) {
    delay(10);
  }
}


// ================================
// BUZZER BEEP
// ================================

void beep() {

  tone(D13, 1000);
  delay(200);
  noTone(D13);
}


// ================================
// GET HIGHEST VOTES
// ================================

int getHighestVotes() {

  return max(
    max(candidateA, candidateB),
    max(candidateC, candidateD)
  );
}


// ================================
// COUNT WINNERS
// ================================

int countWinners(int highest) {

  int winners = 0;

  if (candidateA == highest) winners++;
  if (candidateB == highest) winners++;
  if (candidateC == highest) winners++;
  if (candidateD == highest) winners++;

  return winners;
}


// ================================
// SHOW WINNER
// ================================

void showWinner() {

  // If nobody voted
  if (candidateA == 0 &&
      candidateB == 0 &&
      candidateC == 0 &&
      candidateD == 0) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ELECTION RESULT");

    lcd.setCursor(0, 1);
    lcd.print("No votes yet");

    lcd.setCursor(0, 2);
    lcd.print("Please vote");

    delay(4000);

    return;
  }


  int highest = getHighestVotes();
  int winners = countWinners(highest);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ELECTION RESULT");


  // ================================
  // ONE WINNER
  // ================================

  if (winners == 1) {

    lcd.setCursor(0, 1);
    lcd.print("Winner:");

    lcd.setCursor(0, 2);

    if (candidateA == highest)
      lcd.print(nameA);

    else if (candidateB == highest)
      lcd.print(nameB);

    else if (candidateC == highest)
      lcd.print(nameC);

    else if (candidateD == highest)
      lcd.print(nameD);

    lcd.setCursor(0, 3);
    lcd.print("Votes: ");
    lcd.print(highest);
  }


  // ================================
  // TIE
  // ================================

  else {

    lcd.setCursor(0, 1);
    lcd.print("Tie Winners:");

    lcd.setCursor(0, 2);

    if (candidateA == highest) {
      lcd.print("A ");
    }

    if (candidateB == highest) {
      lcd.print("B ");
    }

    if (candidateC == highest) {
      lcd.print("C ");
    }

    if (candidateD == highest) {
      lcd.print("D ");
    }

    lcd.setCursor(0, 3);
    lcd.print("Votes: ");
    lcd.print(highest);
  }

  delay(5000);
}


// ================================
// SHOW ALL VOTE COUNTS + TOTAL
// ================================

void showVoteCounts() {

  int totalVotes =
    candidateA +
    candidateB +
    candidateC +
    candidateD;


  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("VOTE COUNTS");

  lcd.setCursor(0, 1);
  lcd.print("A: ");
  lcd.print(candidateA);

  lcd.setCursor(10, 1);
  lcd.print("B: ");
  lcd.print(candidateB);

  lcd.setCursor(0, 2);
  lcd.print("C: ");
  lcd.print(candidateC);

  lcd.setCursor(10, 2);
  lcd.print("D: ");
  lcd.print(candidateD);

  lcd.setCursor(0, 3);
  lcd.print("TOTAL: ");
  lcd.print(totalVotes);

  delay(5000);
}


// ================================
// RESET ELECTION
// ================================

void resetElection() {

  candidateA = 0;
  candidateB = 0;
  candidateC = 0;
  candidateD = 0;


  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("RESETTING...");

  lcd.setCursor(0, 1);
  lcd.print("Votes cleared");

  delay(2000);

  showVotingScreen();
}


// ================================
// SETUP
// ================================

void setup() {

  // Candidate buttons
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);

  // Result buttons
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);

  // Reset button
  pinMode(D8, INPUT_PULLUP);


  // LEDs
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, OUTPUT);


  // Buzzer
  pinMode(D13, OUTPUT);


  // Turn LEDs off initially
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  digitalWrite(D11, LOW);
  digitalWrite(D12, LOW);


  // Start I2C
  Wire.begin();


  // Start LCD
  lcd.init();
  lcd.backlight();


  // Welcome screen
  lcd.setCursor(0, 0);
  lcd.print("Electronic Voting");

  lcd.setCursor(0, 1);
  lcd.print("Machine");

  lcd.setCursor(0, 2);
  lcd.print("STM32 Project");

  delay(2500);


  showVotingScreen();
}


// ================================
// MAIN LOOP
// ================================

void loop() {


  // ================================
  // CANDIDATE A
  // ================================

  if (digitalRead(D2) == LOW) {

    candidateA++;

    digitalWrite(D9, HIGH);

    beep();

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("VOTE RECORDED!");

    lcd.setCursor(0, 2);
    lcd.print(nameA);

    lcd.setCursor(0, 3);
    lcd.print("Thank you!");

    delay(1000);

    digitalWrite(D9, LOW);

    waitForRelease(D2);

    showVotingScreen();
  }


  // ================================
  // CANDIDATE B
  // ================================

  if (digitalRead(D3) == LOW) {

    candidateB++;

    digitalWrite(D10, HIGH);

    beep();

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("VOTE RECORDED!");

    lcd.setCursor(0, 2);
    lcd.print(nameB);

    lcd.setCursor(0, 3);
    lcd.print("Thank you!");

    delay(1000);

    digitalWrite(D10, LOW);

    waitForRelease(D3);

    showVotingScreen();
  }


  // ================================
  // CANDIDATE C
  // ================================

  if (digitalRead(D4) == LOW) {

    candidateC++;

    digitalWrite(D11, HIGH);

    beep();

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("VOTE RECORDED!");

    lcd.setCursor(0, 2);
    lcd.print(nameC);

    lcd.setCursor(0, 3);
    lcd.print("Thank you!");

    delay(1000);

    digitalWrite(D11, LOW);

    waitForRelease(D4);

    showVotingScreen();
  }


  // ================================
  // CANDIDATE D
  // ================================

  if (digitalRead(D5) == LOW) {

    candidateD++;

    digitalWrite(D12, HIGH);

    beep();

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("VOTE RECORDED!");

    lcd.setCursor(0, 2);
    lcd.print(nameD);

    lcd.setCursor(0, 3);
    lcd.print("Thank you!");

    delay(1000);

    digitalWrite(D12, LOW);

    waitForRelease(D5);

    showVotingScreen();
  }


  // ================================
  // D6 - SHOW WINNER
  // ================================

  if (digitalRead(D6) == LOW) {

    showWinner();

    waitForRelease(D6);

    showVotingScreen();
  }


  // ================================
  // D7 - SHOW VOTE COUNTS
  // ================================

  if (digitalRead(D7) == LOW) {

    showVoteCounts();

    waitForRelease(D7);

    showVotingScreen();
  }


  // ================================
  // D8 - RESET
  // ================================

  if (digitalRead(D8) == LOW) {

    resetElection();

    waitForRelease(D8);
  }
}
