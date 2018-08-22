/* dialogue formatter -- see readme
 * the executable was compiled with the command:
 * g++ –o format format_dialogue.cpp
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

void set_up(ifstream &fin, ofstream &fout, char *filename);
void format(ifstream &fin, ofstream &fout);
void parse_speaker(ifstream &fin, ofstream &fout, string speaker);
void parse_line(ifstream &fin, ofstream &fout, string speaker);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "usage: ./format [filename.txt]\n";
		return 1;
	}

	ifstream fin;
    ofstream fout;

    set_up(fin, fout, argv[1]);
    format(fin, fout);

    fin.close();
    fout.close();

	return 0;
}

void set_up(ifstream &fin, ofstream &fout, char *filename)
{
    fin.open(filename);   

    if (!fin.is_open())
    {
        cerr << "could not open file\n";
        exit(1);
    }

    //generate output file
    string output = filename;
    output.erase(output.end()-4, output.end());
    output += "_formatted.txt";
    fout.open(output.c_str());
}

void format(ifstream &fin, ofstream &fout)
{
    string curr;

    //format very first line (special case for first speaker)
    fin >> curr;
    while (curr[0] < 65 || (curr[0] > 90 && curr[0] < 97) || curr[0] > 122)
    {
        curr.erase(0, 1);
    }
    fout << "=\n\n";
    parse_speaker(fin, fout, curr);
    parse_line(fin, fout, curr);

    //format rest of document
    while (fin >> curr)
    {
        fout << "=\n\n";

        parse_speaker(fin, fout, curr); //speaker + position + expression
        parse_line(fin, fout, curr);    //speaker's dialogue line

        
    }
}

//assumes first word of each line in the file is "SPEAKERNAME:"
void parse_speaker(ifstream &fin, ofstream &fout, string speaker)
{
    string curr = speaker;

    //check for one word speaker name
    while (curr[curr.length() - 1] != ':')
    {
        fin >> curr;
        speaker += "-" + curr;
    }

    //if midoriya place at front left, else use filler
    if (speaker == "MIDORIYA:")
    {
        fout << "[Midoriya] #front left# |filler_exp| ";
        return;
    }

    //remove colon and convert non-leading chars to lowercase
    speaker.pop_back();
    transform(speaker.begin()+1, speaker.end(), speaker.begin()+1, ::tolower);

    fout << "[" << speaker << "] #filler_pos# |filler_exp| ";
}

void parse_line(ifstream &fin, ofstream &fout, string speaker)
{
    string line;

    //add dialogue line + assume at least 1 secondary char in frame
    if (getline(fin, line))
    {
        //remove extra space at beginning + new line at end
        if (line[0] == ' ')
        {
            line.erase(0, 1);
        }
        if (line[line.length() - 1] == '\n')
        {
            line.pop_back();
        }

        fout << "{ " << line << " }\n"
             << "[filler_char] #filler_pos# |filler_exp|\n\n";
    }
    else
    {
        cerr << "speaker without corresponding dialogue line\n";
        exit(1);
    }
}
