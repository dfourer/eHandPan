# Projet Ardour — DIY eHandPan

Ce projet fournit exactement deux chemins MIDI.

## 1. Mode expander

```text
MocoLUFA MIDI OUT
        ↓
eHandPan EXPANDER
        ↓
sfizz
        ↓
DIY_eHandPan_14notes.sfz
        ↓
14 samples WAV
        ↓
Master audio
```

## 2. Lecture MIDI vers les LED

```text
Fichier MIDI importé dans Ardour
        ↓
eHandPan MIDI PLAYER -> LEDs
        ↓
MocoLUFA MIDI IN
        ↓
Arduino
        ↓
LED
```

Aucun plugin MIDI intermédiaire n'est utilisé. Les messages du fichier MIDI
sont envoyés tels quels à l'instrument.

## Pré-requis

- Ardour ;
- le plugin sampler sfizz ;
- le périphérique MocoLUFA reconnu en entrée et en sortie MIDI.

Sous Debian/Ubuntu, sfizz peut généralement être installé avec le gestionnaire
de paquets de la distribution.

## Création des pistes

1. Créer ou ouvrir une session vide dans Ardour.
2. Ouvrir `Edit > Lua Scripts > Script Manager`.
3. Importer :
   `Scripts/Create_DIY_eHandPan_Tracks.lua`
4. Exécuter le script.

Il crée :

- `eHandPan EXPANDER`
- `eHandPan MIDI PLAYER -> LEDs`

## Configuration de la piste EXPANDER

1. Insérer l'instrument `sfizz`.
2. Dans sfizz, charger :
   `DIY_eHandPan_14notes.sfz`
3. Sélectionner MocoLUFA comme entrée MIDI de la piste.
4. Armer la piste et activer le monitoring.
5. Vérifier que la sortie audio va vers le bus Master.

## Charger tes propres WAV

Le dossier `Samples` contient 14 fichiers WAV silencieux servant de placeholders.

Remplace-les par tes propres fichiers en conservant exactement les noms :

- A3.wav
- Bb3.wav
- B3.wav
- C4.wav
- Db4.wav
- D4.wav
- Eb4.wav
- E4.wav
- F4.wav
- Gb4.wav
- G4.wav
- Ab4.wav
- A4.wav
- Bb4.wav

Le mapping sera immédiatement conservé. Aucun réglage de note n'est nécessaire.

Il est aussi possible de modifier directement les chemins `sample=` dans le
fichier `DIY_eHandPan_14notes.sfz`.

## Mapping MIDI

| Note MIDI | Nom | Fichier WAV |
|---:|:---:|:---|
| 57 | A3 | A3.wav |
| 58 | Bb3 | Bb3.wav |
| 59 | B3 | B3.wav |
| 60 | C4 | C4.wav |
| 61 | Db4 | Db4.wav |
| 62 | D4 | D4.wav |
| 63 | Eb4 | Eb4.wav |
| 64 | E4 | E4.wav |
| 65 | F4 | F4.wav |
| 66 | Gb4 | Gb4.wav |
| 67 | G4 | G4.wav |
| 68 | Ab4 | Ab4.wav |
| 69 | A4 | A4.wav |
| 70 | Bb4 | Bb4.wav |

## Configuration de la piste MIDI PLAYER

1. Importer ou glisser un fichier `.mid` sur la piste
   `eHandPan MIDI PLAYER -> LEDs`.
2. Dans la sortie de la piste, sélectionner le port MIDI MocoLUFA.
3. Ne pas insérer sfizz sur cette piste.
4. Lancer la lecture.

Ardour transmettra les notes, vélocités, canaux et Note Off au firmware sans
modification.

## Test

Le fichier suivant parcourt les 14 notes :

`MIDI/test_14_notes.mid`

Glisse-le sur la piste `eHandPan MIDI PLAYER -> LEDs`, sélectionne MocoLUFA
comme sortie, puis lance la lecture.

## Pourquoi les ports MocoLUFA ne sont pas préconnectés

Les noms de ports matériels dépendent du système d'exploitation, du backend
MIDI, de la version d'Ardour et parfois du port USB utilisé. Les figer dans un
fichier de session rendrait le projet moins portable. Ardour mémorise les
connexions après leur première sélection et l'enregistrement de la session.
