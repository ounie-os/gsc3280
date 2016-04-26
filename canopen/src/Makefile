#
# Copyright (C) 2006 Laurent Bessard
#
# This file is part of canfestival, a library implementing the canopen
# stack
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

# Normal Makefile
PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
OS_NAME = Linux
ARCH_NAME = arm
ENABLE_LSS = 0
INCLUDES = -I../inc -I../../include
CFLAGS = -O2
TARGET = libcanfestival

OBJS = objacces.o lifegrd.o sdo.o pdo.o sync.o nmtSlave.o nmtMaster.o states.o timer.o dcf.o emcy.o

ifeq ($(ENABLE_LSS),1)
OBJS += lss.o
endif

all: canfestival

canfestival: $(TARGET).o

$(TARGET).a: $(OBJS)
	@echo " "
	@echo "*********************************************"
	@echo "**Building [libcanfestival.a]"
	@echo "*********************************************"
	$(CROSS_COMPILE)ar rc $@ $(OBJS)
	$(CROSS_COMPILE)ranlib $@

$(TARGET).o: $(OBJS)
	$(LD) -r $(OBJS) -o $@
	
%.o: %.c
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling $< -> $@"
	@echo "*********************************************"
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET).*
