HOSTARCH?=armv7
BOARD?=realview-pbx-a9
CC:=arm-eabi-gcc
CXX:=arm-eabi-g++

CFLAGS?=-O0 -ggdb
CXXFLAGS?=
LDFLAGS?=
LIBS?=
 
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
 
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CXXFLAGS:=$(CXXFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS) -nostdlib -Wl,--gc-sections -ggdb
LIBS:=$(LIBS) -lc -lnosys -lgcc 
 
ARCHDIR=arch/$(HOSTARCH)
BOARDDIR=board/$(BOARD)

include $(ARCHDIR)/make.config
include $(BOARDDIR)/make.config 

$(foreach driver,$(BOARD_DRIVERS),$(eval include drivers/$(driver)/make.config))

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS) $(BOARD_CFLAGS) $(DRIVER_CFLAGS)
CXXFLAGS:=$(CXXFLAGS) $(KERNEL_ARCH_CXXFLAGS) $(BOARD_CXXFLAGS) $(DRIVER_CXXFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS) $(BOARD_LDFLAGS) $(DRIVER_LDFLAGS)
LIBS:=$(KERNEL_ARCH_LIBS) $(BOARD_LIBS) $(DRIVER_LIBS) $(LIBS)
 
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
$(BOARD_OBJS) \
$(DRIVER_OBJS) \
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
.SUFFIXES: .o .c .S .ld
 
all: plaid.kernel
 
plaid.kernel: $(OBJS) $(BOARDDIR)/linker.ld
	$(CC) -T $(BOARDDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
#	grub-file --is-x86-multiboot plaid.kernel
 
$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
 
.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CXXFLAGS)
 
.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CXXFLAGS)
 
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
 
-include $(OBJS:.o=.d)