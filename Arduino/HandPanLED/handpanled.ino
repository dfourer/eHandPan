/*

 Version 1.0
 
 Authors.  A. Issad, S. Medjbour, D. Fourer
 Date:  15-04-2024
 Last update: 17-04-2024
 Contact: dominique.fourer@univ-evry.fr
 i
*/
#define DEBUG true     //display signal on each analog port

// Définition des constantes MIDI
const int NOTE_ON_COMMAND = 0x90;
const int NOTE_OFF_COMMAND = 0x80;
const int INVALID_PITCH = -1;


// Variables pour stocker les informations MIDI
int midiCommand;
int midiChannel;
int midiNote;
int midiVelocity;

// Définition des notes
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  const int N = 14;
  const char* notesp[14] = {"Bb2", "Db3", "Eb3", "Gb3", "Ab3", "Bb3", "A2", "B2", "C3", "D3", "E3", "F3", "G3", "A3"};
  const int notes[14]    = {46, 49, 51, 54, 56, 58, 45, 47, 48, 50, 52, 53, 55, 57};
  const int ledDroite[]  = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48}; // Broches pour les LEDs de la main droite (rouge)
  const int ledGauche[]  = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49}; // Broches pour les LEDs de la main gauche (verte)
#else
  const int N = 6;
  const char* notesp[6]  = {"Bb2", "Db3", "Eb3", "Gb3", "Ab3", "Bb3"};
  const int notes[6]     = {45, 49, 51, 54, 56, 58};
  const int ledDroite[]  = {2, 4, 6, 8, 10, 12}; // Broches pour les LEDs de la main droite (rouge)
  const int ledGauche[]  = {3, 5, 7, 9, 11, 13}; // Broches pour les LEDs de la main gauche (verte)
#endif

// Fonction pour ajuster le pitch dans la plage [45; 58]
int ajusterPitch(int pitch) {
  int pitch_index = INVALID_PITCH;
  
  if(pitch<0 || pitch > 127)
    return pitch_index;
    
  // Si le pitch est inférieur à 45, ramener à la note la plus basse (45)
  while (pitch < 45) {
    pitch += 12; // Ajouter 12 pour ramener dans la plage [45; 58]
  }

  // Si le pitch est supérieur à 58, ramener à la note la plus haute (58)
  while (pitch > 58) {
    pitch -= 12; // Soustraire 12 pour ramener dans la plage [45; 58]
  }

  
  //final , check if the note index exists in range
  int i = 0;
  while(i < N) {
    if(notes[i] == pitch)
    {
       //note found
       pitch_index = i;
       break;
    }
    i++;
  }

  return pitch_index;
}



void setup() {
  Serial.begin(9600); // Initialisation de la communication série à 9600 bauds

  // Configuration des broches des LEDs en sortie
  for (int i = 0; i < N; i++) {
    pinMode(ledDroite[i], OUTPUT);
    pinMode(ledGauche[i], OUTPUT);
  }
}


void loop() {
  // Vérifie si des données sont disponibles sur le port série
  if (Serial.available() >= 3) {
    
    // Lecture des trois octets entrants
    midiCommand  = Serial.read();
    
    midiChannel  = midiCommand & 0x0F;
    midiCommand  = midiCommand & 0xF0;
    
    
    if(midiCommand != NOTE_ON_COMMAND &&  midiCommand != NOTE_OFF_COMMAND) 
    {
      // Invalid Command, skip..

    }
    else
    {
      midiNote     = Serial.read();
      midiVelocity = Serial.read();
      
      int ledstate = (midiCommand==NOTE_ON_COMMAND)?HIGH:LOW;
      int pitch_index = ajusterPitch(midiNote);
      int hand;
      
      if(pitch_index == INVALID_PITCH) {
        // invalid pitch, skip
      }
      else {
        // Hand is deduced from the velocity parity bit and from the channel number
        
        if( (midiVelocity & 0x01) == 1 && midiChannel == 0 || midiChannel > 0 ) {
          digitalWrite(ledGauche[pitch_index], ledstate);
          hand = 1;
        }
        else {
          digitalWrite(ledDroite[pitch_index], ledstate);
          hand = 0;
        }
       } //invalid pitch
      
      
        if(DEBUG) {
          // Affichage des informations MIDI
          Serial.print("Commande: ");
          Serial.println(midiCommand==NOTE_ON_COMMAND?"NoteON":"NoteOff");
          Serial.print("Channel: ");
          Serial.println(midiChannel);
          Serial.print("Pitch Midi: ");
          Serial.println(notesp[pitch_index]);
          Serial.print("Hand: ");
          Serial.println(hand==0?"Droite":"Gauche");
        }

     }
  } //3 bytes avail
} //loop

