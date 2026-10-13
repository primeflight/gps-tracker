# 🛰️ GPS Tracker — Neo-6M + Arduino Uno

Real-time GPS tracking with a **map-style** visualization, reading data from the Neo-6M GPS module via serial and rendering in the browser.

![GPS Tracker](screenshot.png)

## Hardware

| Component | Wiring |
|---|---|
| **GPS Neo-6M Shield** | RX→D4, TX→D3, VCC→5V, GND→GND |
| **Arduino Uno R3** | Connected via USB |
| **External antenna** | Connected to the shield |

## Software

- **Arduino sketch** (`shield-gps-neo6m-ublox.ino`): reads NMEA data from the GPS and sends JSON over serial every second
- **Web page** (`gps.html`): real-time map with track history, coordinates, altitude, speed, satellites — uses **Web Serial API** (Chrome/Edge)

## Usage

1. **Upload the sketch** to the Arduino:
   ```bash
   arduino-cli compile --fqbn arduino:avr:uno shield-gps-neo6m-ublox
   arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno shield-gps-neo6m-ublox
   ```

2. **Open** `gps.html` in Chrome or Edge

3. **Click "Connect"** and select the Arduino serial port

4. **Wait for GPS fix** (may take 30s-2min outdoors) and watch the track on the map

## Data format

```json
{"lat":-23.550520,"lon":-46.633308,"alt":760.5,"spd":0.0,"sat":8,"hdop":1.2,"fix":1,"date":"2026-10-13","time":"18:30:45"}
```

| Field | Description |
|---|---|
| `lat` | Latitude in degrees |
| `lon` | Longitude in degrees |
| `alt` | Altitude in meters |
| `spd` | Speed in km/h |
| `sat` | Number of satellites |
| `hdop` | Horizontal dilution of precision |
| `fix` | 1 = valid fix, 0 = no fix |
| `date` | UTC date (YYYY-MM-DD) |
| `time` | UTC time (HH:MM:SS) |

## Structure

```
shield-gps-neo6m-ublox/
├── shield-gps-neo6m-ublox.ino  # Arduino sketch (GPS → Serial JSON)
├── gps.html                    # Map web page (Web Serial API → Canvas)
├── screenshot.png              # Map screenshot
└── README.md                   # This file
```

## Notes

- The GPS needs a clear view of the sky for a fix
- First fix may take 30 seconds to 2 minutes
- The map shows the last 100 positions as a green track
- HDOP < 2.0 indicates good accuracy
