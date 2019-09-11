#include "main.h"
#include <util/delay.h>

volatile uint8_t pwm_counter = 0;
uint8_t pwm_red = 0; 
uint8_t pwm_blue = 0; 
uint8_t pwm_green = 0; 

// initialize timer, interrupt and variable
void initPWM(void)
{
    // set up timer with prescaler = 8 and CTC (clear timer on compare) mode
    TCCR1B |= _BV(WGM12) | _BV( CS11);

    // initialize counter
    TCNT1 = 0;

    // initialize compare value
    OCR1A = 1;

    // enable compare interrupt
    TIMSK1 |= _BV(OCIE1A);

    // enable global interrupts
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    pwm_counter ++;

    if(pwm_counter >= pwm_red)
        HIGH(PORTC,PWM_R_PIN);  // off
    else
        LOW(PORTC,PWM_R_PIN);   // on

    if(pwm_counter >= pwm_green)
        HIGH(PORTC,PWM_G_PIN);  // off
    else
        LOW(PORTC,PWM_G_PIN);   // on

    if(pwm_counter >= pwm_blue)
        HIGH(PORTC,PWM_B_PIN);  // off
    else
        LOW(PORTC,PWM_B_PIN);   // on

}

void adj_delay_us(int ms)
{
  while (0 < ms)
  {  
    _delay_us(1);
    --ms;
  }
}

int main(void) 
{

    initPWM();

    srand(1); // could use ADC read value for this

    // set all RGB LED pins output
    SET_OUTPUT(DDRC,PWM_R_PIN);
    SET_OUTPUT(DDRC,PWM_G_PIN);
    SET_OUTPUT(DDRC,PWM_B_PIN);
    // and high (common anode, so LEDs are all off
    HIGH(PORTC,PWM_R_PIN);
    HIGH(PORTC,PWM_G_PIN);
    HIGH(PORTC,PWM_B_PIN);

    SET_INPUT(DDRA, MODE_PIN);
    HIGH(PORTA,MODE_PIN); // pull up

    uint8_t throb = 0;
    uint8_t throb_dir = 1;

    while(1) {
        if(PINA & _BV(MODE_PIN))
        {
            _delay_us(100);
            throb += throb_dir;

            if(throb == 255)
                throb_dir = -1;
            if(throb == 0)
                throb_dir = 1;


            pwm_blue    = gamma8[throb];
            pwm_red     = gamma8[throb];
            pwm_green   = 0;
        }
        else
        {
            adj_delay_us(rand() / (RAND_MAX / MAX_DIDDLE_DELAY_US + 1));
            pwm_red     = gamma8[rand() / (RAND_MAX / MAX_PWM_R + 1)];
            pwm_green   = gamma8[rand() / (RAND_MAX / MAX_PWM_G + 1)];
            pwm_blue    = gamma8[rand() / (RAND_MAX / MAX_PWM_B + 1)];
        }
    }
    __builtin_unreachable();
}


