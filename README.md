# IoT Door Control System

An IoT-based door control system using ESP32 and Blynk. This project enables users to control door relays via a smartphone app or physical push buttons, with support for both online and offline modes. Features include Wi-Fi status monitoring, debounce handling for buttons, and seamless integration with the Blynk platform for remote operation.

## Features

- Control two relays to manage door locks.
- Use Blynk mobile app for remote control.
- Physical push buttons for local control.
- Wi-Fi status LED indicator for connection status.
- Supports both online and offline modes.
- Debounce handling for button presses to avoid multiple triggers.

## Prerequisites

Before running the project, ensure that you have the following:

- **ESP32** development board
- **Blynk app** installed on your smartphone (available on iOS/Android)
- A **Wi-Fi network** for the ESP32
- **Blynk Auth Token** (obtainable from the Blynk app)

## Installation

1. **Clone the repository:
   git clone https://github.com/Whtshudisay/IOT_DOOR.git
   cd IoT-Door-Control
2. **Install the necessary libraries:**
   - **Blynk Library**: In Arduino IDE, go to **Sketch** > **Include Library** > **Manage Libraries**, then search for and install the `Blynk` library.
   - **WiFi Library**: The `WiFi.h` library is included by default for ESP32 boards.

3. **Configure your Wi-Fi and Blynk credentials:**
   - Replace `WIFI_SSID`, `WIFI_PASS`, and `AUTH` with your own details:
   
     #define AUTH "Your-Blynk-Auth-Token"
     #define WIFI_SSID "Your-Wi-Fi-SSID"
     #define WIFI_PASS "Your-Wi-Fi-Password"
    

4. **Upload the code:**
   - Use the Arduino IDE to upload the code to your ESP32.

## Usage

1. **Set up the Blynk app:**
   - Open the Blynk app on your smartphone.
   - Create a new project and choose your device (ESP32).
   - Add two **Button widgets** connected to virtual pins `V1` and `V2` to control relays.
   - Link the widgets to the corresponding virtual pins in the code (`VPIN_BUTTON_1` and `VPIN_BUTTON_2`).

2. **Power the ESP32:**
   - Once powered, the ESP32 will connect to the Wi-Fi network, and you will be able to control the door relays from the Blynk app.

3. **Physical button control:**
   - The push buttons connected to GPIO pins `32` and `33` can also control the relays locally.

## Troubleshooting

- If the ESP32 is unable to connect to Wi-Fi, double-check the Wi-Fi credentials and make sure the network is accessible.
- If the Blynk app is not syncing, try restarting both the app and the ESP32 board.
- 
## Contact

For any questions or suggestions, feel free to contact me at yashavjekar2455@gmail.com.

