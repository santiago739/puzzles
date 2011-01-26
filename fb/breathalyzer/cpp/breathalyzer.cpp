#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <string.h>
#include <stdio.h>

using namespace std;

#define MAXLEN          31

#define MATCH           0       
#define INSERT          1       
#define DELETE          2 

#define COST_DELETE     1
#define COST_INSERT     1
#define COST_SUSTITUTE  1
#define COST_MATCH      0

#define DICT_PATH		"/var/tmp/twl06.txt"

typedef unsigned int uint;

int m[MAXLEN+1][MAXLEN+1];

int string_compare(const char *s, const char *t)
{
    uint i, j, k;
    int opt[3], cost_match;;

    for (i = 0; i < MAXLEN; i++) {
		m[0][i] = i;
		m[i][0] = i;
    }

    for (i = 1; i < strlen(s); i++) {
        for (j = 1; j < strlen(t); j++) {
			cost_match = (s[i] == t[j]) ? COST_MATCH : COST_SUSTITUTE;
            opt[MATCH]  = m[i-1][j-1] + cost_match;
            opt[INSERT] = m[i][j-1] + COST_INSERT;
            opt[DELETE] = m[i-1][j] + COST_DELETE;

            m[i][j] = opt[MATCH];
            for (k = INSERT; k <= DELETE; k++) {
                if (opt[k] < m[i][j]) {
                    m[i][j] = opt[k];
                }
            }
        }
    }
	
	i = strlen(s) - 1;
    j = strlen(t) - 1;
	
    return m[i][j];
} 

void print_matrix(const char *s, const char *t)
{
	int i,j;			
	int x,y;			

	x = strlen(s);
	y = strlen(t);

	printf("   ");
	for (i = 0; i < y; i++) {
		printf("  %c", t[i]);
    }
	printf("\n");

	for (i = 0; i < x; i++) {
		printf("%c: ", s[i]);
		for (j = 0; j < y; j++) {
			printf(" %2d", m[i][j]);
			
		}
		printf("\n");
	}
}

bool read_dict(const string &file_name, vector<string> &dict)
{
    ifstream in_file(file_name.c_str());
    istringstream iss;
    string file_line, word;
    
    if (!in_file) {
        cerr << "Cannot open " << file_name << endl;
        return false;
    }

    while (!getline(in_file, file_line).eof()) {
        iss.clear();
        iss.str(file_line);
        if (iss >> word) {
            dict.push_back(" " + word);
        }
    }
    
    return true;
}

bool read_words(const string &file_name, vector<string> &words)
{
    ifstream in_file(file_name.c_str());
    istringstream iss;
    string file_line, word;
    
    if (!in_file) {
        cerr << "Cannot open " << file_name << endl;
        return false;
    }

    while (!getline(in_file, file_line).eof()) {
        iss.clear();
        iss.str(file_line);
        
        while (iss >> word) { 
            std::transform(word.begin( ), word.end( ), word.begin( ), ::toupper);
            words.push_back(" " + word);
        }
    }
    
    return true;
}

int main(int argc, char *argv[]) {
    const char *p_word, *p_dict;
    int cost, min_cost, total_cost = 0, i;
    vector<string> dict;
    vector<string> words;
    vector<string>::iterator it_words, it_dict, it_begin;
    string s_dict, s_word;
    map<char,int> chars_map;
    map<char,int>::iterator it_map;
    char ch;
    bool word_ready;
    
    if (argc != 2) {
        return 0;
    }
    
    if (!read_words(argv[1], words)) {
        return 1;
    }
    
    if (!read_dict(DICT_PATH, dict)) {
        return 1;
    }
    
    sort(dict.begin(), dict.end());
    
    
    for (i = 0, it_dict = dict.begin(); it_dict != dict.end( ); ++i, ++it_dict) {
		p_dict = (*it_dict).c_str();
		ch = p_dict[1];
		if (chars_map.find(ch) == chars_map.end()) {
			chars_map[ch] = i;
		} 
	}
	
	//for ( it_map = chars_map.begin() ; it_map != chars_map.end(); it_map++) {
		//cout << (*it_map).first << " => " << (*it_map).second << endl;
	//}
	
    for (it_words = words.begin(); it_words != words.end(); ++it_words) {
        min_cost = -1;
        s_word = *it_words;
        p_word = (*it_words).c_str();
        word_ready = false;
        
        // check if words exists in dict
        if (binary_search(dict.begin(), dict.end(), s_word)) {
            continue;
        }
        
        // find initial position for process start
        ch = p_word[1];
        it_map = chars_map.find(ch);
        if (it_map == chars_map.end()) {
			it_begin = dict.begin();
		} else {
			it_begin = dict.begin() + it_map->second;
		}
        
        //for (it_dict = dict.begin(); it_dict != dict.end(); ++it_dict) {
        for (it_dict = it_begin; it_dict != dict.end(); ++it_dict) {
            p_dict = (*it_dict).c_str();
            cost = string_compare(p_word, p_dict);
            if (min_cost == -1 || cost < min_cost) {
                min_cost = cost;
                s_dict = *it_dict;
            }
            if (min_cost == 1) {
				word_ready = true;
                break;
            }
        }
        
        if (word_ready == false && it_begin != dict.begin()) {
			for (it_dict = dict.begin(); it_dict != (it_begin + 1); ++it_dict) {
				p_dict = (*it_dict).c_str();
				cost = string_compare(p_word, p_dict);
				if (min_cost == -1 || cost < min_cost) {
					min_cost = cost;
					s_dict = *it_dict;
				}
				if (min_cost == 1) {
					word_ready = true;
					break;
				}
			}
		}
        
        //cout << s_word << " -> " << s_dict << " cost: " << min_cost << endl;
        
        if (min_cost > 0) {
            total_cost += min_cost;
        }
    }
	cout << total_cost << endl;

    return 0;
}
