SERIAL_PORT_v3=COM7


FQBN_PCB_V1=arduino:avr:uno
FQBN_PCB_v2=arduino:avr:pro:cpu=8MHzatmega328
#FQBN_PCB_v3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,DebugLevel=none
#FQBN_PCB_v3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,DebugLevel=none
FQBN_PCB_v3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=160,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,LoopCore=1,EventsCore=1,DebugLevel=none


CC=arduino-cli
CFLAGS_PCB3_PROD =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010"


build_v1: 
	$(CC) compile -b $(FQBN_PCB_v3) $(CFLAGS_PCB3_PROD) --warnings all

upload:
	$(CC) upload -b $(FQBN_PCB_v3)   -p $(SERIAL_PORT_v3)  -v -t



