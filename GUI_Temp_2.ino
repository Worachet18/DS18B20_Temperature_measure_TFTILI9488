// Edit >> D:\Arduino\libraries\TFT_eSPI\User_Setups\Setup21_ILI9488.h
// #define TFT_MISO 19
// #define TFT_MOSI 23
// #define TFT_SCLK 18
// #define TFT_CS    15
// #define TFT_DC    2 
// #define TFT_RST   33
// Edit position file : GUI_Temp_GSLC.h

#include "GUI_Temp_GSLC.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();
#define TL_DATUM 0

#define ONE_WIRE_BUS 13
#define MAX_SENSORS 3

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiClient client;
PubSubClient mqtt(client);

DeviceAddress knownAddresses[MAX_SENSORS];
bool addressValid[MAX_SENSORS] = { false, false, false };
DeviceAddress scannedAddresses[10];
int scannedCount = 0;

DynamicJsonDocument docs(256);
char output[256];

float avg1 = 0.0, avg2 = 0.0, avg3 = 0.0;

#define WIFI_STA_NAME "Rungtiwa"
#define WIFI_STA_PASS "0818774251"
// #define WIFI_STA_NAME "TRAI-HED02@2.4G"   //customer
// #define WIFI_STA_PASS "0818773850"
#define MQTT_SERVER "119.59.99.155"
#define MQTT_PORT 1883
#define MQTT_USERNAME "TAVYEKvqyj50DyN2ZFgo"   //DB Temp_tai_mushroom 1
// #define MQTT_USERNAME "dl1vdsonuhcc7f5zs74w"   //DB Temp_tai_mushroom 2
#define MQTT_PASSWORD ""
#define MQTT_NAME "test_2"

gslc_tsElemRef* m_pElemRBRadioButton = NULL;
gslc_tsElemRef* m_pElemRBRadioButton2 = NULL;
gslc_tsElemRef* m_pElemRBRadioButton2_3 = NULL;
gslc_tsElemRef* t1 = NULL;
gslc_tsElemRef* t2 = NULL;
gslc_tsElemRef* t3 = NULL;
gslc_tsElemRef* m_pElemStatusText = NULL;

static int16_t DebugOut(char ch) {
  if (ch == (char)'\n') Serial.println("");
  else Serial.write(ch);
  return 0;
}

bool CbBtnCommon(void* pvGui, void* pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY) {

  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

  if (eTouch == GSLC_TOUCH_UP_IN) {
    switch (pElem->nId) {
      default:
        break;
    }
  }
  return true;
}

bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState) {
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  if (pElemRef == NULL) {
    return false;
  }

  boolean bChecked = gslc_ElemXCheckboxGetState(pGui, pElemRef);

  switch (pElem->nId) {
    case E_ELEM_RADIO1:
      break;
    case E_ELEM_RADIO2:
      break;
    case E_ELEM_RADIO3:
      break;
    default:
      break;
  } 
  return true;
}

void setup() {
  Serial.begin(9600);
  pinMode(32,OUTPUT);
  digitalWrite(32,1);
  gslc_InitDebug(&DebugOut);
  InitGUIslice_gen();
  sensors.begin();
  scanAndAssignSensors();
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_WHITE);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);
  Serial.println("Connecting to WiFi...");
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!mqtt.connected()) {
      reconnectMQTT();
    }
    mqtt.loop();
  } else {
    Serial.println("WiFi not connected.");
    gslc_ElemSetTxtStr(&m_gui, m_pElemStatusText, "OFFLINE");




  }

  scanAndAssignSensors();
  sensors.requestTemperatures();

  float temps[MAX_SENSORS] = { NAN, NAN, NAN };

  docs.clear();
  docs["rssi"] = WiFi.RSSI();

  for (int i = 0; i < MAX_SENSORS; i++) {
    char key[8];
    sprintf(key, "temp%d", i + 1);

    if (addressValid[i]) {
      float temp = sensors.getTempC(knownAddresses[i]);
      if (temp == DEVICE_DISCONNECTED_C) {
        Serial.printf("Sensor %d = Disconnect\n", i + 1);
        docs[key] = nullptr;
        addressValid[i] = false;
      } else {
        Serial.printf("Sensor %d = %.2f °C\n", i + 1, temp);
        docs[key] = temp;
        temps[i] = temp;
      }
    } else {
      Serial.printf("Sensor %d = None\n", i + 1);
      docs[key] = nullptr;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    serializeJson(docs, output);
    bool state_pub = mqtt.publish("v1/devices/me/telemetry", output);
    Serial.println(output);
    Serial.println(state_pub ? "Data sent successfully." : "Failed to send data.");
    gslc_ElemSetTxtStr(&m_gui, m_pElemStatusText, "ONLINE");
    gslc_ElemSetCol(&m_gui, m_pElemStatusText, GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_GREEN);
  }

  avg1 = temps[0];
  avg2 = temps[1];
  avg3 = temps[2];

  char buf[16];
  if (!isnan(avg1)) {
    snprintf(buf, sizeof(buf), "%.1f C", avg1);
    gslc_ElemSetTxtStr(&m_gui, t1, buf);
  } else {
    gslc_ElemSetTxtStr(&m_gui, t1, "--");
  }

  if (!isnan(avg2)) {
    snprintf(buf, sizeof(buf), "%.1f C", avg2);
    gslc_ElemSetTxtStr(&m_gui, t2, buf);
  } else {
    gslc_ElemSetTxtStr(&m_gui, t2, "--");
  }

  if (!isnan(avg3)) {
    snprintf(buf, sizeof(buf), "%.1f C", avg3);
    gslc_ElemSetTxtStr(&m_gui, t3, buf);
  } else {
    gslc_ElemSetTxtStr(&m_gui, t3, "--");
  }
  Serial.println("-----");
  delay(3000);
  gslc_Update(&m_gui);
  delay(1000);
}


void reconnectMQTT() {
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("connected");
     

    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 3 seconds");
      delay(3000);
    }
  }
}

void scanAndAssignSensors() {
  scannedCount = 0;
  DeviceAddress tempAddr;
  int count = sensors.getDeviceCount();

  for (int i = 0; i < count; i++) {
    if (sensors.getAddress(tempAddr, i)) {
      if (!isKnownAddress(tempAddr)) {
        memcpy(scannedAddresses[scannedCount], tempAddr, sizeof(DeviceAddress));
        scannedCount++;
      }
    }
  }

  for (int i = 0; i < MAX_SENSORS && scannedCount > 0; i++) {
    if (!addressValid[i]) {
      memcpy(knownAddresses[i], scannedAddresses[0], sizeof(DeviceAddress));
      addressValid[i] = true;
      Serial.print("New Sensor ");
      Serial.print(i + 1);
      Serial.print(" Address: ");
      printAddress(knownAddresses[i]);

      for (int j = 1; j < scannedCount; j++) {
        memcpy(scannedAddresses[j - 1], scannedAddresses[j], sizeof(DeviceAddress));
      }
      scannedCount--;
    }
  }
}

bool isKnownAddress(DeviceAddress addr) {
  for (int i = 0; i < MAX_SENSORS; i++) {
    if (addressValid[i] && memcmp(knownAddresses[i], addr, sizeof(DeviceAddress)) == 0) {
      return true;
    }
  }
  return false;
}

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
}

