# tinytemp
Using an ATtiny, read temperature from a DS18B20 and transmit it with a 433 MHz tx module.

I got tired of buying overpriced inaccurate wireless thermometers for my home monitoring, so decided to make my own.

This program uses my [FineOffset library](https://github.com/zagor/FineOffset) 
and Paul Stoffregen's [OneWire library](https://github.com/PaulStoffregen/OneWire.git).

# Hardware used

* AVR ATtiny85. The software compiles to ~3500 bytes so it should to fit in an ATtiny45 too, but I have only tried the 85.
* [DS18B20](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS18B20.html) 1-wire thermometer. This thermometer is ±0.5°C accurate which is pretty good, but I'm tempted to spend a little extra for the impressive ±0.1°C accurate [IST TSIC 506F](http://se.farnell.com/ist-innovative-sensor-technology/tsic-506f-to92/sensor-temp-digital--0-1k-to92/dp/2191826) for the next batch.
* FS1000A 433 MHz tx module. Add a 17cm long wire to the ANT pad to get useful range.
* AA battery
* 5V DC-DC boost converter to step up the voltage from the battery to 5V. You can use lower voltage, but the TX power of the FS1000A is rather linear to the supply voltage so you don't want to go too low in real-world applications.
* LED as activity indicator

# Battery life

This setup sleeps at around 90 µW and wakes up every 4 minutes to draw 10 mW for half a second. Using a 2300 mAh NiMH AA battery, this translates to over 3 years of battery life. The self-discharge of normal NiMH batteries is much bigger than that, so use a low-self-discharge NiMH2 type battery (or use a LiPo).

Update 2018-06-01: My first deployed devices are now running out of battery. This means the 2300 mAh NiMH battery shown in the below image lasted ~18 months in real-life conditions.

# Photo

![Photo of tinytemp module](https://github.com/zagor/tinytemp/blob/master/photo.jpg)

# Illustration

This is an illustration with some roughly matching components I found in Fritzing. It's not perfectly accurate.

![Image of tinytemp module](https://github.com/zagor/tinytemp/blob/master/tinytemp.png)
