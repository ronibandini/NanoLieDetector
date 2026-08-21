# 🤥📟 Kinski Polygraph — Arduino Nano Lie Detector

**A small polygraph that combines heart-rate sensing, galvanic skin response, two vintage analog VU meters, and an audible alert.**

Kinski Polygraph — the `NanoLieDetector` project — was built after a copy of **Klaus Kinski's autobiography** disappeared during a dinner with fellow writers.

Instead of sending an accusatory email, the response was to build a small homemade polygraph.

The device measures two physiological signals:

- ❤️ pulse / heart-rate activity
- 💧 galvanic skin response (GSR)

An **Arduino Nano** processes those signals and drives two analog VU meters. One meter reacts to the pulse sensor, while the other displays changes in skin conductivity. A buzzer provides an additional alert when the programmed conditions are reached.

```text
                 Person
                   │
          ┌────────┴────────┐
          │                 │
          ▼                 ▼
    Heart-rate          GSR electrodes
      sensor            aluminum foil
          │                 │
          ▼                 ▼
      Arduino Nano ←── Analog input
          │
      ┌───┴─────────────┐
      │                 │
      ▼                 ▼
 Pulse VU meter    GSR VU meter
      │                 │
      └────────┬────────┘
               │
               ▼
             Buzzer
```

> The machine measures physiological arousal, not truth itself. Heart rate and skin conductance can change for many reasons unrelated to deception.

---

## ✨ Features

- 🧮 Arduino Nano controller
- ❤️ Heart-rate sensor
- 💧 Galvanic skin response measurement
- 📟 Two analog VU meters
- ⚡ PWM-driven analog needles
- 🔊 Buzzer alert
- 🖐️ Aluminum-foil finger electrodes
- 🎛️ Configurable pulse threshold
- ♻️ Vintage-instrument aesthetic

---

## 🧠 How it works

A conventional polygraph records several physiological variables while questions are being asked.

Kinski Polygraph implements a much simpler version using:

```text
heart activity
+
skin conductance
```

The software repeatedly reads both sensor channels.

```text
Heart sensor
     │
     ▼
Detect pulse
     │
     ▼
Drive left VU meter


GSR electrodes
     │
     ▼
Read A1
     │
     ▼
Drive right VU meter
```

The readings are then compared against programmed conditions.

```text
physiological response
         │
         ▼
configured threshold
         │
    ┌────┴────┐
    │         │
 below      above
    │         │
    ▼         ▼
 continue    buzzer
```

The device therefore provides a physical visualization of changing physiological signals.

---

# 📖 Origin of the project

The project began with a missing book.

After inviting several writers to dinner, a copy of:

**Klaus Kinski — autobiography**

disappeared.

The resulting chain of events was approximately:

```text
Dinner
  │
  ▼
Book disappears
  │
  ▼
Potential suspects
  │
  ▼
Build polygraph
```

The machine became the **Kinski Polygraph**.

The project was completed and published in August 2020.

---

# 🧰 Parts

| Qty | Component | Link |
|---:|---|---|
| 1 | **Arduino Nano** | [Amazon](https://amzn.to/3ih8mQw) |
| 2 | **Analog VU meters** | [Amazon](https://amzn.to/2EPgXez) |
| 1 | **Heart-rate sensor** | [Amazon](https://amzn.to/2Dq3Os0) |
| 1 | Buzzer | — |
| 1 | Toggle / power switch | — |
| 1 | Approx. 300–330 kΩ resistor | — |
| — | Aluminum foil | — |
| — | Jumper wires | — |
| 1 | 5 V power source | — |
| 1 | 3D-printed enclosure | [Cults3D](https://cults3d.com/en/3d-model/gadget/arduino-lie-detector-polygraph) |

---

# 🧮 Arduino Nano

The project uses the classic **Arduino Nano**, based on the ATmega328P.

Relevant characteristics include:

- 16 MHz AVR microcontroller
- 32 KB Flash
- 2 KB SRAM
- 8 analog inputs
- PWM-capable digital outputs
- compact breadboard-friendly format
- USB programming

Official documentation:

**[Arduino Nano](https://docs.arduino.cc/hardware/nano/)**

---

# ❤️ Heart-rate sensing

The first physiological channel measures pulse activity.

Conceptually:

```text
Heartbeat
    │
    ▼
Pulse sensor
    │
    ▼
Analog signal
    │
    ▼
Arduino
    │
    ▼
Beat detection
    │
    ▼
VU meter movement
```

The Arduino sketch contains a configurable heart-rate:

```text
Threshold
```

used to determine when an incoming signal should be considered a heartbeat.

The correct value depends on:

- sensor model
- finger placement
- signal amplitude
- ambient noise
- individual physiology

The threshold should therefore be calibrated before using the device.

---

# 💧 Galvanic skin response

The second channel measures **galvanic skin response**, also known as:

- GSR
- electrodermal activity
- EDA
- skin conductance response

Human skin conductivity changes partly because of sweat-gland activity controlled by the sympathetic nervous system.

The project creates a simple GSR sensor using:

```text
aluminum foil
+
finger contact
+
resistor
+
Arduino analog input
```

The current project documentation uses:

```text
A1
```

for this signal.

---

## 🔌 GSR input

During development, direct readings were unstable.

More reliable measurements were obtained after adding approximately:

```text
300 kΩ
```

between the GSR measurement input and ground.

The Hackster component list specifies:

```text
330 kΩ
```

so a standard 330 kΩ resistor is suitable for reproducing the documented circuit.

Conceptually:

```text
Finger electrodes
       │
       ▼
      A1
       │
       ├──── Arduino ADC
       │
      ~330 kΩ
       │
       ▼
      GND
```

The exact electrode wiring should follow the circuit diagram in the Hackster tutorial.

---

# 📈 Interpreting the GSR value

The sketch reads:

```text
Analog input A1
```

and uses its changing value to control one of the analog meters.

In the original implementation, higher readings are interpreted as increased finger perspiration / galvanic response.

```text
low response
     │
     ▼
smaller needle movement

higher response
     │
     ▼
larger needle movement
```

This is a measure of physiological arousal rather than a direct measurement of deception.

---

# 📟 Analog VU meters

One of the most distinctive parts of the project is the use of two physical analog meters instead of an LCD or OLED.

```text
┌─────────────────┐    ┌─────────────────┐
│       /\        │    │         /\      │
│      /  \       │    │        /  \     │
│                 │    │                 │
│   HEART RATE    │    │       GSR       │
└─────────────────┘    └─────────────────┘
```

The meters convert numerical sensor readings into visible needle motion.

---

## ⚡ Driving a VU meter from Arduino

The Arduino Nano does not provide a true analog voltage output.

Instead, the project uses:

```text
PWM
```

through `analogWrite()`.

```text
Arduino PWM
     │
     ▼
rapid HIGH/LOW pulses
     │
     ▼
average current
     │
     ▼
meter needle
```

The mechanical inertia of the meter helps smooth the PWM signal into visible movement.

---

## ⚠️ PWM pins

A development issue occurred because not every digital pin on the Arduino Nano supports PWM.

For the classic Nano, suitable PWM outputs include:

```text
D3
D5
D6
D9
D10
D11
```

The project notes specifically mention correcting the design to use pins such as:

```text
3
5
6
```

instead of:

```text
4
```

which is not PWM-capable on the classic Nano.

Always verify that the two meter outputs are connected to PWM-capable pins.

---

# 🔊 Buzzer

The buzzer provides an immediate audio signal when the programmed comparison conditions indicate a sufficiently large physiological response.

```text
Heart activity
      +
GSR activity
      │
      ▼
comparison
      │
      ▼
threshold condition
      │
      ▼
    BUZZ
```

This makes the device usable without watching both analog needles continuously.

---

# 🧠 Software logic

The current repository contains a single Arduino sketch:

```text
NanoLieDetector.ino
```

Its overall logic is straightforward:

```text
setup()
   │
   ▼
Configure sensors and outputs
   │
   ▼
loop()
   │
   ├── Read heart-rate sensor
   │
   ├── Detect beats
   │
   ├── Move pulse VU meter
   │
   ├── Read GSR on A1
   │
   ├── Move GSR VU meter
   │
   └── Evaluate buzzer condition
```

---

# 🎛️ Heart-rate threshold

The sketch includes a manually configurable threshold for identifying heartbeats.

The original build notes describe this as one of the main values that needs adjustment.

A practical calibration process is:

```text
Connect pulse sensor
        │
        ▼
Remain still
        │
        ▼
Observe signal
        │
        ▼
Adjust Threshold
        │
        ▼
Confirm one event per beat
```

A potentiometer could also replace the hardcoded value to allow physical adjustment without recompiling the firmware.

---

# 🧪 Calibration

Before using the device, establish a baseline.

## Heart-rate channel

Observe the pulse sensor while the subject is relaxed.

Adjust the threshold until beats are detected consistently.

## GSR channel

Attach the finger electrodes and observe the resting value.

```text
resting GSR
     │
     ▼
baseline
```

Then observe how the signal changes with:

- movement
- pressure on the electrodes
- temperature
- stress
- laughter
- surprise
- deep breathing

The physiological response should be understood relative to the baseline rather than treated as a universal absolute value.

---

# 🤥 What a polygraph measures

A polygraph does not directly detect:

```text
truth
```

or:

```text
lies
```

It measures physiological activity that may change during questioning.

Commercial polygraphs commonly monitor variables including:

- respiration
- heart rate
- blood pressure
- electrodermal activity

Kinski Polygraph simplifies this to:

```text
heart activity
+
electrodermal response
```

These signals can also change because of:

- nervousness
- surprise
- embarrassment
- excitement
- fear
- movement
- temperature
- expectations
- unrelated stress

The machine is therefore best treated as an electronics and psychophysiology experiment rather than an authoritative test of whether somebody is telling the truth.

---

# 🧪 Scientific context

Polygraphs infer deception indirectly from physiological responses.

The **National Academies** notes that physiological responses associated with polygraph testing do not correspond uniquely to deception and can have other causes.

The **American Psychological Association** similarly notes that scientific evidence does not support treating polygraph testing as a consistently reliable and valid detector of deception.

References:

- **[The Polygraph and Lie Detection — National Academies](https://nap.nationalacademies.org/catalog/10420/the-polygraph-and-lie-detection)**
- **[Do “lie detectors” work? — American Psychological Association](https://www.apa.org/topics/cognitive-neuroscience/polygraph)**

---

# 🖨️ 3D-printed enclosure

A custom enclosure is available on Cults3D:

**[Arduino Lie Detector Polygraph — Cults3D](https://cults3d.com/en/3d-model/gadget/arduino-lie-detector-polygraph)**

The package contains:

```text
Case.stl
Front.stl
```

The published printing settings are:

```text
Material: PLA
Layer height: 0.30 mm
Supports: No
```

The enclosure is deliberately simple:

```text
front panel
+
rear case
+
four screws
+
drawer-style handle
```

A cardboard enclosure can also be used for a quick prototype.

---

# 🚀 Installation

## 1. Clone the repository

```bash
git clone https://github.com/ronibandini/NanoLieDetector.git
cd NanoLieDetector
```

The repository currently uses:

```text
master
```

as its default branch.

---

## 2. Install Arduino IDE

Download:

**[Arduino IDE](https://www.arduino.cc/en/software)**

---

## 3. Open the sketch

Open:

```text
NanoLieDetector.ino
```

---

## 4. Select the board

In Arduino IDE:

```text
Tools
→ Board
→ Arduino AVR Boards
→ Arduino Nano
```

For some older or clone Nano boards it may also be necessary to select:

```text
Tools
→ Processor
→ ATmega328P (Old Bootloader)
```

depending on the bootloader installed on the board.

---

## 5. Connect the sensors

Connect:

```text
Heart-rate sensor → analog input defined in sketch
GSR              → A1
```

For the GSR circuit, include the approximately:

```text
300–330 kΩ
```

resistor described in the original build.

---

## 6. Connect the meters

Connect both analog meters through the circuit shown in the original project documentation.

Make sure the Arduino control signals use:

```text
PWM-capable pins
```

rather than an ordinary digital-only output such as D4.

---

## 7. Connect the buzzer

Connect the buzzer to the digital output defined by:

```text
NanoLieDetector.ino
```

and ground.

---

## 8. Adjust the pulse threshold

Find the heart-rate:

```text
Threshold
```

setting in the sketch.

Adjust it for the sensor and subject until pulse detection is stable.

---

## 9. Upload

Compile and upload:

```text
NanoLieDetector.ino
```

to the Arduino Nano.

---

# 🧪 Suggested test procedure

A simple demonstration sequence is:

```text
1. Attach pulse sensor

2. Attach GSR finger electrodes

3. Power the device

4. Wait for stable readings

5. Observe baseline meter positions

6. Ask neutral questions

7. Observe physiological response

8. Ask other questions

9. Compare needle movement
```

Useful baseline questions are simple questions with known answers.

For example:

```text
What is your name?
What day is it?
Are you sitting down?
```

The purpose is to observe the person's normal physiological response before comparing later readings.

---

# 📁 Repository structure

```text
NanoLieDetector/
├── NanoLieDetector.ino
└── README.md
```

### `NanoLieDetector.ino`

Arduino firmware.

Handles:

- pulse sensing
- heartbeat threshold
- galvanic response input
- VU-meter output
- buzzer logic

### `README.md`

Original project summary, hardware links, demo, and external project documentation.

---

# 🎥 Demo

## Nano Lie Detector

The completed Kinski Polygraph can be seen here:

**[▶️ Watch on YouTube](https://www.youtube.com/watch?v=HMHFfJFrfWk)**

The video demonstrates:

- completed enclosure
- twin analog meters
- finger sensors
- live needle movement
- the physical polygraph interface

---

# 🔬 Ideas for extending the project

1. **📊 Add session logging** — record timestamped heart-rate and GSR values to microSD or a computer for later plotting.

2. **🎛️ Add physical calibration controls** — replace hardcoded heart-rate and GSR thresholds with potentiometers.

3. **📈 Add a baseline mode** — calculate a short resting baseline before questioning and display changes relative to that baseline.

---

# 📰 External references

## 🛠️ Hackster.io

### Arduino Polygraph

The complete build tutorial was published on Hackster.io on August 6, 2020.

It documents:

- project origin
- Arduino Nano
- heart-rate sensor
- GSR electrodes
- analog VU meters
- PWM issue
- A1 GSR circuit
- resistor adjustment
- buzzer
- custom enclosure
- source code
- demo

**[Arduino Polygraph — Hackster.io](https://www.hackster.io/roni-bandini/arduino-polygraph-4d3849)**

---

## ✍️ Medium

### Kinski Polygraph

The original article explains the missing-book premise, hardware, physiological measurements, construction, and completed machine.

**[Kinski Polygraph — Medium](https://bandini.medium.com/lie-detector-with-arduino-45e44befa810)**

---

# 🖨️ Cults3D

## Arduino Lie Detector Polygraph

The printable enclosure was later published on Cults3D.

Files:

```text
Case.stl
Front.stl
```

**[Arduino Lie Detector Polygraph — Cults3D](https://cults3d.com/en/3d-model/gadget/arduino-lie-detector-polygraph)**

---

# 📕 Contracultura Maker

Kinski Polygraph belongs to a broader collection of machines built around unusual purposes, physical interfaces, electronics, art, literature, and technological experimentation.

More projects and context are collected in:

**[Contracultura Maker — book](https://bandini.medium.com/libro-de-contracultura-maker-94d1bb0d951c)**

---

# 📚 Useful references

- **[Arduino Nano](https://docs.arduino.cc/hardware/nano/)**
- **[Arduino IDE](https://www.arduino.cc/en/software)**
- **[The Polygraph and Lie Detection — National Academies](https://nap.nationalacademies.org/catalog/10420/the-polygraph-and-lie-detection)**
- **[Polygraph overview — American Psychological Association](https://www.apa.org/topics/cognitive-neuroscience/polygraph)**

---

# 🔗 You may also be interested in...

Other projects by **Roni Bandini** combining physical sensors, retro instrumentation, Arduino, and electronic objects.

## 🌱🔊 The Sound Machine

**Arduino-powered literary machine that converts soil-moisture readings into an imagined audible mood for plants.**

Like Kinski Polygraph, it transforms an analog sensor reading into an expressive physical interface.

**[github.com/ronibandini/TheSoundMachine](https://github.com/ronibandini/TheSoundMachine)**

---

## 🧮🕵️ P101

**Electronic art installation built from a discarded Olivetti calculator, Arduino UNO R4 Minima, analog mechanics, and a six-digit LCD.**

Another project combining electronics with the visual language of older instruments and machines.

**[github.com/ronibandini/p101](https://github.com/ronibandini/p101)**

---

## 🎲⭕ Arduino Nano R4

**Arduino Nano R4 experiments including a Monte Carlo π-estimation machine with display, button, buzzer, and RGB feedback.**

**[github.com/ronibandini/ArduinoNanoR4](https://github.com/ronibandini/ArduinoNanoR4)**

---

# ⚠️ Notes


## Sensor variability

Heart-rate and GSR values differ between individuals and can change with environmental conditions.

Calibration should be performed each time the device is used.

---

# 📜 License

The current repository does not specify a software license.

Copyright therefore remains with the repository author unless a license is added separately.

---

# 👤 Author

**Roni Bandini**

Maker, AI developer, electronic artist and writer.

- 🐙 GitHub: [@ronibandini](https://github.com/ronibandini)
- 💼 LinkedIn: [Roni Bandini](https://www.linkedin.com/in/ronibandini/)
- 📸 Instagram: [@ronibandini](https://www.instagram.com/ronibandini/)
- 🐦 X: [@RoniBandini](https://x.com/RoniBandini)
- ✍️ Medium: [bandini.medium.com](https://bandini.medium.com/)
- 🛠️ Hackster: [Roni Bandini](https://www.hackster.io/roni-bandini)

Buenos Aires, Argentina.
