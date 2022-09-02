SERIAL_PORT_v2=COM6
SERIAL_PORT_v3=COM8
DEVICE = 3034
CODEVERSION= v1.0.2

FQBN_PCB_v3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=160,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,LoopCore=1,EventsCore=1,DebugLevel=none




CC=arduino-cli



CFLAGS_PCB1_PROD =--build-property  "build.extra_flags=-DPROD_BUILD \"-DPCB_V_0_1_0 \""
CFLAGS_PCB2_PROD =--build-property  "build.extra_flags=-DPROD_BUILD \"-DPCB_V_0_2_0 \""
CFLAGS_PCB3_PROD =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010 -DSOFTWARE_I2C -DSTAND_ALONE"
CFLAGS_PCB32_PROD =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010 -DFRAM_V010 -DSTAND_ALONE -DSUBCRIPTION_ON"
CFLAGS_PCB32_PROD_NEW_PIN =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010 -DFRAM_V010 -DSTAND_ALONE -DSUBCRIPTION_ON -DGSM_NEW_PIN"
CFLAGS_PCB32_PROD_GSM =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010 -DFRAM_V010 -DSTAND_ALONE -DGSM_V010 -DSUBCRIPTION_ON -DGSM_NEW_PIN"
CFLAGS_PCB32 =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010"


 
build_prod_v32: #for wifi old pin
	$(CC) compile -b $(FQBN_PCB_v3)  $(CFLAGS_PCB32_PROD) --warnings all
build_prod_v32_ota:
	$(CC) compile -b $(FQBN_PCB_v3)  $(CFLAGS_PCB32_PROD) --warnings all --output-dir ./bin/
build_prod_v32_gsm: #To build for gsm with new pinout
	$(CC) compile -b $(FQBN_PCB_v3)  $(CFLAGS_PCB32_PROD_GSM) --warnings all 
build_prod_v32_new_pin: #To build for wifi with new pinout
	$(CC) compile -b $(FQBN_PCB_v3)  $(CFLAGS_PCB32_PROD_NEW_PIN) --warnings all
build: 
	$(CC) compile -b $(FQBN_PCB_v3)  $(CFLAGS_PCB32) --warnings all


up:
	$(CC) upload -b $(FQBN_PCB_v3)   -p $(SERIAL_PORT_v3)  -v -t 
uplo:
	$(CC) upload -b $(FQBN_PCB_v3)   -p $(SERIAL_PORT_v3)  -v -t --input-dir ./output/$(CODEVERSION)/$(DEVICE) 



.PHONY: download delete_lib
