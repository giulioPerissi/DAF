/*
  Indirizzi EEPROM
  si parte dal 16esimo byte
  4 byte per Drop: gg, hh, mm, cosaDroppare
  sono in sequenza: il secondo Drop perte da 20, il terzo da 24, ecc...
*/



//routine per riportare i dati delle varibili VGS/VOra/VMin/VcosaDrop nella EEPROM
void EEPROMreset() {
  for (int i = 0; i < quantitaDiDrop; i++) {
    int currentAddr = dataAddrStart + 4 * i;
    EEPROM.write(currentAddr, VGSEE[i]);
    currentAddr++;
    EEPROM.write(currentAddr, VOraEE[i]);
    currentAddr++;
    EEPROM.write(currentAddr, VMinEE[i]);
    currentAddr++;
    EEPROM.write(currentAddr, VcosaDropEE[i]);
  }
  //Serial.println(" FINE EEPROMwrite ");
}

//####################################################################################################
//####################################################################################################

//routine per riportare i dati della EEPROM nelle varibili VGS/VOra/VMin/VcosaDrop
void EEPROMimport() {
  for (int i = 0; i < quantitaDiDrop; i++) {
    int currentAddr = dataAddrStart + 4 * i;
    VGS[i] = EEPROM.read(currentAddr);
    currentAddr++;
    VOra[i] = EEPROM.read(currentAddr);
    currentAddr++;
    VMin[i] = EEPROM.read(currentAddr);
    currentAddr++;
    VcosaDrop[i] = EEPROM.read(currentAddr);
  }
  //Serial.println(" FINE EEPROMimport ");
}

//####################################################################################################
//####################################################################################################

//routine per printare i valori della EEPROM agli indirizzi dati da terminale
//può essere un solo valore o un'intervallo se la fine dell'intervallo è maggiore dell'inizio dà errore
void EEPROMread(int val[7]) {

  if (val[1]) {
    if (val[1] > val[0]) {
      int diff = val[1] + 1 - val[0];
      for (int i = 0; i < diff; i++) {
        Serial.print("addr: "); Serial.print(val[0] + i);
        Serial.print(" dato EEPROM: "); Serial.println(EEPROM.read(val[0] + i));
      }
    } else Serial.println("il valore id fine non può essere maggiure dell'inizio");
  } else {
    Serial.print("indirizzo selezionato: "); Serial.println(val[0]);
    Serial.print("dati EEPROM: "); Serial.println(EEPROM.read(val[0]));
  }
  Serial.println();
}
