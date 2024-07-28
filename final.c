/* This files provides address values that exist in the system */

#define BOARD                 "DE1-SoC"

/* Memory */
#define DDR_BASE              0x00000000
#define DDR_END               0x3FFFFFFF
#define A9_ONCHIP_BASE        0xFFFF0000
#define A9_ONCHIP_END         0xFFFFFFFF
#define SDRAM_BASE            0xC0000000
#define SDRAM_END             0xC3FFFFFF
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_ONCHIP_END       0xC803FFFF
#define FPGA_CHAR_BASE        0xC9000000
#define FPGA_CHAR_END         0xC9001FFF

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define JP1_BASE              0xFF200060
#define JP2_BASE              0xFF200070
#define PS2_BASE              0xFF200100
#define PS2_DUAL_BASE         0xFF200108
#define JTAG_UART_BASE        0xFF201000
#define JTAG_UART_2_BASE      0xFF201008
#define IrDA_BASE             0xFF201020
#define TIMER_BASE            0xFF202000
#define AV_CONFIG_BASE        0xFF203000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030
#define AUDIO_BASE            0xFF203040
#define VIDEO_IN_BASE         0xFF203060
#define ADC_BASE              0xFF204000

/* Cyclone V HPS devices */
#define HPS_GPIO1_BASE        0xFF709000
#define HPS_TIMER0_BASE       0xFFC08000
#define HPS_TIMER1_BASE       0xFFC09000
#define HPS_TIMER2_BASE       0xFFD00000
#define HPS_TIMER3_BASE       0xFFD01000
#define FPGA_BRIDGE           0xFFD0501C

/* ARM A9 MPCORE devices */
#define   PERIPH_BASE         0xFFFEC000    // base address of peripheral devices
#define   MPCORE_PRIV_TIMER   0xFFFEC600    // PERIPH_BASE + 0x0600

/* Interrupt controller (GIC) CPU interface(s) */
#define MPCORE_GIC_CPUIF      0xFFFEC100    // PERIPH_BASE + 0x100
#define ICCICR                0x00          // offset to CPU interface control reg
#define ICCPMR                0x04          // offset to interrupt priority mask reg
#define ICCIAR                0x0C          // offset to interrupt acknowledge reg
#define ICCEOIR               0x10          // offset to end of interrupt reg
/* Interrupt controller (GIC) distributor interface(s) */
#define MPCORE_GIC_DIST       0xFFFED000    // PERIPH_BASE + 0x1000
#define ICDDCR                0x00          // offset to distributor control reg
#define ICDISER               0x100         // offset to interrupt set-enable regs
#define ICDICER               0x180         // offset to interrupt clear-enable regs
#define ICDIPTR               0x800         // offset to interrupt processor targets regs
#define ICDICFR               0xC00         // offset to interrupt configuration regs

/* set a single pixel on the screen at x,y
 * x in [0,319], y in [0,239], and colour in [0,65535]
 */
#include<stdio.h>
#include<math.h>
int over=0;

int spx=0,spy=0;

int person1_x, person1_y;
int person2_x, person2_y;

int player1tower,player2tower;

void write_pixel(int x, int y, short colour) {
  volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
  *vga_addr=colour;
}

/* use write_pixel to set entire screen to black (does not clear the character buffer) */
void clear_screen() {
  int x, y;
  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
	  write_pixel(x,y,0xffffff);
	}
  }
}
void clear_screen1() {
  int x, y;
  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
	  write_pixel(x,y,0xf00000);
	}
  }
}

int all_screen[330][250];
void write_char(int x, int y, char c) ;
void one_block(int x, int y);
void one_block1(int x, int y);

void tower_base1(int x);
void tower_base2(int x);
void tower_base3(int x);
void tower_base4(int x);
void tower_base5(int x);
void tower_base6(int x);

void project_bullet1(int x, int y,int a, int b, int c, int d);
void projectile1( int power);

void project_bullet2(int x, int y,int a, int b, int c, int d);
void projectile2(int power);

int min(int a,int b);

void person1(int x,int y);
void person2(int x,int y);

int detect_block_x(int x);
int detect_block_y(int y);

void remove_block(int x, int y);
void remove_block_man(int x,int y);

void remove_block_man1(int x,int y);

void water();

void winner2();
void winner1();

void clear_projectile();
void specialpower1();
void home1();
void home2();
void startt();
void left_key_1();
void right_key_1();
void left_key_2();
void right_key_2();
// void write_char(int x1, int y1, char c1) {
//   // VGA character buffer
//   volatile char * character_buffer = (char *) (0x09000000 + (y1<<7) + x1);
//   *character_buffer = c1;
// }
// void clear_screen1() {
//   int x, y;
//   for (x = 0; x < 320; x++) {
//     for (y = 0; y < 240; y++) {
// 	  write_pixel(x,y,0xffffff);
// 	}
//   }
// }
// void clear_screen2() {
//   int x, y;
//   for (x = 0; x < 320; x++) {
//     for (y = 0; y < 240; y++) {
// 	  write_pixel(x,y,0xff0000);
// 	}
//   }
// }
// void clear_screen3() {
//   int x, y;
//   for (x = 0; x < 320; x++) {
//     for (y = 0; y < 240; y++) {
// 	  write_pixel(x,y,0x00fff0);
// 	}
//   }
// }
// void clear_screen4() {
//   int x, y;
//   for (x = 0; x < 320; x++) {
//     for (y = 0; y < 240; y++) {
// 	  write_pixel(x,y,0xf0ff0f);
// 	}
//   }
// }
// void clear_screen5() {
//   int x, y;
//   for (x = 0; x < 320; x++) {
//     for (y = 0; y < 240; y++) {
// 	  write_pixel(x,y,0xf0000f);
// 	}
//   }
// }

/* write a single character to the character buffer at x,y
 * x in [0,79], y in [0,59]
 */
void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000 + (y<<7) + x);
  *character_buffer = c;
}


void one_block(int x, int y){

    for(int i=x;i<x+10;i++){
        for(int j=y;j<y+10;j++){
            all_screen[i][j]=1;
            write_pixel(i,j,0x00FF00);
        }
    }

}


void one_block1(int x, int y){

    for(int i=x;i<x+10;i++){
        for(int j=y;j<y+10;j++){
            all_screen[i][j]=1;
            write_pixel(i,j,0x00FF00);
        }
    }

}


void tower_base1(int x){


    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);

    x += 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);

    x += 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);

}


void tower_base2(int x){


    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);

    x -= 10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);

    x-=10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);
    one_block1(x,160);
    one_block1(x,150);
    x-=10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);
    one_block1(x,160);
    one_block1(x,150);

    x-=10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);
    one_block1(x,160);
    one_block1(x,150);
    one_block1(x,140);
    one_block1(x,130);
    x-=10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);
    one_block1(x,160);
    one_block1(x,150);
    one_block1(x,140);
    one_block1(x,130);

    x-=10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);
    one_block1(x,160);
    one_block1(x,150);
    x-=10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);
    one_block1(x,160);
    one_block1(x,150);

    x-=10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);

    x -= 10;
    one_block1(x,200);
    one_block1(x,190);
    one_block1(x,180);
    one_block1(x,170);

}

void tower_base3(int x){


    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x += 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    x+=10;
    one_block(x,200);
    one_block(x,190);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);

    x += 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

}
void tower_base4(int x){


    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x -= 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    x-=10;
    one_block(x,200);
    one_block(x,190);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);

    x -= 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

}


void tower_base5(int x){


    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x += 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x+=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);

    x += 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

}
void tower_base6(int x){


    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x -= 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);
    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);
    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

    x-=10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);

    x -= 10;
    one_block(x,200);
    one_block(x,190);
    one_block(x,180);
    one_block(x,170);
    one_block(x,160);
    one_block(x,150);
    one_block(x,140);
    one_block(x,130);
    one_block(x,120);

}

void project_bullet1(int x, int y,int a, int b, int c, int d){


    for(int i=0;i<a;i++){
        if( y-4*i>0 && all_screen[x+i][y-4*i]==3) {
                winner1();
                return;
            }if(y-4*i>1 &&all_screen[x+i][y-4*i-1]==3) {
                winner1();

                return;
            }
            if(y-4*i>2 && all_screen[x+i][y-4*i-2]==3) {
                winner1();

                return;
            }
            if(y-4*i>3 && all_screen[x+i][y-4*i-3]==3) {
                winner1();

                return;
            }
        if( y-4*i>0 && all_screen[x+i][y-4*i]==1) {
                remove_block_man1(x+i,y-4*i);
                return;
            }if(y-4*i>1 &&all_screen[x+i][y-4*i-1]==1) {
                remove_block_man1(x+i,y-4*i-1);
                return;
            }
            if(y-4*i>2 && all_screen[x+i][y-4*i-2]==1) {
                remove_block_man1(x+i,y-4*i-2);
                return;
            }
            if(y-4*i>3 && all_screen[x+i][y-4*i-3]==1) {
                remove_block_man1(x+i,y-4*i-3);
                return;
            }
            if(y-4*i>0)  {write_pixel(x+i,y-4*i,0xf0000f);all_screen[x+i][y-4*i]=20;}
            if(y-4*i>1) {write_pixel(x+i,y-4*i-1,0xf0000f);all_screen[x+i][y-4*i-1]=20;}
            if(y-4*i>2) {write_pixel(x+i,y-4*i-2,0xf0000f);all_screen[x+i][y-4*i-2]=20;}
            if(y-4*i>3) {write_pixel(x+i,y-4*i-3,0xf0000f);all_screen[x+i][y-4*i-3]=20;}
        }
        x+=a;
        y-=4*a;

        for(int i=0;i<b;i++){
            if(y-3*i>0 && all_screen[x+i][y-3*i]==3) {
                winner1();
                return;
            }
            if(y-3*i>1 && all_screen[x+i][y-3*i-1]==3) {
                winner1();
                return;
            }
            if(y-3*i>2 && all_screen[x+i][y-3*i-2]==3) {
                winner1();
                return;
            }
            if(y-3*i>0 && all_screen[x+i][y-3*i]==1) {
                remove_block_man1(x+i,y-3*i);
                return;
            }if(y-3*i>1 && all_screen[x+i][y-3*i-1]==1) {
                remove_block_man1(x+i,y-3*i-1);
                return;
            }
            if(y-3*i>2 && all_screen[x+i][y-3*i-2]==1) {
                remove_block_man1(x+i,y-3*i-2);
                return;
            }
            if(y-3*i>0) {write_pixel(x+i,y-3*i,0xf0000f);all_screen[x+i][y-3*i]=20;}
            if(y-3*i>1) {write_pixel(x+i,y-3*i-1,0xf0000f);all_screen[x+i][y-3*i-1]=20;}
            if(y-3*i>2) {write_pixel(x+i,y-3*i-2,0xf0000f);all_screen[x+i][y-3*i-2]=20;}
        }
        x+=b;
        y-=3*b;

        for(int i=0;i<c;i++){
            if(y-2*i>0 && all_screen[x+i][y-2*i]==3) {
                winner1();
                return;
            }
            if(y-2*i>1 && all_screen[x+i][y-2*i-1]==3) {
                winner1();
                return;
            }
            if(y-2*i>0 && all_screen[x+i][y-2*i]==1) {
                remove_block_man1(x+i,y-2*i);
                return;
            }
            if(y-2*i>1 && all_screen[x+i][y-2*i-1]==1) {
                remove_block_man1(x+i,y-2*i-1);
                return;
            }
            if(y-2*i>0) {write_pixel(x+i,y-2*i,0xf0000f);all_screen[x+i][y-2*i]=20;}
            if(y-2*i>1) {write_pixel(x+i,y-2*i-1,0xf0000f);all_screen[x+i][y-2*i-1]=20;}
        }
        x+=c;
        y-=2*c;

        for(int i=0;i<d;i++){
            if(y-i>0 && all_screen[x+i][y-i]==3) {
                winner1();
                return;
            }
            if(y-i>0 && all_screen[x+i][y-i]==1) {
                remove_block_man1(x+i,y-i);
                return;
            }
            if(y-i>0) {write_pixel(x+i,y-i,0xf0000f);all_screen[x+i][y-i]=20;}
        }
        x+=d;
        y-=d;


        for(int i=0;i<5;i++){
            if(y>0) {write_pixel(x+i,y,0xf0000f);all_screen[x+i][y]=20;}
        }
        
        x += 5;

        for(int i=0;i<5;i++){
            if(y>0) {write_pixel(x+i,y,0xf0000f);all_screen[x+i][y]=20;}
        }
        
        x += 5;
        
        for(int i=0;i<d;i++){
            if(y+i>0 &&all_screen[x+i][y+i]==3) {
                winner1();
                return;
            }

            if(y+i>0 &&all_screen[x+i][y+i]==1) {
                remove_block_man1(x+i,y+i);
                return;
            }

            if(y+i>0) {write_pixel(x+i,y+i,0xf0000f);all_screen[x+i][y+i]=20;}
        }
        x+=d;
        y+=d;

        for(int i=0;i<c;i++){

            if(y+2*i>0 && all_screen[x+i][y+2*i]==3) {
                winner1();
                return;
            }if(y+2*i+1>0 && all_screen[x+i][y+2*i+1]==3) {
                winner1();
                return;
            }
            if(y+2*i>0 && all_screen[x+i][y+2*i]==1) {
                remove_block_man1(x+i,y+2*i);
                return;
            }if(y+2*i+1>0 && all_screen[x+i][y+2*i+1]==1) {
                remove_block_man1(x+i,y+2*i+1);
                return;
            }

            if(y+2*i>0) {write_pixel(x+i,y+2*i,0xf0000f);all_screen[x+i][y+2*i]=20;}
            if(y+2*i+1>0) {write_pixel(x+i,y+2*i+1,0xf0000f);all_screen[x+i][y+2*i+1]=20;}
        }
        x+=c;
        y+=2*c;


        for(int i=0;i<b;i++){


            if(y+3*i>0 && all_screen[x+i][y+3*i]==3) {
                winner1();
                return;
            }if(y+3*i+1>0 && all_screen[x+i][y+3*i+1]==3) {
                winner1();
                return;
            }
            if(y+3*i+2>0 && all_screen[x+i][y+3*i+2]==3) {
                winner1();
                return;
            }

            if(y+3*i>0 && all_screen[x+i][y+3*i]==1) {
                remove_block_man1(x+i,y+3*i);
                return;
            }if(y+3*i+1>0 && all_screen[x+i][y+3*i+1]==1) {
                remove_block_man1(x+i,y+3*i+1);
                return;
            }
            if(y+3*i+2>0 && all_screen[x+i][y+3*i+2]==1) {
                remove_block_man1(x+i,y+3*i+2);
                return;
            }

            if(y+3*i>0) {write_pixel(x+i,y+3*i,0xf0000f);all_screen[x+i][y+3*i]=20;}
            if(y+3*i+1>0) {write_pixel(x+i,y+3*i+1,0xf0000f);all_screen[x+i][y+3*i+1]=20;}
            if(y+3*i+2>0) {write_pixel(x+i,y+3*i+2,0xf0000f);all_screen[x+i][y+3*i+2]=20;}
        }
        x+=b;
        y+=3*b;

        for(int i=0;;i++){


            if( y+4*i>=240 || x+i>=320 ) break;

            if(y+4*i>0 && all_screen[x+i][y+4*i]==3) {
                winner1();
                return;
            }if(y+4*i+1>0 && all_screen[x+i][y+4*i+1]==3) {
                winner1();
                return;
            }
            if(y+4*i+2>0 && all_screen[x+i][y+4*i+2]==3) {
                winner1();
                return;
            }
            if(y+4*i+3>0 && all_screen[x+i][y+4*i+3]==3) {
                winner1();
                return;
            }

            if(y+4*i>0 && all_screen[x+i][y+4*i]==1) {
                spx=x+i,spy=y+4*i;
                remove_block_man1(x+i,y+4*i);
                return;
            }if(y+4*i+1>0 && all_screen[x+i][y+4*i+1]==1) {
                spx=x+i,spy=y+4*i+1;
                remove_block_man1(x+i,y+4*i+1);
                return;
            }
            if(y+4*i+2>0 && all_screen[x+i][y+4*i+2]==1) {
                spx=x+i,spy=y+4*i+2;
                remove_block_man1(x+i,y+4*i+2);
                return;
            }
            if(y+4*i+3>0 && all_screen[x+i][y+4*i+3]==1) {
                spx=x+i,spy=y+4*i+3;
                remove_block_man1(x+i,y+4*i+3);
                return;
            }
            if(y+4*i>0) {write_pixel(x+i,y+4*i,0xf0000f);all_screen[x+i][y+4*i]=20;}
            if(y+4*i+1>0) {write_pixel(x+i,y+4*i+1,0xf0000f);all_screen[x+i][y+4*i+1]=20;}
            if(y+4*i+2>0) {write_pixel(x+i,y+4*i+2,0xf0000f);all_screen[x+i][y+4*i+2]=20;}
            if(y+4*i+3>0) {write_pixel(x+i,y+4*i+3,0xf0000f);all_screen[x+i][y+4*i+3]=20;}
        }
        x+=a;
        y+=4*a;
}


void projectile1( int power){

  

    int x = person1_x;
    int y = person1_y+11;
    if(power == 0){
        project_bullet1(x,y,10,10,10,10);
    }
    else if(power == 1){
        project_bullet1(x,y,11,12,13,14);
    }
    else if(power == 2){
        project_bullet1(x,y,12,14,16,18);
    }
    else if(power == 3){
        project_bullet1(x,y,13,16,19,22);
    }
    else if(power == 4){
        project_bullet1(x,y,14,18,22,26);
    }
    else if(power == 5){
        project_bullet1(x,y,15,20,25,30);
    }
    else if(power == 6){
        project_bullet1(x,y,16,22,28,34);
    }
    else if(power == 7){
        project_bullet1(x,y,17,24,31,38);
    }
    else if(power == 8){
        project_bullet1(x,y,18,26,34,42);
    }
    else if(power == 9){
        project_bullet1(x,y,19,28,37,46);
    }
    water();

}

void project_bullet2(int x, int y,int a, int b, int c, int d){

    for(int i=0;i<320;i++){
        for(int j=0;j<240;j++){
            if(all_screen[i][j]==20){
                all_screen[i][j]=0;
                write_pixel(i,j,0xffffff);
            }
        }
    }

    for(int i=0;i<a;i++){
        if(y-4*i>0 && all_screen[x-i][y-4*i]==2) {
                winner2();
                return;
            }if(y-4*i>1 && all_screen[x-i][y-4*i-1]==2) {
                winner2();
                return;
            }
            if(y-4*i>2 && all_screen[x-i][y-4*i-2]==2) {
                winner2();
                return;
            }
            if(y-4*i>3 && all_screen[x-i][y-4*i-3]==2) {
                winner2();
                return;
            }
        if(y-4*i>0 && all_screen[x-i][y-4*i]==1) {
                remove_block_man(x-i,y-4*i);
                return;
            }if(y-4*i>1 && all_screen[x-i][y-4*i-1]==1) {
                remove_block_man(x-i,y-4*i-1);
                return;
            }
            if(y-4*i>2 && all_screen[x-i][y-4*i-2]==1) {
                remove_block_man(x-i,y-4*i-2);
                return;
            }
            if(y-4*i>3 && all_screen[x-i][y-4*i-3]==1) {
                remove_block_man(x-i,y-4*i-3);
                return;
            }
            if(y-4*i>0)  {write_pixel(x-i,y-4*i,0xf0000f);all_screen[x-i][y-4*i]=30;}
            if(y-4*i>1) {write_pixel(x-i,y-4*i-1,0xf0000f);all_screen[x-i][y-4*i-1]=30;}
            if(y-4*i>2) {write_pixel(x-i,y-4*i-2,0xf0000f);all_screen[x-i][y-4*i-2]=30;}
            if(y-4*i>3) {write_pixel(x-i,y-4*i-3,0xf0000f);all_screen[x-i][y-4*i-3]=30;}
        }
        x-=a;
        y-=4*a;

        for(int i=0;i<b;i++){
            if(y-3*i>0 && all_screen[x-i][y-3*i]==2) {
                winner2();
                return;
            }if(y-3*i>1 && all_screen[x-i][y-3*i-1]==2) {
                winner2();
                return;
            }
            if(y-3*i>2 && all_screen[x-i][y-3*i-2]==2) {
                winner2();
                return;
            }
            if(y-3*i>0 && all_screen[x-i][y-3*i]==1) {
                remove_block_man(x-i,y-3*i);
                return;
            }if(y-3*i>1 && all_screen[x-i][y-3*i-1]==1) {
                remove_block_man(x-i,y-3*i-1);
                return;
            }
            if(y-3*i>2 && all_screen[x-i][y-3*i-2]==1) {
                remove_block_man(x-i,y-3*i-2);
                return;
            }
            if(y-3*i>0) {write_pixel(x-i,y-3*i,0xf0000f);all_screen[x-i][y-3*i]=30;}
            if(y-3*i>1) {write_pixel(x-i,y-3*i-1,0xf0000f);all_screen[x-i][y-3*i-1]=30;}
            if(y-3*i>2) {write_pixel(x-i,y-3*i-2,0xf0000f);all_screen[x-i][y-3*i-2]=30;}
        }
        x-=b;
        y-=3*b;

        for(int i=0;i<c;i++){
            if(y-2*i>0 && all_screen[x-i][y-2*i]==2) {
                winner2();
                return;
            }if(y-2*i>1 && all_screen[x-i][y-2*i-1]==2) {
                winner2();
                return;
            }
            if(y-2*i>0 && all_screen[x-i][y-2*i]==1) {
                remove_block_man(x-i,y-2*i);
                return;
            }if(y-2*i>1 && all_screen[x-i][y-2*i-1]==1) {
                remove_block_man(x-i,y-2*i-1);
                return;
            }
            if(y-2*i>0) {write_pixel(x-i,y-2*i,0xf0000f);all_screen[x-i][y-2*i]=30;}
            if(y-2*i>1) {write_pixel(x-i,y-2*i-1,0xf0000f);all_screen[x-i][y-2*i-1]=30;}
        }
        x-=c;
        y-=2*c;

        for(int i=0;i<d;i++){
            if(y-i>0 && all_screen[x-i][y-i]==2) {
                winner2();
                return;
            }
            if(y-i>0 && all_screen[x-i][y-i]==1) {
                remove_block_man(x-i,y-i);
                return;
            }
            if(y-i>0) {write_pixel(x-i,y-i,0xf0000f);all_screen[x-i][y-i]=30;}
        }
        x-=d;
        y-=d;


        for(int i=0;i<5;i++){
            if(y>0) {write_pixel(x-i,y,0xf0000f);all_screen[x-i][y]=30;}
        }
        
        x -= 5;

        for(int i=0;i<5;i++){
            if(y>0) {write_pixel(x-i,y,0xf0000f);all_screen[x-i][y]=30;}
        }
        
        x -= 5;
        
        for(int i=0;i<d;i++){
            if(y+i>0 && all_screen[x-i][y+i]==2) {
                winner2();
                return;
            }
            if(y+i>0 && all_screen[x-i][y+i]==1) {
                remove_block_man(x-i,y+i);
                return;
            }
            if(y+i>0) {write_pixel(x-i,y+i,0xf0000f);all_screen[x-i][y+i]=30;}
        }
        x-=d;
        y+=d;

        for(int i=0;i<c;i++){
            if(y+2*i>0 && all_screen[x-i][y+2*i]==2) {
                winner2();
                return;
            }
            if(y+2*i+1>0 && all_screen[x-i][y+2*i+1]==2) {
                winner2();
                return;
            }
            if(y+2*i>0 && all_screen[x-i][y+2*i]==1) {
                remove_block_man(x-i,y+2*i);
                return;
            }
            if(y+2*i+1>0 && all_screen[x-i][y+2*i+1]==1) {
                remove_block_man(x-i,y+2*i+1);
                return;
            }
            if(y+2*i>0) {write_pixel(x-i,y+2*i,0xf0000f);all_screen[x-i][y+2*i]=30;}
            if(y+2*i+1>0) {write_pixel(x-i,y+2*i+1,0xf0000f);all_screen[x-i][y+2*i+1]=30;}
        }
        x-=c;
        y+=2*c;


        for(int i=0;i<b;i++){
            if(y+3*i>0 && all_screen[x-i][y+3*i]==2) {
                winner2();
                return;
            }if(y+3*i+1>0 && all_screen[x-i][y+3*i+1]==2) {
                winner2();
                return;
            }
            if(y+3*i+2>0 && all_screen[x-i][y+3*i+2]==2) {
                winner2();
                return;
            }
            if(y+3*i>0 && all_screen[x-i][y+3*i]==1) {
                remove_block_man(x-i,y+3*i);
                return;
            }if(y+3*i+1>0 && all_screen[x-i][y+3*i+1]==1) {
                remove_block_man(x-i,y+3*i+1);
                return;
            }
            if(y+3*i+2>0 && all_screen[x-i][y+3*i+2]==1) {
                remove_block_man(x-i,y+3*i+2);
                return;
            }
            if(y+3*i>0) {write_pixel(x-i,y+3*i,0xf0000f);all_screen[x-i][y+3*i]=30;}
            if(y+3*i+1>0) {write_pixel(x-i,y+3*i+1,0xf0000f);all_screen[x-i][y+3*i+1]=30;}
            if(y+3*i+2>0) {write_pixel(x-i,y+3*i+2,0xf0000f);all_screen[x-i][y+3*i+2]=30;}
        }
        x-=b;
        y+=3*b;

        for(int i=0;;i++){
            
            if(y+4*i>0 && all_screen[x-i][y+4*i]==2) {
                winner2();
                return;
            }if(y+4*i+1>0 && all_screen[x-i][y+4*i+1]==2) {
                winner2();
                return;
            }
            if(y+4*i+2>0 && all_screen[x-i][y+4*i+2]==2) {
                winner2();
                return;
            }
            if(y+4*i+3>0 && all_screen[x-i][y+4*i+3]==2) {
                winner2();
                return;
            }
            if(y+4*i>0 && all_screen[x-i][y+4*i]==1) {
                spx=x-i,spy=y+4*i;
                remove_block_man(x-i,y+4*i);
                return;
            }if(y+4*i+1>0 && all_screen[x-i][y+4*i+1]==1) {
                spx=x-i,spy=y+4*i+1;
                remove_block_man(x-i,y+4*i+1);
                return;
            }
            if(y+4*i+2>0 && all_screen[x-i][y+4*i+2]==1) {
                spx=x-i,spy=y+4*i+2;
                remove_block_man(x-i,y+4*i+2);
                return;
            }
            if(y+4*i+3>0 && all_screen[x-i][y+4*i+3]==1) {
                spx=x-i,spy=y+4*i+3;
                remove_block_man(x-i,y+4*i+3);
                return;
            }
            if( y+4*i>=240 || x-i<=0 ) break;
            if(y+4*i>0) {write_pixel(x-i,y+4*i,0xf0000f);all_screen[x-i][y+4*i]=30;}
            if(y+4*i+1>0) {write_pixel(x-i,y+4*i+1,0xf0000f);all_screen[x-i][y+4*i+1]=30;}
            if(y+4*i+2>0) {write_pixel(x-i,y+4*i+2,0xf0000f);all_screen[x-i][y+4*i+2]=30;}
            if(y+4*i+3>0) {write_pixel(x-i,y+4*i+3,0xf0000f);all_screen[x-i][y+4*i+3]=30;}
        }
        x-=a;
        y+=4*a;
}


void projectile2(int power){
 
    int x = person2_x;
    int y = person2_y+11;
    if(power == 0){
        project_bullet2(x,y,10,10,10,10);
    }
    else if(power == 1){
        project_bullet2(x,y,11,12,13,14);
    }
    else if(power == 2){
        project_bullet2(x,y,12,14,16,18);
    }
    else if(power == 3){
        project_bullet2(x,y,13,16,19,22);
    }
    else if(power == 4){
        project_bullet2(x,y,14,18,22,26);
    }
    else if(power == 5){
        project_bullet2(x,y,15,20,25,30);
    }
    else if(power == 6){
        project_bullet2(x,y,16,22,28,34);
    }
    else if(power == 7){
        project_bullet2(x,y,17,24,31,38);
    }
    else if(power == 8){
        project_bullet2(x,y,18,26,34,42);
    }
    else if(power == 9){
        project_bullet2(x,y,19,28,37,46);
    }
    water();

}

int min(int a,int b){
    if(a<b) return a;
    else return b;
}



void person1(int x,int y){


    int ok=0;
    int temp_y=2400;
    int temp_y_1 = 2400;

    for(int j=0;j<240;j++){

        if( all_screen[x+6][j]==1 ){
            ok=1;
            temp_y = j;
        }
        if( all_screen[x-4][j]==1 ){
            ok=2;
            temp_y_1 = j;
        }

    }
    if(ok==1 && all_screen[x+6][y+7]==1){
        x = x+4;
        y=temp_y-12;
    }
    if(ok==2 && all_screen[x-4][y+7]==1){
        x = x-4;
        y=temp_y-12;
    }

    // tp down
    int mini = 2400;
    for(int j=0;j<240;j++){
        if( all_screen[x][j]==1 ){
            mini = min(mini,j);
        }
        if( all_screen[x+2][j]==1 ){
            mini = min(mini,j);
        }
    }

    if(mini==2400){
        if(x<40) x-=5;
        else x+=5;


        y=205;
        for(int i=0;i<320;i++){
        for(int j=0;j<240;j++){
            if(all_screen[i][j]==2){
                all_screen[i][j]=0;
                write_pixel(i,j,0xffffff);
            }
        }
    }
        // head
    all_screen[x][y]=2;
    write_pixel(x,y,0);
    all_screen[x+1][y]=2;
    write_pixel(x+1,y,0);
    all_screen[x+2][y]=2;
    write_pixel(x+2,y,0);
    all_screen[x][y+1]=2;
    write_pixel(x,y+1,0);
    all_screen[x+1][y+1]=2;
    write_pixel(x+1,y+1,0);
    all_screen[x+2][y+1]=2;
    write_pixel(x+2,y+1,0);
    all_screen[x][y+2]=2;
    write_pixel(x,y+2,0);
    all_screen[x+1][y+2]=2;
    write_pixel(x+1,y+2,0);
    all_screen[x+2][y+2]=2;
    write_pixel(x+2,y+2,0);

    // neck 
    all_screen[x+1][y+3]=2;
    write_pixel(x+1,y+3,0);

    // body
    all_screen[x-1][y+4]=2;
    write_pixel(x-1,y+4,0);
    all_screen[x][y+4]=2;
    write_pixel(x,y+4,0);
    all_screen[x+1][y+4]=2;
    write_pixel(x+1,y+4,0);
    all_screen[x+2][y+4]=2;
    write_pixel(x+2,y+4,0);
    all_screen[x+3][y+4]=2;
    write_pixel(x+3,y+4,0);

    all_screen[x-1][y+5]=2;
    write_pixel(x-1,y+5,0);
    all_screen[x][y+5]=2;
    write_pixel(x,y+5,0);
    all_screen[x+1][y+5]=2;
    write_pixel(x+1,y+5,0);
    all_screen[x+2][y+5]=2;
    write_pixel(x+2,y+5,0);
    all_screen[x+3][y+5]=2;
    write_pixel(x+3,y+5,0);

    all_screen[x-1][y+6]=2;
    write_pixel(x-1,y+6,0);
    all_screen[x][y+6]=2;
    write_pixel(x,y+6,0);
    all_screen[x+1][y+6]=2;
    write_pixel(x+1,y+6,0);
    all_screen[x+2][y+6]=2;
    write_pixel(x+2,y+6,0);
    all_screen[x+3][y+6]=2;
    write_pixel(x+3,y+6,0);

    all_screen[x-1][y+7]=2;
    write_pixel(x-1,y+7,0);
    all_screen[x][y+7]=2;
    write_pixel(x,y+7,0);
    all_screen[x+1][y+7]=2;
    write_pixel(x+1,y+7,0);
    all_screen[x+2][y+7]=2;
    write_pixel(x+2,y+7,0);
    all_screen[x+3][y+7]=2;
    write_pixel(x+3,y+7,0);

    all_screen[x-1][y+8]=2;
    write_pixel(x-1,y+8,0);
    all_screen[x][y+8]=2;
    write_pixel(x,y+8,0);
    all_screen[x+1][y+8]=2;
    write_pixel(x+1,y+8,0);
    all_screen[x+2][y+8]=2;
    write_pixel(x+2,y+8,0);
    all_screen[x+3][y+8]=2;
    write_pixel(x+3,y+8,0);

    // arms
    
    all_screen[x-2][y+5]=2;
    write_pixel(x-2,y+5,0);
    all_screen[x-3][y+6]=2;
    write_pixel(x-3,y+6,0);
    all_screen[x-4][y+7]=2;
    write_pixel(x-4,y+7,0);

    all_screen[x+4][y+5]=2;
    write_pixel(x+4,y+5,0);
    all_screen[x+5][y+6]=2;
    write_pixel(x+5,y+6,0);
    all_screen[x+6][y+7]=2;
    write_pixel(x+6,y+7,0);

    // legs

    all_screen[x][y+9]=2;
    write_pixel(x,y+9,0);
    all_screen[x][y+10]=2;
    write_pixel(x,y+10,0);
    all_screen[x][y+11]=2;
    write_pixel(x,y+11,0);

    all_screen[x+2][y+9]=2;
    write_pixel(x+2,y+9,0);
    all_screen[x+2][y+10]=2;
    write_pixel(x+2,y+10,0);
    all_screen[x+2][y+11]=2;
    write_pixel(x+2,y+11,0);
        winner2();
        return;
    }

    x = x;
    // y = y-11;
    y = mini-12;


    person1_x = x;
    person1_y = y;

    for(int i=0;i<320;i++){
        for(int j=0;j<240;j++){
            if(all_screen[i][j]==2){
                all_screen[i][j]=0;
                write_pixel(i,j,0xffffff);
            }
        }
    }

    // head
    all_screen[x][y]=2;
    write_pixel(x,y,0);
    all_screen[x+1][y]=2;
    write_pixel(x+1,y,0);
    all_screen[x+2][y]=2;
    write_pixel(x+2,y,0);
    all_screen[x][y+1]=2;
    write_pixel(x,y+1,0);
    all_screen[x+1][y+1]=2;
    write_pixel(x+1,y+1,0);
    all_screen[x+2][y+1]=2;
    write_pixel(x+2,y+1,0);
    all_screen[x][y+2]=2;
    write_pixel(x,y+2,0);
    all_screen[x+1][y+2]=2;
    write_pixel(x+1,y+2,0);
    all_screen[x+2][y+2]=2;
    write_pixel(x+2,y+2,0);

    // neck 
    all_screen[x+1][y+3]=2;
    write_pixel(x+1,y+3,0);

    // body
    all_screen[x-1][y+4]=2;
    write_pixel(x-1,y+4,0);
    all_screen[x][y+4]=2;
    write_pixel(x,y+4,0);
    all_screen[x+1][y+4]=2;
    write_pixel(x+1,y+4,0);
    all_screen[x+2][y+4]=2;
    write_pixel(x+2,y+4,0);
    all_screen[x+3][y+4]=2;
    write_pixel(x+3,y+4,0);

    all_screen[x-1][y+5]=2;
    write_pixel(x-1,y+5,0);
    all_screen[x][y+5]=2;
    write_pixel(x,y+5,0);
    all_screen[x+1][y+5]=2;
    write_pixel(x+1,y+5,0);
    all_screen[x+2][y+5]=2;
    write_pixel(x+2,y+5,0);
    all_screen[x+3][y+5]=2;
    write_pixel(x+3,y+5,0);

    all_screen[x-1][y+6]=2;
    write_pixel(x-1,y+6,0);
    all_screen[x][y+6]=2;
    write_pixel(x,y+6,0);
    all_screen[x+1][y+6]=2;
    write_pixel(x+1,y+6,0);
    all_screen[x+2][y+6]=2;
    write_pixel(x+2,y+6,0);
    all_screen[x+3][y+6]=2;
    write_pixel(x+3,y+6,0);

    all_screen[x-1][y+7]=2;
    write_pixel(x-1,y+7,0);
    all_screen[x][y+7]=2;
    write_pixel(x,y+7,0);
    all_screen[x+1][y+7]=2;
    write_pixel(x+1,y+7,0);
    all_screen[x+2][y+7]=2;
    write_pixel(x+2,y+7,0);
    all_screen[x+3][y+7]=2;
    write_pixel(x+3,y+7,0);

    all_screen[x-1][y+8]=2;
    write_pixel(x-1,y+8,0);
    all_screen[x][y+8]=2;
    write_pixel(x,y+8,0);
    all_screen[x+1][y+8]=2;
    write_pixel(x+1,y+8,0);
    all_screen[x+2][y+8]=2;
    write_pixel(x+2,y+8,0);
    all_screen[x+3][y+8]=2;
    write_pixel(x+3,y+8,0);

    // arms
    
    all_screen[x-2][y+5]=2;
    write_pixel(x-2,y+5,0);
    all_screen[x-3][y+6]=2;
    write_pixel(x-3,y+6,0);
    all_screen[x-4][y+7]=2;
    write_pixel(x-4,y+7,0);

    all_screen[x+4][y+5]=2;
    write_pixel(x+4,y+5,0);
    all_screen[x+5][y+6]=2;
    write_pixel(x+5,y+6,0);
    all_screen[x+6][y+7]=2;
    write_pixel(x+6,y+7,0);

    // legs

    all_screen[x][y+9]=2;
    write_pixel(x,y+9,0);
    all_screen[x][y+10]=2;
    write_pixel(x,y+10,0);
    all_screen[x][y+11]=2;
    write_pixel(x,y+11,0);

    all_screen[x+2][y+9]=2;
    write_pixel(x+2,y+9,0);
    all_screen[x+2][y+10]=2;
    write_pixel(x+2,y+10,0);
    all_screen[x+2][y+11]=2;
    write_pixel(x+2,y+11,0);

}

void person2(int x,int y){

    int ok=0;
    int temp_y=2400;
    int temp_y_1 = 2400;

    for(int j=0;j<240;j++){

        if( all_screen[x+6][j]==1 ){
            ok=1;
            temp_y = j;
        }
        if( all_screen[x-4][j]==1 ){
            ok=2;
            temp_y_1 = j;
        }

    }
    if(ok==1 && all_screen[x+6][y+7]==1){
        x = x+4;
        y=temp_y-12;
    }
    if(ok==2 && all_screen[x-4][y+7]==1){
        x = x-4;
        y=temp_y-12;
    }

    int mini = 2400;
    for(int j=0;j<240;j++){
        if( all_screen[x][j]==1 ){
            mini = min(mini,j);
        }
        if( all_screen[x+2][j]==1 ){
            mini = min(mini,j);
        }
    }

    if(mini==2400){
        if(x>250) x+=5;
        else x-=5;
        y=205;
        
    for(int i=0;i<320;i++){
        for(int j=0;j<240;j++){
            if(all_screen[i][j]==3){
                all_screen[i][j]=0;
                write_pixel(i,j,0xffffff);
            }
        }
    }

    // head
    all_screen[x][y]=3;
    write_pixel(x,y,0);
    all_screen[x+1][y]=3;
    write_pixel(x+1,y,0);
    all_screen[x+2][y]=3;
    write_pixel(x+2,y,0);
    all_screen[x][y+1]=3;
    write_pixel(x,y+1,0);
    all_screen[x+1][y+1]=3;
    write_pixel(x+1,y+1,0);
    all_screen[x+2][y+1]=3;
    write_pixel(x+2,y+1,0);
    all_screen[x][y+2]=3;
    write_pixel(x,y+2,0);
    all_screen[x+1][y+2]=3;
    write_pixel(x+1,y+2,0);
    all_screen[x+2][y+2]=3;
    write_pixel(x+2,y+2,0);

    // neck 
    all_screen[x+1][y+3]=3;
    write_pixel(x+1,y+3,0);

    // body
    all_screen[x-1][y+4]=3;
    write_pixel(x-1,y+4,0);
    all_screen[x][y+4]=3;
    write_pixel(x,y+4,0);
    all_screen[x+1][y+4]=3;
    write_pixel(x+1,y+4,0);
    all_screen[x+2][y+4]=3;
    write_pixel(x+2,y+4,0);
    all_screen[x+3][y+4]=3;
    write_pixel(x+3,y+4,0);

    all_screen[x-1][y+5]=3;
    write_pixel(x-1,y+5,0);
    all_screen[x][y+5]=3;
    write_pixel(x,y+5,0);
    all_screen[x+1][y+5]=3;
    write_pixel(x+1,y+5,0);
    all_screen[x+2][y+5]=3;
    write_pixel(x+2,y+5,0);
    all_screen[x+3][y+5]=3;
    write_pixel(x+3,y+5,0);

    all_screen[x-1][y+6]=3;
    write_pixel(x-1,y+6,0);
    all_screen[x][y+6]=3;
    write_pixel(x,y+6,0);
    all_screen[x+1][y+6]=3;
    write_pixel(x+1,y+6,0);
    all_screen[x+2][y+6]=3;
    write_pixel(x+2,y+6,0);
    all_screen[x+3][y+6]=3;
    write_pixel(x+3,y+6,0);

    all_screen[x-1][y+7]=3;
    write_pixel(x-1,y+7,0);
    all_screen[x][y+7]=3;
    write_pixel(x,y+7,0);
    all_screen[x+1][y+7]=3;
    write_pixel(x+1,y+7,0);
    all_screen[x+2][y+7]=3;
    write_pixel(x+2,y+7,0);
    all_screen[x+3][y+7]=3;
    write_pixel(x+3,y+7,0);

    all_screen[x-1][y+8]=3;
    write_pixel(x-1,y+8,0);
    all_screen[x][y+8]=3;
    write_pixel(x,y+8,0);
    all_screen[x+1][y+8]=3;
    write_pixel(x+1,y+8,0);
    all_screen[x+2][y+8]=3;
    write_pixel(x+2,y+8,0);
    all_screen[x+3][y+8]=3;
    write_pixel(x+3,y+8,0);

    // arms
    
    all_screen[x-2][y+5]=3;
    write_pixel(x-2,y+5,0);
    all_screen[x-3][y+6]=3;
    write_pixel(x-3,y+6,0);
    all_screen[x-4][y+7]=3;
    write_pixel(x-4,y+7,0);

    all_screen[x+4][y+5]=3;
    write_pixel(x+4,y+5,0);
    all_screen[x+5][y+6]=3;
    write_pixel(x+5,y+6,0);
    all_screen[x+6][y+7]=3;
    write_pixel(x+6,y+7,0);

    // legs

    all_screen[x][y+9]=3;
    write_pixel(x,y+9,0);
    all_screen[x][y+10]=3;
    write_pixel(x,y+10,0);
    all_screen[x][y+11]=3;
    write_pixel(x,y+11,0);

    all_screen[x+2][y+9]=3;
    write_pixel(x+2,y+9,0);
    all_screen[x+2][y+10]=3;
    write_pixel(x+2,y+10,0);
    all_screen[x+2][y+11]=3;
    write_pixel(x+2,y+11,0);
        winner1();
        return;
    }

    x = x;
    // y = y-11;
    y = mini-12;

    person2_x = x;
    person2_y = y;

    for(int i=0;i<320;i++){
        for(int j=0;j<240;j++){
            if(all_screen[i][j]==3){
                all_screen[i][j]=0;
                write_pixel(i,j,0xffffff);
            }
        }
    }

    // head
    all_screen[x][y]=3;
    write_pixel(x,y,0);
    all_screen[x+1][y]=3;
    write_pixel(x+1,y,0);
    all_screen[x+2][y]=3;
    write_pixel(x+2,y,0);
    all_screen[x][y+1]=3;
    write_pixel(x,y+1,0);
    all_screen[x+1][y+1]=3;
    write_pixel(x+1,y+1,0);
    all_screen[x+2][y+1]=3;
    write_pixel(x+2,y+1,0);
    all_screen[x][y+2]=3;
    write_pixel(x,y+2,0);
    all_screen[x+1][y+2]=3;
    write_pixel(x+1,y+2,0);
    all_screen[x+2][y+2]=3;
    write_pixel(x+2,y+2,0);

    // neck 
    all_screen[x+1][y+3]=3;
    write_pixel(x+1,y+3,0);

    // body
    all_screen[x-1][y+4]=3;
    write_pixel(x-1,y+4,0);
    all_screen[x][y+4]=3;
    write_pixel(x,y+4,0);
    all_screen[x+1][y+4]=3;
    write_pixel(x+1,y+4,0);
    all_screen[x+2][y+4]=3;
    write_pixel(x+2,y+4,0);
    all_screen[x+3][y+4]=3;
    write_pixel(x+3,y+4,0);

    all_screen[x-1][y+5]=3;
    write_pixel(x-1,y+5,0);
    all_screen[x][y+5]=3;
    write_pixel(x,y+5,0);
    all_screen[x+1][y+5]=3;
    write_pixel(x+1,y+5,0);
    all_screen[x+2][y+5]=3;
    write_pixel(x+2,y+5,0);
    all_screen[x+3][y+5]=3;
    write_pixel(x+3,y+5,0);

    all_screen[x-1][y+6]=3;
    write_pixel(x-1,y+6,0);
    all_screen[x][y+6]=3;
    write_pixel(x,y+6,0);
    all_screen[x+1][y+6]=3;
    write_pixel(x+1,y+6,0);
    all_screen[x+2][y+6]=3;
    write_pixel(x+2,y+6,0);
    all_screen[x+3][y+6]=3;
    write_pixel(x+3,y+6,0);

    all_screen[x-1][y+7]=3;
    write_pixel(x-1,y+7,0);
    all_screen[x][y+7]=3;
    write_pixel(x,y+7,0);
    all_screen[x+1][y+7]=3;
    write_pixel(x+1,y+7,0);
    all_screen[x+2][y+7]=3;
    write_pixel(x+2,y+7,0);
    all_screen[x+3][y+7]=3;
    write_pixel(x+3,y+7,0);

    all_screen[x-1][y+8]=3;
    write_pixel(x-1,y+8,0);
    all_screen[x][y+8]=3;
    write_pixel(x,y+8,0);
    all_screen[x+1][y+8]=3;
    write_pixel(x+1,y+8,0);
    all_screen[x+2][y+8]=3;
    write_pixel(x+2,y+8,0);
    all_screen[x+3][y+8]=3;
    write_pixel(x+3,y+8,0);

    // arms
    
    all_screen[x-2][y+5]=3;
    write_pixel(x-2,y+5,0);
    all_screen[x-3][y+6]=3;
    write_pixel(x-3,y+6,0);
    all_screen[x-4][y+7]=3;
    write_pixel(x-4,y+7,0);

    all_screen[x+4][y+5]=3;
    write_pixel(x+4,y+5,0);
    all_screen[x+5][y+6]=3;
    write_pixel(x+5,y+6,0);
    all_screen[x+6][y+7]=3;
    write_pixel(x+6,y+7,0);

    // legs

    all_screen[x][y+9]=3;
    write_pixel(x,y+9,0);
    all_screen[x][y+10]=3;
    write_pixel(x,y+10,0);
    all_screen[x][y+11]=3;
    write_pixel(x,y+11,0);

    all_screen[x+2][y+9]=3;
    write_pixel(x+2,y+9,0);
    all_screen[x+2][y+10]=3;
    write_pixel(x+2,y+10,0);
    all_screen[x+2][y+11]=3;
    write_pixel(x+2,y+11,0);

}


int detect_block_x(int x){
    x = (x/10)*10;
    return x;
}

int detect_block_y(int y){
    y = (y/10)*10;
    return y;
}

void remove_block(int x, int y){


    for(int i=0;i<y;i++){
        if( all_screen[x][i]==1 ){
            y=i;
            break;
        }
    }

    for(int i=x;i<x+10;i++){
        for(int j=y;j<y+10;j++){
            all_screen[i][j]=0;
            write_pixel(i,j,0xffffff);
        }
    }

}

void remove_block_man(int x,int y){

    x = detect_block_x(x);
    y = detect_block_y(y);

    // find person
    int temp_x,temp_y;

    for(int j=0;j<240;j++){

        for(int i=0;i<320;i++){
            if(all_screen[i][j]==2){
                temp_x=i;
                temp_y=j;
                // break;
            }
        }

    }
    
    remove_block(x,y);
    person1(temp_x-2,temp_y-12);


}

void remove_block_man1(int x,int y){

    x = detect_block_x(x);
    y = detect_block_y(y);

    // find person
    int temp_x,temp_y;

    for(int j=0;j<240;j++){

        for(int i=0;i<320;i++){
            if(all_screen[i][j]==3){
                temp_x=i;
                temp_y=j;
                // break;
            }
        }

    }
    
    remove_block(x,y);
    person2(temp_x-2,temp_y-12);


}

void water(){

    for(int i=0;i<320;i++){

        for(int j=210;j<240;j++){
            all_screen[i][j]=10;
        }

    }

    // design

    for(int i=0;i<320;i++){

        for(int j=210;j<222;j++){
            write_pixel(i,j,0x0000FF);
        }
        for(int j=222;j<229;j++){
            write_pixel(i,j,0x0000FF);
        }
        for(int j=229;j<240;j++){
            write_pixel(i,j,0x0000ff);
        }

    }

    


}

void winner2(){

    over=2;
    // x = 141, y=  20

    // W
    int x = 141, y=10;
    write_pixel(x,y,0);
    write_pixel(x,y+1,0);
    write_pixel(x,y+2,0);
    write_pixel(x,y+3,0);
    write_pixel(x,y+4,0);

    write_pixel(x+1,y+4,0);

    write_pixel(x+2,y+3,0);

    write_pixel(x+3,y+4,0);

    write_pixel(x+4,y,0);
    write_pixel(x+4,y+1,0);
    write_pixel(x+4,y+2,0);
    write_pixel(x+4,y+3,0);
    write_pixel(x+4,y+4,0);

    // I

    write_pixel(x+8,y,0);
    write_pixel(x+8,y+1,0);
    write_pixel(x+8,y+2,0);
    write_pixel(x+8,y+3,0);
    write_pixel(x+8,y+4,0);

    write_pixel(x+7,y+4,0);
    write_pixel(x+7,y,0);

    write_pixel(x+9,y+4,0);
    write_pixel(x+9,y,0);



    // N
    write_pixel(x+12,y,0);
    write_pixel(x+12,y+1,0);
    write_pixel(x+12,y+2,0);
    write_pixel(x+12,y+3,0);
    write_pixel(x+12,y+4,0);

    write_pixel(x+13,y,0);
    write_pixel(x+14,y+1,0);
    write_pixel(x+15,y+2,0);
    write_pixel(x+16,y+3,0);
    write_pixel(x+17,y+4,0);
    
    write_pixel(x+18,y,0);
    write_pixel(x+18,y+1,0);
    write_pixel(x+18,y+2,0);
    write_pixel(x+18,y+3,0);
    write_pixel(x+18,y+4,0);

    // N
    write_pixel(x+21,y,0);
    write_pixel(x+21,y+1,0);
    write_pixel(x+21,y+2,0);
    write_pixel(x+21,y+3,0);
    write_pixel(x+21,y+4,0);

    write_pixel(x+22,y,0);
    write_pixel(x+23,y+1,0);
    write_pixel(x+24,y+2,0);
    write_pixel(x+25,y+3,0);
    write_pixel(x+26,y+4,0);
    
    write_pixel(x+27,y,0);
    write_pixel(x+27,y+1,0);
    write_pixel(x+27,y+2,0);
    write_pixel(x+27,y+3,0);
    write_pixel(x+27,y+4,0);

    // E

    write_pixel(x+30,y,0);
    write_pixel(x+30,y+1,0);
    write_pixel(x+30,y+2,0);
    write_pixel(x+30,y+3,0);
    write_pixel(x+30,y+4,0);

    write_pixel(x+31,y,0);
    write_pixel(x+31,y+2,0);
    write_pixel(x+31,y+4,0);

    write_pixel(x+32,y,0);
    write_pixel(x+32,y+2,0);
    write_pixel(x+32,y+4,0);

    // R

    write_pixel(x+35,y,0);
    write_pixel(x+35,y+1,0);
    write_pixel(x+35,y+2,0);
    write_pixel(x+35,y+3,0);
    write_pixel(x+35,y+4,0);

    write_pixel(x+36,y,0);
    write_pixel(x+37,y,0);
    write_pixel(x+38,y+1,0);
    write_pixel(x+37,y+2,0);
    write_pixel(x+36,y+2,0);

    write_pixel(x+36,y+3,0);
    write_pixel(x+37,y+4,0);

    x+=5;

    // 2
    write_pixel(x+40,y+4,0);
    write_pixel(x+40,y+1,0);
    write_pixel(x+41,y,0);
    write_pixel(x+41,y+4,0);
    write_pixel(x+41,y+3,0);
    write_pixel(x+42,y+4,0);
    write_pixel(x+42,y+2,0);
    write_pixel(x+42,y,0);
    // write_pixel(x+42,y+1,0);
    // write_pixel(x+42,y,0);
    write_pixel(x+43,y+4,0);
    write_pixel(x+43,y+1,0);
    // write_pixel(x+44,y+4,0);

}

void winner1(){

    over=1;
    // x = 141, y=  20

    // W
    int x = 141, y=10;
    write_pixel(x,y,0);
    write_pixel(x,y+1,0);
    write_pixel(x,y+2,0);
    write_pixel(x,y+3,0);
    write_pixel(x,y+4,0);

    write_pixel(x+1,y+4,0);

    write_pixel(x+2,y+3,0);

    write_pixel(x+3,y+4,0);

    write_pixel(x+4,y,0);
    write_pixel(x+4,y+1,0);
    write_pixel(x+4,y+2,0);
    write_pixel(x+4,y+3,0);
    write_pixel(x+4,y+4,0);

    // I

    write_pixel(x+8,y,0);
    write_pixel(x+8,y+1,0);
    write_pixel(x+8,y+2,0);
    write_pixel(x+8,y+3,0);
    write_pixel(x+8,y+4,0);

    write_pixel(x+7,y+4,0);
    write_pixel(x+7,y,0);

    write_pixel(x+9,y+4,0);
    write_pixel(x+9,y,0);



    // N
    write_pixel(x+12,y,0);
    write_pixel(x+12,y+1,0);
    write_pixel(x+12,y+2,0);
    write_pixel(x+12,y+3,0);
    write_pixel(x+12,y+4,0);

    write_pixel(x+13,y,0);
    write_pixel(x+14,y+1,0);
    write_pixel(x+15,y+2,0);
    write_pixel(x+16,y+3,0);
    write_pixel(x+17,y+4,0);
    
    write_pixel(x+18,y,0);
    write_pixel(x+18,y+1,0);
    write_pixel(x+18,y+2,0);
    write_pixel(x+18,y+3,0);
    write_pixel(x+18,y+4,0);

    // N
    write_pixel(x+21,y,0);
    write_pixel(x+21,y+1,0);
    write_pixel(x+21,y+2,0);
    write_pixel(x+21,y+3,0);
    write_pixel(x+21,y+4,0);

    write_pixel(x+22,y,0);
    write_pixel(x+23,y+1,0);
    write_pixel(x+24,y+2,0);
    write_pixel(x+25,y+3,0);
    write_pixel(x+26,y+4,0);
    
    write_pixel(x+27,y,0);
    write_pixel(x+27,y+1,0);
    write_pixel(x+27,y+2,0);
    write_pixel(x+27,y+3,0);
    write_pixel(x+27,y+4,0);

    // E

    write_pixel(x+30,y,0);
    write_pixel(x+30,y+1,0);
    write_pixel(x+30,y+2,0);
    write_pixel(x+30,y+3,0);
    write_pixel(x+30,y+4,0);

    write_pixel(x+31,y,0);
    write_pixel(x+31,y+2,0);
    write_pixel(x+31,y+4,0);

    write_pixel(x+32,y,0);
    write_pixel(x+32,y+2,0);
    write_pixel(x+32,y+4,0);

    // R

    write_pixel(x+35,y,0);
    write_pixel(x+35,y+1,0);
    write_pixel(x+35,y+2,0);
    write_pixel(x+35,y+3,0);
    write_pixel(x+35,y+4,0);

    write_pixel(x+36,y,0);
    write_pixel(x+37,y,0);
    write_pixel(x+38,y+1,0);
    write_pixel(x+37,y+2,0);
    write_pixel(x+36,y+2,0);

    write_pixel(x+36,y+3,0);
    write_pixel(x+37,y+4,0);

    x+=5;
    // 1
    write_pixel(x+40,y+4,0);
    write_pixel(x+40,y+2,0);
    write_pixel(x+41,y+4,0);
    write_pixel(x+41,y+1,0);
    write_pixel(x+42,y+4,0);
    write_pixel(x+42,y+3,0);
    write_pixel(x+42,y+2,0);
    write_pixel(x+42,y+1,0);
    write_pixel(x+42,y,0);
    write_pixel(x+43,y+4,0);
    write_pixel(x+44,y+4,0);


}

void left_key_1(){
    // a
    person1( person1_x-3,person1_y );
    water();
}

void right_key_1(){
    // d
    person1( person1_x+3,person1_y );
    water();
}

void left_key_2(){
    // j
    person2(person2_x-3,person2_y);
    water();
}
void right_key_2(){
    // l
    person2(person2_x+3,person2_y);
    water();
}

void space_key(int power){
    // s
    projectile1(power);
    water();
}

void enter_key(int power){
    // k
    projectile2(power);
    water();
}


void clear_projectile(){
      for(int i=0;i<320;i++){
        for(int j=0;j<240;j++){
            if(all_screen[i][j]==30){
                all_screen[i][j]=0;
                write_pixel(i,j,0xffffff);
            }
        }
    }
      for(int i=0;i<320;i++){
        for(int j=0;j<240;j++){
            if(all_screen[i][j]==20){
                all_screen[i][j]=0;
                write_pixel(i,j,0xffffff);
            }
        }
    }

}

void specialpower1(){
    int x=spx, y=spy;
    x=detect_block_x(x);
    y=detect_block_y(y);
    for(int i=0;i<200;i+=10){
        remove_block_man(x,i);
    }
}
void specialpower2(){
    int x=spx, y=spy;
    x=detect_block_x(x);
    y=detect_block_y(y);
    for(int i=0;i<200;i+=10){
        remove_block_man1(x,i);
    }
}
void home1(){
    clear_screen1();
    char* hw = "ISLAND CAPTURE";
    int x = 30;
    while (*hw) {
     write_char(x, 5 , *hw);
	 x++;
	 hw++;
   }
    char* hw1 = "Player 1";
   int x1 = 30;
   while (*hw1) {
     write_char(x1, 15, *hw1);
	 x1++;
	 hw1++;
   }
    char* hw2 = "CHOOSE ISLAND";
   int x2 = 30;
   while (*hw2) {
     write_char(x2, 20, *hw2);
	 x2++;
	 hw2++;
   }
    char* hw3 = "1";
   int x3 = 13;
   while (*hw3) {
     write_char(x3, 25, *hw3);
	 x3++;
	 hw3++;
   }
    char* hw4 = "2";
   int x4 = 40;
   while (*hw4) {
     write_char(x4, 25, *hw4);
	 x4++;
	 hw4++;
   }
    char* hw5 = "3";
   int x5 = 67;
   while (*hw5) {
     write_char(x5, 25, *hw5);
	 x5++;
	 hw5++;
   }
    
     tower_base1(8); 
     tower_base3(110); 
     tower_base5(212);
      int choose1;
    scanf("%d",&choose1);
    if(choose1==1){
        player1tower=choose1;
    }
    else if(choose1==2){
        player1tower=choose1;
    }
    else if(choose1==3){
        player1tower=choose1;
    }
    else{
        home1();
    }
    return;
}
void home2(){
    clear_screen1();
    char* hw = "ISLAND CAPTURE";
    int x = 30;
    while (*hw) {
     write_char(x, 5 , *hw);
	 x++;
	 hw++;
   }
    char* hw1 = "Player 2";
   int x1 = 30;
   while (*hw1) {
     write_char(x1, 15, *hw1);
	 x1++;
	 hw1++;
   }
    char* hw2 = "CHOOSE ISLAND";
   int x2 = 30;
   while (*hw2) {
     write_char(x2, 20, *hw2);
	 x2++;
	 hw2++;
   }
    char* hw3 = "1";
   int x3 = 13;
   while (*hw3) {
     write_char(x3, 25, *hw3);
	 x3++;
	 hw3++;
   }
    char* hw4 = "2";
   int x4 = 40;
   while (*hw4) {
     write_char(x4, 25, *hw4);
	 x4++;
	 hw4++;
   }
    char* hw5 = "3";
   int x5 = 67;
   while (*hw5) {
     write_char(x5, 25, *hw5);
	 x5++;
	 hw5++;
   }
 tower_base1(8); 
     tower_base3(110); 
     tower_base5(212);
      int choose2;
    scanf("%d",&choose2);
    if(choose2==1){
        player2tower=choose2;
    }
    else if(choose2==2){
        player2tower=choose2;
    }
    else if(choose2==3){
        player2tower=choose2;
    }
    else{
        home2();
    }
    return;

}
void startt(){
     clear_screen1();
    home1();
    clear_screen1();
    home2();
    clear_screen();
    
    // volatile int * KEYS_ptr = (int *) KEY_BASE;

        int  flag = 0;	
        int ct=0;	
        
    for(int i=0;i<320;i++){
        for(int j=0;j<240;j++) all_screen[i][j]=0;
    }

    //  printf("hello")  ;
    
    if(player1tower==1){
        tower_base1(20);
    }
    else  if(player1tower==2){
        tower_base3(20);
    }
    else{
        tower_base5(20);
    }
    if(player2tower==1){
        tower_base2(290);
    }
    else  if(player2tower==2){
        tower_base4(290);
    }
    else{
        tower_base6(290);
    }
    
    water();

    person1(60,18);
    person2(250,118);								 	// clear flag for KEY pressed

}

int main () {

    clear_screen1();
    home1();
    clear_screen1();
    home2();
    clear_screen();
    
    // volatile int * KEYS_ptr = (int *) KEY_BASE;

        int  flag = 0;	
        int ct=0;	
        
    for(int i=0;i<320;i++){
        for(int j=0;j<240;j++) all_screen[i][j]=0;
    }

    //  printf("hello")  ;
    
    if(player1tower==1){
        tower_base1(20);
    }
    else  if(player1tower==2){
        tower_base3(20);
    }
    else{
        tower_base5(20);
    }
    if(player2tower==1){
        tower_base2(290);
    }
    else  if(player2tower==2){
        tower_base4(290);
    }
    else{
        tower_base6(290);
    }
    // tower_base1(20);
    // tower_base2(290);
    // // tower_base3(104);
    // // tower_base5 (206);

    water();

    person1(60,18);
    person2(250,118);								 	// clear flag for KEY pressed

    // projectile1(0);
    // printf("Enter the first shot ");
    // int x1,x2;
    // scanf("%d",&x1);
    // projectile2(x1);
    // printf("Enter the first shot ");
    //    scanf("%d",&x2);
    // projectile1(x2);
    // char c1;
    printf("Hello ! \n HOW TO PLAY? \n* Left Player: move left (press 'a') , move right (press 'd') \n   , shoot (press any number), special power(press q)");
    printf("\n* Right Player: move left (press 'j') , move right (press 'l')\n   , shoot (press any number), special power(press u)\n");
    
    printf("\nGame start from left player\n");
    // scanf("%c",&c1);

        int check = 0;

        int x1=0,x2=0;
        int s1=0,s2=0;
        while(1){
            if(over==1){
                printf("\nPlayer 1 Wins\n");
                 char c1;
                printf("Play Again? y/n : ");
                 scanf("%c",&c1);
                //  printf("%c",&c1);
                 if(c1=='y'){
                    x1=0,x2=0;
                    s1=0,s2=0;

                    startt();
                    
                 }
                 else if(c1=='n'){
                    // endd();
                    return 0;
                 }
                 over=0;
            }
            else if(over==2){
                printf("\nPlayer 2 Wins\n");
                printf("Play Again? y/n : ");
                char c1;
                scanf("%c",&c1);
                //  printf("%c",&c1);
                 if(c1=='y'){
                    x1=0,x2=0;
                    s1=0,s2=0;
                    startt();
                 }
                 else if(c1=='n'){
                    // endd();
                    return 0;
                 }
                 over=0;
            }
            char c;
            scanf("%c",&c);
            if(check==0){
                if(c<='9'&& c>='0'){
                    clear_projectile();
                    projectile1(c-'0');
                    check=1;
                }
                else{
                    if(c=='a'){
                        left_key_1();
                    }
                    else if(c=='d'){
                        right_key_1();
                    }
                    else if(c=='q'&&x1==0){
                        char g;
                        scanf("%c",&g);
                        if(g<='8'&&g>='1'){
                            clear_projectile();
                            projectile1(g-'0');
                            projectile1(g-'0'+1);
                            projectile1(g-'0'-1);
                        }
                        else{
                            continue;
                        }
                        x1++;
                    check=1;

                    }
                    else if(c=='e'&&s1==0){
                         char g;
                        scanf("%c",&g);
                        if(g<='8'&&g>='1'){
                            clear_projectile();
                            projectile1(g-'0');
                            specialpower1();
                        }
                        else{
                            continue;
                        }
                        s1++;
                    check=1;
                    }
                }
            }
           else {
                if(c<='9'&& c>='0'){
                    clear_projectile();
                    projectile2(c-'0');
                    check=0;
                }
                else{
                    if(c=='j'){
                        left_key_2();
                    }
                    else if(c=='l'){
                        right_key_2();
                    }
                     else if(c=='u'&&x2==0){
                        char g;
                        scanf("%c",&g);
                        if(g<='8'&&g>='1'){
                            clear_projectile();
                            projectile2(g-'0');
                            projectile2(g-'0'+1);
                            projectile2(g-'0'-1);
                        }
                        else{
                            continue;
                        }
                        x2++;
                    check=0;
                    }
                    else if(c=='o'&&s2==0){
                         char g;
                        scanf("%c",&g);
                        if(g<='8'&&g>='1'){
                            clear_projectile();
                            projectile2(g-'0');
                           specialpower2();
                        }
                        else{
                            continue;
                        }
                        s2++;
                    check=0;
                    }
                }
            }
        }


 return 0;
}
