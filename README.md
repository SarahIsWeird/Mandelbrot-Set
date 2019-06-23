# Mandelbrot Set Viewer

A Mandelbrot set renderer in C++/SFML. The program renders a black and white Mandelbrot set. It's not being worked on anymore, as this was just a little project to explore the math behind the Mandelbrot set, and thus it's not optimized _at all_. Prepare for a horrendous drawing time.

## Compiling

Requirements:
- GNU GCC, LLVM Clang or any other C++ compiler
- [SFML](https://www.sfml-dev.org/)

```bash
$ <compiler> -o mandelbrot[.exe] mandelbrot.cpp -I"<sfml-path>/include/" -L"<sfml-path>/lib/" \
         -lsfml-system -lsfml-window -lsfml-graphics
```

## Binaries

A windows binary can be found on the [release page](https://github.com/SarahIsWeird/Mandelbrot-Set/releases/tag/v1.0).

## License

Released under the WTFPL license. See [COPYING](COPYING) for more information.
