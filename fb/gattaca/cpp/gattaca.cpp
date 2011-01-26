#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

void profit(const vector< vector<int> > &predicts, vector<int> &profits)
{
	vector<int> comp(predicts.size(), -1);
	int incl, excl;
	
	for (uint i = 0; i < predicts.size(); ++i) {
		int start = predicts[i][0];
		
		for (int j = i - 1; j >= 0; --j) {
			int finish = predicts[j][1];
			if (finish < start) {
				comp[i] = j;
				break;
			}
		}
	}
	
	profits[0] = 0;
	for (uint i = 1; i < profits.size(); ++i) {
		incl = predicts[i-1][2] + profits[comp[i-1]+1];
		excl = profits[i-1];
		profits[i] = (incl > excl) ? incl : excl;
	}
}

bool sort_predicts(const vector<int> &lhs, const vector<int> &rhs) 
{
	return lhs[1] < rhs[1];
}

bool read_input(const char *file_name, vector< vector<int> > &predicts)
{
	ifstream in_file(file_name);
    istringstream iss;
    string file_line;
    int dna_len, total_predicts;
    vector<int> predict(3, 0);
    
    if (!in_file) {
        cerr << "Cannot open " << file_name << endl;
        return false;
    }
    
    if (!getline(in_file, file_line).eof()) {
        iss.clear();
        iss.str(file_line);
        
        iss >> dna_len;
#ifdef DEBUG
        cout << dna_len << endl;
#endif        
    }
    
    while (dna_len > 0 && !getline(in_file, file_line).eof()) {
        if (file_line.size() > 80) {
			dna_len -= 80;
		} else {
			dna_len -= file_line.size();
		}
	}
	
	if (!getline(in_file, file_line).eof()) {
        iss.clear();
        iss.str(file_line);
        
        iss >> total_predicts;
#ifdef DEBUG
        cout << total_predicts << endl;
#endif        
    }
    
    //predicts.resize(total_predicts);
    
    while (total_predicts > 0 && !getline(in_file, file_line).eof()) {
		iss.clear();
        iss.str(file_line);
        
        iss >> predict[0] >> predict[1] >> predict[2];
        predicts.push_back(predict);
        --total_predicts;
	}
    
    return true;
}

int main(int argc, char *argv[]) 
{
	vector< vector<int> > predicts;
	vector<int> profits;
	
	if (argc != 2) {
        return 1;
    }
	//cout << "Start reading..." << endl;
	if (!read_input(argv[1], predicts)) {
		return 1;
	}
	//cout << "Stop reading" << endl;

#ifdef DEBUG
	cout << "Predicts (unsorted):" << endl;
	for (uint i = 0; i < predicts.size(); ++i) {
		cout << predicts[i][0] << " " << predicts[i][1] << " " << predicts[i][2] << endl;
	}
#endif
	
	if (predicts.size() <= 0) {
		return 1;
	}
	profits.resize(predicts.size() + 1, 0);
	
	//cout << "Start sorting..." << endl;
	sort(predicts.begin(), predicts.end(), sort_predicts);
	//cout << "Stop sorting" << endl;

#ifdef DEBUG	
	cout << endl << "Predicts (sorted):" << endl;
	for (uint i = 0; i < predicts.size(); ++i) {
		cout << predicts[i][0] << " " << predicts[i][1] << " " << predicts[i][2] << endl;
	}
#endif
	
	profit(predicts, profits);
	
	cout << profits[predicts.size()] << endl;
	
	return 0;
	
}
