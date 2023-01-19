#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int ledPin = 2;

const int oneWireBus = 32;
String message = "";
char incomingChar;
String temperatureString = "";

unsigned long previousMillis = 0;  // Stores last time temperature was published
const long interval = 10000;       // interval at which to publish sensor readings

#define rmotorb 26
#define rmotorf 25
#define lmotorb 33
#define lmotorf 32


void setup() {
  pinMode(lmotorf, OUTPUT);
  pinMode(lmotorb, OUTPUT);
  pinMode(rmotorf, OUTPUT);
  pinMode(rmotorb, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // Bluetooth device name
  SerialBT.begin("ESP32 01");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n') {
      message += String(incomingChar);
    } else {
      message = "";
    }
    Serial.write(incomingChar);
  }
  Serial.write("\n");
  
  if (message.indexOf("2") != -1) {
    digitalWrite(rmotorb, HIGH);
    digitalWrite(lmotorb, HIGH);
    Serial.println("Backward");

  } else if (message.indexOf("1") != -1){
     
    digitalWrite(rmotorb, HIGH);
    digitalWrite(lmotorb, LOW);
    digitalWrite(ledPin, HIGH);
    Serial.println("Backward");
}
   else if (message.indexOf("3") != -1) {
    digitalWrite(rmotorb, LOW);
    digitalWrite(lmotorb, HIGH);
    Serial.println("Right");
    
  } else if (message.indexOf("4") != -1) {
    digitalWrite(rmotorf, HIGH);
    digitalWrite(lmotorf, HIGH);
    Serial.println("Left");
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}