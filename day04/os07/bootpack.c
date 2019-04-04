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
//|     C 函数声明     |
//---------------------
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0,
              int x1, int y1);

//---------------------
//|       主方法      |
//---------------------
void HariMain(void) {
    char *p;

    // 初始化调色板
    init_palette();

    p = (char *)0xa0000;

    // 绘制3个矩形
    boxfill8(p, 320, COL8_FF0000, 20, 20, 120, 120);
    boxfill8(p, 320, COL8_00FF00, 70, 50, 170, 150);
    boxfill8(p, 320, COL8_0000FF, 120, 80, 220, 180);

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