import midi
import serial
import struct
import time

# Ouvre une connexion avec le port série spécifié
ser = serial.Serial('/dev/ttyUSB0', baudrate=9600)

# Définit la fonction pour envoyer les données MIDI sur le port série
def send_midi_data(data):
    ser.write(data)

# Définit le chemin du fichier MIDI à lire
midi_file_path = "votre_fichier.mid"

# Lit le fichier MIDI et stocke son contenu dans la variable pattern
pattern = midi.read_midifile(midi_file_path)

# Parcourt chaque piste dans le fichier MIDI et chaque événement dans chaque piste
for track in pattern:
    for event in track:
        # Vérifie si l'événement est de type NoteOnEvent
        if isinstance(event, midi.NoteOnEvent):
            # Encode l'événement MIDI en 3 octets (status, note, velocity)
            status = 0x90 | event.channel  # NoteOn status (0x90) avec le canal MIDI
            data = struct.pack('BBB', status, event.pitch, event.velocity)
            # Envoie les données MIDI sur le port série
            send_midi_data(data)
            # Attend un court instant avant de passer à l'événement suivant
            time.sleep(0.01)

# Ferme la connexion avec le port série une fois que le programme a fini d'envoyer les données
ser.close()print('Hello world!')