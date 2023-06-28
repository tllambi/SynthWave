//=====[#include guards - begin]===============================================

#ifndef _SSD1306_H_
#define _SSD1306_H_

#include "mbed.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================
typedef enum {
     DISPLAY_CONNECTION_I2C_SSD1306_OLED,               // <-- Por ahora implemente solo esta
     DISPLAY_CONNECTION_3WIRES_SPI_SSD1306_OLED,
     DISPLAY_CONNECTION_4WIRES_SPI_SSD1306_OLED,
     DISPLAY_CONNECTION_8BITS_SERIE_8080_SSD1306_OLED,
     DISPLAY_CONNECTION_8BITS_SERIE_6800_SSD1306_OLED,
} displayConnection_t;

class SSD1306{
public:
  SSD1306(uint8_t w, uint8_t h, I2C *i2c);
  SSD1306(uint8_t w, uint8_t h, I2C *i2c, UnbufferedSerial *uartUsb);
  // En el futuro se pueden agregar otros constructores para admitir SPI y Comunicacion Serie
  ~SSD1306(void);

  bool displayInit(displayConnection_t connection);
  void magicInit(displayConnection_t connection);
  void serieI2CCom();
  void clearDisplay();                                  // Limpia el buffer 
  void display(void);                                   // Envia al display lo que contiene el buffer
  void drawBitmap(int16_t x, int16_t y, const char bitmap[], int16_t w, int16_t h, uint16_t color);
  void writePixel(int16_t x, int16_t y, uint16_t color);
  void drawPixel(int16_t x, int16_t y, uint16_t color);

protected:
  void displayCommand(char command);
  void displayCommandList(const char *command, uint8_t commandLen);
  void displayData(char data);

  I2C *i2c;   
  UnbufferedSerial *uartUsb;

  char *buffer; 
  int8_t i2caddr;  
  int address;

  displayConnection_t connection;

};
//=====[Declarations (prototypes) of public functions]=========================

//void displayInit(displayConnection_t connection);
 
//static void displayCommand(char command);

//static void displayCommandList(const char *command, uint8_t commandLen);

//=====[#include guards - end]=================================================

#endif // _SSD1306_H_