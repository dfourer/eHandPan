/*

 Version 3.26 sp  -   buffer - (serial port, latency problem)
 
 Authors.  D. Fourer, B. Collin
 Date:  08-jan-2024
 Last update: 27-march-2024
 Contact: dominique@fourer.fr
 
 Successfuly tested with MocoLufa
 
*/
#define DEBUG  false     //display signal on each analog port
#define DEBUGG  false      //compute execution time at each loop


/* 
  Predefined const for executing prog

*/
const int noteON  = 0x90; //144;//144 = 10010000 in binary, note on command
const int noteOFF = 0x80; // 128;//128 = 10000000 in binary, note off command, 0x80
const int transpo = 12;

const int led   = 13;          //led on arduino card
const int period_ms = 1;       // time interval on each loop()

const int min_dur = 80; //10;         //7; //min duration of an active note expressed in ms (to avoid repeated notes)

//0 tested
const int seuil = 120; //100;             //80; //80; //100; //150  signal threshold for active note
const unsigned int maxi = 1024;    //maximal value of an analogical port

// Function that writes a MIDI event to serial port   (no lib needed to work)
/*
command : noteOn / noteOff
pitch midi : 0 - 127
vel: 0-127
chan: 1:16

*/
void MIDImessage(int command, int MIDInote, int MIDIvelocity, int channel=1) {
  Serial.write(command+(channel-1));//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

// Function used to clear a buffer array
void empty_buffer(int *current_notes, int maxPoly)
{
  for(int i=0;i < maxPoly; i++)
  {
    current_notes[i] = 0;
  }
}



// Conditional compilation for Arduino Mega (14 notes) and Arduino Uno (6 notes) compatibility
#if ((defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)))
// code for an MEGA goes here
  const int nports = 14;  //number of avail notes
  
  const int ports[14]   = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13};   //arduino analogical ports IDs
  //gnd - blanc
  //const char* color[14]  = {"C1:marron-bleu", "C1:violet-bleu", "C1:bleuciel-vert", "C1:orange-vert", "C1:jaune-vert", "C1:gris-vert", 
  //                    "C2:jaune-vert", "C2:orange-rouge", "C2:dore-rouge", "C2:blanc-rouge", "C2:bleuciel-rouge", "C2:violet-rouge",
  //                    "C2:marron-rouge", "C2:gris-rouge"};
  
  const char* notesp[14] = {"Bb2", "Db3", "Eb3", "Gb3", "Ab3", "Bb3",
                      "A2", "B2", "C3", "D3", "E3", "F3", "G3", "A3"};   //notes names
  
  //A2 = 45
  const int notes[14] = {46, 49, 51, 54, 56, 58,
                   45, 47, 48, 50, 52, 53, 55, 57};   //midi pitchs
  
  char ver[] = "Mega";
#else  
// code for an UNO goes here
 const char* notesp[6] = {"Bb2", "Db3", "Eb3", "Gb3", "Ab3", "Bb3"};
 const int nports = 6;
 const int ports[6] = {A0, A1, A2, A3, A4, A5};
 const int notes[6] = {45, 49, 51, 54, 56, 58};
 const char ver[] = "Uno";
#endif

int current_notes[nports];              // buffer of actives notes, initialized at 0

///////////////////////////////////////////////////////////////////////// Init  serial port and LED 13 (on board), executed once
void setup() {
  pinMode(led, OUTPUT); 
  
  if(DEBUG)
    Serial.begin(115200);   //serial port speed, 115200
  else
    Serial.begin(31250); //MocoLufa 
  //31250
  
  empty_buffer(current_notes, nports);
}




///////////////////////////////////////////////////////////////////////// Program starts here ;-)

void loop() {
  
  int data;                               // raw value of an analogical port

  unsigned long t;                        // used for DEBUGG, to measure execution time in micro seconds
  if(DEBUGG) {
    t = micros();                        //predefined function that returns the current time in micro seconds (since power on)
  }
  
  // read signal on all analogical available ports and check buffer
  for(int i=0;i<nports;i++)
  {
    
    data = analogRead(ports[i]);      //returns raw value of signal at analogical port i
    
    // 
    if(data > seuil && current_notes[i] <= 0) //if note is active (above threshold and note yet activated )
    {
      
      digitalWrite(led, HIGH);          //turn on led 13
     
      current_notes[i] = min_dur;        //store the min duration  (avoid repeated noteON)
     
      int vel =  ((float)data/1024)*127; //120; // adaptative velocity (maps signal in [0;1023]   to [0;127]  (Midi velocity, check max value)
      //int vel = (int) (map(data,0,1023,0,127)); //alternative implementation to check
     
      if(DEBUG)   //if debug, display the velocity for each port  (result is openable by Excel as CSV file)
      {
        //Serial.print(data);
        Serial.print(vel);
       
        //add more debug info if needed (leave commented)
        //Serial.print("A");
        //Serial.print(i);
        //Serial.print("   ");
        //Serial.print(notesp[i]);
        //Serial.print("   ");
        //Serial.print(" =");
        //Serial.print(data);
        //Serial.print("version");
        //Serial.println(ver);
       }
       else     //if not debug, send Midi code
       {
         MIDImessage(noteON, notes[i]+transpo, vel);
       }
    }
    else  //signal under threshold and note possibly not yet active
    {
       digitalWrite(led, LOW);   //turn off led
        
       if(DEBUG)
       {
         Serial.print(0);
       }
       
       if( current_notes[i] >= 0)    //decrement the current active note duration
         current_notes[i] -= period_ms;
         
       if( current_notes[i] == 0 ) // if 0 is reached, Midi NoteOff event is send
       {
         if(DEBUG)
         {
           // Natural ending note
         }
         else
         {
             //Note off
            MIDImessage(noteOFF, notes[i]+transpo, 0);
         }
       }
    }
    
    
    if(DEBUG && i < nports-1)  //used only for debug
    {
      Serial.print(",");
    }
  } //for 
  
  if(DEBUG)
    Serial.print("\n");
    
       
  //delay for synchronicity (useless)  
  delay(period_ms);   // 1000 Hz
  
  
  if(DEBUGG)
  {
    t = micros()-t;
    Serial.print("Execution time ");
    Serial.print(t);
    Serial.println(" micro seconds");
  }
 
}

// EOF
