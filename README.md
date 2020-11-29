# RGBLED_RaspPi4_DeviceDriver
Robot Systems Task 1<br>
(ロボットシステム学 課題1)

---
## Description
Using RGB_LED, I created a device driver that lights the LED in the specified color.<br>
(RGB_LEDを用いて，指定した色にLEDを点灯させるデバイスドライバを作成しました.)

It was created by modifying the device driver created by Professor Ryuichi Ueda in class.<br>
(上田隆一教授が授業で作成したデバイスドライバを改変し作成しました.)

Click [here](https://youtu.be/xQW8-FNuboo) for a video of the class.<br>
(授業の動画は[こちら](https://youtu.be/xQW8-FNuboo)です.)

---
## Movie

[![デモ動画](https://img.youtube.com/vi//maxresdefault.jpg)](https://youtu.be/)

Click the image to jump to Youtube.<br>
(画像をクリックするとYoutubeに飛びます.)

---
## Requirements
|No.|Item Name|Quantity|
|---|---|---|
|1|[Raspberry Pi4 ModelB](https://akizukidenshi.com/catalog/g/gM-14778/)|1|
|2|[bread board](https://akizukidenshi.com/catalog/g/gP-05155/)|1|
|3|[Plug-Socket Jumper cable](https://www.aitendo.com/product/16084)|4|
|4|[RGB Full color LED](https://akizukidenshi.com/catalog/g/gI-02476/)|1|
|5|[150Ω Resistor](https://akizukidenshi.com/catalog/g/gR-16151/)|3|

---
## Circuit
- Circuit diagram(回路図)
<img src="" width="320px">

- Wiring diagram (配線図)
<img src="https://user-images.githubusercontent.com/53966390/100541151-35d32000-3285-11eb-9579-d510d458697c.jpg" width="320px">


- GPIO pin to connect (接続するGPIOピン)
  |No.|Name|CableColor|GPIO|PinNumber|
  |---|---|---|---|---|
  |1|Red LED|Red|GPIO23|16|
  |2|GND|Black||20|
  |3|Blue LED|Blue|GPIO24|18|
  |4|Green LED|Green|GPIO25|22|

Check [here](https://www.raspberrypi.org/documentation/usage/gpio/README.md) for GPIO and pin numbers.<br>
(GPIO・ピン番号については[こちら](https://www.raspberrypi.org/documentation/usage/gpio/README.md)で確認してください．)

---
## Build

```
$ git clone https://github.com/MasatoKubotera/RGBLED_RaspPi4_DeviceDriver.git
$ cd RGBLED_RaspPi4_DeviceDriver
$ make
$ sudo insmod RGB_LED.ko
$ sudo chmod 666 /dev/RGB_LED0
```
---
## Run
Enter the initial of the color you want to light in `dev / RGB_LED0` and it will light for 3 seconds.<br>
(点灯させたい色の頭文字を`dev/RGB_LED0 `に入力すると3秒間点灯します.)

1.  Red<br>
  `$ echo R > /dev/RGB_LED0` or `$ echo R > /dev/RGBLED0`
  <img src="https://user-images.githubusercontent.com/53966390/100541013-6a92a780-3284-11eb-9e51-569623416ff1.png" width="320px">

2.  Green<br>
  `$ echo G > /dev/RGB_LED0` or `$ echo g > /dev/RGBLED0`
  <img src="https://user-images.githubusercontent.com/53966390/100541017-6c5c6b00-3284-11eb-953c-b9fd230c7838.png" width="320px">

3.  Brue<br>
  `$ echo B > /dev/RGB_LED0` or `$ echo b > /dev/RGBLED0`
  <img src="https://user-images.githubusercontent.com/53966390/100541020-6d8d9800-3284-11eb-8be1-9aa364b14689.png" width="320px">

4.  Yellow<br>
  `$ echo Y > /dev/RGB_LED0` or `$ echo y > /dev/RGBLED0`
  <img src="https://user-images.githubusercontent.com/53966390/100541021-6ebec500-3284-11eb-9bc2-84ff7a381d82.png" width="320px">

5.  Cyan<br>
  `$ echo C > /dev/RGB_LED0` or `$ echo c > /dev/RGBLED0`
  <img src="https://user-images.githubusercontent.com/53966390/100541023-6f575b80-3284-11eb-8c4d-d965b76742ac.png" width="320px">

6.  Magenta<br>
  `$ echo M > /dev/RGB_LED0` or `$ echo m > /dev/RGBLED0`
  <img src="https://user-images.githubusercontent.com/53966390/100541024-70888880-3284-11eb-8894-0653a3fc2229.png" width="320px">

7. White<br>
  `$ echo W > /dev/RGB_LED0` or `$ echo w > /dev/RGBLED0`
  <img src="https://user-images.githubusercontent.com/53966390/100541011-66ff2080-3284-11eb-9beb-31c4be142489.png" width="320px">

---
## License
[GNU General Public License v3.0](https://github.com/MasatoKubotera/RGBLED_RaspPi4_DeviceDriver/blob/master/LICENSE)