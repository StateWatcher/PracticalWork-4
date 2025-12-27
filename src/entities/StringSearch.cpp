#include "StringSearch.h"
#include <iostream>
#include <algorithm>

StringSearch::StringSearch() {}

StringSearch::~StringSearch() {}

std::vector<SearchResult> StringSearch::linearSearch(const std::string &text, const std::string &pattern)
{
  std::vector<SearchResult> results;
  int n = text.length();
  int m = pattern.length();

  for (int i = 0; i <= n - m; i++)
  {
    int j;
    for (j = 0; j < m; j++)
    {
      if (text[i + j] != pattern[j])
        break;
    }

    if (j == m)
    {
      results.push_back(SearchResult(i));
    }
  }

  return results;
}

std::vector<int> suffixes(const std::string &pattern)
{
  int length = pattern.length();
  std::vector<int> suffix(length, 0);

  int g, f;
  g = f = length - 1;
  for (int i = length - 2; i >= 0; --i)
  {
    if (i > g && suffix[i + length - 1 - f] < i - g)
    {
      suffix[i] = suffix[i + length - 1 - f];
    }
    else
    {
      if (i < g)
      {
        g = i;
      }
      f = i;
      while (g >= 0 && pattern[g] == pattern[g + length - 1 - f])
      {
        --g;
      }
      suffix[i] = f - g;
    }
  }

  return suffix;
}

std::vector<SearchResult> StringSearch::boyerMooreSearch(const std::string &text, const std::string &pattern)
{
  int n = text.length();
  int m = pattern.length();
  std::vector<SearchResult> results;

  if (m == 0 || n < m)
  {
    return results;
  }

  std::vector<int> shift(256, m);
  for (int i = 0; i < m - 1; ++i)
  {
    shift[static_cast<unsigned char>(pattern[i])] = m - i - 1;
  }

  std::vector<int> suffix = suffixes(pattern);

  int i = 0;
  while (i <= n - m)
  {
    int j = m - 1;
    while (j >= 0 && pattern[j] == text[i + j])
    {
      --j;
    }
    if (j < 0)
    {
      results.push_back(SearchResult(i));
      if (i + m < n)
      {
        int shiftValue = shift[static_cast<unsigned char>(text[i + m])];
        i += (shiftValue > 0) ? shiftValue : 1;
      }
      else
      {
        i += 1;
      }
    }
    else
    {
      int x = suffix[j];
      int y = j - x;
      int z = m - 1 - j;
      int shiftValue = max(shift[static_cast<unsigned char>(text[i + j])] - y, z);
      i += (shiftValue > 0) ? shiftValue : 1;
    }
  }

  return results;
}

void StringSearch::displayResults(const std::vector<SearchResult> &results, const std::string &algorithmName)
{
  std::cout << "\n=== Результаты поиска (" << algorithmName << ") ===" << std::endl;

  if (results.empty())
  {
    std::cout << "Подстрока не найдена." << std::endl;
  }
  else
  {
    std::cout << "Найдено вхождений: " << results.size() << std::endl;
    std::cout << "Позиции: ";
    for (size_t i = 0; i < results.size(); i++)
    {
      std::cout << results[i].position;
      if (i < results.size() - 1)
      {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
}

void StringSearch::buildBadCharTable(const std::string &pattern, int badChar[256])
{
  int m = pattern.length();

  for (int i = 0; i < 256; i++)
  {
    badChar[i] = m;
  }

  for (int i = 0; i < m - 1; i++)
  {
    badChar[static_cast<unsigned char>(pattern[i])] = m - i - 1;
  }
}

int StringSearch::max(int a, int b)
{
  return (a > b) ? a : b;
}