/*
 * TinyTemp - Using an ATtiny, read temperature from a DS18B20 and
 * transmit it using a FS1000A 433 MHz tx module.
 *
 * Copyright (c) 2016 Björn Stenberg <bjorn@haxx.se>
 * License: MIT, see file LICENSE
 *
 */
#include <OneWire.h>
#include <FineOffset.h>

# include <avr/sleep.h>
# include <avr/wdt.h>
# define TX_PIN 2
# define TEMP_PIN 0
# define LED_PIN 3

#define DEVICE_ID 202
#define EBADTEMP -999

OneWire ow(TEMP_PIN);
FineOffset tx(TX_PIN);
byte addr[8];

ISR(WDT_vect) {
  //Don't do anything. This is just here so that we wake up.
}

void powerDown(int time) {

  if (time > 9 )
    time = 9; //Limit incoming amount to legal settings

  MCUSR &= ~(1<<WDRF); // Clear watch dog reset flag
  WDTCR |= (1<<WDCE) | (1<<WDE); // Set WD_change enable, set WD enable
  WDTCR = (time & 7) | (time & 8) << 2;
  WDTCR |= (1<<WDIE); // enable interrupt

  sleep_mode();
}

void flash_led(int count) {
  for (int i=0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
  }
}

void setup(void)
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // find temp sensor
  while (!ow.search(addr)) {
    flash_led(3);
    delay(750);
  }

  // setup power
  ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Power down everything, wake up from WDT
  sleep_enable();

}

double read_temp(void)
{
  ow.reset();
  ow.select(addr);
  ow.write(0x44, 1); // start conversion, with parasite power on at the end
  digitalWrite(LED_PIN, LOW);

  powerDown(WDTO_1S); // conversion takes 750ms

  digitalWrite(LED_PIN, HIGH);
  ow.reset();
  ow.select(addr);
  ow.write(0xBE); // read scratchpad

  byte data[9];
  ow.read_bytes(data, 9);
  if (OneWire::crc8(data, 8) != data[8])
    return EBADTEMP;

  return (data[1] << 8 | data[0]) / 16.0;
}

void loop(void)
{
  digitalWrite(LED_PIN, HIGH);
  double temp = read_temp();

  if (temp == EBADTEMP)
    flash_led(3);
  else
    tx.send(DEVICE_ID, temp);

  digitalWrite(LED_PIN, LOW);

  // full loop takes ~10 seconds, so 30 loops = ~300 sec = ~5 min
  for (int i=0; i<30; i++)
    powerDown(WDTO_8S);
}
