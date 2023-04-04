#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;

//t stands for the whole string
//p stands for the desired pattern
//this was the notation during the classes so I will continue using it

void brute_force(string, string);
void sunday(string, string);
string txt_to_string(string);

int main()
{
    using clock = chrono::steady_clock;
    using ns = chrono::nanoseconds;
    int times = 100000;
    ns total_time_taken = ns(0);

    string test_t = "12341235612123236123";
    string test_p = "123";
    string text = txt_to_string("1984.txt");
    string small_pattern = "IGNORANCE IS STRENGTH";
    string large_pattern = "It was a bright cold day in April, and the clocks were striking thirteen.\nWinston Smith, his chin nuzzled into his breast in an effort to escape the\nvile wind, slipped quickly through the glass doors of Victory Mansions,\nthough not quickly enough to prevent a swirl of gritty dust from entering\nalong with him.";
    
    for (size_t i = 0; i < times; ++i)
    {
        auto start = clock::now();
        brute_force(text, large_pattern);
        auto end = clock::now();
        total_time_taken += chrono::duration_cast<ns>(end - start);
    }

    cout << "Brute force: " << total_time_taken.count() / times << "ns\n";
    total_time_taken = ns(0);

    for (size_t i = 0; i < times; ++i)
    {
        auto start = clock::now();
        sunday(text, large_pattern);
        auto end = clock::now();
        total_time_taken += chrono::duration_cast<ns>(end - start);
    }

    cout << "Sunday: " << total_time_taken.count() / times << "ns\n";
}

void brute_force(string t, string p)
{
    size_t t_size = t.size();
    size_t p_size = p.size();
    bool found;

    for (size_t i = 0; i <= t_size - p_size; ++i)
    {
        found = true;

        for (size_t j = 0; j < p_size; ++j)
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

void sunday(string t, string p)
{
    size_t t_size = t.size();
    size_t p_size = p.size();

    vector<int> positions(256, -1);

    for (int i = 0; i < p_size; ++i)
    {
        positions[p[i]] = i;
    }

    size_t t_index = 0;
    while (t_index <= t_size - p_size)
    {
        size_t p_index = p_size - 1;

        while (p_index >= 0 && p[p_index] == t[t_index + p_index])
        {
            --p_index;
        }

        if (p_index < 0)
        {
            //cout << "Pattern found!" << endl;

            if (t_index + p_size < t_size)
            {
                t_index += p_size - positions[t[t_index + p_size]];
            }
            else
            {
                ++t_index;
            }
        }
        else
        {
            int shift = p_index - positions[t[t_index + p_index]];

            if (shift > 0)
            {
                t_index += shift;
            }
            else
            {
                ++t_index;
            }
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