## add\_day - List Dates

add\_day(1) is a silly utility that prints all dates
between a low/high range.

This can be useful in scripts that need a list of Dates
for testing or other purposes.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* If "DESTDIR" is not set, will install under /usr/local
* Execute ./build.sh to create a Makefile
* this assumes [j\_lib2](https://github.com/jmcunx/j_lib2)
  is also installed under "DESTDIR".
* Works on Linux, BSD and AIX

_To uninstall_, execute
"make uninstall"
from the source directory
