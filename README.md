# SharpSpades.Native

Native C library for [SharpSpades](https://github.com/JStalnac/SharpSpades)

The native code has been moved into SharpSpades for easier maintainance and this repository is now archived.
You can find the latest native code under the
[`native`](https://github.com/JStalnac/SharpSpades/tree/master/native)
directory in the SharpSpades repository.

## Credits
 - Physics code - [SpadesX](https://github.com/SpadesX/SpadesX)
 - Map library - [libmapvxl](https://github.com/SpadesX/libmapvxl)

## Building
```bash
cmake -S . -B ./build
cmake --build ./build --config Release
```

## Creating a NuGet package
See `package`
