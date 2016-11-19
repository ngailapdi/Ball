//Name: NGOC ANH THAI
#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int r, int c, unsigned short color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;
}



void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = (&videoBuffer[OFFSET(row+r, col, 240)]);
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}


void waitForVBlank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

// Draw one row of the screen with DMA
void drawScreen(int row, const unsigned short *image) {
	DMA[3].src = &(image[row * 240]);
  	DMA[3].dst = videoBuffer + 240 * row;
  	DMA[3].cnt = (240 * 160) |
                             DMA_SOURCE_INCREMENT |
                             DMA_DESTINATION_INCREMENT |
                             DMA_ON;
}

void drawImage(int row, int col, int width,
	int height, const unsigned short *image) {
		for(int i = 0; i < height; i++) {
			DMA[3].src = &(image[i * width]);
		  	DMA[3].dst = videoBuffer + 240 * (row + i) + col;
		  	DMA[3].cnt = width |
		                             DMA_SOURCE_INCREMENT |
		                             DMA_DESTINATION_INCREMENT |
		                             DMA_ON;
		}
	}

void drawChar(int row, int col, char ch, u16 color) {
	for(int r = 0; r < 8; r++) {
		for(int c = 0; c < 6; c++) {
			if(fontdata_6x8[OFFSET(r, c, 6) + ch * 48]) {
				setPixel(row + r, col + c, color);
			}
		}
	}
}

void drawString(int row, int col, char *str, u16 color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

void drawDiamond(int row, int col, int height, int width, u16 color) {
	int start = 1;
	int mid = width/2+1;
	for (int i = 0; i <= height/2 + 1; i++) {
		for (int j = mid - (start-1)/2; j <= mid + (start-1)/2; j++) {
			setPixel(row + i, col + j, color);
		}
		start+=2;
	}
	start-=2;
	for (int i = height/2+1; i <= height; i++) {
		for (int j = mid-(start-1)/2; j <= mid + (start-1)/2; j++) {
			setPixel(row + i, col + j, color);
		}
		start-=2;
	}
}

void fillScreen(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}

int hitLog(LOG l, BALL b) {
		if ((b.row == l.row - l.height + 5)
			&& (b.col >= l.col && b.col <= l.col + l.width)) {
				return 1;
		}
		return 0;
}

int hitDiamond(BALL b, DIAMOND d) {
		if ((b.row < d.row + d.height + 10 && b.row > d.row - 10) && (b.col > d.col - 10 && b.col < d.col + d.width + 10)) {
				return 1;
		}
		return 0;
}
