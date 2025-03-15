#include "ladder.h"
#include <algorithm>
#include <unordered_set>
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg) {
    cerr << word1 << " and " << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int str1_len = str1.length(), str2_len = str2.length();
    if (abs(str1_len - str2_len) > d) return false;

    vector<vector<int>> matrix(str1_len + 1, vector<int>(str2_len + 1));

    for (int i = 0; i <= str1_len; ++i) {
        for (int j = 0; j <= str2_len; ++j) {
            if (i == 0)
                matrix[i][j] = j;  
            else if (j == 0)
                matrix[i][j] = i;

            else if (str1[i - 1] == str2[j - 1])
                matrix[i][j] = matrix[i-1][j-1];

            else
                matrix[i][j] = 1 + min({matrix[i][j-1], matrix[i-1][j] , matrix[i-1][j-1]});
        }
    }
    return matrix[str1_len][str2_len] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

// vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
//     if (begin_word == end_word || word_list.find(end_word) == word_list.end()) return {begin_word};

//     queue<vector<string>> ladder_queue;
//     ladder_queue.push({begin_word});
//     map<string, bool> visited;
//     for (string word: word_list) 
//         visited[word] = false;
//     visited[begin_word] = true;

//     while (!(ladder_queue.empty())) {
//         vector<string> ladder = ladder_queue.front();
//         ladder_queue.pop();
//         string last_word = ladder.back();

//         for (string word : word_list) {
//             if (is_adjacent(last_word, word) && visited[word] == false) {
//                 cout << "DEBUG: " << last_word << " " << word << endl;
//                 visited[word] = true;
//                 vector<string> new_ladder = ladder;
//                 new_ladder.push_back(word);

//                 if (word == end_word) return new_ladder;

//                 ladder_queue.push(new_ladder);
//             }
//         }
//     }
//     return {"No word ladder found."};
// }

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word};
    if (word_list.find(end_word) == word_list.end()) return {};

    queue<pair<string, vector<string>>> q;
    unordered_set<string> visited;  // Set to keep track of visited words
    q.push({begin_word, {begin_word}});
    visited.insert(begin_word);

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        string currentWord = current.first;
        vector<string> path = current.second;

        for (const string& word : word_list) {
            // Check if the word is adjacent and hasn't been visited
            if (is_adjacent(currentWord, word) && visited.find(word) == visited.end()) {
                // If the new word is the end word, return the path
                if (word == end_word) {
                    path.push_back(word);
                    return path;
                }

                // Otherwise, add the new word to the queue and mark it as visited
                vector<string> newPath = path;  // Copy current path
                newPath.push_back(word);  // Add new word to the path
                q.push({word, newPath});
                visited.insert(word);
            }
        }
    }
    return {"No word ladder found."};  // Return an empty list if no path exists
}


void load_words(set<string> & word_list, const string& file_name) {
    std::ifstream file(file_name);
    string line;
    while (getline(file, line))
        word_list.insert(line);
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder[0] == "No word ladder found.") cout << ladder[0];
    else {
        cout << "Word ladder found: ";
        for (string s : ladder) 
            cout << s << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    // my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    // my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
