
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config DEBUG = OFF
#pragma config WRT = OFF


#pragma interruptSaveCheck n

#define	u8	char
#define	u16	unsigned long
#define	s16	long

#define	uint8_t	char
#define	uint16_t	unsigned long
#define	int8_t	long

#define	b0	0x01
#define	b1	0x02
#define	b2	0x04
#define	b3	0x08
#define	b4	0x10
#define	b5	0x20
#define	b6	0x40
#define	b7	0x80

//#define	rs	PORTC.4
//#define	rw	PORTC.5
//#define	e	PORTC.6

#define	rs			b4
#define	rw			b5
#define	e			b3//b6

#define	ds	PORTA.4
#define clk	PORTA.5


#define	lcd_data	PORTD
#define	lcd_tris	TRISD


#define start SSPSTAT.3;
#define stop SSPSTAT.4;
#define RW SSPSTAT.2;

//#define GO 0b00000100;

//#define zero STATUS.2;


	

u8 w_tmp @ 0x70;
u8 st_tmp @ 0x71;
u8 pc_temp @ 0x72;
u8 tmp8 @ 0x73;
u16 tmp16 @ 0x74;
//u8 c0 @ 0x76;
//u8 c1 @ 0x77;
//u8 c2 @ 0x78;
u8 d0 @ 0x79;
u8 d1 @ 0x7a;
u8 d2 @ 0x7b;
u8 d3 @ 0x7c;
u16 count @ 0x7d;



u8 btn_t1, btn_t2, btn_t3, btn_t4, lcd_c, tdc, pc_tmp, enc1, enc2, enc_buf, tmr1hh, t0h, btn0_buf, btn1_buf;
u16 value, value1, value_tmp, value_buf;
u16 volt00, volt01, volt10, volt11;
u16 volt01tmp, volt10tmp, volt11tmp, volt00tmp;
u16 pwm0, pwm1, volt0, volt1;
u16 v_e0;
s16 v_integral0, pi_temp, tmp_s16;

uint8_t msg[7];

//u16 angle;

u8 kp, ki;


bit update_lcd_flag, up_ndown, btn0, btn1;

u8 char0;
u8 char1;
u8 char2;
u8 char3;
u8 char4;

u8 c0;
u8 c1;
u8 c2;
u8 c3;
u8 c4;


u8 c00 @ 0xa0;
u8 c01 @ 0xa1;
u8 c02 @ 0xa2;
u8 c03 @ 0xa3;
u8 c04 @ 0xa4;
u8 c05 @ 0xa5;
u8 c06 @ 0xa6;
u8 c07 @ 0xa7;
u8 c08 @ 0xa8;
u8 c09 @ 0xa9;
u8 c0a @ 0xaa;
u8 c0b @ 0xab;
u8 c0c @ 0xac;
u8 c0d @ 0xad;
u8 c0e @ 0xae;
u8 c0f @ 0xaf;
  
  
u8 c10 @ 0xb0;
u8 c11 @ 0xb1;
u8 c12 @ 0xb2;
u8 c13 @ 0xb3;
u8 c14 @ 0xb4;
u8 c15 @ 0xb5;
u8 c16 @ 0xb6;
u8 c17 @ 0xb7;
u8 c18 @ 0xb8;
u8 c19 @ 0xb9;
u8 c1a @ 0xba;
u8 c1b @ 0xbb;
u8 c1c @ 0xbc;
u8 c1d @ 0xbd;
u8 c1e @ 0xbe;
u8 c1f @ 0xbf;









