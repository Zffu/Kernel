# Kernel

This repository contains my second attempt at making a Kernel.

## Goals for the project
My goals for the project are to build a kernel that is:
- Fast
- Compatible with most hardware
- Customizable
- Non-Telemetric
- Easy to use (in terms of commands, and other)
- Easy to understand
- Low on RAM usage
- Good for both servers and computers

## Structure
Here's the structure for the kernel:
- ``kernel``: Contains the core kernel code, this code is the actual kernel and isn't accessible by anything else
- ``bios``: The BIOS version of the bootloader
- ``drivers``: The kernel drivers, these drivers are mostly the internal/important ones
- ``cpu``: Contains the CPU ISR, IDT and interruption handling
- ``cstdlib``: The shared public C headers and implementations for the kernel related applications, these can be accessed and used by anything.s