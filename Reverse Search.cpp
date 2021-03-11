#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <string>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error

using namespace std;
struct Trie {

    int index;

    Trie* child[26];

    /*to make new trie*/
    Trie()
    {
        for (int i = 0; i < 26; i++)
            child[i] = NULL;
        index = -1;
    }
};

/* function to insert in trie */
void insert(Trie* root, string str, int index)
{
    Trie* node = root;

    for (int i = 0; i < str.size(); i++) {

        /* taking ascii value to find index of
          child node */
        char ind = str[i] - 'a';

        /* making new path if not already */
        if (!node->child[ind])
            node->child[ind] = new Trie();

        // go to next node
        node = node->child[ind];
    }

    // Mark leaf (end of word) and store
    // index of word in arr[]
    node->index = index;
}

/* function for PrintThatWord  */
void PrintThatWord(Trie* node, vector<string> arr,int index)
{
    if (node == NULL)
        return ;

    for (int i = 0; i < 26; i++) {
        if (node->child[i] != NULL) {

            /* if leaf node then print key*/
            if (node->child[i]->index == index){
                cout<<arr[node->child[i]->index] ;
                return;
            }
            PrintThatWord(node->child[i], arr,index);
        }
    }
}



int main()
{



    Trie* root = new Trie();


    // File pointer
    fstream fin;

    // Open an existing file
    fin.open("EnglishDictionary.csv", ios::in);


    // Read the Data from the file
    // as String Vector
    vector<string> row,arr;
    string line, word, temp;
    int index=1;
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
        arr.push_back(wordTobe);
        insert(root,wordTobe,index);
        index++;

    }

    cout<<"Enter index whose word has to be found out : ";
    cin>>index;
    PrintThatWord(root, arr ,index);



    return 0;
}
