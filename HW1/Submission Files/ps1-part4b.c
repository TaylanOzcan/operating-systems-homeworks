#include <linux/resource.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

struct fileinfo304 {
	size_t size;
	char filename[100];
        char datecreated[100];
	int owner_id;
        int file_id; 
	struct list_head list;
};

static LIST_HEAD(files_list);

static int pid = -1;

module_param(pid, int, 0);
MODULE_PARM_DESC(pid, "Pid to find a process");

int fileinfo304_init(void){
	struct task_struct *task;

	for_each_process(task){
		if(task->pid == pid){
			printk(KERN_INFO "PID = %d\n", pid);
			printk(KERN_INFO "Name = %s\n", task->comm);
			printk(KERN_INFO "Parent: PID = %d, Name = %s\n", (int)task->parent->pid, task->parent->comm);

			struct list_head *list;
			int counter = 1;

			list_for_each(list, &task->children){
				struct task_struct *child_task;
				child_task = list_entry(list, struct task_struct, sibling);
				printk(KERN_INFO "%d. Child: PID = %d, Name = %s\n", counter, (int)child_task->pid, child_task->comm);
				counter++;
			}

			if(counter==1){
				printk(KERN_INFO "No Children Found\n");
			}

			return 0;
		}
	}

	printk(KERN_INFO "PID not found");
	return 0;
}

void fileinfo304_exit(void) {
	printk(KERN_INFO "Removing Module\n");

}

module_init(fileinfo304_init);
module_exit(fileinfo304_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Exercise for COMP304");
MODULE_AUTHOR("Ozgur Ozcan");
