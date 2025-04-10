
CXX = tools/cc/bin/ee-g++
LD = tools/cc/bin/ee-ld
OBJCOPY = tools/cc/bin/ee-objcopy
OBJDUMP = tools/cc/bin/ee-objdump
CXXFLAGS = -G0 -O3 -ffreestanding -fno-exceptions -nostdlib -I include

# b
$(OBJDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BINDIR)/%.bin: %.asm
	tools/armips.exe $(ASMFLAGS) $<