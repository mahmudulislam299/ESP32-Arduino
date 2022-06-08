SERIAL_ESP32_PORT = COM4
CC = arduino-cli
FQBN3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,LoopCore=1,EventsCore=1,DebugLevel=none
CFLAGS_LILYGO = --build-property build.extra_flags="-DESP32_LILYGO"
CFLAGS_DEVKIT = --build-property build.extra_flags="-DESP32_DEVKIT"


build_l:
	$(CC) compile -b $(FQBN3) $(CFLAGS_LILYGO) --warnings all 

build:
	$(CC) compile -b $(FQBN3) $(CFLAGS_DEVKIT) --warnings all 

upload:
	$(CC) upload -b $(FQBN3)   -p $(SERIAL_ESP32_PORT)  -v -t