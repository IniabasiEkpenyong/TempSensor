/**
 * DHT11 Sensor Reader
 * This sketch reads temperature and humidity data from the DHT11 sensor and prints the values to the serial port.
 * It also handles potential error states that might occur during reading.
 *
 * Author: Iniabasi Ekpenyong
 */

// Include the DHT11 library for interfacing with the sensor.
#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(2);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
    Serial.begin(9600);

    lcd.init(); 
    lcd.backlight();

    dht11.setDelay(1000); // Set this to the desired delay. Default is 500ms.
}

void loop() {
    int temperature = 0;
    int humidity = 0;

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    lcd.clear();

    lcd.setCursor(0, 0);
    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    if (result == 0) {
        lcd.print("Temperature:");
        lcd.print(temperature);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(humidity);
        lcd.print("%");
    } else {
        // Print error message based on the error code.
        lcd.println(DHT11::getErrorString(result));
    }

}
