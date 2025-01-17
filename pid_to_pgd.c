#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/pgtable.h>

#define BUFSIZE  100

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Francesco Ciraolo");

unsigned long pgd_addr;

static struct proc_dir_entry *ent;

static ssize_t pidread(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) {

    char buf[BUFSIZE];

    long unsigned int p_id;
    struct pid *pid_struct;
    struct task_struct *task;

    if (*ppos > 0 || count >= BUFSIZE)
        return -EFAULT;

    if (copy_from_user(buf, ubuf, count))
        return -EFAULT;

    buf[count] = 0;

    if (kstrtoul(buf, 0, &p_id))
        return -EFAULT;

    pid_struct = find_get_pid(p_id);
    task = pid_task(pid_struct, PIDTYPE_PID);

    if (p_id != task->pid) {
        printk("Can't retrieve process with pid: %lu\n", p_id);
        return -ESRCH;
    }

    pgd_addr = virt_to_phys(task->mm->pgd);

    *ppos = strlen(buf);

    return *ppos;
}

static ssize_t pgdwrite(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) {
    int len;

    char buf[BUFSIZE];

    if(*ppos > 0 || count < BUFSIZE)
        return 0;

    len = sprintf(buf,"%lx\n", pgd_addr);

    if(copy_to_user(ubuf,buf,len))
        return -EFAULT;

    *ppos = len;

    return len;
}


static int init(void) {

    static struct proc_ops ops = {
            .proc_read = pgdwrite,
            .proc_write = pidread
    };

    ent=proc_create("pid_to_pgd", 0660, NULL, &ops);
    return 0;
}

static void cleanup(void) {
    proc_remove(ent);
}

module_init(init);
module_exit(cleanup);
