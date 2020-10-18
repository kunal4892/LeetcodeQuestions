/* This is a simple program to create a Trie from a bunch of strings.
 * The user can then provide the some substring to check for all the 
 * autocompletions possible 
 * 
 * Author: Kumar Kunal
 * /



#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;
 
class Trie{
public:
    shared_ptr<Trie> children[26];
    char val;
    bool isWord;
    bool visited;
    Trie():val('\0'), isWord(false), visited(false){
    }
    Trie(char val):val(val), isWord(false), visited(false)
    {
        for(int i = 0; i<26; ++i){
            children[i] = make_shared<Trie>();
        }
    }
};

class Solution {
    std::vector<string> words;
    std::shared_ptr<Trie> root;
    void createTrie(std::shared_ptr<Trie> root, string word){
        for(int i=0; i<word.length(); ++i){
                auto a = word[i]-'a';
                if(!root->children[a]){
                    root->children[a] = make_shared<Trie>();
                    root->children[a]->val = word[i];
                }
            root = root->children[a];
            }
        root->isWord=true;
        }
    
    public:
    Solution(std::vector<string> words):words(words){
        root = std::make_shared<Trie>();
        for(auto const& word: words){
            createTrie(root, word);
        }
    }
    
    void dfs(std::shared_ptr<Trie> dfsroot, string s, vector<string>& res){
        if(dfsroot->isWord){
            res.push_back(s);
        }
        for(int i =0; i<26; ++i){
            if(dfsroot->children[i] && !dfsroot->children[i]->visited){
                dfsroot->children[i]->visited=true;
                dfs(dfsroot->children[i], s+dfsroot->children[i]->val, res);
            }
        }
        return;

    }
    
    vector<string> giveAutocompletedWords(const string& s) {
        //dfs
        auto newRoot = root;
        for(auto const& a: s){
            newRoot = newRoot->children[a -'a'];
        }
        vector<string> res;
        dfs(newRoot, s, res);
        return res;
    }
};



//Driver Program
int main(){
    vector<string>v{"dog", "dot", "dodge", "dust", "cute"};
    Solution sol(v);
    auto res = sol.giveAutocompletedWords("c");
    for(const auto& r: res){
        cout<<r<<endl;
    }
    return 0;
}
