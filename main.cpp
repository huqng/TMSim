#include "TM.h"

#include <unistd.h>
#include <getopt.h>

#include <iostream>
using namespace std;

int start(bool verbose, string filename, string input) {
	TM* tm = new TM(filename, verbose);
	tm->run(input, verbose);
	return 0;
}

void help(){
	cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
}

int main(int argc, char* argv[]) {

	const option long_options[] = {				// long-options
		{"help", no_argument, NULL, 'h'},
		{"verbose", no_argument, NULL, 'v'},
		{0, 0, 0, 0}
	};							// tmp
	char ch;						// tmp
	int longind;						// tmp
	int argid = 0;						// tmp
	bool verbose_flag = false;				// if --verbose or -v

	while((ch = getopt_long(argc, argv, "vh", long_options, &longind))!=-1) {
		if (ch == 'v') 					// --verbose or -v
			verbose_flag = true;
		else if (ch == 'h') { 				// --help or -h
			help();
			exit(-1);
		}
		else {}
		argid++;					
	}

	if(argid >= argc - 2) {					// if no <tm> & <input>
		help();
		exit(-1);
	}

	start(verbose_flag, argv[argid + 1], argv[argid + 2]);					// here we go

	return 0;
}