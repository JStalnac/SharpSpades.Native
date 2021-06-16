# SharpSpades.Native

Native C++ library for [SharpSpades](https://github.com/JStalnac/SharpSpades)

## Sources
`common_c.h`, `constants_c.h`, `vxl_c.h`, `vxl_c.cpp` and `world_c.cpp`: [piqueserver](https://github.com/piqueserver/piqueserver) (License GPLv3)

## Building
```bash
cmake -S . -B ./build
cmake --build ./build --config Release
```

## Creating a NuGet package
See `package`
