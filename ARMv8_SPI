#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define NUM_DEVICES 5
#define SPI_BUS "/dev/spidev0.0"
#define SPI_MODE SPI_MODE_0
#define SPI_BITS_PER_WORD 8
#define SPI_SPEED_HZ 1000000

int main(void) {
    int spi_fd;
    uint8_t tx_buf[NUM_DEVICES], rx_buf[NUM_DEVICES];
    struct spi_ioc_transfer spi_transfers[NUM_DEVICES];

    // Open SPI device
    spi_fd = open(SPI_BUS, O_RDWR);
    if (spi_fd < 0) {
        perror("Failed to open SPI device");
        exit(EXIT_FAILURE);
    }

    // Set SPI mode
    int spi_mode = SPI_MODE;
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode) < 0) {
        perror("Failed to set SPI mode");
        exit(EXIT_FAILURE);
    }

    // Set SPI bits per word
    int spi_bits_per_word = SPI_BITS_PER_WORD;
    if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits_per_word) < 0) {
        perror("Failed to set SPI bits per word");
        exit(EXIT_FAILURE);
    }

    // Set SPI speed
    int spi_speed_hz = SPI_SPEED_HZ;
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed_hz) < 0) {
        perror("Failed to set SPI speed");
        exit(EXIT_FAILURE);
    }

    // Initialize SPI transfer structures
    for (int i = 0; i < NUM_DEVICES; i++) {
        tx_buf[i] = i + 1;      //Use tx_buf to send data to slave
        memset(&spi_transfers[i], 0, sizeof(spi_transfers[i]));
        spi_transfers[i].tx_buf = (unsigned long)&tx_buf[i];
        spi_transfers[i].rx_buf = (unsigned long)&rx_buf[i];
        spi_transfers[i].len = sizeof(tx_buf[i]);
        spi_transfers[i].speed_hz = spi_speed_hz;
        spi_transfers[i].bits_per_word = spi_bits_per_word;
        spi_transfers[i].delay_usecs = 0;
    }

    // Perform SPI transfers
    if (ioctl(spi_fd, SPI_IOC_MESSAGE(NUM_DEVICES), spi_transfers) < 0) {
        perror("Failed to perform SPI transfers");
        exit(EXIT_FAILURE);
    }

    // Print received data
    for (int i = 0; i < NUM_DEVICES; i++) {
        printf("Device %d: Received data: 0x%02X\n", i+1, rx_buf[i]);
    }

    // Close SPI device
    close(spi_fd);

    return 0;
}
