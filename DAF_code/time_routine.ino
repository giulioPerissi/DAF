

//routine principale dell'allarme
void bugiaESuonataLaSveglia() {
  //droppo ciò che ha il valore di priorità 3
  for (int i = 0; i <= quantitaDiDrop; i++) {
    if (VPrior[i] == 3) Drop(i);
  }

}

//####################################################################################################
//####################################################################################################


//impostare le prossime assunzioni
void setNextAlarm(int dati[]) {
  //cancello l'allarme
  clock.armAlarm1(false);
  clock.clearAlarm1();

  //setto l'allarme con le informazioni nella stringa dati ->solo se il primo carattere è abilitato<- (non usato)
  if (dati[0]) {
    clock.setAlarm1(dati[1], dati[2], dati[3], dati[4],  DS3231_MATCH_DY_H_M_S);

    //leggo l'allarme e lo printo
    RTCAlarmTime a1;
    Serial.print("Prossima Assunzione: ");
    Serial.println(clock.dateFormat("l H:i:s", a1));
  }
  //altrimenti printo che non è stato impostato nessun allarme (no perchè le variabili attive non le uso
  else Serial.println("Nessun allarme impostato"); //al

  delay(10);
}


//####################################################################################################
//####################################################################################################

//routine per printare il tempo attuale
void timeNow() {
  //leggo il tempo
  dt = clock.getDateTime();

  //lo printo
  Serial.println("Now it's:");
  Serial.println("  dd-mm-YYYY l HH:ii:ss");
  Serial.print("  "); Serial.println(clock.dateFormat("d-m-Y l H:i:s", dt));
  Serial.println();
}


//####################################################################################################
//####################################################################################################

//routine per settare il tempo
void timeSet(int DtimeNow[5]) {
  //setto il tempo
  clock.setDateTime(DtimeNow[0], DtimeNow[1], DtimeNow[2], DtimeNow[3], DtimeNow[4], DtimeNow[5]);

  timeNow();

  //bisogna aggiungere una parte di verifica del formato dei dati che vengono inseriti e che rispettino il minimo e massimo (es. ora tra 0 e 23)
  if (true) Serial.println("time set correctly");
  else Serial.println("Cheicos lè andaita mal");
}
