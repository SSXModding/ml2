# ML2 Makefile
# Currently this only builds the core

include mk/games.mk

VPATH = src/core/ $(GAMEDIR) $(GRDIR) $(MODDIR)

BINDIR := bin/$(GAME)/$(VERSION)
OBJDIR := obj/$(GAME)/$(VERSION)

# runtime
RUNTIME_OBJECTS = \
	$(OBJDIR)/cxx_new_delete.o \
	$(OBJDIR)/cxx_runtime.o \
	$(OBJDIR)/sio.o

OBJS = $(RUNTIME_OBJECTS) \
	$(OBJDIR)/main.o $(OBJDIR)/mod.o \
	$(GAME_$(GAME)_$(VERSION)_OBJECTS)

include mk/ee.mk

CXXFLAGS += $(GAMEDEFS)


all: $(BINDIR)/ $(OBJDIR)/ $(OBJDIR)/vthook_generated.hpp $(BINDIR)/$(GAME_$(GAME)_$(VERSION)_PNACH)

clean:
	rm -rf $(BINDIR)/ $(OBJDIR)/

$(OBJDIR)/vthook_generated.hpp: tools/vthook_template.jinja2 tools/generate_vthook.py
	tools/generate_vthook.py $@

$(BINDIR)/$(GAME_$(GAME)_$(VERSION)_PNACH): $(BINDIR)/core.bin $(GAME_$(GAME)_$(VERSION)_PRODUCTS)
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
