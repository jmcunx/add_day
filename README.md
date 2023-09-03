## add\_day - List Dates

**Note:** Starting October 12 2023, GitHub is forcing me to
use my 2FA access to my repositories via my Cell Phone or some
proprietary application.  So updates to this project will no
longer occur on GitHub.  Updates can be downloaded from my
gemini capsule:

* gemini://gem.sdf.org/jmccue/reposatory.gmi
* gemini://gem.sdf.org/jmccue/reposatory.gmi (mirror)

[See gemini wikipedia](https://en.wikipedia.org/wiki/Gemini_(protocol)#Software) for clients.


add\_day(1) is a silly utility that prints all dates
between a low/high range.

This can be useful in scripts that need a list of Dates
for testing or other purposes.

[j\_lib2](https://github.com/jmcunx/j_lib2) is an **optional** dependency.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* If "DESTDIR" is not set, will install under /usr/local
* Execute ./build.sh to create a Makefile
* Works on Linux, BSD and AIX

_To uninstall_, execute
"make uninstall"
from the source directory
