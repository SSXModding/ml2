# default to ssx3/us if no game is explicitly provided on make invocations
GAME ?= ssx3
REGION ?= us

GAMEDIR = src/core/game/$(GAME)
GRDIR = src/core/game/$(GAME)/$(REGION)
MODDIR = src/mods/$(GAME)

GAME_ssx3_VALID = yes
GAME_ssx3_mods = test_mod

# game specific stuff goes here!!!!
# what each thing is:
# _VALID=yes
# _OBJECTS=custom objects to add to core build process
# _PRODUCTS=custom products to add to the build
# _PNACH=output PNACH filename (using new pnach organization format)
GAME_ssx3_us_VALID=yes
GAME_ssx3_us_OBJECTS=$(OBJDIR)/func_wrappers.o $(OBJDIR)/init.o $(foreach mod,$(GAME_ssx3_mods),$(OBJDIR)/$(mod).o)
GAME_ssx3_us_PRODUCTS=$(BINDIR)/crt0_patch.bin $(BINDIR)/libkernl_patch.bin $(BINDIR)/systeminit_patch.bin
GAME_ssx3_us_PNACH=08FFF00D.ml2.pnach

ifneq ($(GAME_$(GAME)_$(REGION)_VALID),yes)
$(error "The game/region combination $(GAME)/$(REGION) is currently not supported by elfldr2. Please pick a different one")
endif