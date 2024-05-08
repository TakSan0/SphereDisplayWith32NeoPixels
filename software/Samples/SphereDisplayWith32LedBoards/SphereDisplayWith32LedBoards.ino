// -----=====<<<<<[[[[[ Include ]]]]]>>>>>=====-----
#include <Arduino.h>
#include "Hardware_cfg.h"
#include "App_cfg.h"
#if defined(BOARD_M5_SERIES)
#include <M5Unified.h>
#endif // defined(BOARD_M5_SERIES)
#if defined(USE_FAST_LED)
#include <FastLED.h>
#elif defined(USE_ADAFRUIT_NEOPIXEL)
#include "Adafruit_NeoPixel.h"
#else
#error "Neopixele Library Not Selected! Check the board setting in the hardware config file."
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)


// -----=====<<<<<[[[[[ Define ]]]]]>>>>>=====-----

#define ARRAY_SIZEOF(x) (sizeof(x)/sizeof(x[0]))


//@ 応急エラー対策
#define ERR_LOG(x)
#define getLocalTime(t) false

#if defined(USE_FAST_LED)
#define NeoPixelWrapper_RGB CRGB
#elif defined(USE_ADAFRUIT_NEOPIXEL)
#define NeoPixelWrapper_RGB neopixel.Color
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)

#if (NUM_OF_NEOPIXELS == 180)
 #define THIS_BLOCK_IS_180LEDs_ONLY
#elif (NUM_OF_NEOPIXELS == 32)
 #define THIS_BLOCK_IS_32LEDs_ONLY
#else
#error "Invalid Num Of LEDs (Neopixels)"
#endif

#if defined(THIS_BLOCK_IS_180LEDs_ONLY)
#elif defined(THIS_BLOCK_IS_32LEDs_ONLY)
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY) || defined(THIS_BLOCK_IS_32LEDs_ONLY)


// -----=====<<<<<[[[[[ Types ]]]]]>>>>>=====-----

#if defined(USE_FAST_LED)
typedef CRGB NeoPixelWrapper_Color;
#elif defined(USE_ADAFRUIT_NEOPIXEL)
typedef uint32_t NeoPixelWrapper_Color;
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)


// -----=====<<<<<[[[[[ Valiable ]]]]]>>>>>=====-----

#if defined(USE_FAST_LED)
NeoPixelWrapper_Color led_ram[NUM_OF_NEOPIXELS+1];
#elif defined(USE_ADAFRUIT_NEOPIXEL)
Adafruit_NeoPixel neopixel(NUM_OF_NEOPIXELS, NEOPIXEL_PIN, COLOR_ORDER_NEOPIXEL + NEO_KHZ800);
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)

bool TimeAvailable = false;


// -----=====<<<<<[[[[[ Prototype ]]]]]>>>>>=====-----
void setup();
void loop();
bool waitForSignalOrDelay(uint32_t time_to_wait);

void NeoPixelWrapper_initialize(void);
void NeoPixelWrapper_show(void);
void NeoPixelWrapper_setBrightness(int percent);
int NeoPixelWrapper_numPixels(void);
void NeoPixelWrapper_setPixelColor(int pos, NeoPixelWrapper_Color col);

#if defined(HAS_DEBUG_LCD)
void DebugDispWrapper_initialize(void);
void DebugDispWrapper_drawBase(void);
void DebugDispWrapper_drawLedPixelOnLCDScreen(NeoPixelWrapper_Color c, uint8_t index);
#else // defined(HAS_DEBUG_LCD)
#define DrawLedPixelOnLCDScreen(c, index)
#endif // defined(HAS_DEBUG_LCD)

uint8_t logicPosToRealPos(uint8_t pos);
uint8_t realPosToLogicPos(uint8_t pos);

NeoPixelWrapper_Color convHueToRgb(int hue);

void colorSet(NeoPixelWrapper_Color c, uint8_t index, bool skip_show = false);
void colorSetRange(NeoPixelWrapper_Color c, uint8_t from, uint8_t to, bool skip_show = false);
void colorSetArray(NeoPixelWrapper_Color c, uint8_t arr[], uint8_t count, bool skip_show = false);
void colorSetNumToClockDigit(NeoPixelWrapper_Color c, int digit, int num);
void colorWipeWithDelay(NeoPixelWrapper_Color c, uint8_t wait);

void RGBW_Simple(void);
void RGBW_FadeInOut(void);
void RGBW_SwipeFadeInOut(void);
void RGBW_Dots();
void RandomColor();

void HueScroll();
void RainbowScroll(void);
void RedAndWhite();
void PatrolLight();

#if defined(THIS_BLOCK_IS_180LEDs_ONLY)
void ColorCircles();
void SoccerBall();

void DrawClock();
void DrawBingoDemo();

void DrawEarth();
void FireWork();
void DrawFace();
void DrawHalloweenPumpkin();
void DrawStar();
void DrawHeart();
void DrawJanken();

void DrawStringA();
void DrawStringB();
void DrawStringC();
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY)

void DotRun();
void CheckLEDOrder();

#if defined(THIS_BLOCK_IS_180LEDs_ONLY)
void DrawStringA();
void DrawStringB();
void DrawStringC();
bool IsValidCode(char code);
void DrawFont(char code, NeoPixelWrapper_Color col, NeoPixelWrapper_Color back);
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY)


// -----=====<<<<<[[[[[ Tables ]]]]]>>>>>=====-----
#if defined(THIS_BLOCK_IS_180LEDs_ONLY)
const uint8_t led_position_table[] = {
    0,   1,   2,   3,   4,
    8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,   5,   6,   7,
   26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  20,  21,  22,  23,  24,  25,
   53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  45,  46,  47,  48,  49,  50,  51,  52,
   84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104,  75,  76,  77,  78,  79,  80,  81,  82,  83,
  115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
  150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 159, 158, 157, 156, 155, 154, 153, 152, 151,
  169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 174, 173, 172, 171, 170, 
  178, 177, 176, 175, 179
};

const struct {
  uint8_t from;
  uint8_t to;
} led_line_range_table[] {
  {   0,   4},  // 0:5
  {   5,  19},  // 1:15
  {  20,  44},  // 2:25
  {  45,  74},  // 3:30
  {  75, 104},  // 4:30
  { 105, 134},  // 5:30
  { 135, 159},  // 6:25
  { 160, 174},  // 7:15
  { 175, 179}   // 8:5
};

#elif defined(THIS_BLOCK_IS_32LEDs_ONLY)
const uint8_t led_position_table[] = {
    0,
    1,   5,   4,   3,   2,
    7,   6,  15,  14,  13,  12,  11,  10,   9,   8,
   17,  16,  25,  24,  23,  22,  21,  20,  19,  18,
   26,  30,  29,  28,  27,
   31
};

const struct {
  uint8_t from;
  uint8_t to;
} led_line_range_table[] {
  {   0,   0},  // 0:1
  {   1,   5},  // 1:5
  {   6,  15},  // 2:10
  {  16,  25},  // 3:10
  {  26,  30},  // 4:5
  {  31,  31}   // 5:1
};
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY) || defined(THIS_BLOCK_IS_32LEDs_ONLY)

const NeoPixelWrapper_Color rgbwTable[] = {
  NeoPixelWrapper_RGB(0xFF, 0x00, 0x00),
  NeoPixelWrapper_RGB(0x00, 0xFF, 0x00),
  NeoPixelWrapper_RGB(0x00, 0x00, 0xFF),
  NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF)
};

const NeoPixelWrapper_Color rainbowTable[] = {
  NeoPixelWrapper_RGB(0xFF, 0x00, 0x00),
  NeoPixelWrapper_RGB(0xFF, 0x96, 0x00),
  NeoPixelWrapper_RGB(0xFF, 0xF0, 0x00),
  NeoPixelWrapper_RGB(0x00, 0x87, 0x00),
  NeoPixelWrapper_RGB(0x00, 0x91, 0xFF),
  NeoPixelWrapper_RGB(0x00, 0x64, 0xBE),
  NeoPixelWrapper_RGB(0x91, 0x00, 0x82)
};


#if defined(THIS_BLOCK_IS_180LEDs_ONLY)

#include "DrawData.h"
#include "FontData.h"

#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY)


// -----=====<<<<<[[[[[ Functions ]]]]]>>>>>=====-----
void setup()
{
#if defined(BOARD_M5_SERIES)
  // Start M5 Stack
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  cfg.output_power = true;
  M5.begin(cfg);
#endif // defined(BOARD_M5_SERIES)

  randomSeed(analogRead(0));

  NeoPixelWrapper_initialize();
  NeoPixelWrapper_setBrightness(BRIGHTNESS);

#if defined(HAS_DEBUG_LCD)
  DebugDispWrapper_initialize();
  DebugDispWrapper_drawBase();
#endif // defined(HAS_DEBUG_LCD)

}

void loop()
{
#if 0
  PatrolLight();
#else
  RGBW_Simple();
  RGBW_FadeInOut();
  RGBW_SwipeFadeInOut();
  RGBW_Dots();
  RandomColor();
  HueScroll();
  RainbowScroll();
#if defined(THIS_BLOCK_IS_180LEDs_ONLY)
  ColorCircles();
  SoccerBall();
  DrawEarth();
  FireWork();
  DrawFace();
  DrawJanken();
  DrawBingoDemo();
  DrawStringA();
  DrawStringB();
  DrawStringC();
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY)
  RedAndWhite();
  PatrolLight();
  //DotRun();
  //CheckLEDOrder();
#endif
}
bool waitForSignalOrDelay(uint32_t time_to_wait)
{
#if 0
  static message_queue_data_t msg;

  if ( pdTRUE == xQueueReceive(taskMessageQueue, &msg, time_to_wait) ) {
    executeCommand(msg.command_str);
    return (true);
    //DBG_LOG("Recieved:%s", msg.command_str);
  }
#else
  delay(time_to_wait);
#endif

//@s  if (NextFunc != NEXT_FUNC_NOT_SPECIFIED) return (true);

  return (false);
}


// ========================================
//             NeoPixelドライバラッパ関数関連
// ========================================
void NeoPixelWrapper_initialize(void)
{
#if defined(USE_FAST_LED)
  FastLED.addLeds<WS2812B, NEOPIXEL_PIN, COLOR_ORDER>(led_ram, NUM_OF_NEOPIXELS);
#elif defined(USE_ADAFRUIT_NEOPIXEL)
  neopixel.begin();
  neopixel.show();
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)

}
void NeoPixelWrapper_show(void)
{
#if defined(USE_FAST_LED)
  FastLED.show();
#elif defined(USE_ADAFRUIT_NEOPIXEL)
  neopixel.show();
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)

}
void NeoPixelWrapper_setBrightness(int percent)
{
#if defined(USE_FAST_LED)
  FastLED.setBrightness(percent);
#elif defined(USE_ADAFRUIT_NEOPIXEL)
  neopixel.setBrightness(percent);
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)
}
int NeoPixelWrapper_numPixels(void)
{
#if defined(USE_FAST_LED)
  return(NUM_OF_NEOPIXELS)
#elif defined(USE_ADAFRUIT_NEOPIXEL)
  return(neopixel.numPixels());
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)
}
void NeoPixelWrapper_setPixelColor(int pos, NeoPixelWrapper_Color col)
{
#if defined(USE_FAST_LED)
  // replace   leds[ \t]*\[[ \t]*(.*)[ \t]*\][ \t]*=[ \t]*(.*)[ \t]*;	NeoPixelWrapper_setPixelColor(\1, \2);
  led_ram[pos] = col;
#elif defined(USE_ADAFRUIT_NEOPIXEL)
  neopixel.setPixelColor(pos, col);
#endif // defined(USE_FAST_LED) || defined(USE_ADAFRUIT_NEOPIXEL)
}

// ========================================
//               単色表示系
// ========================================
#if defined(HAS_DEBUG_LCD)
void DebugDispWrapper_initialize(void)
{
}

void DebugDispWrapper_drawBase(void)
{
#if defined(HAS_LCD_SCREEN)
  uint16_t x_center, y_center;
  uint16_t x_before, y_before;
  uint16_t color;
  uint16_t shape;
  uint8_t count_in_shape = 0;
  int index = 0;

  M5.Lcd.fillRect(0, 0, 320, TOP_FIXED_HEIGHT, TFT_DARKGRAY);

  for (int i = 0; i < ARRAY_SIZEOF(polygon_axis_table); i++) {
    if ( PENTAGON == polygon_axis_table[i].pos ) {
      shape = PENTAGON;
      color = TFT_YELLOW;
      x_center = polygon_axis_table[i].x;
      y_center = polygon_axis_table[i].y;
      count_in_shape = 0;
    }
    else if ( HEXAGON == polygon_axis_table[i].pos ) {
      shape = HEXAGON;
      color = TFT_RED;
      x_center = polygon_axis_table[i].x;
      y_center = polygon_axis_table[i].y;
      count_in_shape = 0;
    }
    else {
      if (0 == count_in_shape) {
        if (PENTAGON == shape) {
          M5.Lcd.drawLine(x_center, y_center + M5_POLYGON_Y_OFFSET, polygon_axis_table[i + (5-1)].x, polygon_axis_table[i + (5-1)].y + M5_POLYGON_Y_OFFSET, color);
          M5.Lcd.drawLine(polygon_axis_table[i + (5-1)].x, polygon_axis_table[i + (5-1)].y + M5_POLYGON_Y_OFFSET, polygon_axis_table[i].x, polygon_axis_table[i].y + M5_POLYGON_Y_OFFSET, TFT_NAVY);
          M5DrawPos[polygon_axis_table[i].pos].x = (x_center + polygon_axis_table[i].x + polygon_axis_table[i + (5-1)].x) / 3;
          M5DrawPos[polygon_axis_table[i].pos].y = (y_center + polygon_axis_table[i].y + polygon_axis_table[i + (5-1)].y) / 3;
        }
        else if ( HEXAGON == shape ) {
          M5.Lcd.drawLine(x_center, y_center + M5_POLYGON_Y_OFFSET, polygon_axis_table[i + (6-1)].x, polygon_axis_table[i + (6-1)].y + M5_POLYGON_Y_OFFSET, color);
          M5.Lcd.drawLine(polygon_axis_table[i + (6-1)].x, polygon_axis_table[i + (6-1)].y + M5_POLYGON_Y_OFFSET, polygon_axis_table[i].x, polygon_axis_table[i].y + M5_POLYGON_Y_OFFSET, TFT_NAVY);
          M5DrawPos[polygon_axis_table[i].pos].x = (x_center + polygon_axis_table[i].x + polygon_axis_table[i + (6-1)].x) / 3;
          M5DrawPos[polygon_axis_table[i].pos].y = (y_center + polygon_axis_table[i].y + polygon_axis_table[i + (6-1)].y) / 3;
        }
      }
      else {
          M5.Lcd.drawLine(x_center, y_center + M5_POLYGON_Y_OFFSET, x_before, y_before + M5_POLYGON_Y_OFFSET, color);
          M5.Lcd.drawLine(x_before, y_before + M5_POLYGON_Y_OFFSET, polygon_axis_table[i].x, polygon_axis_table[i].y + M5_POLYGON_Y_OFFSET, TFT_NAVY);
          M5DrawPos[polygon_axis_table[i].pos].x = (x_center + x_before + polygon_axis_table[i].x) / 3;
          M5DrawPos[polygon_axis_table[i].pos].y = (y_center + y_before + polygon_axis_table[i].y) / 3;
      }
      count_in_shape++;
    }
    x_before = polygon_axis_table[i].x;
    y_before = polygon_axis_table[i].y;
  }
  M5.Lcd.setTextColor(TFT_GREEN, TFT_DARKGRAY);
  M5.Lcd.drawString("DEMO   ", 0, 156, 4);
  M5.Lcd.setTextColor(TFT_WHITE);

#endif // defined(HAS_LCD_SCREEN)
}
void DebugDispWrapper_drawLedPixelOnLCDScreen(NeoPixelWrapper_Color c, uint8_t index)){
{
#if defined(HAS_LCD_SCREEN)
  //DBG_LOG("M5Set[%d]@%d,%d=%02x,%02x,%02x", index, M5DrawPos[index].x, M5DrawPos[index].y, c.r, c.g, c.b);
  M5.Lcd.fillEllipse(M5DrawPos[index].x - 1, M5DrawPos[index].y + M5_POLYGON_Y_OFFSET - 1, 3, 3, M5.Lcd.color565(c.r, c.g, c.b));
#endif // defined(HAS_LCD_SCREEN)
}
#endif // defined(HAS_DEBUG_LCD)

// ========================================
//             LED位置管理関連
// ========================================
uint8_t logicPosToRealPos(uint8_t pos)
{
  uint8_t ret_pos;

  if (pos < ARRAY_SIZEOF(led_position_table) ) {
    ret_pos = led_position_table[pos];
  }
  else {
    ret_pos = NUM_OF_NEOPIXELS;
  }
  return ret_pos;
}

uint8_t realPosToLogicPos(uint8_t pos)
{
  uint8_t ret_pos;

  ret_pos = NUM_OF_NEOPIXELS;
  for (int i = 0; i < ARRAY_SIZEOF(led_position_table) ; i++) {
    if ( led_position_table[i] == pos ) {
      ret_pos = i;
      break;
    }
  }
  return ret_pos;
}

NeoPixelWrapper_Color convHueToRgb(int hue)
{
  NeoPixelWrapper_Color result;
  int sector, remainder;
  int p, q, t;
  int r, g, b;

  // 色相を0～359の範囲に収める
  hue %= 360;
  if (hue < 0) {
    hue += 360;
  }

  // 色相を6つのセクターに分ける
  sector = hue / 60;
  remainder = hue % 60;

  // 各セクターごとの計算
  p = 0;
  q = ((60 - remainder) * 256) / 60;
  t = (remainder * 256) / 60;

  switch (sector) {
    case 0:
      r = 255;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = 255;
      b = p;
      break;
    case 2:
      r = p;
      g = 255;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = 255;
      break;
    case 4:
      r = t;
      g = p;
      b = 255;
      break;
    case 5:
      r = 255;
      g = p;
      b = q;
      break;
    default:
      r = 0;
      g = 0;
      b = 0;
      break;
  }
  result = NeoPixelWrapper_RGB(r,g,b);

  return result;
}

// ========================================
//               LED設定関連
// ========================================
void colorSet(NeoPixelWrapper_Color c, uint8_t index, bool skip_show)
{
  NeoPixelWrapper_setPixelColor(logicPosToRealPos(index), c);
  DrawLedPixelOnLCDScreen(c, index);

  if (false == skip_show) NeoPixelWrapper_show();
}

void colorSetRange(NeoPixelWrapper_Color c, uint8_t from, uint8_t to, bool skip_show)
{
  for(uint8_t i = from; i <= to; i++) {
    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), c);
    DrawLedPixelOnLCDScreen(c, i);
  }
  if (false == skip_show) NeoPixelWrapper_show();
}

void colorSetArray(NeoPixelWrapper_Color c, uint8_t arr[], uint8_t count, bool skip_show)
{
  for(uint8_t i = 0; i < count; i++) {
    NeoPixelWrapper_setPixelColor(logicPosToRealPos(arr[i]), c);
    DrawLedPixelOnLCDScreen(c, arr[i]);
  }
  if (false == skip_show) NeoPixelWrapper_show();
}

void colorWipeWithDelay(NeoPixelWrapper_Color c, uint8_t wait)
{
  for(uint16_t i=0; i<NUM_OF_NEOPIXELS; i++) {
    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), c);
    DrawLedPixelOnLCDScreen(c, i);
    NeoPixelWrapper_show();
    delay(wait);
  }
}

// ========================================
//               単色表示系
// ========================================
void RGBW_Simple(void)
{
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for (int i = 0; i<4; i++) {
    colorWipeWithDelay(NeoPixelWrapper_RGB(255, 0, 0), 1); // Red
    if (true == waitForSignalOrDelay(50)) return;
    colorWipeWithDelay(NeoPixelWrapper_RGB(0, 0, 0), 1); // Clear
    if (true == waitForSignalOrDelay(50)) return;
    colorWipeWithDelay(NeoPixelWrapper_RGB(0, 255, 0), 1); // Green
    if (true == waitForSignalOrDelay(50)) return;
    colorWipeWithDelay(NeoPixelWrapper_RGB(0, 0, 0), 1); // Clear
    if (true == waitForSignalOrDelay(50)) return;
    colorWipeWithDelay(NeoPixelWrapper_RGB(0, 0, 255), 1); // Blue
    if (true == waitForSignalOrDelay(50)) return;
    colorWipeWithDelay(NeoPixelWrapper_RGB(0, 0, 0), 1); // Clear
    if (true == waitForSignalOrDelay(50)) return;
    colorWipeWithDelay(NeoPixelWrapper_RGB(255, 255, 255), 1); // White
    if (true == waitForSignalOrDelay(50)) return;
    colorWipeWithDelay(NeoPixelWrapper_RGB(0, 0, 0), 1); // Clear
    if (true == waitForSignalOrDelay(50)) return;
  }
}

void RGBW_FadeInOut(void)
{
  NeoPixelWrapper_Color col;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for (int i = 0; i<4; i++) {
    for (int step = 0; step < 4; step++) {
      for (int bright = 0; bright < 512; bright++) {
        int val = (bright < 256)? bright: 512 - bright - 1;
        switch(step) {
          case 0:
            col = NeoPixelWrapper_RGB( val, 0, 0 ); break;
          case 1:
            col = NeoPixelWrapper_RGB( 0, val, 0 ); break;
          case 2:
            col = NeoPixelWrapper_RGB( 0, 0, val ); break;
          case 3:
            col = NeoPixelWrapper_RGB( val, val, val ); break;
          default:
            col = NeoPixelWrapper_RGB( 0, 0, 0 ); break;
        }
        colorSetRange(col,  0, (NUM_OF_NEOPIXELS-1));
        if (true == waitForSignalOrDelay(2)) return;
      }
    }
  }
}

void RGBW_SwipeFadeInOut(void)
{
  const struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  } rgb_mask[] = { {0xFF, 0x00, 0x00}, {0x00, 0xFF, 0x00}, {0x00, 0x00, 0xFF}, {0xFF, 0xFF, 0xFF} };
#if defined(THIS_BLOCK_IS_180LEDs_ONLY)
  const uint8_t gradationTable[] = {0x00, 0x1F, 0x3F, 0x5F, 0x7F, 0x9F, 0xBF, 0xDF, 0xFF};
  const int8_t wait_time = 20;
#elif defined(THIS_BLOCK_IS_32LEDs_ONLY)
  const uint8_t gradationTable[] = {0x00, 0x2B, 0x55, 0x80, 0xAA, 0xD5, 0xFF};
  const int8_t wait_time = 40;
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY) || defined(THIS_BLOCK_IS_32LEDs_ONLY)
  const int step_count = (ARRAY_SIZEOF(led_line_range_table)-1) * 4;
  int gradation_index = 0;
  NeoPixelWrapper_Color col;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for (int i = 0; i<4; i++) {
    for (int step = 0; step < step_count; step++) {
      for (int line_index = 0; line_index < ARRAY_SIZEOF(led_line_range_table); line_index++) {
        if (step < ((step_count / 2) + 1)) gradation_index = line_index + step - (ARRAY_SIZEOF(led_line_range_table)-1);
        else gradation_index = step_count - line_index - step;
        if (gradation_index < 0) gradation_index = 0;
        if (gradation_index > (ARRAY_SIZEOF(led_line_range_table)-1)) gradation_index = (ARRAY_SIZEOF(led_line_range_table)-1);
        col = NeoPixelWrapper_RGB( gradationTable[gradation_index] & rgb_mask[i].r, gradationTable[gradation_index] & rgb_mask[i].g, gradationTable[gradation_index] & rgb_mask[i].b);
        colorSetRange(col, led_line_range_table[line_index].from, led_line_range_table[line_index].to);
      }
      if (true == waitForSignalOrDelay(wait_time)) return;
    }
  }
}

void RGBW_Dots()
{
#if (NUM_OF_NEOPIXELS == 32)
  const uint8_t PosGroups[4][8] = {
    { 0, 6, 9, 11, 13, 20, 22, 30 },
    { 1, 4, 8, 10, 14, 16, 27, 29 },
    { 2, 5, 17, 19, 23, 25, 26, 28 },
    { 3, 7, 12, 15, 18, 21, 24, 31 }
  };
  NeoPixelWrapper_Color col;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for(int n = 0; n<10; n++) {//@@
    for (int step = 0; step < ARRAY_SIZEOF(rgbwTable); step++) {
      for (int i = 0; i<4; i++) {
        col = rgbwTable[(step + i) % ARRAY_SIZEOF(rgbwTable)];
        for (int j = 0; j<8; j++) {
          NeoPixelWrapper_setPixelColor(logicPosToRealPos(PosGroups[i][j]), col);
        }
      }
      NeoPixelWrapper_show();
      if (true == waitForSignalOrDelay(100)) return;
    }
  }
#else
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for(int n = 0; n<3; n++) //@@
    for (int j = 0; j < 3; j++) {
      for (int step = 0; step < ARRAY_SIZEOF(rgbwTable); step++) {
        for (int i = 0; i<NUM_OF_NEOPIXELS; i++) {
          NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), rgbwTable[((i + step) % ARRAY_SIZEOF(rgbwTable))]);
          DrawLedPixelOnLCDScreen(rgbwTable[((i + step) % ARRAY_SIZEOF(rgbwTable))], i);
        }
        NeoPixelWrapper_show();
        if (true == waitForSignalOrDelay(100)) return;
      }
    }
  }
#endif
}
// ========================================
//             カラフル表示系
// ========================================
void RandomColor()
{
  NeoPixelWrapper_Color col;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for (int i = 0; i<50; i++) {
    for (int index = 0; index< NUM_OF_NEOPIXELS; index++) {
      col = NeoPixelWrapper_RGB(random(0,255), random(0,255), random(0,255));
      NeoPixelWrapper_setPixelColor(logicPosToRealPos(index), col);
    }
    NeoPixelWrapper_show();
    if (true == waitForSignalOrDelay(100)) return;
  }
}

void HueScroll()
{
  int index;
  int width;
  int hue;
  NeoPixelWrapper_Color col;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

for(int n = 0; n<3; n++) //@@
  for (int base = 0; base<360; base+=10) {
    for (index = 0; index < ARRAY_SIZEOF(led_line_range_table); index++ ) {
      width = led_line_range_table[index].to - led_line_range_table[index].from + 1;
      for (int i = 0; i<width; i++) {
        hue = ( 360 * i / width ) + base;
        col = convHueToRgb(hue);
        NeoPixelWrapper_setPixelColor(logicPosToRealPos(i + led_line_range_table[index].from), col);
        DrawLedPixelOnLCDScreen(col, i + led_line_range_table[index].from);
      }
    }
    NeoPixelWrapper_show();
    if (true == waitForSignalOrDelay(50)) return;
  }
}

void RainbowScroll(void)
{
  uint8_t index;
  NeoPixelWrapper_Color col;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for(int n = 0; n<3; n++) {//@@
    for (int i=0; i<5; i++) {
      for (int step = 0; step < ARRAY_SIZEOF(rainbowTable); step++) {
        for (index = 0; index < ARRAY_SIZEOF(led_line_range_table); index++) {
          if (index == 0) col = rainbowTable[(0 + step) % ARRAY_SIZEOF(rainbowTable)];
          else if (index < (ARRAY_SIZEOF(led_line_range_table)-1)) col = rainbowTable[(index - 1 + step) % ARRAY_SIZEOF(rainbowTable)];
          else col = rainbowTable[( ( ARRAY_SIZEOF(rainbowTable) - 1 ) + step) % ARRAY_SIZEOF(rainbowTable)];
          colorSetRange(col, led_line_range_table[index].from, led_line_range_table[index].to);
        }
        if (true == waitForSignalOrDelay(50)) return;
      }
    }
  }
}

void RedAndWhite()
{
  int index;
  int width;
  int deg;
  NeoPixelWrapper_Color col;
  const NeoPixelWrapper_Color white_col = NeoPixelWrapper_RGB(255, 255, 255);
  const NeoPixelWrapper_Color red_col = NeoPixelWrapper_RGB(255, 0, 0);

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for(int n = 0; n<5; n++) {//@@
    for (int base = 0; base<360; base+=10) {
      for (index = 0; index < ARRAY_SIZEOF(led_line_range_table); index++ ) {
        width = led_line_range_table[index].to - led_line_range_table[index].from + 1;
        for (int i = 0; i<width; i++) {
          deg = ( 360 * i / width ) + base;
          col = ((deg / 60 ) & 1)? white_col: red_col;
          NeoPixelWrapper_setPixelColor(logicPosToRealPos(i + led_line_range_table[index].from), col);
          DrawLedPixelOnLCDScreen(col, i + led_line_range_table[index].from);
        }
      }
      NeoPixelWrapper_show();
      if (true == waitForSignalOrDelay(50)) return;
    }
  }
}

void PatrolLight()
{
  int index;
  int width;
  int deg;
  NeoPixelWrapper_Color col;
  const NeoPixelWrapper_Color black_col = NeoPixelWrapper_RGB(0, 0, 0);

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );

  for(int n = 0; n<3; n++) {//@@
    for (int step = 0; step < ARRAY_SIZEOF(rgbwTable); step++) {
      for (int c = 0; c< 10; c++) {
        for (int base = 0; base<360; base+=10) {
          for (index = 0; index < ARRAY_SIZEOF(led_line_range_table); index++ ) {
            width = led_line_range_table[index].to - led_line_range_table[index].from + 1;
            for (int i = 0; i<width; i++) {
              deg = ( 360 * i / width ) + base;
              col = ((deg / 180 ) & 1)? rgbwTable[step]: black_col;
              NeoPixelWrapper_setPixelColor(logicPosToRealPos(i + led_line_range_table[index].from), col);
              DrawLedPixelOnLCDScreen(col, i + led_line_range_table[index].from);
            }
          }
          NeoPixelWrapper_show();
          if (true == waitForSignalOrDelay(5)) return;
        }
      }
    }
  }
}

#if defined(THIS_BLOCK_IS_180LEDs_ONLY)

void ColorCircles()
{
  const struct {
    uint8_t* ptr;
    uint8_t size;
  } circleTable[] = {
    { (uint8_t*)pentagons[0], sizeof(pentagons[0]) },

    { (uint8_t*)hexagons[0], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[1], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[2], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[3], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[4], sizeof(hexagons[0]) },

    { (uint8_t*)hexagons[5], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[1], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[6], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[2], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[7], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[3], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[8], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[4], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[9], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[5], sizeof(pentagons[0]) },

    { (uint8_t*)pentagons[6], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[10], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[7], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[11], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[8], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[12], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[9], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[13], sizeof(hexagons[0]) },
    { (uint8_t*)pentagons[10], sizeof(pentagons[0]) },
    { (uint8_t*)hexagons[14], sizeof(hexagons[0]) },

    { (uint8_t*)hexagons[15], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[16], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[17], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[18], sizeof(hexagons[0]) },
    { (uint8_t*)hexagons[19], sizeof(hexagons[0]) },

    { (uint8_t*)pentagons[11], sizeof(pentagons[0]) },
  };
for(int n = 0; n<3; n++) {//@@
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

  for (int i = 0; i < ARRAY_SIZEOF( circleTable); i++ ) {
    colorSetArray(rgbwTable[ i % ARRAY_SIZEOF(rgbwTable)], (uint8_t*)circleTable[i].ptr, circleTable[i].size);
    if (true == waitForSignalOrDelay(100)) return;
  }
}//@@
}

void SoccerBall()
{
for(int n = 0; n<3; n++) {//@@
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), (uint8_t*)hexagons, sizeof(hexagons) );

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)pentagons, sizeof(pentagons) );
  if (true == waitForSignalOrDelay(700)) return;

  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), (uint8_t*)pentagons, sizeof(pentagons) );
  if (true == waitForSignalOrDelay(700)) return;

  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)pentagons, sizeof(pentagons) );
  if (true == waitForSignalOrDelay(700)) return;
}//@@
}

// ========================================
//              情報表示系
// ========================================
void DrawClock()
{
#if 0
  static int sec_before = -1;
  struct tm time_tm;

  int cntdown_sec = 60;
//@@  int cntdown_sec = 15;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

  while ( cntdown_sec >= 0) {
    if (getLocalTime(&time_tm)) {
      if (time_tm.tm_sec != sec_before) {

        colorSetNumToClockDigit(NeoPixelWrapper_RGB(255, 0, 0), 0, time_tm.tm_hour / 10);
        colorSetNumToClockDigit(NeoPixelWrapper_RGB(255, 0, 0), 1, time_tm.tm_hour % 10);
        colorSetNumToClockDigit(NeoPixelWrapper_RGB(0, 255, 0), 2, time_tm.tm_min / 10);
        colorSetNumToClockDigit(NeoPixelWrapper_RGB(0, 255, 0), 3, time_tm.tm_min % 10);
        colorSetNumToClockDigit(NeoPixelWrapper_RGB(0, 0, 255), 4, time_tm.tm_sec / 10);
        colorSetNumToClockDigit(NeoPixelWrapper_RGB(0, 0, 255), 5, time_tm.tm_sec % 10);

        sec_before = time_tm.tm_sec;
        cntdown_sec--;
      }
    }
    else {
      if (!TimeAvailable) break;
      ERR_LOG("Can't getLocalTime!");
      cntdown_sec--;
    }

    if (true == waitForSignalOrDelay(100)) return;
  }
#endif
}

void DrawBingoDemo()
{
  const NeoPixelWrapper_Color colors[] = {
    NeoPixelWrapper_RGB(0xFF, 0x00, 0x00),
    NeoPixelWrapper_RGB(0x00, 0xFF, 0x00),
    NeoPixelWrapper_RGB(0x00, 0x00, 0xFF),
    NeoPixelWrapper_RGB(0xFF, 0xFF, 0x00),
    NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF)
  };
  int wait_time;
  long num;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

for(int n = 0; n<3; n++) //@@
  for (int i = 0; i < 3; i++) {
    for (wait_time = 50; wait_time < 500; wait_time += 20) {
      num = random(1,99);
      colorSetNumToClockDigit(colors[num/20], 2, num / 10);
      colorSetNumToClockDigit(colors[num/20], 3, num % 10);
      
      if (true == waitForSignalOrDelay(wait_time)) return;
    }
    if (true == waitForSignalOrDelay(2500)) return;
  }
}

void colorSetNumToClockDigit(NeoPixelWrapper_Color c, int digit, int num)
{
  uint16_t mask = 1;

  for (int i = 0; i<10; i++) {
    if ( (mask & num_for_clock_segment_table[num]) != 0 ) {
      NeoPixelWrapper_setPixelColor(logicPosToRealPos(clock_segment_digit_table[digit][i]), c);
      DrawLedPixelOnLCDScreen(c, clock_segment_digit_table[digit][i]);
    }
    else {
      NeoPixelWrapper_setPixelColor(logicPosToRealPos(clock_segment_digit_table[digit][i]), NeoPixelWrapper_RGB(0, 0, 0));
      DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0, 0, 0), clock_segment_digit_table[digit][i]);
    }
    mask <<= 1;
  }
  NeoPixelWrapper_show();
//const uint8_t clock_segment_digit_table[][10] = {
//const uint16_t num_for_clock_segment_table[] = {
}

// ========================================
//               絵表示系
// ========================================
void DrawEarth()
{
  NeoPixelWrapper_Color col;
  int width;
  int count_per_pix;
  int index_offset;
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

for(int n = 0; n<3; n++) //@@
  for (int base_offset = 0; base_offset < 150; base_offset+= 5) {
    for (int y = 0; y<9; y++) {
      width = led_line_range_table[y].to - led_line_range_table[y].from + 1;
      count_per_pix = 150 / width;
      for (int x = 0, index_offset = 0; x < 150; x += count_per_pix ) {
        uint16_t r=0, g=0, b=0;
        for (int x_offset = 0; x_offset < count_per_pix; x_offset++) {
          r += earth_bitmap_data[y][(x + x_offset + (150-base_offset-1))%150][0];
          g += earth_bitmap_data[y][(x + x_offset + (150-base_offset-1))%150][1];
          b += earth_bitmap_data[y][(x + x_offset + (150-base_offset-1))%150][2]>>3;
        }
        col = NeoPixelWrapper_RGB( r / count_per_pix, g / count_per_pix, b / count_per_pix);
        NeoPixelWrapper_setPixelColor(logicPosToRealPos(index_offset + led_line_range_table[y].from), col);
        DrawLedPixelOnLCDScreen(col, index_offset + led_line_range_table[y].from);
        index_offset++;
      }
    }
    NeoPixelWrapper_show();
    if (true == waitForSignalOrDelay(300)) return;
  }
}

void FireWork()
{
  const uint8_t data1[] = {  4, 0, 1, 8, 7, 24, 23, 22, 47, 46, 45, 78, 73, 43, 42, 41, 18, 17};
  const uint8_t data2[] = {  23, 49, 48, 78, 77, 76, 75, 104, 103, 102, 72, 71, 70, 69, 40};
  const uint8_t data3[] = {  50,80,79,109,108,107,106,105,134,133,132,131,101,100,70};

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

  // Red
  colorSet(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), led_line_range_table[7].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), led_line_range_table[6].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[7].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), led_line_range_table[5].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[6].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), led_line_range_table[4].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[5].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), led_line_range_table[3].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[4].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)data2, sizeof(data2) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)data3, sizeof(data3) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data2, sizeof(data2) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data3, sizeof(data3) );
  if (true == waitForSignalOrDelay(500)) return;

  // Green
  colorSet(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), led_line_range_table[7].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), led_line_range_table[6].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[7].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), led_line_range_table[5].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[6].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), led_line_range_table[4].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[5].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), led_line_range_table[3].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[4].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), (uint8_t*)data2, sizeof(data2) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), (uint8_t*)data3, sizeof(data3) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data2, sizeof(data2) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data3, sizeof(data3) );
  if (true == waitForSignalOrDelay(500)) return;

  // Blue
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), led_line_range_table[7].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), led_line_range_table[6].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[7].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), led_line_range_table[5].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[6].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), led_line_range_table[4].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[5].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), led_line_range_table[3].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[4].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)data2, sizeof(data2) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)data3, sizeof(data3) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data2, sizeof(data2) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data3, sizeof(data3) );
  if (true == waitForSignalOrDelay(500)) return;

  // White
  colorSet(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), led_line_range_table[7].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[8].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), led_line_range_table[6].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[7].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), led_line_range_table[5].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[6].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), led_line_range_table[4].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[5].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSet(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), led_line_range_table[3].from);
  colorSet(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), led_line_range_table[4].from);
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), (uint8_t*)data2, sizeof(data2) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)hexagons[0], sizeof(hexagons[0]) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), (uint8_t*)data3, sizeof(data3) );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data1, sizeof(data1) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data2, sizeof(data2) );
  if (true == waitForSignalOrDelay(200)) return;
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)data3, sizeof(data3) );
  if (true == waitForSignalOrDelay(500)) return;
}

void DrawFace()
{
  const static uint8_t hair[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
    66, 67, 68, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 112, 113, 114, 115, 116, 117,
    118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152
  };
  const static uint8_t skin [] = {
    45, 46, 47, 48, 49, 50, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 99, 100, 101, 102, 103, 104, 106, 107, 108,
    109, 110, 111, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 153, 154, 155, 156, 157, 158,
    159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179
  };
  const static uint8_t nose [] = {
    105
  };

  // [a:Smile]
  const static uint8_t eye_a [] = {
    46, 47, 48, 72, 73, 74
  };
  const static uint8_t mouse_a [] = {
    108, 132, 136, 137, 157, 158
  };

  // [b:Sleepy]
  const static uint8_t eye_b [] = {
    76, 77, 78, 102, 103, 104
  };
  const static uint8_t mouse_b [] = {
    135, 137, 157, 159
  };

  // [c:Angry]
  const static uint8_t eye_c [] = {
    48, 72, 76, 104
  };
  const static uint8_t mouse_c [] = {
    135, 137, 157, 159
  };

  // [d:Surprise]
  const static uint8_t eye_d [] = {
    46, 47, 48, 72, 73, 74, 76, 77, 78, 102, 103, 104
  };
  const static uint8_t mouse_d [] = {
    135, 136, 158, 159, 160, 174
  };

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

for(int n = 0; n<3; n++) {//@@
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x40, 0x00), (uint8_t*)hair, sizeof(hair), true );
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)nose, sizeof(nose), true );

  colorSetArray(NeoPixelWrapper_RGB(0x2D, 0x1F, 0x0F), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)eye_a, sizeof(eye_a), true );
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)mouse_a, sizeof(mouse_a) );
  if (true == waitForSignalOrDelay(900)) return;

  colorSetArray(NeoPixelWrapper_RGB(0x2D, 0x1F, 0x0F), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)eye_b, sizeof(eye_b), true );
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)mouse_b, sizeof(mouse_b) );
  if (true == waitForSignalOrDelay(900)) return;

  colorSetArray(NeoPixelWrapper_RGB(0x2D, 0x1F, 0x0F), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)eye_c, sizeof(eye_c), true );
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)mouse_c, sizeof(mouse_c) );
  if (true == waitForSignalOrDelay(900)) return;

  colorSetArray(NeoPixelWrapper_RGB(0x2D, 0x1F, 0x0F), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)eye_d, sizeof(eye_d), true );
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)mouse_d, sizeof(mouse_d) );
  if (true == waitForSignalOrDelay(900)) return;
}//@@
}

void DrawHalloweenPumpkin()
{
  const static uint8_t skin [] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
    62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 76, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94,
    95, 96, 97, 98, 99, 100, 101, 102, 104, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,
    123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147,
    148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
    171, 172, 173, 174, 175, 176, 177, 178, 179
  };
  const static uint8_t eye_mouse [] = {
    46, 47, 48, 72, 73, 74, 75, 77, 103, 105, 106, 107, 133, 134
  };

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

for(int n = 0; n<6; n++) {//@@
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x7F), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x7F, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x7F), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x7F, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x7F), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0x7F, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x45, 0x00), (uint8_t*)skin, sizeof(skin), true );
  colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), (uint8_t*)eye_mouse, sizeof(eye_mouse) );
  if (true == waitForSignalOrDelay(800)) return;
}//@@
}

void DrawStar()
{
  const static uint8_t star_inner [] = {
    46, 56, 58, 62, 64, 74, 76, 86, 88, 92, 93, 94, 104
  };
  const static uint8_t star_middle [] = {
    45, 47, 55, 57, 63, 73, 75, 77, 85, 87, 91, 95, 103
  };
  const static uint8_t star_outer [] = {
    5, 11, 14, 20, 30, 35, 48, 49, 53, 54, 59, 60, 61, 65, 66, 67, 71, 72, 108, 114, 120, 126, 132
  };

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

for(int n = 0; n<3; n++) {//@@
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179, true);
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0x10, 0x10, 0x00), (uint8_t*)star_inner, sizeof(star_inner) );
  if (true == waitForSignalOrDelay(100)) return;

  colorSetArray(NeoPixelWrapper_RGB(0x40, 0x40, 0x00), (uint8_t*)star_inner, sizeof(star_inner), true );
  colorSetArray(NeoPixelWrapper_RGB(0x10, 0x10, 0x00), (uint8_t*)star_middle, sizeof(star_middle) );
  if (true == waitForSignalOrDelay(100)) return;

  for (int i = 0; i<6; i++) {
    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0x00), (uint8_t*)star_inner, sizeof(star_inner), true );
    colorSetArray(NeoPixelWrapper_RGB(0x40, 0x40, 0x00), (uint8_t*)star_middle, sizeof(star_middle), true );
    colorSetArray(NeoPixelWrapper_RGB(0x10, 0x10, 0x00), (uint8_t*)star_outer, sizeof(star_outer) );
    if (true == waitForSignalOrDelay(100)) return;

    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0x00), (uint8_t*)star_inner, sizeof(star_inner), true );
    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0x00), (uint8_t*)star_middle, sizeof(star_middle), true );
    colorSetArray(NeoPixelWrapper_RGB(0x40, 0x40, 0x00), (uint8_t*)star_outer, sizeof(star_outer) );
    if (true == waitForSignalOrDelay(100)) return;

    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0x00), (uint8_t*)star_inner, sizeof(star_inner), true );
    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0x00), (uint8_t*)star_middle, sizeof(star_middle), true );
    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0xFF, 0x00), (uint8_t*)star_outer, sizeof(star_outer) );
    if (true == waitForSignalOrDelay(100)) return;
  }
}//@@
}

void DrawHeart()
{
  const static uint8_t heart_outer [] = {
    22, 23, 42, 43, 45, 49, 71, 79, 101, 108, 132, 135, 159
  };
  const static uint8_t heart_inner [] = {
    46, 47, 48, 72, 73, 74, 75, 76, 77, 78, 102, 103, 104, 105, 106, 107, 133, 134
  };

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

for(int n = 0; n<3; n++) //@@
  for (int i = 0; i<6; i++) {
    colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), (uint8_t*)heart_outer, sizeof(heart_outer), true );
    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)heart_inner, sizeof(heart_inner) );
    if (true == waitForSignalOrDelay(500)) return;

    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x3F, 0x7F), (uint8_t*)heart_outer, sizeof(heart_outer), true );
    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x3F, 0x7F), (uint8_t*)heart_inner, sizeof(heart_inner) );
    if (true == waitForSignalOrDelay(500)) return;
  }
}

void DrawJanken()
{
  const static uint8_t janken_goo [] = {
    75, 76, 77, 103, 104, 105, 106, 107, 133, 134
  };
  const static uint8_t janken_choki [] = {
    22, 44, 46, 74, 75, 76, 77, 103, 104, 105, 106, 107, 133, 134
  };
  const static uint8_t janken_pah [] = {
    20, 22, 42, 45, 46, 47, 73, 75, 76, 77, 78, 102, 103, 104, 105, 106, 107, 133, 134
  };

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

for(int n = 0; n<3; n++) //@@
  for (int i = 0; i<2; i++) {
    colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179, true);
    colorSetArray(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), (uint8_t*)janken_goo, sizeof(janken_goo) );
    if (true == waitForSignalOrDelay(500)) return;

    colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179, true);
    colorSetArray(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), (uint8_t*)janken_choki, sizeof(janken_choki) );
    if (true == waitForSignalOrDelay(500)) return;

    colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179, true);
    colorSetArray(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), (uint8_t*)janken_pah, sizeof(janken_pah) );
    if (true == waitForSignalOrDelay(500)) return;
  }
}
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY)

void DotRun()
{
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, (NUM_OF_NEOPIXELS-1) );
  if (true == waitForSignalOrDelay(500)) return;

  for (int i = 0; i<NUM_OF_NEOPIXELS; i++) {
    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0xFF, 0x00, 0x00));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0xFF, 0x00, 0x00), i);
    NeoPixelWrapper_show();

    if (true == waitForSignalOrDelay(5)) return;

    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0x00, 0x00, 0x00));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), i);
    NeoPixelWrapper_show();
  }
  if (true == waitForSignalOrDelay(200)) return;

  for (int i = 0; i<NUM_OF_NEOPIXELS; i++) {
    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0x00, 0xFF, 0x00));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0x00, 0xFF, 0x00), i);
    NeoPixelWrapper_show();

    if (true == waitForSignalOrDelay(5)) return;

    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0x00, 0x00, 0x00));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), i);
    NeoPixelWrapper_show();
  }
  if (true == waitForSignalOrDelay(200)) return;

  for (int i = 0; i<NUM_OF_NEOPIXELS; i++) {
    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0x00, 0x00, 0xFF));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0x00, 0x00, 0xFF), i);
    NeoPixelWrapper_show();

    if (true == waitForSignalOrDelay(5)) return;

    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0x00, 0x00, 0x00));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), i);
    NeoPixelWrapper_show();
  }
  if (true == waitForSignalOrDelay(200)) return;

  for (int i = 0; i<NUM_OF_NEOPIXELS; i++) {
    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0xFF, 0xFF, 0xFF), i);
    NeoPixelWrapper_show();

    if (true == waitForSignalOrDelay(5)) return;

    NeoPixelWrapper_setPixelColor(logicPosToRealPos(i), NeoPixelWrapper_RGB(0x00, 0x00, 0x00));
    DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), i);
    NeoPixelWrapper_show();
  }
  if (true == waitForSignalOrDelay(200)) return;
}

void CheckLEDOrder() {
  NeoPixelWrapper_Color col;

  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);

  for (int i = 0; i<4; i++) {
    for (int step = 0; step < NUM_OF_NEOPIXELS; step++) {
      for (int index = 0; index<NUM_OF_NEOPIXELS; index++) {
        if ( ( index % 5 ) == ( step % 5 ) ) {
          col = rgbwTable[( ( NUM_OF_NEOPIXELS + (NUM_OF_NEOPIXELS % 5) + step - index ) / 5 ) % 4 ];
#if 1
          NeoPixelWrapper_setPixelColor(index, col);
          DrawLedPixelOnLCDScreen(col, index);
#else
          NeoPixelWrapper_setPixelColor(logicPosToRealPos(index), col);
          DrawLedPixelOnLCDScreen(col, index);
#endif
        }
        else {
          NeoPixelWrapper_setPixelColor(index, NeoPixelWrapper_RGB(0x00, 0x00, 0x00));
          DrawLedPixelOnLCDScreen(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), index);
        }
      }
      NeoPixelWrapper_show();
      if (true == waitForSignalOrDelay(500)) return;
    }
  }
}


#if defined(THIS_BLOCK_IS_180LEDs_ONLY)
void DrawStringA()
{
  const NeoPixelWrapper_Color font_cols[] = { NeoPixelWrapper_RGB(255, 0, 0), NeoPixelWrapper_RGB(0, 255, 0), NeoPixelWrapper_RGB(0, 0, 255), NeoPixelWrapper_RGB(255, 255, 255) };
  const NeoPixelWrapper_Color back_col = NeoPixelWrapper_RGB(0, 0, 0);
//  const String str_to_print = "Hello World";
//  const String str_to_print = "MOUSER MAKE AWARD";
  const String str_to_print = "M5STACK";
  static int col_index = 0;
  int code;

for(int n = 0; n<3; n++) {//@@
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);
  if (true == waitForSignalOrDelay(500)) return;

  for (int i = 0; i < str_to_print.length(); i++) {
    code = (int)str_to_print.c_str()[i];
    if ( true == IsValidCode(code) ) {
      DrawFont(code, font_cols[col_index], back_col);
      col_index ++;
      col_index %= ARRAY_SIZEOF(font_cols);
      if (true == waitForSignalOrDelay(300)) return;
    }
  }
  if (true == waitForSignalOrDelay(1500)) return;
}//@@
}

void DrawStringB()
{
  const NeoPixelWrapper_Color font_cols[] = { NeoPixelWrapper_RGB(255, 0, 0), NeoPixelWrapper_RGB(0, 255, 0), NeoPixelWrapper_RGB(0, 0, 255), NeoPixelWrapper_RGB(255, 255, 255) };
  const NeoPixelWrapper_Color back_col = NeoPixelWrapper_RGB(0, 0, 0);
//  const String str_to_print = "Hello World";
  const String str_to_print = "MOUSER MAKE AWARD";
//  const String str_to_print = "M5STACK";
  static int col_index = 0;
  int code;

for(int n = 0; n<3; n++) {//@@
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);
  if (true == waitForSignalOrDelay(500)) return;

  for (int i = 0; i < str_to_print.length(); i++) {
    code = (int)str_to_print.c_str()[i];
    if ( true == IsValidCode(code) ) {
      DrawFont(code, font_cols[col_index], back_col);
      col_index ++;
      col_index %= ARRAY_SIZEOF(font_cols);
      if (true == waitForSignalOrDelay(300)) return;
    }
  }
  if (true == waitForSignalOrDelay(1500)) return;
}//@@
}

void DrawStringC()
{
  const NeoPixelWrapper_Color font_cols[] = { NeoPixelWrapper_RGB(255, 0, 0), NeoPixelWrapper_RGB(255, 255, 0), NeoPixelWrapper_RGB(0, 255, 0), NeoPixelWrapper_RGB(0, 255, 255), NeoPixelWrapper_RGB(0, 0, 255), NeoPixelWrapper_Color(255, 0, 255), NeoPixelWrapper_Color(255, 127, 0), NeoPixelWrapper_Color(255, 255, 255) };
  const NeoPixelWrapper_Color back_col = NeoPixelWrapper_RGB(0, 0, 0);
//  const String str_to_print = "Hello World";
  const String str_to_print = "A Happy New Year 2024";
//  const String str_to_print = "M5STACK";
  static int col_index = 0;
  int code;

for(int n = 0; n<1; n++) {//@@
  // All Black
  colorSetRange(NeoPixelWrapper_RGB(0x00, 0x00, 0x00), 0, 179);
  if (true == waitForSignalOrDelay(500)) return;

  for (int i = 0; i < str_to_print.length(); i++) {
    code = (int)str_to_print.c_str()[i];
    if ( true == IsValidCode(code) ) {
      DrawFont(code, font_cols[col_index], back_col);
      col_index ++;
      col_index %= ARRAY_SIZEOF(font_cols);
      if (true == waitForSignalOrDelay(300)) return;
    }
  }
  if (true == waitForSignalOrDelay(1500)) return;
}//@@

}

bool IsValidCode(char code)
{
  if ( (code == ' ') || ( (code >= '0') && (code <= 'z') ) ) {
    return true;
  }
  return false;
}

void DrawFont(char code, NeoPixelWrapper_Color col, NeoPixelWrapper_Color back)
{
  colorSetArray(back, (uint8_t*)center_font_area_table, sizeof(center_font_area_table), true);
  if (code != ' ') {
    colorSetArray(col, (uint8_t*)center_font_data_table[code - '0'].data, center_font_data_table[code - '0'].len, true);
  }
  NeoPixelWrapper_show();

}
#endif // defined(THIS_BLOCK_IS_180LEDs_ONLY)
