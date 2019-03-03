/*
    GoPro Anti Lose 'Guardian' device 0.1 by Konrad Iturbe
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "esp_bt_main.h"
#include "esp_bt_device.h"

// Defines:

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define LED 2
#define BUZZ 12

// Buzz

int freq = 2000;
int channel = 0;
int resolution = 8;

// BLE server
BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;

// GoPro camera
bool GoProConnected = false;
BLEAddress* GoProAddress = NULL;
uint16_t connId = NULL;


esp_bd_addr_t* RemoteBDA = NULL;

// GoPro Bluetooth API
// From: https://github.com/KonradIT/goprowifihack/blob/master/Bluetooth/Platforms/ArchLinux.md

uint16_t WiFiOn[] = {17, 01, 01};
uint16_t WiFiOff[] = {17, 01, 00};
uint16_t RecordStart[] = {01, 01, 01};
uint16_t RecordStop[] = {01, 01, 00};
uint16_t ModeVideo[] = {02, 01, 00};
uint16_t ModePhoto[] = {02, 01, 01};
uint16_t ModeMultiShot[] = {02, 01, 02};

// Helpers, callbacks and functions

class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer, esp_ble_gatts_cb_param_t* param) {
      BLEAddress* address = new BLEAddress(param->connect.remote_bda);
      connId = param->connect.conn_id;
      GoProAddress = address;
      Serial.println(address->toString().c_str());
      GoProConnected = true;
      // Refresh cache:
      esp_ble_gattc_search_service(4, connId, NULL);
    
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println(pServer->getConnectedCount());
      GoProConnected = false;
    }
};

// Main setup

void setup() {
  Serial.begin(115200);

  // LED

  pinMode(LED,OUTPUT);

  // BUZZ

  ledcSetup(channel, freq, resolution);
  ledcAttachPin(12, channel);

  // Server
    
  BLEDevice::init("camera32");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());
  
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void beepOnce(){

  ledcWriteTone(channel, 2000);
 
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle=dutyCycle+10){
 
    Serial.println(dutyCycle);
 
    ledcWrite(channel, dutyCycle);
  }
}
// Main loop
void loop() {
  if (GoProConnected) {
    Serial.println("GoPro is connected");
    if (GoProAddress != NULL){
    Serial.println(GoProAddress->toString().c_str());
    }
    digitalWrite(LED, LOW);
    
  }
  if (!GoProConnected) {
    Serial.println("GoPro disconnected!");
    digitalWrite(LED, HIGH);
    beepOnce();
  }
  delay(1000);
}
