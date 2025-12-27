#pragma once
#include <string>
#include <vector>

class TextProcessor
{
public:
    TextProcessor();
    ~TextProcessor();

    std::string removeExtraSpaces(const std::string &text);
    std::string removeExtraPunctuation(const std::string &text);
    std::string fixCapitalization(const std::string &text);
    
    std::string editText(const std::string &text);

    std::vector<std::string> getWordsWithoutDigits(const std::string &text);
    std::string replaceDigitsWithLetters(const std::string &text);

private:
    std::vector<std::string> splitIntoWords(const std::string &text);
    bool containsDigit(const std::string &word);
    bool isPunctuation(char c);
    char digitToLetter(char digit);
};