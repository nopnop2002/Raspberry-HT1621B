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


/*  TS206 Address map 
 *  
 *  +-+-+---+---+---+---+---+---+---+---+---+
 *  |1|2| 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 | 
 *  | 0 |   |   |   |   |   |   |   |   |   |
 *  +---+---+---+---+---+---+---+---+---+---+
 *
 *  Address 0 Character
 *   KVArh  
 *   KWh
 *  
 *  Address 1-7 is 7 segments
 *  Address 8-11 is 8 segments
 *  
 *       a
 *       -
 *    f | | b
 *       -  <-g
 *    e | | c
 * h->.  -
 *       d
 *       
 *   a = 0x10
 *   b = 0x01
 *   c = 0x04
 *   d = 0x80
 *   e = 0x40
 *   f = 0x20
 *   g = 0x02
 *   h = 0x08
 *   
 *
 */

uint8_t pattern[] = {
  B11110101, // 0
  B00000101, // 1
  B11010011, // 2
  B10010111, // 3
  B00100111, // 4
  B10110110, // 5
  B11110110, // 6
  B00010101, // 7
  B11110111, // 8
  B10110111, // 9
  B00000010, // -
  B10000000, // _
  B00000000  // Space
 };

void setNum(uint8_t adr, uint8_t num, bool dot=0) {
  if (dot) {
    ht.write(adr, pattern[num] | B00001000);
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
  for(int digit=0; digit<12; digit++)
    ht.write(digit,0);

  // all digit ON
  for(int digit=0; digit<12; digit++) {
    ht.write(digit, 0xff);
    delay(100);
  }
  delay(10000);

  // all 0 to 9
  for(int num=0;num<10;num++) {
    for(int digit=1; digit<12; digit++) {
      setNum(digit,num);
   }
  delay(1000);
  }

  setNum(3,0);
  setNum(4,1);
  setNum(5,2);
  setNum(6,3);
  setNum(7,4);
  setNum(8,5);
  setNum(9,6);
  setNum(10,7);
  setNum(11,8);
  delay(1000);
  
  setNum(3,1);
  setNum(4,2);
  setNum(5,3);
  setNum(6,4);
  setNum(7,5);
  setNum(8,6,1); // with dot
  setNum(9,7,1); // with dot
  setNum(10,8,1); // with dot
  setNum(11,9,1); // with dot
  delay(1000);
  
  setNum(3,1);
  setNum(4,2);
  setNum(5,10); // -
  setNum(6,3);
  setNum(7,4);
  setNum(8,11); // _
  setNum(9,12); // Space
  setNum(10,5);
  setNum(11,6);
  
}

void loop() {
}
