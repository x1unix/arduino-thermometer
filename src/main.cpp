#include <Arduino.h>
#include "DHT.h"
#include "TM74HC595Display.h"
#include "stat.h"
#include "timer.h"
#include "charset.h"

#define PIN_DHT 5
#define PIN_DIO 10
#define PIN_RCLK 9
#define PIN_SCLK 8

#define READ_INTERVAL 1000
#define DISPLAY_UPDATE_INTERVAL 2000

DHT dht(PIN_DHT, DHT11);
TM74HC595Display display(PIN_SCLK, PIN_RCLK, PIN_DIO);
Timer statsTimer(READ_INTERVAL, true);
Timer refreshTimer(DISPLAY_UPDATE_INTERVAL, true);

Stat stats;
bool showHumidity = false;


void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    dht.begin();
}

void logStat(const char label, float data) {
    display.send(label, 0b0001);
    if (isnan(data)) {
        display.send(_dash, 0b0110);
        return;
    }

    int clearVal = (int)(data);
    if (clearVal == 0) {
        display.send(_0, 0b0010);
        return;
    }

    if (clearVal < 0) {
        display.send(_dash, 0b1000);
        clearVal = clearVal * -1;
    }

    int high = clearVal / 10;
    if (high > 0) {
        display.send(formatDigit(high), 0b0100);
    }

    int low = clearVal % 10;
    display.send(formatDigit(low, true), 0b0010);
}

void loop() {
    auto m = millis();
    if (statsTimer.tick(m)) {
        stats.humidity = dht.readHumidity();
        stats.temp = dht.readTemperature();
    }

    if (refreshTimer.tick(m)) {
        showHumidity = !showHumidity;
    }

    if (showHumidity) {
        logStat(_h, stats.humidity);
    } else {
        logStat(_c, stats.temp);
    }
}
