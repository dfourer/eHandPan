/*
 * DIY eHandPan - Arduino firmware
 *
 * Version:      1.02 - Full Version
 * Author:       Dominique Fourer
 * 
 * Date:         13-May-2024
 * Last update:  07-Aug-2026
 * Contact:      dominique@fourer.fr
 *
 * Successfully tested with MocoLUFA.
 */


/* ==========================================================================
 * Debug configuration
 * ========================================================================== */

#define DEBUG   false  // Output piezo velocity values on the serial port
#define DEBUGL  false  // LED/MIDI input debugging
#define DEBUGG  false  // Measure loop execution time


/* ==========================================================================
 * MIDI constants
 * ========================================================================== */

const int noteON        = 0x90;   // MIDI Note On command
const int noteOFF       = 0x80;   // MIDI Note Off command
const int transpo       = 0;      // Global MIDI transposition
const int INVALID_PITCH = -1;


/* ==========================================================================
 * Piezoelectric sensor configuration
 * ========================================================================== */

const int led       = 13;    // Built-in Arduino LED
const int period_ms = 1;     // Main loop period in milliseconds
const int min_dur   = 80;    // Minimum note duration / retrigger protection (ms)
const int seuil     = 200;   // Piezoelectric impact detection threshold

const unsigned int maxi = 1024;   // ADC range (10-bit Arduino ADC)


/* ==========================================================================
 * Incoming MIDI state
 * ========================================================================== */

int midiCommand;
int midiChannel;
int midiNote;
int midiVelocity;


/* ==========================================================================
 * MIDI output
 * ========================================================================== */

/**
 * Send a three-byte MIDI message through the hardware serial port.
 *
 * command:      MIDI Note On or Note Off command
 * MIDInote:     MIDI pitch in [0, 127]
 * MIDIvelocity: MIDI velocity in [0, 127]
 * channel:      MIDI channel in [1, 16]
 */
void MIDImessage(int command, int MIDInote, int MIDIvelocity, int channel = 1)
{
    Serial.write(command + (channel - 1));
    Serial.write(MIDInote);
    Serial.write(MIDIvelocity);
}


/**
 * Reset the active-note buffer.
 */
void empty_buffer(int *current_notes, int maxPoly)
{
    for (int i = 0; i < maxPoly; ++i) {
        current_notes[i] = 0;
    }
}


/* ==========================================================================
 * Hardware-dependent configuration
 * ========================================================================== */

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)

/* --------------------------------------------------------------------------
 * Arduino Mega - 14-note configuration
 * -------------------------------------------------------------------------- */

const char ver[] = "Mega";

const int nports = 14;

const int ports[nports] = {
    A0, A1, A2, A3, A4, A5, A6,
    A7, A8, A9, A10, A11, A12, A13
};

const char *notesp[nports] = {
    "Bb3", "Db4", "Eb4", "Gb4", "Ab4", "Bb4",
    "A3",  "B3",  "C4",  "D4",  "E4",  "F4", "G4", "A4"
};

const int notes[nports] = {
    58, 61, 63, 66, 68, 70,
    57, 59, 60, 62, 64, 65, 67, 69
};

/* Right hand = red LED */
const int ledDroite[nports] = {
    22, 24, 26, 28, 30, 32, 34,
    36, 38, 40, 42, 44, 46, 48
};

/* Left hand = green LED */
const int ledGauche[nports] = {
    23, 25, 27, 29, 31, 33, 35,
    37, 39, 41, 43, 45, 47, 49
};

#else

/* --------------------------------------------------------------------------
 * Arduino Uno - 6-note configuration
 * -------------------------------------------------------------------------- */

const char ver[] = "Uno";

const int nports = 6;

const int ports[nports] = {
    A0, A1, A2, A3, A4, A5
};

const char *notesp[nports] = {
    "Bb3", "Db4", "Eb4", "Gb4", "Ab4", "Bb4"
};

const int notes[nports] = {
    58, 61, 63, 66, 68, 70
};

/* Right hand = red LED */
const int ledDroite[nports] = {
    2, 4, 6, 8, 10, 12
};

/* Left hand = green LED */
const int ledGauche[nports] = {
    3, 5, 7, 9, 11, 13
};

#endif


/* Active-note hold-off counters */
int current_notes[nports];


/* ==========================================================================
 * MIDI pitch lookup
 * ========================================================================== */

/**
 * Return the sensor index corresponding to a MIDI pitch.
 *
 * Returns INVALID_PITCH when the pitch is not part of the current instrument
 * configuration.
 */
int ajusterPitch(int pitch)
{
    if (pitch < 0 || pitch > 127) {
        return INVALID_PITCH;
    }

    for (int i = 0; i < nports; ++i) {
        if (notes[i] == pitch) {
            return i;
        }
    }

    return INVALID_PITCH;
}


/* ==========================================================================
 * Arduino initialization
 * ========================================================================== */

void setup()
{
    /*
     * Debug modes use a conventional serial connection.
     * Normal MocoLUFA operation requires the standard MIDI baud rate.
     */
    if (DEBUG || DEBUGL) {
        Serial.begin(9600);
    }
    else {
        Serial.begin(31250);
    }

    pinMode(led, OUTPUT);

    empty_buffer(current_notes, nports);

    /* Configure all LED pins as outputs */
    for (int i = 0; i < nports; ++i) {
        pinMode(ledDroite[i], OUTPUT);
        pinMode(ledGauche[i], OUTPUT);
    }
}


/* ==========================================================================
 * Main loop
 * ========================================================================== */

void loop()
{
    unsigned long t = 0;

    if (DEBUGG) {
        t = micros();
    }


    /* ----------------------------------------------------------------------
     * Piezoelectric sensor acquisition
     * ---------------------------------------------------------------------- */

    for (int i = 0; i < nports; ++i) {

        /* Read the raw 10-bit ADC value */
        const int data = analogRead(ports[i]);

        /*
         * Trigger a new note when:
         *   - the signal exceeds the detection threshold;
         *   - the corresponding note is currently inactive.
         */
        if (data > seuil && current_notes[i] <= 0) {

            digitalWrite(led, HIGH);

            /*
             * Start the hold-off counter to prevent repeated Note On events
             * caused by the oscillatory piezoelectric waveform.
             */
            current_notes[i] = min_dur;

            /*
             * Map the 10-bit ADC amplitude [0, 1023]
             * to the MIDI velocity range [0, 127].
             */
            const int vel = ((float)data / 1024.0f) * 127.0f;

            if (DEBUG) {
                Serial.print(vel);
            }
            else {
                MIDImessage(
                    noteON,
                    notes[i] + transpo,
                    vel
                );
            }
        }
        else {

            digitalWrite(led, LOW);

            if (DEBUG) {
                Serial.print(0);
            }

            /* Decrement the active-note duration */
            if (current_notes[i] >= 0) {
                current_notes[i] -= period_ms;
            }

            /* Send Note Off when the hold-off counter reaches zero */
            if (current_notes[i] == 0) {

                if (!DEBUG) {
                    MIDImessage(
                        noteOFF,
                        notes[i] + transpo,
                        0
                    );
                }
            }
        }

        /* CSV separator used only in sensor debug mode */
        if (DEBUG && i < nports - 1) {
            Serial.print(",");
        }
    }


    if (DEBUG) {
        Serial.println();
    }


    /* ----------------------------------------------------------------------
     * Incoming MIDI messages and LED control
     * ---------------------------------------------------------------------- */

    if (Serial.available() >= 3) {

        /* Read MIDI status byte */
        midiCommand = Serial.read();

        /* Extract MIDI channel and command */
        midiChannel = midiCommand & 0x0F;
        midiCommand = midiCommand & 0xF0;


        if (DEBUGL) {
            Serial.print("Incoming MIDI command: ");
            Serial.println(midiCommand);
        }


        /* Only Note On and Note Off messages are handled */
        if (midiCommand != noteON && midiCommand != noteOFF) {

            if (DEBUGL) {
                Serial.println("Unsupported MIDI command");
            }
        }
        else {

            midiNote     = Serial.read();
            midiVelocity = Serial.read();

            const int ledstate =
                (midiCommand == noteON) ? HIGH : LOW;

            const int pitch_index =
                ajusterPitch(midiNote);


            /* Ignore pitches that are not mapped to a playing surface */
            if (pitch_index != INVALID_PITCH) {

                int hand = -1;

                /*
                 * A Note Off message turns both LED colors off.
                 */
                if (ledstate == LOW) {

                    digitalWrite(
                        ledGauche[pitch_index],
                        LOW
                    );

                    digitalWrite(
                        ledDroite[pitch_index],
                        LOW
                    );
                }
                else {

                    /*
                     * Hand selection follows the original firmware logic.
                     *
                     * Velocity parity and the MIDI channel are used to
                     * determine which LED color is activated.
                     */
                    if ((midiVelocity & 0x01) == 1 &&
                        midiChannel == 0 ||
                        midiChannel > 0) {

                        /* Green LED = left hand */
                        digitalWrite(
                            ledGauche[pitch_index],
                            ledstate
                        );

                        hand = 1;
                    }
                    else {

                        /* Red LED = right hand */
                        digitalWrite(
                            ledDroite[pitch_index],
                            ledstate
                        );

                        hand = 0;
                    }
                }


                /* Optional incoming-MIDI diagnostics */
                if (DEBUGL) {

                    Serial.print("Command: ");
                    Serial.println(
                        midiCommand == noteON ?
                        "Note On" :
                        "Note Off"
                    );

                    Serial.print("Channel: ");
                    Serial.println(midiChannel);

                    Serial.print("MIDI pitch: ");
                    Serial.println(
                        notesp[pitch_index]
                    );

                    if (hand >= 0) {
                        Serial.print("Hand: ");
                        Serial.println(
                            hand == 0 ?
                            "Right" :
                            "Left"
                        );
                    }
                }
            }
            else if (DEBUGL) {
                Serial.println("MIDI pitch not mapped");
            }
        }
    }


    /* ----------------------------------------------------------------------
     * Loop synchronization
     * ---------------------------------------------------------------------- */

    delay(period_ms);


    /* ----------------------------------------------------------------------
     * Execution-time diagnostics
     * ---------------------------------------------------------------------- */

    if (DEBUGG) {

        t = micros() - t;

        Serial.print("Execution time: ");
        Serial.print(t);
        Serial.println(" us");
    }
} 
