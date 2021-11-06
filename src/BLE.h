#ifndef __BLE_H__
#define __BLE_H__

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// See the following for generating UUIDs: https://www.uuidgenerator.net/
#define SERVICE_UUID "361c5a1c-ac4c-4a44-8f7f-cff5146f4ecd" // UART service UUID
#define CHARACTERISTIC_UUID_RX "71718066-16df-4a02-af2a-2ec136378b44"
#define CHARACTERISTIC_UUID_TX "d87bb294-1af4-44d3-a454-a0262c4a1a46"

class BLE : public BLEServerCallbacks, public BLECharacteristicCallbacks
{
private:
  bool deviceConnected = 0;
  BLEServer *bleServer;
  BLECharacteristic *bleCharacteristic;
  std::string recv = "";

public:
  BLE(std::string name);
  ~BLE();
  bool isAvailable();
  void onConnect(BLEServer *pServer);
  void onDisconnect(BLEServer *pServer);
  void onWrite(BLECharacteristic *pCharacteristic);
  void waitForConnection();
  std::string getRecv();
};

#endif
