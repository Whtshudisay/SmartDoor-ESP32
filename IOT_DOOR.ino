#define BLYNK_TEMPLATE_ID "TMPL345DJTsAq"
#define BLYNK_TEMPLATE_NAME "IOT DOOR"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

int toggleState_1 = 1;
int toggleState_2 = 1;

#define AUTH "Jd5pu43T7H0RYWttl3SIFqSKKQuil5Va"        // Your Blynk Auth Token  
#define WIFI_SSID "LOQ"                                // Wi-Fi SSID
#define WIFI_PASS "YASH2455"                           // Wi-Fi Password

#define RELAY_PIN_1      26                            // Relay 1 pin
#define RELAY_PIN_2      27                            // Relay 2 pin
#define WIFI_LED         25                            // Wi-Fi status LED pin

#define PUSH_BUTTON_1    32                            // Push Button 1 pin
#define PUSH_BUTTON_2    33                            // Push Button 2 pin

#define VPIN_BUTTON_1    V1                            // Virtual pin for Button 1
#define VPIN_BUTTON_2    V2                            // Virtual pin for Button 2

bool wifiConnected = false;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
const unsigned long debounceDelay = 200;

void relayOnOff(int relay) {
    switch(relay) {
        case 1: 
            toggleState_1 = !toggleState_1;
            digitalWrite(RELAY_PIN_1, toggleState_1 ? HIGH : LOW);
            break;
        case 2: 
            toggleState_2 = !toggleState_2;
            digitalWrite(RELAY_PIN_2, toggleState_2 ? HIGH : LOW);
            break;
        default:
            break;      
    } 
}

BLYNK_CONNECTED() {
    Blynk.syncVirtual(VPIN_BUTTON_1, VPIN_BUTTON_2);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
    toggleState_1 = param.asInt();
    digitalWrite(RELAY_PIN_1, toggleState_1 ? HIGH : LOW);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
    toggleState_2 = param.asInt();
    digitalWrite(RELAY_PIN_2, toggleState_2 ? HIGH : LOW);
}

void with_internet() {
    if (digitalRead(PUSH_BUTTON_1) == LOW) {
        if (millis() - lastDebounceTime1 > debounceDelay) {
            relayOnOff(1);
            Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
            lastDebounceTime1 = millis();
        }
    }
    if (digitalRead(PUSH_BUTTON_2) == LOW) {
        if (millis() - lastDebounceTime2 > debounceDelay) {
            relayOnOff(2);
            Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
            lastDebounceTime2 = millis();
        }
    }
}

void without_internet() {
    if (digitalRead(PUSH_BUTTON_1) == LOW) {
        if (millis() - lastDebounceTime1 > debounceDelay) {
            relayOnOff(1);
            lastDebounceTime1 = millis();
        }
    }
    if (digitalRead(PUSH_BUTTON_2) == LOW) {
        if (millis() - lastDebounceTime2 > debounceDelay) {
            relayOnOff(2);
            lastDebounceTime2 = millis();
        }
    }
}

void checkWiFiStatus() {
    bool isConnected = WiFi.status() == WL_CONNECTED;

    if (isConnected && !wifiConnected) {
        Serial.println("Wi-Fi Connected!");
        wifiConnected = true;
        digitalWrite(WIFI_LED, HIGH);
    } else if (!isConnected && wifiConnected) {
        Serial.println("Wi-Fi Disconnected!");
        wifiConnected = false;
        digitalWrite(WIFI_LED, LOW);
    }
    
    if (!isConnected) {
        WiFi.begin(WIFI_SSID, WIFI_PASS);
    }
}

void setup() {
    Serial.begin(115200);

    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_2, OUTPUT);
    pinMode(WIFI_LED, OUTPUT);
    pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
    pinMode(PUSH_BUTTON_2, INPUT_PULLUP);

    digitalWrite(RELAY_PIN_1, toggleState_1 ? HIGH : LOW);
    digitalWrite(RELAY_PIN_2, toggleState_2 ? HIGH : LOW);

    Serial.print("Connecting to Wi-Fi: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {  // 10 seconds timeout
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWi-Fi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        Blynk.config(AUTH);
        wifiConnected = true;
        digitalWrite(WIFI_LED, HIGH);
    } else {
        Serial.println("\nWi-Fi connection failed. Check Wi-Fi credentials or network.");
        wifiConnected = false;
        digitalWrite(WIFI_LED, LOW);
    }

    timer.setInterval(3000L, checkWiFiStatus);
}

void loop() {  
    if (wifiConnected) {
        Blynk.run();
        with_internet();
    } else {
        without_internet();
    }
    timer.run();
}

