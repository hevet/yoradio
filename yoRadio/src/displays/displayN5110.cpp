#include "../core/options.h"
#if DSP_MODEL==3

#include "displayN5110.h"
#include <Wire.h>
#include "../core/config.h"
#include "../core/network.h"

#define LOGO_WIDTH 21
#define LOGO_HEIGHT 28

const unsigned char logo [] PROGMEM=
{
	0x07, 0x03, 0x80, 0x0f, 0x87, 0xc0, 0x0f, 0x87, 0xc0, 0x0f, 0x87, 0xc0, 0x0f, 0x87, 0xc0, 0x07,
	0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x07, 0xff, 0x80, 0x1f, 0xff,
	0xc0, 0x1f, 0xff, 0xe0, 0x3f, 0xff, 0xf0, 0x7f, 0x07, 0xf0, 0x7e, 0x03, 0xf0, 0x7e, 0x01, 0xf8,
	0x7f, 0xff, 0xf8, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xf8, 0x7e, 0x00, 0x00, 0x7f,
	0x00, 0x00, 0x7f, 0x80, 0x20, 0x3f, 0xff, 0xe0, 0x3f, 0xff, 0xe0, 0x1f, 0xff, 0xe0, 0x0f, 0xff,
	0xe0, 0x01, 0xff, 0xc0
};

#if DSP_HSPI
DspCore::DspCore(): Adafruit_PCD8544(TFT_DC, TFT_CS, TFT_RST, &SPI2) {}
#else
DspCore::DspCore(): Adafruit_PCD8544(TFT_DC, TFT_CS, TFT_RST) {}
#endif

#include "tools/utf8RusGFX.h"

////////////////////////////////////////////////////////////////////////////
#ifndef BATTERY_OFF

  #include "driver/adc.h"			// Подключение необходимого драйвера
  #include "esp_adc_cal.h"			// Подключение необходимой библиотеки

  #ifndef ADC_PIN
    #define ADC_PIN 1
  #endif
  #if (ADC_PIN == 1 || ADC_PIN == 36)
    #define USER_ADC_CHAN 	ADC1_CHANNEL_0
  #endif
  #if (ADC_PIN == 2)
    #define USER_ADC_CHAN 	ADC1_CHANNEL_1
  #endif
  #if (ADC_PIN == 39)
    #define USER_ADC_CHAN 	ADC1_CHANNEL_3
  #endif

  #ifndef R1
    #define R1 50		// Номинал резистора на плюс (+)
  #endif
  #ifndef R2
    #define R2 100		// Номинал резистора на плюс (-)
  #endif
  #ifndef DELTA_BAT
    #define DELTA_BAT 0	// Величина коррекции напряжения батареи
  #endif

  float ADC_R1 = R1;		// Номинал резистора на плюс (+)
  float ADC_R2 = R2;		// Номинал резистора на минус (-)
  float DELTA = DELTA_BAT;	// Величина коррекции напряжения батареи

  uint8_t g, d, e, t = 1;	// Счётчики для мигалок и осреднений
  bool Charging;			// Признак, что подключено зарядное устройство

  uint8_t reads = 100;    	// Количество замеров в одном измерении
  float Volt = 0; 			// Напряжение на батарее
  float Volt1, Volt2, Volt3, Volt4, Volt5 = 0;	 // Предыдущие замеры напряжения на батарее
  static esp_adc_cal_characteristics_t adc1_chars;

  uint8_t ChargeLevel;
// ==================== Массив напряжений на батарее, соответствующий проценту оставшегося заряда: 
  float vs[22] = {2.60, 3.10, 3.20, 3.26, 3.29, 3.33, 3.37, 3.41, 3.46, 3.51, 3.56, 3.61, 3.65, 3.69, 3.72, 3.75, 3.78, 3.82, 3.88, 3.95, 4.03, 4.25};

  #endif	//#ifndef BATTERY_OFF
/////////////////////////////////////////////////////////////////////////////////

void DspCore::command(uint8_t c) {
  Adafruit_PCD8544::command(c);
}

void DspCore::data(uint8_t c) {
  Adafruit_PCD8544::data(c);
}

void DspCore::initDisplay() {
  begin();
  setReinitInterval(0);
  config.theme.background = TFT_BG;
  config.theme.meta       = TFT_FG;
  config.theme.clock      = TFT_FG;
  config.theme.weather    = TFT_FG;
  config.theme.metabg     = TFT_BG;
  config.theme.metafill   = TFT_BG;
  config.theme.title1     = TFT_FG;
  config.theme.title2     = TFT_FG;
  config.theme.rssi       = TFT_FG;
  config.theme.ip         = TFT_FG;
  config.theme.bitrate    = TFT_FG;
  config.theme.digit      = TFT_FG;
  config.theme.buffer     = TFT_FG;
  config.theme.volbarout  = TFT_FG;
  config.theme.volbarin   = TFT_FG;
  config.theme.plcurrent     = TFT_BG;
  config.theme.plcurrentbg   = TFT_FG;
  config.theme.plcurrentfill = TFT_FG;
  for(byte i=0;i<5;i++) config.theme.playlist[i] = TFT_FG;
  
  setContrast(config.store.contrast);
  cp437(true);
  invert();
  flip();
  setTextWrap(false);
  
  plItemHeight = playlistConf.widget.textsize*(CHARHEIGHT-1)+playlistConf.widget.textsize*4;
  plTtemsCount = round((float)height()/plItemHeight);
  if(plTtemsCount%2==0) plTtemsCount++;
  plCurrentPos = plTtemsCount/2;
  plYStart = (height() / 2 - plItemHeight / 2) - plItemHeight * (plTtemsCount - 1) / 2 + playlistConf.widget.textsize*2;
}

void DspCore::drawLogo(uint16_t top) {
  drawBitmap((width()  - LOGO_WIDTH ) / 2, top, logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display();
}

void DspCore::printPLitem(uint8_t pos, const char* item, ScrollWidget& current){
  setTextSize(playlistConf.widget.textsize);
  if (pos == plCurrentPos) {
    current.setText(item);
  } else {
    uint8_t plColor = (abs(pos - plCurrentPos)-1)>4?4:abs(pos - plCurrentPos)-1;
    setTextColor(config.theme.playlist[plColor], config.theme.background);
    setCursor(TFT_FRAMEWDT, plYStart + pos * plItemHeight);
    fillRect(0, plYStart + pos * plItemHeight - 1, width(), plItemHeight - 2, config.theme.background);
    print(utf8Rus(item, true));
  }
}

void DspCore::drawPlaylist(uint16_t currentItem) {
  uint8_t lastPos = config.fillPlMenu(currentItem - plCurrentPos, plTtemsCount);
  if(lastPos<plTtemsCount){
    fillRect(0, lastPos*plItemHeight+plYStart, width(), height()/2, config.theme.background);
  }
}

void DspCore::clearDsp(bool black) {
  fillScreen(TFT_BG);
}

GFXglyph *pgm_read_glyph_ptr(const GFXfont *gfxFont, uint8_t c) {
  return gfxFont->glyph + c;
}

uint8_t DspCore::_charWidth(unsigned char c){
  GFXglyph *glyph = pgm_read_glyph_ptr(&DS_DIGI15pt7b, c - 0x20);
  return pgm_read_byte(&glyph->xAdvance);
}

uint16_t DspCore::textWidth(const char *txt){
  uint16_t w = 0, l=strlen(txt);
  for(uint16_t c=0;c<l;c++) w+=_charWidth(txt[c]);
  return w;
}

void DspCore::_getTimeBounds() {
  _timewidth = textWidth(_timeBuf);
  char buf[4];
  strftime(buf, 4, "%H", &network.timeinfo);
  _dotsLeft=textWidth(buf);
}

void DspCore::_clockSeconds(){
  setTextSize(1);
  setFont(&DS_DIGI15pt7b);
  setTextColor((network.timeinfo.tm_sec % 2 == 0) ? config.theme.clock : config.theme.background, config.theme.background);
  setCursor(_timeleft+_dotsLeft, clockTop);
  print(":");  
  setFont();                                   /* print dots */
  setTextSize(1);
  setCursor(_timeleft+_timewidth+2, clockTop-CHARHEIGHT*2-1);
  setTextColor(config.theme.clock, config.theme.background);
  sprintf(_bufforseconds, "%02d", network.timeinfo.tm_sec);
  print(_bufforseconds); 

/////////////////////////////////////////////////////////////////////////////
  #ifndef BATTERY_OFF
  if(!config.isScreensaver) {
// ===================== Отрисовка мигалок ========================================
    setTextSize(1);

  if (Charging)		// Если идёт зарядка (подключено зарядное устр-во) - бегающие квадратики
    {
//	setTextColor(config.theme.clock, config.theme.background);				// Светлый
	if (network.timeinfo.tm_sec % 1 == 0)
	{
           setCursor(BatX, BatY);
	   if (g == 1) {print("\xA0\xA2\x9E\x9F");} 			// 2 квад. в конце
	   if (g == 2) {print("\xA0\x9E\x9E\xA3");} 			// 2 квад. по краям
	   if (g == 3) {print("\x9D\x9E\xA2\xA3");} 			// 2 квад. в начале
	   if (g >= 4) {g = 0; print("\x9D\xA2\xA2\x9F");} 		// 2 квад. в середине
           g++;
	}
    }

// ============= Отрисовка предупреждающей мигалки ==================================
    if (Volt < 2.8 )                 //мигающие квадратики
    {
     if (network.timeinfo.tm_sec % 1 == 0)
      {
//	 setTextColor(config.theme.clock, config.theme.background);				// Светлый
         setCursor(BatX, BatY);
         if (d == 1) {print("\xA0\xA2\xA2\xA3");} 			// полная - 6 кв.
         if (d >= 2) {d = 0; print("\x9D\x9E\x9E\x9F");} 		// пустая - 0 кв.
         d++;
      }
     }

// ================= Вывод цифровых значений заряда и напряжения =======================
   if (network.timeinfo.tm_min % 1 == 0)
      {
//         setTextColor(config.theme.clock, config.theme.background);
         setCursor(ProcX, ProcY); 			// Установка координат для вывода процентов заряда
         if (e == 1) {printf("%4i%%", ChargeLevel);}  // Вывод процентов заряда батареи с форматом
         if (e >= 3) {
            #ifndef HIDE_VOLT  			// Если напряжение выводится
//              if (_mode()!=PLAYER) {		// и если не режим "Play"
//              if (plStatus_e()!=PLAYING) {		// и если не режим "Play"
//              if (Display.displayMode!=PLAYER) {		// и если не режим "Play"
                 setCursor(ProcX, ProcY);		// Установка координат для вывода напряжения
                 printf("%.2fv", Volt);     /* } */			// Вывод напряжения
            #endif 				// Конец вывода напряжения
                         }
         if (e >= 4) {e = 0;}
         e++;
       }
// ========================== Расчёт напряжений и заряда ==========================
   if (network.timeinfo.tm_sec % 5 == 0)
  {

          //  Читаем АЦП "reads"= раз и складываем результат в милливольтах
  float tempmVolt = 0;

         //  Настройка и инициализация АЦП
  adc1_config_width(ADC_WIDTH_BIT_12); 
  adc1_config_channel_atten(USER_ADC_CHAN, ADC_ATTEN_DB_12);

          //  Расчет характеристик АЦП т.е. коэффициенты усиления и смещения
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 0, &adc1_chars);

  for(uint8_t i = 0; i < reads; i++){
  tempmVolt += esp_adc_cal_raw_to_voltage(adc1_get_raw(USER_ADC_CHAN), &adc1_chars);
                                           }

  float mVolt = (tempmVolt / reads) / 1000;		       //  Получаем средний результат в Вольтах

          //  Коррекция результата и получение напряжения батареи в Вольтах
  Volt = (mVolt + 0.0028 * mVolt * mVolt + 0.0096 * mVolt - 0.051) / (ADC_R2 / (ADC_R1 + ADC_R2)) + DELTA;
  if (Volt < 0) Volt = 0;

          // подготовка к контролю подключения зарядного устройства	- - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  if (Volt3 > 0) {Volt = (Volt + Volt1 + Volt2 + Volt3) / 4;}
  Volt4 += Volt;
  Volt3 = Volt2; Volt2 = Volt1; Volt1 = Volt;
  t++;
          //	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ============ Рассчитываем остаток заряда в процентах ====================================
// Поиск индекса, соответствующего вольтажу. Индекс соответствует проценту оставшегося заряда

  uint8_t idx = 0;
  while (true) {
//================= Получение % оставшегося заряда ============================
    if (Volt < vs[idx]) {ChargeLevel =0; break;}
    if (Volt < vs[idx+1]) {mVolt = Volt - vs[idx]; ChargeLevel = idx * 5 + round(mVolt /((vs[idx+1] - vs[idx]) / 5 )); break;}
    else {idx++;}
                 }
    if (ChargeLevel < 0) ChargeLevel = 0; if (ChargeLevel > 100) ChargeLevel = 100;
// ===================== Отрисовка статической батарейки =================================
  if (!Charging)		// Если не идёт зарядка
  {
//  setTextColor(config.theme.clock, config.theme.background); 
  setCursor(BatX, BatY);

  if (                         Volt >= 3.82) {print("\xA0\xA2\xA2\xA3");} 	//больше 85 % (6 квад.)
  if ((Volt < 3.82) && (Volt >= 3.72)) {print("\x9D\xA2\xA2\xA3");} 	//от70 до 85% (5 квад.)
  if ((Volt < 3.72) && (Volt >= 3.61)) {print("\x9D\xA1\xA2\xA3");} 	//от 55 до 70% (4 квад.)
  if ((Volt < 3.61) && (Volt >= 3.46)) {print("\x9D\x9E\xA2\xA3");} 	//от 40 до 55% (3 квад.)
  if ((Volt < 3.46) && (Volt >= 3.33)) {print("\x9D\x9E\xA1\xA3");} 	//от 25 до 40% (2 квад.)
  if ((Volt < 3.33) && (Volt >= 3.20)) {print("\x9D\x9E\x9E\xA3");} 	//от 10 до 25% (1 квад.)
  if ((Volt < 3.20) && (Volt >= 2.8)) {print("\x9D\x9E\x9E\x9F");} 	//от 0 до 10% (0 квад.)
  }

//  if (Volt < 2.8) {setTextColor(config.theme.background, config.theme.clock);}	// (0%) установка инверсного цвета

//Serial.printf("#BATT#: ADC: %i reads, V-batt: %.3f v, Capacity: %i\n", reads, Volt, ChargeLevel);	// Вывод значений в COM-порт для контроля

//  drawFastVLine(_timeleft-2, clockTop, 8, config.theme.clock); 			/*divider vert*/
//  drawFastVLine(_timeleft-2, clockTop, clockTimeHeight, config.theme.clock); 		/*divider vert*/
  }

// ===================  Контроль подключения зарядного устройства ============================
   if (network.timeinfo.tm_sec % 60 == 0)
  {
    t -= 1;
    Volt4 = Volt4 / t;
    if ((Volt5 > 0) && ((Volt4 - Volt5) > 0.001)) {
      Charging = true;						// установка признака, что подключено зарядное устройство
     setTextColor(config.theme.clock, config.theme.background);			// Светлый
								}
    else {Charging = false;}					// установка признака, что зарядное устройство не подключено
    Volt5 = Volt4; Volt4 = 0; t = 1;
  }
          //	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  }
  #endif	//#ifndef BATTERY_OFF
/////////////////////////////////////////////////////////////////////////////////
}

void DspCore::_clockDate(){  }

void DspCore::_clockTime(){
  if(_oldtimeleft>0) dsp.fillRect(_oldtimeleft,  clockTop-clockTimeHeight+1, _oldtimewidth+CHARWIDTH*2+2, clockTimeHeight, config.theme.background);
  //if(_oldtimeleft>0) dsp.fillRect(_oldtimeleft, clockTop-clockTimeHeight+1, _oldtimewidth, clockTimeHeight, config.theme.background);
  _timeleft = (width()/2 - _timewidth/2)-clockRightSpace;
  setTextSize(1);
  setFont(&DS_DIGI15pt7b);
  setTextColor(config.theme.clock, config.theme.background);
  setCursor(_timeleft, clockTop);
  print(_timeBuf);
  setFont();
  strlcpy(_oldTimeBuf, _timeBuf, sizeof(_timeBuf));
  _oldtimewidth = _timewidth;
  _oldtimeleft = _timeleft;
}

void DspCore::printClock(uint16_t top, uint16_t rightspace, uint16_t timeheight, bool redraw){
  clockTop = top;
  clockRightSpace = rightspace;
  clockTimeHeight = timeheight;
  strftime(_timeBuf, sizeof(_timeBuf), "%H:%M", &network.timeinfo);
  if(strcmp(_oldTimeBuf, _timeBuf)!=0 || redraw){
    _getTimeBounds();
    _clockTime();
  }
  _clockSeconds();
}

void DspCore::clearClock(){
  dsp.fillRect(_timeleft,  clockTop-clockTimeHeight, _timewidth+CHARWIDTH*2+2, clockTimeHeight+2, config.theme.background);
  //dsp.fillRect(_timeleft,  clockTop-clockTimeHeight, _timewidth+CHARWIDTH*3*2+24, clockTimeHeight+10+CHARHEIGHT, config.theme.background);
}


void DspCore::loop(bool force) {
  if(digitalRead(TFT_CS)==LOW) return;
  display();
  delay(10);
}

void DspCore::charSize(uint8_t textsize, uint8_t& width, uint16_t& height){
  width = textsize * CHARWIDTH;
  height = textsize * CHARHEIGHT;
}

void DspCore::setTextSize(uint8_t s){
  Adafruit_GFX::setTextSize(s);
}

void DspCore::flip(){
  setRotation(config.store.flipscreen?2:0);
}

void DspCore::invert(){
  invertDisplay(config.store.invertdisplay);
}

void DspCore::sleep(void) { command( PCD8544_FUNCTIONSET | PCD8544_POWERDOWN); }
void DspCore::wake(void) { initDisplay(); }

void DspCore::writePixel(int16_t x, int16_t y, uint16_t color) {
  if(_clipping){
    if ((x < _cliparea.left) || (x > _cliparea.left+_cliparea.width) || (y < _cliparea.top) || (y > _cliparea.top + _cliparea.height)) return;
  }
  Adafruit_PCD8544::writePixel(x, y, color);
}

void DspCore::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  if(_clipping){
    if ((x < _cliparea.left) || (x >= _cliparea.left+_cliparea.width) || (y < _cliparea.top) || (y > _cliparea.top + _cliparea.height))  return;
  }
  Adafruit_PCD8544::writeFillRect(x, y, w, h, color);
}

void DspCore::setClipping(clipArea ca){
  _cliparea = ca;
  _clipping = true;
}

void DspCore::clearClipping(){
  _clipping = false;
}

void DspCore::setNumFont(){
  setFont(&DS_DIGI15pt7b);
  setTextSize(1);
}

#endif
