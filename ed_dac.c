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
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); //Clock freq: 250MHz/divider.
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, LOW);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);

	uint32_t len = 2;
	char tbuf[len];
  
 	uint16_t i = 0;

<<<<<<< HEAD
 	tbuf[0] = 0x0F
 	tbuf[1] = 0xFF
	bcm2835_spi_writenb(&tbuf[0], len);
	bcm2835_delayMilliseconds(500);
	tbuf[0] = 0x05
 	tbuf[1] = 0x55
	bcm2835_spi_writenb(&tbuf[0], len);
	bcm2835_delayMilliseconds(500);
	tbuf[0] = 0x00
 	tbuf[1] = 0x00
	bcm2835_spi_writenb(&tbuf[0], len);
	bcm2835_delayMilliseconds(500);
 	tbuf[0] = 0x0F
 	tbuf[1] = 0xFF
	bcm2835_spi_writenb(&tbuf[0], len);
	bcm2835_delayMilliseconds(500);
	tbuf[0] = 0x05
 	tbuf[1] = 0x55
	bcm2835_spi_writenb(&tbuf[0], len);
	bcm2835_delayMilliseconds(500);
	tbuf[0] = 0x00
 	tbuf[1] = 0x00
	bcm2835_spi_writenb(&tbuf[0], len);
	bcm2835_delayMilliseconds(500);
=======
	for (i = 0; i < len/3; i++) {
		tbuf[i] = 0xFF;
	}

	for (i = len/3; i < 2*len/3; i++){
		tbuf[i] = 0x55;
	}

	for (i = 2*len/3; i < len; i++) {
		tbuf[i] = 0x00;
	}

	while (1){
		bcm2835_spi_writenb(&tbuf[0], len-2);
		bcm2835_delayMicroseconds(10);
	}

	bcm2835_spi_end();
        bcm2835_close();
        return 0;
>>>>>>> 345adc2a094c99a0402a3554b3fabed8f7958563
}	
