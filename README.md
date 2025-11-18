# **🌡️ IoT Smart Temperature Controlled Fan**

This project utilizes an ESP8266 (NodeMCU) to automatically control the speed of a DC fan based on ambient temperature readings from a DHT11 sensor. Real-time status updates, including current temperature and fan speed percentage, are displayed on a 0.96" OLED screen.

## **🚀 Features**

* **Automatic Speed Control:** Fan speed increases linearly as temperature rises (20°C to 35°C).  
* **Visual Feedback:** OLED display shows real-time Temperature (°C) and Fan Speed (%).  
* **Safety Cutoff:** Fan remains off below the minimum temperature threshold to save power.  
* **PWM Output:** Uses Pulse Width Modulation for smooth fan speed transitions.

## **📸 Hardware Requirements**

* **Microcontroller:** NodeMCU ESP8266 (ESP-12E)  
* **Sensor:** DHT11 Temperature & Humidity Sensor  
* **Display:** 0.96" I2C OLED Display (SSD1306 Driver)  
* **Actuator:** 12V DC Fan  
* **Driver:** MOSFET Module or Transistor (e.g., 2N2222/IRF540) to drive the fan  
* **Power:** External power supply for the fan (if \>5V)

## **🔌 Wiring Diagram**

| Component | NodeMCU Pin | Description |
| :---- | :---- | :---- |
| **DHT11 Data** | D4 (GPIO 2\) | Temperature Data Signal |
| **OLED SDA** | D2 (GPIO 4\) | I2C Data Line |
| **OLED SCL** | D1 (GPIO 5\) | I2C Clock Line |
| **Fan Signal** | D5 (GPIO 14\) | PWM Control Signal to MOSFET/Base |
| **VCC** | 3.3V / Vin | Power (Match component voltage) |
| **GND** | GND | Common Ground (Essential) |

**⚠️ Important:** Never power a high-current 12V fan directly from the ESP8266 GPIO pins. Always use a separate power source for the fan and share the Ground (GND) connection with the NodeMCU.

## **🛠️ Installation & Setup**

1. **Install Arduino IDE:** Download and install the latest version.  
2. **Board Manager:** Go to File \> Preferences and add http://arduino.esp8266.com/stable/package\_esp8266com\_index.json. Then install **esp8266** via the Board Manager.  
3. **Install Libraries:** Open the Library Manager (Sketch \> Include Library \> Manage Libraries) and install:  
   * Adafruit SSD1306  
   * Adafruit GFX  
   * DHT sensor library (by Adafruit)  
4. **Upload Code:** Open SmartFan.ino, select your Board (NodeMCU 1.0) and Port, and click Upload.

## **⚙️ Control Logic**

The system uses a linear mapping logic to determine fan speed:

* **Below 20°C:** Fan is **OFF** (0% speed).  
* **20°C \- 35°C:** Fan speed scales linearly from **20% to 100%**.  
* **Above 35°C:** Fan runs at **Maximum Speed** (100%).

## **📄 License**

This project is open-source and available under the MIT License.
