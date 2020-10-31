#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h> /* printf, fgets */
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include <map>
#include <iterator> 
#include <algorithm>
#include "calculate.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: not enough arguments");
        exit(0);
    }
    int arg_len = (int) argc;
    int k = atoi(argv[arg_len-1]);

    calculate cal = calculate();
    cal.map_file_ham(argv[1]);
    cal.map_file_spam(argv[2]);

    cal.prior_class_probablities(k,2);
    cal.conditional_word_probablities(k);

    // cal.map_file_ham_testing(argv[3]);
    // cal.map_file_spam_testing(argv[4]);
    cal.posterior_class_probablities(argv[3],argv[4]);
    //after caulcation
    cal.print_metric();

    return 0;
}
