#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Class that reads data from tab seperated values (a   b   c   )
class CSV
{
    // class member of input stream
    ifstream in_file;
public:
    // data is stored as a vector of vectors of string
    vector< vector<string> > data;

    // Constructor
    CSV(string ip)
    {
        in_file.open(ip);
        this->make_vector();
    }

    // Copying the data properly from the tsv to vector
    void make_vector()
    {
        string line;
        while(getline(in_file, line))
        {
            stringstream ss(line);
            string s;
            vector<string> v;
            while(ss >> s)
                v.push_back(s);
            data.push_back(v);
        }
    }

    // If needed we can print the loaded data in a neat manner with this method
    void print_data()
    {
        for(auto&e:data)
        {
            for(auto&f:e)
                cout << f << '\t';
        }
        cout << '\n';
    }
    ~CSV(){}
};