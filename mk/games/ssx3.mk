GAME_ssx3_mods = test_mod

# US version
GAME_ssx3_us_VALID = yes
GAME_ssx3_us_GCC_VERSION = 2.96-ee-001003-1
GAME_ssx3_us_OBJECTS = $(OBJDIR)/func_wrappers.o $(OBJDIR)/init.o $(foreach mod,$(GAME_ssx3_mods),$(OBJDIR)/$(mod).o)
GAME_ssx3_us_PRODUCTS = $(BINDIR)/crt0_patch.bin $(BINDIR)/libkernl_patch.bin $(BINDIR)/systeminit_patch.bin
GAME_ssx3_us_PNACH = 08FFF00D.ml2.pnach