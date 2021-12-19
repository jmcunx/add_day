/*
 * Copyright (c) 2020 2021 2022
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
 * aday.c -- Generate a list of Dates between a specified range
 */

#define PROG_NAME "add_list"

#ifndef _MSDOS
#include <sys/param.h>
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

#ifndef OpenBSD
#include <sys/timeb.h>
#endif

#ifdef OpenBSD
#include <sys/time.h>
#define BSD_TODAY 1
#endif

#ifdef __FreeBSD_version
#include <sys/time.h>
#define BSD_TODAY 1
#endif

#ifdef __NetBSD_Version__
#include <sys/time.h>
#define BSD_TODAY 1
#endif

#include <j_lib2.h>
#include <j_lib2m.h>

#define SCKARG 80
#define FMT_DATE 11

struct s_work
{
  int ofmt;
  char *date_low;
  char *date_high;
};

#define FMT_OUT_00   0    /* YYYYMMDD   */
#define FMT_OUT_01   1    /* YYYY/MM/DD */
#define FMT_OUT_02   2    /* YYYY-MM-DD */
#define FMT_OUT_03   3    /* MM/DD/YYYY */
#define FMT_OUT_04   4    /* DD-MM-YYYY */

#define MSG_HELP_11  "Print Dates by adding one Day"

/*
 * verify_date() -- Validate a date argument
 */
void verify_date(char *dstr, char argletter)
{

  if ( j2_is_numr(dstr) == FALSE)
    {
	fprintf(stderr, MSG_ERR_E081,  SWITCH_CHAR, argletter, dstr);
	fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	exit(EXIT_FAILURE);
    }
  if ( strlen(dstr) != 8)
    {
	fprintf(stderr, MSG_ERR_E082,  SWITCH_CHAR, argletter, dstr);
	fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	exit(EXIT_FAILURE);
    }

} /* verify_date() */

/*
 * show_help()
 */
void show_help(FILE *fp)
{
  fprintf(fp, USG_MSG_USAGE_1, PROG_NAME);
  fprintf(fp, "\t%s\n", MSG_HELP_11);
  fprintf(fp, USG_MSG_OPTIONS);
  fprintf(fp, USG_MSG_ARG_OUT_FMT_DH,    SWITCH_CHAR, ARG_OUT_FMT);
  fprintf(fp, USG_MSG_ARG_OUT_FMT_D0,    FMT_OUT_00);
  fprintf(fp, USG_MSG_ARG_OUT_FMT_D1,    FMT_OUT_01);
  fprintf(fp, USG_MSG_ARG_OUT_FMT_D2,    FMT_OUT_02);
  fprintf(fp, USG_MSG_ARG_OUT_FMT_D3,    FMT_OUT_03);
  fprintf(fp, USG_MSG_ARG_OUT_FMT_D4,    FMT_OUT_04);
  fprintf(fp, USG_MSG_ARG_HELP,          SWITCH_CHAR, ARG_HELP);
  fprintf(fp, USG_MSG_ARG_DATE_LOW,      SWITCH_CHAR, ARG_DATE_LOW);
  fprintf(fp, USG_MSG_ARG_DATE_MAX,      SWITCH_CHAR, ARG_DATE_MAX);
  fprintf(fp, USG_MSG_ARG_VERSION,       SWITCH_CHAR, ARG_VERSION);

  exit(EXIT_FAILURE);

} /* show_help() */

/*
 * show_rev()
 */
void show_rev(FILE *fp)

{

  fprintf(fp,"%s %s:\n", PROG_NAME, LIT_REV);
  fprintf(fp,"\t%s\n",   PROG_REV);

#ifdef J_LIB2M_H
  fprintf(fp, "\t%s\n", J_LIB2M_H);
#endif
#ifdef J_LIB2_H
  fprintf(fp, "\t%s\n", J_LIB2_H);
  fprintf(fp, "\t     %s %s\n", LIT_INFO_02, j2_get_build());
#endif

#ifdef OSTYPE
  fprintf(fp,"\t%s\n",OSTYPE);
#endif  /* OSTYPE  */
#ifdef PRETTY_NAME
  fprintf(fp,"\t%s\n",PRETTY_NAME);
#endif  /* OSTYPE  */
  fprintf(fp, LIT_INFO_01, __DATE__, __TIME__);

  exit(EXIT_FAILURE);

}  /* show_rev() */

/*
 * process_arg() -- process arguments
 */
void process_arg(int argc, char **argv, struct s_work *w)

{
  char ckarg[SCKARG];
  int opt;
  int fmt_found = FALSE;
  struct s_j2_datetime d;
  char fmt_low[(FMT_DATE + 1)];
  char fmt_high[(FMT_DATE + 1)];

  memset(fmt_low,  JLIB2_CHAR_NULL, (FMT_DATE + 1));
  memset(fmt_high, JLIB2_CHAR_NULL, (FMT_DATE + 1));

  j2_today(&d);

  w->ofmt      = -1;
  w->date_low  = (char *) NULL;
  w->date_high = (char *) NULL;

  snprintf(ckarg, SCKARG, "%c%c%c:%c:%c:", 
	  ARG_HELP,    ARG_VERSION,
          ARG_OUT_FMT, ARG_DATE_LOW, ARG_DATE_MAX);

  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	case ARG_VERSION:
	  show_rev(stderr);
	  break;
	case ARG_DATE_LOW:
	  if (w->date_low != (char *) NULL)
	    {
	      fprintf(stderr, MSG_ERR_E074, SWITCH_CHAR, ARG_DATE_LOW);
	      fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	      exit(EXIT_FAILURE);
	    }
	    w->date_low = strdup(optarg);
	  break;
	case ARG_DATE_MAX:
	  if (w->date_high != (char *) NULL)
	    {
	      fprintf(stderr, MSG_ERR_E074, SWITCH_CHAR, ARG_DATE_MAX);
	      fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	      exit(EXIT_FAILURE);
	    }
	    w->date_high = strdup(optarg);
	  break;
	case ARG_OUT_FMT:
	  fmt_found = TRUE;
	  if ( w->ofmt != -1)
	    {
	      fprintf(stderr, MSG_ERR_E074, SWITCH_CHAR, ARG_OUT_FMT);
	      fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	      exit(EXIT_FAILURE);
	    }
	  if ( j2_is_numr(optarg) == FALSE)
	    {
	      fprintf(stderr, MSG_ERR_E008, optarg, SWITCH_CHAR, ARG_OUT_FMT);
	      fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	      exit(EXIT_FAILURE);
	    }
	  w->ofmt = atoi(optarg);
	  break;
	case ARG_HELP:
	  show_help(stderr);
	  break;
	default:
	  fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	  exit(EXIT_FAILURE);
	  break;
	}
    }

  if (w->date_low == (char *) NULL)
    {
      snprintf(fmt_low,  FMT_DATE, "%04d%02d%02d", d.yyyy, d.month, d.dd);
      w->date_low  = strdup(fmt_low);
    }
  if (w->date_high == (char *) NULL)
    {
      snprintf(fmt_high, FMT_DATE, "%04d%02d%02d", d.yyyy, d.month, 31);
      w->date_high = strdup(fmt_high);
    }
  verify_date(w->date_low,  ARG_DATE_LOW);
  verify_date(w->date_high, ARG_DATE_MAX);

  if (fmt_found == FALSE)
    w->ofmt = FMT_OUT_00;
  if (w->ofmt < FMT_OUT_00)
    {
      fprintf(stderr, MSG_ERR_E083, SWITCH_CHAR, ARG_OUT_FMT, FMT_OUT_00, FMT_OUT_04, w->ofmt);
      fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }
  if (w->ofmt > FMT_OUT_04)
    {
      fprintf(stderr, MSG_ERR_E083, SWITCH_CHAR, ARG_OUT_FMT, FMT_OUT_00, FMT_OUT_04, w->ofmt);
      fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }

} /* END process_arg() */

/*
 * split_date() -- converted a date formatted as YYYYMMDD
 *                 into the date/time structure
 */
void split_date(struct s_j2_datetime *d, char *fmt)

{

  char *str = (char *) NULL;

  str = strdup(fmt);

  d->dd     = atoi(&(str[6])); str[6] = JLIB2_CHAR_NULL;
  d->month  = atoi(&(str[4])); str[4] = JLIB2_CHAR_NULL;
  d->yyyy   = atoi(str);
  free(str);

  d->hh       =  0;
  d->minutes  =  0;
  d->ss       =  0;
  d->mil      =  0;
  d->tm_isdst =  0;

} /* split_date() */

/*
 * datetol() -- convert datetol to a long
 */
long int datetol(struct s_j2_datetime *d)

{

  char fmt[(FMT_DATE + 1)];

  memset(fmt,  JLIB2_CHAR_NULL, (FMT_DATE + 1));

  snprintf(fmt, FMT_DATE, "%04d%02d%02d", d->yyyy, d->month, d->dd);

  return(atol(fmt));

} /* split_date() */

/*
 * show_date() -- print the date value
 */
void show_date(int fmt, struct s_j2_datetime *d)
{

  switch (fmt)
    {
      case FMT_OUT_01:
	fprintf(stdout,"%04d/%02d/%02d\n", d->yyyy, d->month, d->dd);
	break;
      case FMT_OUT_02:
	fprintf(stdout,"%04d-%02d-%02d\n", d->yyyy, d->month, d->dd);
	break;
      case FMT_OUT_03:
	fprintf(stdout,"%02d/%02d/%04d\n", d->month, d->dd, d->yyyy);
	break;
      case FMT_OUT_04:
	fprintf(stdout,"%02d-%02d-%04d\n", d->dd, d->month, d->yyyy);
	break;
      default:
	fprintf(stdout,"%04d%02d%02d\n", d->yyyy, d->month, d->dd);
	break;
    }

} /* show_date() */

/*
* add_one_day() -- add one day to a date/time structure
*/
void add_one_day(struct s_j2_datetime *now)
{
  int max_days=31;

  if (now->dd < 28)
    {
      now->dd++;
      return;
    }

  switch (now->month)
    {
      case 2:
	if (j2_d_isleap(now->yyyy) == TRUE)
	  max_days=29;
	else
	  max_days=28;
	break;
      case 4:
      case 6:
      case 9:
      case 11:
	max_days=30;
	break;
      default:
	max_days=31;
	break;
    }

  if (now->dd < max_days)
    {
      now->dd++;
      return;
    }

  now->dd = 1;
  if (now->month < 12)
    {
      now->month++;
      return;
    }

  now->month = 1;
  now->yyyy++;

} /* add_one_day() */

/*
 * main()
 */
int main(int argc, char **argv)
{
  struct s_work w;
  struct s_j2_datetime d;
  long int dlow   = 0L;
  long int dhigh  = 0L;

  process_arg(argc, argv, &w);
  split_date(&d, w.date_low);

  dlow  = atol(w.date_low);
  dhigh = atol(w.date_high);

  while (dlow <= dhigh)
    {
      show_date(w.ofmt, &d);
      add_one_day(&d);
      dlow = datetol(&d);
    }

} /* main() */

/* END: add_day.c */
