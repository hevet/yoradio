#include "Arduino.h"
#include "../../core/options.h"
#include "../dspcore.h"
#include "utf8Pol.h"

#ifndef DSP_LCD
static const unsigned char iso2_upper_table[256] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
  0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
  0x60, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
  0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
  0x80, 0x9a, 0x90, 0x83, 0x8e, 0x85, 0x86, 0x87, 0x88, 0xcb, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
  0x90, 0x91, 0x92, 0x93, 0x99, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
  0xa0, 0xa1, 0xa2, 0xa3, 0xa5, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
  0xb0, 0xa1, 0xb2, 0xa3, 0xb4, 0xa5, 0xa6, 0xb7, 0xb8, 0xa9, 0xaa, 0xab, 0xac, 0xbd, 0xae, 0xaf,
  0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
  0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
  0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
  0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xf7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xff
};

// Translation table, one rule per item. First character is output code, rest is input UTF-8 code.
const char * translate[] =
{
    "\xa1\xc4\x84",  // 0xa1: Ą
    "\xc6\xc4\x86",  // 0xc6: Ć
    "\xca\xc4\x98",  // 0xca: Ę
    "\xa3\xc5\x81",  // 0xa3: Ł
    "\xd1\xc5\x83",  // 0xd1: Ń
    "\xd3\xc3\x93",  // 0xd3: Ó
    "\xa6\xc5\x9a",  // 0xa6: Ś
    "\xac\xc5\xb9",  // 0xac: Ź
    "\xaf\xc5\xbb",  // 0xaf: Ż
    "\xb1\xc4\x85",  // 0xb1: ą
    "\xe6\xc4\x87",  // 0xe6: ć
    "\xea\xc4\x99",  // 0xea: ę
    "\xb3\xc5\x82",  // 0xb3: ł
    "\xf1\xc5\x84",  // 0xf1: ń
    "\xf3\xc3\xb3",  // 0xf3: ó
    "\xb6\xc5\x9b",  // 0xb6: ś
    "\xbc\xc5\xba",  // 0xbc: ź
    "\xbf\xc5\xbc",  // 0xbf: ż
    // Extra translations
    "\x2d\xe2\x80\x93",  // 0x2d (-): 0x8211 (–)
    "\x2d\xe2\x80\x94",  // 0x2d (-): 0x8212 (—)
    "\x22\xe2\x80\x9e",  // 0x22 ("): 0x8222 („)
    "\x22\xe2\x80\x9d",  // 0x22 ("): 0x8221 (”)
    // iso2, cp1250
    "\xa1\xa1",  // iso2 Ą
    "\xc6\xc6",  // iso2 Ć
    "\xca\xca",  // iso2 Ę
    "\xa3\xa3",  // iso2 Ł
    "\xd1\xd1",  // iso2 Ń
    "\xd3\xd3",  // iso2 Ó
    "\xa6\xa6",  // iso2 Ś
    "\xac\xac",  // iso2 Ź
    "\xaf\xaf",  // iso2 Ż
    "\xb1\xb1",  // iso2 ą
    "\xe6\xe6",  // iso2 ć
    "\xea\xea",  // iso2 ę
    "\xb3\xb3",  // iso2 ł
    "\xf1\xf1",  // iso2 ń
    "\xf3\xf3",  // iso2 ó
    "\xb6\xb6",  // iso2 ś
    "\xbc\xbc",  // iso2 ź
    "\xbf\xbf",  // iso2 ż
    "\xa1\xa5",  // cp1250 Ą
    "\xa6\x8c",  // cp1250 Ś
    "\xac\x8f",  // cp1250 Ź
    "\xb1\xb9",  // cp1250 ą
    "\xb6\x9c",  // cp1250 ś
    "\xbc\x9f",  // cp1250 ź
    // niepolskie znaki
    "\xa5\xc3\x91",  //0xa5: Ñ
    "\xa4\xc3\xb1",  //0xa4: ñ
    "\x89\xc3\xab",  //0x89: ë
    "\xeb\xc3\xab",  //0xeb: ë
    "\xcb\xc3\x8b",  //0xcb: Ë
    "\x84\xc3\xa4",  //0x84: ä
    "\x8e\xc3\x84",  //0x8e: Ä
    "\x81\xc3\xbc",  //0x81: ü
    "\x9a\xc3\x9c",  //0x9a: Ü
    "\x94\xc3\xb6",  //0x94: ö
    "\x99\xc3\x96",  //0x99: Ö
    "\x8b\xc3\xaf",  //0x8b: ï
    "\x98\xc3\xbf",  //0x98: ÿ
    "\x90\xc3\x89",  //0x90: É
    "\x82\xc3\xa9",  //0x82: é
    "\x91\xc4\x87",  //0x91: æ
    "\x92\xc4\x86",  //0x92: Æ
    "\x9d\xc4\x84",  //0x9d: ¥
    "\xc1\xc3\x81",  //0xc1: Á
    "\xe1\xc3\xa1",  //0xe1: á
    "\xcd\xc3\x8d",  //0xcd: Í
    "\xed\xc3\xad",  //0xed: í
    "\x8a\xc3\xa8",  //0x8a: è
   
};

// Returns utf-8 character length (in bytes).
int utf8_char_len(unsigned char b)
{
    if (b < 0x80)      // 0xxxxxxx - ASCII
        return 1;
    if (b < 0xc0)      // 10xxxxxx - continuation byte, invalid as start
        return 1;
    if (b < 0xe0)      // 110xxxxx - 2 bytes
        return 2;
    if (b < 0xf0)      // 1110xxxx - 3 bytes
        return 3;
    if (b < 0xf8)      // 11110xxx - 4 bytes
        return 4;
    // Invalid UTF-8 start byte
    return 1;
}


// Replace Polish characters from UTF-8 to ISO-8858-2 *IN PLACE*.
void utf8_to_iso2(char * s, char missing)
{
    char *d = s;
    const char **tr_ptr, **tr_end = translate + sizeof(translate) / sizeof(*translate);
    while(*s)
    {
        unsigned char b = *(unsigned char*)s;
        if(b < 0x80)  // pure ASCII
        {
            *d++ = *s++;
        }
        else  // UTF-8
        {
            // search translation
            for(tr_ptr = translate; tr_ptr < tr_end; ++tr_ptr)
            {
                // asymetric strcmp/strncmp
                const char *tr = *tr_ptr;
                const char *se, *te;
                for(se=s, te=tr+1; *te && *te == *se; ++se, ++te) ;
                if( ! *te )  // match
                {
                    s += te - tr - 1;  // utf-8 character length
                    *d++ = tr[0];
                    break;
                }
            }
            // no match
            if(tr_ptr == tr_end)
            {
                // skip unknown utf-8 character
                s += utf8_char_len(b);
                if(missing)
                    *d++ = missing;
            }
        }
    }
    *d = '\0';
}

char* utf8Rus(const char* str, bool uppercase) {
  static char buf[BUFLEN];
  strlcpy(buf, str, BUFLEN);
  utf8_to_iso2(buf, '?');
  if(uppercase) {
    for(unsigned char *b = (unsigned char *) buf; *b; ++b)
      *b = iso2_upper_table[*b];
  }
  return buf;
}
#else //#ifndef DSP_LCD
char* utf8Rus(const char* str, bool uppercase) {
  int index = 0;
  static char strn[BUFLEN];
  static char newStr[BUFLEN];
  strncpy(strn, str, BUFLEN - 1);
  strn[BUFLEN - 1] = '\0';
  newStr[0] = '\0';

  while (strn[index]) {
    if (strlen(newStr) > BUFLEN - 2) break;

    uint8_t c1 = (uint8_t)strn[index];
    uint8_t c2 = (uint8_t)strn[index + 1];

    if ((c1 >= 0xC3 && c1 <= 0xC5) && c2 != 0) {
      if (c1 == 0xC3) {
        switch (c2) {
          case 0x93: strcat(newStr, "O"); break; // Ó
          case 0xB3: strcat(newStr, uppercase ? "O" : "o"); break; // ó
        }
      } else if (c1 == 0xC4) {
        switch (c2) {
          case 0x84: strcat(newStr, "A"); break; // Ą
          case 0x85: strcat(newStr, uppercase ? "A" : "a"); break; // ą
          case 0x86: strcat(newStr, "C"); break; // Ć
          case 0x87: strcat(newStr, uppercase ? "C" : "c"); break; // ć
          case 0x98: strcat(newStr, "E"); break; // Ę
          case 0x99: strcat(newStr, uppercase ? "E" : "e"); break; // ę
        }
      } else if (c1 == 0xC5) {
        switch (c2) {
          case 0x81: strcat(newStr, "L"); break; // Ł
          case 0x82: strcat(newStr, uppercase ? "L" : "l"); break; // ł
          case 0x83: strcat(newStr, "N"); break; // Ń
          case 0x84: strcat(newStr, uppercase ? "N" : "n"); break; // ń
          case 0x9A: strcat(newStr, "S"); break; // Ś
          case 0x9B: strcat(newStr, uppercase ? "S" : "s"); break; // ś
          case 0xB9: strcat(newStr, "Z"); break; // Ź
          case 0xBA: strcat(newStr, uppercase ? "Z" : "z"); break; // ź
          case 0xBB: strcat(newStr, "Z"); break; // Ż
          case 0xBC: strcat(newStr, uppercase ? "Z" : "z"); break; // ż
        }
      }
      index += 2;
      continue;
    }

    if(strn[index]==7) strn[index]=165;
    if(strn[index]==9) strn[index]=223;

    // Dodawanie pojedynczego znaku do nowego łańcucha
    if (uppercase) {
      strn[index] = toupper(strn[index]);
    }
    strncat(newStr, &strn[index], 1);
    index++;
  }

  return newStr;
}
#endif //#ifndef DSP_LCD


