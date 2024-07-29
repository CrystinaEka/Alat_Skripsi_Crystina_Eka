#include <SimpleKalmanFilter.h>
SimpleKalmanFilter panjang_KalmanFilter(2, 2, 1);
SimpleKalmanFilter lebar_KalmanFilter  (2, 2, 1);
SimpleKalmanFilter tinggi_KalmanFilter (2, 2, 1);

double berat;
float panjang, lebar, tinggi;
float pan, leb, tin;
float panjang2, lebar2, tinggi2;
float panjang3, lebar3, tinggi3;
float pjg, lbr, tgi;
int iterations = 5;
float Smooth_panjang;
float Smooth_lebar;
float Smooth_tinggi;
double a, b1, b2, b3, y1;
double aa, bb1, bb2, bb3, yy1;
float x1, x2, x3;
float y, yy;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <NewPing.h>

#define TRIGGER_PIN1  12
#define ECHO_PIN1     11
#define MAX_DISTANCE1 50

#define TRIGGER_PIN2  6
#define ECHO_PIN2     5
#define MAX_DISTANCE2 50

#define TRIGGER_PIN3  9
#define ECHO_PIN3     8
#define MAX_DISTANCE3 50

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE3);
//==============================================================
//==============================================================
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  print_awal();
}
//==============================================================
//==============================================================
void print_awal()
{
  Serial.println("Startting..");
  lcd.setCursor(0, 0);
  lcd.print("Startting..");
  delay(1000);
  lcd.clear();
}
//==============================================================
//==============================================================
void loop()
{
  baca_ping_loop();
  rumus();
  tampil_lcd();
}
//==============================================================
//==============================================================
void tampil_lcd()
{
  lcd.setCursor(0, 0);
  lcd.print(panjang);
  lcd.print("  ");

  lcd.setCursor(6, 0);
  lcd.print(lebar);
  lcd.print("  ");

  lcd.setCursor(12, 0);
  lcd.print(tinggi);
  lcd.print("  ");

  lcd.setCursor(9, 1);
  lcd.print("V:");
  lcd.print(y, 1);
  lcd.print("  ");

  lcd.setCursor(0, 1);
  lcd.print("W:");
  lcd.print(yy, 1);
  lcd.print("  ");
}
//==============================================================
//==============================================================
void baca_ping_loop()
{
  panjang3 = 15.28;
  lebar3   = 9.38;
  tinggi3  = 12.61;

  for (int p = 0; p < 20; p++)
  {
    pjg = sonar1.ping_median(iterations);
    panjang2 = (pjg / 2) * 0.0343;
    pan = panjang3 - panjang2;
    panjang = panjang_KalmanFilter.updateEstimate(pan);
    tampil_lcd();
  }
  delay(1000);
  for (int pp = 0; pp < 20; pp++)
  {
    lbr = sonar2.ping_median(iterations);
    lebar2 = (lbr / 2) * 0.0343;
    leb = lebar3 - lebar2;
    lebar = lebar_KalmanFilter.updateEstimate(leb);
    tampil_lcd();
  }
  delay(1000);
  for (int ppp = 0; ppp < 20; ppp++)
  {
    tgi = sonar3.ping_median(iterations);
    tinggi2 = (tgi / 2) * 0.0343;
    tin = tinggi3 - tinggi2;
    tinggi = tinggi_KalmanFilter.updateEstimate(tin);
    tampil_lcd();
  }
  delay(1000);
}

//==============================================================
//==============================================================
void rumus()
{
  x1 = panjang;
  x2 = lebar;
  x3 = tinggi;

  y  = -30.0782 + (-8.45148 * x1) + (22.356 * x2) + (3.46399 * x3);
  yy = -51.4931 + (-1.26133 * x1) + (24.1255 * x2) + (1.60631 * x3);
}
//==============================================================
//==============================================================
