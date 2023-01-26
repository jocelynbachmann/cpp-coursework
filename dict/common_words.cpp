/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::cout;
using std::endl;
using std::feof;
using std::ifstream;
using std::string;
using std::vector;

string remove_punct(const string &str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c)
                        { return std::ispunct(c); });
    return ret;
}

CommonWords::CommonWords(const vector<string> &filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string> &filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++)
    {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);

        // go through all the words in the file
        /* Your code goes here! */
        for (string word : words)
        {
            auto lookup = file_word_maps[i].find(word);

            if (lookup == file_word_maps[i].end())
                file_word_maps[i][word] = 0;
            file_word_maps[i][word]++;
        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here!  */
    // iterate over list of files
    for (auto map : file_word_maps)
    {
        // iterate over words
        for (auto pair : map)
        {
            if (common.find(pair.first) == common.end())
                common[pair.first] = 0;
            common[pair.first]++;
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    // if a word appears in every file it must be in the file with the least number of unique words
    // so we only consider every word in that file
    // saving time on the number of words checked
    auto min_map = file_word_maps[0];

    for (auto &m : file_word_maps)
    {
        if (m.size() < min_map.size())
        {
            min_map = m;
        }
    }

    for (auto &kv : min_map)
    {
        // if appears in min_map at least n times
        // then we check rest of the maps
        if (kv.second >= n)
        {
            bool n_in_every_file = true;

            for (map<string, unsigned int> m : file_word_maps)
            {
                if (m[kv.first] < n)
                {
                    n_in_every_file = false;
                    break;
                }
            }

            if (n_in_every_file)
                out.push_back(kv.first);
        }
    }

    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string &filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open())
    {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof())
        {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
