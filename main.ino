#include "FastLED.h"
#include "RTClib.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define HORLOGE 0
#define DATA_PIN_HORLOGE    8        // data pin : D8
#define COLOR_ORDER GRB
#define NUM_LEDS_HORLOGE    30       // number of ledsh in the strip
#define LED_TYPE    WS2812B
#define PASSWORD 
#define NETWORK
#define AUTH

CRGB ledsh[NUM_LEDS_HORLOGE];

char auth[] = AUTH; //token généré par le projet Blynk sur le smartphone
char ssid[] = NETWORK;      //SSID du réseau WiFi auquel se connecte l'ESP
char pass[] = PASSWORD;    //clé du réseau WiFi

uint8_t r[1] = {0};
uint8_t g[1] = {0};
uint8_t b[1] = {0};

long temps = 0;
uint8_t env = 0;

int s = 0;
int m = 0;
int h = 0;
int t = 0;
int um = 0;
int dm = 0;
int uh = 0;
int dh = 0;
int nh = 0;
int nm = 0;
int ns = 0;

BLYNK_WRITE(V0) { //Rouge Lampe sur V0
  r[HORLOGE] = (uint8_t)param.asInt();
}
BLYNK_WRITE(V1) { //Vert sur V1
  g[HORLOGE] = (uint8_t)param.asInt();
}
BLYNK_WRITE(V2) { //Bleu Lampe sur V2
  b[HORLOGE] = (uint8_t)param.asInt();
}
BLYNK_WRITE(V3) { //Réglage de l'heure sur V3
  temps = (long)param.asLong();
}
BLYNK_WRITE(V4) { //Bouton "envoyer" sur V4
  env = (uint8_t)param.asInt();
}

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN_HORLOGE, GRB>(ledsh, NUM_LEDS_HORLOGE);
  
  r[HORLOGE] = 0;
  g[HORLOGE] = 70;
  b[HORLOGE] = 70;

  Blynk.begin(auth, ssid, pass);
  
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif
  if (! rtc.begin()) {
  Serial.println("Couldn't find RTC");
  while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    //rtc.adjust(DateTime(2020,6, 11, 21, 22, 0));
  }
}
void loop() {
    Blynk.run();
    DateTime now = rtc.now();
    
    s = now.second();
    m = now.minute();
    h = now.hour();
    t = s%2;
    um = m%10;
    dm = m/10;
    uh = h%10;
    dh = h/10;
    nh = temps/3600;
    nm = (temps%3600)/60;
    ns = (temps%60);

    if(env==1){ //Réglage de l'horloge quand on appuie sur envoyer
      rtc.adjust(DateTime(now.year(),now.month(), now.day(), nh, nm, ns));
    }
    
    if(t==0){ // Clignotement des 2 points
      ledsh[14] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
      ledsh[15] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
    }
    else{
      ledsh[14] = CRGB::Black;
      ledsh[15] = CRGB::Black;
    }
    switch(um) { //Affichage unité de minutes
        case 0:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[4] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[5] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[6] = CRGB::Black;
            FastLED.show();
            break;
        case 1:    
            ledsh[0] = CRGB::Black;
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB::Black;
            ledsh[4] = CRGB::Black;
            ledsh[5] = CRGB::Black;
            ledsh[6] = CRGB::Black;
            FastLED.show();
            break;
        case 2:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB::Black;
            ledsh[3] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[4] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[5] = CRGB::Black;
            ledsh[6] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 3:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[4] = CRGB::Black;
            ledsh[5] = CRGB::Black;
            ledsh[6] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 4:    
            ledsh[0] = CRGB::Black;
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB::Black;
            ledsh[4] = CRGB::Black;
            ledsh[5] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[6] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 5:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB::Black;
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[4] = CRGB::Black;
            ledsh[5] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[6] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 6:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB::Black;
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[4] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[5] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[6] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 7:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB::Black;
            ledsh[4] = CRGB::Black;
            ledsh[5] = CRGB::Black;
            ledsh[6] = CRGB::Black;
            FastLED.show();
            break;
        case 8:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[4] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[5] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[6] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 9:    
            ledsh[0] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[1] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[2] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[3] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[4] = CRGB::Black;
            ledsh[5] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[6] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        default :
            ledsh[0] = CRGB::Black;
            ledsh[1] = CRGB::Black;
            ledsh[2] = CRGB::Black;
            ledsh[3] = CRGB::Black;
            ledsh[4] = CRGB::Black;
            ledsh[5] = CRGB::Black;
            ledsh[6] = CRGB::Black;
            FastLED.show();
            break;
    }
    switch(dm) { //Affichage dizaine de minutes
        case 0:    
            ledsh[7] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[8] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[9] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[10] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[11] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[12] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[13] = CRGB::Black;
            FastLED.show();
            break;
        case 1:    
            ledsh[7] = CRGB::Black;
            ledsh[8] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[9] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[10] = CRGB::Black;
            ledsh[11] = CRGB::Black;
            ledsh[12] = CRGB::Black;
            ledsh[13] = CRGB::Black;
            FastLED.show();
            break;
        case 2:    
            ledsh[7] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[8] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[9] = CRGB::Black;
            ledsh[10] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[11] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[12] = CRGB::Black;
            ledsh[13] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 3:    
            ledsh[7] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[8] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[9] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[10] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[11] = CRGB::Black;
            ledsh[12] = CRGB::Black;
            ledsh[13] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 4:    
            ledsh[7] = CRGB::Black;
            ledsh[8] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[9] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[10] = CRGB::Black;
            ledsh[11] = CRGB::Black;
            ledsh[12] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[13] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 5:    
            ledsh[7] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[8] = CRGB::Black;
            ledsh[9] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[10] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[11] = CRGB::Black;
            ledsh[12] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[13] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        default :
            ledsh[7] = CRGB::Black;
            ledsh[8] = CRGB::Black;
            ledsh[9] = CRGB::Black;
            ledsh[10] = CRGB::Black;
            ledsh[11] = CRGB::Black;
            ledsh[12] = CRGB::Black;
            ledsh[13] = CRGB::Black;
            FastLED.show();
            break;
    }
    switch(uh) { //Affichage unité de secondes
        case 0:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[20] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[21] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[22] = CRGB::Black;
            FastLED.show();
            break;
        case 1:    
            ledsh[16] = CRGB::Black;
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB::Black;
            ledsh[20] = CRGB::Black;
            ledsh[21] = CRGB::Black;
            ledsh[22] = CRGB::Black;
            FastLED.show();
            break;
        case 2:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB::Black;
            ledsh[19] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[20] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[21] = CRGB::Black;
            ledsh[22] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 3:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[20] = CRGB::Black;
            ledsh[21] = CRGB::Black;
            ledsh[22] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 4:    
            ledsh[16] = CRGB::Black;
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB::Black;
            ledsh[20] = CRGB::Black;
            ledsh[21] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[22] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 5:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB::Black;
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[20] = CRGB::Black;
            ledsh[21] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[22] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 6:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB::Black;
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[20] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[21] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[22] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 7:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB::Black;
            ledsh[20] = CRGB::Black;
            ledsh[21] = CRGB::Black;
            ledsh[22] = CRGB::Black;
            FastLED.show();
            break;
        case 8:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[20] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[21] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[22] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        case 9:    
            ledsh[16] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[17] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[18] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[19] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[20] = CRGB::Black;
            ledsh[21] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[22] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        default :
            ledsh[16] = CRGB::Black;
            ledsh[17] = CRGB::Black;
            ledsh[18] = CRGB::Black;
            ledsh[19] = CRGB::Black;
            ledsh[20] = CRGB::Black;
            ledsh[21] = CRGB::Black;
            ledsh[22] = CRGB::Black;
            FastLED.show();
            break;
    }
    switch(dh) { //Affichage dizaine de secondes
        case 0:    
            ledsh[23] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[24] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[25] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[26] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[27] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[28] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[29] = CRGB::Black;
            FastLED.show();
            break;
        case 1:    
            ledsh[23] = CRGB::Black;
            ledsh[24] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[25] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[26] = CRGB::Black;
            ledsh[27] = CRGB::Black;
            ledsh[28] = CRGB::Black;
            ledsh[29] = CRGB::Black;
            FastLED.show();
            break;
        case 2:    
            ledsh[23] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[24] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[25] = CRGB::Black;
            ledsh[26] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[27] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            ledsh[28] = CRGB::Black;
            ledsh[29] = CRGB(r[HORLOGE],g[HORLOGE],b[HORLOGE]);
            FastLED.show();
            break;
        default :
            ledsh[23] = CRGB::Black;
            ledsh[24] = CRGB::Black;
            ledsh[25] = CRGB::Black;
            ledsh[26] = CRGB::Black;
            ledsh[27] = CRGB::Black;
            ledsh[28] = CRGB::Black;
            ledsh[29] = CRGB::Black;
            FastLED.show();
            break;
    }
}
