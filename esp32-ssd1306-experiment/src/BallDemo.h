#pragma once

#include <Adafruit_SSD1306.h>

class BallDemo {
    Adafruit_SSD1306& display;
    std::string const name;
    int x;
    int y;
    int vx = 1;
    int vy = 1;
    int r = 10;
  
  public:
    BallDemo(Adafruit_SSD1306& display, std::string const& name) 
    : display(display), name(name) {

        x = display.width() / 2;
        y = display.height() / 2;
    }
  
    void update() {    
      if (x < r) {
        x = r;
        vx = -vx;
      }
      if (x > display.width() - r - 1) {
        x = display.width() - r - 1;
        vx = -vx;
      }
      if (y < r) {
        y = r;
        vy = -vy;
      }
      if (y > display.height() - r - 1) {
        y = display.height() - r - 1;
        vy = -vy;
      }

      display.clearDisplay();

      display.setTextSize(1);
      display.setCursor(0, 0);
      display.setTextColor(WHITE);
      display.printf("*** Hello, world! ***\n%s\nUptime: %d\n", name.c_str(), millis() / 1000);
      
      display.fillCircle(x, y, 10, WHITE);
      display.fillCircle(x - 5, y - 4, 2, BLACK);
      display.fillCircle(x + 5, y - 4, 2, BLACK);
      display.fillRect(x - 5, y + 4, 10, 4, BLACK);

      display.display();
  
      x += vx;
      y += vy;
    }
  };
