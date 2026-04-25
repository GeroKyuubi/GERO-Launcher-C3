# GERO-Launcher-C3
A powerful firmware that turns your ESP32 C3 into a versatile handheld multitool. Store multiple applications on a microSD card and flash them on the fly—no computer required.

# 🚀 GERO Launcher
> **ESP32-based Multi-Firmware Platform**
> A powerful firmware that turns your ESP32 C3 mini into a versatile handheld multitool. Store multiple applications on a microSD card and flash them on the fly—no computer required.

[![Platform](https://img.shields.io/badge/Platform-ESP32-orange.svg)](https://www.espressif.com/en/products/socs/esp32)
[![License](https://img.shields.io/badge/License-Educational-blue.svg)](#-license--support)
[![Store](https://img.shields.io/badge/Tindie-Store-green.svg)](https://www.tindie.com/stores/gero87/)

---

## 🛠 Installation & Setup

### 1. Preparing the Hardware
Ensure your ESP32 is wired as follows:

| Component | Connection | ESP32 Pin |
| :--- | :--- | :--- |
| **OLED (SSD1306)** | SDA | **Pin 8** |
| | SCL | **Pin 9** |
| **SD Card (SPI)** | CS | **Pin 7** |
| | MOSI | **Pin 6** |
| | CLK| **Pin 4** |
| | MISO | **Pin 5** |
| **Buttons** | UP | **Pin 0** |
| | DOWN | **Pin 1** |
| | RIGHT | **Pin 2** |
| | LEFT | **Pin 3** |

### 2. Preparing the SD Card
1. **Format** your microSD card to **FAT32**.
2. **Copy** the `MASTER.bin` file to the root of the SD card.
3. **Copy** any other `.bin` apps you want to use.
   > 💡 **Note:** Keep names short and avoid spaces for better display.

---

## 📘 User Instructions

### 🕹 How to Use the Menu
1. Insert the microSD card into the slot.
2. Power on the device via the USB port.
3. Use the **UP** and **DOWN** buttons to scroll through the list of available apps.
4. Press the **SELECT**  to flash the chosen app.
5. Wait a few seconds for the "Uploading" progress bar to finish. The device will reboot into your new app!

### 🔄 Returning to the Master Menu (With the Gero_App_Template)
GERO-compatible apps allow you to return to the main menu without a PC:
* **Action:** Press and hold the **SELECT** or **BACK** button (at your choice) for 2 seconds (or more it's your choice).
* **Result:** The screen will display `RELOADING MASTER...` and the device will return to the original launcher menu.

---

## 💻 For Developers

### 📦 Installing the Library
To create your own apps for GERO:
1. Copy the `GeroLauncherC3` folder to your `Documents/Arduino/libraries/` path.
2. In your sketch, include the library: `#include <GeroLauncherC3.h>`

### 📝 Template Code & Export
Use the following structure in your Arduino IDE:

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <GeroLauncherC3.h> // La tua libreria per il ritorno al Master

// --- CONFIGURAZIONE HARDWARE GERO C3 ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define I2C_SDA      8
#define I2C_SCL      9
#define SD_CS_PIN    7

// --- MAPPATURA PIN PULSANTI ---
#define PIN_UP       0
#define PIN_DOWN     1
#define PIN_SELECT   2
#define PIN_EXIT     3  // Sinistra (usato per uscire con 3s di pressione)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // 1. Inizializzazione Seriale (per debug)
  Serial.begin(115200);

  // 2. Inizializzazione I2C sui pin corretti del SuperMini C3
  Wire.begin(I2C_SDA, I2C_SCL);
  
  // 3. Avvio Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Errore SSD1306"));
    for(;;); 
  }

  // 4. Configurazione Ingressi
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_SELECT, INPUT_PULLUP);
  pinMode(PIN_EXIT, INPUT_PULLUP);

  // 5. Inizializzazione GeroLauncher (Esci con tasto Sinistra)
  Gero.begin(PIN_EXIT);

  // Splash Screen Iniziale (Opzionale)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 25);
  display.println("CARICAMENTO...");
  display.display();
  delay(1000);
}

void loop() {
  // --- LOGICA DI SISTEMA (OBBLIGATORIA) ---
  // Controlla se l'utente tiene premuto SINISTRA per 3 secondi
  if (Gero.checkExit()) {
    Gero.backToMaster(display, SD_CS_PIN);
  }

  // --- LOGICA DELLA TUA APPLICAZIONE ---
  display.clearDisplay();
  
  // Header fisso
  display.setCursor(0, 0);
  display.println("NOME TUA APP");
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);

  // ESEMPIO: Lettura tasti
  display.setCursor(0, 25);
  if (digitalRead(PIN_UP) == LOW) {
    display.println("Azione: SU");
  } else if (digitalRead(PIN_DOWN) == LOW) {
    display.println("Azione: GIU'");
  } else if (digitalRead(PIN_SELECT) == LOW) {
    display.println("Azione: SELECT");
  } else {
    display.println("In attesa...");
  }

  // Footer fisso con istruzioni di uscita
  display.drawFastHLine(0, 54, 128, SSD1306_WHITE);
  display.setCursor(0, 57);
  display.print("HOLD SIN (3s) p. ESC");

  display.display();
  delay(50); // Piccolo delay per stabilità
}

```

## 📸 Pics
<img width="1538" height="2048" alt="Case_SysyemMonitor" src="https://github.com/user-attachments/assets/4f610dc2-3c22-4a54-af5c-2413ec5b3a74" />
<img width="1538" height="2048" alt="solo PBC montato" src="https://github.com/user-attachments/assets/c95d5b84-de33-4d38-a74f-b5c7149b741b" />



## STL Files
https://makerworld.com/en/models/2679629-esp32-c3-mini-oled-display-for-case-for-7-3-cm#profileId-2967430

## Youtube
https://www.youtube.com/shorts/mm-MAVwzelc







