#pragma once

#include <LovyanGFX.hpp>

class LGFX_SSD1331: public lgfx::LGFX_Device {
  lgfx::Panel_SSD1331 panel;
  lgfx::Bus_SPI bus;

public:
  LGFX_SSD1331() {
    auto busConfig = bus.config();
    busConfig.spi_host = VSPI_HOST;
    busConfig.spi_mode = 0;
    busConfig.freq_write = 12000000; // 12 MHz
    busConfig.freq_read = 16000000;  // not used
    busConfig.spi_3wire = false;
    busConfig.use_lock = true;
    busConfig.dma_channel = 1;
    busConfig.pin_sclk = 18; // SCL
    busConfig.pin_mosi = 23; // SDA
    busConfig.pin_miso = -1;
    busConfig.pin_dc = 25; // DC

    bus.config(busConfig);
    panel.setBus(&bus);

    auto panelConfig = panel.config();
    panelConfig.memory_width  = 96;
    panelConfig.memory_height = 64;
    panelConfig.panel_width   = 96;
    panelConfig.panel_height  = 64;
    panelConfig.offset_x = 0;
    panelConfig.offset_y = 0;
    panelConfig.offset_rotation = 2; // this rotates the display
    panelConfig.dummy_read_pixel = 0;
    panelConfig.dummy_read_bits  = 0;
    panelConfig.readable = false;
    panelConfig.invert = false;
    panelConfig.rgb_order = true; // RGB vs BGR
    panelConfig.dlen_16bit = false;
    panelConfig.bus_shared = true;
    panelConfig.pin_cs = 15; // CS
    panelConfig.pin_rst = 13; // RES

    panel.config(panelConfig);

    setPanel(&panel);
  }
};
