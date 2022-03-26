## add\_day - List Dates

add\_day(1) is a silly utility that prints all dates
between a low/high range.

This can be useful in scripts that need a list of Dates
for testing or other purposes.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* Set "DESTDIR" for where you want this to install.
  Examples: setenv DESTDIR /usr/local
            export DESTDIR=/usr/local
* Edit Makefile
  * If on AIX and comment out the Linux/BSD area and uncomment AIX Area.
  * If Linux or a BSD, validate setting for "LIBJLIB2", right now
    it defaults to 64 bit Linux.
  * this assumes [j\_lib2](https://github.com/jmcunx/j_lib2)
    is also installed under "DESTDIR".

**Will install:**
* Binary add\_day
* Manual add\_day.1[.gz] depending on OS

To uninstall, execute
* "make uninstall" from the source directory
