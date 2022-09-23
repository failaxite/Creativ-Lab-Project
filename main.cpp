#include "Arduino.h"

#include "Ultrasonic.h"

#include <Adafruit_SSD1306.h>

#include <Wire.h>

#include <TM1637Display.h>

#include "pitches.h" 

#define CLK 6 // Pin du clock input
#define DIO 11 // Pin du data input/output

TM1637Display display = TM1637Display(CLK, DIO); // Crée un objet d'affichage qui représente l'affichage TM1637
Ultrasonic ultrasonic(5, 3); // Trig et Echo

void setup() {
  display.clear(); // Clear l'affichage
  display.setBrightness(7); // Set la luminosité de l'affichage sur l'afficheur VS-ELEC AFFICHEUR
  Serial.begin(9600); // Initialisation de la connexion avec la carte arduino
  pinMode(10, OUTPUT); // Initialisation de la led rouge sur la pin 10 en sortie
  pinMode(9, OUTPUT); // Initialisation de la led verte sur la pin 9 en sortie
  pinMode(12, OUTPUT); // Initialisation du buzzer sur la pin 12 en sortie
}

void loop () {
  int dist = ultrasonic.distanceRead(CM); // Initialisation de la variable "dist" qui récupère la distance calculé
  Serial.print(dist); // Print de la distance calculé par le potentiomètre
  Serial.println(" cm"); // Print cm apres le valeur print
  display.showNumberDec(dist); // Affichage distance 

  if (dist < 30) {
    digitalWrite(9, LOW);  // Eteint la led qui est sur le pin 9 (led verte)
    digitalWrite(10, HIGH); // Allumer la led qui est sur le pin 10 (led rouge)
  }
  if (dist > 30) {
    digitalWrite(9, HIGH); // Allumer la led qui est sur le pin 9 (led verte)
    digitalWrite(10, LOW); // Eteint la led qui est sur le pin 10 (led rouge)
  }

if (dist <= 10) {
    digitalWrite(10, HIGH); // Allumer la led qui est sur le pin 10 (led rouge)
    tone(12,NOTE_C7); // Jouer la note C7 via le pin 12
    delay(500); // Delay de 0,5 seconde
    digitalWrite(10, LOW); // Eteint la led qui est sur le pin 10 (led rouge)
    delay(500); // Delay de 0,5 seconde
}
}


