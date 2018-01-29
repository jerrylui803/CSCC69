#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
MODULE_DESCRIPTION("My kernel module");
MODULE_AUTHOR("John Doe");
MODULE_LICENSE("GPL");
static int mymodule_init(void) {
	printk( KERN_ALERT "Hello world!\n" );
	return 0;
}
static void mymodule_exit(void) {
	printk( KERN_ALERT "I'm outta here\n" );
}
module_init(mymodule_init);
module_exit(mymodule_exit);