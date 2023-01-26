/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 */

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string &infile)
    : dict(256), filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold)
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    // /**
    //  * @todo Implement this function.
    //  * @see char_counter.cpp if you're having trouble.
    //  */

    while (infile.good())
        dict[infile.getNextWord()]++;

    for (auto p : dict)
    {
        if (p.second >= threshold)
            ret.push_back(p);
    }
    return ret;
}
