#include <Arduino.h>
#include <avr/pgmspace.h>

#ifndef TFT_h
#define TFT_h

#define MEGA

//Basic Colors
#define RED			0xf800
#define GREEN		0x07e0
#define BLUE		0x001f
#define BLACK		0x0000
#define YELLOW		0xffe0
#define WHITE		0xffff
#define CYAN		0x07ff	
#define BRIGHT_RED	0xf810	
#define GRAY1		0x8410  
#define GRAY2		0x4208 
#define ORANGE		0xFBE0
#define BROWN		0x79E0
#define PINK		0xF81F
#define PURPLE		0x8010
 

//TFT resolution 240*320
#define MIN_X	0
#define MIN_Y	0
#define MAX_X	240
#define MAX_Y	320

/*/==================/CS=====================
#define DDR_CS      DDRB
#define PORT_CS     PORTB					//pin8 - pin13 (6bit)
#define CS_BIT      0x10					//0001 0000
#define CS_OUTPUT   {DDR_CS|=CS_BIT;}		//0001 0000
#define CS_HIGH     {PORT_CS|=CS_BIT;}		//0001 0000
#define CS_LOW      {PORT_CS&=~CS_BIT;}		//0000 0000*/

//------------------RS----------------------

#define DDR_RS      DDRB
#define PORT_RS     PORTB
#define RS_BIT      0x20					//0010 0000
#define RS_OUTPUT   {DDR_RS|=RS_BIT;}		//0010 0000
#define RS_HIGH     {PORT_RS|=RS_BIT;}		//0010 0000
#define RS_LOW      {PORT_RS&=~RS_BIT;}		//0000 0000

//------------------WR----------------------

#define DDR_WR      DDRB
#define PORT_WR     PORTB
#define WR_BIT      0x40									//0100 0000
#define WR_OUTPUT   {DDR_WR|=WR_BIT;}						//0100 0000
#define WR_HIGH     {PORT_WR|=WR_BIT;}						//0100 0000
#define WR_LOW      {PORT_WR&=~WR_BIT;}						//0000 0000
#define WR_RISING   {PORT_WR|=WR_BIT;PORT_WR&=~WR_BIT;}		//0100 0000;0100 0000&1011 1111 =0000 0000

//------------------RD---------------------

#define DDR_RD      DDRB
#define PORT_RD     PORTB
#define RD_BIT      0x80									//1000 0000
#define RD_OUTPUT   {DDR_RD|=RD_BIT;}						//1000 0000
#define RD_HIGH     {PORT_RD|=RD_BIT;}						//1000 0000
#define RD_LOW      {PORT_RD&=~RD_BIT;}						//0000 0000
#define RD_RISING   {PORT_RD|=RD_BIT;PORT_RD&=~RD_BIT;}		//0000 0000
//========================================


/**Macro definitions for char display direction**/
#define LEFT2RIGHT 0
#define DOWN2UP    1
#define RIGHT2LEFT 2
#define UP2DOWN    3

extern unsigned char simpleFont[][8];

class TFT
{
public:

    void init (void);
    void paintScreenBlack(void);
    void sendCommand(unsigned int index);
    void sendData(unsigned int data);
    void pushData(unsigned char data);
    unsigned char getData(void);
    unsigned int readRegister(unsigned int index);

    void setXY(unsigned int poX, unsigned int poY);
    void setPixel(unsigned int poX, unsigned int poY,unsigned int color);
    void drawLine(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int color);
    void drawVerticalLine(unsigned int poX, unsigned int poY,unsigned int length,unsigned int color);
    void drawHorizontalLine(unsigned int poX, unsigned int poY,unsigned int length,unsigned int color);
    void drawRectangle(unsigned int poX, unsigned int poY, unsigned int length,unsigned int width,unsigned int color);
    void fillRectangle(unsigned int poX, unsigned int poY, unsigned int length, unsigned int width, unsigned int color);
    void drawCircle(int poX, int poY, int r,unsigned int color);
    void fillCircle(int poX, int poY, int r,unsigned int color);
    void clockCircle(int poX, int poY, int r,unsigned int color);
    void drawChar(unsigned char ascii,unsigned int poX, unsigned int poY,unsigned int size, unsigned int fgcolor);
    void drawString(char *string,unsigned int poX, unsigned int poY,unsigned int size,unsigned int fgcolor);
    
    void all_pin_input(void);
    void all_pin_output(void);
    void all_pin_low(void);

    void setOrientation(unsigned int HV);
    void setDisplayDirect(unsigned char = LEFT2RIGHT);
private:
    void exitStandBy(void);
    unsigned char DisplayDirect;
};

extern TFT Tft;

#endif

