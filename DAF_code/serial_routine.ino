

//routine seriale principale
//quano la seriale è aperta leggo il messaggio, lo scompatto in usa stringa,
//leggo il comando all'inizo del massaggio e richiamo la funzione abbianata
void serialAvailable() {
  boolean printiamolo = false;  //true per printare messaggi di stato

  if (printiamolo) Serial.println("  INIZIO serialAvailable() ");

  //leggo la seriale fino all'ACAPO
  String Read = Serial.readStringUntil('\n');
  Serial.print("Letto: "); Serial.println(Read);

  //valariabili per la stringa dei dati della seriale
  String sd0;
  String sd1;
  String sd2;
  String sd3;
  String sd4;
  String sd5;
  String sd6;
  String sd7;

  //variabili
  int previ = 0;
  int val = 0;
  int i = 0;

  //scompatto al stringa nelle sottostringhe
  if (printiamolo) Serial.println(sizeof(Read));
  while (i < Read.length() + 1) {
    if (isSpace(Read[i]) == true || Read[i] == '\0') {
      switch (val) {
        case 0: sd0 = Read.substring(previ, i); break;
        case 1: sd1 = Read.substring(previ, i); break;
        case 2: sd2 = Read.substring(previ, i); break;
        case 3: sd3 = Read.substring(previ, i); break;
        case 4: sd4 = Read.substring(previ, i); break;
        case 5: sd5 = Read.substring(previ, i); break;
        case 6: sd6 = Read.substring(previ, i); break;
        case 7: sd7 = Read.substring(previ, i); break;
      }
      val++;  previ = i + 1;
    }

    if (printiamolo) {
      Serial.print(i); Serial.print(" ");
      Serial.print(Read[i]); Serial.print(" ");
      Serial.print(val); Serial.print(" ");
      Serial.println(previ);
    }
    i++;
  }

  if (printiamolo) {
    Serial.println(sd0); Serial.println(sd1);
    Serial.println(sd2); Serial.println(sd3);
    Serial.println(sd4); Serial.println(sd5);
    Serial.println(sd6); Serial.println(sd7);

  }

  //creo l'array con i dati della seriale trasformati in interi
  int arreiDiDati[] = {sd1.toInt(), sd2.toInt(), sd3.toInt(), sd4.toInt(), sd5.toInt(), sd6.toInt(), sd7.toInt()};


  //se il primo dato equivale ad un comando chiamo la routine di quel comando altrimnti rimando errore
  if (sd0 == "help") {
    help();
  } else if (sd0 == "timeNow") {
    timeNow();


  } else if (sd0 == "timeSet") {
    timeSet(arreiDiDati);
    timeNow();


  } else if (sd0 == "nextDrop") {
    nextDrop();


  } else if (sd0 == "viewDrop") {
    viewDrop();


  } else if (sd0 == "setDrop") {
    setDrop(arreiDiDati);


  } else if (sd0 == "EEPROMreset") {
    EEPROMreset();


  } else if (sd0 == "EEPROMread") {
    EEPROMread(arreiDiDati);


  } else if (sd0 == "RESET") {
    //RESET();
    Serial.println("questa funzione sarà presto(piomme) disponibile\n");

  } else Serial.println("Piciuuu hai sbagliato\n");


  if (printiamolo) Serial.println("  FINE serialAvailable()  ");
}

//####################################################################################################
//####################################################################################################

//routine serial per printare la lista dei comandi
void help() {
  Serial.println("Lista comandi:");
  Serial.println(" timeNow                      visualizzare l'ora");
  Serial.println(" timeSet YYYY mm dd HH ii ss  cambiare l'ora");
  Serial.println(" nextDrop                     visualizzare il prossimo drop");
  Serial.println(" viewDrop                     visualizzare tutti i drop");
  Serial.println(" setDrop x DS HH II bbbbbbbb  impostare il drop N°x"); //II sta per minuti
  Serial.println(" EEPROMreset                  porta i dati di reset nella EEPROM");
  Serial.println(" EEPROMread x / x y           visualizza il valore all'indirizzo selezionato della EEPROM");
  Serial.println();
}
