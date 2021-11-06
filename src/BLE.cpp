#include "BLE.h"

BLE::BLE(std::string name)
{
  BLEDevice::init(name);

  this->bleServer = BLEDevice::createServer();
  this->bleServer->setCallbacks(this);
  BLEService *pService = this->bleServer->createService(SERVICE_UUID);

  this->bleCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  this->bleCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic *rxCh = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  rxCh->setCallbacks(this);

  pService->start();
  this->bleServer->startAdvertising();
}

BLE::~BLE()
{
}

void BLE::waitForConnection()
{
  while (!this->deviceConnected)
    delay(200), Serial.println("Waiting for BLE connection...");
}

void BLE::onConnect(BLEServer *pServer)
{
  this->deviceConnected = 1;
  Serial.println("BLE device connected!");
}
void BLE::onDisconnect(BLEServer *pServer)
{
  this->deviceConnected = 0;
  Serial.println("BLE device disconnected!");
}
void BLE::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string rx = pCharacteristic->getValue();

  if (rx.length() > 0)
    this->recv = rx;
}

bool BLE::isAvailable()
{
  return this->recv.length() > 0;
}

std::string BLE::getRecv()
{
  std::string tmp = this->recv;
  this->recv = "";
  return tmp;
}