//=====[Libraries]=============================================================
#include "mbed.h"
#include "SSD1308.h"

DigitalOut ledVerde(LED1);
DigitalOut ledAzul(LED2);
DigitalOut ledRojo(LED3);

#define HEIGHT 64
#define WIDTH  128

#define I2C1_SDA PB_9 // Tomi: En NUCLEO-F429ZI esto va OK, en otra placa checkear pines SDA y SCL
#define I2C1_SCL PB_8

I2C i2cSsd1306(I2C1_SDA, I2C1_SCL); 
SSD1306 OLED(WIDTH, HEIGHT, &i2cSsd1306);
// 'rata synth', 128x64px
const char bitmap_rata_synth [] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xc0, 0x47, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xbf, 0xfb, 0xff, 0xff, 0x9f, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0x9e, 0xb1, 0xff, 0xff, 0x9f, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x75, 0x7c, 0xff, 0xff, 0x69, 0x79, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x6a, 0xac, 0xff, 0xfe, 0x35, 0x59, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x75, 0x3c, 0xff, 0xfd, 0xcb, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xf9, 0x4a, 0x94, 0xff, 0xfc, 0xa9, 0x29, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfd, 0xfa, 0x5c, 0xff, 0xfc, 0xe6, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xf9, 0x2a, 0x94, 0xff, 0xfc, 0xab, 0x59, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xf9, 0xd5, 0x58, 0x00, 0x00, 0xd1, 0xb3, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xf9, 0x6a, 0x94, 0x00, 0x00, 0xcc, 0xf9, 0xf8, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfd, 0xad, 0x4c, 0xdf, 0xed, 0x25, 0x59, 0xf0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xf9, 0xf4, 0xa4, 0xaa, 0xb5, 0x2b, 0xe9, 0xc1, 0xf4, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x57, 0x56, 0xf0, 0x1e, 0x80, 0xa7, 0xc0, 0xdf, 0x80, 0x00, 0x02, 0xff, 0xff, 0xff, 
  0xff, 0xfe, 0x7a, 0x95, 0x50, 0x0b, 0x00, 0xe7, 0xf0, 0x75, 0xe1, 0x24, 0x88, 0x07, 0xff, 0xff, 
  0xff, 0xff, 0x8d, 0xea, 0xc1, 0x04, 0x08, 0x1f, 0xf4, 0xdf, 0x5f, 0xff, 0xfe, 0x90, 0x7f, 0xff, 
  0xff, 0xff, 0xaa, 0x2b, 0xa4, 0x62, 0x52, 0x1f, 0x80, 0x75, 0xfa, 0xaa, 0xd7, 0xfe, 0x07, 0xff, 
  0xff, 0xff, 0xc0, 0x36, 0x85, 0x40, 0x24, 0x9c, 0x17, 0xdf, 0x5f, 0xff, 0xba, 0xab, 0xc0, 0xff, 
  0xff, 0xff, 0xa4, 0x95, 0x89, 0x00, 0x48, 0x11, 0xfd, 0x76, 0xf5, 0xad, 0xff, 0xfe, 0xf0, 0x3f, 
  0xff, 0xff, 0x1b, 0x6a, 0x92, 0x20, 0x12, 0x00, 0x0f, 0xdf, 0xbe, 0xfb, 0x55, 0x57, 0xbe, 0x0f, 
  0xff, 0xff, 0x95, 0x2a, 0x0a, 0x00, 0x40, 0x02, 0x1a, 0xf5, 0xd7, 0xbf, 0xff, 0xfd, 0xdb, 0xc3, 
  0xff, 0xff, 0x3c, 0x81, 0x08, 0x90, 0x12, 0x0e, 0x17, 0xb0, 0x0d, 0x00, 0x80, 0x50, 0x37, 0x70, 
  0xff, 0xfa, 0x10, 0x10, 0x00, 0x00, 0x00, 0x9a, 0x1d, 0xd0, 0x0e, 0x01, 0x80, 0x70, 0x3d, 0xd8, 
  0xff, 0xfe, 0x62, 0x80, 0x12, 0x43, 0x08, 0x3e, 0x0e, 0xfc, 0x34, 0x3e, 0xe1, 0xc3, 0xcf, 0x74, 
  0xff, 0xfa, 0x00, 0x55, 0x40, 0x05, 0x50, 0xea, 0x1b, 0xac, 0x38, 0x2b, 0xa1, 0xc1, 0x4b, 0xdf, 
  0xff, 0xdc, 0x08, 0x6a, 0xa1, 0x05, 0xa0, 0xbe, 0x16, 0xf8, 0x2c, 0x00, 0xe1, 0x43, 0xcd, 0x76, 
  0xff, 0xf8, 0x43, 0x5f, 0xa8, 0x1b, 0x6c, 0xea, 0x1f, 0xac, 0x34, 0x01, 0xa1, 0xc2, 0x8f, 0xdd, 
  0xff, 0xa8, 0x05, 0x55, 0xd0, 0x56, 0xd4, 0xbe, 0x0a, 0xfc, 0x3f, 0xe0, 0xe1, 0xc3, 0xca, 0xf7, 
  0xfe, 0x80, 0x1a, 0xfe, 0xef, 0xfb, 0xf2, 0xee, 0x15, 0x28, 0x08, 0xa3, 0xa1, 0x60, 0x1f, 0x5d, 
  0xff, 0xd9, 0x57, 0x53, 0x5a, 0xae, 0xba, 0x76, 0x00, 0x10, 0x0c, 0x05, 0xc1, 0xd0, 0x35, 0xf7, 
  0xff, 0xf9, 0x5d, 0xad, 0x6d, 0xfb, 0xeb, 0x3a, 0xaa, 0xb5, 0x55, 0x56, 0xeb, 0x7a, 0xbf, 0x7d, 
  0xf7, 0xe6, 0x57, 0xb6, 0x81, 0x16, 0xbc, 0x0f, 0xdd, 0xdf, 0xbf, 0xbb, 0xbd, 0xef, 0xeb, 0xaf, 
  0xff, 0xe2, 0x5a, 0xfb, 0xf6, 0x45, 0xea, 0x16, 0xf6, 0x01, 0xe0, 0x68, 0x07, 0x40, 0xbd, 0xf5, 
  0xff, 0x80, 0x17, 0xae, 0xbb, 0xb5, 0x51, 0x47, 0x5c, 0x02, 0xb0, 0x38, 0x07, 0xc0, 0xef, 0x5e, 
  0xff, 0x40, 0x09, 0x7b, 0xd4, 0xd5, 0x71, 0x65, 0xf6, 0x18, 0xc2, 0x88, 0x71, 0x0d, 0x35, 0xf7, 
  0xfa, 0x08, 0x0d, 0xdd, 0x7a, 0x06, 0x80, 0x87, 0x7c, 0x1c, 0x83, 0x98, 0x59, 0x07, 0x3f, 0x7d, 
  0xf0, 0x00, 0x42, 0x57, 0xc2, 0xfa, 0xfe, 0x5b, 0xae, 0x03, 0xc0, 0x08, 0x07, 0x00, 0x2b, 0xaf, 
  0xf8, 0x20, 0x03, 0x6d, 0x35, 0x52, 0xaa, 0x1d, 0xf4, 0x01, 0x40, 0x18, 0x05, 0x00, 0x3e, 0xf5, 
  0xf0, 0x80, 0x22, 0xaa, 0x5a, 0xa2, 0xad, 0x6f, 0x5e, 0x1f, 0xc3, 0x88, 0x71, 0x8f, 0x2b, 0xbe, 
  0xe0, 0x14, 0x01, 0x55, 0xd2, 0x9d, 0x70, 0xf5, 0xf4, 0x1a, 0x82, 0x98, 0x59, 0x05, 0x3e, 0xeb, 
  0xa2, 0x25, 0x08, 0x5a, 0xaa, 0x29, 0x49, 0x5f, 0x7e, 0x1f, 0xc3, 0xc8, 0x71, 0x8f, 0x2b, 0xbf, 
  0x81, 0x4c, 0x80, 0x6a, 0xac, 0x50, 0x87, 0xf7, 0xaa, 0x35, 0x45, 0x98, 0x5b, 0x0a, 0x3a, 0xaa, 
  0x84, 0xb2, 0x40, 0x2a, 0xa9, 0x0e, 0x0d, 0x5d, 0xff, 0xef, 0xff, 0x6f, 0xfd, 0xff, 0xe8, 0x0f, 
  0x85, 0x49, 0x10, 0x16, 0xd4, 0x07, 0x47, 0xe5, 0x4a, 0x2b, 0x15, 0xfa, 0x0e, 0x41, 0xa0, 0x82, 
  0x92, 0x94, 0xa1, 0x1a, 0xaa, 0x0f, 0xe5, 0xa3, 0xcf, 0x03, 0x87, 0x5c, 0x0b, 0x01, 0xe3, 0xc3, 
  0x8a, 0x42, 0x40, 0x15, 0x52, 0x0f, 0xe3, 0xc1, 0x48, 0x29, 0x85, 0xf0, 0xaa, 0x0a, 0x55, 0x02, 
  0xaa, 0xaa, 0x90, 0x8b, 0x64, 0x0f, 0xe6, 0xc1, 0xcc, 0x38, 0x87, 0x50, 0xf3, 0x1c, 0x7b, 0x03, 
  0x25, 0x15, 0x24, 0x05, 0x4c, 0x0f, 0xe3, 0x63, 0x48, 0x29, 0x85, 0xf0, 0x02, 0x01, 0x6c, 0x2b, 
  0x14, 0xa6, 0x50, 0x05, 0x4a, 0x0f, 0xe5, 0xc1, 0xcc, 0x38, 0x87, 0x68, 0x02, 0x01, 0xdc, 0x1d, 
  0x4b, 0x11, 0x08, 0xa5, 0xaa, 0x0f, 0xe3, 0xb0, 0x28, 0x39, 0x85, 0xf0, 0xa3, 0x0c, 0x77, 0xf7, 
  0x2d, 0x4a, 0xa0, 0x04, 0x94, 0x07, 0xe3, 0xf0, 0x3c, 0x28, 0x87, 0x50, 0xf2, 0x16, 0x5d, 0x5e, 
  0xab, 0x28, 0x54, 0x43, 0x54, 0x0f, 0xf1, 0x5c, 0xab, 0x07, 0x80, 0x30, 0xa3, 0x0e, 0x76, 0x37, 
  0x24, 0xa5, 0x48, 0x02, 0xa8, 0x8f, 0xf9, 0xf4, 0xfe, 0x02, 0x80, 0x10, 0xf2, 0x1a, 0x5c, 0x1c, 
  0x96, 0x92, 0x22, 0x23, 0xf8, 0x0f, 0xf8, 0x5f, 0x57, 0xff, 0xff, 0xff, 0x5f, 0xef, 0xf7, 0xf4, 
  0x54, 0x49, 0x54, 0x09, 0x2c, 0x0f, 0xfc, 0x77, 0xfd, 0x55, 0x55, 0x55, 0xf5, 0xba, 0xbd, 0xb0, 
  0x36, 0xa4, 0x88, 0x01, 0xd4, 0x1f, 0xfe, 0x1d, 0x57, 0xff, 0xff, 0xff, 0x5f, 0x7f, 0xd7, 0x41, 
  0x95, 0x12, 0x52, 0x22, 0xb8, 0x1f, 0xff, 0x03, 0xfd, 0x6d, 0x55, 0x55, 0xf5, 0xd5, 0x7d, 0x07, 
  0x54, 0xa9, 0x24, 0x81, 0x61, 0x7f, 0xff, 0xe0, 0xb7, 0xdf, 0xff, 0xff, 0x7f, 0x7f, 0xd8, 0x1f, 
  0x2a, 0x44, 0x92, 0x00, 0x00, 0xff, 0xff, 0xf8, 0xee, 0xf5, 0x6d, 0xb7, 0xab, 0xd5, 0xe0, 0x7f
};
const char epd_bitmap_negro [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const char epd_bitmap_blanco [] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


//=====[Main function, the program entry point after power on or reset]========

int main()
{
    ledAzul =1;
    OLED.displayInit(DISPLAY_CONNECTION_I2C_SSD1306_OLED);
    while(1){
        OLED.drawBitmap(0,0,epd_bitmap_negro,WIDTH, HEIGHT,1);
        OLED.display();
        wait_us(1000000);
        ledAzul = !ledAzul;
        OLED.drawBitmap(0,0,epd_bitmap_blanco,WIDTH, HEIGHT,1);
        OLED.display();
        wait_us(1000000);
        ledAzul = !ledAzul;
    }
}
