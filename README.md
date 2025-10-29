# 🧠 STM32F446RE – 7 Segment Display (Bare Metal Programming)

## 📘 Project Overview
This project demonstrates how to **interface a 7-Segment Display** with the **STM32F446RE** microcontroller using **Bare Metal Programming** in **Keil µVision**.  
No HAL libraries, no CubeMX — just pure register-level control using the CMSIS header (`stm32f446xx.h`).

The 7-Segment display is driven by setting individual GPIO pins to represent numbers `0–9`.

---

## ⚙️ Hardware Details

**Microcontroller:** STM32F446RE  
**IDE:** Keil µVision  
**Programming Method:** Bare Metal (Register-level)  
**Display Type:** Common Anode 7-Segment  

### 🧩 Pin Configuration

| Segment | Pin Name | Port | Pin No. |
|----------|-----------|------|---------|
| a | PA10 | GPIOA | 10 |
| b | PB3  | GPIOB | 3  |
| c | PB5  | GPIOB | 5  |
| d | PB4  | GPIOB | 4  |
| e | PB10 | GPIOB | 10 |
| f | PA8  | GPIOA | 8  |
| g | PA9  | GPIOA | 9  |
| dp | PC7 | GPIOC | 7  |

---

## 🔩 Code Description

### 1️⃣ GPIO Clock Enable
```c
RCC->AHB1ENR |= (1<<0) | (1<<1) | (1<<2); // Enable GPIOA, GPIOB, GPIOC
```
### 2️⃣ Pin Mode Configuration

Each segment pin is configured as output using the MODER register.
```c
GPIOA->MODER |= (1<<16) | (1<<18) | (1<<20); // PA8, PA9, PA10
GPIOB->MODER |= (1<<6) | (1<<8) | (1<<10) | (1<<20); // PB3, PB4, PB5, PB10
GPIOC->MODER |= (1<<14); // PC7
```
### 3️⃣ Display Data Function

Each bit of data corresponds to one segment of the display.
```c
void Printdata(unsigned char data) {
  if(data & 0x01) GPIOA->ODR |= (1<<10); else GPIOA->ODR &= ~(1<<10); // a
  if(data & 0x02) GPIOB->ODR |= (1<<3);  else GPIOB->ODR &= ~(1<<3);  // b
  if(data & 0x04) GPIOB->ODR |= (1<<5);  else GPIOB->ODR &= ~(1<<5);  // c
  if(data & 0x08) GPIOB->ODR |= (1<<4);  else GPIOB->ODR &= ~(1<<4);  // d
  if(data & 0x10) GPIOB->ODR |= (1<<10); else GPIOB->ODR &= ~(1<<10); // e
  if(data & 0x20) GPIOA->ODR |= (1<<8);  else GPIOA->ODR &= ~(1<<8);  // f
  if(data & 0x40) GPIOA->ODR |= (1<<9);  else GPIOA->ODR &= ~(1<<9);  // g
  if(data & 0x80) GPIOC->ODR |= (1<<7);  else GPIOC->ODR &= ~(1<<7);  // dp
}
```
### 4️⃣ Number Pattern Table
Digit	Hex Code
0	0x3F
1	0x06
2	0x5B
3	0x4F
4	0x66
5	0x6D
6	0x7D
7	0x07
8	0x7F
9	0x6F
### ▶️ Execution Flow

Enable clocks for GPIOA, GPIOB, GPIOC.

Configure GPIO pins as outputs.

Continuously display digits 0–9 with a delay between transitions.

## 🧠 Key Learning Points

Register-level GPIO configuration (MODER, ODR, AHB1ENR)

Bitwise operations to control individual LED segments

Implementing software delay loops and data masking in embedded systems

## 🚀 Future Improvements

Add support for multiple 7-segment displays using multiplexing

Implement timer-based delay instead of software delay

Integrate push button input to manually increment the displayed digit
