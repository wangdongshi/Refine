// A test program to access /dev/second
// This example is to help understand kernel timer 
    
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

main()
{
  int fd;
  int counter = 0;
  int old_counter = 0;
  
  /* open /dev/second device file */
  fd = open("/dev/second", O_RDONLY);
  if (fd !=  - 1)
  {
    while (1)
    {
      read(fd,&counter, sizeof(unsigned int)); /* read current seconds */
      if(counter!=old_counter)
      {	
      	printf("seconds after open /dev/second :%d\n",counter);
      	old_counter = counter;
      }	
    }    
  }
  else
  {
    printf("Device open failure\n");
  }
}
