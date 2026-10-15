# DIY e-HandPan

- Contributors: B. Collin, D. Fourer and E. Genotelle

**DIY e-HandPan** is an open-source electronic handpan designed for makers, musicians, educators, and researchers.

The project combines a custom electronic instrument based on piezoelectric sensors, RGB LEDs, and an ESP32-S3 microcontroller with a complete set of hardware documentation, firmware, and assembly instructions. The objective is to provide a low-cost, reproducible, and fully hackable electronic handpan suitable for education, prototyping, and musical performance.


If you use this work, please cite our paper

B. Collin, D. Fourer and E. Genotelle et al. A new low-cost DIY e-HandPan instrument based on Aruino Microcontroller. arXiv preprint arXiv:2608.10185

```bibtex
@article{collin2026diyehandpan,
  title={DIY e-HandPan: A new DIY Low-Cost Handpan Interface based on Arduino and ESP32 Microcontrollers}, 
  author={Benoit Collin and Dominique Fourer and Eric Genotelle},
  journal={arXiv preprint arXiv:2608.10185},
  year={2026},
  primaryClass={cs.SD},
  url={https://arxiv.org/abs/2608.10185}, 
}
```

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
│   ├── projet_ardour8/ # Example of MIDI Expander project based on Ardour 8
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

## Construction tutorials

The complete construction guide is available in the `instructions/` directory.

Step-by-step video tutorials are available to complement the written
assembly instructions provided in this repository.

The tutorials illustrate the main construction steps, including:

- mechanical assembly of the salad bowls and playing surfaces;
- installation of the piezoelectric sensors and bi-color LEDs;
- wiring and soldering;
- DB25 connector assembly;
- Arduino and ESP32 electronic integration;
- firmware installation and configuration;
- final testing of the instrument.

🎥 **YouTube construction tutorials:** [e-HandPan construction tutorials](https://www.youtube.com/playlist?list=PL_k3PczvzYDb-f5t7U6dC4wk6cq4hSw6F)

The videos are intended as complementary visual guidance. All information
required to reproduce the instrument is also provided in this repository.



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

---

## License

The DIY e-HandPan project is distributed under the following licenses:

Software: The Arduino and ESP32 firmware are released under the MIT License.

Hardware: The electronic schematics, PCB designs, and associated hardware design files are released under the CERN Open Hardware Licence Version 2 – Permissive (CERN-OHL-P-2.0).

Documentation: The original assembly instructions, tutorials, and project documentation are released under the Creative Commons Attribution 4.0 International License (CC BY 4.0).

Audio samples: Licensing information and attribution are provided separately for the audio resources. Redistribution and reuse are subject to the rights associated with each sample.

Copyright © 2026 Benoit Collin, Dominique Fourer and Eric Genotelle.

The applicable license is determined by the type of material. 

See the `LICENSE` file for details.

