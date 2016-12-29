# tinytemp
Using an ATtiny, read temperature from a DS18B20 and transmit it using a 433 MHz tx module

I got tired of buying overpriced inaccurate wireless thermometers for my house monitoring system, so decided to make my own instead. The current version uses the SD18B20 sensor which is ±0.5°C accurate, but I'm tempted to go for the impressively accurate ±0.1°C [IST TSIC 506F](http://se.farnell.com/ist-innovative-sensor-technology/tsic-506f-to92/sensor-temp-digital--0-1k-to92/dp/2191826) in the future.

This program uses my FineOffset library: https://github.com/zagor/FineOffset
