* README_EN.txt
* 2023.03.08
* p7client

1. DESCRIPTION
2. SOURCES
3. PATCHES
4. DEPENDENCIES
5. EXTERNALS
6. AUTHOR

-------------------------------------------------------------------------------
1. DESCRIPTION
-------------------------------------------------------------------------------
`p7client` library fork

Some review and tests versus other loggers on russian website (RU):
  https://habr.com/post/313686/

-------------------------------------------------------------------------------
2. SOURCES
-------------------------------------------------------------------------------
http://baical.net/p7.html

-------------------------------------------------------------------------------
3. PATCHES
-------------------------------------------------------------------------------
The original library patched to fix these issues:

1. Linux x86_64 build.
2. Msys/mingw build.
3. Asm compilation under gcc `error: symbol crc32loop is already defined`.
4. Access to long UNC paths under Windows (only backward slashes must be used
   there).
5. Replaced usage of -pthread by target_link_libraries as more reliable.

-------------------------------------------------------------------------------
4. DEPENDENCIES
-------------------------------------------------------------------------------
`CMakeLists.txt`:

* `tacklelib`

-------------------------------------------------------------------------------
5. EXTERNALS
-------------------------------------------------------------------------------
To checkout externals you must use the
[vcstool](https://github.com/dirk-thomas/vcstool) python module.

NOTE:
  To install the module from the git repository:

  >
  python -m pip install git+https://github.com/dirk-thomas/vcstool

-------------------------------------------------------------------------------
6. AUTHOR
-------------------------------------------------------------------------------
Andrey Dibrov (andry at inbox dot ru)
