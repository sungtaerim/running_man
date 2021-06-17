#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 12, 5, 4, 3, 2);

int key = 8;
int red = 7;
int buttonState = 0;
int random_i = 0;
int score = 0;
int speedCount = 400;
bool isKey = false;
int index = 0;
int y = 0;

byte Chel_1[8] =
{
  0b01110,
  0b01110,
  0b01110,
  0b00100,
  0b00100,
  0b00100,
  0b01010,
  0b10100
};

byte Chel_2[8] =
{
  0b01110,
  0b01110,
  0b01110,
  0b00100,
  0b00100,
  0b10100,
  0b01010,
  0b00001
};

byte mountain[8] = {
  0b00000,
  0b00000,
  0b01000,
  0b01101,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, Chel_1);
  lcd.createChar(1, Chel_2);
  lcd.createChar(2, mountain);
  pinMode(key, INPUT);
  pinMode(red, OUTPUT);
}

void loop() {
  index = 0;
  y = 0;

  for (int i = 0; i < 16; i++) {
    buttonState = digitalRead(key);
    if (i == 0) {
      random_i = 4 + rand() % 9;
    }
    lcd.setCursor(random_i, 1);
    lcd.write(byte(2));

    if (buttonState == LOW) {
      printChar(i, 0, HIGH);
    } else {
      printChar(i, 1, LOW);
    }

    if (random_i == i && y == 1) {
      gameOver();
    } else {
      score++;
      speedCount--;
    }
    delay(speedCount);
    lcd.clear();
  }
}
void gameOver() {
  lcd.clear();
  lcd.print("GAME OVER");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(score / 16);
  delay(1000000);
}

void printChar(int i, int lineNumber, int diod) {
  lcd.setCursor(i, lineNumber);
  if (index == 0) {
    lcd.write(byte(index));
    index = 1;
  } else {
    lcd.write(byte(index));
    index = 0;
  }
  digitalWrite(red, HIGH);
  y = lineNumber;
}
