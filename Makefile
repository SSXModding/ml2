include mk/games.mk

VPATH = src/core/ $(GAMEDIR) $(GRDIR)

BINDIR := bin/$(GAME)/$(REGION)
OBJDIR := obj/$(GAME)/$(REGION)

OBJS = $(OBJDIR)/main.o $(OBJDIR)/sio.o $(GAME_$(GAME)_$(REGION)_OBJECTS)

include mk/ee.mk


all: $(BINDIR)/ $(OBJDIR)/ $(BINDIR)/$(GAME_$(GAME)_$(REGION)_PNACH)

clean:
	rm -rf $(BINDIR)/ $(OBJDIR)/


begin_address: $(BINDIR)/core.bin
	@$(OBJDUMP) -t $(BINDIR)/core.elf | grep "_begin" | cut -d' ' -f1 | cut -c9-

core_entry_address: $(BINDIR)/core.bin
	$(OBJDUMP) -t $(BINDIR)/core.elf | grep "mlStart" | cut -d' ' -f1 | cut -c9-

# PC Tutoriale HOW TO GET ENDING ADDRESS FOR PATCHING
end_address: $(BINDIR)/core.bin
	@$(OBJDUMP) -t $(BINDIR)/core.elf | grep "_end" | cut -d' ' -f1 | cut -c9-

$(BINDIR)/$(GAME_$(GAME)_$(REGION)_PNACH): $(BINDIR)/core.bin $(GAME_$(GAME)_$(REGION)_PRODUCTS)
	tools/pnach_utils/output_pnach.py $(GRDIR)/patch.json $@

$(BINDIR)/core.bin: $(BINDIR)/core.elf
	$(OBJCOPY) -O binary $< $@

$(BINDIR)/core.elf: $(OBJS)
	cpp -P link/ml2core.ld -I$(GRDIR) -o $(OBJDIR)/linktmp.ld
	$(LD) -nostartfiles -T $(OBJDIR)/linktmp.ld $(OBJS) -o $@

$(BINDIR)/:
	mkdir -p $@

$(OBJDIR)/:
	mkdir -p $@
