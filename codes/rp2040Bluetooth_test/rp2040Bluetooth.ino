/*
 * Arduino nano RP2040 Connect exercise:
 * as BLE Peripheral 
 * 
 * reference:
 * ArduinoBLE library-
 * https://www.arduino.cc/en/Reference/ArduinoBLE
 * 
 * In my implementation:
 * BLEByteCharacteristic written event checked by polling.
 * BLEStringCharacteristic/BLEIntCharacteristic using event haandler.
 * 
 */
#include <ArduinoBLE.h>

/*  Visit Online GUID / UUID Generator
 *  (https://www.guidgenerator.com/)
 *  to generate your uuid
 */
const char* serviceUUID = "20a07a95-8c12-484c-94fa-b828c4465a3c";
const char* byteCharUUID = "d34dda3b-7b4a-4ce3-9666-a8338db4e604";
const char* stringCharUUID = "41281b9c-8dc4-4649-8cbe-c39fa01513e2";
const char* intCharUUID = "c7d27dc6-f4d8-4523-b060-3e2e4c187808";

const char* myLocalName = "MyBLE";

BLEService myBLEService(serviceUUID);
BLEByteCharacteristic myBLEByteCharacteristic(byteCharUUID,
                                              BLERead | BLEWrite);
BLEStringCharacteristic myBLEStringCharacteristic(stringCharUUID,
                                                  BLERead | BLEWrite, 10);  //max length = 10
BLEIntCharacteristic myBLEIntCharacteristic(intCharUUID,
                                            BLERead | BLEWrite);

int redLED = 2;
int yellowLED = 3;


void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);

  //Started, connect Serial to begin
  while (!Serial)
    ;
  Serial.println("\n---Start ---");
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("Initialize BLE...");
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1)
      ;
  }
  Serial.println("BLE initialized.");
  Serial.print("MAC: ");
  Serial.println(BLE.address());
  Serial.println("Service UUIID: \t\t\t" + String(serviceUUID));
  Serial.println("Byte Characteristic UUIID: \t" + String(byteCharUUID));
  Serial.println("String Characteristic UUIID: \t" + String(stringCharUUID));
  Serial.println("Int Characteristic UUIID: \t" + String(intCharUUID));

  Serial.println();

  BLE.setLocalName(myLocalName);
  BLE.setAdvertisedService(myBLEService);
  myBLEService.addCharacteristic(myBLEByteCharacteristic);
  myBLEService.addCharacteristic(myBLEStringCharacteristic);
  myBLEService.addCharacteristic(myBLEIntCharacteristic);
  BLE.addService(myBLEService);

  myBLEStringCharacteristic.setEventHandler(BLEWritten, myBLEString_Written_Hndl);
  myBLEIntCharacteristic.setEventHandler(BLEWritten, myBLEInt_Written_Hndl);

  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Connected: ");
    Serial.println(central.address());

    while (central.connected()) {

      if (myBLEByteCharacteristic.written()) {
        byte valByte = myBLEByteCharacteristic.value();
        Serial.print("myBLEByteCharacteristic received: ");
        Serial.println(valByte, HEX);
      }
    }

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Disconnected.");
  }
}

// Event Handler for myBLEStringCharacteristic Written
// Print received Sring, and write back in upper case.
void myBLEString_Written_Hndl(BLEDevice central, BLECharacteristic characteristic) {
  Serial.print("BLEStringCharacteristic event, written: ");

  Serial.println("myBLEStringCharacteristic received: len=" + String(myBLEStringCharacteristic.valueLength()));
  String valString = myBLEStringCharacteristic.value();
  valString.toLowerCase();
  if (valString == "redon") {
    digitalWrite(redLED, HIGH);
  } else if (valString == "redoff") {
    digitalWrite(redLED, LOW);
  } else if (valString == "yellowon") {
    digitalWrite(yellowLED, HIGH);
  } else if (valString == "yellowoff") {
    digitalWrite(yellowLED, LOW);
  }
  Serial.println(valString);
  valString.toUpperCase();
  Serial.println(valString);
  myBLEStringCharacteristic.setValue(valString);
}

// Event Handler for myBLEIntCharacteristic Written
void myBLEInt_Written_Hndl(BLEDevice central, BLECharacteristic characteristic) {
  Serial.print("BLEIntCharacteristic event, written: ");

  int valInt = myBLEIntCharacteristic.value();
  Serial.println(valInt);
}