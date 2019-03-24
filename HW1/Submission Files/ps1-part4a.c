#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include<linux/slab.h>

struct fileinfo304 {
	size_t size;
	char filename[100];
        char datecreated[100];
	int owner_id;
        int file_id; 
	struct list_head list;
};

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

/**
 * The following defines and initializes a list_head object named files_list
 */

static LIST_HEAD(files_list);

static LIST_HEAD(birthday_list);


int fileinfo304_init(void)
{
       printk(KERN_INFO "Loading Module\n");

	struct birthday *ali;
	ali = kmalloc(sizeof(*ali), GFP_KERNEL);
	ali->day = 5;
	ali->month= 8;
	ali->year = 1985;
	INIT_LIST_HEAD(&ali->list);
	list_add_tail(&ali->list, &birthday_list);

	struct birthday *ayse;
	ayse = kmalloc(sizeof(*ayse), GFP_KERNEL);
	ayse->day = 2;
	ayse->month= 4;
	ayse->year = 1994;
	INIT_LIST_HEAD(&ayse->list);
	list_add_tail(&ayse->list, &birthday_list);

	struct birthday *ahmet;
	ahmet = kmalloc(sizeof(*ahmet), GFP_KERNEL);
	ahmet->day = 12;
	ahmet->month= 7;
	ahmet->year = 1995;
	INIT_LIST_HEAD(&ahmet->list);
	list_add_tail(&ahmet->list, &birthday_list);

	struct birthday *veli;
	veli = kmalloc(sizeof(*veli), GFP_KERNEL);
	veli->day = 17;
	veli->month= 3;
	veli->year = 1994;
	INIT_LIST_HEAD(&veli->list);
	list_add_tail(&veli->list, &birthday_list);

	struct birthday *fatma;
	fatma = kmalloc(sizeof(*fatma), GFP_KERNEL);
	fatma->day = 23;
	fatma->month= 1;
	fatma->year = 1971;
	INIT_LIST_HEAD(&fatma->list);
	list_add_tail(&fatma->list, &birthday_list);

	struct birthday *ptr;

	list_for_each_entry(ptr, &birthday_list, list){
		printk(KERN_INFO "%d %d %d\n", ptr->day, ptr->month, ptr->year);
	}

	return 0;
}

void fileinfo304_exit(void) {

	printk(KERN_INFO "Removing Module\n");
	
	struct birthday *ptr, *next;

	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		list_del(&ptr->list);
		kfree(ptr);
	}
}

module_init( fileinfo304_init);
module_exit( fileinfo304_exit);

MODULE_LICENSE( "GPL");
MODULE_DESCRIPTION( "Exercise for COMP304");
MODULE_AUTHOR("Ozgur Ozcan");
