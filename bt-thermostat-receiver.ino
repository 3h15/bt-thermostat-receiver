#include <RFduinoGZLL.h>

struct SensorData {
  // Keep under 20 bytes!
  bool isValid; // 1 byte
  float temperature;  // 4 bytes
  float humidity;  // 4 bytes
  // NOTE: compiler will reserve a byte here not defined
};

device_t role = DEVICE0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");

  // use the lowest power level
  RFduinoGZLL.txPowerLevel = +4;

  // the host/device base address can be changed to create independent networks in the same area
  // (note: the msb cannot be 0x55 or 0xaa)
  RFduinoGZLL.hostBaseAddress = 0x4A27E98F;    // default host base address is 0x0D0A0704;
  RFduinoGZLL.deviceBaseAddress = 0xF487EE4A;  // default device base address is 0x0E0B0805;

  // start the GZLL stack
  RFduinoGZLL.begin(role);
}

void loop()
{
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *packet, int len)
{
  Serial.println("Got data!");
  struct SensorData data;

  memcpy( &data, &packet[0], len);

  if(data.isValid){
    Serial.println(data.temperature);
    Serial.println(data.humidity);
  }
  else{
    Serial.println("NO SENSOR?");
  }


}
