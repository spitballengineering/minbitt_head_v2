# Minbitt head v2

# Build
```bash

meson setup builddir --buildtype=release
meson compile -C builddir
```

## Running
```bash
./builddir/minbitt_hud
```
> Note you may have to add env variables in linux to use gpu
```bash
__GLX_VENDOR_LIBRARY_NAME=nvidia;__NV_PRIME_RENDER_OFFLOAD=1
```