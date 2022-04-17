// ***** Librerie display *****
// ***** Display ***** 

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define INDIRIZZO_DISPLAY 0x3c
#define LARGHEZZA_DISPLAY 128 
#define ALTEZZA_DISPLAY 64 
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY, &Wire, OLED_RESET);

// ***** Variabili *****
#define MAX_CARATTERI 20 // Caratteri massimi visibili per righa
#define MAX_RIGHE 6 // Righe massime visibili

String parola="";
String linea="";
String txt_row [MAX_RIGHE];
int row=0;

// ***** Funzioni usate *****
void setup_display();

void setup(){
  Serial.begin(9600);
  setup_display();
}
  
void loop() {
  if (Serial.available()){
    char ch=Serial.read();
    if (ch=='\n'){
      Serial.print(F("If /n Linea= "));
      Serial.println(linea);
      parola="";
      linea="";
      row=0;
    } else {
      parola+=ch;
      if (ch== ' ' or ch=='\r'){
        if ((linea.length() + parola.length()) < MAX_CARATTERI){
          linea+=parola;
          parola="";
         } else {
          Serial.print(F("Linea= "));
          Serial.println (linea);
          delay (1000);
          txt_row[row]=linea;
          linea=parola;
          parola="";
          row++;
          if (row==MAX_RIGHE){
            Serial.print(F("txt_righa= "));
            for (int i=0; i<MAX_RIGHE; i++){
              Serial.println(txt_row[i]);
              }
              row=0;
              delay (2000);
            }
        }
      }
    }
  }   
}

  // ---- Setup display ----
void setup_display() {
  display.begin(INDIRIZZO_DISPLAY, true);
  display.setTextSize(1); // Dimensione testo
  display.setTextColor(SH110X_WHITE );  //  Colore testo
  delay (100);
  display.clearDisplay();
  display.display();
}
