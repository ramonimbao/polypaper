polypaper
=========

Random low-poly wallpaper generator
with inspiration from
[Flat Surface Shader by Matther Wagerfield](http://matthew.wagerfield.com/flat-surface-shader/), and
[Poly Wallpaper Pack by Ryan Kelly](http://ryanmkelly.me/android/wallpaper/).

Sample of ten randomly generated wallpapers: http://imgur.com/a/LRFQt#0

usage
=====
polypaper [-h] [width] [height] [light-ambient] [light-diffuse] [mesh-ambient] [mesh-diffuse]

-h, --help, -help: shows the help

width: width of the output bmp

height: height of the output bmp

light-ambient: hex ambient color of the light

light-diffuse: hex diffuse color of the light

mesh-ambient: hex ambient color of the mesh

mesh-diffuse: hex diffuse color of the mesh


outputs a "output.bmp" of the generated wallpaper.

dependencies
============
* [SDL 1.2](https://www.libsdl.org/download-1.2.php)
* [SDL_gfx](http://cms.ferzkopp.net/index.php/software/13-sdl-gfx)
* [glm](http://glm.g-truc.net/)

license
=======

The MIT License (MIT)

Copyright (c) 2014 Ramon Imbao

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

SDL under the [GNU LGPL license](http://www.gnu.org/copyleft/lesser.html)

SDL_gfx under the [zlib license](http://en.wikipedia.org/wiki/Zlib_License)

