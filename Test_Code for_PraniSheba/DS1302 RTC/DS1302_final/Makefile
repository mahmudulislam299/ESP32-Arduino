SERIAL_PORT=COM14


FQBN_PCB_V1=arduino:avr:uno
FQBN_PCB_v2=arduino:avr:pro:cpu=8MHzatmega328
#FQBN_PCB_v3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,DebugLevel=none
FQBN_PCB_v3=esp32:esp32:esp32:PSRAM=disabled,PartitionScheme=default,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,DebugLevel=none


# PCB_FLAG_v1 = build.extra_flags=-DPCB_V_0_1_0
# PCB_FLAG_v2 = build.extra_flags=-DPCB_V_0_2_0

CC=arduino-cli
CFLAG_PCB1_DEV = --build-property  "build.extra_flags=-DDEV \"-DPCB_V_0_1_0 \""
CFLAG_PCB2_DEV = --build-property  "build.extra_flags=-DDEV \"-DPCB_V_0_2_0 \""


CFLAGS_PCB1_PROD =--build-property  "build.extra_flags=-DPROD_BUILD \"-DPCB_V_0_1_0 \""
CFLAGS_PCB2_PROD =--build-property  "build.extra_flags=-DPROD_BUILD \"-DPCB_V_0_2_0 \""
CFLAGS_PCB3_PROD =--build-property build.extra_flags="-DPROD_BUILD -DESP32_V010 -DESP32_V010"

build_v1:
	$(CC) compile -b $(FQBN_PCB_V1) $(CFLAG_PCB1_DEV) 
build_v2: 
	$(CC) compile -b $(FQBN_PCB_v2) $(CFLAG_PCB2_DEV) 

build_prod_v1: download
	$(CC) compile -b $(FQBN_PCB_V1)  $(CFLAGS_PCB1_PROD)
build_prod_v2: download
	$(CC) compile -b $(FQBN_PCB_v2)  $(CFLAGS_PCB2_PROD)
build_prod_v3: 
	$(CC) compile -b $(FQBN_PCB_v3)  $(CFLAGS_PCB3_PROD) -v -t

upload_v1:
	$(CC) upload -b $(FQBN_PCB_V1)   -p $(SERIAL_PORT)  -v -t
upload_v2:
	$(CC) upload -b $(FQBN_PCB_v2)   -p $(SERIAL_PORT)  -v -t
upload_v3:
	$(CC) upload -b $(FQBN_PCB_v3)   -p $(SERIAL_PORT)  -v -t


delete_lib:
	rm -rf ./src/lib
download:
	powershell  .\download.ps1

.PHONY: download delete_lib

# deploy_v1: 
# 	$(CC) compile -b $(FQBN_PCB_V1)  $(CFLAG_PCB1_DEV) -p $(SERIAL_PORT) -u -v -e -t 
# deploy_v2:
# 	$(CC) compile -b $(FQBN_PCB_v2)  $(CFLAG_PCB2_DEV) -p $(SERIAL_PORT)   -u -v -e -t 