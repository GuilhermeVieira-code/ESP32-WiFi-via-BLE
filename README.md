# Utilizando BLE com ESP32 para Configuração de Wi-Fi

Este tutorial demonstra como usar o Bluetooth Low Energy (BLE) com o ESP32 para receber credenciais de rede e, em seguida, habilitar a conexão Wi-Fi no dispositivo.

## Configuração Inicial

Inclua as bibliotecas necessárias para BLE e Wi-Fi:

```cpp
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <WiFi.h>
```

## Implementando o Servidor BLE para Receber Credenciais

Inicialize o BLE e crie um servidor e serviço BLE:

```cpp
BLEDevice::init("ESP32-WiFi-Config");
BLEServer *pServer = BLEDevice::createServer();
BLEService *pService = pServer->createService("12345678-1234-1234-1234-123456789012");
```

Crie características para SSID e senha:

```cpp
BLECharacteristic *pSSIDCharacteristic = pService->createCharacteristic(
                                            "12345678-1234-1234-1234-123456789013",
                                            BLECharacteristic::PROPERTY_WRITE
                                          );
BLECharacteristic *pPasswordCharacteristic = pService->createCharacteristic(
                                                "12345678-1234-1234-1234-123456789014",
                                                BLECharacteristic::PROPERTY_WRITE
                                              );
```

Inicie o serviço e a publicidade do BLE:

```cpp
pService->start();
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
pAdvertising->addServiceUUID(pService->getUUID());
pAdvertising->start();
```

## Lendo as Credenciais e Conectando-se ao Wi-Fi

Implemente callbacks para as características do SSID e da senha:

```cpp
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) {
        // Use o valor para conectar ao Wi-Fi
      }
    }
};

pSSIDCharacteristic->setCallbacks(new MyCallbacks());
pPasswordCharacteristic->setCallbacks(new MyCallbacks());
```

Conecte-se ao Wi-Fi com as credenciais recebidas:

```cpp
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
```

## Conclusão

Este tutorial fornece um exemplo básico de como configurar um servidor BLE no ESP32 para receber credenciais de Wi-Fi e conectar-se à rede. Ideal para cenários IoT onde a configuração de rede deve ser feita sem uma interface direta de usuário.
