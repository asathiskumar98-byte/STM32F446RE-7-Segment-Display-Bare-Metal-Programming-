#include "stm32f446xx.h"

void delay(long d)
{
	while(d--);
}

void Printdata(unsigned char data)  // data = 8 bit hexadecimal data
{
	// Bit 0 => a // a = PA10
	if((data&0x01) == 0x01) { GPIOA->ODR |= (1<<10);     }
	else                    { GPIOA->ODR &= (~(1<<10));  }
	// Bit 0 => b // b = PB3
	if((data&0x02) == 0x02) { GPIOB->ODR |= (1<<3);    }
	else                    { GPIOB->ODR &= (~(1<<3)); }
	// Bit 0 => c // c = PB5
	if((data&0x04) == 0x04) { GPIOB->ODR |= (1<<5);    }
	else                    { GPIOB->ODR &= (~(1<<5)); }
	// Bit 0 => d // d = PB4
	if((data&0x08) == 0x08) { GPIOB->ODR |= (1<<4);    }
	else                    { GPIOB->ODR &= (~(1<<4)); }
	// Bit 0 => e // e = PB10
	if((data&0x10) == 0x10) { GPIOB->ODR |= (1<<10);   }
	else                    { GPIOB->ODR &= (~(1<<10));}
	// Bit 0 => f // f = PA8
	if((data&0x20) == 0x20) { GPIOA->ODR |= (1<<8);    }
	else                    { GPIOA->ODR &= (~(1<<8)); }
	// Bit 0 => g // g = PA9
	if((data&0x40) == 0x40) { GPIOA->ODR |= (1<<9);    }
	else                    { GPIOA->ODR &= (~(1<<9)); }
	// Bit 0 => dp // dp = PC7
	if((data&0x80) == 0x80) { GPIOC->ODR |= (1<<7);    }
	else                    { GPIOC->ODR &= (~(1<<7)); }
}

int main(void)
{
	RCC->AHB1ENR = RCC->AHB1ENR | (1<<0) | (1<<1) | (1<<2);  // Clock of GPIO's Enabled GPIOA, GPIOB, GPIOC
	// all 7 Segment Terminals must be made output
	// a = PA10
	// b = PB3
	// c = PB5
	// d = PB4
	// e = PB10
	// f = PA8
	// g = PA9
	// dp = PC7
	
	GPIOA->MODER = GPIOA->MODER | (1<<16) | (1<<18) | (1<<20);
  GPIOA->MODER = GPIOA->MODER & (1<<17) & (1<<19) & (1<<21);   // PA10,PA9,PA8 as Output
	
	GPIOB->MODER = GPIOB->MODER | (1<<6) | (1<<8) | (1<<10) | (1<<20);
  GPIOB->MODER = GPIOB->MODER & (1<<7) & (1<<9) & (1<<11) & (1<<21);  // PB3,PB4,PB5,PB10 as Output
	
	GPIOC->MODER = GPIOC->MODER | (1<<14); 
  GPIOC->MODER = GPIOC->MODER & (1<<15);	// PC7 as Output
	
	while(1)
	{
		// Common Anode
		Printdata(0x3F);
		delay(500000);delay(500000);
		Printdata(0x06);
		delay(500000);delay(500000);
		Printdata(0x5B);
		delay(500000);delay(500000);
		Printdata(0x4F);
		delay(500000);delay(500000);
		Printdata(0x66);
		delay(500000);delay(500000);
		Printdata(0x6D);
		delay(500000);delay(500000);
		Printdata(0x7D);
		delay(500000);delay(500000);
		Printdata(0x07);
		delay(500000);delay(500000);
		Printdata(0x7F);
		delay(500000);delay(500000);
		Printdata(0x6F);
		delay(500000);delay(500000);
	}
}