//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// FILE: libserlcdarduino.cpp
// VERSION: 0.1.00
// PURPOSE: Easy controlling 16x2 serial lcd
// CREATED BY: Arnaud D. LINA
// DATE: Jan 2015
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\


#include <SoftwareSerial.h>
#include "libserlcdarduino.h"

// General
#define LCD_NUMBER_LINES         2
#define LCD_NUMBER_CHARS         16

// Special Commands
#define LCD_SPECIAL_COMMAND      0x7C
#define LCD_BACKLIGHT_MIN	     128
#define LCD_BACKLIGHT_MAX	     157

// Commands
#define LCD_COMMAND              0xFE
#define LCD_CLEARDISPLAY	     0x01
#define LCD_HOMEDISPLAY          0x02
#define LCD_SETDDRAMADDR	     0x80
#define LCD_CMD_DISPLAY          0x08
#define LCD_SETDISPLAY_ON        0x04
#define LCD_SETCURSOR_ON         0x02
#define LCD_SETBLINK_ON          0x01
#define LCD_DISPLAY_SHIFT_RIGHT  0x1C
#define LCD_DISPLAY_SHIFT_LEFT   0x18
#define LCD_CURSOR_SHIFT_RIGHT   0x14
#define LCD_CURSOR_SHIFT_LEFT    0x10
#define LCD_ENTRY_MODE_RIGHT     0x06
#define LCD_ENTRY_MODE_LEFT      0x04
   

namespace libserlcdarduino
{

/////////////////////////////////////////////////////
//
// PUBLIC
//

SerLcd16x2Arduino::SerLcd16x2Arduino(int pin) : SoftwareSerial(pin, pin)
   {
   pinMode(pin, OUTPUT);
   begin(9600);
   }

void SerLcd16x2Arduino::SetBrightness(int value)
   {
   if((value>=0) && (value<=100))
      {
      int MapValue = map(value, 0,100,LCD_BACKLIGHT_MIN,LCD_BACKLIGHT_MAX);
      LcdCommand(LCD_SPECIAL_COMMAND, MapValue);
      } 
   }

void SerLcd16x2Arduino::Home()
   {
   LcdCommand(LCD_COMMAND, LCD_HOMEDISPLAY);
   }
   
void SerLcd16x2Arduino::Clear()
   {
   LcdCommand(LCD_COMMAND, LCD_CLEARDISPLAY);
   }

void SerLcd16x2Arduino::ClearLine(int line)
   {
   if((line > 0) && (line<= LCD_NUMBER_LINES))
      {
      SetPosition(line, 1);
      write("                ");
      SetPosition(line, 1);
      }
   }
   
void SerLcd16x2Arduino::ClearRange(int line, int pos, int size)
   {
   for (int i=0; i<size; i++)
      {
      SetPosition(line, pos+i);
      write(" ");
      }
   }

void SerLcd16x2Arduino::Print(int line, int pos, char* string, int size)
   {
   int max_print = min((LCD_NUMBER_CHARS+1-pos), size);
   for (int i=0; i<max_print; i++)
      {
      SetPosition(line, pos+i);
      write(string[i]);
      }
   }
   
void SerLcd16x2Arduino::Print(int line, int pos, String& string)
   {
   int max_print = min((LCD_NUMBER_CHARS+1-pos), string.length());
   for (int i=0; i<max_print; i++)
      {
      SetPosition(line, pos+i);
      write(string.charAt(i));
      }
   }
   
void SerLcd16x2Arduino::Print(int line, int pos, uint8_t* charmap, int size)
   {
   int max_print = min((LCD_NUMBER_CHARS+1-pos), size);
   for (int i=0; i<max_print; i++)
      {
      SetPosition(line, pos+i);
      write(charmap[i]);
      }
   }

void SerLcd16x2Arduino::MoveToStart(int line)
   {
   if((line > 0) && (line <= LCD_NUMBER_LINES))
      SetPosition(line, 1);
   }

void SerLcd16x2Arduino::SetDisplay(boolean DisplayOn, boolean CursorOn, boolean CursorBlinkOn)
   {
   uint8_t display_command = LCD_CMD_DISPLAY;
   if(DisplayOn)     {display_command |= LCD_SETDISPLAY_ON;}
   if(CursorOn)      {display_command |= LCD_SETCURSOR_ON;}
   if(CursorBlinkOn) {display_command |= LCD_SETBLINK_ON;}
   LcdCommand(LCD_COMMAND, display_command);
   }
   
void SerLcd16x2Arduino::DisplayScrollRight(int value, int delayval)
   {
   for(int i=0; i<value; i++)
      {
      LcdCommand(LCD_COMMAND, LCD_DISPLAY_SHIFT_RIGHT);
      delay(delayval);
      }
   }

void SerLcd16x2Arduino::DisplayScrollLeft(int value, int delayval)
   {
   for(int i=0; i<value; i++)
      {
      LcdCommand(LCD_COMMAND, LCD_DISPLAY_SHIFT_LEFT);
      delay(delayval);
      }
   }
   
void SerLcd16x2Arduino::CursorMoveLeft(int value)
   {
   for(int i=0; i<value; i++)
      {
      LcdCommand(LCD_COMMAND, LCD_CURSOR_SHIFT_LEFT);
      }
   }
   
void SerLcd16x2Arduino::CursorMoveRight(int value)
   {
   for(int i=0; i<value; i++)
      {
      LcdCommand(LCD_COMMAND, LCD_CURSOR_SHIFT_RIGHT);
      }
   }
   
void SerLcd16x2Arduino::SetEntryModeRight(boolean movedisplay)
   {
   uint8_t entry_command = LCD_ENTRY_MODE_RIGHT;
   if(movedisplay) {entry_command |= 0x01;}
   LcdCommand(LCD_COMMAND, entry_command);
   }

void SerLcd16x2Arduino::SetEntryModeLeft(boolean movedisplay)
   {
   uint8_t entry_command = LCD_ENTRY_MODE_LEFT;
   if(movedisplay) {entry_command |= 0x01;}
   LcdCommand(LCD_COMMAND, entry_command);
   }

void SerLcd16x2Arduino::SetPosition(int line, int pos)
   {
   if((pos > 0) && (pos <= LCD_NUMBER_CHARS))
      {
	  if(line==1)
         LcdCommand(LCD_COMMAND, LCD_SETDDRAMADDR | (pos - 1));
	   else if(line==2)
	     LcdCommand(LCD_COMMAND, LCD_SETDDRAMADDR | ((pos - 1) + 0x40));
	   }
   }

/////////////////////////////////////////////////////
//
// PRIVATE
//

void SerLcd16x2Arduino::LcdCommand(uint8_t code, uint8_t value)
   {
   write(code);
   write(value);
   delay(5);
   }
}