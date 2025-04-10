GAME ?= ssx3
REGION ?= us

GAMEDIR = src/core/game/$(GAME)
GRDIR = src/core/game/$(GAME)/$(REGION)

# game specific stuff goes here!!!!
GAME_ssx3_us_VALID=yes
GAME_ssx3_us_OBJECTS=$(OBJDIR)/func_wrappers.o
# Extra productssss yoooooo holy fuck pacman here
GAME_ssx3_us_PRODUCTS=$(BINDIR)/codemem_patch.bin $(BINDIR)/systeminit_patch.bin
GAME_ssx3_us_PNACH=08FFF00D.ml2.pnach

ifneq ($(GAME_$(GAME)_$(REGION)_VALID),yes)
$(error "The game/region combination $(GAME)/$(REGION) is currently not supported by elfldr2. Please pick a different one")
endif