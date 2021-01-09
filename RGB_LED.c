/*
	RGB_LED.c
	Device driver that lights in a specific color using RGB LED.
	
	Copyright (C) 2020  Masato Kubotera

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

//LED数
#define LED_Num 3

//GPIOピン設定
#define Red_LED_Pin 23 
#define Green_LED_Pin 24
#define Blue_LED_Pin 25

//点灯時間[ms]
#define LED_Time 3000 

MODULE_AUTHOR("Masato Kubotera and Ryuichi Ueda");
MODULE_DESCRIPTION("driver for RGB LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static unsigned int LED_Pins[LED_Num] = { Red_LED_Pin, Green_LED_Pin, Blue_LED_Pin};

void RGB_write(int r, int g, int b){
	if(r == 1)
		gpio_base[7] = 1 << Red_LED_Pin;

	if(g == 1)
		gpio_base[7] = 1 << Green_LED_Pin;

	if(b == 1)
		gpio_base[7] = 1 << Blue_LED_Pin;

	msleep(LED_Time);
}

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char character;
	int i;

	if(copy_from_user(&character, buf, sizeof(char)))
		return -EFAULT;
	
	if(character == 'r' || character == 'R')
		RGB_write( 1, 0, 0); //赤
	
	else if(character == 'g' || character == 'G')
		RGB_write( 0, 1, 0); //緑
	
	else if(character == 'b' || character == 'B')
		RGB_write( 0, 0, 1); //青
	
	else if(character == 'y' || character == 'Y')
		RGB_write( 1, 1, 0); //黄
	
	else if(character == 'c' || character == 'C')
		RGB_write( 0, 1, 1); //シアン
	
	else if(character == 'm' || character == 'M')
		RGB_write( 1, 0, 1); //マゼンタ

	else if(character == 'w' || character == 'W')
		RGB_write( 1, 1, 1); //白

	else{	
		//全LEDを消灯
		for(i = 0; i < LED_Num; i++)
			gpio_base[10] = 1 << LED_Pins[i];
	}

	return 1;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
};


static int __init init_mod(void)
{
	int retval,i;
	retval = alloc_chrdev_region(&dev, 0, 1, "RGB_LED");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}

	printk(KERN_INFO "%s is loaded. major:%d\n", __FILE__, MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
        if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d", MAJOR(dev), MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "RGB_LED");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	
	device_create(cls, NULL, dev, NULL, "RGB_LED%d", MINOR(dev));
	
	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

        for(i = 0; i < LED_Num; i++){
        	const u32 index = LED_Pins[i] / 10;
        	const u32 shift = (LED_Pins[i] % 10) * 3;
        	const u32 mask = ~(0x7 << shift);
	        gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
        }	

	return(0);
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n", __FILE__, MAJOR(dev));
}

module_init(init_mod);

module_exit(cleanup_mod);
