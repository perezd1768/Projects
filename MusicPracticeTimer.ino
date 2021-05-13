#include <Wire.h>
#include "DFRobot_LCD.h"
#include "arduinoFFT.h"
#include <stdio.h>
#define SAMPLES 4096              //Must be a power of 2(=2^12)
#define SAMPLING_FREQUENCY 10000  //Hz, must be less than 10000 due to ADC (12-bits)
DFRobot_LCD lcd(16, 2); //16 characters and 2 lines of show

// things for FFT
arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

double Freq[7] = {110.0, 123.5, 65.41, 73.42, 82.41, 87.31};

//LED & Sensors
const int IR_Sensor = 13;          //IR sensor to D2
const int IR =  12;               //LED for IR sensor
const int Ss =  11;               //LED for Sound Sensor
const float Sound_Sensor = 0;

//Threshold & Miscellaneous
int x = 5;  //threshold
int r, g, b;//color variables
int t = 0;  //time

// 4 push buttons - red, green, yellow, white
// red = start/stop, green = set, yellow = stopwatch, white = timer
int green = 8;
int red = 7;
int yellow = 9;
int blue = 10;

// up = count up time for Stopwatch Function
int upseconds = 0;
int upminutes = 0;
int uphours = 0;

// down = count down time for Timer Function
int downseconds = 0;
int downminutes = 0;
int downhours = 0;

int pausesec = 0;
int pausemin = 0;
int pausehr = 0;

int playsec = 0;
int playmin = 0;
int playhr = 0;

const int SAMPLE_TIME = 10000;
unsigned long millCurrent;
unsigned long millLast = 0;
unsigned long millElapsed = 0;
int sampleBufferValue = 0;

int done = 0;

void Timer();
void Stopwatch();
void TransformT();
void TransformS();
void CountDown();
void CountUp();

void setup()
{
  Serial.begin(115200);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  lcd.init();
  pinMode(red, INPUT);
  pinMode(green, INPUT);
  pinMode(yellow, INPUT);
  pinMode(blue, INPUT);
}
void loop()
{

  int val;
  int selection = 0;
  val = analogRead(0); //connect mic sensor to Analog 0
  Serial.println(val, DEC); //print the sound value to serial
  delay(100);

  millCurrent = millis();
  millElapsed = millCurrent - millLast;

  //  startUpMenu();

  //START SCREEN
  lcd.clear();
  lcd.setRGB(200, 200, 200);
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Music");
  lcd.setCursor(0, 1);
  lcd.print("Practice Timer");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Before we begin");
  lcd.setCursor(0, 1);
  lcd.print("menu options...");
  delay(2000);

  //MENU OPTIONS
  lcd.setRGB(200, 200, 0);                  //Set R,G,B Value
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Yellow");
  lcd.setCursor(0, 1);
  lcd.print("for Count Up...");
  delay(2000);

  lcd.setRGB(0, 0, 200);                  //Set R,G,B Value
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Blue");
  lcd.setCursor(0, 1);
  lcd.print("for Count Down...");
  delay(2000);

  lcd.setRGB(0, 200, 0);                  //Set R,G,B Value
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Green Button:");
  lcd.setCursor(0, 1);
  lcd.print("Select");
  delay(2000);

  lcd.setRGB(200, 0, 0);                  //Set R,G,B Value
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Red Button:");
  lcd.setCursor(0, 1);
  lcd.print("Start/Stop");
  delay(2000);

  while (true) {
    int valb = digitalRead(blue); //allows for input
    int valy = digitalRead(yellow);
    int valg = digitalRead(green);
    int valr = digitalRead(red);

    r = (abs(sin(3.14 * t / 180))) * 255;
    g = (abs(sin(3.14 * (t + 60) / 180))) * 255;
    b = (abs(sin(3.14 * (t + 120) / 180))) * 255;
    t = t + 10;
    
    lcd.setCursor(0, 0);
    lcd.setRGB(r, g, b);
    lcd.print("Count Up (Y)");
    lcd.setCursor(0, 1);
    lcd.print("Count Down (B)?");
    delay(1000);

    if (valy == HIGH)
    {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.setRGB(255, 255, 0);
      lcd.print("Count Up");
      lcd.setCursor(0, 1);
      delay(2000);
      lcd.clear();
      while (true)
      {
        int valg = digitalRead(green);
        int valr = digitalRead(red);

        lcd.setCursor(0, 0);
        lcd.setRGB(0, 200, 0);
        lcd.print("Green to confirm");
        delay(2000);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.setRGB(200, 0, 0);
        lcd.print("Red to go back");
        delay(2000);
        valg = digitalRead(green);
        valr = digitalRead(red);
        if (valg == HIGH)
        {
          //STOPWATCH function begins
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.setRGB(0, 200, 0);
          lcd.print("Count Up");
          delay(1000);
          lcd.clear();
          Stopwatch();
          break;
        }
        else if (valr == HIGH)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Red");
          delay(1000);
          lcd.clear();
          break;
        }
      }
      break;
    }

    if (valb == HIGH)
    {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.setRGB(200, 200, 200);
      lcd.print("Count Down");
      lcd.setCursor(0, 1);
      delay(2000);
      lcd.clear();
      while (true)
      {
        int valg = digitalRead(green);
        int valr = digitalRead(red);

        lcd.setCursor(0, 0);
        lcd.setRGB(0, 200, 0);
        lcd.print("Green to confirm");
        delay(2000);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.setRGB(200, 0, 0);
        lcd.print("Red to go back");
        delay(2000);
        valg = digitalRead(green);
        valr = digitalRead(red);
        if (valg == HIGH)
        {
          //TIMER function begins
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.setRGB(0, 200, 0);
          lcd.print("Count Down");
          delay(1000);
          lcd.clear();
          Timer();
          break;
        }
        else if (valr == HIGH)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.setRGB(200, 0, 0);
          lcd.print("Red");
          delay(1000);
          lcd.clear();
          break;
        }
      }
      break;
    }
    else {
      continue;
    }
  }
}

void Timer() {
  int selection = 0;
  downseconds = 0;
  downminutes = 0;
  downhours = 0;

  while (true) {

    int valr = digitalRead(red); //read red button first
    if (valr == HIGH) {
      break;
    }

    lcd.setRGB(200, 200, 200);

    int valg = digitalRead(green);
    int valy2 = digitalRead(yellow);
    int valb2 = digitalRead(blue);

    //read the input buttons
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Set the time");
    delay(2000);

    lcd.clear();
    lcd.setRGB(0, 200, 0);
    lcd.setCursor(2, 0);
    lcd.print("Press Green");
    lcd.setCursor(3, 1);
    lcd.print("to start");
    delay(2000);

    lcd.clear();
    lcd.setRGB(0, 0, 200);
    lcd.setCursor(2, 0);
    lcd.print("Press Blue");
    lcd.setCursor(3, 1);
    lcd.print("to change");
    delay(2000);

    valg = digitalRead(green);
    valy2 = digitalRead(yellow);
    valb2 = digitalRead(blue);

    if (valb2 == HIGH) {
      delay(100);
      valb2 = digitalRead(blue);
      if (valb2 == HIGH) {
        if (selection == 0) {
          lcd.clear();
          lcd.setRGB(200, 200, 200);
          lcd.setCursor(0, 1);
          lcd.print("Minutes");
          selection++;
        }
        else if (selection == 1) {
          lcd.clear();
          lcd.setRGB(200, 200, 200);
          lcd.setCursor(0, 1);
          lcd.print("Hours");
          selection++;
        }

        else if (selection == 2) {
          lcd.clear();
          lcd.setRGB(200, 200, 200);
          lcd.setCursor(0, 1);
          lcd.print("Seconds");
          selection = 0;
        }
      }
    }

    //reading green to start program
    if (valg = HIGH) {
      delay(500);
      valg = digitalRead(green);
      if (valg == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Ready...");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Set...");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Go!!!");
        delay(1000);
        TransformT();
        break;
      }
    }

    //reading yellow to increment changes depending on white pressed
    if (valy2 = HIGH) {
      delay(200);
      valy2 = digitalRead(yellow);

      if (valy2 == HIGH && selection == 0) {
        while (valy2 == HIGH) {
          valy2 = digitalRead(yellow);
          if (valy2 == LOW) {
            break;
          }
          if (downseconds == 60 && valy2 == HIGH) {
            downseconds = 0;
            if (downminutes != 60) {
              downminutes++;
            }
          }

          else {
            lcd.clear();
            downseconds++;
            lcd.printf("%i:%i:%i", downhours, downminutes, downseconds);
            delay(200);
          }

        }
      }

      if (valy2 == HIGH && selection == 1) {

        while (valy2 == HIGH) {
          valy2 = digitalRead(yellow);

          if (valy2 == LOW) {
            break;
          }
          else if (downminutes == 60 && valy2 == HIGH) {
            downminutes = 0;
            if (downhours != 5) {
              downhours++;
            }
          }

          else {
            lcd.clear();
            downminutes++;
            lcd.printf("%i:%i:%i", downhours, downminutes, downseconds);
            delay(1000);
          }

        }
      }

      if (valy2 == HIGH && selection == 2) {
        while (valy2 == HIGH) {
          valy2 = digitalRead(yellow);
          if (valy2 == LOW) {
            break;
          }
          else if (downhours == 5 && valy2 == HIGH) {
            downhours = 0;
            delay(1000);
          }
          else {
            lcd.clear();
            downhours++;
            lcd.printf("%i:%i:%i", downhours, downminutes, downseconds);
            delay(1000);
          }

        }
      }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("%i:%i:%i", downhours, downminutes, downseconds); //formating string to be printed on LCD
    delay(3000);

  }
}

void TransformT() {

  bool complete = false;
  playsec = 0;
  playmin = 0;
  playhr = 0;
  pausehr = 0;
  pausemin = 0;
  pausesec = 0;
  done = 0;

  while (true) {

    int valt = digitalRead(red);

    if (complete == true) {
      int valtg = digitalRead(green);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("All Done!");
      delay(2000);
      while (true) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printf("Played: %i:%i:%i", playhr, playmin, playsec);
        lcd.setCursor(0, 1);
        lcd.printf("Paused: %i:%i:%i", pausehr, pausemin, pausesec);
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Press Green to");
        lcd.setCursor(4, 1);
        lcd.print("Finish");
        delay(2000);
        valtg = digitalRead(green);
        if (valtg == HIGH) {
          complete = false;
          done = 1;
          break;
        }
      }
      if (done == 1) {
        break;
      }
    }

    if (analogRead(0) < x || digitalRead(IR_Sensor) == LOW) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Keep Going!");
      while (analogRead(0) < x || digitalRead(IR_Sensor) == LOW) {
        if (pausesec == 60) {
          if (pausemin == 60) {
            pausemin = 0;
            pausehr++;
          }
          pausesec = 0;
          pausemin++;
        }
        pausesec++;
        delay(1000);
        if (valt == HIGH) {
          complete = true;
          break;
        }
        if (analogRead(0) >= x && digitalRead(IR_Sensor) == HIGH) {
          break;
        }
      }
    }
    if (analogRead(0) >= x && digitalRead(IR_Sensor) == HIGH) {
      while (analogRead(0) >= x || digitalRead(IR_Sensor) == HIGH) {
        if (valt == HIGH) {
          complete = true;
          break;
        }
        for (int i = 0; i < SAMPLES; i++)
        {
          microseconds = micros();    //Overflows after around 70 minutes!
          vReal[i] = analogRead(0);
          vImag[i] = 0;
          while (micros() < (microseconds + sampling_period_us)) {
          }
        }
        CountDown();
        if (playsec == 60) {
          if (playmin == 60) {
            playmin = 0;
            playhr++;
          }
          playsec = 0;
          playmin++;
        }
        playsec++;

        if (downseconds == 0 && downminutes == 0 && downhours == 0) {
          complete = true;
          break;
        }
      }
    }
  }

  /*FFT*/
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

  /*PRINT RESULTS*/
  //Serial.println(peak);     //Print out what frequency is the most dominant.
  for (int i = 0; i < (SAMPLES / 4); i++)
  {
    //Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
    //Serial.print(" ");
    Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
  }
}

void Stopwatch() {
  while (true) {
    int valgS = digitalRead(green);
    int valrS = digitalRead(red);

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.setRGB(0, 200, 0);
    lcd.print("Green to start");
    delay(2000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.setRGB(200, 0, 0);
    lcd.print("Red to go back");
    delay(2000);
    valgS = digitalRead(green);
    valrS = digitalRead(red);
    if (valgS == HIGH)
    {
      //STOPWATCH function begins
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.setRGB(0, 200, 0);
      lcd.print("Get ready...");
      delay(1000);
      lcd.clear();
      lcd.print("Get set...");
      delay(1000);
      lcd.clear();
      lcd.print("Play!");
      TransformS();
      break;
    }
    else if (valrS == HIGH)
    {
      break;
    }
  }
}

void TransformS() {

  playsec = 0;
  playmin = 0;
  playhr = 0;
  pausehr = 0;
  pausemin = 0;
  pausesec = 0;
  done = 0;

  while (true) {

    int valsr = digitalRead(red);
    int valsg = digitalRead(green);

    if (analogRead(0) < x || digitalRead(IR_Sensor) == LOW) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Keep Going!");
      while (analogRead(0) < x || digitalRead(IR_Sensor) == LOW) {
        if (pausesec == 60) {
          if (pausemin == 60) {
            pausemin = 0;
            pausehr++;
          }
          pausesec = 0;
          pausemin++;
        }
        pausesec++;
        delay(1000);
        valsr = digitalRead(red);
        if (valsr == HIGH) {

          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("All Done!");
          delay(2000);
          while (true) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.printf("Played: %i:%i:%i", playhr, playmin, playsec);
            lcd.setCursor(0, 1);
            lcd.printf("Paused: %i:%i:%i", pausehr, pausemin, pausesec);
            delay(2000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Press Green to");
            lcd.setCursor(4, 1);
            lcd.print("Finish");
            delay(2000);
            valsg = digitalRead(green);
            if (valsg == HIGH) {
              done = 1;
              break;
            }
          }
        }

        if (analogRead(0) >= x && digitalRead(IR_Sensor) == HIGH) {
          break;
        }
      }
      if (done == 1) {
        break;
      }
    }

    if (analogRead(0) >= x && digitalRead(IR_Sensor) == HIGH) {
      while (analogRead(0) >= x || digitalRead(IR_Sensor) == HIGH) {
        valsr = digitalRead(red);
        if (valsr == HIGH) {
          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("All Done!");
          delay(2000);
          while (true) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.printf("Played: %i:%i:%i", playhr, playmin, playsec);
            lcd.setCursor(0, 1);
            lcd.printf("Paused: %i:%i:%i", pausehr, pausemin, pausesec);
            delay(2000);
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("Press Green to");
            lcd.setCursor(4, 1);
            lcd.print("Finish");
            delay(2000);
            valsg = digitalRead(green);
            if (valsg == HIGH) {
              break;
            }
          }
          lcd.clear();
          break;
        }
        for (int i = 0; i < SAMPLES; i++)
        {
          microseconds = micros();    //Overflows after around 70 minutes!
          vReal[i] = analogRead(0);
          vImag[i] = 0;
          while (micros() < (microseconds + sampling_period_us)) {
          }
        }
        CountUp();
         if (playsec == 60) {
          if (playmin == 60) {
            playmin = 0;
            playhr++;
          }
          playsec = 0;
          playmin++;
        }
        playsec++;
      }
    }


    /*FFT*/
//    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
//    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
//    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
//    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

    /*PRINT RESULTS*/
    //Serial.println(peak);     //Print out what frequency is the most dominant.
//    for (int i = 0; i < (SAMPLES / 4); i++)
//    {
//      //Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
//      //Serial.print(" ");
//      Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
//    }
  }
}
void CountUp() {
  if (upseconds == 60) {
    if (upminutes == 60) {
      upminutes = 0;
      uphours++;
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.printf("%i:%i:%i", uphours, upminutes, upseconds); //formating string to be printed on LCD
      delay(200);
    }
    upseconds = 0;
    upminutes++;
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.printf("%i:%i:%i", uphours, upminutes, upseconds); //formating string to be printed on LCD
    delay(200);
  }
  upseconds++;
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.printf("%i:%i:%i", uphours, upminutes, upseconds); //formating string to be printed on LCD
  delay(200);

}

void CountDown() {
  if (downseconds == 0) {
    if (downminutes == 0) {
      downseconds = 59;
      downminutes = 59;
      downhours--;
      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.printf("%i:%i:%i", downhours, downminutes, downseconds); //formating string to be printed on LCD
      delay(200);
    }
    downseconds = 10;
    downminutes--;
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.printf("%i:%i:%i", downhours, downminutes, downseconds); //formating string to be printed on LCD
    delay(200);
  }
  downseconds--;
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.printf("%i:%i:%i", downhours, downminutes, downseconds); //formating string to be printed on LCD
  delay(200);
}
