# DIY eHandPan

- Contributors: B. Collin, D. Fourer and E. Genotelle

**DIY eHandPan** is an open-source electronic handpan designed for makers, musicians, educators, and researchers.

The project combines a custom electronic instrument based on piezoelectric sensors, RGB LEDs, and an ESP32-S3 microcontroller with a complete set of hardware documentation, firmware, and assembly instructions. The objective is to provide a low-cost, reproducible, and fully hackable electronic handpan suitable for education, prototyping, and musical performance.


If you use this work, please cite our paper

B. Collin, D. Fourer and E. Genotelle et al. A new low-cost DIY eHandPan instrument based on Aruino Microcontroller. Arxiv...

---

## Features

* 🥁 14 pressure-sensitive playing pads
* 🎵 Low-latency audio engine running on ESP32-S3
* 💡 Individual RGB LED feedback for each note
* 🌐 Embedded Wi-Fi configuration interface
* 🎼 MIDI support
* 🔊 Multiple sample banks
* 🔧 Fully open-source hardware and software
* 📚 Complete DIY assembly documentation

---

## Repository structure

```
.
├── eHandPan/
│   ├── ESP32/          # Main firmware (PlatformIO)
│   ├── Arduino/        # Early Arduino prototypes
│   ├── AudioSamples/   # WAV sample libraries
│   ├── MidiLEDPlay/    # MIDI demonstration files
│   └── tools/          # Programming and utility tools
│
├── instructions/       # Assembly manual (LaTeX + PDF)
│
├── handpan.mp4         # Demonstration video
│
└── LICENSE
```

---


## Hardware

The instrument is built around:

* ESP32-S3
* Piezoelectric sensors
* Analog conditioning electronics
* LED feedback system
* Stereo audio output
* Custom mechanical assembly based on stainless steel bowls

The complete construction guide is available in the `instructions/` directory.


## ARDUINO

# firmware
- HandPanPiezo.ino: Reads Analog signal from Piezo and emits a MIDI message (works with MocoLUFA, arduino Mega/Uno)
- HandPanTestLED.ino: Emits Signals to Digital ports for testing LED
- HandPanLED.ino: Process input MidiMessages and command LED

# Parts of the project (python)
- MidiLEDPlay.py: Reas a midi file and send Message to serial port


# tools
- MocoLuFA : firmware for simulating a Midi Instrument using Arduino Mega / Uno
- dfu-programmer: tool for flashing arduino firmware



---

## EPS 32 

The main firmware is located in:

```
eHandPan/ESP32/
```

The project uses:

* PlatformIO
* ESP32-S3
* FreeRTOS
* Embedded Web Server
* Audio sample playback
* MIDI support

Precompiled firmware images are available in:

```
eHandPan/ESP32/firmware/
```

---


## Building the firmware

Install PlatformIO and compile:

```bash
cd eHandPan/ESP32
pio run
```

To upload:

```bash
pio run --target upload
```

---
## Documentation

This repository includes:

* Assembly manual
* Electronic schematics
* Hardware analyses
* Signal measurements
* Datasheets
* Development notes
* Audio samples

---

## Contributing

Contributions are welcome.

You can contribute by:

* improving the firmware;
* designing new hardware revisions;
* adding sound banks;
* improving documentation;
* reporting bugs.

Please open an Issue or submit a Pull Request.

---

## Authors

DIY eHandPan was created by B. Collin, D. Fourer and E. Genotelle

See the publication for the complete list of contributors.

---

## License

This project is released under the MIT License.

See the `LICENSE` file for details.

