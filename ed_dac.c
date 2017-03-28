// Add -lrt flag to the compile command if any bcm2835_delay... function is used!

#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

uint8_t sineBuf[1024];
void initSineBuf(){
	uint16_t i;
	
	for(i = 0; i < 1024; i++){
		sineBuf[i] = (sin( ((double)i/1024) *(2*3.141592) ) + 1) * 2048;
	}
}

int main(int argc, char **argv){

	initSineBuf();
	uint16_t i;
	for(i = 0; i < 1024; i++){
		printf("%d\t", sineBuf[i]);
		if(i % 10 == 0){
			printf("\n");
		}
	}
	for(;;);

	// Initialize the SPI and start a SPI session:
	if (!bcm2835_init()){
		printf("bcm2835_init failed. Are you running as root??\n");
		return 1;
	}
	if (!bcm2835_spi_begin()){
		printf("bcm2835_spi_begin failedg. Are you running as root??\n");
		return 1;
	}

	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(100); //Clock freq: 250MHz/divider.
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

	uint16_t bufIndex = 0;
	while(1){
		bcm2835_spi_writenb(&sineBuf[bufIndex += 2], 2);

	}


	uint32_t len = 2;
	char tbuf[len];

	while(1){
	 	tbuf[0] = 0x0F;
	 	tbuf[1] = 0xFF;
		bcm2835_spi_writenb(&tbuf[0], len);
		tbuf[0] = 0x05;
	 	tbuf[1] = 0x55;
		bcm2835_spi_writenb(&tbuf[0], len);
		tbuf[0] = 0x00;
	 	tbuf[1] = 0x00;
		bcm2835_spi_writenb(&tbuf[0], len);
		bcm2835_delayMicroseconds(90);
	}


}	
