# XIAO nRF52840 Sense × Gemini Motion Analysis

Transmits accelerometer data from XIAO nRF52840 Sense via BLE, and uses Gemini AI to analyze the motion in a web browser.

![Platform](https://img.shields.io/badge/Platform-XIAO%20nRF52840%20Sense-green) ![BLE](https://img.shields.io/badge/Protocol-BLE-blue) ![Gemini](https://img.shields.io/badge/AI-Gemini%202.5%20Flash-orange)

```
[XIAO nRF52840 Sense] --BLE Notify (10Hz)--> [Browser] --10sec data--> [Gemini API] --> Analysis
```

---

## Firmware (Arduino)

**Required Libraries** (install via Arduino IDE Library Manager):

| Library | Purpose |
|---|---|
| `Seeed Arduino LSM6DS3` | IMU (Accelerometer) |
| `Adafruit Bluefruit nRF52` | BLE |

**Board Setup:** Add **Seeed nRF52 Boards** via Board Manager and select **Seeed XIAO nRF52840 Sense**.
```
https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
```

**BLE Specification:**

| Item | Value |
|---|---|
| Device Name | `XIAO-Gemini-Motion` |
| Service UUID | `201aa5c7-ff3a-4e1c-8cc7-2a2b7cf3a754` |
| Characteristic UUID | `014b50d4-8504-4bf6-8949-a7cbe97b84db` |
| Property | Notify |
| Data Format | `x.xx,y.yy,z.zz` (comma-separated string, 10 Hz) |

Flash `xiao_nrf52840_imu.ino` and confirm data output in Serial Monitor (115200 baud).

---

## Web App (motion_gemini.html)

Requires **Chrome or Edge** (desktop or Android). Must be opened via `https://` or `localhost`.

1. Get a Gemini API key at [Google AI Studio](https://aistudio.google.com/app/apikey)
2. Open `motion_gemini.html`, enter your API key
3. Click **"Connect to XIAO"** and select `XIAO-Gemini-Motion`
4. Click **"Analyze 10 seconds of motion"** and move the device

Gemini (`gemini-2.5-flash-lite`) will describe the motion in 300 characters or less.

> API key is stored in `sessionStorage` and cleared when the tab is closed. Do not use on shared computers.

---

## License

MIT License

## References

- [Seeed Studio XIAO nRF52840 Sense Wiki](https://wiki.seeedstudio.com/XIAO_BLE/)
- [Google AI Studio](https://aistudio.google.com/)
- [Web Bluetooth API - MDN](https://developer.mozilla.org/en-US/docs/Web/API/Web_Bluetooth_API)
