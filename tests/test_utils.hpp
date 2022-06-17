#ifndef _TEST_UTILS_
#define _TEST_UTILS_

#include <ctime>
#include <iostream>

/* colors */
#define NC "\x1B[0m"
#define COL_RED "\x1B[0;31m"
#define COL_GRN "\x1B[0;32m"
#define COL_CYN "\x1B[0;36m"
#define COL_YEL "\x1B[0;33m"
#define COL_REDB "\x1B[41m"

extern const long   COUNT;

enum Command{
	ALL,
	PAIR,
	LEX,
	INT,
	VEC,
	STACK,
	MAP,
	SET
};

void    	handle_args(int argc, char** argv);
void    	init_cout();
double  	timer_stop();
void    	timer_start();
void    	print_result(double std, double ft);
void    	print_test_name(long count);
void    	print_comp_res(int err_count, double comp_res);
std::string getNewId();

#endif
