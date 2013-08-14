#include "TFT.h" 

void TFT::pushData(unsigned char data)
{
    all_pin_low();

    //E = pin0,1,2,3,5
    //G = pin4,39,40,41
    //H = pin6,7,8,9,16,17
    //data1
    //data2
    //data?
    PORTE |= ((data<<4) & (0x30));		//data shift l4 & 0011 0000
    PORTG |= ((data<<3) & (0x20));		//data shift l3 & 0010 0000
    PORTE |= ((data & 0x08));			//data &		  0000 1000
    PORTH |= ((data>>1) & (0x78));		//data shift r1 & 0111 1000
}

/*unsigned char TFT::getData(void)
{
    unsigned char data=0;
    delay(1);
    data |= ((PIND&0xfc)>>2);			//(pind & 1111 1100) shift r2
    data |= ((PINB&0x03)<<6);			//(pinB & 0000 0011) shift l6
    return data;
}*/

void TFT::sendCommand(unsigned int index)
{
    //CS_LOW;								//0000 0000
    RS_LOW;								//0000 0000
    RD_HIGH;							//1000 0000
    //WR_HIGH;							//0100 0000
    WR_LOW;								//0000 0000
    //pushData(0);						//0000 0000
    //WR_HIGH;							//0100 0000
   // WR_LOW;								//0000 0000
    pushData(index&0xff);				//(index & 1111 1111)
    WR_HIGH;							//0100 0000
    //CS_HIGH;							//0001 0000
}

void TFT::sendData(unsigned int data)
{
    //CS_LOW;								//0000 0000
    RS_HIGH;							//0010 0000
    RD_HIGH;							//1000 0000

    WR_LOW;								//0000 0000
    pushData((data&0xff00)>>8);			//(data & 1111 1111 0000 0000) shift r8
    //WR_HIGH;							//0100 0000
    //WR_LOW;								//0000 0000
    pushData(data&0xff);				//data & 1111 1111
    WR_HIGH;							//0100 0000
    //CS_HIGH;							//00010 0000
}

/*unsigned int TFT::readRegister(unsigned int index)
{
    unsigned int data=0;

    //CS_LOW;								//0000 0000
    RS_LOW;								//0000 0000
    RD_HIGH;							//1000 0000
    all_pin_output();
    WR_LOW;								//0000 0000
    pushData(0);
    //WR_HIGH;							//0100 0000
    //WR_LOW;								//0000 0000
    pushData(index);
    //WR_HIGH;							//0100 0000
    all_pin_input();
    all_pin_low();
    RS_HIGH;							//0010 0000
    //RD_LOW;								//0000 0000
    //RD_HIGH;							//1000 0000
    data |= getData()<<8;				//get data shift l8
    //RD_LOW;								//0000 0000
    //RD_HIGH;							//1000 0000
    data |= getData();
    CS_HIGH;							//0010 0000
    all_pin_output();
    return data;
}*/

void  TFT::init (void)
{
    //CS_OUTPUT;
    RD_OUTPUT;
    WR_OUTPUT;
    RS_OUTPUT;

    Tft.all_pin_output();
    Tft.all_pin_low();

   delay(10);


    sendCommand(0x0001);
    sendData(0x0100);
    sendCommand(0x0002);
    sendData(0x0700);
    sendCommand(0x0003);
    sendData(0x1030);
    sendCommand(0x0004);
    sendData(0x0000);
    sendCommand(0x0008);
    sendData(0x0302);
    sendCommand(0x000A);
    sendData(0x0000);
    sendCommand(0x000C);
    sendData(0x0000);
    sendCommand(0x000D);
    sendData(0x0000);
    sendCommand(0x000F);
    sendData(0x0000);

    delay(10);

    sendCommand(0x0030);
    sendData(0x0000);
    sendCommand(0x0031);
    sendData(0x0405);
    sendCommand(0x0032);
    sendData(0x0203);
    sendCommand(0x0035);
    sendData(0x0004);
    sendCommand(0x0036);
    sendData(0x0B07);
    sendCommand(0x0037);
    sendData(0x0000);
    sendCommand(0x0038);
    sendData(0x0405);
    sendCommand(0x0039);
    sendData(0x0203);
    sendCommand(0x003c);
    sendData(0x0004);
    sendCommand(0x003d);
    sendData(0x0B07);
    sendCommand(0x0020);
    sendData(0x0000);
    sendCommand(0x0021);
    sendData(0x0000);
    sendCommand(0x0050);
    sendData(0x0000);
    sendCommand(0x0051);
    sendData(0x00ef);
    sendCommand(0x0052);
    sendData(0x0000);
    sendCommand(0x0053);
    sendData(0x013f);

    delay(10);

    sendCommand(0x0060);
    sendData(0xa700);
    sendCommand(0x0061);
    sendData(0x0001);
    sendCommand(0x0090);
    sendData(0x003A);
    sendCommand(0x0095);
    sendData(0x021E);
    sendCommand(0x0080);
    sendData(0x0000);
    sendCommand(0x0081);
    sendData(0x0000);
    sendCommand(0x0082);
    sendData(0x0000);
    sendCommand(0x0083);
    sendData(0x0000);
    sendCommand(0x0084);
    sendData(0x0000);
    sendCommand(0x0085);
    sendData(0x0000);
    sendCommand(0x00FF);
    sendData(0x0001);
    sendCommand(0x00B0);
    sendData(0x140D);
    sendCommand(0x00FF);
    sendData(0x0000);
    delay(10);
    sendCommand(0x0007);
    sendData(0x0133);
    delay(10);
    exitStandBy();
    sendCommand(0x0022);

    //paint screen black
    paintScreenBlack();
}

void TFT::paintScreenBlack(void)
{
    for(unsigned char i=0;i<2;i++)
    {
        for(unsigned int f=0;f<38400;f++)
        {
            sendData(BLACK);
        }
    }
}

void TFT::exitStandBy(void)
{
    sendCommand(0x0010);
    sendData(0x14E0);
    delay(10);
    sendCommand(0x0007);
    sendData(0x0133);
}

void TFT::setOrientation(unsigned int HV)//horizontal or vertical
{
    sendCommand(0x03);
    if(HV==1)//vertical
    {
        sendData(0x5038);
    }
    else//horizontal
    {
        sendData(0x5030);
    }
    sendCommand(0x0022); //Start to write to display RAM
}

void TFT::setDisplayDirect(unsigned char Direction) 
{
  DisplayDirect = Direction;
}

void TFT::setXY(unsigned int poX, unsigned int poY)
{
    sendCommand(0x0020);//X
    sendData(poX);
    sendCommand(0x0021);//Y
    sendData(poY);
    sendCommand(0x0022);//Start to write to display RAM
}

void TFT::setPixel(unsigned int poX, unsigned int poY,unsigned int color)
{
    setXY(poX,poY;)
    sendData(color);
}

void TFT::drawCircle(int poX, int poY, int r,unsigned int color)
{
    int x = -r, y = 0, err = 2-2*r, e2; 
    do {
        setPixel(poX-x, poY+y,color); 
        setPixel(poX+x, poY+y,color); 
        setPixel(poX+x, poY-y,color); 
        setPixel(poX-x, poY-y,color); 
        e2 = err;
        if (e2 <= y) { 
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0; 
        }
        if (e2 > x) err += ++x*2+1; 
    } while (x <= 0);
}

/*void TFT::fillCircle(int poX, int poY, int r,unsigned int color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    int poXinv = poY, poYinv = poX;
            Tft.fillRectangle(50,100,140,140,RED);
    do {

        Tft.drawVerticalLine(poXinv-x,poYinv-y,2*y,RED);
        Tft.drawVerticalLine(poXinv+x,poYinv-y,2*y,RED);
        
        Tft.drawHorizontalLine(poY-y,poX-x,2*y,RED);
        Tft.drawHorizontalLine(poY-y,poX+x,2*y,RED);


        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= -r*0.70);

}*/




void TFT::drawLine(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int color)
{
    int x = x1-x0;
    int y = y1-y0;
    int dx = abs(x), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2; /* error value e_xy */
    for (;;){ /* loop */
        setPixel(x0,y0,color);
        e2 = 2*err;
        if (e2 >= dy) { /* e_xy+e_x > 0 */
            if (x0 == x1) break;
            err += dy; x0 += sx;
        }
        if (e2 <= dx) { /* e_xy+e_y < 0 */
            if (y0 == y1) break;
            err += dx; y0 += sy;
        }
    }
}


void TFT::drawVerticalLine(unsigned int poX, unsigned int poY,unsigned int length,unsigned int color)
{
    setXY(poX,poY);
    setOrientation(1);
    if(length+poY>MAX_Y)
    {
        length=MAX_Y-poY;
    }

    for(unsigned int i=0;i<length;i++)
    {
        sendData(color);
    }
}

void  TFT::drawHorizontalLine(unsigned int poX, unsigned int poY,unsigned int length,unsigned int color)
{
    setXY(poX,poY);
    setOrientation(0);
    if(length+poX>MAX_X)
    {
        length=MAX_X-poX;
    }
    for(unsigned int i=0;i<length;i++)
    {
        sendData(color);
    }
}


void TFT::drawRectangle(unsigned int poX, unsigned int poY, unsigned int length,unsigned int width,unsigned int color)
{
    drawHorizontalLine(poX, poY, length, color);
    drawHorizontalLine(poX, poY+width, length, color);

    drawVerticalLine(poX, poY, width,color);
    drawVerticalLine(poX + length, poY, width,color);
}

void TFT::fillRectangle(unsigned int poX, unsigned int poY, unsigned int length, unsigned int width, unsigned int color)
{
    for(unsigned int i=0;i<width;i++)
    {
        if(DisplayDirect == LEFT2RIGHT)
          drawHorizontalLine(poX, poY+i, length, color);
          else if (DisplayDirect ==  DOWN2UP)
            drawHorizontalLine(poX, poY-i, length, color);
            else if(DisplayDirect == RIGHT2LEFT)
              drawHorizontalLine(poX, poY-i, length, color);
              else if(DisplayDirect == UP2DOWN)
                drawHorizontalLine(poX, poY+i, length, color);
              
    }
}

void TFT::drawChar(unsigned char ascii,unsigned int poX, unsigned int poY,unsigned int size, unsigned int fgcolor)
{
    
    setXY(poX,poY);
    
    if((ascii < 0x20)||(ascii > 0x7e))//Unsupported char.
    {
        ascii = '?';
    }
    for(unsigned char i=0;i<8;i++)
    {
        unsigned char temp = pgm_read_byte(&simpleFont[ascii-0x20][i]);
        for(unsigned char f=0;f<8;f++)
        {
            if((temp>>f)&0x01)
            {
                if(DisplayDirect == LEFT2RIGHT)
                  fillRectangle(poX+i*size, poY+f*size, size, size, fgcolor);
                  else if(DisplayDirect == DOWN2UP)
                    fillRectangle(poX+f*size, poY-i*size, size, size, fgcolor);
                    else if(DisplayDirect == RIGHT2LEFT)
                      fillRectangle(poX-i*size, poY-f*size, size, size, fgcolor);
                      else if(DisplayDirect == UP2DOWN)
                        fillRectangle(poX-f*size, poY+i*size, size, size, fgcolor);
            }

        }
    }
}

void TFT::drawString(char *string,unsigned int poX, unsigned int poY,unsigned int size,unsigned int fgcolor)
{
    while(*string)
    {
        for(unsigned char i=0;i<8;i++)
        {
            drawChar(*string, poX, poY, size, fgcolor);
        }
        *string++;
        if(DisplayDirect == LEFT2RIGHT)
        {
          if(poX < MAX_X)
          {
              poX+=8*size; // Move cursor right
          }
        }
          else if(DisplayDirect == DOWN2UP)
          {
            if(poY > 0)
            {
                poY-=8*size; // Move cursor right
            }
          }
          else if(DisplayDirect == RIGHT2LEFT)
        {
          if(poX > 0)
          {
              poX-=8*size; // Move cursor right
          }
        }
          else if(DisplayDirect == UP2DOWN)
          {
            if(poY < MAX_Y)
            {
                poY+=8*size; // Move cursor right
            }
          }
          
          

    }
}

void TFT::all_pin_input(void)
{
    DDRE &=~ 0x38;
    DDRG &=~ 0x20;
    DDRH &=~ 0x78;
}

void TFT::all_pin_output(void)
{
    DDRE |= 0x38;
    DDRG |= 0x20;
    DDRH |= 0x78;
}

void TFT::all_pin_low(void)
{
    PORTE &=~ 0x38;
    PORTG &=~ 0x20;
    PORTH &=~ 0x78;
}

TFT Tft=TFT();
