/*------------------------------------------
   Projet  : Automate MODBUS version 2.0
   Fichier : modbus.h
   Version du fichier : 1.0
   Auteur  : D. KIHN - Institut Limayrac
   Date    : janv 2015
   REF     : 1SN - S7 Reseaux locaux industriels
                   S5 Solutions constructives

   Fonction du module :
      Declarations communes
------------------------------------------*/
// Test commentaire ghcfgdt

#include "Arduino.h"

//---- definitions de l'esclave modbus
#define ESCLAVE 0x04
#define TAILLE_MEMOIRE 30
#define TEMPS_DE_CYCLE_AUTOMATE 2000
extern word memoire[TAILLE_MEMOIRE+1]; // les W1 à W30. Attention les mots commencent à 1 en MODBUS

/*--- definition des registres internes -----
W0001  Temperature interne partie entiere
W0002  Temperature interne partie decimale
W0010  Premier chantillonnage entree analogique A0 - voir sujet de tp
W0029  Echantillonnage n°30 entree analogique A0
--------------------------------------------*/


//--- Le tableau d'octets qui contient la trame recue ou la trame a emettre
#define MAXREQUESTLEN 25
extern byte Request[MAXREQUESTLEN +1];
extern word RequestLen;

//---- Le tampon d'emission et de reception de la liaison serie
#define MAXSERIALBUFFERLEN (MAXREQUESTLEN*2+1)
extern char SerialBuffer[MAXSERIALBUFFERLEN+1];
extern word SerialBufferLen;
extern boolean SerialReceved;

//----- quelques raccourcis d'écriture pour Serial.print -----
#define Print(A) {Serial.print(A);}
#define Print2(A,B) {Serial.print(A);Serial.print(B);}
#define Print3(A,B,C) {Serial.print(A);Serial.print(B);Serial.print(C);}
#define Print4(A,B,C,D) {Serial.print(A);Serial.print(B);Serial.print(C);Serial.print(D);}
#define Println(A) {Serial.println(A);}
#define Println2(A,B) {Serial.print(A);Serial.println(B);}
#define Println3(A,B,C) {Serial.print(A);Serial.print(B);Serial.println(C);}
#define Println4(A,B,C,D) {Serial.print(A);Serial.print(B);Serial.print(C);Serial.println(D);}

