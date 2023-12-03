#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <vector>

/* Compress a string to a list of output symbols.
 * The result will be written to the output iterator
 * starting at "result"; the final iterator is returned.
 */
template <typename Iterator>
Iterator compress(const std::string &uncompressed, Iterator result)
{
    int  const nums = 3500000; 
    // Build the dictionary.
    int dictSize = nums;
    std::map<std::string, int> dictionary;
    for (int i = 0; i < nums; i++)
        dictionary[std::string(1, i)] = i;

    std::string w;
    for (std::string::const_iterator it = uncompressed.begin();
         it != uncompressed.end(); ++it)
    {
        char c = *it;
        std::string wc = w + c;
        
        if (dictionary.count(wc)) w = wc;
        else
        {
            *result++ = dictionary[w];
            // Add wc to the dictionary.
            dictionary[wc] = dictSize++;
            w = std::string(1, c);
        }
    }

    // Output the code for w.
    if (!w.empty())
        *result++ = dictionary[w];

    return result;
}

/*
 * Decompress a list of output ks to a string.
 * "begin" and "end" must form a valid range of ints
 */
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end)
{ 
    int  const nums = 3500000;
    // Build the dictionary.
    int dictSize = nums;
    std::map<int, std::string> dictionary;
    for (int i = 0; i < nums; i++)
        dictionary[i] = std::string(1, i);

    std::string w(1, *begin++);
    std::string result = w;
    std::string entry;
    for (; begin != end; begin++)
    {
        int k = *begin;
        if (dictionary.count(k))
            entry = dictionary[k];
        else if (k == dictSize)
            entry = w + w[0];
        else
            throw "Bad compressed k";

        result += entry;

        // Add w+entry[0] to the dictionary.
        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }
    return result;
}

int main()
{
    //Test Case 1
    std::vector<int> compressed;
    compress("fGZXWjsVzTIGmDT0oO9PLuHVyTFleYNZ1MyhqwJzQgFz4jWdalfVqzcCRY3EauV8retqbJZvmhAyBpYCcebKr4W7xYquy9k4C4lFWQq2I3efCWPcQ6O8t94ApnjS2IZuPn2dGznHg982hKFybXUHsBbOhTF5NzNtqgbO0cyufCmS3YXzIIjLhiov4pND9X316Ptm8tV6uxT38o32LqyBiDkPoOHgJuvvQu3qmcd9OVyLaQM9hjOlASTsFY6AjJ2zhkhNRaaXHDA0Q0li9eSTZorr9svHL1WPmAR0DWjEBWhEsvhpoJSTRjJUp6SiMOODD5QPbb4bx08ieIszPBWhrdV8GowUI0QBAiz5Dh66Lr6xOPgL03Gzgzn5WjRSkKSyJGkDQrzQCNptvFxS8VDsogtbHiE7VyPVKaZjY9KWwU9qDSwLyP94RF0ZFsG0J74zxSI3OvhnSk9HkcwbuZFi6e1zrecW6HiztaxVTMwHZtTWLfgfNPlpjKikbuK5YD11VsqVdW6L2VvcqNp4yO9fTnWRNkNcU8dbxOv1982EHz9zdITUAQAI9GkLTBQ94puKrbeCNo0WExLz8sWNyXsIK40bKSq0pYvhxi4QYvEXR672f3iZ1YRkiBrHLrz4CXWclueH99P3MW4RdlUrFX7qFoewl8VXrTGU0oXYDaTp7Xy4DlQ7PP4GyBL1fdX3QEfW4Tr8EMht6Y6gV5pGjIeP7HSlro0RS295kMAkQmhEbmNfGW9oE2fGWHRAWvyDdJxlCtQebYHdZ9ioxxCvzKgRAgAFpxFR4Dj9DPcatLEpEOTK2eQesickeCxGXHOKpg7mnncXJXTcP2HS8P1bCQxbI2Rfvs9OV33txEQAoXj3tvWHGFeZvNhtuf3SlmWCJpk8z117GTBcjiI9kZGjhXfQjDwcxhElthP8sPxZ8F8HFcPCmPlFRKxIUxoqdsEbVvOkQUjZcQZQJVUNR9BeUvYQ1kEP0xZToj9Y3yDfCB0S", std::back_inserter(compressed));
    copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    std::string decompressed = decompress(compressed.begin(), compressed.end());
    std::cout << decompressed << std::endl;

    return 0;
}
