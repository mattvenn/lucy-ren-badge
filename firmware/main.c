#include "main.h"
#include <util/delay.h>

int main(void) {
    SET_OUTPUT(DDRC,PWM_R_PIN);
    SET_OUTPUT(DDRC,PWM_G_PIN);
    SET_OUTPUT(DDRC,PWM_B_PIN);
    HIGH(PORTC,PWM_R_PIN);
    HIGH(PORTC,PWM_G_PIN);
    HIGH(PORTC,PWM_B_PIN);

    SET_INPUT(DDRA, MODE_PIN);
    HIGH(PORTA,MODE_PIN); // pull up

    while(1) {
        if(PINA & _BV(MODE_PIN))
        {
            _delay_ms(100);
            LOW(PORTC,PWM_R_PIN);
            _delay_ms(100);
            HIGH(PORTC,PWM_R_PIN);
        }
        else
        {
            _delay_ms(50);
            LOW(PORTC,PWM_B_PIN);
            _delay_ms(50);
            HIGH(PORTC,PWM_B_PIN);
        }
    }
    __builtin_unreachable();
}
