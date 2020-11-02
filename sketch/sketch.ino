#include <Arduino.h>

#include <U8x8lib.h> //https://github.com/olikraus/u8g2/wiki
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display (change config if applicable)

void setup() {
  Serial.begin(9600);
  
  u8x8.begin();
  u8x8.setPowerSave(0);

  u8x8.setFont(u8x8_font_courB24_3x4_r);
  u8x8.setCursor(0, 0);
  u8x8.drawString(0,0,"Load");
  u8x8.drawString(0,4,"ing.");
  delay(1000);
  u8x8.clear();
}

void loop() {
  Serial.println(output);  
  u8x8.drawString(0, 0, String(output).c_str());
  delay(50);
}
