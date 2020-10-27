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
# include "calculate.h"
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

    cal.map_file_ham_testing(argv[3]);
    cal.map_file_spam_testing(argv[4]);
    cal.posterior_class_probablities();
    
    bool real =cal.classify_message();
    cout<<"THe message is: "<<real;
    // cal.calculate_metric()
    // ifstream myfile(argv[1]);
    // cout<<"Information: "<<argv[1]<<" \n\n";
    // string line;
    // map<string, int> ham_word_count;
    // if (myfile.is_open())
    // {
    //     while (getline(myfile, line))
    //     {
    //         std::vector<string> lineData;
    //         std::stringstream lineStream(line);
    //         string value;
    //         // Read an integer at a time from the line
    //         while (lineStream >> value)
    //         {
    //             // ham_word_count.insert(pair<string, int>(, 40));
    //             if(ham_word_count.count(value) == 0){
    //                 ham_word_count[value] = 1;
    //                 value = "";
    //             }
    //             else{
    //                 ham_word_count[value]++;
    //                 value = "";
    //             }
    //         }
    //     }
    // for(auto elem : ham_word_count)
    // {
    // std::cout << elem.first << " "<< ham_word_count[elem.first]<<"\n";
    // }

    //     myfile.close();
    // }
    // //--------------------------------------------------------------------------
    // ifstream myfile2(argv[2]);
    // cout<<"Information: "<<argv[2]<<" \n\n";
    // string line2;
    // map<string, int> spam_word_count;
    // if (myfile2.is_open())
    // {

    //     while (getline(myfile2, line2))
    //     {
    //         std::vector<string> lineData;
    //         std::stringstream lineStream(line2);
    //         string value;
    //         // Read an integer at a time from the line
    //         while (lineStream >> value)
    //         {   
    //             // ham_word_count.insert(pair<string, int>(, 40));
    //             if(spam_word_count.count(value) == 0){
    //                 spam_word_count[value] = 1;
    //                 value = "";
    //             }
    //             else{
    //                 spam_word_count[value]++;
    //                 value = "";
    //             }
    //         }
    //     }
    // for(auto elem : spam_word_count)
    // {
    // std::cout << elem.first << " "<< spam_word_count[elem.first]<<"\n";
    // }

    //     myfile.close();
    // }

    // ------------------------------------------------------------------
    //Total prior class

    // int n = 2;
    // long double P_ham = ( ham_word_count.size() + k) / ( ham_word_count.size() + spam_word_count.size() +  k * n);
    // long double P_spam = ( spam_word_count.size() + k) / ( ham_word_count.size() + spam_word_count.size() +  k * n);
    // map<string, pair<double, double>> 
    
    // n=ham_word_count.size();
    // for(auto const& x: ham_word_count ){
    //  cout<<" whats up"<<(x.second + k) / ( ham_word_count.size() + k * n);
    // }    

    // n = spam_word_count.size();
    // for(auto const& x: spam_word_count ){
    //  cout<<" whats up"<<(x.second + k) / ( spam_word_count.size() + k * n);
    // }


    return 0;
}
