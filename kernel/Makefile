HOSTARCH?=armv7
BOARD?=realview-pbx-a9
CC:=arm-eabi-gcc
CXX:=arm-eabi-g++

CFLAGS?=-O0 -ggdb
CPPFLAGS?=
CXXFLAGS?=-fno-exceptions -fno-rtti
LDFLAGS?=
LIBS?=
 
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
 
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
CXXFLAGS:=$(CXXFLAGS)
LDFLAGS:=$(LDFLAGS) -nostdlib -Wl,--gc-sections -ggdb -static-libgcc -static-libstdc++
LIBS:=$(LIBS) -lstdc++ -lc -lnosys -lgcc 
 
ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
CXXFLAGS:=$(CXXFLAGS) $(KERNEL_ARCH_CXXFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(KERNEL_ARCH_LIBS) $(LIBS)
 
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel.o \
 
OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \
 
LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \
$(LIBS) \
 
.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .cpp .S .ld
 
all: plaid.kernel
 
plaid.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
#	grub-file --is-x86-multiboot plaid.kernel
 
$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.cpp.o:
	$(CXX) -MD -c $< -o $@ -std=gnu++14 $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS)
 
.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)
 
.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
 
clean:
	rm -f plaid.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d
 
install: install-headers install-kernel
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
 
install-kernel: plaid.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp plaid.kernel $(DESTDIR)$(BOOTDIR)

qemu: plaid.kernel
	qemu-system-arm -M realview-pbx-a9 -cpu cortex-a9 -m 256 -kernel plaid.kernel
 
-include $(OBJS:.o=.d)