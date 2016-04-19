#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include "pitches.h"

#define BACKLIGHT_PIN   1

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  pinMode(BACKLIGHT_PIN, OUTPUT);

  digitalWrite(BACKLIGHT_PIN, HIGH);
  
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Loading...");
  
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522

  randomSeed(analogRead(0));
}

void loop() {

  lcd.clear();
  digitalWrite(BACKLIGHT_PIN, LOW);
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  int randNumber = random(1,100);

  if (randNumber <= 20){
    jackpot();
  } else {
    allthebest();
  }
}

void allthebest() {
  digitalWrite(BACKLIGHT_PIN, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("#AllTheBest");
  tone(8,NOTE_C6,200);
  delay(1000);
  lcd.clear();
  delay(200);
}

void jackpot() {
  digitalWrite(BACKLIGHT_PIN, HIGH);
  lcd.setCursor(3, 0);
  lcd.print("You won a");
  lcd.setCursor(4, 1);
  lcd.print("JACKPOT!");
  
  // Final Fantasy Victory Fanfare
  // Ref: http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0056213
  // Key E-flat (Flat notes: B-flat (A-sharp), E-flat (D-sharp), A-flat (G-sharp))
  // Tempo Allegro Brillante 152bpm (1 beat = 394.7ms)
  
  tone(8,NOTE_DS5,131);
  delay(132);
  tone(8,NOTE_DS5,131);
  delay(132);
  tone(8,NOTE_DS5,131);
  delay(132);
  tone(8,NOTE_DS5,395);
  delay(396);
  tone(8,NOTE_B4,395);
  delay(396);
  tone(8,NOTE_CS5,395);
  delay(396);
  tone(8,NOTE_DS5,131);
  delay(264);
  tone(8,NOTE_CS5,131);
  delay(132);
  tone(8,NOTE_DS5,1185);
  delay(1186);
  
  lcd.clear();
  delay(200);
}

void StarWarsMainTheme() {
	// Star Wars (Main Theme)
	// Key G (Sharp notes: F-sharp)
	// Tempo: Majestically, steady march 108bpm (1 beat = 555.5ms => 555ms)

  tone(8, NOTE_D3, 180);
  delay(185);
  tone(8, NOTE_D3, 180);
  delay(185);
  tone(8, NOTE_D3, 180);
  delay(185);
  tone(8, NOTE_G3, 1110);
  delay(1110);
  tone(8, NOTE_D4, 1110);
  delay(1110);
  tone(8, NOTE_C4, 185);
  delay(185);
  tone(8, NOTE_B3, 185);
  delay(185);
  tone(8, NOTE_A3, 185);
  delay(185);
  tone(8, NOTE_G4, 1110);
  delay(1110);
  tone(8, NOTE_D4, 555);
  delay(555);
  tone(8, NOTE_C4, 185);
  delay(185);
  tone(8, NOTE_B3, 185);
  delay(185);
  tone(8, NOTE_A3, 185);
  delay(185);
  tone(8, NOTE_G4, 1110);
  delay(1110);
  tone(8, NOTE_D4, 555);
  delay(555);
  tone(8, NOTE_C4, 185);
  delay(185);
  tone(8, NOTE_B3, 185);
  delay(185);
  tone(8, NOTE_C4, 185);
  delay(185);
  tone(8, NOTE_A3, 1110);
  delay(1110);
}

void StarWarsImperialMarch() {
  // The Imperial March (Darth Vater's Theme)
  // Key A (Sharp notes: F-sharp, C-sharp, G-sharp)
  // Tempo: March 120bpm (1 beat = 500ms)

  tone(8, NOTE_FS3, 450);
  delay(500);
  tone(8, NOTE_FS3, 450);
  delay(500);
  tone(8, NOTE_FS3, 450);
  delay(500);
  tone(8, NOTE_D3, 325);
  delay(375);
  tone(8, NOTE_A3, 75);
  delay(125);
  tone(8, NOTE_FS3, 450);
  delay(500);
  tone(8, NOTE_D3, 325);
  delay(375);
  tone(8, NOTE_A3, 75);
  delay(125);
  tone(8, NOTE_FS3, 950);
  delay(1000);
  tone(8, NOTE_CS4, 450);
  delay(500);
  tone(8, NOTE_CS4, 450);
  delay(500);
  tone(8, NOTE_CS4, 450);
  delay(500);
  tone(8, NOTE_D4, 325);
  delay(375);
  tone(8, NOTE_CS4, 75);
  delay(125);
  tone(8, NOTE_F3, 450);
  delay(500);
  tone(8, NOTE_D3, 325);
  delay(375);
  tone(8, NOTE_A3, 75);
  delay(125);
  tone(8, NOTE_FS3, 950);
  delay(1000);
}
