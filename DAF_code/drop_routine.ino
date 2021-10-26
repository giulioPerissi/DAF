

//routine per determinare il prossimo drop in base alla differenza tra il tempo attuale e quello dei singoli drop
void dropPrioritario() {
  //printo messaggi vari si o no
  boolean printiamolo = false;

  if (printiamolo) Serial.println("  INIZIO dropPrioritario() ");


  //inizializzo alcune variabili
  //lascio il 100 perchè devo tovare il dato più piccolo e non il più grande quinidi devo partire da un dato grande per poi scendere ai successivi
  int minDataGS = 100;
  int minDataOra = 100;
  int minDataMin = 100;

  int minIGS = 0;
  int minIOra = 0;
  int minIMin = 0;

  //ricavo il tempo attuale
  dt = clock.getDateTime();

  int attualeGS = clock.dateFormat("w", dt);
  int attualeOra = dt.hour;
  int attualeMin = dt.minute;

  //calcolo la differenza con il tempo attuale mettendola nelle apposite variabili
  for (int i = 0; i < 8; i++) {
    VdiffGS[i] = VGS[i] - attualeGS;
    VdiffOra[i] = VOra[i] - attualeOra;
    VdiffMin[i] = VMin[i] - attualeMin;

    if (VdiffGS[i] < attualeGS) VdiffGS[i] = 7 - VdiffGS[i];
    if (VdiffOra[i] < attualeOra) VdiffOra[i] = 24 - VdiffOra[i];
    if (VdiffMin[i] < attualeMin) VdiffMin[i] = 60 - VdiffMin[i];
  }

  for (int i = 0; i < 8; i++) {
    VdiffGS[i] = VGS[i] - attualeGS;
    VdiffOra[i] = VOra[i] - attualeOra;
    VdiffMin[i] = VMin[i] - attualeMin;

    if (VdiffGS[i] < attualeGS) VdiffGS[i] = 7 - VdiffGS[i];
    if (VdiffOra[i] < attualeOra) VdiffOra[i] = 24 - VdiffOra[i];
    if (VdiffMin[i] < attualeMin) VdiffMin[i] = 60 - VdiffMin[i];
  }

  if (printiamolo) {
    for (int i = 0; i < quantitaDiDrop; i++) {
      Serial.print(i);
      //Serial.print("  "); Serial.print(minI3);
      Serial.print("  "); Serial.print(VdiffGS[i]);
      Serial.print("  "); Serial.print(VdiffOra[i]);
      Serial.print("  "); Serial.print(VdiffMin[i]);
      Serial.print("  "); Serial.print(VGS[i]);
      Serial.print("  "); Serial.print(VOra[i]);
      Serial.print("  "); Serial.println(VMin[i]);
    } Serial.println("FINE PERTE 0");
  }

  //trovo il drop col GS più vicino
  for (int i = 0; i < quantitaDiDrop; i++) if (VGS[i] < minDataGS) {
      minDataGS = VdiffGS[i];
      minIGS = i;
    } VPrior[minIGS] = 1;
  for (int i = 0; i < quantitaDiDrop; i++) if (VGS[i] == VGS[minIGS]) VPrior[i] = 1;

  if (printiamolo)   {
    for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 1) {
        Serial.print(i);
        Serial.print("  "); Serial.print(minIGS);
        Serial.print("  "); Serial.print(VPrior[i]);
        Serial.print("  "); Serial.print(VdiffGS[i]);
        Serial.print("  "); Serial.println(VGS[i]);
      } Serial.println("FINE PERTE 1");
  }

  //trovo il drop con l'Ora più vicina
  for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 1) if (VOra[i] < minDataOra) {
        minDataOra = VdiffOra[i];
        minIOra = i;
      } VPrior[minIOra] = 2;
  for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 1 && VOra[i] == VOra[minIOra]) VPrior[i] = 2;

  if (printiamolo)   {
    for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 2) {
        Serial.print(i);
        Serial.print("  "); Serial.print(minIOra);
        Serial.print("  "); Serial.print(VPrior[i]);
        Serial.print("  "); Serial.print(VdiffOra[i]);
        Serial.print("  "); Serial.println(VOra[i]);
      } Serial.println("FINE PARTE 2");
  }

  //trovo il drop col Min più vicino
  for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 2) if (VMin[i] < minDataMin) {
        minDataMin = VdiffMin[i];
        minIMin = i;
      } VPrior[minIMin] = 2;
  for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 2 && VMin[i] == VMin[minIMin]) VPrior[i] = 3;

  if (printiamolo)   {
    for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 3) {
        Serial.print(i);
        Serial.print("  "); Serial.print(minIMin);
        Serial.print("  "); Serial.print(VPrior[i]);
        Serial.print("  "); Serial.print(VdiffMin[i]);
        Serial.print("  "); Serial.println(VMin[i]);
      } Serial.println("FINE PARTE 3");
  }

  if (printiamolo) Serial.println("  FINE dropPrioritario() ");
}

//####################################################################################################
//####################################################################################################



//routine per droppare le cose
void Drop(int NRecipe) {
  //dico quando deve essere dropppato
  Serial.print("Drop previsto: GS ");
  Serial.print(VGS[NRecipe]);
  Serial.print("ore ");
  Serial.print(VOra[NRecipe]);
  Serial.print(",");
  Serial.print(VMin[NRecipe]);

  dt = clock.getDateTime();

  //dico in che momento viene droppato(momento attuale)
  Serial.print("Ora è: ");
  Serial.println(clock.dateFormat("N H:i:s",  dt));

  //dico cosa viene droppato
  for (int i = 0; i < 8; i++) {
    switch (i) {
      case 0: if (bitRead(VcosaDrop[NRecipe], 0)) Serial.println("droppo medicina numero 0"); break;
      case 1: if (bitRead(VcosaDrop[NRecipe], 1)) Serial.println("droppo medicina numero 1"); break;
      case 2: if (bitRead(VcosaDrop[NRecipe], 2)) Serial.println("droppo medicina numero 2"); break;
      case 3: if (bitRead(VcosaDrop[NRecipe], 3)) Serial.println("droppo medicina numero 3"); break;
      case 4: if (bitRead(VcosaDrop[NRecipe], 4)) Serial.println("droppo medicina numero 4"); break;
      case 5: if (bitRead(VcosaDrop[NRecipe], 5)) Serial.println("droppo medicina numero 5"); break;
      case 6: if (bitRead(VcosaDrop[NRecipe], 6)) Serial.println("droppo medicina numero 6"); break;
      case 7: if (bitRead(VcosaDrop[NRecipe], 7)) Serial.println("droppo medicina numero 7"); break;
    }
  }
}

//####################################################################################################
//####################################################################################################

//printo il prossimo drop e i suoi valori
void nextDrop() {
  for (int i = 0; i < quantitaDiDrop; i++) if (VPrior[i] == 3) {
      Serial.print("Next drop is n° "); Serial.println(i);
      Serial.print("  time: ");         Serial.print(VGS[i]); Serial.print("  "); Serial.print(VOra[i]); Serial.print(":"); Serial.println(VMin[i]);
      Serial.print("  tra:");           Serial.print(VdiffGS[i]); Serial.print("  "); Serial.print(VdiffOra[i]); Serial.print(":"); Serial.println(VdiffMin[i]);
      Serial.print("  droppo: ");       Serial.println(VMin[i], BIN);
    }
  Serial.println();
}

//####################################################################################################
//####################################################################################################

//printo tutti i drop
void viewDrop() {
  for (int i = 0; i < quantitaDiDrop; i++) {
    Serial.print("Drop n° ");       Serial.println(i);
    Serial.print("  priority: ");   Serial.print(VPrior[i]);
    Serial.print("  time: ");       Serial.print(VGS[i]); Serial.print("  "); Serial.print(VOra[i]); Serial.print(":"); Serial.println(VMin[i]);
    Serial.print("  tra:");         Serial.print(VdiffGS[i]); Serial.print("  "); Serial.print(VdiffOra[i]); Serial.print(":"); Serial.println(VdiffMin[i]);
    Serial.print("  droppo: ");     Serial.println(VcosaDrop[i], BIN);
  }
  Serial.println();
}

//####################################################################################################
//####################################################################################################

//imposto il valore del drop con le specifiche inserite dal terminale
void setDrop(int DsetDrop[7]) {
  int addrEE = dataAddrStart + 4 * DsetDrop[0];

  EEPROM.write(addrEE, DsetDrop[1]);
  addrEE++;
  EEPROM.write(addrEE, DsetDrop[2]);
  addrEE++;
  EEPROM.write(addrEE, DsetDrop[3]);
  addrEE++;
  EEPROM.write(addrEE, DsetDrop[4]);

  EEPROMimport();

  Serial.print("Drop settato: "); Serial.println(DsetDrop[0]);
  Serial.print(" il: "); Serial.print(DsetDrop[1]);
  Serial.print(" alle: "); Serial.print(DsetDrop[2]);
  Serial.print(":"); Serial.println(DsetDrop[3]);
  Serial.print(" droppo medicine: "); Serial.println(DsetDrop[4], BIN);

  Serial.println("setDrop fine \n");
}
