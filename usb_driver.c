/***************************************************************************//**
*  \file       usb_driver.c
*
*  \details    USB driver for Aquaris X Android phone
*
*  \author     Telmo Egues
*
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>

#define USB_ID_VENDOR	( 0x2a47 ) /*Macro for the ID of the vendor*/
#define USB_ID_PRODUCT	( 0xf003 ) /*Mcro for the ID of the product*/

static int pr_probe (struct usb_interface *interface, const struct usb_device_id *id) {
	struct usb_host_interface *iface_desc = interface->cur_altsetting; //iface_desc is defined as a usb_host_interface structure which contains all the interface descriptors
	printk(KERN_INFO "Device name: %s\n", iface_desc->desc.iProduct);
	dev_info(&interface->dev, "USB detected with Vendor ID: 0x%02x an Product ID: 0x%02x/n", id->idVendor, id->idProduct);
	return 0;
}

static void pr_disconnect(struct usb_interface *interface){
	dev_info(&interface->dev, "USB has been unplugged");
}

/* Lists different types of USB devices that are supported, in this case added in macros */
static struct usb_device_id pr_usb_table [] = {
        { USB_DEVICE( USB_ID_VENDOR, USB_ID_PRODUCT) },
        { }                      /* Terminating entry */
};

MODULE_DEVICE_TABLE (usb, pr_usb_table);

static struct usb_driver pr_driver = { /* This structure defines which devices the driver supports and which functions to call when a device supported is plugged in*/
        .name        = "Open-Cosmos project",
        .probe       = pr_probe,
        .disconnect  = pr_disconnect,
        .id_table    = pr_usb_table,
};


static int __init usb_pr_init(void) /* Usbs must be registered once plugged in*/
{
        int result;

        /* register this driver with the USB subsystem */
        result = usb_register(&pr_driver);
	if (result < 0) {
		printk(KERN_INFO "There has been an error");
                return -1;
        }

        return 0;
}

static void __exit usb_pr_exit(void) /* Usbs are unregistered once the device is being unplugged*/
{
        usb_deregister(&pr_driver);
}

module_init(usb_pr_init);
module_exit(usb_pr_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("tegues");
MODULE_DESCRIPTION("OC project");
