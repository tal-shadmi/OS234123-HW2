#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/errno.h>

asmlinkage long sys_hello(void) {
	printk("Hello, World!\n");
	return 0;
}

asmlinkage int sys_set_weight(int weight){
    if (weight < 0){
        return -EINVAL;
    }
    current->weight = weight;
    return 0;
}

asmlinkage int sys_get_weight(void){
    return current->weight;
}

asmlinkage int sys_get_children_sum(void){
    return 0;
}

asmlinkage pid_t sys_get_heaviest_ancestor(void){
    return 0;
}
