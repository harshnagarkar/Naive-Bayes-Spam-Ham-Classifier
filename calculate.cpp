#include "calculate.h"
using namespace std;

calculate::calculate()
{
    spam_line_count = 0;
    ham_line_count = 0;
    TPos=0.0000;
    FNeg=0.0000;
    TNeg=0.0000;
    FPos=0.0000;
    total_words=0;
    total_ham=0;
    total_spam=0;
}
void calculate::map_file_spam(string filename)
{
    ifstream myfile2(filename);
    string line2;
    // int count=0;
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
                total_spam++;
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
        // for (auto elem : spam_word_count)
        // {
        //     std::cout << elem.first << " " << spam_word_count[elem.first] << "\n";
        // }
        // cout << "Priot size: " << spam_word_count.size();

        myfile2.close();
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
                total_ham++;
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
        // cout << "Prior size: " << ham_word_count.size();
        // for (auto elem : ham_word_count)
        // {
        //     std::cout << elem.first << " " << ham_word_count[elem.first] << "\n";
        // }

        myfile.close();
    }
}

void calculate::prior_class_probablities(int k, int n)
{
    // cout << "\n Prior class: \n";
    prior_prob_spam = (1.00 * (spam_line_count + k)) / (ham_line_count + spam_line_count + k * n);
    // cout << prior_prob_spam << "\n";
    prior_prob_ham = (1.00 * (ham_line_count + k)) / (ham_line_count + spam_line_count + k * n);
    // cout << prior_prob_ham << "\n";
}

int calculate::calculate_distinct()
{
    int distinct = 0;
    // distinct += ham_word_count.size();
    // cout<<"before size "<<distinct_dictionary.size();
    for(auto elem: ham_word_count){
        if(find(distinct_dictionary.begin(),distinct_dictionary.end(),elem.first)==distinct_dictionary.end()){
        distinct++;
        distinct_dictionary.push_back(elem.first);
        // cout<<elem.first<<" ";
        }
    }
    // cout<<" current distinct"<<distinct_dictionary.size();
    for (auto elem : spam_word_count)
    {
        if (find(distinct_dictionary.begin(),distinct_dictionary.end(),elem.first)==distinct_dictionary.end())
        {
            distinct++;
            distinct_dictionary.push_back(elem.first);
            // cout<<elem.first<<" ";
        }
    }
    // cout<<"distinct "<<distinct_dictionary.size();
    return distinct;
}

void calculate::conditional_word_probablities(int k)
{
    int n = calculate_distinct();

    // cout<<" ham size: "<<ham_word_count.size();

    min_Pham = (1.0000*k)/(total_ham+k*n);
    min_Pspam = (1.0000*k)/(total_spam+k*n);
    for (auto elem: distinct_dictionary)
    {
        // cout<<"\n "<<total_ham<<" "<<total_spam<<"\n";
        pair<double,double> data;
        if(ham_word_count.count(elem)!=0){
            data.first=(1.0000 * (ham_word_count[elem] + k)) / (total_ham + k * n);
        }else{
            data.first=min_Pham;
        }

        if(spam_word_count.count(elem)!=0){
            data.second=(1.000000 * (spam_word_count[elem] + k)) / (total_spam + k * n); //spam
        }else{
            data.second=min_Pspam;
        }
 //ham
        conditional_dictionary[elem]=data;
    }
    

}

void calculate::posterior_class_probablities(string testing_filename1, string testing_filename2)
{
    // cout << "\n Posterior \n";
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
            Plog_ham = log(prior_prob_ham);
            Plog_spam = log(prior_prob_spam);
            total_words++;
            // Read an integer at a time from the line
            while (lineStream >> value)
            {

                    // cout<<"Spam word: "<<spam_conditional_word_count[value];
                    Plog_ham += log(conditional_dictionary[value].first);
                    // cout<<Plog_spam<<" value \n";
                    // cout<<" added "<< log2l(ham_conditional_word_count[value]);

                    Plog_spam += log(conditional_dictionary[value].second);
                    // cout<<spam_conditional_word_count[value]<<" t \n";
                
            }
            // cout << "\n Main value " << Plog_ham << " " << Plog_spam << "\n";
            string class_choosen=classify_message();
            cout<< classify_message() <<" "<<Plog_ham<<" "<<Plog_spam<<"\n";
            calculate_metric(class_choosen,"ham");
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
            Plog_spam = log(prior_prob_spam);
            Plog_ham = log(prior_prob_ham);
            total_words++;
            // cout<<min_Pham<<" rot "<<min_Pspam;


            // Read an integer at a time from the line
            while (lineStream >> value)
            {
                    Plog_spam += log(conditional_dictionary[value].second);
                    // cout<<spam_conditional_word_count[value]<<" t \n";
                    Plog_ham += log(conditional_dictionary[value].first);

            }
            // cout << "\n Main value " << Plog_ham << " " << Plog_spam << "\n";

            string class_choosen=classify_message();
            cout<< class_choosen <<" "<<Plog_ham<<" "<<Plog_spam<<"\n";
            Plog_spam=0;
            Plog_ham=0;
            calculate_metric(class_choosen,"spam");
        }
    }
    myfile2.close();
    // Plog_spam = log2l(prior_prob_ham);
    // for (auto elem : spam_conditional_word_count)
    // {
    //     Plog_spam += log2l(spam_conditional_word_count[elem.second]);
    // }
    // cout << classify_message() << Plog_spam << " " << Plog_ham;
}



string calculate::classify_message()
{
    if (Plog_ham > Plog_spam)
    {
        return "ham";
    }
    else
    {
        return "spam";
    }
}


void calculate::calculate_metric(string given, string actual){
    if(actual=="ham" && given=="ham"){
        TPos++;
    }else if(actual=="ham" && given=="spam"){
        FNeg++;
    }else if(actual=="spam" && given=="ham"){
        FPos++;
    }else if(actual=="spam" && given=="spam"){
        TNeg++;
    }
}

void calculate::print_metric(){
    // cout<<"\n"<<TNeg<<" "<<FPos<<" "<<TPos<<" "<<FNeg<<"\n\n";
    // cout<<"test"<< (TNeg/(TNeg+FPos));
    cout<<(long double)(TNeg/(TNeg+FPos))<<" ";
    cout<<(long double)(TPos/(TPos+FNeg))<<" ";
    cout<<(long double)(TPos+TNeg+(0.000))/(total_words);
    // cout<<"\n";

}
