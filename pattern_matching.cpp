#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

//t stands for the whole string
//p stands for the desired pattern
//this was the notation during the classes so I will continue using it

void brute_force(string, string);
string txt_to_string(string);

int main()
{
    using clock = chrono::steady_clock;
    using ns = chrono::nanoseconds;
    int times = 1000;
    ns total_time_taken = ns(0);

    string text = txt_to_string("1984.txt");
    string small_pattern = "IGNORANCE IS STRENGTH";
    string large_pattern = "It was a bright cold day in April, and the clocks were striking thirteen.\nWinston Smith, his chin nuzzled into his breast in an effort to escape the\nvile wind, slipped quickly through the glass doors of Victory Mansions,\nthough not quickly enough to prevent a swirl of gritty dust from entering\nalong with him.";
    
    for (int i = 0; i < times; ++i)
    {
        auto start = clock::now();
        //brute_force(text, small_pattern);
        brute_force(text, large_pattern);
        auto end = clock::now();
        total_time_taken += chrono::duration_cast<ns>(end - start);
    }

    cout << "Brute force: " << total_time_taken.count() / times << "ns\n";
}

void brute_force(string t, string p)
{
    size_t t_size = t.size();
    size_t p_size = p.size();
    bool found;

    for (int i = 0; i <= t_size - p_size; ++i)
    {
        found = true;

        for (int j = 0; j < p_size; ++j)
        {
            if (t[i + j] != p[j])
            {
                found = false;  
                break;
            }
        }
        
        if (found)
        {
            //cout << "Pattern found!\n";
        }
    }
}

string txt_to_string(string filename)
{
    string tmp;
    string file_text;
    ifstream file_in;

    file_in.open(filename);
    while (getline(file_in, tmp))
    {
        file_text += tmp += '\n';
    }
    file_in.close();
    
    return file_text;
}