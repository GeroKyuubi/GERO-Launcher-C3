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
