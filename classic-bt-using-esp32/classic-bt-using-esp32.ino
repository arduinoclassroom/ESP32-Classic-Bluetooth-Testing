#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define rmotorb 26
#define rmotorf 25
#define lmotorb 33
#define lmotorf 32
#define ledPin 2

void setup() {
  pinMode(lmotorf, OUTPUT);
  pinMode(lmotorb, OUTPUT);
  pinMode(rmotorf, OUTPUT);
  pinMode(rmotorb, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("ESP32test");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    // Serial.write(SerialBT.read());
    char massege = SerialBT.read();
    if (massege == '1') {
      digitalWrite(rmotorb, HIGH);
      digitalWrite(lmotorb, LOW);
      digitalWrite(ledPin, HIGH);
      Serial.println("Backward");
      
    } else if (massege == '2') {
      digitalWrite(rmotorb, HIGH);
      digitalWrite(lmotorb, HIGH);
      Serial.println("Backward");
      
    } else if (massege == '3') {
      digitalWrite(rmotorb, LOW);
      digitalWrite(lmotorb, HIGH);
      Serial.println("Right");

    } else if (massege == '4') {
      digitalWrite(rmotorf, HIGH);
      digitalWrite(lmotorf, HIGH);
      Serial.println("Left");
      digitalWrite(ledPin, LOW);
    }
  }
  delay(20);
}