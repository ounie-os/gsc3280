#! gmake

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

OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS =  -D_GNU_SOURCE -D_REENTRANT -nostdlib -fno-builtin
EXE_CFLAGS =  -L/usr/xenomai/lib -lxenomai -lpthread -lrt -L/usr/xenomai/lib -Wl,-rpath /usr/xenomai/lib -lnative -lrtdm -ldl
TARGET = libcanopenuser

INCLUDES = -I ./matiec -I../inc -I../../include

MASTER_OBJS = CF_0.o OD_0_0.o plc_debugger.o

OBJS = $(MASTER_OBJS)

all: $(TARGET).o

$(TARGET).a: $(OBJS)
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
	rm -f $(MASTER_OBJS) $(TARGET).*