* README_EN.txt
* 2019.11.24
* p7client

1. DESCRIPTION
2. LICENSE
3. REPOSITORIES
4. INSTALLATION
5. AUTHOR EMAIL

-------------------------------------------------------------------------------
1. DESCRIPTION
-------------------------------------------------------------------------------
p7client patched sources fork from: http://baical.net/p7.html

Based on version: 5.2

Some review and tests versus other loggers on russian website (RU):
  https://habr.com/post/313686/

From author:
  P7 is open source and cross-platform library for high-speed sending
  telemetry & trace data from your application with minimal usage of CPU and
  memory. Library contains exhaustive documentation inside package.

Features:
  * C++/C/C#/Python support
  * Cross platform (Linux x86/x64, Windows x86/x64)
  * Speed is priority, library and server are designed and optimized to suit
    high load, for example average performance for Intel i7-870
    (more than 10 years old CPU) is
  Traces:
  ** 0,5% CPU, one core: 450 000 traces per second (binary file or network)
  ** 100% CPU, one core: ~5.7 million traces per second to network
  ** 100% CPU, one core: ~10 million traces per second to binary file
  Telemetry:
  ** 0,5% CPU, one core: 600 000 telemetry samples per second (binary file or
     network)
  ** 100% CPU, one core: ~6.8 million telemetry samples per second to network
  ** 100% CPU, one core: ~11 million telemetry samples per second to binary
     file
  * Small memory footprint (optional, min is 16KB) - used for embedded devices
  * Thread safe
  * Unicode support (UTF-8, UTF-32 for Linux, UTF-16 for Windows)
  * ANSI char support
  * No external dependencies
  * High-resolution time stamps (resolution depends on HW high-resolution
    performance counter, usually it is 100ns)
  * Different sinks (transport & storages) are supported:
  ** Network (Baical server)
  ** Binary File
  ** Text File (Linux: UTF-8, Windows: UTF-16)
  ** Console
  ** Syslog (RFC 5424)
  ** Auto (Baical server if reachable, else - binary file)
  ** Null
  * Files rotation setting (by size or time)
  * Files max count setting (deleting old files automatically)
  * Remote management from Baical server (set verbosity per module,
    enable/disable telemetry counters)
  * Shared memory is used - create your trace and telemetry channels once and
    access it from any process module or class without passing handles
  * Crash handler or in case of user defined crash handler - special function
    to flush all P7 buffers for all P7 objects inside process in case of crush
  * Trace & telemetry files have compact binary format (due to speed
    requirements - binary files much more compact than raw text), export to
    text is available
  * Command line interface for configuration may be used in addition to
    application parameters
  * Big/Little endian support
  * Intel/AMD, ARM, MCST, PowerPC, Baikal T1, etc.
  * GCC, VC++, Clang, MinGW

The original library patched to fix these issues:

1. Added CMakeLists.txt file.

Cmake scripts uses the cmake modules from the tacklelib library:

https://svn.code.sf.net/p/tacklelib/tacklelib/trunk/cmake/tacklelib

-------------------------------------------------------------------------------
2. LICENSE
-------------------------------------------------------------------------------
GNU LESSER GENERAL PUBLIC LICENSE
(see included text file "License.txt" or
https://en.wikipedia.org/wiki/GNU_Lesser_General_Public_License)

-------------------------------------------------------------------------------
3. REPOSITORIES
-------------------------------------------------------------------------------
Primary:
  * https://sf.net/p/tacklelib/3dparty--p7client/HEAD/tree/trunk
    https://svn.code.sf.net/p/tacklelib/3dparty--p7client/trunk
First mirror:
  * https://github.com/andry81/tacklelib--3dparty--p7client/tree/trunk
    https://github.com/andry81/tacklelib--3dparty--p7client.git
Second mirror:
  * https://bitbucket.org/andry81/tacklelib-3dparty-p7client/src/trunk
    https://bitbucket.org/andry81/tacklelib-3dparty-p7client.git

-------------------------------------------------------------------------------
4. INSTALLATION
-------------------------------------------------------------------------------
N/A

-------------------------------------------------------------------------------
5. AUTHOR EMAIL
-------------------------------------------------------------------------------
Andrey Dibrov (andry at inbox dot ru)
