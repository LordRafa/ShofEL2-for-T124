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

int send_rcm_cmd( int rcm_usb, char* payload_filename, uint32_t payload_thumb_mode );

#endif
