#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char **argv){

  system("/sbin/insmod ./inject.ko");
 // system("/sbin/rmmod hInjLKM.ko");

  return 0;
  }

  
