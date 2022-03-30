#!/bin/sh
#
# generate a Makefile from Makefile.unx
# for a UN*X Type Systems
#

#------------------------------------------------------------------------------
# set install location and OS Info
#------------------------------------------------------------------------------
if test "$DESTDIR" = ""
then
    DESTDIR="/usr/local"
    export DESTDIR
fi

if test "$OS" = ""
then
    OS=`uname -s`
    export OS
fi

case "`uname -m`" in
    "x86_64")
	if test "$OS" = "Linux"
	then
	    g_sed_1="^#LINUX64#"
	    g_lib="lib64"
	else
	    g_sed_1="^#LINUX32#"
	    g_lib="lib"
	fi
	;;
    "amd64")
	g_sed_1="^#BSD64#"
	g_lib="lib"
	;;
    *)
	if test "$OS" = "AIX"
	then
	    g_sed_1="^#AIX#"
	    g_lib="lib"
	else
	    echo "E01: $OS not supported"
	    exit 2
	fi
	;;
esac

#------------------------------------------------------------------------------
# look for j_lib2
#------------------------------------------------------------------------------
if test -f "$DESTDIR/$g_lib/libj_lib2.so" -o "$DESTDIR/$g_lib/libj_lib2.a"
then
    g_include="$DESTDIR/include"
    g_libloc="$DESTDIR/$g_lib"
else
    if test -f "/usr/$g_lib/libj_lib2.so" -o "/usr/$g_lib/libj_lib2.a"
    then
	g_include="/usr/include"
	g_libloc="/usr/$g_lib"
    else
	if test -f "/usr/local/$g_lib/libj_lib2.so" -o "/usr/local/$g_lib/libj_lib2.a"
	then
	    g_include="/usr/local/include"
	    g_libloc="/usr/local/$g_lib"
	else
	    if test -f "/opt/jmc/$g_lib/libj_lib2.so" -o "/opt/jmc/$g_lib/libj_lib2.a"
	    then
		g_include="/opt/jmc/include"
		g_libloc="/opt/jmc/$g_lib"
	    else
		echo "E10: cannot find j_lib2"
		exit 2
	    fi
	fi
    fi
fi

#------------------------------------------------------------------------------
# create Makefile
#------------------------------------------------------------------------------
sed "s%$g_sed_1%%;s%INCJLIB%$g_include%g;s%JLIBLOC%$g_libloc%g" < Makefile.unx > Makefile

cat << EOF

Created Makefile
    OS     $OS
    j_lib2 Include Location:  $g_include
    j_lib2 Library Location:  $g_libloc
    Install Location:         $DESTDIR

Review and modify if necessary

EOF

exit 0
