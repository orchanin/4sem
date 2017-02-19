#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector> 
#include <iostream>

const int _NOTMCW_ = 40; //number of the most common words in text


std::string prepare(const std::string& word)
{
	std::string result = word;
	std::transform(word.begin(), word.end(), result.begin(), ::tolower);
	std::string symbols = ".,/:;'!?-";
	for(int i = 0; i < symbols.size(); i++)
		if (result[result.size() - 1] == symbols[i])
			result.pop_back();
	return result;
}

struct Statistics 
{
	int count;
	std::string word;
};

bool compare(const Statistics& stat1, const Statistics& stat2) 
{
	if (stat1.count != stat2.count) 
	{
		return stat1.count > stat2.count;
	}
	return stat1.word < stat2.word;
}

int main()
{
	std::ifstream file("TheLastLeaf.txt");
	std::map<std::string, int> allWords;
	if (file.is_open())
	{
		std::string word;
		while (!file.eof()) 
		{
			file >> word;
			word = prepare(word);
			allWords[word]++;
		}
		file.close();
	}
	allWords.erase(""); // clear empty words (e.g. after removing "-" from " - ")
	
	std::vector<Statistics> stat;
	stat.resize(allWords.size());
	
	int i = 0;
	
	for (auto it = allWords.begin(); it != allWords.end(); ++it)
	{
		stat[i].word = it->first;
		stat[i].count = it->second;
		i++;
	}
	
	std::sort(stat.begin(), stat.end(), compare);
	
	std::ofstream fout("stat.txt");
	
	for (i = 0; i < _NOTMCW_; i++) 
	{
		fout << stat[i].word << "\t: " << stat[i].count << std::endl;
	}

	return 0;
}