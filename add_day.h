/*
 * Copyright (c) 2020 ... 2023 2024
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * aday.h -- Header
 */

#ifndef ADD_DAY_H

#define ADD_DAY_H "INCLUDED"

#define PROG_NAME "add_list"
#define FMT_DATE 11

#define FMT_OUT_00   0    /* YYYYMMDD   */
#define FMT_OUT_01   1    /* YYYY/MM/DD */
#define FMT_OUT_02   2    /* YYYY-MM-DD */
#define FMT_OUT_03   3    /* MM/DD/YYYY */
#define FMT_OUT_04   4    /* DD-MM-YYYY */

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif

struct s_work
{
  int ofmt;
  char *date_low;
  char *date_high;
};
#ifdef NO_JLIB
struct s_j2_datetime
{
  int month;    /* Month,           01 --12             */
  int dd;       /* Day of Month,    01 -- [28|29|30|31] */
  int yy;       /* two digit year,  00 -- 99            */
  int yyyy;     /* four digit year, 0000 -- 9999        */
  int hh;       /* Hour of the day, 00 -- 23            */
  int minutes;  /* minutes,         00 -- 59            */
  int ss;       /* seconds,         00 -- 59            */
  int mil;      /* milliseconds,    000 -- 999          */
  int tm_isdst; /* Daylight ?  0 = no, > 0 = yes        */
} ;
#endif /* NO_JLIB */

/*** messages ***/
#define MSG_HELP_11  "Print Dates by adding one Day"

#ifdef NO_JLIB
#define ARG_DATE_LOW      'L'  /* Low Date                           */
#define ARG_DATE_MAX      'M'  /* Maximum (High) Date                */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_OUT_FMT       'F'  /* Output Format                      */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_REV           "Revision"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E008      "ERROR E008: '%s' is an invalid value for %c%c, must be numeric\n"
#define MSG_ERR_E074      "ERROR E074: 'Too many Arguments specified for %c%c\n"
#define MSG_ERR_E081      "ERROR E081: Required Argument '%c%c' is NOT numeric (%s)\n"
#define MSG_ERR_E082      "ERROR E082: Required Argument '%c%c' invalid length (%s)\n"
#define MSG_ERR_E083      "ERROR E083: Required Argument '%c%c' must be between %d and %d, but is %d\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_DATE_LOW    "\t%c%c date\t\t: Low Date Value for Range Print.\n"
#define USG_MSG_ARG_DATE_MAX    "\t%c%c date\t\t: Maximum (High) Date for Date Range Print.\n"
#define USG_MSG_ARG_HELP        "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_OUT_FMT_D0  "\t\t\t    %d  Use Format YYYYMMDD \n"
#define USG_MSG_ARG_OUT_FMT_D1  "\t\t\t    %d  Use Format YYYY/MM/DD \n"
#define USG_MSG_ARG_OUT_FMT_D2  "\t\t\t    %d  Use Format YYYY-MM-DD \n"
#define USG_MSG_ARG_OUT_FMT_D3  "\t\t\t    %d  Use Format MM/DD/YYYY \n"
#define USG_MSG_ARG_OUT_FMT_D4  "\t\t\t    %d  Use Format DD-MM-YYYY \n"
#define USG_MSG_ARG_OUT_FMT_DH  "\t%c%c n\t\t: Print the date using format 'n' where 'n' is:\n"
#define USG_MSG_ARG_VERSION     "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_OPTIONS         "Options\n"
#define USG_MSG_USAGE_1         "usage:\t%s [OPTIONS]\n"
#endif /* NO_JLIB */

/*** prototypes ***/
#ifdef NO_JLIB
int j2_is_numr(char *s);
void j2_today(struct s_j2_datetime *dt);
int j2_d_isleap(int year_yyyy);
#endif /* NO_JLIB */

#endif /* ADD_DAY_H */

