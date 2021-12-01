#include <msp430g2553.h>

volatile long temp, tempRaw;//Declares later used variables
volatile long bright;//Declares later used variables

void ConfigureAdc_temp();

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    ConfigureAdc_temp();      //Activates ADC Based on function
    _delay_cycles(5);         // Wait for ADC Ref to settle


    while(1){

         tempRaw = ADC10MEM;                // read the converted data into a variable
         temp = (((tempRaw-673)*423)/1024); //converts to degree celsius
    }
}



// Configure ADC Temperature
void ConfigureAdc_temp(){

     ADC10CTL1 = INCH_10 + ADC10DIV_0 + CONSEQ_2;       //1010 temp sensor, Divides clock by 1(no effect), Repeat single channel
     ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON ;//Vref+, Vss, 64 ATD clocks per sample, internal references, turn ADCON
     ADC10CTL0 |= ENC + ADC10SC + MSC;                  //Enable conversion, Start sample and conversion, Multiple sample and conversion
}
