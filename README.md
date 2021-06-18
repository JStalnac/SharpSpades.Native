# SharpSpades.Native

Native C++ library for [SharpSpades](https://github.com/JStalnac/SharpSpades)

## Sources
`common_c.h`, `constants_c.h`, `memory.h` and `world_c.c`: [piqueserver](https://github.com/piqueserver/piqueserver) (License GPLv3)

`libvxl.c`, `libvxl.h`: [libvxl](https://github.com/xtreme8000/libvxl) (License MIT)

## Building
```bash
cmake -S . -B ./build
cmake --build ./build --config Release
```

## Creating a NuGet package
See `package`
