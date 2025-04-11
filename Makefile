# ML2 Makefile
# Currently this only builds the core

include mk/games.mk

VPATH = src/core/ $(GAMEDIR) $(GRDIR) $(MODDIR)

BINDIR := bin/$(GAME)/$(REGION)
OBJDIR := obj/$(GAME)/$(REGION)

OBJS = $(OBJDIR)/rt.o $(OBJDIR)/main.o $(OBJDIR)/sio.o $(OBJDIR)/mod.o $(GAME_$(GAME)_$(REGION)_OBJECTS)

include mk/ee.mk


all: $(BINDIR)/ $(OBJDIR)/ $(BINDIR)/$(GAME_$(GAME)_$(REGION)_PNACH)

clean:
	rm -rf $(BINDIR)/ $(OBJDIR)/

$(BINDIR)/$(GAME_$(GAME)_$(REGION)_PNACH): $(BINDIR)/core.bin $(GAME_$(GAME)_$(REGION)_PRODUCTS)
	tools/pnach_utils/output_pnach.py $(GRDIR)/patch.json $@

$(BINDIR)/core.bin: $(BINDIR)/core.elf
	$(OBJCOPY) -O binary $< $@

$(OBJDIR)/linktmp.ld: link/ml2core.ld $(GRDIR)/symbols.ld
	cpp -P link/ml2core.ld -I$(GRDIR) -o $(OBJDIR)/linktmp.ld

# note that the linker script is preprocessed so that we can add game/region-specific definitions
$(BINDIR)/core.elf: $(OBJS) $(OBJDIR)/linktmp.ld
	$(LD) -nostartfiles -T $(OBJDIR)/linktmp.ld $(EE_CRTBEGIN) $(OBJS) $(EE_CRTEND) -o $@

$(BINDIR)/:
	mkdir -p $@

$(OBJDIR)/:
	mkdir -p $@
