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

String linea[MAX_RIGHE];

// ***** Funzioni usate *****
void setup_display();
void Stampa_a_display();
void Ripulisci_linea();
void prova();

void setup(){
  Serial.begin(9600);
  setup_display();
  
  String msg="Ciao Davide, come stai? Che fai? 0";
  msg+=" ";
  int N=0, pos=0;
  int n=msg.indexOf(' ');

  while (n>0){
    String txt=msg.substring(n,N);
    N=n+1;
    n=msg.indexOf(' ',N);
    
    if ((linea[pos].length() + txt.length()) <= MAX_CARATTERI){
      linea[pos]= linea[pos]+ txt + " ";
    }
    else {
      pos++;
      if (pos==6){
        pos=0;
        Stampa_a_display();
        Ripulisci_linea();
        delay (1000);
      }
      linea[pos]= txt + " ";
    }   
   } 
    Stampa_a_display();
}
  
void loop() {
 }
 
// ---- Pulisce l'array di stringhe----
void Ripulisci_linea(){
  for (int i=0; i<MAX_RIGHE; i++){
    linea[i]="";
    }
  }
  
// ---- Stampiamo la stringa sul dipslay ----
 void Stampa_a_display(){
  display.clearDisplay();
  for (int i=0; i<MAX_RIGHE; i++){
    Serial.println(linea[i]);
    display.setCursor (0, i*10); //x - y
    display.println(linea[i]);
    }
  display.display();
  }

  // ---- Setup display ----
void setup_display() {
  display.begin(INDIRIZZO_DISPLAY, true);
  display.setTextSize(1); // Dimensione testo
  display.setTextColor(SH110X_WHITE );  //  Colore testo
  delay (100);
}
