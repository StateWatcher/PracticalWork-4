#pragma once
#include <string>
#include <vector>

struct SearchResult
{
    int position;
    SearchResult(int pos) : position(pos) {}
};

class StringSearch
{
public:
    StringSearch();
    ~StringSearch();

    std::vector<SearchResult> linearSearch(const std::string &text, const std::string &pattern);
    std::vector<SearchResult> boyerMooreSearch(const std::string &text, const std::string &pattern);

    void displayResults(const std::vector<SearchResult> &results, const std::string &algorithmName);

private:
    void buildBadCharTable(const std::string &pattern, int badChar[256]);
    int max(int a, int b);
};