# Raspberry-HT1621B

HT1621B Segment LED Example Code for RaspberryPi

I ported from [here](https://github.com/marc-gist/HT1621).


# Software requiment   
- WiringPi Library   
 This project uses the wiringPiSetup() function to initialize GPIOs.   
 If you use it on a board other than the RPI board, you may need to change the WiringPi number.   
 As far as I know, there are these libraries.   
	- WiringPi for OrangePi   
	- WiringPi for BananaPi   
	- WiringPi for NanoPi   
	- WiringPi for Pine-64   

# Wireing
|HT1621B||RaspberryPi|
|:-:|:-:|:-:|
|DATA|--|GPIO17(#11)|
|RW|--|GPIO18(#12)|
|CS|--|GPIO27(#13)|
|VCC|--|5V|
|GND|--|GND|

(*)You can change to other GPIO.  
```
#define DATA 0
#define RW   1
#define CS   2
```

# TS206
cc -o ts206 ts206.c -lwiringPi
![ts206-seg6](https://cloud.githubusercontent.com/assets/6020549/23609495/a4f7d5be-02b1-11e7-953a-e61938011230.JPG)

# TS119
cc -o ts119 ts119.c -lwiringPi
![ts119-12](https://cloud.githubusercontent.com/assets/6020549/23609760/f116efa6-02b2-11e7-8f0c-e774e34fd692.JPG)

# TS125
cc -o ts125 ts125.c -lwiringPi
![ts125-17](https://cloud.githubusercontent.com/assets/6020549/23609794/21346268-02b3-11e7-9733-46c4811a3e73.JPG)

