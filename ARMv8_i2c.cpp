#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define NUM_DEVICES 5
#define I2C_BUS "/dev/i2c-1"  // I2C bus device file
#define I2C_ADDRESS_BASE 0x20  // Base I2C address of Atmega328p devices
#define I2C_DATA_LENGTH 16  // Maximum length of data to read/write

// Function to open I2C bus
int i2c_open(char *filename) {
    int file;
    if ((file = open(filename, O_RDWR)) < 0) {
        perror("Failed to open I2C bus");
        exit(1);
    }
    return file;
}

// Function to set I2C slave address
int i2c_set_slave(int file, int address) {
    if (ioctl(file, I2C_SLAVE, address) < 0) {
        perror("Failed to set I2C slave address");
        exit(1);
    }
    return 0;
}

// Function to write data to I2C slave
int i2c_write(int file, char *data, int length) {
    if (write(file, data, length) != length) {
        perror("Failed to write to I2C slave");
        exit(1);
    }
    return 0;
}

// Function to read data from I2C slave
int i2c_read(int file, char *data, int length) {
    if (read(file, data, length) != length) {
        perror("Failed to read from I2C slave");
        exit(1);
    }
    return 0;
}

int main() {
    int i, file;
    char i2c_filename[] = I2C_BUS;
    char i2c_data[I2C_DATA_LENGTH];
    int i2c_address;
    
    // Open I2C bus
    file = i2c_open(i2c_filename);

    // Send data to each device
    for (i = 0; i < NUM_DEVICES; i++) {
        i2c_address = I2C_ADDRESS_BASE + i;

        // Set I2C slave address
        i2c_set_slave(file, i2c_address);

        // Write data to I2C slave
        i2c_data[0] = i;  // Data to send
        i2c_write(file, i2c_data, 1);

        // Read data from I2C slave
        i2c_read(file, i2c_data, 1);
        printf("Data received from device %d: %d\n", i, i2c_data[0]);
    }

    // Close I2C bus
    close(file);

    return 0;
}
