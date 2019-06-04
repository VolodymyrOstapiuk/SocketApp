avr:libs?=
avr:file?=main
avr:mcu?=atmega328p
avr:
	avr-gcc -Wall -o $(file).o $(file).c $(libs) -O2 -mmcu=$(mcu) -std=c99 && avr-objcopy $(file).o $(file).hex -O ihex
nano328p: device?=atmega328p 
nano328p: programmer?=arduino 
nano328p: port?=COM4 
nano328p: speed?=57600  
nano328p: hexfile?=main
nano328p:
	avrdude -v -p $(device) -c $(programmer) -P $(port) -b $(speed) -D -Uflash:w:$(hexfile).hex:i
uno: device?=atmega328p 
uno: programmer?=arduino 
uno: port?=COM4 
uno: speed?=115200  
uno: hexfile?=main
uno:
	avrdude -v -p$(device) -c$(programmer) -P$(port) -b$(speed) -D -Uflash:w:$(hexfile).hex:i
nano168: device?=atmega168 
nano168: programmer?=arduino 
nano168: port?=COM4 
nano168: speed?=19200
nano168: hexfile?=main
nano168:
	avrdude -v -p $(device) -c $(programmer) -P $(port) -b $(speed) -D -Uflash:w:$(hexfile).hex:i
mega2560: device?=atmega2560 
mega2560: programmer?=arduino 
mega2560: port?=COM4 
mega2560: speed?=115200  
mega2560: hexfile?=main
mega2560:
	avrdude -v -p $(device) -c $(programmer) -P $(port) -b $(speed) -D -Uflash:w:$(hexfile).hex:i
mega1280: device?=atmega1280 
mega1280: programmer?=arduino 
mega1280: port?=COM4 
mega1280: speed?=57600  
mega1280: hexfile?=main
mega1280:
	avrdude -v -p $(device) -c $(programmer) -P $(port) -b $(speed) -D -Uflash:w:$(hexfile).hex:i
leonardo: device?=atmega32u4 
leonardo: programmer?=avr109 
leonardo: port?=COM4 
leonardo: speed?=57600  
leonardo: hexfile?=main
leonardo:
	avrdude -v -p $(device) -c $(programmer) -P $(port) -b $(speed) -D -Uflash:w:$(hexfile).hex:i
micro: device?=atmega32u4 
micro: programmer?=avr109 
micro: port?=COM4 
micro: speed?=57600  
micro: hexfile?=main
micro:
	avrdude -v -p $(device) -c $(programmer) -P $(port) -b $(speed) -D -Uflash:w:$(hexfile).hex:i
gcc:libs?=
gcc:file?=main
gcc:	
	gcc -Wall $(file).c	$(libs) -o $(file).o $(file).exe
g++:libs?=
g++:file?=main
g++:	
	g++ -Wall $(file).cpp $(libs) -o $(file).exe