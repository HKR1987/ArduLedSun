#include <Adafruit_NeoPixel.h>


#define PIN_NEO_PIXEL  7   // Arduino pin that connects to NeoPixel
#define NUM_PIXELS     12  // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);
long int godz;
long int offset;
int wlaczone; // 0 - wyłączone, 1 - włączone

long int gToMs(long int gdz)
{
  String g = String(gdz);
  long int hms = g.substring(0,2).toInt() * 3600000;
  long int mms = g.substring(2,4).toInt() * 60000;
  long int sms = g.substring(4,6).toInt() * 1000;
  long int ms = hms + mms + sms;
  return ms;
}

long int msToG(long int mm)
{
  long int ms = mm  - (mm/86400000 * 86400000);
  int hi = ms/3600000;
  int mi =(ms - hi * 3600000) / 60000;
  int si = (ms - hi * 3600000 - mi * 60000) / 1000;
  String h = String(hi);
  String m = String(mi);
  String s = String(si);
  if(hi < 10) { h = '0' + h;}
  if(mi < 10) { m = '0' + m;}
  if(si < 10) { s = '0' + s;}
  String hm = h + m + s;
  return hm.toInt();
}

void setup()
{
  Serial.begin(9600);
  NeoPixel.begin();
  Serial.println("Podaj godzine");
  while(Serial.available() == 0) {}
  godz = Serial.readString().toInt();
  offset = gToMs(godz) - millis();
  wlaczone = 0;
}

void wlaczWszystkie(long int i)
{
  if(wlaczone != 1 && i == godz)
  {
    for (int i =0; i < NUM_PIXELS; i++)
    {
      NeoPixel.setPixelColor(i, NeoPixel.Color(255, 255, 255));
      NeoPixel.setBrightness(255);
    }
    NeoPixel.show();
    wlaczone = 1;
  }
}

void wylaczWszystkie(long int i)
{
  if (wlaczone != 0 && i == godz)
  {
    NeoPixel.clear();
    NeoPixel.show();
    wlaczone = 0;
  }
}

void rozjasniaj(long int odg, long int dog)
{
  if (godz >= odg && godz <= dog)
  {
    long int interwal = gToMs(dog) - gToMs(odg);
    long int biezacy = (millis() + offset) - gToMs(odg);
    double proc = (double)biezacy/(double)interwal;
    int r = 255;
    int g = 255 * (proc * 2);
    int b = 255 * proc;
    int bright = 255 * (proc * 2);
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    if(bright > 255) bright = 255;
    for (int i = 0; i < NUM_PIXELS; i++)
    {
      NeoPixel.setPixelColor(i, NeoPixel.Color(r, g, b));
    }
    NeoPixel.setBrightness(bright);
    NeoPixel.show();
  }
}

void przyciemniaj(long int odg, long int dog)
{
  if (godz >= odg && godz <= dog)
  {
    long int interwal = gToMs(dog) - gToMs(odg);
    long int biezacy = (millis() + offset) - gToMs(odg);
    double proc = (double)biezacy/(double)interwal;
    int r = 255;
    int g = 255 - (255 * proc);
    int b = 255 - (255 * (proc * 2));
    int bright = 255 - (255 * proc);
    if(g < 0 ) g = 0;
    if(b < 0) b = 0;
    if(bright < 0) bright = 0;
    for (int i = 0; i < NUM_PIXELS; i++)
    {
      NeoPixel.setPixelColor(i, NeoPixel.Color(r, g, b));
    }
    NeoPixel.setBrightness(bright);
    NeoPixel.show();
  }
}

void loop()
{
  godz = msToG(millis() + offset);
  Serial.println(String(godz));
  //wlaczWszystkie(120010);
  //wylaczWszystkie(120015);
  rozjasniaj(120010, 120020);
  przyciemniaj(120021, 120030);
}
