#include <bluefruit.h>
#include <LSM6DS3.h>
#include <Wire.h>

// IMU instance
LSM6DS3 myIMU(I2C_MODE, 0x6A);

// BLE service definition
// 128bit Custom UUID
#define MOTION_SERVICE_UUID  "2a41d33a-02d7-4daf-b78b-361dd670abe5"
#define MOTION_CHAR_UUID     "d6632d94-d2d3-45a2-9a88-e98fe270e4ca"
BLEService        motionService = BLEService(MOTION_SERVICE_UUID);
BLECharacteristic motionChar    = BLECharacteristic(MOTION_CHAR_UUID);

void setup() {
  Serial.begin(115200);
  
  if (myIMU.begin() != 0) {
    Serial.println("IMU error");
    while (1);
  }

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("XIAO-Gemini-Motion");

  motionService.begin();

  // Configure characteristic (Notify: allow notifications)
  motionChar.setProperties(CHR_PROPS_NOTIFY);
  motionChar.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  motionChar.setMaxLen(32);
  motionChar.begin();

  startAdvertising();

  Serial.println("Ready to connect!");
}

void startAdvertising(void) {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(motionService);
  Bluefruit.ScanResponse.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // Unit: 0.625ms
  Bluefruit.Advertising.setFastTimeout(30);      // Seconds
  Bluefruit.Advertising.start(0);                // 0 = no timeout
}

void loop() {
  if ( Bluefruit.connected() ) {
    float x = myIMU.readFloatAccelX();
    float y = myIMU.readFloatAccelY();
    float z = myIMU.readFloatAccelZ();

    // Comma-separated string — simple format for Gemini to parse
    String data = String(x, 2) + "," + String(y, 2) + "," + String(z, 2);
    
    // Send data via BLE and check return value
    if (!motionChar.notify(data.c_str())) {
      Serial.println("Notify failed");
    }
    
    Serial.println(data);
  }
  delay(100); // Send at 10Hz
}
