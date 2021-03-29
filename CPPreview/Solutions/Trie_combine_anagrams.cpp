struct TrieNode
{
	TrieNode() : _isEnd(false), _kids{}, _idxs{} {}

	bool _isEnd;
	std::unordered_map<char, TrieNode*> _kids;
	std::vector<int> _idxs;
};

void insertTrie(TrieNode* & root, std::string word, unsigned int charIdx, unsigned int wordIdx)
{
	if (!root)
	{
		root = new TrieNode;
	}

	if (charIdx < word.size())
	{
		insertTrie(root->_kids[word[charIdx]], word, charIdx + 1, wordIdx);
	}
	else
	{
		root->_isEnd = true;
		root->_idxs.push_back(wordIdx);
	}
}

void traverseTrie(TrieNode* root, std::vector<std::string>& words, std::vector<std::vector<std::string>>& result)
{
	if (!root) return;

	if (root->_isEnd)
	{
		std::vector<std::string> bucket;

		for (auto el : root->_idxs)
		{
			bucket.push_back(words[el]);
		}

		result.push_back(bucket);
	}
	else
	{
		for (auto el : root->_kids)
		{
			traverseTrie(el.second, words, result);
		}
	}
}

std::vector<std::vector<std::string>> combineAnagram(std::vector<std::string>& words)
{
	std::vector<std::vector<std::string>> result;

	TrieNode* root = new TrieNode;

	for (auto i = 0; i < words.size(); ++i)
	{
		auto buffer = words[i];
		std::sort(buffer.begin(), buffer.end());

		insertTrie(root, buffer, 0, i);
	}

	traverseTrie(root, words, result);

	return result;
}



int main()
{	
	std::vector<std::string> words{ "cat", "dog", "tac", "god", "act", "gdo" };    // res {{"cat", "tac", "act"}, {"dog", "god", "gdo"}}
	auto res = combineAnagram(words);
}
