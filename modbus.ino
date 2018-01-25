/*------------------------------------------
   Projet  : Automate MODBUS version 2.0
   Fichier : modbus.ino
   Version du fichier : 1.0
   Auteur  : D. KIHN - Institut Limayrac
   Date    : janv 2015
   REF     : 1SN - S7 Reseaux locaux industriels
                   S5 Solutions constructives

   Fonction du module :
        Ce module comprend les fonctions principales
------------------------------------------*/
#include "modbus.h"

/*-------------- Variables globales du programme ----*/
word memoire[TAILLE_MEMOIRE+1];	// Les registres MODBUS W0001 à W0030 (mots de 16 bits)
byte Request[MAXREQUESTLEN +1]; // La requete du maitre ou la reponse de l'esclave (le tableau d'octets)
word RequestLen=0;	        // La requete du maitre ou la reponse de l'esclave (sa taille)
char SerialBuffer[MAXSERIALBUFFERLEN+1]; // le tampon de la liaison serie (le tableau d'octets)
word SerialBufferLen=0;                  // le tampon de la liaison serie (sa taille)
boolean SerialReceved=false;             // le tampon de la liaison serie est vide (pour l'instant)


/*-------  Fonction d'intialisation ---------*/
void setup(){
    for( int i=0; i<=TAILLE_MEMOIRE ; i++) memoire[i]=0; memoire[3]=0xABCD; // initialisation de la memoire
    Serial.begin(9600); // ATTENTION choisissez NL & CR dans le moniteur
    pinMode(13, OUTPUT); // Sortie sur la LED
    pinMode(A0, INPUT);  // entree sur le CAN 0
    delay(2000);
    Serial.println(":)");
}

/*------  La bouckle principale -------------*/
void loop(){        
    if( Serial.available() > 0 ){ SerialReadLine(); return; }
    if( SerialReceved ){ TraiterRequete(); return; }
    if( faire_un_cycle() ){
        //---- acquisition cyclique des valeurs toutes les TEMPS_DE_CYCLE_AUTOMATE millisecondes
        PORTB ^= 0x20;     // pour "voir" la LED changer a chaque cycle
        getInternalTemp(); // mesurer temperature interne
        //---- AJOUTEZ ICI VOS PROPRES SCRUTATIONS --------------
        getEtatDuCapteur();// votre propre acquisition de quelque chose
    }
}


boolean TraiterRequete( void ){
     //---- Decodage trame ASCII -> RTU
     Println2("Requete du maitre    : ", SerialBuffer); 
     SerialBufferVersRequete(); 
     LibererSerialBuffer();
     //----------- cette requete est-elle pour nous ? ---------------------------------
     if( Request[0] != ESCLAVE ) return exception( "Requete adressee a un autre esclave.");
     
     //----------- traitement de la requete du maitre ---------------------------------
     switch( Request[1] ){
     case 0x03: //fonction lecture
          if( !ModBusFonctionLire() ) return false;
          break;
     case 0x41: //fonction 65 identification
//          if( !ModBusFonctionIdentification() ) return false;
//          break;
     default: // fonction non reconnue
          RepondreErreur( 0x01 ); // illegal function
          break;
     } 
     //---- Encodage trame RTU -> ASCII
     RequeteVersSerialBuffer(); 
     Println2("Reponse de l'esclave : ", SerialBuffer);
     Println( ":)" ); // afficher le prompt
     LibererSerialBuffer();
}




