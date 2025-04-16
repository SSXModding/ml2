GAME_ssxog_mods = test_mod

# US version
GAME_ssxog_us_VALID = yes
# This is incorrect, but I don't feel like rebuilding the 
# 2.9-ee-990721 version that the game *actually* used
GAME_ssxog_us_GCC_VERSION = 2.96-ee-001003-1
GAME_ssxog_us_OBJECTS = $(OBJDIR)/func_wrappers.o $(OBJDIR)/init.o $(foreach mod,$(GAME_ssxog_mods),$(OBJDIR)/$(mod).o)
GAME_ssxog_us_PRODUCTS = $(BINDIR)/crt0_patch.bin $(BINDIR)/libkernl_patch.bin $(BINDIR)/systeminit_patch.bin
GAME_ssxog_us_PNACH = 085653F4.ml2.pnach