typedef unsigned short u16;

#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE_3 3
#define BG2_EN (1<<10)

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

extern u16 *videoBuffer;
extern const unsigned char fontdata_6x8[12288];

#define COLOR(R,G,B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   COLOR(0 , 0 , 0 )
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0 , 0 )
#define GREEN   COLOR(0 , 31, 0 )
#define BLUE    COLOR(0 , 0 , 31)
#define YELLOW  COLOR(31, 31, 0 )
#define MAGENTA COLOR(31, 0 , 31)
#define CYAN    COLOR(0 , 31, 31)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)
#define OFFSET(r, c, rowlen) ((r)*(rowlen) + (c))

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130


typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;


// Defines
#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

typedef struct {
	int row;
	int col;
	int height;
	int width;
	unsigned short color;
} LOG;

typedef struct {
	int row;
	int col;
	int height;
	int width;
	unsigned short color;
} BALL;

typedef struct {
	int row;
	int col;
	int height;
	int width;
	int isActive;
	unsigned short color;
} DIAMOND;

// Prototypes
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);
void waitForVBlank();
void drawScreen(int row, const unsigned short *image);
void drawImage(int row, int col, int width,
	int height, const unsigned short *image);
void drawDiamond(int row, int col, int height, int width, u16 color);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);
void fillScreen(volatile u16 color);
int hitLog(LOG l, BALL b);
int hitDiamond(BALL b, DIAMOND d);
