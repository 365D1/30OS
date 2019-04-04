//---------------------
//|    汇编函数声明    |
//---------------------
void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

//---------------------
//|     C 函数声明     |
//---------------------
void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);

//---------------------
//|       主方法      |
//---------------------
void HariMain(void) {
    int i;
    char *p;

    // 初始化调色板
    init_palette();

    for (i = 0xa0000; i <= 0xaffff; i++) {
        p[i] = i & 0x0f;
    }

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