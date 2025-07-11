/*************************************************************************************
    ST7920 128x64 displays configuration file.
    Copy this file to yoRadio/src/displays/conf/displayST7920conf_custom.h
    and modify it
    More info on https://github.com/e2002/yoradio/wiki/Widgets#widgets-description
*************************************************************************************/

#ifndef displaySSD1305conf_h
#define displaySSD1305conf_h

#define DSP_WIDTH       128
#define TFT_FRAMEWDT    1
#define MAX_WIDTH       DSP_WIDTH-TFT_FRAMEWDT*2

#define HIDE_HEAPBAR
#define HIDE_VOL
#define HIDE_VU

#define bootLogoTop     68

#ifndef BATTERY_OFF
#define BatX      7		// X coordinate for batt. (Координата X для батарейки)
#define BatY      35		// Y coordinate for batt. (Координата Y для батарейки)
#define ProcX     7		// X coordinate for percent (Координата X для процентов заряда)
#define ProcY     44		// Y coordinate for percent (Координата Y для процентов заряда)
#endif

/* SROLLS  */                            /* {{ left, top, fontsize, align }, buffsize, uppercase, width, scrolldelay, scrolldelta, scrolltime } */
const ScrollConfig metaConf       PROGMEM = {{ TFT_FRAMEWDT, 0, 2, WA_LEFT }, 140, true, MAX_WIDTH, 5000, 3, 15 };
const ScrollConfig title1Conf     PROGMEM = {{ 0, 17, 1, WA_LEFT }, 140, true, DSP_WIDTH-6*4, 5000, 2, 35 };
const ScrollConfig title2Conf     PROGMEM = {{ 0, 26, 1, WA_LEFT }, 140, true, DSP_WIDTH, 5000, 2, 35 };
const ScrollConfig playlistConf   PROGMEM = {{ TFT_FRAMEWDT, 26, 1, WA_LEFT }, 140, true, MAX_WIDTH, 500, 2, 25 };
const ScrollConfig apTitleConf    PROGMEM = {{ TFT_FRAMEWDT, 0, 2, WA_CENTER }, 140, false, MAX_WIDTH, 0, 2, 35 };
const ScrollConfig apSettConf     PROGMEM = {{ TFT_FRAMEWDT, 64-7, 1, WA_LEFT }, 140, false, MAX_WIDTH, 0, 2, 15 };
const ScrollConfig weatherConf    PROGMEM = {{ 0, 53, 1, WA_LEFT }, 140, true, DSP_WIDTH-6*4, 0, 2, 25 };	// Weather (погода)

/* BACKGROUNGC9106DS  */                       /* {{ left, top, fontsize, align }, width, height, outlined } */
const FillConfig   metaBGConf     PROGMEM = {{ 0, 0, 0, WA_LEFT }, DSP_WIDTH, 16, false };
const FillConfig   volbarConf     PROGMEM = {{ 0, 61, 0, WA_LEFT }, DSP_WIDTH, 3, true };
const FillConfig  playlBGConf     PROGMEM = {{ 0, 23, 0, WA_LEFT }, DSP_WIDTH, 19, false };
const FillConfig  heapbarConf     PROGMEM = {{ 0, 63, 0, WA_LEFT }, DSP_WIDTH, 1, false };

/* WIDGETS  */                           /* { left, top, fontsize, align } */
const WidgetConfig bootstrConf    PROGMEM = { 0, 64-8, 1, WA_CENTER };
const WidgetConfig bitrateConf    PROGMEM = { 0, 17, 1, WA_RIGHT };
//const WidgetConfig voltxtConf     PROGMEM = { 32, 108, 1, WA_RIGHT };
const WidgetConfig  iptxtConf     PROGMEM = { 0, 53, 1, WA_LEFT };
const WidgetConfig   rssiConf     PROGMEM = { 0, 53, 1, WA_RIGHT };
const WidgetConfig numConf        PROGMEM = { 0, 28, 2, WA_CENTER };
const WidgetConfig apNameConf     PROGMEM = { 0, 18, 1, WA_CENTER };
const WidgetConfig apName2Conf    PROGMEM = { 0, 27, 1, WA_CENTER };
const WidgetConfig apPassConf     PROGMEM = { 0, 37, 1, WA_CENTER };
const WidgetConfig apPass2Conf    PROGMEM = { 0, 46, 1, WA_CENTER };
const WidgetConfig  clockConf     PROGMEM = { 6, 36, 2, WA_CENTER };
const WidgetConfig vuConf         PROGMEM = { 1, 28, 1, WA_LEFT };

const WidgetConfig bootWdtConf    PROGMEM = { 0, 64-8*2-5, 1, WA_CENTER };
const ProgressConfig bootPrgConf  PROGMEM = { 90, 14, 4 };

/* BANDS  */                             /* { onebandwidth, onebandheight, bandsHspace, bandsVspace, numofbands, fadespeed } */
const VUBandsConfig bandsConf     PROGMEM = { 12, 48, 2, 1, 8, 3 };

/* STRINGS  */
const char         numtxtFmt[]    PROGMEM = "%d";
const char           rssiFmt[]    PROGMEM = "%d";
const char          iptxtFmt[]    PROGMEM = "%s";
//const char         voltxtFmt[]    PROGMEM = "%d";
const char        bitrateFmt[]    PROGMEM = "%d";

/* MOVES  */                         /* { left, top, width (0 - auto, -1 - lock )} */
const MoveConfig    clockMove     PROGMEM = { 0, 0, -1 };
const MoveConfig   weatherMove    PROGMEM = { 0, 0, -1 };
const MoveConfig   weatherMoveVU  PROGMEM = { 0, 0, -1 };

#endif
