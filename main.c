#include "D:\cc5x\16f877a.h"
#include "D:\cc5x\INLINE.H"
#include "main.h"



#pragma origin 0x04
interrupt isr(void) {
//
	w_tmp = W;
	W = swap(STATUS);
	st_tmp = W;
	pc_tmp = PCLATH;
//#pragma update_RP 0
//
	STATUS = 0;
	PCLATH = 0;
//
	
	//PORTB.6 = 1;
	
	if(ADIF && ADIE) {	//ADC int
		ADIF = 0;
		
	}
	
	if(T0IF && T0IE) {	//TMR0 int
		T0IF = 0;
	}
	
	if(TMR1IF && TMR1IE) {	//TMR1 int
		TMR1IF = 0;
		
	}
	
	if(TMR2IF && TMR2IE) {	//TMR2 int
		TMR2IF = 0;
	}
	
    if(RCIF && RCIE) {	//UART RX int
        RCIF = 0;
        c03 = RCREG;
        //PORTB.0 = 1;
    }
    if(TXIF && TXIE) {	//UART TX int
        TXIF = 0;
        //PORTB.1 = 1;
    }
    
	//PORTB.6 = 0;
    //PORTB.1 = 0;
	
//
//#pragma update_RP 1
	PCLATH = pc_tmp;
	STATUS = swap(st_tmp);
	w_tmp = swap(w_tmp);
	W = swap(w_tmp);
//
}

void move_left(void);
void move_right(void);
void move_stop(void);
void send_msg(void);
void Init_UART(void);
void delay(u8 dly_val);
void lcd_init(void);
void byte_send(u8 bs);
u8 busy_check(void);
void cmd_send_noACK(u8 bs);
void cmd_send(u8 bs);
void print(void);
void calc_value16(u16 value);
u8 convert_char(u8 char0);
void delay_10u(void);
void delay_50u(void);
u16 get_angle(void);




void main(void) {
	STATUS = 0;
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	TRISA = 0b00101111;
	TRISB = 0b11110000;
	TRISC = 0b10000000;
	TRISD = 0b00000000;//0b00000011;//0x00;
	TRISE = 0x03;
	OPTION_REG = 0b11000111;
	
	//lcd_init();
	
	PIR1 = 0;
	PIR2 = 0;
	PIE1 = 0;
	PIE2 = 0;
	
	INTE = 0;
	
	T0IE = 1;
	PEIE = 1;
	TMR1IF = 0;
	//TMR1IE = 1;
	//GIE = 1;
	
	//PR2 = 0xff;
	
//	T2CON = 0b00000010;	// 1:16
//	T2CON = 0b00000001;	// 1:4
	//T2CON = 0b01111000;	// 1:1
	
	//TMR2IE = 1;
		
	//CCPR1L = 0xff;
	//CCP1CON = 0b00001100;
	//CCPR2L = 0x50;
	//CCP2CON = 0b00001100;
	//CCP1IF = 0;
	//CCP1IE = 1;
	
	////T2CON.2 = 1; // timer on
    
    
	
	//PORTB = 0b00000000;
    
    Init_UART();
	
	u8 dd = 8;	// delay value
	
	update_lcd_flag = 1;
    
    u8 dly_tmp;
    
    //send_pulses(13);
    
    
    
    c00 = 'p';
    c01 = '0';
    c02 = ':';
    c03 = '0';
    c04 = '0';
    c05 = '0';
    c06 = '0';
    c07 = '0';
    c08 = ' ';
    c09 = ' ';
    c0a = ' ';
    c0b = ' ';
    c0c = ' ';
    c0d = ' ';
    c0e = ' ';
    c0f = ' ';
    
    c10 = ' ';
    c11 = ' ';
    c12 = ' ';
    c13 = ' ';
    c14 = ' ';
    c15 = ' ';
    c16 = ' ';
    c17 = ' ';
    c18 = ' ';
    c19 = ' ';
    c1a = ' ';
    c1b = ' ';
    c1c = ' ';
    c1d = ' ';
    c1e = ' ';
    c1f = ' ';
    //print();
    //delay_50u();
    u16 main_counter = 0;
    
    //PORTB = 0xaa;
    
    //move_stop();
    //TXREG = 'a';
    PORTB.2 = 1;
    
	while(1) {
        
        //PORTB = PORTA;
        
        //if(PORTB.4 == 1 && PORTB.5 == 0) {
        if(PORTB.4 && !PORTB.5) {
            PORTB = 0x0a;
            //PORTB = 0x0f;
            move_right();
        }
        else if(!PORTB.4 && PORTB.5) {
        //if(PORTB.5) {
            PORTB = 0x05;
        //    //PORTB = 0x00;
            move_left();
        }
        else if(!PORTB.4 && !PORTB.5) {
            PORTB = 0x00;
            move_stop();
        }
        //if(PORTB.4 == 0 && PORTB.5 == 0) {
        //if(PORTB.6) {
        //    PORTB.2 = 0;
        //    PORTB.3 = 0;
        //    move_stop();
        //}
        
        //delay(0x88);
        //*/
        
        /*
        TRISD = 0b00000011;//0b00000011;
        while(!PORTD.0) {
            PORTB.1 = 0;
            dly_tmp = 5;
            PORTB.3 = 1;
            
            while(dly_tmp)
                dly_tmp--;
            
            PORTB.3 = 0;
            
            dly_tmp = 0x30;//0x2a;
            while(dly_tmp)
                dly_tmp--;
        }
        
        while(!PORTD.1) {
            PORTB.1 = 1;
            dly_tmp = 5;
            PORTB.3 = 1;
            
            while(dly_tmp)
                dly_tmp--;
            
            PORTB.3 = 0;
            
            dly_tmp = 0x30;//0x2a;
            while(dly_tmp)
                dly_tmp--;
        }
        TRISD = 0b00000000;//0b00000011;
        //*/
        /*
        //send_pulses();
        //calc_value16(get_angle());
        calc_value16(main_counter);
        c03 = c0;
        c04 = c1;
        c05 = c2;
        c06 = c3;
        c07 = c4;
        c17 = 'A';
        print();
        //*/
        
		/*
		if(update_lcd_flag) {
			
			calc_value16(666);
			c03 = c0;
			c04 = c1;
			c05 = c2;
			c06 = c3;
			c07 = c4;
			
			calc_value16(777);
			c13 = c0;
			c14 = c1;
			c15 = c2;
			c16 = c3;
			c17 = c4;
			
            
			if(PORTB.0 && !PORTB.1) {
				if(volt00 > volt01) {
					volt0 = volt00 - volt01;
					c0b = '+';
				}
				else {
					volt0 = volt01 - volt00;
					c0b = '-';
				}
			}
			
			if(!PORTB.0 && PORTB.1) {
				if(volt00 > volt01) {
					volt0 = volt00 - volt01;
					c0b = '-';
				}
				else {
					volt0 = volt01 - volt00;
					c0b = '+';
				}
			}
            
			
			calc_value16(888);
		//	c0b = c0;
			c0c = c1;
			c0d = c2;
			c0e = c3;
			c0f = c4;
			
			calc_value16(999);
			c1b = c0;
			c1c = c1;
			c1d = c2;
			c1e = c3;
			c1f = c4;
			
			//PORTB.7 = 1;
			print();
			//PORTB.7 = 0;
		}
		delay_50u();
        //*/
	}
}

void move_left(void) {
    msg[0] = 0xff;
    msg[1] = 0x01;
    msg[2] = 0x00;
    msg[3] = 0x04;
    msg[4] = 0x10;
    msg[5] = 0x00;
    msg[6] = 0x15;
    send_msg();
}

void move_right(void) {
    msg[0] = 0xff;
    msg[1] = 0x01;
    msg[2] = 0x00;
    msg[3] = 0x02;
    msg[4] = 0x10;
    msg[5] = 0x00;
    msg[6] = 0x13;
    send_msg();
}

void move_stop(void) {
    msg[0] = 0xff;
    msg[1] = 0x01;
    msg[2] = 0x00;
    msg[3] = 0x00;
    msg[4] = 0x00;
    msg[5] = 0x00;
    msg[6] = 0x01;
    send_msg();
}



void send_msg(void) {
    uint8_t i = 0;
    GIE = 0;
    
    TXIF = 0;
    TXEN = 1;
    for(i = 0; i < 7; i++) {
        
        TXREG = msg[i];
        //TXEN = 1;
        while(TXIF == 0) continue;
        TXIF = 0;
    }
    GIE = 1;
}


void Init_UART(void) {
    SPBRG = 31;//129;//31;
    
    TXSTA = 0;
    //TXEN = 1;
    
    //PORTB.0 = 1;
    
    RCSTA = 0;
    SPEN = 1;
    
    RCIE = 1;
    //TXIE = 1;
    
    //TXREG = 'X';
    TXEN = 1;
    
}


#pragma codepage 0


u16 get_angle(void) {
    u8 counter;
    u16 angle = 0;
    
    //PORTB.4 = 0;
    for(counter = 0; counter < 14; counter++) {
        //PORTB.4 = 1;
        RLF(angle, 1);
        angle.0 = PORTB.5;
        //PORTB.4 = 0;
    }
    //PORTB.4 = 1;
    return angle;
}


void print(void) {
	cmd_send(0x02);		// to begin
	cmd_send(0x80);		// 1st string
	

	byte_send(c00);
	byte_send(c01);
	byte_send(c02);
	byte_send(c03);
	// 0x04
	byte_send(c04);
	byte_send(c05);
	byte_send(c06);
	byte_send(c07);
	// 0x08
	byte_send(c08);
	byte_send(c09);
	byte_send(c0a);
	byte_send(c0b);
	// 0x0c
	byte_send(c0c);
	byte_send(c0d);
	byte_send(c0e);
	byte_send(c0f);
	// 0x0f
	
	cmd_send(0x02);		// to begin
	cmd_send(0x80);		// 1st string
	cmd_send(0xc0);		// 2nd string
	
	byte_send(c10);
	byte_send(c11);
	byte_send(c12);
	byte_send(c13);
	// 0x14
	byte_send(c14);
	byte_send(c15);
	byte_send(c16);
	byte_send(c17);
	// 0x18
	byte_send(c18);
	byte_send(c19);
	byte_send(c1a);
	byte_send(c1b);
	// 0x1c
	byte_send(c1c);
	byte_send(c1d);
	byte_send(c1e);
	byte_send(c1f);
	// 0x1f
	
	cmd_send(0x02);		// to begin
	//cmd_send(0xc0);		// 2nd string
	cmd_send(0x80);		// 1st string
	
	TRISD = 0b00000011;
	
	btn0 = !PORTD.0;
	Carry = !PORTD.0;
	RRF(btn0_buf, 1);
	
	btn1 = !PORTD.1;
	Carry = !PORTD.1;
	RRF(btn1_buf, 1);
	
	TRISD = 0b00000000;
	
	update_lcd_flag = 0;
}


void byte_send(u8 bs) {
	GIE = 0;
	lcd_data = bs;
	pc_tmp = PORTC;
	pc_tmp |= rs;
	pc_tmp |= e;
	PORTC = pc_tmp;
	nop();
	nop();
	nop();
	nop();
	nop();
	pc_tmp &= ~e;
	PORTC = pc_tmp;
	while (busy_check()) continue;
	GIE = 1;
	delay_50u();
}


void cmd_send(u8 bs) {
	GIE = 0;
	lcd_data = bs;
	pc_tmp = PORTC;
	pc_tmp &= ~rs;
	pc_tmp |= e;
	PORTC = pc_tmp;
	nop();
	nop();
	nop();
	nop();
	nop();
	pc_tmp &= ~e;
	PORTC = pc_tmp;
	while (busy_check()) continue;
	GIE = 1;
	delay_50u();
}


void cmd_send_noACK(u8 bs) {
	GIE = 0;
	lcd_data = bs;
	pc_tmp = PORTC;
	pc_tmp &= ~rs;
	pc_tmp |= e;
	nop();
	nop();
	nop();
	nop();
	nop();
	pc_tmp &= ~e;
	PORTC = pc_tmp;
	GIE = 1;
	delay_50u();
}


void calc_value16(u16 value) {
	c0 = 0;
	c1 = 0;
	c2 = 0;
	c3 = 0;
	c4 = 0;
	
	if(value < 10000)
		c0 = 0;
	else {
		while(value >= 10000) {
			value -= 10000;
			c0++;
		}
	}
	
	if(value < 1000)
		c1 = 0;
	else {
		while(value >= 1000) {
			value -= 1000;
			c1++;
		}
	}
	
	if(value < 100)
		c2 = 0;
	else {
		while(value >= 100) {
			value -= 100;
			c2++;
		}
	}
	
	if(value < 10)
		c3 = 0;
	else {
		while(value >= 10) {
			value -= 10;
			c3++;
		}
	}
	
	c4 = value;
	
	c0 = convert_char(c0);
	c1 = convert_char(c1);
	c2 = convert_char(c2);
	c3 = convert_char(c3);
	c4 = convert_char(c4);
}


u8 convert_char(u8 char0) {
	if(char0 == 0)
		return '0';
	if(char0 == 1)
		return '1';
	if(char0 == 2)
		return '2';
	if(char0 == 3)
		return '3';
	if(char0 == 4)
		return '4';
	if(char0 == 5)
		return '5';
	if(char0 == 6)
		return '6';
	if(char0 == 7)
		return '7';
	if(char0 == 8)
		return '8';
	if(char0 == 9)
		return '9';
	return 0;
	
}


void delay(u8 dly_val) {
//	u8 dly_val;
//	u8 wait_val;

	while(dly_val > 0) {
		dly_val--;
		u8 dly_val0 = 0xff;
		while(dly_val0 > 0) {
			dly_val0--;
			u8 dly_val1 = 0xff;
			while(dly_val1 > 0) {
				dly_val1--;
				nop();
				nop();
				nop();
			}
		}
	}
}


u8 busy_check(void) {
	u8 ack=0;
	pc_tmp = PORTC;
	pc_tmp &= ~(rs | rw | e);
	PORTC = pc_tmp;
	lcd_tris = 0xff;
	pc_tmp |= rw;
	PORTC = pc_tmp;
	pc_tmp |= rw | e;
	PORTC = pc_tmp;
	nop();
	ack = lcd_data;
	ack &= 0x80;
	pc_tmp &= ~e;
	PORTC = pc_tmp;
	pc_tmp &= ~rw;
	PORTC = pc_tmp;
	lcd_tris = 0x00;
	return ack;
}


void lcd_init(void) {
	pc_tmp = 0;
	PORTC = 0;
	tmp8 = 15;
	TMR0 = 0;
	T0IF = 0;
	do {
		while (!T0IF) continue;
		T0IF = 0;
		tmp8 --;
	}
	while (tmp8);		// delay
	cmd_send_noACK(0x30);
	
	tmp8 = 15;
	TMR0 = 0;
	T0IF = 0;
	do {
		while (!T0IF) continue;
		T0IF = 0;
		tmp8 --;
	}
	while (tmp8);		// delay
	cmd_send_noACK(0x30);
	
	TMR0 = 0;
	T0IF = 0;
	while (!T0IF) continue;
	cmd_send_noACK(0x30);
	
	TMR0 = 0;
	T0IF = 0;
	while (!T0IF) continue;
//
	cmd_send(0x38);		// 8 bit, 2 strings
	cmd_send(0b00001000);		// lcd off
	cmd_send(0x01);		// reset lcd
	cmd_send(0x06);		// shift right
	cmd_send(0x0c);		// lcd on
//	cmd_send(0x40);
}


void delay_10u(void) {
    u8 tmp_delay = 0x9;
	while(tmp_delay != 0) {
		tmp_delay--;
        //nop();

    }
}


void delay_50u(void) {
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	
	nop();
	nop();
	
	
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	nop();
	
//	u8 tmp_delay=3;
//	while(tmp_delay != 0)
//	{
//		tmp_delay--;
//	}
}
