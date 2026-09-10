project('minbitt_head_v2', 'c',
        version : '1.0.0',
        default_options : ['warning_level=3', 'c_std=c11'],
)

#TODO: configure option to select which platform to compile for
# also allow for cross compilation

#raylib = dependency('raylib', default_options : ['warning_level=0'])
cmake = import('cmake')
opt_var = cmake.subproject_options()
opt_var.add_cmake_defines({ 'BUILD_EXAMPLES' : false, # Call CMake with `-DBUILD_EXAMPLES=OFF`
                            'CMAKE_POLICY_DEFAULT_CMP0200' : 'OLD', # supressses dev warnings
                          })
opt_var.append_compile_args('c', '-w') # supresses warnings from raylib
raylib_sub_proj = cmake.subproject('raylib', options : opt_var)
raylib = raylib_sub_proj.dependency('raylib')


raygui = dependency('raygui', default_options : ['warning_level=0'])
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false) # reqired by raylib

hud = executable('minbitt_hud', ['main.c'],
                 dependencies : [m_dep, raylib, raygui],
                 install : true)

test('test', hud)
