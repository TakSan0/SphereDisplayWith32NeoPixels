#ifndef HARDWARE_CFG_H
#define HARDWARE_CFG_H

#define NEOPIXEL_WS2812B 1
#define NEOPIXEL_WS2812C 2

#define ARDUINO_CH32V00x_EVT
#define NEOPIXEL_TYPE  NEOPIXEL_WS2812B


#if ( NEOPIXEL_TYPE == NEOPIXEL_WS2812B )
  #define NEOPIXEL_TYPE_FASTLED 
//  #define NEOPIXEL_TYPE_NEOPIXEL 
  #define COLOR_ORDER_FASTLED GRB
  #define COLOR_ORDER_NEOPIXEL NEO_GRB
#elif ( NEOPIXEL_TYPE == NEOPIXEL_WS2812C )
  #define NEOPIXEL_TYPE_FASTLED 
  #define NEOPIXEL_TYPE_NEOPIXEL 
//  #define COLOR_ORDER_FASTLED GRBW
  #define COLOR_ORDER_NEOPIXEL NEO_GRBW
#else
  #error "NeoPixel type not defined!"
#endif




// -<[{ Board Support Features }]>-
#if defined(ARDUINO_M5Stack_Core_ESP32)
  #define NEOPIXEL_1_PIN 21 // Grove Connector 2pin(Inner)
  #define NEOPIXEL_2_PIN 22 // Grove Connector 1pin(Outter)
  #define NEOPIXEL_PIN NEOPIXEL_1_PIN //Inner Selected

  #define BOARD_M5_SERIES

  #define HAS_DEBUG_LCD
  #define USE_M5QVGA_LCD

  #define USE_FAST_LED  // for ESP32, M5Stack Core2/Atom


#elif defined(ARDUINO_M5STACK_Core2)
  #define NEOPIXEL_1_PIN 21 // Grove Connector 2pin(Inner)
  #define NEOPIXEL_2_PIN 22 // Grove Connector 1pin(Outter)
  #define NEOPIXEL_PIN NEOPIXEL_1_PIN //Inner Selected

  #define BOARD_M5_SERIES

  #define HAS_DEBUG_LCD
  #define USE_M5QVGA_LCD

  #define USE_FAST_LED  // for ESP32, M5Stack Core2/Atom

#elif defined(ARDUINO_M5Stack_ATOM)
  #define NEOPIXEL_1_PIN 26 // Grove Connector 2pin(Inner)
  #define NEOPIXEL_2_PIN 32 // Grove Connector 1pin(Outter)
  #define NEOPIXEL_PIN NEOPIXEL_1_PIN //Inner Selected

  #define BOARD_M5_SERIES

  #define USE_FAST_LED  // for ESP32, M5Stack Core2/Atom

#elif defined(ARDUINO_CH32V00x_EVT)
  #define NEOPIXEL_PIN        PD6 // On Trinket or Gemma, suggest changing this to 1

  #define USE_ADAFRUIT_NEOPIXEL

#endif // defined(ARDUINO_CH32V00x_EVT)



// -<[{ Display Settings }]>-
#if defined(HAS_DEBUG_LCD)

#if defined(USE_M5QVGA_LCD)
#define SCREEN_WIDTH                    LCD_PIXEL_WIDTH     // (320u)
#define SCREEN_HEIGHT                   LCD_PIXEL_HEIGHT    // (240u)
#define M5_FONT_WIDTH                   4
#define M5_FONT_HEIGHT                  8
#define FONT_WIDTH                      M5_FONT_WIDTH
#define FONT_HEIGHT                     M5_FONT_HEIGHT
#define TOP_FIXED_HEIGHT                168                 //上部の固定エリア高さ
#define BOTTOM_FIXED_HEIGHT             (FONT_HEIGHT*4)     //下部の固定エリア高さ
#define M5_POLYGON_Y_OFFSET 32

#define FUNC_BUTTON_POS_Y               (SCREEN_HEIGHT - 20)
#define FUNC_BUTTON_AREA_WIDTH          (SCREEN_WIDTH)
#else
#error "Unknown LCD"

#endif // defined(USE_M5QVGA_LCD)
#endif // defined(HAS_DEBUG_LCD)

#endif // HARDWARE_CFG_H
