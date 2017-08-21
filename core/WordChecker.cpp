// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <string>
#include <cstring>
#include <vector>
#include "Set.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>





WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
    //return false;
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    std::vector<std::string> suggest;
    std::string letter = "QWERTYUIOPASDFGHJKLZXCVBNM";
    std::string temp;

    std::cout << words.size() << std::endl;
    //Swapping each adjacent pair of characters in the word.
    for (unsigned int i = 0; i < word.size()-1; ++i)
    {
    	std::string temp2 = word;
    	temp = word;
    	temp2[i] = temp[i+1];
    	temp2[i+1] = temp[i];
    	if (wordExists(temp2) && (std::find(suggest.begin(), suggest.end(), temp2) == suggest.end()))
    	{
    		suggest.push_back(temp2);
    	}
    }

    //In between each adjacent pair of characters in the word (also before the first character and after the last character), each letter from 'A' through 'Z' is inserted.
    for (unsigned int i = 0; i<word.size(); ++i)
    {
    	for (unsigned int j = 0; j<letter.size(); ++j)
    	{
    		temp = word;
    		temp.insert(i, 1, letter[j]);
    		if (wordExists(temp) && (std::find(suggest.begin(), suggest.end(), temp) == suggest.end()))
    		{
    			suggest.push_back(temp);
    		}

    	}
    }

    //Deleting each character from the word.
    for (unsigned int i = 0; i<word.size(); ++i)
    {
    	temp = word;
    	temp.erase(i, 1);
    	
    	if (wordExists(temp) && (std::find(suggest.begin(), suggest.end(), temp) == suggest.end()))
    	{
    		suggest.push_back(temp);
    	}
    		
    }

    //Replacing each character in the word with each letter from 'A' through 'Z'.
    for (unsigned int i = 0; i<word.size(); ++i)
    {
    	for (unsigned int j = 0; j<letter.size(); ++j)
    	{
    		temp = word;
    		temp[i] = letter[j];
    		if (wordExists(temp) && (std::find(suggest.begin(), suggest.end(), temp) == suggest.end()))
    		{
    			suggest.push_back(temp);
    		}

    	}
    }

    //Splitting the word into a pair of words by adding a space in between each adjacent pair of characters in the word. 
    //It should be noted that this will only generate a suggestion if both words in the pair are found in the word set.
    for (unsigned int i = 0; i<word.size(); ++i)
    {
    	for (unsigned int j = 0; j<letter.size(); ++j)
    	{
    		temp = word;
    		temp.insert(i, " ");
    		if (wordExists(temp) && (std::find(suggest.begin(), suggest.end(), temp) == suggest.end()))
    		{
    			suggest.push_back(temp);
    		}

    	}
    }
    return suggest;
}

