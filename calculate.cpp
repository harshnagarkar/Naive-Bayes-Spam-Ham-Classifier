#include "calculate.h"
using namespace std;

calculate::calculate()
{
    spam_line_count = 0;
    ham_line_count = 0;
}
void calculate::map_file_spam(string filename)
{
    ifstream myfile2(filename);
    string line2;
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
                if (spam_word_count.count(value) == 0)
                {
                    spam_word_count[value] = 1;
                    value = "";
                }
                else
                {
                    spam_word_count[value]++;
                    value = "";
                }
            }
        }
        for (auto elem : spam_word_count)
        {
            std::cout << elem.first << " " << spam_word_count[elem.first] << "\n";
        }
        cout<<"Priot size: "<<spam_word_count.size();

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
                if (spam_word_count.count(value) == 0)
                {
                    spam_testing_count[value] = 1;
                    value = "";
                }
                else
                {
                    spam_word_count[value]++;
                    value = "";
                }
            }
        }
        for (auto elem : spam_word_count)
        {
            std::cout << elem.first << " " << spam_word_count[elem.first] << "\n";
        }

        myfile2.close();
    }
}

void calculate::map_file_ham_testing(string filename)
{
    cout << "loading testing";
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
                if (ham_testing_count.count(value) == 0)
                {
                    ham_testing_count[value] = 1;
                    value = "";
                }
                else
                {
                    ham_testing_count[value]++;
                    value = "";
                }
            }
        }
        for (auto elem : ham_testing_count)
        {
            std::cout << elem.first << " " << elem.second << "\n";
        }

        myfile.close();
    }
}

void calculate::map_file_ham(string filename)
{
    ifstream myfile(filename);
    string line;
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
                if (ham_word_count.count(value) == 0)
                {
                    ham_word_count[value] = 1;
                    value = "";
                }
                else
                {
                    ham_word_count[value]++;
                    value = "";
                }
            }
        }
        // min_Pham = 5000000;
        cout<<"Prior size: "<<ham_word_count.size();
        for (auto elem : ham_word_count)
        {
            std::cout << elem.first << " " << ham_word_count[elem.first] << "\n";
        }

        myfile.close();
    }
}

void calculate::prior_class_probablities(int k, int n)
{
    cout << "\n In the function: \n";
    prior_prob_spam = (1.00 * (spam_line_count + k)) / (ham_line_count + spam_line_count + k * n);
    cout << prior_prob_spam << "\n";
    prior_prob_ham = (1.00 * (ham_line_count + k)) / (ham_line_count + spam_line_count + k * n);
    cout << prior_prob_ham << "\n";
}

int calculate::calculate_distinct(){
    int distinct = 0;
    // for (auto elem : ham_word_count)
    // {
    //     if(spam_word_count.count(elem.first)<=0){
    //         distinct++;
    //     }
    // }
    distinct += ham_word_count.size();
    for (auto elem : spam_word_count)
    {
        if(ham_word_count.count(elem.first)<=0){
            distinct++;
        }
    }
    return distinct;
}

void calculate::conditional_word_probablities(int k)
{
    int n = calculate_distinct();


    // cout<<" ham size: "<<ham_word_count.size();


    min_Pham=50000000000000;
    for (auto elem : ham_word_count)
    {
    // cout<<" conditional word probablity \n";
        // cout<<"elem "<<elem.first<<" "<<elem.second;
        ham_conditional_word_count[elem.first] = (1.0000*(elem.second + k)) / (ham_line_count + k * n);
        // cout<<"conditional "<<ham_conditional_word_count[elem.first];
        if (ham_conditional_word_count[elem.first] < min_Pham)
        {
            min_Pham = ham_conditional_word_count[elem.first];
        }
    }
    cout<<"\n spam conditional "<<spam_word_count.size();
    n = spam_word_count.size();
    for (auto elem : spam_word_count)
    {
        spam_conditional_word_count[elem.first] = (1.000000*(elem.second + k)) / (spam_line_count + k * n);
        if (spam_conditional_word_count[elem.first] < min_Pham)
        {
            min_Pspam = spam_conditional_word_count[elem.first];
        }
    }
}

void calculate::posterior_class_probablities(string testing_filename1, string testing_filename2)
{
    cout<<"\n Posterior \n";
    vector<long double> ham_prob;
    vector<long double> spam_prob;

    // cout<<Plog_ham;
    ifstream myfile(testing_filename1);
    string line;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line);
            string value;
            Plog_ham = log2l(prior_prob_ham);
            Plog_spam = log2l(prior_prob_spam);
            // Read an integer at a time from the line
            while (lineStream >> value)
            {
                if (ham_conditional_word_count.count(value)!=0)
                {
                    // cout<<"Spam word: "<<spam_conditional_word_count[value];
                    Plog_ham += log2l(ham_conditional_word_count[value]);
                    Plog_spam += log2l(spam_conditional_word_count[value]);
                    // cout<<Plog_spam<<" value \n";
                    // cout<<" added "<< log2l(ham_conditional_word_count[value]);
                }else{
                    Plog_ham += min_Pham;
                    Plog_spam += min_Pspam;
                    // cout<<" added min "<<min_Pham;
                }
            }
            cout<<"\n Main value "<<Plog_ham<<" "<<Plog_spam<<"\n";
            
        }
    }
    myfile.close();
    
    ifstream myfile2(testing_filename2);
    string line2;
    if (myfile2.is_open())
    {
        while (getline(myfile2, line2))
        {
            std::vector<string> lineData;
            std::stringstream lineStream(line2);
            string value;
            Plog_spam = log2l(prior_prob_spam);
            cout<<Plog_spam<<" rot";
            // Read an integer at a time from the line
            while (lineStream >> value)
            {
                if (spam_conditional_word_count.count(value)!=0)
                {
                    Plog_spam += log2l(spam_conditional_word_count[value]);
                    cout<<spam_conditional_word_count[value]<<" t \n";
                }else{
                    Plog_spam+=min_Pspam;
                }
            }
            cout<<"Spam value: "<<Plog_spam;
            
        }
    }
    myfile2.close();
    // Plog_spam = log2l(prior_prob_ham);
    // for (auto elem : spam_conditional_word_count)
    // {
    //     Plog_spam += log2l(spam_conditional_word_count[elem.second]);
    // }
    cout << "Posterior probablities: " << Plog_spam << " " << Plog_ham;
}
bool calculate::classify_message()
{
    if (Plog_ham > Plog_spam)
    {
        return true;
    }
    else
    {
        return false;
    }
};
// void calculate_metric();
