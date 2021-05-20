#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/errno.h>

asmlinkage long sys_hello(void) {
	printk("Hello, World!\n");
	return 0;
}

asmlinkage long sys_set_weight(int weight){
    if (weight < 0){
        return -EINVAL;
    }
    current->weight = weight;
    return 0;
}

asmlinkage long sys_get_weight(void){
    return current->weight;
}

long get_children_sum_aux(struct task_struct* c){
    long total_weight;
    struct list_head* child;
    struct task_struct* task;
    if(list_empty(&(c->children))){
        return  c->weight;
    }
    total_weight+= c->weight;
    list_for_each(child , &(c->children)){
        task = list_entry(child,struct task_struct,sibling);
        total_weight+= get_children_sum_aux(task);
    }
    return total_weight;
}

asmlinkage long sys_get_children_sum(void){
    if(list_empty(&(current->children))){
        return  -ECHILD;
    }
    long save_weight = current->weight;
    current->weight = 0;
    long sum = get_children_sum_aux(current);
    current->weight = save_weight;
    return sum;
}

asmlinkage pid_t sys_get_heaviest_ancestor(void){
    long max_weight = current->weight;
    pid_t pid = current->pid;
    struct task_struct* task = current;
    while(task->pid>0){
        if(task->real_parent->weight>max_weight){
            max_weight = task->real_parent->weight;
            pid = task->real_parent->pid;
        }
        task = task->real_parent;
    }
    return pid;
}
