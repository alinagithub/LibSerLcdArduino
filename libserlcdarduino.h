//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// FILE: libserlcdarduino.h
// VERSION: 0.1.00
// PURPOSE: Easy controlling 16x2 serial lcd
// CREATED BY: Arnaud D. LINA
// DATE: Jan 2015
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\

#ifndef libserlcdarduino_h
#define libserlcdarduino_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

#include "SoftwareSerial.h"

#define LIBSERLCDARDUINO_LIB_VERSION "0.1.00"

namespace libserlcdarduino
{

class SerLcd16x2Arduino : public SoftwareSerial 
{
/*
   Arduino sample code:
   ====================
    
    #include <LibSerLcdArduino.h>
    
    #define LcdPin           7
    
    // Instantiate the serial lcd object
    SerLcd16x2Arduino myLcd(LcdPin);
   
    void setup()
    {
    }
   
    void loop()
    {
      String myString = "Hello World";
      
      myLcd.Clear();                       // clear the display
      myLcd.SetBrightness(80);             // set the brightness to 80%
      myLcd.SetDisplay(true, true, false); // enable display and cursor underline
      myLcd.Print(1,3,myString);           // print a string @ line 1, offset 3
      delay(1000);
    }
   */
   
public:
	SerLcd16x2Arduino (int lcdpin);
	/* 
    Allocation function:
       
         - lcdpin:  specifies the Arduino pin connected to the lcd serial input
       
    ex: SerLcd16x2Arduino myLcd(7);
    */

    void Home();
    /* 
    Set the cursor to the first position of 
    the first line (Home position).
              
    ex: myLcd.Home();
    */
    
	void Clear();
	/* 
    Clear the display:
              
    ex: myLcd.Clear();
    */
      
	void ClearLine(int line);
	/* 
    Clear a line:
       - line: the line index (1 or 2)
              
    ex: myLcd.ClearLine(1);
    */
    
    void ClearRange(int line, int pos, int size);
    /* 
    Clear a section:
      - line: the line index (1 or 2)
      - pos: the position in the line (1 to 16)
      - size: the number of characters to clear
              
    ex: myLcd.ClearRange(1, 4, 2);
    */
    
	void SetBrightness(int value=100);
	/* 
    Sets the display brightness:
       - value: from 0 to 100
       
    ex: myLcd.SetBrightness(80);
    */
    
	void MoveToStart(int line);
	/* 
    Move the cursor at the beginning of the line:
       - line: the line index (1 or 2)
       
    ex: myLcd.MoveToStart(2);
    */
    
    void SetPosition(int line=1, int pos=1);
    /* 
    Move the cursor at the specified location:
       - line: the line index (1 or 2)
       - pos: the position in the line (1 to 16)
       
    ex: myLcd.SetPosition(2,7);
    */
    
	void SetDisplay(boolean DisplayOn=true, boolean CursorOn=false, boolean CursorBlinkOn=false);
	/* 
    Sets the display mode:
       - DisplayOn: whether the display is On or Off
       - CursorOn: whether the cursor line is displayed or not
       - CursorBlinkOn: whether the cursor position blinks or not
       
    ex: myLcd.SetDisplay(true,true, false);
    */
	
	void DisplayScrollRight(int value=1, int delayval=100);
	/* 
    Moves the display to the right.
       - value: displacement size
       - delayval: delay between each displacement (in ms)
       
    ex: myLcd.DisplayScrollRight(3, 100);
    */
    
    void DisplayScrollLeft(int value=1, int delayval=100);
    /* 
    Moves the display to the left.
       - value: displacement size
       - delayval: delay between each displacement (in ms)
       
    ex: myLcd.DisplayScrollLeft(3, 100);
    */
    
    void CursorMoveRight(int value=1);
    /* 
    Moves the cursor to the right.
       - value: displacement size
       
    ex: myLcd.CursorMoveRight(2);
    */
    
    void CursorMoveLeft(int value=1);
    /* 
    Moves the display to the right.
       - value: displacement size
       
    ex: myLcd.CursorMoveLeft(3);
    */
    
    void Print(int line, int pos, String& string);
    /* 
    Display a String at the specified location.
    The string is clipped at the end of the line.
       - line: the line index (1 or 2)
       - pos: the position in the line (1 to 16)
    
    ex: String myString = "Hello String";
        myLcd.Print(1,3,myString);
    */
    
    void Print(int line, int pos, char* arrayChar, int size);
    /* 
    Display an array of characters at the specified location.
    The string is clipped at the end of the line.
       - line: the line index (1 or 2)
       - pos: the position in the line (1 to 16)
    
    ex: char myChars[] = "Hello String";
        myLcd.Print(1,3,myChars,12);
    */
    
    void Print(int line, int pos, uint8_t* arrayCode, int size);
    /* 
    Display an array of ascii codes at the specified location.
    The string is clipped at the end of the line.
       - line: the line index (1 or 2)
       - pos: the position in the line (1 to 16)
    
    ex:  uint8_t myAscii[] = {72, 69, 76, 76, 79, 33, 33}; // HELLO!!
         myLcd.Print(1,3,myAscii,7);
    */
    
    void SetEntryModeRight(boolean movedisplay=false);
    /* 
    Sets the lcd entry mode to the right (advanced).
    Characters (using .write() ) are printed left to right.
       -movedisplay: whether the display is also moved.
       
    ex: myLcd.SetEntryModeRight(false);
    */
    
    void SetEntryModeLeft(boolean movedisplay=false);
    /* 
    Sets the lcd entry mode to the left (advanced).
    Characters (using .write() ) are printed right to left.
       -movedisplay: whether the display is also moved.
       
    ex: myLcd.SetEntryModeLeft(false);
    */



private:
	void LcdCommand(uint8_t, uint8_t);

};

} // end namespace
#endif

using namespace libserlcdarduino;
//
// END OF FILE
//