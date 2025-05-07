#include <Arduino.h>
#include <vector>

class SN74HC595 {
   const int srclk;
   const int ser;
   const int rclk;

public:
   SN74HC595(int srclk, int ser, int rclk) 
   : srclk(srclk), ser(ser), rclk(rclk) {      
   }

   void begin() {
    pinMode(srclk, OUTPUT);
    pinMode(ser, OUTPUT);
    pinMode(rclk, OUTPUT);
   }

   void write(uint8_t data) {
      for (int i = 0; i < 8; ++i) {
         digitalWrite(ser, (data & (1 << i)) ? HIGH : LOW);
         digitalWrite(srclk, HIGH);
         delayMicroseconds(1);
         digitalWrite(srclk, LOW);
      }
      digitalWrite(rclk, HIGH);
      delayMicroseconds(1);
      digitalWrite(rclk, LOW);
   }
};

SN74HC595 sn74hc595(13, 15, 14);

struct Frame {
  uint8_t data;
  int delay;
};

std::vector<Frame> frames = {
  Frame{0b00000001, 500},
  Frame{0b00000010, 50},
  Frame{0b00000100, 50},
  Frame{0b00001000, 50},
  Frame{0b00010000, 50},
  Frame{0b00100000, 50},
  Frame{0b01000000, 50},
  Frame{0b10000000, 500},
  Frame{0b01000000, 50},
  Frame{0b00100000, 50},
  Frame{0b00010000, 50},
  Frame{0b00001000, 50},
  Frame{0b00000100, 50},
  Frame{0b00000010, 50},

  Frame{0b10101010, 100},
  Frame{0b01010101, 100},
  Frame{0b10101010, 100},
  Frame{0b01010101, 100},
  Frame{0b10101010, 100},
  Frame{0b01010101, 100},
  
  Frame{0b11110000, 100},
  Frame{0b00000000, 100},
  Frame{0b11110000, 100},
  Frame{0b00000000, 100},
  Frame{0b00001111, 100},
  Frame{0b00000000, 100},
  Frame{0b00001111, 100},
  Frame{0b00000000, 100},

  Frame{0b11111111, 50},
  Frame{0b00000000, 300},  
  Frame{0b11111111, 50},
  Frame{0b00000000, 300},  
  Frame{0b11111111, 50},
  Frame{0b00000000, 300},  
  Frame{0b11111111, 1000},
};

void setup () { 
   sn74hc595.begin();
}

void loop() {
  for (const auto& frame : frames) {
    sn74hc595.write(frame.data);
    delay(frame.delay);
  }
}
