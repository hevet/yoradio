#ifndef dsp_full_loc
#define dsp_full_loc
#include <pgmspace.h>
/*************************************************************************************
    HOWTO:
    Copy this file to yoRadio/locale/displayL10n_custom.h
    and modify it
*************************************************************************************/
const char mon[] PROGMEM = "po";
const char tue[] PROGMEM = "wt";
const char wed[] PROGMEM = "śr";
const char thu[] PROGMEM = "cz";
const char fri[] PROGMEM = "pi";
const char sat[] PROGMEM = "so";
const char sun[] PROGMEM = "ni";

const char monf[] PROGMEM = "poniedziałek";
const char tuef[] PROGMEM = "wtorek";
const char wedf[] PROGMEM = "środa";
const char thuf[] PROGMEM = "czwartek";
const char frif[] PROGMEM = "piątek";
const char satf[] PROGMEM = "sobota";
const char sunf[] PROGMEM = "niedziela";

const char jan[] PROGMEM = "styczeń";
const char feb[] PROGMEM = "luty";
const char mar[] PROGMEM = "marzec";
const char apr[] PROGMEM = "kwiecień";
const char may[] PROGMEM = "maj";
const char jun[] PROGMEM = "czerwiec";
const char jul[] PROGMEM = "lipiec";
const char aug[] PROGMEM = "sierpień";
const char sep[] PROGMEM = "wrzesień";
const char octt[] PROGMEM = "październik";
const char nov[] PROGMEM = "listopad";
const char decc[] PROGMEM = "grudzień";

const char wn_N[]      PROGMEM = "Północny";
const char wn_NNE[]    PROGMEM = "Północno-Północno-Wschodni";
const char wn_NE[]     PROGMEM = "Północno-Wschodni";
const char wn_ENE[]    PROGMEM = "Wschodnio-Północno-Wschodni";
const char wn_E[]      PROGMEM = "Wschodni";
const char wn_ESE[]    PROGMEM = "Wschodnio-Południowo-Wschodni";
const char wn_SE[]     PROGMEM = "Południowo-Wschodni";
const char wn_SSE[]    PROGMEM = "Południowo-Południowo-Wschodni";
const char wn_S[]      PROGMEM = "Południowy";
const char wn_SSW[]    PROGMEM = "Południowo-Południowo-Zachodni";
const char wn_SW[]     PROGMEM = "Południowo-Zachodni";
const char wn_WSW[]    PROGMEM = "Zachodnio-Południowo-Zachodni";
const char wn_W[]      PROGMEM = "Zachodni";
const char wn_WNW[]    PROGMEM = "Zachodnio-Północno-Zachodni";
const char wn_NW[]     PROGMEM = "Północno-Zachodni";
const char wn_NNW[]    PROGMEM = "Północno-Północno-Zachodni";

const char* const dow[]     PROGMEM = { sun, mon, tue, wed, thu, fri, sat };
const char* const dowf[]    PROGMEM = { sunf, monf, tuef, wedf, thuf, frif, satf };
const char* const mnths[]   PROGMEM = { jan, feb, mar, apr, may, jun, jul, aug, sep, octt, nov, decc };
const char* const wind[]    PROGMEM = { wn_N, wn_NNE, wn_NE, wn_ENE, wn_E, wn_ESE, wn_SE, wn_SSE, wn_S, wn_SSW, wn_SW, wn_WSW, wn_W, wn_WNW, wn_NW, wn_NNW, wn_N };

const char    const_PlReady[]    PROGMEM = "[gotowy]";
const char  const_PlStopped[]    PROGMEM = "[zatrzymano]";
const char  const_PlConnect[]    PROGMEM = "[brak danych]";
const char  const_DlgVolume[]    PROGMEM = "Głośność";
const char    const_DlgLost[]    PROGMEM = "*Restart*";
const char  const_DlgUpdate[]    PROGMEM = "Aktualizacja";
const char const_DlgNextion[]    PROGMEM = "* NEXTION *";
const char const_getWeather[]    PROGMEM = "";
const char  const_waitForSD[]    PROGMEM = "INDEX SD";

const char        apNameTxt[]    PROGMEM = "Nazwa AP";
const char        apPassTxt[]    PROGMEM = "Hasło";
const char       bootstrFmt[]    PROGMEM = "Łączę z %s";
const char        apSettFmt[]    PROGMEM = "Ustawienia na stronie: http://%s/";
#if EXT_WEATHER
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 Odczuwalna: %.1f\011C \007 Ciśnienie: %dhPa \007 Wilgotność: %s%% \007 Wiatr: %.1f m/s [%d]";
#else
const char       weatherFmt[]    PROGMEM = "%s, %.1f\011C \007 Ciśnienie: %dhPa \007 Wilgotność: %d%%";
#endif
const char     weatherUnits[]    PROGMEM = "metric";   /* standard, metric, imperial */
const char      weatherLang[]    PROGMEM = "pl";       /* https://openweathermap.org/current#multi */

#endif
