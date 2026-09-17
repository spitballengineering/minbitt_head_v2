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
#                            'GLFW_USE_HYBRID_HPG': 1, # (NOTE: Windows only) to use gpu instead of intigrated graphics
                          })
opt_var.append_compile_args('c', '-w') # supresses warnings from raylib
raylib_sub_proj = cmake.subproject('raylib', options : opt_var)
raylib = raylib_sub_proj.dependency('raylib')


#TODO: decided if you want to keep raygui for non GUI Debug
raygui = dependency('raygui', default_options : ['warning_level=0'])
cc = meson.get_compiler('c') # TODO: switch to clang
m_dep = cc.find_library('m', required : false) # reqired by raylib

src = [
    'src/blendshapes.h',
    'src/camera.h',
    'src/connection.c',
    'src/connection.h',
    'src/controller.c',
    'src/controller.h',
    'src/front_screen.h',
    'src/main.c',
    'src/minbitt_face_animation.c',
    'src/minbitt_face_animation.h',
    'src/gui_minbitt_editor.h'
]

#TODO: decided if you want to do the headder and 2 implementation .c files for cross compliation or just a bunch of ifdefs
#TODO: optimize cmake build for embedded https://github.com/raysan5/raylib/wiki/CMake-Build-Options
hud = executable('minbitt_hud', src,
                 dependencies : [m_dep, raylib, raygui],
                 install : true)

hud_editor = executable('minbitt_hud_editor', src,
                        dependencies : [m_dep, raylib, raygui],
                        c_args : ['-DEDITOR'],
                        install : true) #TODO: test on windows

test('test', hud)
