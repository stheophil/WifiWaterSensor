# What is this?

This repository contains the code and 3D source files to create a simple water level sensor that can be attached to a bucket of water, e.g. on your balcony, from which you're watering your plants using [self-watering probes](http://www.amazon.com/Self-Watering-Probes-Package-of-5/dp/B0002VAHXC). 

# Parts

You will need a few things to assemble the water level sensor:  

- [A simple float switch](http://www.ebay.co.uk/itm/New-Liquid-Water-Level-Sensor-Horizontal-Float-Switch-UK-seller/281535436270?_trksid=p2047675.c100005.m1851&_trkparms=aid%3D222007%26algo%3DSIC.MBE%26ao%3D1%26asc%3D20140122125356%26meid%3Dbb54abe65c6a44788b7bfc30358d424f%26pid%3D100005%26rk%3D1%26rkt%3D2%26sd%3D111683723239&rt=nc)  
- [A charging circuit for 18650 lithium batteries](http://www.aliexpress.com/item/Micro-USB-5V-1A-18650-Lithium-Battery-Charging-Board-Charger-Module-With-Protection/32265626505.html)  
- [A holder for an 18650 lithium battery](http://www.aliexpress.com/item/FREE-SHIPPING-5-Pcs-New-18650-Battery-3-7V-Clip-Holder-Box-Case-Black-With/32331098387.html)  
- 3mm screws. You have to experiment which ones work best. The holes have a diameter of about 2mm.  

These parts cost about $1 each.   

- A 18650 lithium ion battery. Available e.g. at Amazon. Don't take the cheapest ones.   
- A programmable microprocessor with Wifi, e.g. the [Adafruit ESP8266 Huzzah](http://www.adafruit.com/product/2471) or a generic NodeMCU board. Maximum size about 25mm x 50mm.   

These parts cost about 10$ each. 

- You'll probably need a soldering iron and some cables.   

And last but not least a 3D printer to print the enclosure and inner structure that holds all these things together. 

# Assembly 

![image](http://thingiverse-production-new.s3.amazonaws.com/renders/7e/ba/90/2a/41/IMG_0096_preview_featured.jpg)

- Download the STL files from [thingiverse.com](http://www.thingiverse.com/thing:862976) and print them. 
- Connect battery holder and charging circuit e.g. by soldering them together. 
- Connect charging circuit and ESP8266 board with (female) jumper cables. 
	_(That's important! Don't solder them together. I had problems flashing the chip when it ran directly off the battery. Probably because the battery provides more than 3.3V which may have confused the USB-serial converter.)_

- See the documentation of the ESP8266 board that you use. You probably need to connect GPIO16 to the RESET pin to enable deep sleep mode. Other boards than the Adafruit board [may require more connections to work at all](http://blog.squix.ch/2015/02/esp8266-esp-201-breakout-board-review.html).

- Stick float switch cables through the hole in the outer sensor enclosure. Connect them to the Wifi board. One cable goes to GND, the other to GPIO13. Again, it may be a good idea to solder the switch cables to female breadboard connectors. 

- Glue everything in place. I used strong double-sided foam tape. 

# Flash 

- Change Wifi configuration in `sketch/sketch.ino` and register at thingspeak.com. Also insert your thingspeak.com API key. 
- Again, see the docs for your ESP8266 board on how to flash it. 

# Finish

- Insert a battery, put everything inside the enclosure and close it with two screws. 