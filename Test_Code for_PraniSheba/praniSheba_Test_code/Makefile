
SERIAL_PORT_v3=COM3




FQBN_PCB_v3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=160,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,LoopCore=1,EventsCore=1,DebugLevel=none




CC=arduino-cli

CFLAGS_PCB3_PROD =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010 -DSOFTWARE_I2C -DSTAND_ALONE"
CFLAGS_PCB32_PROD =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010 -DFRAM_V010 -DSTAND_ALONE"





build: 
	$(CC) compile -b $(FQBN_PCB_v3)  $(CFLAGS_PCB32_PROD) --warnings all

upload:
	$(CC) upload -b $(FQBN_PCB_v3)   -p $(SERIAL_PORT_v3)  -v -t


delete_lib:
	rm -rf ./src/lib
download:
	powershell  .\download.ps1

.PHONY: download delete_lib

# deploy_v1: 
# 	$(CC) compile -b $(FQBN_PCB_V1)  $(CFLAG_PCB1_DEV) -p $(SERIAL_PORT) -u -v -e -t 
# deploy_v2:
# 	$(CC) compile -b $(FQBN_PCB_v2)  $(CFLAG_PCB2_DEV) -p $(SERIAL_PORT)   -u -v -e -t 