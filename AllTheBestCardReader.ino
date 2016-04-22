#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include "pitches.h"

#define BACKLIGHT_PIN   1

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

byte CONTROL_ID[] = {0x34, 0x39, 0x1A, 0xDC, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

#define NUMBER_OF_MODES 2

int MODE = 0;

void setup() {
  //Serial.begin(9600);
   
  pinMode(BACKLIGHT_PIN, OUTPUT);

  digitalWrite(BACKLIGHT_PIN, HIGH);
  
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Loading...");
  
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522

  randomSeed(analogRead(0));

  PrintModeTitle();
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

  if (CompareWithControl((&(mfrc522.uid))->uidByte, (&(mfrc522.uid))->size)) {
    MODE = (MODE + 1) % NUMBER_OF_MODES;
    PrintModeTitle();
    return;
  }

  int randNumber = random(1,100);

  if (MODE == 0) // Normal mode
  {
    if (randNumber <= 20){
      jackpot();
    } else {
      allthebest();
    }
  }
  else if (MODE == 1) // May 4th Mode
  {
    if (randNumber <= 50){
      StarWarsImperialMarch();
    } else {
      StarWarsMainTheme();
    }
  }
}

bool CompareWithControl(byte input[], byte size)
{
  bool retVal = true;
  for (byte i = 0; i < size; i++) { 
     retVal = retVal && (input[i] == CONTROL_ID[i]);
  }

  return retVal;
}

void PrintModeTitle() {
  digitalWrite(BACKLIGHT_PIN, HIGH);
  lcd.clear();
  if (MODE == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("MODE 0");
    lcd.setCursor(0, 1);
    lcd.print("Normal Mode");
  } else if (MODE == 1) {
    lcd.setCursor(0, 0);
    lcd.print("MODE 1");
    lcd.setCursor(0, 1);
    lcd.print("May 4th Mode");
  }

  delay(1000);
  lcd.clear();
  delay(200);
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
  digitalWrite(BACKLIGHT_PIN, HIGH);
  lcd.setCursor(1, 0);
  lcd.print("May the force");
  lcd.setCursor(2, 1);
  lcd.print("be with you!");
  
	// Star Wars (Main Theme)
	// Key G (Sharp notes: F-sharp)
	// Tempo: Majestically, steady march 108bpm (1 beat = 555.5ms => 555ms)

  tone(8, NOTE_D4, 170);
  delay(185);
  tone(8, NOTE_D4, 170);
  delay(185);
  tone(8, NOTE_D4, 170);
  delay(185);
  tone(8, NOTE_G4, 1110);
  delay(1110);
  tone(8, NOTE_D5, 1110);
  delay(1110);
  tone(8, NOTE_C5, 185);
  delay(185);
  tone(8, NOTE_B4, 185);
  delay(185);
  tone(8, NOTE_A4, 185);
  delay(185);
  tone(8, NOTE_G5, 1110);
  delay(1110);
  tone(8, NOTE_D5, 555);
  delay(555);
  tone(8, NOTE_C5, 185);
  delay(185);
  tone(8, NOTE_B4, 185);
  delay(185);
  tone(8, NOTE_A4, 185);
  delay(185);
  tone(8, NOTE_G5, 1110);
  delay(1110);
  tone(8, NOTE_D5, 555);
  delay(555);
  tone(8, NOTE_C5, 185);
  delay(185);
  tone(8, NOTE_B4, 185);
  delay(185);
  tone(8, NOTE_C5, 185);
  delay(185);
  tone(8, NOTE_A4, 1110);
  delay(1110);

  lcd.clear();
  delay(200);
}

void StarWarsImperialMarch() {
  digitalWrite(BACKLIGHT_PIN, HIGH);
  lcd.setCursor(3, 0);
  lcd.print("Luke, I am");
  lcd.setCursor(1, 1);
  lcd.print("your father!");

  // The Imperial March (Darth Vader's Theme)
  // Key A (Sharp notes: F-sharp, C-sharp, G-sharp)
  // Tempo: March 120bpm (1 beat = 500ms)

  tone(8, NOTE_FS3, 475);
  delay(500);
  tone(8, NOTE_FS3, 475);
  delay(500);
  tone(8, NOTE_FS3, 475);
  delay(500);
  tone(8, NOTE_D3, 350);
  delay(375);
  tone(8, NOTE_A3, 100);
  delay(125);
  tone(8, NOTE_FS3, 475);
  delay(500);
  tone(8, NOTE_D3, 350);
  delay(375);
  tone(8, NOTE_A3, 100);
  delay(125);
  tone(8, NOTE_FS3, 975);
  delay(1000);
  tone(8, NOTE_CS4, 475);
  delay(500);
  tone(8, NOTE_CS4, 475);
  delay(500);
  tone(8, NOTE_CS4, 475);
  delay(500);
  tone(8, NOTE_D4, 350);
  delay(375);
  tone(8, NOTE_CS4, 100);
  delay(125);
  tone(8, NOTE_F3, 475);
  delay(500);
  tone(8, NOTE_D3, 350);
  delay(375);
  tone(8, NOTE_A3, 100);
  delay(125);
  tone(8, NOTE_FS3, 1000);
  delay(1000);

  lcd.clear();
  delay(200);
}
