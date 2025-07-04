/****************************************************************************************************
  S3 ILI9341(FSPI) + I2S + SD(FPI) + Encoder1. Maleksm мод + батарейка  + Mute. Делитель (38.5х99.2) - 1-й или 2-й (S3) пин.
****************************************************************************************************/
/* Generated by myoptions.h online-generator - v0.9.0 
https://trip5.github.io/yoradio-docs/docs/myoptions-generator.html?b=ESP32-S3-DevKitC-1_44Pin&r=72,1,2,4,6,7,9,19,42,43,54,75,68&i=1,2,3,4,15,16,17,28,29,30,39,45,46,47,42&v=9,10,-1,14,17,16,18,5,6,4,39,41,42,40,8
Put this file next to yoRadio.ino and restart Arduino IDE. */

#ifndef myoptions_h
#define myoptions_h

//#define LED_BUILTIN_S3    48        /* S3-onboard RGB led pin */
//#define USE_BUILTIN_LED   false     /* Use S3-onboard RGB led */
//#define DSP_INVERT_TITLE  false     /*  Инверсные цвета названия станции (заголовок дисплея). По умолчанию "true"  */
//#define EXT_WEATHER       false     /*  Расширенная погода. По умолчанию "true"  */
//#define CLOCKFONT_MONO    false     /* Откл/Вкл моношрифтов для часов TFT дисплеев. По умолчанию "true"  */
//#define RSSI_DIGIT        true      /* Графический/цифровой значок Wi-Fi. (false - лесенка, true - цифирьки) */
//#define BITRATE_FULL      false     /* Значек битрейта. По умолчанию "true" */ 
#define L10N_LANGUAGE RU    /*  Language (EN, RU). More info in yoRadio/locale/displayL10n_(en|ru).h*/

/* Display */
//#define DSP_MODEL    DSP_ST7735  /* Select ST7735*/
//#define DTYPE     INITR_GREENTAB  /*  ST7735 display submodel. По умолчанию "INITR_BLACKTAB" */
#define DSP_MODEL    DSP_ILI9341 /* Select ILI9341*/
//#define DSP_MODEL   DSP_ST7789  /* Select ST7789*/
//#define DSP_MODEL   DSP_ST7789_170  /* Select ST7789x170*/
//#define DSP_MODEL    DSP_ILI9488 /* Select ILI9488*/
//#define DSP_MODEL    DSP_ST7796 /* Select ILI9486*/
//#define DSP_MODEL    DSP_SSD1306x32    /* Select SSD1306-128х32*/
//#define DSP_MODEL    DSP_SH1106    /* Select SH1106-128х64*/
/* **************************************** */

/* TFT */
#define TFT_CS          10    /* (FSPI CS0)        can be CS pin ( ) */
#define TFT_RST         -1    /* SPI RST pin. (-1 if connect to EN, RST) */
#define TFT_DC           9    /* (FSPI HD)         can be DC, RS */
#define BRIGHTNESS_PIN  14    /* Pin for brightness (output 0 - 3v3)    (FSPI WP)    can be BLK, BL */
					/* Connect TFT_MOSI  to pin  11     (FSPI D)      can be SDA, DIN, SDI */
					/* Connect TFT_SCLK  to pin  12     (FSPI CLK)   can be SCL, SCK, CLK */
/* **************************************** */

/*  I2S DAC    */
#define I2S_DOUT      17    /*  = DIN connection. Should be set to 255 if the board is not used */
#define I2S_BCLK      16    /*  = BCLK Bit clock */
#define I2S_LRC       18    /*  = WSEL Left Right Clock */
/* **************************************** */

/*  VS1053 PINS */
#define VS1053_CS     255    /*  XCS pin. Should be set to 255 if the board is not used */
//#define VS1053_DCS    18   /*             = XDCS pin.  */
//#define VS1053_DREQ   16   /*             = DREQ pin.  */
//#define VS1053_RST    -1   /* Set to -1 if connected to Esp EN pin, or any other = XRESET pin. */
					/* Connect VS1053 MOSI to  11   (FSPI D)     = SI pin.  */
					/* Connect VS1053 MISO to  13   (FSPI Q)     = MISO pin. */
					/* Connect VS1053 SCK to   12   (FSPI CLK)   = SCK pin. */
/* **************************************** */

/*  BUTTONS  */
//#define BTN_LEFT    6    /*  VolDown, Prev */
//#define BTN_CENTER  4    /*  Play, Stop, Show playlist */
//#define BTN_RIGHT   5    /*  VolUp, Next */
//#define BTN_UP      255   /*  Prev, Move Up */
//#define BTN_DOWN    255   /*  Next, Move Down */
#define BTN_INTERNALPULLUP    false    /*  Enable the weak pull up resistors. По умолчанию "true" */
//#define BTN_LONGPRESS_LOOP_DELAY  200   /*  Delay between calling DuringLongPress event . По умолчанию "200" */
//#define BTN_CLICK_TICKS     300   /*  Event Timing https://github.com/mathertel/OneButton#event-timing По умолчанию "300" */
//#define BTN_PRESS_TICKS     500   /*  Event Timing https://github.com/mathertel/OneButton#event-timing По умолчанию "500" */
/* **************************************** */

/*  ENCODERs  */
#define ENC_BTNL              6       /*  Левое вращение энкодера (S1, DT)*/
#define ENC_BTNR              5       /*  Правое вращение энкодера (S2, CLK) */
#define ENC_BTNB              4       /*  Кнопка энкодера (Key, SW)*/
//#define ENC2_BTNL             6       /*  Левое вращение энкодера-2 (S1, DT)*/
//#define ENC2_BTNR             5       /*  Правое вращение энкодера-2 (S2, CLK) */
//#define ENC2_BTNB             4       /*  Кнопка энкодера-2 (Key, SW)*/
#define ENC_INTERNALPULLUP    false    /*  Enable the weak pull up resistors. По умолчанию "true"  */
#define ENC2_INTERNALPULLUP   false    /*  Enable the weak pull up resistors. По умолчанию "true"  */

/*  SDCARD  */
#define SDC_CS          39      /* SDCARD CS pin */
					// Connect SDC_MOSI to  40  /* On board can be D1 pin */
					// Connect SDC_SCK to   41   /* On board can be CLK pin */
					// Connect SDC_MISO to  42  /* On board can be D0 pin */
#define SD_SPIPINS  41, 42, 40    /* SCK, MISO, MOSI */
/* **************************************** */

/*  Other settings.  */
#define MUTE_PIN    8           /*  MUTE Pin */
#define MUTE_VAL    LOW     /*  Write this to MUTE_PIN when player is stopped. По умолчанию "HIGH" */
//#define PLAYER_FORCE_MONO false   /*  mono option on boot - false stereo, true mono. По умолчанию "false" */
//#define I2S_INTERNAL  false /*  If true - use esp32 internal DAC. По умолчанию "false" */
//#define ROTATE_90 false     /*  Optional 90 degree rotation for square displays. По умолчанию "false"*/
//#define HIDE_VOLPAGE       /* Скрыть страницу "Громкость", ориентируемся по прогрессбару. (МОД nva_lw и Maleksm)  */
//#define HIDE_DATE            /* Скрыть дату. (МОД nva_lw и Maleksm)  */
#define BOOMBOX_STYLE     /*  Разные варианты "показометра" VUmetr. Столбик, если строку закоментировать. */
//#define WAKE_PIN              255

#define DOWN_LEVEL           2      /* lowest level brightness (from 0 to 255, default "2"). (МОД Maleksm) */
#define DOWN_INTERVAL        60     /* interval for BacklightDown in sec (60 sec = 1 min, default "60"). (МОД Maleksm) */
/* ***************************************** */

/*  Аккумулятор */
//#define BATTERY_OFF         /*  Выключить показатель уровня заряда и напряжения аккумулятора */
//#define HIDE_VOLT             /*  Скрыть только показатель напряжения аккумулятора */
//#define ADC_PIN     1          /*  (или GPIO2) для считывания с делителя напряжения аккумулятора. По умолчанию GPIO1.  */
#define R1               38.5      /*  Номинал резистора, подключенного к плюсу батареи, в КОм или Ом. По умолчанию 50.  */
#define R2               99.2      /*  Номинал резистора, подключенного к минусу, в КОм  или Ом. По умолчанию 100. */
//#define DELTA_BAT       -0.009    /*  Величина коррекции показаний напряжения батареи в вольтах */
/* *********** ****************************** */
#define GRND_HEIGHT     231     /* (231 м) Высота местности над уровнем моря в метрах для поправки в давление */

/*  IR control  */
//#define IR_PIN                21
//#define IR_TIMEOUT        80              /*  see kTimeout description in IRremoteESP8266 example */
                   /*  https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRrecvDumpV2/IRrecvDumpV2.ino */
/******************************************/

/*  RTC control  */
//#define RTC_MODULE    DS3231  /* или DS1307  */
//#define RTC_SDA       7    /* 47 */
//#define RTC_SCL       8    /* 48 */
/* **************************************** */

#endif
