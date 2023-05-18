#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10,  9,  8);

/*
const unsigned char rus_codes[66]=

{
// А  Б      В   Г    Д   Е    Ё    Ж
\x41,\xa\,\x42,\xa1,\xe0,\x45,\xa2,\xa3,
\\ З  И    Й     К    Л     М   Н    О
\xA4,\xA5,\xA6,\x4B,\xA7,\x4D,\x48,\x4F,
\\ П   Р    С    Т    У    Ф    Х    Ц   Ч
\xA8,\x5\,\x43,\x54,\xA9,\xAA,\x58,\xE1,\xAB,
\\ Ш  Щ    Ъ     Ы    Ь    Э    Ю   Я
\xAC,\xE2,\xAD,\xAE,\x62,\xAF,\xB\,\xB1,
\\а    б    в   г    д     е    ё   ж
\x61,\xB2,\xB3,\xB4,\xE3,\x65,\xB5,\xB6,
\\з    и    й    к    л   м    н    о
\xb7,\xb8,\xb9,\xba,\xbb,\xbc,\xbd,\x6f,
\\ п   р    с     т    у   ф    х    ц    ч
\xbe,\x70\,\x63,\xbf,\x79,\xe4,\x78,\xe5,\xc0,
\\ Ш   Щ    Ъ     Ы    Ь    Э    Ю   Я
\xc1,\xe6,\xc2,\xc3,\xc4,\xc5,\xc6,\xc7

} ;
*/

const char *strings[] = {
    "\xA5\x42\xa0\x4F-05-22",
    "\xAA\xb8\xbb\xb8\xbe\xbe\x6f\xB3 \x4B.",
    "\x54\x70\xc7\xba\xb8\xbd \xA5.",
    "\x42\x6f\x70\x6f\xB2\xc4\xB5\xB3 \xe0."
};

char string_lcd[] = "                    ";

byte num_str = 4; //кол-во прокручевыемых строк

void setup() {
    lcd.begin(16, 2);
}

void loop() {
    for (byte k = 0; k < num_str; k++) { //Перебор строк.
        word len_str  = 0;
        while (*strings[k]) {  // Пока не конец строки ...
            for (byte i = 0; i < 15; i++) {
                string_lcd[i] = string_lcd[i+1]; // Производим побайтовый сдвиг влево,
            }
            string_lcd[15] = *strings[k]; // отображаемой на LCD строки, и добавляем
            strings[k]++; // символ в последний байт.
            len_str++ ; // Счётчик длины строки.
            //lcd.clear() ;
            //lcd.setCursor(1,0);lcd.print("Бегущая строка") ;
            for (byte i=0 ; i < 16; i++) {  // Отображаем на LCD посимвольно.
                lcd.setCursor(i,1);
                lcd.print(string_lcd[i]);
                lcd.setCursor(0,1);
                    // lcd.print(' тест ');
            }
            delay(200);
            //blink( 13 , 190 ) ; // Задержка отображения строки и мигание светодиодом ))
        }

        for (word n = 0; n < len_str; n++) {
            strings[k]--; //Возвращаем указатель на начало строки
        }
        //Иначе строки прокрутятся тольео один раз

        for (byte n = 0; n < 16; n++) {
            for (byte i = 0; i < 15; i++) {
                string_lcd[i] = string_lcd[i+1]; //Добиваем строку пробелами
            }
            string_lcd[15] = ' ';
            //lcd.clear() ;
            //lcd.setCursor(1,0);lcd.print("Бегущая строка") ;

            float voltage = analogRead(A0) / 1024.0 * 10.0 + 0.2;
            float voltageTemp;
            if (voltage > 0.5) {
                voltageTemp = voltage;
            }
            else {
                voltageTemp = 0;
            }
            lcd.setCursor(1, 0);
            lcd.print(voltageTemp, 2);
            lcd.print(" \x42\x6f\xbb\xc4\xbf");

            for (byte i=0 ; i < 16 ; i++) {
                lcd.setCursor(i,1);
                lcd.print(string_lcd[i]);
                lcd.setCursor(0,1);
                lcd.print(' ');
            }
            delay(300);
            //blink( 13 , 190 ) ;
        }
        delay(2000);
    }
}
