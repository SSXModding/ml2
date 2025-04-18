#!/bin/bash

# Wrapper script to add equates to armips invocation from the ml2 core elf file
set -euo pipefail

# Query addresses from core.elf (they are valid for the bin file too)
END_ADDRESS=$(printf '0x%s' $($OBJDUMP -t $2 | grep "_end" | cut -d' ' -f1 | cut -c9-))
MLSTART_ADDRESS=$(printf '0x%s' $($OBJDUMP -t $2 | grep "mlStart" | cut -d' ' -f1 | cut -c9-))

echo "End is $END_ADDRESS"
echo "mlStart @ $MLSTART_ADDRESS"

# Assemble required object
tools/armips -equ NEW_END_ADDRESS $END_ADDRESS -equ MLSTART_ADDRESS $MLSTART_ADDRESS $1