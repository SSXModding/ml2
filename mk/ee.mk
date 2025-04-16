
CC = tools/cc/$(GAME_$(GAME)_$(VERSION)_GCC_VERSION)/bin/ee-gcc
CXX = tools/cc/$(GAME_$(GAME)_$(VERSION)_GCC_VERSION)/bin/ee-g++
LD = tools/cc/$(GAME_$(GAME)_$(VERSION)_GCC_VERSION)/bin/ee-ld
OBJCOPY = tools/cc/$(GAME_$(GAME)_$(VERSION)_GCC_VERSION)/bin/ee-objcopy
OBJDUMP = tools/cc/$(GAME_$(GAME)_$(VERSION)_GCC_VERSION)/bin/ee-objdump
CCFLAGS = -G0 -O3 -ffreestanding -nostdlib -Iinclude -I$(GAMEDIR) -I$(OBJDIR)
CXXFLAGS = -G0 -O3 -ffreestanding -fno-rtti -fno-exceptions -nostdlib -Iinclude -I$(GAMEDIR) -I$(OBJDIR)

export CXX
export LD
export OBJDUMP

# Needed to get the paths to crt(begin|end).o.
EE_LIBDIR=tools/cc/$(GAME_$(GAME)_$(VERSION)_GCC_VERSION)/lib/gcc-lib/ee/$(GAME_$(GAME)_$(VERSION)_GCC_VERSION)
EE_CRTBEGIN=$(EE_LIBDIR)/crtbegin.o
EE_CRTEND=$(EE_LIBDIR)/crtend.o

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BINDIR)/%.bin: %.asm
	tools/assemble.sh $< $(BINDIR)/core.elf