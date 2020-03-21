//
//  main.cpp
//  MultiStringSearch
//
//  Created by adeeb mohammed on 15/03/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//
// program for searching the multiple string
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

/*
    this problem which can be solved in multiple ways
    we need to have a tri tree which can have
    either big string or small string
 
 time complexity o(ns+bs) time
 o(ns) space complexity
 */

class TrieNode{
public:
    std::unordered_map<char, TrieNode*> children;
};

class SuffixTrie{
private:
    TrieNode *rootNode = new TrieNode();
    char endSymbol = '*';
public:
   void insertString(std::string str){
       TrieNode *currentNode = this->rootNode;
       for(int i = 0; i < str.size(); i++){
           char ch = str[i];
           if(currentNode->children.find(ch) == currentNode->children.end()){
               currentNode->children.insert({ch,new TrieNode()});
           }
           currentNode = currentNode->children[ch];
       }
       currentNode->children.insert({this->endSymbol,nullptr});
   }
    
    void searchString(std::string str,
        std::unordered_map<std::string, bool> &wordMap
        ){
        TrieNode *currentNode = this->rootNode;
        std::string currentWord = "";
        for(int  i = 0; i < str.size(); i++){
            char ch = str[i];
            if(currentNode->children.find(ch) != currentNode->children.end()){
                currentWord+=ch;
                TrieNode *nextNode = currentNode->children[ch];
                if(nextNode->children.find(this->endSymbol)!= nextNode->children.end()){
                    wordMap[currentWord] = true;
                }
                currentNode = currentNode->children[ch];
            }else {
                currentWord="";
                currentNode = this->rootNode;
            }
        }
        return;
    }
   
};

std::vector<bool> multiStringSearch(std::string bigString, std::vector<std::string> smallStrings) {
    std::vector<bool> searchResult;
    SuffixTrie oSuffixTrie;
    // all strings are now inserted
    std::unordered_map<std::string,bool> wordMap;
    for(auto oneString : smallStrings){
        oSuffixTrie.insertString(oneString);
        wordMap.insert({oneString,false});
    }
    oSuffixTrie.searchString(bigString, wordMap);
    for(auto oneString : smallStrings){
        if(wordMap[oneString] == true){
            searchResult.push_back(true);
        }else{
            searchResult.push_back(false);
        }
    }
    wordMap.clear();
    return searchResult;
}


int main(int argc, const char * argv[]) {
    std::string bigString = "Mary goes to the shopping  center every week";
    std::vector<std::string> smallStrings = {"to","Mary","centers","shop","shopping","shoppingbus","string","kappa"};
    auto result = multiStringSearch(bigString, smallStrings );
    for(auto res : result){
        std::cout << res << std::endl;
    }
    return 0;
}
