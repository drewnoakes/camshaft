#include "camshaft/ccolor.hh"

#include <stdio.h>

#define CC_FORECOLOR(C) "\033[" #C "m"
#define CC_BACKCOLOR(C) "\033[" #C "m"
#define CC_ATTR(A) "\033[" #A "m"

enum Color
{
  Black = 0,
  Red = 1,
  Green = 2,
  Yellow = 3,
  Blue = 4,
  Magenta = 5,
  Cyan = 6,
  White = 7,
  Default = 9
};

enum Attributes
{
  Reset = 0,
  Bright = 1,
  Dim = 2,
  Underline = 3,
  Blink = 4,
  Reverse = 5,
  Hidden = 6
};

char* ccolor::color(int attr, int fg, int bg)
{
  static char command[13];

  // Command is the control command to the terminal
  sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
  return command;
}

const char* ccolor::error = CC_FORECOLOR(91);
const char* ccolor::warning = CC_FORECOLOR(95);
const char* ccolor::info = CC_FORECOLOR(92);

const char* ccolor::reset = CC_ATTR(0);
const char* ccolor::bold = CC_ATTR(1);
const char* ccolor::underline = CC_ATTR(4);

const char* ccolor::fore::black = CC_FORECOLOR(30);
const char* ccolor::fore::blue = CC_FORECOLOR(34);
const char* ccolor::fore::red = CC_FORECOLOR(31);
const char* ccolor::fore::magenta = CC_FORECOLOR(35);
const char* ccolor::fore::green = CC_FORECOLOR(92);
const char* ccolor::fore::cyan = CC_FORECOLOR(36);
const char* ccolor::fore::yellow = CC_FORECOLOR(33);
const char* ccolor::fore::white = CC_FORECOLOR(37);
const char* ccolor::fore::console = CC_FORECOLOR(39);

const char* ccolor::fore::lightblack = CC_FORECOLOR(90);
const char* ccolor::fore::lightblue = CC_FORECOLOR(94);
const char* ccolor::fore::lightred = CC_FORECOLOR(91);
const char* ccolor::fore::lightmagenta = CC_FORECOLOR(95);
const char* ccolor::fore::lightgreen = CC_FORECOLOR(92);
const char* ccolor::fore::lightcyan = CC_FORECOLOR(96);
const char* ccolor::fore::lightyellow = CC_FORECOLOR(93);
const char* ccolor::fore::lightwhite = CC_FORECOLOR(97);

const char* ccolor::back::black = CC_BACKCOLOR(40);
const char* ccolor::back::blue = CC_BACKCOLOR(44);
const char* ccolor::back::red = CC_BACKCOLOR(41);
const char* ccolor::back::magenta = CC_BACKCOLOR(45);
const char* ccolor::back::green = CC_BACKCOLOR(42);
const char* ccolor::back::cyan = CC_BACKCOLOR(46);
const char* ccolor::back::yellow = CC_BACKCOLOR(43);
const char* ccolor::back::white = CC_BACKCOLOR(47);
const char* ccolor::back::console = CC_BACKCOLOR(49);

const char* ccolor::back::lightblack = CC_BACKCOLOR(100);
const char* ccolor::back::lightblue = CC_BACKCOLOR(104);
const char* ccolor::back::lightred = CC_BACKCOLOR(101);
const char* ccolor::back::lightmagenta = CC_BACKCOLOR(105);
const char* ccolor::back::lightgreen = CC_BACKCOLOR(102);
const char* ccolor::back::lightcyan = CC_BACKCOLOR(106);
const char* ccolor::back::lightyellow = CC_BACKCOLOR(103);
const char* ccolor::back::lightwhite = CC_BACKCOLOR(107);
