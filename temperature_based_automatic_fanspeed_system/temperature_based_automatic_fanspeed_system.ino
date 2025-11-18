#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define DHTPIN 4
#define DHTTYPE DHT11   // or DHT22
DHT dht(DHTPIN, DHTTYPE);

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// PWM settings for ESP32
#define FAN_PIN 5
#define FAN_PWM_CHANNEL 0
#define FAN_FREQ 25000
#define FAN_RES 8  // 0–255

int fanSpeed = 0;

void setup() {
  Serial.begin(115200);

  dht.begin();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1);
  }



  display.clearDisplay();
  
  
  // Initialize PWM on ESP32
  ledcSetup(FAN_PWM_CHANNEL, FAN_FREQ, FAN_RES);
  ledcAttachPin(FAN_PIN, FAN_PWM_CHANNEL);

  Serial.println("System Ready!");
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Sensor Error!");
    return;
  }

  // FAN LOGIC
  if (temp <= 15) {
    fanSpeed = 0;
  } else {
    fanSpeed = map(temp, 15, 35, 20, 100);
    fanSpeed = constrain(fanSpeed, 0, 255);
  }

  // Apply PWM
  ledcWrite(FAN_PWM_CHANNEL, fanSpeed);

  // Debug
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Fan Speed: ");
  Serial.println(fanSpeed);

  // OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.setCursor(0, 20);
  if (fanSpeed == 0) {
    display.println("Fan: OFF");
  } else {
    display.print("Fan Speed(%): ");
    display.println(fanSpeed);
    // display.print("%");
  }

  display.display();

  delay(1000);
}
