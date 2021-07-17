
/* Example sketch using progmem to store wav filenames. Uses 
program memory to store filenames instead of ram when playing
many different wav files. 
See http://arduino.cc/en/Reference/PROGMEM for more info.
Sketch below based on the above link
*/

#include <avr/pgmspace.h>
#include <TMRpcm.h>
#include <SPI.h>

TMRpcm wav;

#include <SD.h>
#define SD_ChipSelectPin 10
int beforeJoke = 0;
static const char wav_1[] PROGMEM = "joke0.wav";
static const char wav_2[] PROGMEM = "joke1.wav";
static const char wav_3[] PROGMEM = "joke2.wav";
static const char wav_4[] PROGMEM = "joke3.wav";
static const char wav_5[] PROGMEM = "joke4.wav";
static const char wav_6[] PROGMEM = "joke5.wav";
static const char wav_7[] PROGMEM = "joke6.wav";
static const char wav_8[] PROGMEM = "joke7.wav";
static const char wav_9[] PROGMEM = "joke8.wav";
static const char wav_10[] PROGMEM = "joke9.wav";
static const char wav_11[] PROGMEM = "joke10.wav";


const char *wav_table[] = 
{
  wav_1,
  wav_2,
  wav_3,
  wav_4,
  wav_5,
  wav_6,
  wav_7,
  wav_8,
  wav_9,
  wav_10,
  wav_11
  //etc..
};


void setup(){
  
  Serial.begin(115200);
  wav.speakerPin = 9; 
  pinMode(10,OUTPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  
  if (!SD.begin(SD_ChipSelectPin)) { 
    Serial.println("SD fail");  
    return;
  }else{   Serial.println("SD ok"); }

  wav.volume(1);
  wav.quality(1);

}


void loop(){
if(!wav.isPlaying()) {
    digitalWrite(wav.speakerPin, LOW);
  }

  
  if(digitalRead(7) == HIGH){
    delay(2000);
      char wavFile[33];
      int jokeNumber = random(0, 10);
      beforeJoke = jokeNumber;
      Serial.println(jokeNumber);
         strcpy_P(wavFile, wav_table[jokeNumber]);
                wav.play(wavFile);
     
      }
      if(digitalRead(6) == HIGH){
    delay(2000);
      char wavFile[33];
      Serial.println(beforeJoke);
         strcpy_P(wavFile, wav_table[beforeJoke]);
                wav.play(wavFile);
     
      }
  
}
