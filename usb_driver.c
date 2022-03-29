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


static struct usb_driver pr_driver = { /* This structure defines which devices the driver supports and which functions to call when a device supported by the driver is inserted or removed */
        .name        = "Open-Cosmos project",
        .probe       = pr_probe, /* Probes if the device is connected or disconnected*/ 
	.disconnect  = pr_disconnect,
        .id_table    = pr_usb_table,
};

/* Lists different types of USB devices that are supported */
static struct usb_device_id pr_usb_table [] = {
        { USB_DEVICE( USB_ID_VENDOR, USB_ID_PRODUCT) },
        { }                      /* Terminating entry */
};

static int pr_probe () {
	
}

static void pr_disconnect(){
	
}

MODULE_DEVICE_TABLE (usb, pr_usb_table);

static int __init usb_pr_init(void) /* Usbs must be registered once plugged in*/
{
        int result;

        /* register this driver with the USB subsystem */
        result = usb_register(&pr_driver);
        if (result < 0) {
                err("usb_register failed for the "__FILE__ "driver."
                    "Error number %d", result);
                return -1;
        }

        return 0;
}

static void __exit usb_pr_exit(void) /* Usbs are unregistered once the device is being unplugged*/
{
        /* deregister this driver with the USB subsystem */
        usb_deregister(&pr_driver);
}
module_init(usb_pr_init);
module_exit(usb_pr_exit);
