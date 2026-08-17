# ESP32 Mini Weather Badge

A tiny desk badge that shows live temperature and humidity on an OLED display, with a cute face that changes mood based on the temperature — shivering when cold, smiling when comfortable, sweating when hot.

Built by TechTadka360.

## Components Used

- ESP32 Dev Board
- DHT11 Temperature & Humidity Sensor
- SSD1306 OLED Display (128x64, I2C)
- 10kΩ resistor (pull-up for DHT11 data line)

## Wiring

| Component     | ESP32 Pin           |
|---------------|----------------------|
| OLED SDA      | GPIO21               |
| OLED SCL      | GPIO22               |
| OLED VCC      | 3.3V                 |
| OLED GND      | GND                  |
| DHT11 Data    | GPIO4 (10kΩ pull-up to 3.3V) |
| DHT11 VCC     | 3.3V                 |
| DHT11 GND     | GND                  |

See `wiring_diagram.svg` for a visual reference.

## Required Libraries

Install via Arduino IDE Library Manager:

- Adafruit SSD1306
- Adafruit GFX Library
- DHT sensor library (by Adafruit)
- Adafruit Unified Sensor (auto-installed as dependency)

## How It Works

1. On boot, the OLED shows a short TechTadka360 splash animation.
2. Every 2 seconds, the DHT11 sensor is read for temperature and humidity.
3. Temperature and humidity are displayed on the right side of the screen.
4. A cute face on the left side animates based on temperature:
   - Below 20°C → cold face (shivering)
   - 20°C to 28°C → happy face
   - Above 28°C → hot face (sweat drop animation)

## Upload Instructions

1. Open `weather_badge.ino` in Arduino IDE.
2. Select Board: **ESP32 Dev Module**.
3. Select the correct COM port.
4. Click Upload.

## Credits

Project by TechTadka360 — DIY electronics and ESP32 projects.

- YouTube: [@techtadka360official](https://www.youtube.com/@techtadka360official)
- Instagram: [@techtadka360official](https://www.instagram.com/techtadka360official)
- Facebook: [TechTadka360](https://www.facebook.com/share/1EkKAJNLdB/)
