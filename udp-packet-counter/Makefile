ifeq ($(KERNELRELEASE),)

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

module:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD)  modules

clean:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD)  clean

.PHONY: module clean

else

MODULE = udp_packet_counter.o
CFLAGS_$(MODULE) := -DDEBUG
obj-m := $(MODULE)

endif
