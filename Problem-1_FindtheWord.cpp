#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <string>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error

using namespace std;

// trie node
struct TrieNode
{
    struct TrieNode *children[26];

    int  isEndOfWord =0;
    // if isEndOfWord==0 then no word is ending at this node

};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
    pNode->isEndOfWord = 0;

    for (int i = 0; i < 26; i++)
        pNode->children[i] = NULL;

    return pNode;
}

void insert(struct TrieNode *root, string key,int frequencyTobe)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord +=frequencyTobe;
}

// Returns true if key presents in trie, else
// false
int search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }
    
    if(pCrawl != NULL && pCrawl->isEndOfWord > 0)
        return pCrawl->isEndOfWord;
    
    else return 0;
}

int main()
{



    struct TrieNode *root = getNode();


    // File pointer
    fstream fin;

    // Open an existing file
    fin.open("EnglishDictionary.csv", ios::in);


    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
    while (fin >> temp) {

        row.clear();
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);
        // used for breaking words
        stringstream s(line);
        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word)) {
            row.push_back(word);
        }

        string wordTobe = row[0];
        int frequencyTobe = stoi(row[1]);

        insert(root,wordTobe,frequencyTobe);

    }


    cout<<"Enter Word to be searched : ";
    string wordtobeSearched = "";
    int FrequencyobeSearched = "";
    // Search for different words
    FrequencyobeSearched = search(root, wordtobeSearched);
    if(FrequencyobeSearched>0)
        cout<<"No";
    else
        cout<<"YES, "<<FrequencyobeSearched;
    
    
    return 0;
}
