#!/bin/python3

from __init__ import *

import json
import sys

# Filename of the patch.json schema
kPatchJsonFilename = 'patch.json'

# Main 

if len(sys.argv) != 3:
    print(f'Usage: {sys.argv[0]} [patch.json file] [output pnach file]')
    sys.exit(1)

patchJson = None
with open(sys.argv[1], 'r') as patchJsonFile:
    patchJson = json.load(patchJsonFile)

    with open(sys.argv[2], 'w') as pnachFileRaw:
        pnachWriter = PnachWriter(pnachFileRaw)
        cheat = pnachWriter.begin_cheat(patchJson['patchName'], patchJson['patchAuthor'], patchJson['patchDescription'])

        # Write all segments out
        for segment in patchJson['patchSegments']:
            pnachWriter.set_base_address(int(segment['org'], 16) & 0xff_ff_ff_ff)
            pnachWriter.write_comment(f' Patch Segment \"{segment['name']}\"')
            # Let's do it!
            with open(segment['source'], 'rb') as segmentDataSource:
                for word in read_as_word_chunks(segmentDataSource):
                    cheat.write_word(word)
            print(f'Wrote segment \"{segment['name']}\" to pnach')
        print('Finished writing pnach!')
