project('minbitt_head_v2', 'c',
        version : '1.0.0',
        default_options : ['warning_level=3', 'c_std=c11'],
)
raylib = dependency('raylib', default_options : ['warning_level=0'])
raygui = dependency('raygui', default_options : ['warning_level=0'])
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false) # reqired by raylib

hud = executable('minbitt_hud', ['main.c'],
                 dependencies : [m_dep, raylib, raygui],
                 install : true)

test('test', hud)
