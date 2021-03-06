//---------------------
//|    汇编函数声明    |
//---------------------
void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

//---------------------
//|      定义颜色      |
//---------------------
#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

//---------------------
//|     结构体声明     |
//---------------------
struct BOOTINFO {
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
};

//---------------------
//|      函数声明      |
//---------------------
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0,
              int x1, int y1);
void init_screen(char *vram, int x, int y);

//---------------------
//|       主方法      |
//---------------------
void HariMain(void) {
    char *vram;
    int xsize, ysize;
    struct BOOTINFO *binfo;

    // 初始化调色板
    init_palette();

    binfo = (struct BOOTINFO *)0x0ff0;
    xsize = (*binfo).scrnx;
    ysize = (*binfo).scrny;
    vram = (*binfo).vram;

    init_screen(vram, xsize, ysize);

    for (;;) {
        io_hlt();
    }
}

// 初始化调色板
void init_palette(void) {
    static unsigned char table_rgb[16 * 3] = {
        0x00, 0x00, 0x00,  // 0:黑色
        0xff, 0x00, 0x00,  // 1:亮红
        0x00, 0xff, 0x00,  // 2:亮绿
        0xff, 0xff, 0x00,  // 亮黄
        0x00, 0x00, 0xff,  // 亮蓝
        0xff, 0x00, 0xff,  // 亮紫
        0x00, 0xff, 0xff,  // 浅蓝
        0xff, 0xff, 0xff,  // 白色
        0xc6, 0xc6, 0xc6,  // 亮灰
        0x84, 0x00, 0x00,  // 暗红
        0x00, 0x84, 0x00,  // 暗绿
        0x84, 0x84, 0x00,  // 暗黄
        0x00, 0x00, 0x84,  // 暗蓝
        0x84, 0x00, 0x84,  // 暗紫
        0x00, 0x84, 0x84,  // 浅暗蓝
        0x84, 0x84, 0x84   // 暗灰
    };
    set_palette(0, 15, table_rgb);
    return;
}

// 设置调色板
void set_palette(int start, int end, unsigned char *rgb) {
    int i, eflags;
    // 记录中断许可标志的值
    eflags = io_load_eflags();
    // 将中断许可标志设为0，禁止中断
    io_cli();
    io_out8(0x03c8, start);
    for (i = 0; i < end; i++) {
        io_out8(0x03c9, rgb[0] / 4);
        io_out8(0x03c9, rgb[1] / 4);
        io_out8(0x03c9, rgb[2] / 4);
        rgb += 3;
    }
    // 还原中断许可
    io_store_eflags(eflags);
    return;
}

// 画矩形方法
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0,
              int x1, int y1) {
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            vram[y * xsize + x] = c;
        }
    }
    return;
}

void init_screen(char *vram, int x, int y) {
    boxfill8(vram, x, COL8_008484, 0, 0, x - 1, y - 29);
    boxfill8(vram, x, COL8_C6C6C6, 0, y - 28, x - 1, y - 28);
    boxfill8(vram, x, COL8_FFFFFF, 0, y - 27, x - 1, y - 27);
    boxfill8(vram, x, COL8_C6C6C6, 0, y - 26, x - 1, y - 1);

    boxfill8(vram, x, COL8_FFFFFF, 3, y - 24, 59, y - 24);
    boxfill8(vram, x, COL8_FFFFFF, 2, y - 24, 2, y - 4);
    boxfill8(vram, x, COL8_848484, 3, y - 4, 59, y - 4);
    boxfill8(vram, x, COL8_848484, 59, y - 23, 59, y - 5);
    boxfill8(vram, x, COL8_000000, 2, y - 3, 59, y - 3);
    boxfill8(vram, x, COL8_000000, 60, y - 24, 60, y - 3);

    boxfill8(vram, x, COL8_848484, x - 47, y - 24, x - 4, y - 24);
    boxfill8(vram, x, COL8_848484, x - 47, y - 23, x - 47, y - 4);
    boxfill8(vram, x, COL8_FFFFFF, x - 47, y - 3, x - 4, y - 3);
    boxfill8(vram, x, COL8_FFFFFF, x - 3, y - 24, x - 3, y - 3);
    return;
}