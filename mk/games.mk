# Default to ssx3/us if no game is explicitly provided.
GAME ?= ssx3
REGION ?= us

# directories for game/region-speciffic sources
GAMEDIR = src/core/game/$(GAME)
GRDIR = src/core/game/$(GAME)/$(REGION)
MODDIR = src/mods/$(GAME)

GAMEDEFS = -DGAME_$(GAME)=1 -DREGION_$(REGION)=1

# Note that a game being valid is automatically proven by make continuing to build.
#
# GAME_[game]_MODS = list of mod source files to add to the build (region should add them as PRODUCTS)
# 
# GAME_[game]_[region]_VALID=yes
# GAME_[game]_[region]_OBJECTS=custom objects to add to core build process
# GAME_[game]_[region]_PRODUCTS=custom products to add to the build
# GAME_[game]_[region]_PNACH=output PNACH filename (using new pnach organization format)

include mk/$(GAME).mk

ifneq ($(GAME_$(GAME)_$(REGION)_VALID),yes)
$(error The game/region combination $(GAME)/$(REGION) is currently not supported by ml2. Please pick a different one)
endif