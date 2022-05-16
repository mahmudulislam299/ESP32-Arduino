#ifndef _HTTP_H_
#define _HTTP_H_
#include <Arduino.h>
#include "includefile.h"

// const char server[]   = "vsh.pp.ua";
// const char resource[] = "/TinyGSM/logo.txt";
const int      port = 80;
const char server[] = "showcase.api.linx.twenty57.net";
const char resource[] = "/UnixTime/tounix?date=now";


uint32_t getUnixTime();


#endif // _HTTP_H_