/*
 * \file HT1621-test.ino
 * \brief Simple test sketch for the HT1621 class.
 * \author Enrico Formenti
 * \date 4 february 2015
 * \version 1.0
 * \copyright BSD license, check the License page on the blog for more information. All this text must be
 *  included in any redistribution.
 *  <br><br>
 *  See macduino.blogspot.com for more details.
 */

#include "HT1621.h" // https://github.com/marc-gist/HT1621

// refere to Macduino website for pin connections and their meaning
HT1621 ht(2,3,4);  // CS RW DATA


/*  TS125 Address map 
 *  
 *  +---------------------+-------------------+
 *  |       11            |      12           |
 *  +--+--+---+---+---+---+---+---+---+---+---+
 *  |  |10| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |13 | 
 *  |8 |9 |   |   |   |   |   |   |   |   |   |
 *  +-----+---+---+---+---+---+---+---+---+---+
 *
 *  Address 0-7 is 8 segments
 *  
 *       a
 *       -
 *    f | | b
 *       -  <-g
 *    e | | c
 * h->.  -
 *       d
 *       
 *   a = 0x08
 *   b = 0x04
 *   c = 0x02
 *   d = 0x10
 *   e = 0x20
 *   f = 0x80
 *   g = 0x40
 *   h = 0x01
 *   
 *
 */

uint8_t pattern[] = {
  B10111110, // 0
  B00000110, // 1
  B01111100, // 2
  B01011110, // 3
  B11000110, // 4
  B11011010, // 5
  B11111010, // 6
  B00001110, // 7
  B11111110, // 8
  B11011110, // 9
  B01000000, // -
  B00010000, // _
  B00000000  // Space
 };

void setNum(uint8_t adr, uint8_t num, bool dot=0) {
  if (dot) {
    ht.write(adr, pattern[num] | B00000001);
  } else {
    ht.write(adr, pattern[num]);
  }
}

void setup() {
  Serial.begin(115200);
  
  ht.begin();
  
  ht.sendCommand(HT1621::RC256K);
  ht.sendCommand(HT1621::BIAS_THIRD_4_COM);
  ht.sendCommand(HT1621::SYS_EN);
  ht.sendCommand(HT1621::LCD_ON);

  // clear memory
  for(int digit=0; digit<14; digit++)
    ht.write(digit,0);

  // all digit ON
  for(int digit=0; digit<14; digit++) {
    ht.write(digit, 0xff);
    delay(100);
  }
  delay(10000);


  // all 0 to 7
  for(int num=0;num<10;num++) {
    for(int digit=0; digit<8; digit++) {
      setNum(digit,num);
   }
  delay(1000);
  }
  
  setNum(0,2);
  setNum(1,3);
  setNum(2,4);
  setNum(3,5);
  setNum(4,6);
  setNum(5,7);
  setNum(6,8);
  setNum(7,9);
  setNum(8,0);
  setNum(9,1);
  delay(5000);
  
  setNum(0,2,1);
  setNum(1,3,1);
  setNum(2,4,1);
  setNum(3,5,1);
  setNum(4,6,1);
  setNum(5,7,1);
  setNum(6,8,1);
  setNum(7,9,1);
  setNum(8,0);
  setNum(9,1);
  delay(5000);
  

}

void loop() {
}
