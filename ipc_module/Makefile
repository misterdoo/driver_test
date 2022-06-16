
KO_FILE_NAME = test-simple
NAME = $(KO_FILE_NAME)

obj-m := $(KO_FILE_NAME).o

$(KO_FILE_NAME)-objs := main.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	@rm -f Module.symvers modules.order
	@rm -f ${NAME}.o ${NAME}.mod ${NAME}.mod.c ${NAME}.mod.o

