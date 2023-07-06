//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "SSD1308.h"

//=====[Declaration of private defines]========================================
#define HEIGHT 64
#define WIDTH  128

#define SSD1306_BLACK 0   ///< Draw 'off' pixels
#define SSD1306_WHITE 1   ///< Draw 'on' pixels
#define SSD1306_INVERSE 2 ///< Invert pixels

#define SSD1306_MEMORYMODE          0x20    ///< See datasheet
#define SSD1306_COLUMNADDR          0x21    ///< See datasheet
#define SSD1306_PAGEADDR            0x22    ///< See datasheet
#define SSD1306_SETCONTRAST         0x81    ///< See datasheet
#define SSD1306_CHARGEPUMP          0x8D    ///< See datasheet
#define SSD1306_SEGREMAP            0xA0    ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4    ///< See datasheet
#define SSD1306_DISPLAYALLON        0xA5    ///< Not currently used
#define SSD1306_NORMALDISPLAY       0xA6    ///< See datasheet
#define SSD1306_INVERTDISPLAY       0xA7    ///< See datasheet
#define SSD1306_SETMULTIPLEX        0xA8    ///< See datasheet
#define SSD1306_DISPLAYOFF          0xAE    ///< See datasheet
#define SSD1306_DISPLAYON           0xAF    ///< See datasheet
#define SSD1306_COMSCANINC          0xC0    ///< Not currently used
#define SSD1306_COMSCANDEC          0xC8    ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET    0xD3    ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5    ///< See datasheet
#define SSD1306_SETPRECHARGE        0xD9    ///< See datasheet
#define SSD1306_SETCOMPINS          0xDA    ///< See datasheet
#define SSD1306_SETVCOMDETECT       0xDB    ///< See datasheet

#define SSD1306_SETLOWCOLUMN        0x00    ///< Not currently used
#define SSD1306_SETHIGHCOLUMN       0x10    ///< Not currently used
#define SSD1306_SETSTARTLINE        0x40    ///< See datasheet

#define SSD1306_EXTERNALVCC         0x01    ///< External display voltage source
#define SSD1306_SWITCHCAPVCC        0x02    ///< Gen. display voltage from 3.3V

#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26    ///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27    ///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29    ///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A    ///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL                       0x2E    ///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL                         0x2F    ///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3    ///< Set scroll range

#define I2C1_SDA PB_9 // Tomi: En NUCLEO-F429ZI esto va OK, en otra placa checkear pines SDA y SCL
#define I2C1_SCL PB_8

#define SSD1306_I2C_BUS_8BIT_WRITE_ADDRESS 0x3C // Tomi: 0x3D para display de 128x64px, 0x3C para 128x32px  
                                                //       Aunque encontre que el mio tiene la posibilidad de 
                                                //       elegir cortocircuitando una pista.

#define ssd1306_swap(a, b)                                                     \
  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))) ///< No-temp-var swap operation

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool initial8BitCommunicationIsCompleted;

//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================
SSD1306::SSD1306(uint8_t w, uint8_t h, I2C *i2c){
    this->i2c = i2c;
}
SSD1306::SSD1306(uint8_t w, uint8_t h, I2C *i2c, UnbufferedSerial *uartUsb){
    this->i2c = i2c;
    this->uartUsb = uartUsb;
}

DigitalOut Rojo(LED3);
void SSD1306::magicInit(displayConnection_t connection){
    char magicString[] = {0x00,0xAE,0xD5,0x80,0xA8,0x00,0x3F,0x00,0xD3,0x00, 0x40, 0x8D, 0x00, 0x20, 0x00, 0xA1, 0xC8, 0x00, 0x12, 0x00, 0xCF, 0x00, 0xD9, 0x00, 0xF1, 0x00, 0x22, 0x00, 0xFF, 0x21, 0x00, 0x40, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x5F, 0xCF, 0xCF, 0xCF, 0xCF, 0x4F, 0xCF, 0x6F, 0xCF, 0xCF, 0x5F, 0x3F, 0x7F, 0x40, 0x0C, 0x94, 0x8D, 0xCF, 0xC2, 0xE7, 0xE1, 0xF1};
    //char magicString2[] = {0x21,0x00,0x40,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x40,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    char *magicChar = magicString;
    //char *magicChar2 = magicString2;
    
    i2c->write(this->address, magicString, sizeof(magicString));
    //i2c->write(this->address, magicChar2++,count);
}
void SSD1306::magicInit(){
    char magicString[] = {0x00,0xAE,0xD5,0x80,0xA8,0x00,0x3F,0x00,0xD3,0x00, 0x40, 0x8D, 0x00, 0x20, 0x00, 0xA1, 0xC8, 0x00, 0x12, 0x00, 0xCF, 0x00, 0xD9, 0x00, 0xF1, 0x00, 0x22, 0x00, 0xFF, 0x21, 0x00, 0x40, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x5F, 0xCF, 0xCF, 0xCF, 0xCF, 0x4F, 0xCF, 0x6F, 0xCF, 0xCF, 0x5F, 0x3F, 0x7F, 0x40, 0x0C, 0x94, 0x8D, 0xCF, 0xC2, 0xE7, 0xE1, 0xF1};
    char *magicChar = magicString;
    char view;
    for(int i=0; i<sizeof(magicString); i++){
        i2c->write(this->address, &magicString[i], 1);
        view=magicString[i];
    }
}
void SSD1306::serieI2CCom(){
    char receivedChar = '\0';
    if( this->uartUsb->readable() ) {
        this->uartUsb->read( &receivedChar, 1);
        this->uartUsb->write("\n0. Print anything \n", 20);
        this->uartUsb->write("a. Increment Contrast   \n", 26);
        this->uartUsb->write("b. Dencrement Contrast  \n", 26);
        this->uartUsb->write("c. magicInit            \n", 26);
        this->uartUsb->write("d. Print anything invert\n", 26);
        this->uartUsb->write("e. Print anything invert\n", 26);
        this->uartUsb->write("f. Print anything invert\n", 26);
        this->uartUsb->write("g. Print anything invert\n", 26);        
        this->uartUsb->write("1. Display On (A4)\n", 20);
        this->uartUsb->write("2. Display On (A5)\n", 19);
        this->uartUsb->write("3. Set Normal (A6)\n", 19);
        this->uartUsb->write("4. Set Inverse (A7)\n", 20);
        this->uartUsb->write("5. Scroll Right\n", 16);
        this->uartUsb->write("6. Scroll Left\n", 15);
        this->uartUsb->write("7. Scroll Up\n", 13);
        this->uartUsb->write("8. Scroll Down\n", 15);
        this->uartUsb->write("9. Scroll Stop\n", 15);
        static const char testChar = 0x55;
        static const char controlByte = 0x40;
        char contrastList[] = {SSD1306_SETCONTRAST, contraste};

        switch(receivedChar){
            case '0':
                static const char dlist0[] = {
                    SSD1306_MEMORYMODE,
                    0x02};  

                static const char dlist1[] = {
                    SSD1306_PAGEADDR,
                    0x00,                      // Page start address
                    0xFF};                   // Page end (not really, but works here)
                    
                static const char list2[] = {
                    SSD1306_COLUMNADDR, 
                    0x00,           // Column start address
                    WIDTH - 1};  // Column end address
                    
                this->displayCommandList(list2, sizeof(dlist0));
                this->displayCommandList(list2, sizeof(list2));
                this->displayCommandList(dlist1, sizeof(dlist1));

                
                for (uint16_t i=0; i<(WIDTH*HEIGHT/8); i++) {
                    i2c->write(this->address, &controlByte, 1);
                    i2c->write(this->address, &testChar, 1);
                }
                //i2c->unlock();
                break;
            case 'a':
            if(contraste != 0xFF){
                contraste += 0x01;
                contrastList[1] = contraste;
                this->displayCommandList(contrastList, 2);
            }
            break;
            case 'b':
            if(contraste != 0x00){
                contraste -= 0x01;
                contrastList[1] = contraste;
                this->displayCommandList(contrastList, 2);
            }
            break;
            case 'c':
                magicInit();
            break;

            case '1':
                this->displayCommand(0xA4);
            break;
            case '2':
                this->displayCommand(0xA5);
            break;
            case '3':
                this->displayCommand(0xA6);
            break;
            case '4':
                this->displayCommand(0xA7);
            break;
            case '5':                    
                this->displayCommand(SSD1306_RIGHT_HORIZONTAL_SCROLL); //Commando de Right Horizontal scroll
                this->displayCommand(0x00); //Dummy byte
                this->displayCommand(0x00); //Defino la pagina
                this->displayCommand(0x07); 
                this->displayCommand(0x0F); 
                this->displayCommand(0x00);
                this->displayCommand(0xFF);
                this->displayCommand(0x2F);
            break;
            case '6':
                this->displayCommand(SSD1306_LEFT_HORIZONTAL_SCROLL); //Commando de Left Horizontal scroll
                this->displayCommand(0x00); // Dummy byte
                this->displayCommand(0x00); // Defino inicio de pagina
                this->displayCommand(0x00); // Defino el intervalo entre cada scroll 
                this->displayCommand(0x0F); // Defino fin de pagina
                this->displayCommand(0x00); // Dummy byte
                this->displayCommand(0xFF); // Dummy byte
                this->displayCommand(0x2F); // Activo scroll
            break;
            case '7':
                this->displayCommand(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL); //Commando de Up Horizontal scroll
                this->displayCommand(0x00); // Dummy byte
                this->displayCommand(0x00); // Defino inicio de pagina
                this->displayCommand(0x00); // Defino el intervalo entre cada scroll 
                this->displayCommand(0x0F); // Defino fin de pagina
                this->displayCommand(0x01); // Dummy byte
                this->displayCommand(0xFF); // Dummy byte
                this->displayCommand(0x2F); // Activo scroll
            break;
            case '8':
                this->displayCommand(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL); //Commando de Up Horizontal scroll
                this->displayCommand(0x00); // Dummy byte
                this->displayCommand(0x00); // Defino inicio de pagina
                this->displayCommand(0x00); // Defino el intervalo entre cada scroll 
                this->displayCommand(0x0F); // Defino fin de pagina
                this->displayCommand(0x01); // Dummy byte
                this->displayCommand(0xFF); // Dummy byte
                this->displayCommand(0x2F); // Activo scroll
            break;
            case '9':
                this->displayCommand(SSD1306_DEACTIVATE_SCROLL);
            break;
        }
        //i2c->write(this->address, &receivedChar, 1);
    }
}
bool SSD1306::displayInit(displayConnection_t connection){
    this->connection = connection;
    if( this->connection == DISPLAY_CONNECTION_I2C_SSD1306_OLED) {
        this->address = SSD1306_I2C_BUS_8BIT_WRITE_ADDRESS << 1;
        this->i2c->frequency(100000); //Tomi: fmax=400k por hoja de datos     
    }

    initial8BitCommunicationIsCompleted = false;  
    //if ((!buffer) && !(buffer = (char *)malloc(WIDTH * ((HEIGHT + 7) / 8)))) // Tomi: WIDTH * ((HEIGHT + 7) / 8) es una matriz de WIDTH x HEIGHT
                                                                                //       al sumar 7 si HEIGHT no es multiplo de 8 redondeamos para arriba.
      //  return false;
    char b [] = {
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
    buffer = b;
   // clearDisplay();
  /*
   //--- Secuencia de inicio segun hoja de datos
    // 1- Set MUX Ratio
    char commandoTmp[] = {SSD1306_SETMULTIPLEX,0x80};
    displayCommandList(commandoTmp, 2);

    // 2- Set Display Offset
    commandoTmp[0] = SSD1306_SETDISPLAYOFFSET;
    commandoTmp[1] = 0x00;
    displayCommandList(commandoTmp, 2);

    // 3- Set Display Start Line
    displayCommand(SSD1306_SETSTARTLINE);
    
    // 4- Set Segment re-map
    displayCommand(SSD1306_SEGREMAP | 0x1); // Al parecer es lo mismo utilizar cualquiera de los valores

    // 5- Set COM Output Scan Direction
    displayCommand(SSD1306_COMSCANINC);

    // 6- Set COM Pins hardware configuration
    char comPins = 0x12;
    
    if ((WIDTH == 128) && (HEIGHT == 32)) {
      comPins = 0x02;
    } else if ((WIDTH == 128) && (HEIGHT == 64)) {
      comPins = 0x12;
    } else if ((WIDTH == 96) && (HEIGHT == 16)) {
      comPins = 0x2; // ada x12
    } else {
      // Other screen varieties -- TBD
    }
    commandoTmp[0] = SSD1306_SETCOMPINS;
    commandoTmp[1] = comPins;
    displayCommandList(commandoTmp, 2);

    // 7- Set Contrast Control    
    commandoTmp[0] = SSD1306_SETCONTRAST;
    commandoTmp[1] = 0x8F;                  //Puede ser un valor de 0x00 a 0xFF 
    displayCommandList(commandoTmp, 2);

    // 8- Disable Entire Display On
    displayCommand(SSD1306_DISPLAYALLON_RESUME);

    // 9- Set Normal Display
    displayCommand(SSD1306_NORMALDISPLAY);

    // 10- Set Osc Frecuency    
    commandoTmp[0] = SSD1306_SETDISPLAYCLOCKDIV;
    commandoTmp[1] = 0x7F;                      //Puede ser un valor de 0x00 a 0xFF 
    displayCommandList(commandoTmp, 2);

    // 11- Enable change pump regulator
    commandoTmp[0] = SSD1306_CHARGEPUMP;
    commandoTmp[1] = 0x14;                      
    displayCommandList(commandoTmp, 2);    

    // 12- Display ON
    displayCommand(SSD1306_DISPLAYON);
  */

    // Init sequence  
    // Init
    int _reset = 1;
    wait_us(10);
    _reset = 0;
    wait_us(100);
    _reset = 1;   

    static const char init1[] = {SSD1306_DISPLAYOFF,          // 0xAE
                               SSD1306_SETDISPLAYCLOCKDIV,  // 0xD5
                               0x80, // the suggested ratio 0x80
                               SSD1306_SETMULTIPLEX};       // 0xA8

    displayCommandList(init1, sizeof(init1));
    displayCommand(HEIGHT - 1);

    static const char init2[] = {SSD1306_SETDISPLAYOFFSET,    // 0xD3
                               0x0,                         // no offset
                               SSD1306_SETSTARTLINE | 0x0,  // line #0
                               SSD1306_CHARGEPUMP};         // 0x8D   

    displayCommandList(init2, sizeof(init2));

    displayCommand(0x14);
    displayCommand(SSD1306_DISPLAYON);

    static const char init3[] = {SSD1306_MEMORYMODE, // 0x20
                                            0x00, // 0x0 act like ks0108
                                            SSD1306_SEGREMAP | 0x1,
                                            SSD1306_COMSCANDEC};
    displayCommandList(init3, sizeof(init3));

    this->contraste = 0x9F;

    displayCommand(SSD1306_SETCOMPINS);
    displayCommand(0x12);
    displayCommand(SSD1306_SETCONTRAST);
    displayCommand(contraste);

    displayCommand(SSD1306_SETPRECHARGE); // 0xd9
    displayCommand(0xF1);
    static const char init5[] = {
        SSD1306_SETVCOMDETECT, // 0xDB
        0x40,
        SSD1306_DISPLAYALLON_RESUME, // 0xA4
        SSD1306_NORMALDISPLAY,       // 0xA6
        SSD1306_DEACTIVATE_SCROLL,
        SSD1306_DISPLAYON // Main screen turn on  
    };  
    displayCommandList(init5, sizeof(init5));
    //displayCommand(SSD1306_DISPLAYOFF);
    //displayCommand(SSD1306_DISPLAYALLON);

    return true; //Retorno que esta todo ok
}

//=====[Implementations of private functions]==================================

void SSD1306::clearDisplay(){
    memset(buffer, 0, WIDTH * ((HEIGHT + 7) / 8)); // Tomi: WIDTH * ((HEIGHT + 7) / 8) es una matriz de WIDTH x HEIGHT
                                                   //       al sumar 7 redondeamos hacia arriba el número de bytes.
                                                   //       (IMPORTANTE: Esto siempre que el malloc lo hagamos
                                                   //       siguiendo esta logica)
}

void SSD1306::displayData(char data){
    char controlByte = 0x40; // 0x40 = Indica que se enviara un dato. Más info leer datasheet ssd1306.
    const char dataSSD1306 [] ={controlByte, data};
    switch(this->connection) {
        case DISPLAY_CONNECTION_I2C_SSD1306_OLED:
            i2c->write(this->address, dataSSD1306, 2);
            break;
        case DISPLAY_CONNECTION_3WIRES_SPI_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_4WIRES_SPI_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_8BITS_SERIE_8080_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_8BITS_SERIE_6800_SSD1306_OLED:
            break;
    }
}
void SSD1306::displayCommand(char command){
    char controlByte = 0x00; // 0x00 = Indica que se enviara un comando. Más info leer datasheet ssd1306.
    const char commandSSD1306 [] ={controlByte, command};
    switch(this->connection) {
        case DISPLAY_CONNECTION_I2C_SSD1306_OLED:
            i2c->write(this->address, commandSSD1306, 2);
            break;
        case DISPLAY_CONNECTION_3WIRES_SPI_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_4WIRES_SPI_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_8BITS_SERIE_8080_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_8BITS_SERIE_6800_SSD1306_OLED:
            break;
    }
}

void SSD1306::displayCommandList(const char *command, uint8_t commandLen){
    char controlByte = 0x00; // 0x00 = Indica que se enviará un comando. Más info leer datasheet ssd1306.
    char commandList[commandLen + 1];
    char *ptr = commandList;

    commandList[0] = controlByte;
    for (int i = 1; i <= commandLen; i++) {
        ptr++;
        *ptr = command[i-1];
    }
    

    switch (this->connection) {
        case DISPLAY_CONNECTION_I2C_SSD1306_OLED:
            i2c->write(this->address, commandList, commandLen+1);
            break;
        case DISPLAY_CONNECTION_3WIRES_SPI_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_4WIRES_SPI_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_8BITS_SERIE_8080_SSD1306_OLED:
            break;
        case DISPLAY_CONNECTION_8BITS_SERIE_6800_SSD1306_OLED:
            break;
    }
}


void SSD1306::display(void) {
   static const char dlist1[] = {
      SSD1306_PAGEADDR,
      0,                      // Page start address
      (HEIGHT / 8) - 1,                  
      SSD1306_COLUMNADDR, 0}; // Column start address
    displayCommandList(dlist1, sizeof(dlist1));
    displayCommand(WIDTH - 1); // Column end address

    char c = 0x40;
    char *cptr = &c;
    char *ptr = buffer;

    for (uint16_t i=0; i<(WIDTH*HEIGHT/8); i++) {
      // send a bunch of data in one xmission

      i2c->write(this->address,cptr,1);

      for (uint8_t x=0; x<16; x++) {
        i2c->write(this->address,ptr,1);
        ptr++;
      }
      
      i--;
    }
}

void SSD1306::drawBitmap(int16_t x, int16_t y, const char bitmap[], int16_t w, int16_t h, uint16_t color){

    int16_t byteWidth = (w + 7) / 8;    // Calcula el ancho en bytes de una línea del bitmap (se redondea hacia arriba 
                                        // para asegurar que se reserve suficiente memoria).
    uint8_t b = 0;                      // Byte actual del bitmap

    for (int16_t j = 0; j < h; j++, y++) { // Itera sobre cada línea vertical del bitmap
      for (int16_t i = 0; i < w; i++) { // Itera sobre cada pixel horizontal en una línea
        if (i & 7) // Si no es un múltiplo de 8 (es decir, no es el primer pixel del byte actual)
          b <<= 1; // Desplaza los bits a la izquierda en el byte actual
        else
          b = bitmap[j * byteWidth + i / 8]; // Obtiene el siguiente byte del bitmap
        if (b & 0x80) // Comprueba si el bit más significativo del byte actual está encendido
          writePixel(x + i, y, color); // Escribe el pixel en la posición (x + i, y) con el color especificado
      }
    }
}

void SSD1306::writePixel(int16_t x, int16_t y, uint16_t color) {
    drawPixel(x, y, color);
}

void SSD1306::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if (buffer) {
    if ((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT))
      return;

    char *ptr = &buffer[(x / 8) + y * ((WIDTH + 7) / 8)];

    if (color)
      *ptr |= 0x80 >> (x & 7);
    else
      *ptr &= ~(0x80 >> (x & 7));
    }
}