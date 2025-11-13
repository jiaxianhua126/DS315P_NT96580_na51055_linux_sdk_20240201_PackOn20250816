DTS_SENSOR = ./SrcCode/Dx/$(MODEL)/sensor.dts
DTS_APP = ./SrcCode/Dx/$(MODEL)/application.dts
DX_SRC = \
	./SrcCode/Dx/$(MODEL)/DxInput_Key.c \
	./SrcCode/Dx/$(MODEL)/IOCfg.c \
	./SrcCode/Dx/$(MODEL)/DxUsb.c \
	./SrcCode/Dx/$(MODEL)/DxCfg.c \
	./SrcCode/Dx/$(MODEL)/DxDisplay_LCD.c \
	./SrcCode/Dx/$(MODEL)/DxPower_Battery.c \
	./SrcCode/Dx/$(MODEL)/DxPower_DC.c \
	./SrcCode/Dx/$(MODEL)/DxStorage_Card.c \
	./SrcCode/Dx/$(MODEL)/DxStorage_EmbMem.c \
	./SrcCode/Dx/$(MODEL)/uart.c \
	./SrcCode/Dx/$(MODEL)/DxGSensor.c \
	./SrcCode/Dx/$(MODEL)/DxGPS.c \
	./SrcCode/Dx/$(MODEL)/DxLed.c \
	./SrcCode/Dx/$(MODEL)/DxGpio.c \
	./SrcCode/Dx/$(MODEL)/Dxwatchdog.c \
	./SrcCode/Dx/$(MODEL)/DxASR.c		\
	./SrcCode/Dx/$(MODEL)/DxEdog.c		\
	./SrcCode/Dx/$(MODEL)/DxEdog_Sound.c		\
#	./SrcCode/Dx/$(MODEL)/ProjectInfo.c \
#	./SrcCode/Dx/$(MODEL)/DxCamera_Sensor.c \
#	./SrcCode/Dx/$(MODEL)/DxCfg.c
#	./SrcCode/Dx/$(MODEL)/DxCmd.c
#	./SrcCode/Dx/$(MODEL)/DxDisplay_LCD.c
#	./SrcCode/Dx/$(MODEL)/DxOutput_LED.c
#	./SrcCode/Dx/$(MODEL)/DxPower_Battery.c
#	./SrcCode/Dx/$(MODEL)/DxSound_Audio.c
#	./SrcCode/Dx/$(MODEL)/DxStorage_Card.c
#	./SrcCode/Dx/$(MODEL)/DxStorage_EmbMem.c
#	./SrcCode/Dx/$(MODEL)/DxWiFi.c
#	./SrcCode/Dx/$(MODEL)/DxCmd.c


