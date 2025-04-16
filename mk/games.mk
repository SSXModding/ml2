# Default to ssx3/us if no game is explicitly provided.
GAME ?= ssx3
VERSION ?= us

# directories for game/region-speciffic sources
GAMEDIR = src/core/game/$(GAME)
GRDIR = src/core/game/$(GAME)/$(VERSION)
MODDIR = src/mods/$(GAME)

GAMEDEFS = -DGAME_$(GAME)=1 -DVERSION_$(VERSION)=1

# Note that a game being valid is automatically proven by make continuing to build.
#
# GAME_[game]_MODS = list of mod source files to add to the build (version should add them as PRODUCTS)
# 
# GAME_[game]_[version]_VALID=yes
# GAME_[game]_[version]_OBJECTS=custom objects to add to core build process
# GAME_[game]_[version]_PRODUCTS=custom products to add to the build
# GAME_[game]_[version]_PNACH=output PNACH filename (using new pnach organization format)

include mk/games/$(GAME).mk

# sanity check
ifneq ($(GAME_$(GAME)_$(VERSION)_VALID),yes)
$(error The game/version combination $(GAME)/$(VERSION) is currently not supported by ml2. Please pick a different one)
endif