#include "calculate.h"
using namespace std;

calculate::calculate()
{
    spam_line_count=0;
    ham_line_count=0;
}
void calculate::map_file_spam(string filename)
{
    ifstream myfile2(filename);
    string line2;
    // map<string, int> spam_word_count;
    if (myfile2.is_open())
    {

        while (getline(myfile2, line2))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line2);
            string value;
            spam_line_count++;
            // Read an integer at a time from the line
            while (lineStream >> value)
            {   
                // ham_word_count.insert(pair<string, int>(, 40));
                if(spam_word_count.count(value) == 0){
                    spam_word_count[value] = 1;
                    value = "";
                }
                else{
                    spam_word_count[value]++;
                    value = "";
                }
            }
        }
    for(auto elem : spam_word_count)
    {
    std::cout << elem.first << " "<< spam_word_count[elem.first]<<"\n";
    }

        myfile2.close();
    }

}

void calculate::map_file_spam_testing(string filename)
{
    ifstream myfile2(filename);
    string line2;
    // map<string, int> spam_word_count;
    if (myfile2.is_open())
    {

        while (getline(myfile2, line2))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line2);
            string value;
        spam_testing_line_count++;
            // Read an integer at a time from the line
            while (lineStream >> value)
            {   
                // ham_word_count.insert(pair<string, int>(, 40));
                if(spam_word_count.count(value) == 0){
                    spam_testing_count[value] = 1;
                    value = "";
                }
                else{
                    spam_word_count[value]++;
                    value = "";
                }
            }
        }
    for(auto elem : spam_word_count)
    {
    std::cout << elem.first << " "<< spam_word_count[elem.first]<<"\n";
    }

        myfile2.close();
    }

}

void calculate::map_file_ham_testing(string filename){
    cout<<"loading testing";
    ifstream myfile(filename);
    string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line);
            string value;
            ham_testing_line_count++;
            // Read an integer at a time from the line
            while (lineStream >> value)
            {
                // ham_word_count.insert(pair<string, int>(, 40));
                if(ham_testing_count.count(value) == 0){
                    ham_testing_count[value] = 1;
                    value = "";
                }
                else{
                    ham_testing_count[value]++;
                    value = "";
                }
            }
        }
    for(auto elem : ham_testing_count)
    {
    std::cout << elem.first << " "<< elem.second<<"\n";
    }

        myfile.close();
    }
}

void calculate::map_file_ham(string filename){
    ifstream myfile(filename);
    string line;
    map<string, int> ham_word_count;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line);
            string value;
            ham_line_count++;
            // Read an integer at a time from the line
            while (lineStream >> value)
            {
                // ham_word_count.insert(pair<string, int>(, 40));
                if(ham_word_count.count(value) == 0){
                    ham_word_count[value] = 1;
                    value = "";
                }
                else{
                    ham_word_count[value]++;
                    value = "";
                }
            }
        }
    for(auto elem : ham_word_count)
    {
    std::cout << elem.first << " "<< ham_word_count[elem.first]<<"\n";
    }

        myfile.close();
    }
}


void calculate::prior_class_probablities(int k, int n){
    cout<<"\n In the function: \n";
    prior_prob_spam = 1.00*(spam_line_count + k) / ( ham_line_count + spam_line_count + k*n);
    cout<<prior_prob_spam<<"\n";
    prior_prob_ham = 1.00*(ham_line_count + k) / ( ham_line_count + spam_line_count + k*n);
    cout<<prior_prob_ham<<"\n";
}

void calculate::conditional_word_probablities(int k){
    int n = ham_word_count.size();
    for(auto elem : ham_word_count)
    {
    ham_conditional_word_count[elem.first] = ( elem.second + k ) / ( ham_line_count + k * n);
    }
    n = spam_word_count.size();
    for(auto elem : spam_word_count)
    {
    spam_conditional_word_count[elem.first] = ( elem.second + k ) / ( spam_line_count + k * n);
    }
}


void calculate::posterior_class_probablities(){
    Plog_ham = log2l(prior_prob_spam); 
    for(auto elem : ham_conditional_word_count)
    {
    Plog_ham += log2l(elem.second);
    }

    Plog_spam = log2l(prior_prob_ham);
    for(auto elem : spam_conditional_word_count)
    {
    Plog_spam += log2l(elem.second);
    }
    cout<<"Posterior probablities: "<<Plog_spam<<" "<<Plog_ham;

}
bool calculate::classify_message(){
    if(Plog_ham>Plog_spam){
        return true;
    }else{
        return false;
    }
};
// void calculate_metric();
