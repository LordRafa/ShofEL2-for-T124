#ifndef _RCM_H_
#define _RCM_H_

#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "t124.h"
#include "mini_libusb.h"
#include "endianness.h"

int send_rcm_cmd( int rcm_usb, uint32_t usb_transport_add );

#endif
