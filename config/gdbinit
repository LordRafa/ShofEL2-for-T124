# J-LINK GDB SERVER initialization
#
# This connects to a GDB Server listening
# for commands on localhost at tcp port 2331
target remote localhost:2331
# Set JTAG speed to 30 kHz
monitor speed 4
# Set GDBServer to little endian
monitor endian little
# Reset the chip to get to a known state.
monitor reset
#
# CPU core initialization (to be done by user)
#
# Set the processor mode (Enables THUMB)
monitor reg cpsr = 0xf3
# Set auto JTAG speed
monitor speed auto
# Setup GDB FOR FASTER DOWNLOADS
set remote memory-write-packet-size 1024
set remote memory-write-packet-size fixed
# Load the program executable called "reset_example.elf"
load reset_example.elf 
