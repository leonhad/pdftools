/*
 * This code is a modification of the Free Software Foundation, Inc.
 * Getopt library for parsing command line argument the purpose was
 * to provide a Microsoft Visual C friendly derivative. This code
 * provides functionality for both Unicode and Multibyte builds.
 */
#ifndef __GETOPT_H_
#define __GETOPT_H_

	#if defined(EXPORTS_GETOPT)
		#pragma message("Exporting getopt library")
		#define _GETOPT_API __declspec(dllexport)
	#else
		#pragma message("Importing getopt library")
		#define _GETOPT_API __declspec(dllimport)
	#endif

	// Standard GNU options
	#define	null_argument		0	/*Argument Null*/
	#define	no_argument			0	/*Argument Switch Only*/
	#define required_argument	1	/*Argument Required*/
	#define optional_argument	2	/*Argument Optional*/	

	// Shorter Options
	#define ARG_NULL	0	/*Argument Null*/
	#define ARG_NONE	0	/*Argument Switch Only*/
	#define ARG_REQ		1	/*Argument Required*/
	#define ARG_OPT		2	/*Argument Optional*/

	#include <string.h>

	extern _GETOPT_API int optind;
	extern _GETOPT_API int opterr;
	extern _GETOPT_API int optopt;

	// Ansi
	struct option
	{
		const char* name;
		int has_arg;
		int *flag;
		int val;
	};

	extern _GETOPT_API char *optarg;
	extern _GETOPT_API int getopt(int argc, char *const *argv, const char *optstring);
	extern _GETOPT_API int getopt_long(int argc, char *const *argv, const char *options, const struct option *long_options, int *opt_index) ;
	extern _GETOPT_API int getopt_long_only(int argc, char *const *argv, const char *options, const struct option *long_options, int *opt_index) ;

#endif
