#!/usr/bin/env python3

from jinja2 import Environment, FileSystemLoader

# This script generates individual mlVtHookMan* C++ implementations
# from a single Jinja template. While this code generation
# is, in multiple aspects, quite annoying, it's the least
# friction required short of implementing Babel for C++,
# which... I'm not going to do. Sorry

kMaxArguments = 9 # 10 actually but whatever!!!

def formatArgTypeName(i):
    return f'TArg{i}'

def formatArgName(i):
    return f'arg{i}'

env = Environment(loader=FileSystemLoader('.'), trim_blocks=True, lstrip_blocks=True)
template = env.get_template('vthook_template.jinja2')
outputs = []

for i in range(0, kMaxArguments+1):
    data = {}
    data['name'] = f'mlVtHookMan{i}'
    data['nr_args'] = i

    data['signature_template_types'] = ''
    data['signature'] = ''
    data['signature_call'] = ''

    if i != 0:
        # setup these
        data['signature_template_types'] = ', '
        data['signature'] = ', '
        data['signature_call'] = ', '

        for j in range(0, i):
            data['signature_template_types'] += f'typename {formatArgTypeName(j+1)}'
            data['signature'] += f'{formatArgTypeName(j+1)} {formatArgName(j+1)}'
            data['signature_call'] += f'{formatArgName(j+1)}'
            if j != i - 1:
                data['signature_template_types'] += ', '
                data['signature'] += ', '
                data['signature_call'] += ', '
    output = template.render(data=data)
    outputs.append(output)

with open(f'vthook_generated.hpp', 'w') as hppFile:
    hppFile.write('#ifndef ML_VTHOOK_GENERATED_HPP\n')
    hppFile.write('#define ML_VTHOOK_GENERATED_HPP\n\n')
    hppFile.write('// This file was generated. Do not edit it, changes will be lost the next time it is regenerated.\n\n')
    for output in outputs:
        hppFile.write(output)
        hppFile.write('\n\n')

    hppFile.write('\n')
    hppFile.write('#endif')
