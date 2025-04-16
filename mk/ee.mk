
CXX = tools/cc/bin/ee-g++
LD = tools/cc/bin/ee-ld
OBJCOPY = tools/cc/bin/ee-objcopy
OBJDUMP = tools/cc/bin/ee-objdump
CXXFLAGS = -G0 -O3 -ffreestanding -fno-rtti -fno-exceptions -nostdlib -Iinclude -I$(GAMEDIR) -I$(OBJDIR)

# Needed for some stuff
EE_LIBDIR=tools/cc/lib/gcc-lib/ee/2.96-ee-001003-1
EE_CRTBEGIN=$(EE_LIBDIR)/crtbegin.o
EE_CRTEND=$(EE_LIBDIR)/crtend.o

# b
$(OBJDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BINDIR)/%.bin: %.asm
	tools/assemble.sh $< $(BINDIR)/core.elf