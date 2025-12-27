#include "Menu.h"
#include "InputHandler.h"
#include "TextProcessor.h"
#include "StringSearch.h"
#include <iostream>
#include <string>

std::string currentText = "";
std::string editedText = "";

void inputText()
{
    InputHandler inputHandler;
    currentText = inputHandler.getText();
    editedText = "";
    std::cout << "\nТекст успешно введён!" << std::endl;
    std::cout << "Исходный текст: " << currentText << std::endl;
}

void editText()
{
    if (currentText.empty())
    {
        std::cout << "Сначала введите текст (пункт 1)!" << std::endl;
        return;
    }

    TextProcessor processor;
    editedText = processor.editText(currentText);
    
    std::cout << "\n=== Результат редактирования ===" << std::endl;
    std::cout << "Исходный текст: " << currentText << std::endl;
    std::cout << "Отредактированный текст: " << editedText << std::endl;
}

void showWordsWithoutDigits()
{
    if (currentText.empty())
    {
        std::cout << "Сначала введите текст (пункт 1)!" << std::endl;
        return;
    }

    TextProcessor processor;
    std::string textToUse = editedText.empty() ? currentText : editedText;
    
    std::vector<std::string> words = processor.getWordsWithoutDigits(textToUse);
    
    std::cout << "\n=== Слова без цифр ===" << std::endl;
    if (words.empty())
    {
        std::cout << "Слов без цифр не найдено." << std::endl;
    }
    else
    {
        std::cout << "Найдено слов: " << words.size() << std::endl;
        for (const auto &word : words)
        {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
}

void replaceDigitsWithLetters()
{
    if (currentText.empty())
    {
        std::cout << "Сначала введите текст (пункт 1)!" << std::endl;
        return;
    }

    TextProcessor processor;
    std::string textToUse = editedText.empty() ? currentText : editedText;
    
    std::string result = processor.replaceDigitsWithLetters(textToUse);
    
    std::cout << "\n=== Замена цифр на буквы ===" << std::endl;
    std::cout << "Исходный текст: " << textToUse << std::endl;
    std::cout << "Результат: " << result << std::endl;
    std::cout << "\nПравило замены: 1→a, 2→b, 3→c, 4→d, 5→e, 6→f, 7→g, 8→h, 9→i, 0 остаётся 0" << std::endl;
}

void searchSubstring()
{
    if (currentText.empty())
    {
        std::cout << "Сначала введите текст (пункт 1)!" << std::endl;
        return;
    }

    std::string textToUse = editedText.empty() ? currentText : editedText;
    
    std::cout << "\nВведите подстроку для поиска: ";
    std::string pattern;
    std::getline(std::cin, pattern);

    if (pattern.empty())
    {
        std::cout << "Подстрока не может быть пустой!" << std::endl;
        return;
    }

    StringSearch searcher;
    
    std::cout << "\nТекст для поиска: " << textToUse << std::endl;
    std::cout << "Искомая подстрока: " << pattern << std::endl;

    auto linearResults = searcher.linearSearch(textToUse, pattern);
    searcher.displayResults(linearResults, "Линейный поиск");

    auto boyerMooreResults = searcher.boyerMooreSearch(textToUse, pattern);
    searcher.displayResults(boyerMooreResults, "Бойер-Мур");
}

void showCurrentText()
{
    std::cout << "\n=== Текущие тексты ===" << std::endl;
    
    if (currentText.empty())
    {
        std::cout << "Текст ещё не введён." << std::endl;
        return;
    }

    std::cout << "Исходный текст: " << currentText << std::endl;
    
    if (!editedText.empty())
    {
        std::cout << "Отредактированный текст: " << editedText << std::endl;
    }
}

int main()
{
    Menu mainMenu("Обработка текста");

    mainMenu.addOption("Ввод текста", inputText);
    mainMenu.addOption("Редактирование текста", editText);
    mainMenu.addOption("Показать слова без цифр", showWordsWithoutDigits);
    mainMenu.addOption("Заменить цифры на буквы", replaceDigitsWithLetters);
    mainMenu.addOption("Поиск подстроки", searchSubstring);
    mainMenu.addOption("Показать текущий текст", showCurrentText);

    mainMenu.run();

    return 0;
}