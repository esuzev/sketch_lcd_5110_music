// http://fritzing.org/media/fritzing-repo/projects/p/play-snake-on-arduino-nano-with-ir/code/Tuorial%20Snake.ino

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
//#include <IRremote.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);  //Initialise display object

// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

const static unsigned char PROGMEM logoBmp[] =
{
  B11111111, B11111111, B10000000,
  B11111111, B11111111, B10000000,
  B11111111, B11111111, B10000000,
  B11111100, B00000011, B10000000,
  B11111000, B00000001, B10000000,
  B11111100, B00000011, B10000000,
  B11111111, B11000011, B10000000,
  B11111111, B10000111, B10000000,
  B11111111, B10001111, B10000000,
  B11111111, B00001111, B10000000,
  B11111110, B00011111, B10000000,
  B11111110, B00011111, B10000000,
  B11111100, B00111111, B10000000,
  B11111100, B01111111, B10000000,
  B11111000, B00000011, B10000000,
  B11111000, B00000001, B10000000
};

  #define speakerPin 2

// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
//THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALLED Ab AND NOT LAb)
#define  TONE_C0 16.35
#define TONE_Db0 17.32
#define TONE_D0  18.35
#define TONE_Eb0 19.45
#define TONE_E0  20.60
#define TONE_F0  21.83
#define TONE_Gb0 23.12
#define TONE_G0  24.50
#define TONE_Ab0 25.96
#define TONE_LA0 27.50
#define TONE_Bb0 29.14
#define TONE_B0  30.87
#define TONE_C1  32.70
#define TONE_Db1 34.65
#define TONE_D1  36.71
#define TONE_Eb1 38.89
#define TONE_E1  41.20
#define TONE_F1  43.65
#define TONE_Gb1 46.25
#define TONE_G1  49.00
#define TONE_Ab1 51.91
#define TONE_LA1 55.00
#define TONE_Bb1 58.27
#define TONE_B1  61.74
#define TONE_C2  65.41
#define TONE_Db2 69.30
#define TONE_D2  73.42
#define TONE_Eb2 77.78
#define TONE_E2  82.41
#define TONE_F2  87.31
#define TONE_Gb2 92.50
#define TONE_G2  98.00
#define TONE_Ab2 103.83
#define TONE_LA2 110.00
#define TONE_Bb2 116.54
#define TONE_B2  123.47
#define TONE_C3  130.81
#define TONE_Db3 138.59
#define TONE_D3  146.83
#define TONE_Eb3 155.56
#define TONE_E3  164.81
#define TONE_F3  174.61
#define TONE_Gb3 185.00
#define TONE_G3  196.00
#define TONE_Ab3 207.65
#define TONE_LA3 220.00
#define TONE_Bb3 233.08
#define TONE_B3  246.94
#define TONE_C4  261.63
#define TONE_Db4 277.18
#define TONE_D4  293.66
#define TONE_Eb4 311.13
#define TONE_E4  329.63
#define TONE_F4  349.23
#define TONE_Gb4 369.99
#define TONE_G4  392.00
#define TONE_Ab4 415.30
#define TONE_LA4 440.00
#define TONE_Bb4 466.16
#define TONE_B4  493.88
#define TONE_C5  523.25
#define TONE_Db5 554.37
#define TONE_D5  587.33
#define TONE_Eb5 622.25
#define TONE_E5  659.26
#define TONE_F5  698.46
#define TONE_Gb5 739.99
#define TONE_G5  783.99
#define TONE_Ab5 830.61
#define TONE_LA5 880.00
#define TONE_Bb5 932.33
#define TONE_B5  987.77
#define TONE_C6  1046.50
#define TONE_Db6 1108.73
#define TONE_D6  1174.66
#define TONE_Eb6 1244.51
#define TONE_E6  1318.51
#define TONE_F6  1396.91
#define TONE_Gb6 1479.98
#define TONE_G6  1567.98
#define TONE_Ab6 1661.22
#define TONE_LA6 1760.00
#define TONE_Bb6 1864.66
#define TONE_B6  1975.53
#define TONE_C7  2093.00
#define TONE_Db7 2217.46
#define TONE_D7  2349.32
#define TONE_Eb7 2489.02
#define TONE_E7  2637.02
#define TONE_F7  2793.83
#define TONE_Gb7 2959.96
#define TONE_G7  3135.96
#define TONE_Ab7 3322.44
#define TONE_LA7 3520.01
#define TONE_Bb7 3729.31
#define TONE_B7  3951.07
#define TONE_C8  4186.01
#define TONE_Db8 4434.92
#define TONE_D8  4698.64
#define TONE_Eb8 4978.03
// DURATION OF THE NOTES 
#define TONE_BPM 120    //  you can change this value changing all the others
#define TONE_H 2*TONE_Q //half 2/4
#define TONE_Q 60000/TONE_BPM //quarter 1/4 
#define TONE_E TONE_Q/2   //eighth 1/8
#define TONE_S TONE_Q/4 // sixteenth 1/16
#define TONE_W 4*TONE_Q // whole 4/4

  

void setup() {
  Serial.begin(9600);
  display.begin();              // Инициализация дисплея
  display.setContrast(60);      // Устанавливаем контраст
  display.setTextColor(BLACK);  // Устанавливаем цвет текста
  display.setTextSize(1);       // Устанавливаем размер текста
  display.clearDisplay();       // Очищаем дисплей
  display.display();
  delay(1000); 

  pinMode(speakerPin,OUTPUT);  //Buzzer pin

}

void play_music(){
  //tone(pin, note, duration)
    tone(speakerPin,TONE_LA3,TONE_Q); 
    delay(1+TONE_Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(speakerPin,TONE_LA3,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_LA3,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_F3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_LA3,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_F3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_LA3,TONE_H);
    delay(1+TONE_H);
    
    tone(speakerPin,TONE_E4,TONE_Q); 
    delay(1+TONE_Q); 
    tone(speakerPin,TONE_E4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_E4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_F4,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_Ab3,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_F3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_LA3,TONE_H);
    delay(1+TONE_H);
    
    tone(speakerPin,TONE_LA4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_LA3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_LA3,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_LA4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_Ab4,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_G4,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_Gb4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_E4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_F4,TONE_E);
    delay(1+TONE_E);
    delay(1+TONE_E);//PAUTONE_SE
    tone(speakerPin,TONE_Bb3,TONE_E);
    delay(1+TONE_E);
    tone(speakerPin,TONE_Eb4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_D4,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_Db4,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_B3,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_C4,TONE_E);
    delay(1+TONE_E);
    delay(1+TONE_E);//PAUTONE_SE TONE_QUATONE_SI FINE RIGA
    tone(speakerPin,TONE_F3,TONE_E);
    delay(1+TONE_E);
    tone(speakerPin,TONE_Ab3,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_F3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_LA3,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_C4,TONE_Q);
    delay(1+TONE_Q);
     tone(speakerPin,TONE_LA3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_E4,TONE_H);
    delay(1+TONE_H);
    
     tone(speakerPin,TONE_LA4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_LA3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_LA3,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_LA4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_Ab4,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_G4,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_Gb4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_E4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_F4,TONE_E);
    delay(1+TONE_E);
    delay(1+TONE_E);//PAUTONE_SE
    tone(speakerPin,TONE_Bb3,TONE_E);
    delay(1+TONE_E);
    tone(speakerPin,TONE_Eb4,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_D4,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_Db4,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_B3,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_C4,TONE_E);
    delay(1+TONE_E);
    delay(1+TONE_E);//PAUTONE_SE TONE_QUATONE_SI FINE RIGA
    tone(speakerPin,TONE_F3,TONE_E);
    delay(1+TONE_E);
    tone(speakerPin,TONE_Ab3,TONE_Q);
    delay(1+TONE_Q);
    tone(speakerPin,TONE_F3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    
    tone(speakerPin,TONE_LA3,TONE_Q);
    delay(1+TONE_Q);
     tone(speakerPin,TONE_F3,TONE_E+TONE_S);
    delay(1+TONE_E+TONE_S);
    tone(speakerPin,TONE_C4,TONE_S);
    delay(1+TONE_S);
    tone(speakerPin,TONE_LA3,TONE_H);
    delay(1+TONE_H);
    
    delay(2*TONE_H);
}


void loop() {

  //tone(speakerPin, 1000); // Send 1KHz sound signal...
  //delay(1000);        // ...for 1 sec
  //noTone(speakerPin);     // Stop sound...
  //delay(1000);        // ...for 1sec

play_music();
  
  // Рисуем заранее подготовленное лого
  // Подготовлен массив из 16 пар байтов
  // каждый байт состоит из 8 битов, соответсвенно
  // получаем матрицу 16х16 битов, 1-черный цвет, 0-белый цвет
  display.drawBitmap(LCDWIDTH/2-8, LCDHEIGHT/2-8, logoBmp, 24, 16, BLACK); // x, y, logo, w, h, color 
  display.display();
  delay(2000);
  
    // Очищаем дисплей
  display.clearDisplay();
  display.display();
  delay(1000);
  
  // Рисуем несколько пикселей (точек)
  display.drawPixel(0, 0, BLACK);  
  display.drawPixel(1, 1, BLACK);  
  display.drawPixel(2, 2, WHITE); // Посередине белый пиксель  
  display.drawPixel(3, 3, BLACK);  
  display.drawPixel(4, 4, BLACK);  
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем диагональ
  display.drawLine(0, LCDHEIGHT-1, LCDWIDTH, 0, BLACK); // x0, y0, x1, y1, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Для рисования вертикальных и горизонтальных линий лучше использовать
  // более быстрые функции
  display.drawFastVLine(LCDWIDTH/2, 0, LCDHEIGHT, BLACK); // x, y, h, color
  display.drawFastHLine(0, LCDHEIGHT/2, LCDWIDTH, BLACK); //x, y, w, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем прямоугольник
  display.drawRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, BLACK); // x, y, w, h, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенный прямоугольник
  display.fillRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, BLACK); // x, y, w, h, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Закрашиваем весь дисплей
  display.fillScreen(BLACK);
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем окружность
  display.drawCircle(LCDWIDTH/2, LCDHEIGHT/2, LCDHEIGHT/2, BLACK); // x, y, r, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенную окружность
  display.fillCircle(LCDWIDTH/2, LCDHEIGHT/2, LCDHEIGHT/2, BLACK); // x, y, r, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем треугольник
  display.drawTriangle(LCDWIDTH/4, LCDHEIGHT/4, 3*LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, 3*LCDHEIGHT/4, BLACK); // x0, y0, x1, y1, x2, y2, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенный треугольник
  display.fillTriangle(LCDWIDTH/4, LCDHEIGHT/4, 3*LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, 3*LCDHEIGHT/4, BLACK); // x0, y0, x1, y1, x2, y2, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем прямоугольник с закругленными углами
  display.drawRoundRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, 10, BLACK); // x, y, w, h, r, color
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем закрашенный прямоугольник с закругленными углами
  display.fillRoundRect(LCDWIDTH/4, LCDHEIGHT/4, LCDWIDTH/2, LCDHEIGHT/2, 10, BLACK); // x, y, w, h, r, colordisplay.display();
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Рисуем заранее подготовленное лого
  // Подготовлен массив из 16 пар байтов
  // каждый байт состоит из 8 битов, соответсвенно
  // получаем матрицу 16х16 битов, 1-черный цвет, 0-белый цвет
  display.drawBitmap(LCDWIDTH/2-8, LCDHEIGHT/2-8, logoBmp, 24, 16, BLACK); // x, y, logo, w, h, color 
  display.display();
  delay(2000);

  display.clearDisplay();
  display.display();
  delay(1000);

  // Выведем текст
  display.print("Zelectro");
  delay(3000);

  display.clearDisplay();
  display.display();
  delay(5000);
}


