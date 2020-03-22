#ifndef _MINI_LIBUSB_H_
#define _MINI_LIBUSB_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <ctype.h>

#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>

#define USB_CTRL_DEVICE_ENDPOINT_TO_HOST 0x82
#define USB_CTRL_GET_STATUS 0x00

#define USB_BULK_TIMEOUT 500

#if DEBUG
    #define DEBUG_MSG(fmt, ...) do { fprintf( stderr, "%s:%d:%s(): " fmt, \
                                __FILE__, __LINE__, __func__, ##__VA_ARGS__ ); } while(0)
#else
    #define DEBUG_MSG(fmt, ...) 
#endif

int usb_open_by_vid_pid( uint16_t vid, uint16_t pid, uint8_t wait );
int usb_close( int usb );
int usb_send_bulk_txn( int usb, uint32_t ep, uint32_t len, void *data );
int usb_send_control_txn( int usb, uint8_t bRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint16_t len, uint8_t *data );

#endif

