#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

#define PWM_R_PIN 0
#define PWM_G_PIN 1
#define PWM_B_PIN 2

#define MODE_PIN 0

#define SET_OUTPUT(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define SET_INPUT(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

#define HIGH(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define LOW(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
