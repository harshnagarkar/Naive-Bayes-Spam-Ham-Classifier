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
using namespace std;

class calculate{
    map<string, int> spam_word_count;
    map<string, int> ham_word_count;
    map<string, int> spam_conditional_word_count;
    map<string, int> ham_conditional_word_count;
    map<string, int> spam_testing_count;
    int spam_testing_line_count;
    map<string, int> ham_testing_count;
    int ham_testing_line_count;
    int spam_line_count;
    int ham_line_count;
    int k, n;
    long double prior_prob_spam;
    long double prior_prob_ham;
    long double Plog_ham;
    long double Plog_spam;

    public:
    calculate();
    void map_file_spam(string filename);
    void map_file_ham(string filename);
    void map_file_ham_testing(string filename);
    void map_file_spam_testing(string filename);
    void prior_class_probablities(int k, int n);
    void conditional_word_probablities(int k);
    void posterior_class_probablities();
    bool classify_message();
    void calculate_metric();
};