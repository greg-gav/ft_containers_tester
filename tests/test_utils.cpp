#include "test_utils.hpp"

const long      COUNT = 100000;
const int	    pres_num = 5;
std::string     test_name;
std::clock_t    start;
double          duration;
Command  comm;

void handle_args(int argc, char** argv){
	std::cout << "Usage: [pair][lex][int][vec][stack][map][set]" << std::endl;
	if (argc == 2){
		std::string command = argv[1];
		if (command == "pair")	comm = PAIR;
		if (command == "lex")	comm = LEX;
		if (command == "int")	comm = INT;
		if (command == "vec")	comm = VEC;
		if (command == "stack")	comm = STACK;
		if (command == "map")	comm = MAP;
		if (command == "set")	comm = SET;
	}
}

void init_cout(){
	std::cout.precision(pres_num);
	std::cout << std::fixed;
}

double timer_stop(){
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	start = 0;
	return duration;
}

void timer_start(){
	start = std::clock();
}

void print_result(double std, double ft){
	std::cout.precision(2);
	double delta = std / ft;
    std::string col;
    if (delta >= 1)
        col = COL_GRN;
    if (delta < 0.5)
        col = COL_YEL;
    if (delta < 0.05)
        col = COL_RED;
	std::cout << "performance: "<< col << "x" << delta << NC << " (1 is equal, higher is better)" << std::endl;
	std::cout.precision(pres_num);
}

void print_test_name(long count){
	std::cout << COL_YEL << test_name << NC << " x" << count / COUNT << " of 100k iterations" << std::endl;
}

void print_comp_res(int err_count, double comp_res){
    std::string col = COL_GRN;
    if (err_count > 0)
        col = COL_RED;
    std::cout << "Output comparison results (std vs ft): " << col <<
		err_count << " errors" << NC << " in " << comp_res << " sec" << std::endl;

}

std::string getNewId(){
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    int len = 20;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}
