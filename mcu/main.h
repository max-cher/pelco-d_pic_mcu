
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

//#define	u8	char
//#define	u16	unsigned long
//#define	s16	long

#define	uint8_t	char
#define	uint16_t	unsigned long
#define	int16_t	long

#define	b0	0x01
#define	b1	0x02
#define	b2	0x04
#define	b3	0x08
#define	b4	0x10
#define	b5	0x20
#define	b6	0x40
#define	b7	0x80

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
	

uint8_t w_tmp @ 0x70;
uint8_t st_tmp @ 0x71;
uint8_t pc_temp @ 0x72;
uint8_t tmp8 @ 0x73;
uint16_t tmp16 @ 0x74;
//u8 c0 @ 0x76;
//u8 c1 @ 0x77;
//u8 c2 @ 0x78;
uint8_t d0 @ 0x79;
uint8_t d1 @ 0x7a;
uint8_t d2 @ 0x7b;
uint8_t d3 @ 0x7c;
uint16_t count @ 0x7d;



uint8_t btn_t1, btn_t2, btn_t3, btn_t4, lcd_c, tdc, pc_tmp, enc1, enc2, enc_buf, tmr1hh, t0h, btn0_buf, btn1_buf;
uint16_t value, value1, value_tmp, value_buf;
uint16_t volt00, volt01, volt10, volt11;
uint16_t volt01tmp, volt10tmp, volt11tmp, volt00tmp;
uint16_t pwm0, pwm1, volt0, volt1;
uint16_t v_e0;
int16_t v_integral0, pi_temp, tmp_s16;

uint8_t msg[7];
//uint8_t rx_buffer[7];

//u16 angle;

uint8_t kp, ki;

bit update_lcd_flag, up_ndown, btn0, btn1;

uint8_t char0;
uint8_t char1;
uint8_t char2;
uint8_t char3;
uint8_t char4;

uint8_t c0;
uint8_t c1;
uint8_t c2;
uint8_t c3;
uint8_t c4;


uint8_t c00 @ 0xa0;
uint8_t c01 @ 0xa1;
uint8_t c02 @ 0xa2;
uint8_t c03 @ 0xa3;
uint8_t c04 @ 0xa4;
uint8_t c05 @ 0xa5;
uint8_t c06 @ 0xa6;
uint8_t c07 @ 0xa7;
uint8_t c08 @ 0xa8;
uint8_t c09 @ 0xa9;
uint8_t c0a @ 0xaa;
uint8_t c0b @ 0xab;
uint8_t c0c @ 0xac;
uint8_t c0d @ 0xad;
uint8_t c0e @ 0xae;
uint8_t c0f @ 0xaf;

uint8_t c10 @ 0xb0;
uint8_t c11 @ 0xb1;
uint8_t c12 @ 0xb2;
uint8_t c13 @ 0xb3;
uint8_t c14 @ 0xb4;
uint8_t c15 @ 0xb5;
uint8_t c16 @ 0xb6;
uint8_t c17 @ 0xb7;
uint8_t c18 @ 0xb8;
uint8_t c19 @ 0xb9;
uint8_t c1a @ 0xba;
uint8_t c1b @ 0xbb;
uint8_t c1c @ 0xbc;
uint8_t c1d @ 0xbd;
uint8_t c1e @ 0xbe;
uint8_t c1f @ 0xbf;

void move_left(void);
void move_right(void);
void move_up(void);
void move_down(void);
void move_stop(void);
uint8_t crc(void);
void send_msg(void);
void Init_UART(void);
void delay(uint8_t dly_val);
void lcd_init(void);
void byte_send(uint8_t bs);
uint8_t busy_check(void);
void cmd_send_noACK(uint8_t bs);
void cmd_send(uint8_t bs);
void print(void);
void calc_value16(uint16_t value);
uint8_t convert_char(uint8_t char0);
void delay_10u(void);
void delay_50u(void);
uint16_t get_angle_x(void);
uint16_t get_angle_y(void);










