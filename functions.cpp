//Jefferson Crelia
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "functions.h"

using namespace std;

void get_stream(ifstream& in_s, ofstream& out_s)
{
        char input_file[100], output_file[100]; // declare file variables


        cout << "Please enter the file you would like to read from: "; // get the file name
                cin >> input_file;
                cout << endl;

        in_s.open(input_file); // connecty to the input file and test


        if(in_s.fail())
        {
                cout << "Input file opening failed. \n";
                exit(EXIT_FAILURE); //exit if cannot open file
        }


/*        cout << "Please enter the file you would like to write to: "; // get file name
                cin >> output_file;
                cout << endl;

        out_s.open(output_file); // connect to output file



        if (out_s.fail())
         {
                cout << "Output file opening failed. \n";

                exit(EXIT_FAILURE); // exit if cannot open
        }*/
}


