/**
 * Configuração de Wi-Fi via BLE no ESP32
 * Autor: GuilhermeVieira- code (GitHub)
 * Data: 13/11/2023
 * Descrição: Este código demonstra como usar o Bluetooth Low Energy (BLE)
 * com o ESP32 para receber credenciais de Wi-Fi e, em seguida, conectar o dispositivo à rede Wi-Fi.
 */

// Inclusão das bibliotecas para BLE e Wi-Fi
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <WiFi.h>

// Inicialização do BLE com um nome específico para o dispositivo
BLEDevice::init("ESP32-WiFi-Config");

// Criação de um servidor BLE no ESP32
BLEServer *pServer = BLEDevice::createServer();

// Criação de um serviço BLE com um UUID único
BLEService *pService = pServer->createService("12345678-1234-1234-1234-123456789012");

// Criação de uma característica BLE para o SSID com propriedade de escrita
BLECharacteristic *pSSIDCharacteristic = pService->createCharacteristic(
                                            "12345678-1234-1234-1234-123456789013",
                                            BLECharacteristic::PROPERTY_WRITE
                                          );

// Criação de uma característica BLE para a senha com propriedade de escrita
BLECharacteristic *pPasswordCharacteristic = pService->createCharacteristic(
                                                "12345678-1234-1234-1234-123456789014",
                                                BLECharacteristic::PROPERTY_WRITE
                                              );

// Inicialização do serviço BLE
pService->start();

// Configuração e inicialização da publicidade do serviço BLE
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
pAdvertising->addServiceUUID(pService->getUUID());
pAdvertising->start();

// Implementação de callbacks para as características do SSID e da senha
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) {
        // Aqui, você pode usar o valor recebido para conectar ao Wi-Fi
      }
    }
};

// Configuração dos callbacks para as características
pSSIDCharacteristic->setCallbacks(new MyCallbacks());
pPasswordCharacteristic->setCallbacks(new MyCallbacks());

// Função principal
void setup() {
  // Configurações iniciais
}

void loop() {
  // Implementação do loop principal
  // Aqui você pode adicionar a lógica para conectar ao Wi-Fi após receber as credenciais
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }
}
