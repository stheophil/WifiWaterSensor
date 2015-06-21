
// TODO: Save and load m_data to/from EEPROM
struct SData {
  char m_aszSSID[32] = "WifiNetwork";
  char m_aszPassword[64] = "WifiPassword";
  char m_aszApiKey[24] = "thingspeakAPIKey";

  // The id of the device for which the firmware is burned.
  // Device 1 will upload float sensor value to field1 and
  // voltage to field2, device 2 to field3 and field4 etc.
  unsigned int m_nSensorID = 1; 
} m_data;
