# Plaid Kernel

The Project Plaid kernel, in C, using newlib as a libc.

## Platforms

Targets in development now:

* armv7-a
  * ARM realview-pbx-a9 (via qemu)

Planned targets:

* armv8
  * PINE64
  * Raspberry Pi 3

## Compiling

You need an arm-eabi-* compiler. I use the Linaro gcc-linaro-6.2.1-2016.11-x86_64_arm-eabi compiler, and CMake.

```bash
make
```

## Running in qemu

```bash
qemu-system-arm -M realview-pbx-a9 -cpu cortex-a9 -m 1024M -S -s -kernel kernel/plaid.kernel $*
```

## Debugging

When you run it like above, it will halt waiting on a debugger.

```bash
cd build
arm-eabi-gdb kernel/plaid.kernel
target remote localhost:1234
```

## License

Apache Public License 2.0
