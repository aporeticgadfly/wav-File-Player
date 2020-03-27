#include <TMRpcm.h>
#include <pcmConfig.h>
#include <pcmRF.h>

#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

LiquidCrystal lcd(9, 10, 5, 6, 7, 8);

File root;
File counterEntry;
byte volumeLevel = 5;
byte counter = 1;
TMRpcm music;
boolean marker = false;
positionNumber = 0;
boolean ScrollUpButton = 0;
boolean ScrollDownButton = 0;
boolean playButton = 0;
boolean volumeUpButton = 0;
boolean volumeDownButton = 0;
boolean flowStateButton = 0;
byte repeat = 1;
byte continuous = 2;
byte shuffle = 3;
byte flowState = 1;

void setup() {
  
  lcd.begin(16, 2);
  SD.begin(4);
  music.speakerPin = 3;
  pinMode(A0, INPUT); //volume up button
  pinMode(A1, INPUT); //volume down button
  pinMode(A2. INPUT); //play/pause button
  pinMode(A3, INPUT); //scroll up button
  pinMode(A4, INPUT); //scroll down button
  pinMode(A5, INPUT); //flowstate button
  root = SD.open("/");
  root.rewindDirectory();
  music.setVolume(volumeLevel);
  randomSeed(analogRead(2));

  while(counterEntry)
  {
    counterEntry = root.openNextFile();
    counter++;
  }
  
  root.rewindDirectory();
  File Songs[counter];
  
  for(int x = 0; x <= counter; x++)
  {
    counterEntry = root;
    Songs[x] = counterEntry;
    counterEntry = root.openNextFile();
  }

  lcd.print(Songs[0].name());
}

void loop() {

  if(marker == true)
  {
    music.play(Songs[positionNumber]);
  }

  ScrollDownButton = digitalRead(A3);

  if(ScrollDownButton == HIGH && positionCounter < counter)
  {
    positionCounter++;
    lcd.print(Songs[positionCounter].name());
  }

  ScrollUpButton = digitalReadRead(A4);

  if(ScrollUpButton == HIGH && positionCounter > 0)
  {
    positionCounter--;
    lcd.print(Songs[positionCounter].name());
  }

  playButton = digitalRead(A2);
  
  if(playButton == HIGH)
  {
    if(music.isPlaying() == 0)
    {
      music.play(Songs[positionCounter]);
      marker = true;
    }
    else if(music.isPlaying() == 1)
    {
      music.pause(Songs[positionCounter]);
    }
  }

  volumeUpButton = digitalRead(A0);

  if(volumeUpButton == HIGH && volumeLevel <= 7)
  {
    volumeLevel++;
    music.setVolume(volumeLevel);
  }

  volumeDownButton = digitalRead(A1);

  if(volumeDownButton == HIGH && volumeLevel >= 0)
  {
    volumeLevel--;
    music.setVolume(volumeLevel);
  }

  flowStateButton = digitalRead(A5);

  if(flowStateButton == HIGH)
  {
    if(flowState == repeat)
    {
      flowState = continuous;
    }
    else if(flowState == continuous)
    {
      flowState = shuffle;
    }
    else if(flowState == shuffle)
    {
      flowState = repeat;
    }
  }

  if(flowState == repeat)
  {
    
  }
  else if(flowState == continuous)
  {
    if(positionCounter == counter)
    {
      positionCounter = 0;
    }
    else if
    {
      positionCounter++;
    }
  }
  else if(flowState == shuffle)
  {
    positionNumber = random(counter+1);
  }
}
