#include "Arduino.h"
#include "Esp.h"
#include "ESP8266WiFi.h"

const char* c_szSSID = "XXXXXXXXX";
const char* c_szPASSWD = "XXXXXXXXX";

// If you want to deploy multiple sensors, change the field names here:
const char* c_szWATER = "&field1=";
const char* c_szBATTERY = "&field2=";

int const c_nSENSOR_PIN = 13;

const char* c_szHOST = "api.thingspeak.com";
const char* c_szPATH = "/update?api_key=XXXXXXXXXXXX"; 

uint32_t c_nSLEEP = (uint32_t)-1;

void setup() {
   Serial.begin(115200);
   Serial.println("WifiPlantSensor");
   Serial.print("Waking up every ");
   Serial.println(c_nSLEEP);
   
   pinMode(c_nSENSOR_PIN, INPUT_PULLUP);
   
   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(c_szSSID);
  
   WiFi.begin(c_szSSID, c_szPASSWD);
  
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
   }

   Serial.println("");
   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());   
}

bool get_request(char const* szHost, int nPort, char const* szUri) {
  Serial.print("Connecting to ");
  Serial.println(szHost);
  
  WiFiClient client;
  if (!client.connect(szHost, nPort)) {
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
  bool bResponse = client.available();
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("Closing connection");
  return bResponse;
}

bool bSent = false;
bool bSleep = false;

String strUri; 
extern "C" uint16_t readvdd33(void);

void loop() {
  if( !bSent ) {
    strUri = c_szPATH;
    strUri += c_szWATER;
    strUri += digitalRead(c_nSENSOR_PIN) ? '1' : '0';
    strUri += c_szBATTERY;
    strUri += readvdd33();
    
    bSent = get_request(c_szHOST, 80, strUri.c_str());
  }
  
  if(bSent) {
    if(!bSleep) {
      Serial.println("Disconnecting");
      WiFi.disconnect();
      delay(500);
   
      bSleep = true;
      ESP.deepSleep(c_nSLEEP);
    }
  } else {
    delay(100);
  }
}  
