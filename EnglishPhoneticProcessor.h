#pragma once
#include "TextTokenizer.h"

// Suppress the about 300 warnings from FST and Phonetisaurus headers
#pragma warning(push, 0)
#include <include/PhonetisaurusScript.h>
#pragma warning(pop)

#include "phoneticdict.h"

class EnglishPhoneticProcessor
{
private:
	TextTokenizer Tokenizer;
	PhonetisaurusScript* Phonemizer;

	inline bool FileExists(const std::string& name) {
		ifstream f(name.c_str());
		return f.good();
	}

public:
	bool Initialize(const std::string& PhoneticModelFn);
    std::string ProcessTextPhonetic(const std::string& InText, const std::vector<string> &InPhonemes,const std::vector<DictEntry>& InDict,ETTSLanguage::Enum InLanguage);
	EnglishPhoneticProcessor();
	EnglishPhoneticProcessor(const std::string& PhModelFn);
	~EnglishPhoneticProcessor();
};

