#include <vector>
#include "LGFX_SSD1331.h"

struct Ball {
  int x, y;
  int vx, vy;
  int radius;
  uint32_t color;
};

LGFX_SSD1331 display;
std::vector<Ball> balls;

void setup() {
  display.init();

  randomSeed(2302);

  const auto numberOfBalls = 10;
  for (int i = 0; i < numberOfBalls; ++i) {
    int radius = std::array<int, 3>{2, 7, 20}[random(0, 3)];
    int x = random(radius, display.width() - radius);
    int y = random(radius, display.height() - radius);
    int vx = std::array<int, 2>{-1, 1}[random(0, 2)];
    int vy = std::array<int, 2>{-1, 1}[random(0, 2)];

    uint8_t r, g, b;
    do {
      r = std::array<uint8_t, 3>{0, 127, 255}[random(0, 3)];
      g = std::array<uint8_t, 3>{0, 127, 255}[random(0, 3)];
      b = std::array<uint8_t, 3>{0, 127, 255}[random(0, 3)];
    } while (r == 0 && g == 0 && b == 0);

    uint32_t color = display.color888(r, g, b);
    balls.push_back(Ball {x, y, vx, vy, radius, color});
  }
}

void loop() {
  display.fillScreen(display.color888(0, 0, 0));

  for (auto& ball : balls) {
    display.fillCircle(ball.x, ball.y, ball.radius, ball.color);
    ball.x += ball.vx;
    ball.y += ball.vy;

    if (ball.x <= ball.radius || ball.x > display.width() - ball.radius - 1) {
      ball.vx = -ball.vx;
    }
    if (ball.y <= ball.radius || ball.y > display.height() - ball.radius - 1) {
      ball.vy = -ball.vy;
    }
  }

  float t = float(millis());
  display.setTextColor(display.color888(
    127 + sin(t / 3121) * 128, 
    127 + cos(t / 2231) * 128, 
    127 + sin(t / 7432) * 128));
  display.setCursor(0, 10);
  display.printf("Uptime: %d\n", millis() / 1000);

  delay(30);
}
