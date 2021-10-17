#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FastLED.h>

const char *ssid = "Orange_światłowzwód_69";
const char *password = "haniaIkonrad29";

//#define LED_PIN 14
#define COLOR_ORDER GRB
#define CHIPSET WS2813
#define BRIGHTNESS 255
#define NUM_LEDS1 91
#define NUM_LEDS2 120

#define jasnosc 0
#define tryb 2
#define barwa 15
#define Lplus 4
#define Lminus 16
#define Pplus 17
#define Pminus 13
#define L_ON_OFF 5
#define P_ON_OFF 18
#define led1 14
#define led2 12
#define power 27

CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];

int sts_jasnosc = 1;
int sts_tryb = 1;
int sts_barwa = 1;
int sts_lplus = 1;
int sts_lminus = 1;
int sts_pplus = 1;
int sts_pminus = 1;
int sts_L_onoff = 1;
int sts_P_onoff = 1;

bool last_led_is_black_LEFT = true;
bool last_led_is_black_RIGHT = true;
bool lewe_ledy = false;
bool prawe_ledy = false;
int delay_onoff = 2;
int delay_power = 100;

CRGB color = CRGB::LightPink;

/* IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0); */

void setup()
{
  Serial.begin(115200);

  /* Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]()
                     {
                       String type;
                       if (ArduinoOTA.getCommand() == U_FLASH)
                         type = "sketch";
                       else // U_SPIFFS
                         type = "filesystem";

                       // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
                       Serial.println("Start updating " + type);
                     })
      .onEnd([]()
             { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
      .onError([](ota_error_t error)
               {
                 Serial.printf("Error[%u]: ", error);
                 if (error == OTA_AUTH_ERROR)
                   Serial.println("Auth Failed");
                 else if (error == OTA_BEGIN_ERROR)
                   Serial.println("Begin Failed");
                 else if (error == OTA_CONNECT_ERROR)
                   Serial.println("Connect Failed");
                 else if (error == OTA_RECEIVE_ERROR)
                   Serial.println("Receive Failed");
                 else if (error == OTA_END_ERROR)
                   Serial.println("End Failed");
               });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); */

  FastLED.addLeds<CHIPSET, led1, RGB>(leds1, NUM_LEDS1);
  FastLED.addLeds<CHIPSET, led2, RGB>(leds2, NUM_LEDS2);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(power, OUTPUT);
  pinMode(jasnosc, INPUT);
  pinMode(tryb, INPUT);
  pinMode(barwa, INPUT);
  pinMode(Lplus, INPUT);
  pinMode(Lminus, INPUT);
  pinMode(Pplus, INPUT);
  pinMode(Pminus, INPUT);
  pinMode(L_ON_OFF, INPUT);
  pinMode(P_ON_OFF, INPUT);

  digitalWrite(power, LOW);

  FastLED.clear();
}

void loop()
{
  //ArduinoOTA.handle();

  //digitalWrite(power, HIGH);

  if (digitalRead(jasnosc) == HIGH)
    sts_jasnosc = 0;
  else if (digitalRead(jasnosc) == LOW)
    sts_jasnosc = 1;

  if (digitalRead(tryb) == HIGH)
    sts_tryb = 0;
  else if (digitalRead(tryb) == LOW)
    sts_tryb = 1;

  if (digitalRead(barwa) == HIGH)
    sts_barwa = 0;
  else if (digitalRead(barwa) == LOW)
    sts_barwa = 1;

  if (digitalRead(Lplus) == HIGH)
    sts_lplus = 0;
  else if (digitalRead(Lplus) == LOW)
    sts_lplus = 1;

  if (digitalRead(Lminus) == HIGH)
    sts_lminus = 0;
  else if (digitalRead(Lminus) == LOW)
    sts_lminus = 1;

  if (digitalRead(Pplus) == HIGH)
    sts_pplus = 0;
  else if (digitalRead(Pplus) == LOW)
    sts_pplus = 1;

  if (digitalRead(Pminus) == HIGH)
    sts_pminus = 0;
  else if (digitalRead(Pminus) == LOW)
    sts_pminus = 1;

  if (digitalRead(L_ON_OFF) == HIGH)
    sts_L_onoff = 0;
  else if (digitalRead(L_ON_OFF) == LOW)
    sts_L_onoff = 1;

  if (digitalRead(P_ON_OFF) == HIGH)
    sts_P_onoff = 0;
  else if (digitalRead(P_ON_OFF) == LOW)
    sts_P_onoff = 1;

  /* if (sts_L_onoff == 1)
    leds1[0] = CRGB::DarkViolet;
  else
    leds1[0] = CRGB::Black;

  if (sts_lplus == 1)
    leds1[1] = CRGB::DarkViolet;
  else
    leds1[1] = CRGB::Black;

  if (sts_lminus == 1)
    leds1[2] = CRGB::DarkViolet;
  else
    leds1[2] = CRGB::Black;

  if (sts_jasnosc == 1)
    leds1[3] = CRGB::DarkViolet;
  else
    leds1[3] = CRGB::Black;

  if (sts_tryb == 1)
    leds1[4] = CRGB::DarkViolet;
  else
    leds1[4] = CRGB::Black;

  if (sts_barwa == 1)
    leds1[5] = CRGB::DarkViolet;
  else
    leds1[5] = CRGB::Black;

  if (sts_pplus == 1)
    leds1[6] = CRGB::DarkViolet;
  else
    leds1[6] = CRGB::Black;

  if (sts_pminus == 1)
    leds1[7] = CRGB::DarkViolet;
  else
    leds1[7] = CRGB::Black;

  if (sts_P_onoff == 1)
    leds1[8] = CRGB::DarkViolet;
  else
    leds1[8] = CRGB::Black; */

  if (leds1[NUM_LEDS1 - 1].r != 0 && leds1[NUM_LEDS1 - 1].g != 0 && leds1[NUM_LEDS1 - 1].b != 0)
    last_led_is_black_LEFT = false;
  else
    last_led_is_black_LEFT = true;

  if (leds2[NUM_LEDS2 - 1].r != 0 && leds2[NUM_LEDS2 - 1].g != 0 && leds2[NUM_LEDS2 - 1].b != 0)
    last_led_is_black_RIGHT = false;
  else
    last_led_is_black_RIGHT = true;

  if (sts_L_onoff == 1 || sts_P_onoff == 1)
  {
    digitalWrite(power, HIGH);
    Serial.println("power ON");
  }

  // === LEFT ===
  if (digitalRead(power) && sts_L_onoff == 1 && last_led_is_black_LEFT == true && lewe_ledy == false)
  {
    FastLED.delay(delay_power);
    Serial.println("left ON");

    for (int i = 0; i < NUM_LEDS1; i++)
    {
      leds1[i] = color;
      FastLED.delay(delay_onoff);
    }
    lewe_ledy = true;
  }

  if (digitalRead(power) && sts_L_onoff == 0 && lewe_ledy == true)
  {
    for (int i = NUM_LEDS1 - 1; i > -1; i--)
    {
      leds1[i] = CRGB::Black;
      FastLED.delay(delay_onoff);
    }
    lewe_ledy = false;
  }

  // === RIGHT ===
  if (digitalRead(power) && sts_P_onoff == 1 && last_led_is_black_RIGHT == true && prawe_ledy == false)
  {
    FastLED.delay(delay_power);
    Serial.println("right ON");

    for (int i = 0; i < NUM_LEDS2; i++)
    {
      leds2[i] = color;
      Serial.println(i);
      FastLED.delay(delay_onoff);
    }
    prawe_ledy = true;
  }

  if (digitalRead(power) && sts_P_onoff == 0 && prawe_ledy == true)
  {
    for (int i = NUM_LEDS2 - 1; i > -1; i--)
    {
      leds2[i] = CRGB::Black;
      FastLED.delay(delay_onoff);
    }
    prawe_ledy = false;
  }

  if (lewe_ledy == false && prawe_ledy == false && digitalRead(power) == 1)
  {
    delay(700);
    digitalWrite(power, LOW);
    Serial.println("power OFF");
  }

  FastLED.show();
  FastLED.delay(10);
}