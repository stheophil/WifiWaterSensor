#include "Arduino.h"
#include "Esp.h"
#include "ESP8266WiFi.h"

// To configure sensor, change values in ap_config.h
#include "ap_config.h" 

enum EState {
  estateCONNECTED,
  estateDONE,
  estateSLEEP
} m_estate = estateDONE;

int const c_nSENSOR_PIN = 13;

char const* c_szHOST = "api.thingspeak.com";
char const* c_szPATH = "/update?api_key=";
char const* c_szFIELD = "&field";

uint32_t const c_nSLEEP = (uint32_t)-1; 
unsigned int const c_nSecondsWaitingWifi = 10; // How long to wait for Wifi connection
unsigned int const c_cRetrySend = 5; // How often to retry sending measurements

void setup() {
  Serial.begin(115200);
  pinMode(c_nSENSOR_PIN, INPUT_PULLUP);
  
  Serial.println();
  Serial.println();
  Serial.print("WifiPlantSensor ");
  Serial.println(m_data.m_nSensorID);

  try_connect();
}

void try_connect() {
  // TODO:
  // When we load from EEPROM initially, make sure 
  // SSID and password are 0-terminated
  // m_data.m_aszSSID[sizeof(m_data.m_aszSSID) - 1] = '\0';
  // m_data.m_aszPassword[sizeof(m_data.m_aszPassword) - 1] = '\0';

  Serial.print("Connecting to: ");
  Serial.println(m_data.m_aszSSID);
  
  WiFi.begin(m_data.m_aszSSID, m_data.m_aszPassword);

  for(int i = 0; i < c_nSecondsWaitingWifi && WiFi.status() != WL_CONNECTED; ++i) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    m_estate = estateCONNECTED;
  } else {
    Serial.println("Could not connect to Wifi");
    m_estate = estateDONE;
  }
}

bool get_request(char const* szHost, int nPort, char const* szUri) {
  Serial.print("Connecting to ");
  Serial.println(szHost);

  WiFiClient client;
  if(!client.connect(szHost, nPort)) {
    Serial.println("Connection failed");
    return false;
  }

  // We now create a URI for the request
  Serial.print("Requesting URL: ");
  Serial.println(szUri);

  // This will send the request to the server
  client.print(String("GET ") + szUri + " HTTP/1.1\r\n" +
               "Host: " + szHost + "\r\n" +
               "Connection: close\r\n\r\n");

  delay(100);

  // Read all the lines of the reply from server and print them to Serial
  String line = client.readStringUntil('\r');
  Serial.print(line);  

  Serial.println();
  Serial.println("Closing connection");
  return nullptr != strstr(line.c_str(), "200 OK");
}

String strUri;
extern "C" uint16_t readvdd33(void);

void loop() {
  switch (m_estate) {
    case estateCONNECTED:
      strUri = c_szPATH;
      strUri += m_data.m_aszApiKey;
      strUri += c_szFIELD;
      strUri += m_data.m_nSensorID * 2 - 1; // sensor id and field are 1-based
      strUri += "=";
      strUri += digitalRead(c_nSENSOR_PIN) ? '1' : '0';

      strUri += c_szFIELD;
      strUri += m_data.m_nSensorID * 2; // sensor id and field are 1-based
      strUri += "=";
      strUri += readvdd33();

      static unsigned int nSend = 0;
      if(get_request(c_szHOST, 80, strUri.c_str()) 
      || ++nSend==c_cRetrySend) {
        m_estate = estateDONE;
      } else {
        Serial.print("GET request ");
        Serial.print(nSend);
        Serial.println(" failed");
        delay(1000);
      }
      break;

    case estateDONE:
      Serial.println("Disconnecting");
      WiFi.disconnect();
      delay(500);

      m_estate = estateSLEEP;
      ESP.deepSleep(c_nSLEEP);
      break;

    case estateSLEEP:
      delay(100);
      break;
  }
}

