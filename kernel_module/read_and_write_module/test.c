#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/rwlock.h>

#define SIZE 15

static int major = 0;
static rwlock_t lock;
static char string[SIZE] = "Hello\0";

ssize_t test_read(struct file *fd, char __user *buff, size_t size, loff_t *off){
    size_t rc;

    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, string, SIZE);
    read_unlock(&lock);

    return rc;
}

ssize_t test_write(struct file *fd, const char __user *buff, size_t size, loff_t *off){
    size_t rc = 0;

    if(size > SIZE){
        return -EINVAL;
    }

    write_lock(&lock);
    rc = simple_write_to_buffer(string, SIZE, off, buff, size);
    write_unlock(&lock);

    return rc;
}

static struct file_operations fops {
    .owner = THIS_MODULE,
    .read = test_read,
    .write = test_write
};

int init_module(void){
    pr_info("Read and write module is loaded!\n");
    rwlock_init(&lock);
    major = register_chrdev(major, "test", &fops);

    if(major < 0){
        return major;
    }
    pr_info("Major = %d\n", major);

    return 0;
}

void cleanup_module(void){
    unregister_chrdev(major, "test");
    pr_info("Read and write module is unloaded!\n");
}

MODULE_LICENSE("GPLv2");
MODULE_DESCRIPTION("desc");
