#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/ioctl.h> 
#include <linux/types.h>
#include <fcntl.h> 
#include <string.h>
#include <xenctrl.h>
#include <xen/sys/privcmd.h>
 
int main(int argc, char *argv[]) 
{ 
        int fd, ret, i;
	__guest_handle_xen_pfn_t addr;
	struct xen_memory_reservation in = {
		1,
		(xen_ulong_t)1,
		(unsigned int)0,
		(domid_t)0
	};
	struct xen_memory_reservation out = {
		18446603885977010000,
		(xen_ulong_t)16,
		(unsigned int)1,
		(domid_t)0
	};
	struct xen_memory_exchange my_exchange = {
		in,
		out,
		(xen_ulong_t)1
	};

        	privcmd_hypercall_t my_hypercall = { 
			__HYPERVISOR_memory_op, //超级调用号   12
		(__u64){IOCTL_PRIVCMD_HYPERCALL, &my_exchange, 0, 0, 0}   //超级调用参数  操作码11
	    	};
	   	
        	fd = open("/proc/xen/privcmd", O_RDWR);
        	if (fd < 0) {
                 	perror("can't open /proc/xen/privcmd");
                 	exit(1);
        	}
        	else
                 	printf("privcmd's fd = %d\n", fd);
        	ret = ioctl(fd, IOCTL_PRIVCMD_HYPERCALL, &my_hypercall);
	   	//ret = ioctl(fd, IOCTL_PRIVCMD_HYPERCALL, (__u64)1234);
        	printf("ret = %d\n", ret); 
	
}
