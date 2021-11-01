#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define mem_size 8

int8_t testBuffer[mem_size];

int main()
{
	int fd;
	
	printf("Starting User Space Application\n");
	
	for (int i = 0; i < mem_size; i++)
	{
		testBuffer[i]=(rand()%100)+1;
	}
	
	printf("Size of buffer: %d\n", mem_size);
	printf("Initializing buffer with random values between 1 and 100\n\n");
	
	for (int i = 0; i < mem_size; i++)
	{
		printf("Contents of buffer: index %d = %d\n", i, testBuffer[i]);
	}
	
	
	fd = open("/dev/chr_device", O_RDWR);
	if(fd < 0){
		printf("Could not open device file\n");
		return 0;
	}
	printf("Successfully opened the device file\n");
	write(fd, testBuffer, mem_size);
	printf("Successfully wrote buffer data to kernel space\n");
	
	return 0;
}
