#pragma once

#include "Arduino.h"
#include "config.h"

#ifdef DEBUGAPP
#define DEBUG1(a1)       { Serial.println(a1); }
#define DEBUG2(a1,a2)    { Serial.print(a1); Serial.print(" "); Serial.println(a2); }
#define DEBUG3(a1,a2,a3) { Serial.print(a1); Serial.print(" ");Serial.print(a2);Serial.print(" ");Serial.println(a3); }
#define DEBUG4(a1,a2,a3,a4) { Serial.print(a1); Serial.print(" "); Serial.print(a2); Serial.print(" ");Serial.print(a3); Serial.print(" "); Serial.println(a4); }
#define DEBUG5(a1,a2,a3,a4,a5) { Serial.print(a1); Serial.print(" "); Serial.print(a2); Serial.print(" ");Serial.print(a3); Serial.print(" "); Serial.print(a4); Serial.print(" "); Serial.println(a5);}
#define DEBUG6(a1,a2,a3,a4,a5,a6) { Serial.print(a1); Serial.print(" "); Serial.print(a2); Serial.print(" ");Serial.print(a3); Serial.print(" "); Serial.print(a4); Serial.print(" "); Serial.print(a5); Serial.print(" "); Serial.println(a6);}
#else
#define DEBUG1(a1)       { ; }
#define DEBUG2(a1,a2)    { ;}
#define DEBUG3(a1,a2,a3) { ;}
#define DEBUG4(a1,a2,a3,a4) { ;}
#define DEBUG5(a1,a2,a3,a4,a5) { ;}
#define DEBUG6(a1,a2,a3,a4,a5,a6) { ;}
#endif



