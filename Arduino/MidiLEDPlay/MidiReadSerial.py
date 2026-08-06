#!/usr/bin/python3
import serial as ser
import serial.tools.list_ports
import time
import midi



#  Programme de lecture d un fichier midi pour arduino
#
#

# Definition des constantes MIDI
NOTE_ON_COMMAND = 0x90
NOTE_OFF_COMMAND = 0x80

# Notes dfinies en Arduino
notes = [45, 49, 51, 54, 56, 58]

# Fonction pour trouver le port serie de l'Arduino
def trouver_port_serie():
    ports_disponibles = serial.tools.list_ports.comports()
    for port in ports_disponibles:
        if 'n/a' not in port[2]:  #Arduino
            return port[0]
    return None


# Configuration du port serie
port = trouver_port_serie()

ser = serial.Serial(port, 9600)  # Port serie sur Windows '/dev/ttyACM0'

if ser is None:
    print("No Arduino port found.")
    exit()
else:
	print("Detected port: {}".format(port))
	
	

# Fonction pour envoyer un message MIDI
def envoyer_message_midi(commande, note, velocite):
    ser.write(bytes([commande, note, velocite]))

# Boucle pour envoyer les 6 notes
for i in range(len(notes)):
	
	message_midi = {
        'commande': NOTE_ON_COMMAND,
        'note': notes[i],
        'velocite': 100  # Valeur de velocite (0-127)
	}

    # Envoi du message MIDI
	envoyer_message_midi(message_midi['commande'], message_midi['note'], message_midi['velocite'])
	print("Note envoyee:", message_midi['note'])
	time.sleep(2)
	envoyer_message_midi(NOTE_OFF_COMMAND, message_midi['note'], message_midi['velocite'])
	
	message_midi = {
        'commande': NOTE_ON_COMMAND,
        'note': notes[i],
        'velocite': 101  # Valeur de velocite (0-127)
	}
	
	# Envoi du message MIDI
	envoyer_message_midi(message_midi['commande'], message_midi['note'], message_midi['velocite'])
	print("Note envoyee:", message_midi['note'])
	time.sleep(2)
	envoyer_message_midi(NOTE_OFF_COMMAND, message_midi['note'], message_midi['velocite'])
	
	

# Fermeture du port serie
ser.close()
