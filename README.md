# eHandPan

- Contributors: D. Fourer, B. Collin
- Students: Alycia ISSAD, Sofiane MEDJBOUR

If you use this work, please cite

D. Fourer and B. Collin. A new low-cost DIY eHandPan instrument based on Aruino Microcontroller. Arxiv...

# Parts of the project (arduino)
- HandPanPiezo.ino: Reads Analog signal from Piezo and emits a MIDI message (works with MocoLUFA, arduino Mega/Uno)
- HandPanTestLED.ino: Emits Signals to Digital ports for testing LED
- HandPanLED.ino: Process input MidiMessages and command LED

# Parts of the project (python)
- MidiLEDPlay.py: Reas a midi file and send Message to serial port


# tools
- MocoLuFA : firmware for simulating a Midi Instrument using Arduino Mega / Uno
- dfu-programmer: tool for flashing arduino firmware
