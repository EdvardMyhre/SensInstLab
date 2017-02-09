// Add -lrt flag to the compile command if any bcm2835_delay... function is used!

#include <bcm2835.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){
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
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);
	bcm2835_spi_setClockDivider(8192); //Clock freq: 250MHz/divider.
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

	uint16_t len = 65000;
	uint8_t tbuf[len];
	uint8_t rbuf[len];
  
 	uint16_t i = 0;

	for (i = 0; i < len/2; i++) {
		tbuf[i] = 0x11111110;
	}
	for (i = len/2; i < len; i++) {
		tbuf[i] = 0x00000000;
	}

	while (1){
		bcm2835_spi_writenb(&tbuf, &rbuf, len);
		//bcm2835_delayMicroseconds(100);
	}
}	
