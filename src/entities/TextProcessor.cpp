#include "TextProcessor.h"
#include <sstream>
#include <cctype>
#include <algorithm>

TextProcessor::TextProcessor() {}

TextProcessor::~TextProcessor() {}

std::string TextProcessor::editText(const std::string &text)
{
    std::string result = text;
    result = removeExtraSpaces(result);
    result = removeExtraPunctuation(result);
    result = fixCapitalization(result);
    return result;
}

std::string TextProcessor::removeExtraSpaces(const std::string &text)
{
    std::string result;
    bool lastWasSpace = false;

    for (size_t i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            if (!lastWasSpace && !result.empty())
            {
                result += ' ';
            }
            lastWasSpace = true;
        }
        else
        {
            result += text[i];
            lastWasSpace = false;
        }
    }

    if (!result.empty() && result.back() == ' ')
    {
        result.pop_back();
    }

    return result;
}

std::string TextProcessor::removeExtraPunctuation(const std::string &text)
{
    std::string result;
    
    for (size_t i = 0; i < text.length(); i++)
    {
        char current = text[i];
        
        if (isPunctuation(current))
        {
            if (current == '.' && i + 2 < text.length() && 
                text[i + 1] == '.' && text[i + 2] == '.')
            {
                result += "...";
                i += 2;
                continue;
            }

            if (result.empty() || !isPunctuation(result.back()))
            {
                result += current;
            }
        }
        else
        {
            result += current;
        }
    }

    return result;
}

std::string TextProcessor::fixCapitalization(const std::string &text)
{
    std::string result = text;
    bool newSentence = true;

    for (size_t i = 0; i < result.length(); i++)
    {
        if (std::isalpha(result[i]))
        {
            if (newSentence)
            {
                result[i] = std::toupper(result[i]);
                newSentence = false;
            }
            else
            {
                result[i] = std::tolower(result[i]);
            }
        }
        else if (result[i] == '.' || result[i] == '!' || result[i] == '?')
        {
            newSentence = true;
        }
    }

    return result;
}

std::vector<std::string> TextProcessor::getWordsWithoutDigits(const std::string &text)
{
    std::vector<std::string> words = splitIntoWords(text);
    std::vector<std::string> result;

    for (const auto &word : words)
    {
        if (!containsDigit(word))
        {
            result.push_back(word);
        }
    }

    return result;
}

std::string TextProcessor::replaceDigitsWithLetters(const std::string &text)
{
    std::string result;

    for (char c : text)
    {
        if (std::isdigit(c))
        {
            result += digitToLetter(c);
        }
        else
        {
            result += c;
        }
    }

    return result;
}

std::vector<std::string> TextProcessor::splitIntoWords(const std::string &text)
{
    std::vector<std::string> words;
    std::string word;

    for (char c : text)
    {
        if (std::isalnum(c))
        {
            word += c;
        }
        else if (!word.empty())
        {
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}

bool TextProcessor::containsDigit(const std::string &word)
{
    for (char c : word)
    {
        if (std::isdigit(c))
        {
            return true;
        }
    }
    return false;
}

bool TextProcessor::isPunctuation(char c)
{
    return c == '.' || c == ',' || c == '!' || c == '?' || 
           c == ';' || c == ':' || c == '-' || c == '\'' || c == '"';
}

char TextProcessor::digitToLetter(char digit)
{
    if (digit == '0')
    {
        return '0';
    }
    return 'a' + (digit - '1');
}