//base_002
//D.A.F.(distributore automatico di medicinali) di Perissinotto Giulio e Bellucci Francesco

//codice funzionante solo da seriale
//completata la parte riguardante la gestione del tempo, il salvataggio dei dati sulla EEPROM, il settaggio dei vari drop e la lettura
//manca la parte di I/O hardware

//includo le librerie
#include <Wire.h>
#include <DS3231.h>
#include <Arduino.h>
#include <EEPROM.h>

int quantitaDiDrop = 8;  //drop registrabili, possono essere infiniti ma poi utilizzano troppa memoria

//variabili locali per operazioni sui drop
int VAttivo[] = {1, 1, 1, 1, 0, 0, 0, 0};   //attivo o no non lo uso
int VPrior[] = {0, 0, 0, 0, 0, 0, 0, 0};    //priorità
int VdiffGS[] = {0, 0, 0, 0, 0, 0, 0, 0};   //GS da ora
int VdiffOra[] = {0, 0, 0, 0, 0, 0, 0, 0};  //ora da ora
int VdiffMin[] = {0, 0, 0, 0, 0, 0, 0, 0};  //minuti da ora

int VGS[] = {0, 0, 0, 0, 0, 0, 0, 0};       //GS di drop
int VOra[] = {0, 0, 0, 0, 0, 0, 0, 0};      //ora di drop
int VMin[] = {0, 0, 0, 0, 0, 0, 0, 0};      //minuti di drop
int VcosaDrop[] = {0, 0, 0, 0, 0, 0, 0, 0}; //cosa droppare(devo cambiarla)


//valori di default caricati nella EEPROM tramite EEPROMreset
const int VGSEE[] = {1, 1, 1, 1, 2, 2 , 2, 2};         //GS di drop
const int VOraEE[] = {10, 10, 20, 20, 10, 10, 20, 20}; //ora di drop
const int VMinEE[] = {40, 50, 40, 50, 40, 50, 40, 50}; //minuti di drop
const int VcosaDropEE[] = {0b1100, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111, 0b1111}; //cosa droppare

//indirizzo della EEPROM da cui inizio a scrivere i dati sui drop
int dataAddrStart = 16;

//inizializzo l'RTC
DS3231 clock;
RTCDateTime dt;

//variabili per l'RTC
boolean isAlarm = false;
boolean alarmState = false;
int alarmLED = 13;

//####################################################################################################
//####################################################################################################

void setup() {
  //inizializzo la comunicazione seriale
  Serial.begin(250000);
  Serial.println("\n\n  START  \n");

  //inizializzo l'RTC
  if (clock.begin()) Serial.println("RTC Inizialized succesfully");
  else Serial.println("RTC Inizialized failed");


  timeNow();          //printo l'ora
  EEPROMimport();     //importo i dati salvati dalla EEPROM
  dropPrioritario();  //calcolo il drop prioritario


  Serial.println("\n\nEnter 'help' for command list \n");
}

void loop() {
  //Serial.println("  NEW LOOP  ");


  //se l'allarme sta scattando chiamo la funzione bugiaESuonataLaSveglia() per droppare le medicine
  if (clock.isAlarm1()) bugiaESuonataLaSveglia();

  //se la seriale è aperta eseguo serialAvailable() per eseguire le istruzioni date dal terminale
  if (Serial.available()) serialAvailable();

  delay(10);
}

//####################################################################################################
//####################################################################################################

/*  da fare (un autoresettatore)
  void RESET() {
  Serial.println("RESET in:");
  Serial.println("5");
  delay(1000);
  Serial.println("4");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("1");
  Serial.println("Resettamento");
  Serial.println();
  Serial.println();
  Reset();
  }

  void(* Reset)(void) = 0;
*/
