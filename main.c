#include <msp430.h> 
#include "lcdLib.h"
/**
 * main.c
 */


//constants and variables
unsigned int ADC_value=0;
const static int Vcc=5;
static int dividerResistance=47500;
float flexVoltage=0;
unsigned int flexResistance=0;

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	lcdInit();

	lcdClear();

	while(1)
	{
	    //Reading flex sensor resistances one-by-one
	    unsigned int sensorValue0 = readSensor(0);
	    unsigned int sensorValue1 = readSensor(1);
	    unsigned int sensorValue2 = readSensor(2);
	    unsigned int sensorValue3 = readSensor(3);
	    unsigned int sensorValue4 = readSensor(4);

	    if(sensorValue0 < 65000) //Deciding whether flex is bent or not and then printing the message
	    {
	        lcdClear();
	        lcdSetText("MERHABA",0,0);
	    }

	    if(sensorValue1 < 5000) //Deciding whether flex is bent or not and then printing the message
	    {
	        lcdClear();
	        lcdSetText("NASILSIN",0,0);
	    }

	    if(sensorValue2 < 5000) //Deciding whether flex is bent or not and then printing the message
	    {
	        lcdClear();
	        lcdSetText("TESEKKURLER",0,0);
	    }

	    if(sensorValue3 < 25000)
	    {
	        lcdClear();
	        lcdSetText("GUNAYDIN",0,0);
	    }

	    if(sensorValue4 < 30000)
	    {
	        lcdClear();
	        lcdSetText("5. Flex Sensor is bent",0,0);
	    }
	}
}



unsigned int readSensor(int pin)
{
    switch(pin)
    {
          case 0:
              BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
              BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
              P1SEL |= BIT0; // ADC input pin P1.0
              ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
              ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
              ADC10AE0 &= BIT0; // ADC input enable P1.0

              delay_us(1000);               // Wait for ADC Ref to settle
              ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
              //__bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
              ADC_value = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value
              flexVoltage = ADC_value * Vcc / 1023.0; //flexADC * VCC / 1023.0;
              flexResistance = dividerResistance * (Vcc / flexVoltage - 1);//R_DIV * (VCC / flexV - 1.0);
              return flexResistance;
          case 1:
              BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
              BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
              P1SEL |= BIT1; 				  // ADC input pin P1.1
              ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
              ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
              ADC10AE0 &= BIT1; 			  // ADC input enable P1.1

              delay_us(1000);               // Wait for ADC Ref to settle
              ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
              //__bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
              ADC_value = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value
              flexVoltage = ADC_value * Vcc / 1023.0; //flexADC * VCC / 1023.0;
              flexResistance = dividerResistance * (Vcc / flexVoltage - 1);//R_DIV * (VCC / flexV - 1.0);
              return flexResistance;
          case 2:
              BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
              BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
              P1SEL |= BIT2; 				  // ADC input pin P1.1
              ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
              ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
              ADC10AE0 &= BIT2; // ADC input enable P1.2

              delay_us(1000);               // Wait for ADC Ref to settle
              ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
              //__bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
              ADC_value = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value
              flexVoltage = ADC_value * Vcc / 1023.0; //flexADC * VCC / 1023.0;
              flexResistance = dividerResistance * (Vcc / flexVoltage - 1);//R_DIV * (VCC / flexV - 1.0);
              return flexResistance;
          case 3:
              BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
              BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
              P1SEL |= BIT3; // ADC input pin P1.3
              ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
              ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
              ADC10AE0 &= BIT3; // ADC input enable P1.3

              delay_us(1000);               // Wait for ADC Ref to settle
              ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
              //__bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
              ADC_value = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value
              flexVoltage = ADC_value * Vcc / 1023.0; //flexADC * VCC / 1023.0;
              flexResistance = dividerResistance * (Vcc / flexVoltage - 1);//R_DIV * (VCC / flexV - 1.0);
              return flexResistance;
          case 4:
              BCSCTL1 = CALBC1_1MHZ;          // Set range   DCOCTL = CALDCO_1MHZ;
              BCSCTL2 &= ~(DIVS_3);           // SMCLK = DCO = 1MHz
              P1SEL |= BIT4; // ADC input pin P1.4
              ADC10CTL1 = INCH_3 + ADC10DIV_3 ;         // Channel 3, ADC10CLK/3
              ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;  // Vcc & Vss as reference, Sample and hold for 64 Clock cycles, ADC on, ADC interrupt enable
              ADC10AE0 &= BIT4; // ADC input enable P1.4

              delay_us(1000);               // Wait for ADC Ref to settle
              ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
              //__bis_SR_register(CPUOFF + GIE);    // Low Power Mode 0 with interrupts enabled
              ADC_value = ADC10MEM;               // Assigns the value held in ADC10MEM to the integer called ADC_value
              flexVoltage = ADC_value * Vcc / 1023.0; //flexADC * VCC / 1023.0;
              flexResistance = dividerResistance * (Vcc / flexVoltage - 1);//R_DIV * (VCC / flexV - 1.0);
              return flexResistance;
          default :
             return 0.000;
       }


}
