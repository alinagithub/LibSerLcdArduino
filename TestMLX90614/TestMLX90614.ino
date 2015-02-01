
#include <Wire.h>
#include <SoftwareSerial.h>

#include <Adafruit_MLX90614.h> // see https://github.com/adafruit/Adafruit-MLX90614-Library    
#include <libserlcdarduino.h>  // see https://github.com/alinagithub/LibSerLcdArduino

SerLcd16x2Arduino LCD(7);
Adafruit_MLX90614 mlx  = Adafruit_MLX90614();

void setup()
{
  Serial.begin(9600);
  mlx.begin();
  
  LCD.Clear();
  LCD.SetBrightness(80);
  LCD.SetDisplay(true, false, false);
  LCD.Print(1,1,"Global:",7);
  LCD.Print(2,1,"Local:",6);
}


void loop() 
{
  String Measure;
  
  Measure = "";
  Measure += mlx.readAmbientTempC();
  LCD.Print(1,9,Measure);
  LCD.Print(1,14,"_C ",3);
  
  Measure = "";
  Measure += mlx.readObjectTempC();
  LCD.Print(2,9,Measure);  
  LCD.Print(2,14,"_C ",3); 
}


