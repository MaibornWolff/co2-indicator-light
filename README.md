# co2-indicator-light
This project presents the co2 indicator light, which is used at several places since summer 2018. The indicator-light at the sensor is the direct feedback for the people in the same room. The firmware takes the measurement of the co2 sensors and shows the result at the neopixel led. 
It is possible to transmit the values of co2, temperature and humidity to a MQTT service of your choice. 

## Parts
<ul>
<li>Wemos D1 mini ESP8266 </li>
<li>MH-Z14A co2 sensor</li>
<li>DHT22 temperature & humidity sensor</li>
<li>neopixel 8 led smd</li>
<li>5V USB powersupply + micro-USB cable</li>
</ul>

## Printed Parts
Two parts need to be printed. The case itself is one piece and can be printed without support. The lid is separated in two parts, the lid and the diffuse window for the indicator. 
#### Printers with one extruder
Align the lid and the diffusor part in your slicer, then slice two files, one with only the diffusor selected, one with only the lid. Start with the diffusor, which is a very thin layer of white or another bright color. After the print is finished, leave the part on your build plate, change the filament to whatever you want to use as the main color and print the lid ontop. The lid should now be melted together with the first printed diffusor. 

#### Printers with multicolor or >2 extruders
Print all the parts, the lid is a multicolor part. For the diffusor, choose white or a very bright color to make the light visible.

## Assembly 
First, assemble the electronics as shown in the schematic, then proceed to install it into the case. The neopixel and microcontroller boards are fixed with m3 screws. The lid snaps in the case. To power up your device or upload the code, connect the micro-USB cable to the microcontroller.
