#include "InputHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

std::string InputHandler::getText()
{
    InputMode mode = selectInputMode();
    std::string text;

    if (mode == KEYBOARD)
    {
        text = getFromKeyboard();
    }
    else
    {
        text = getFromFile();
    }

    if (!validateInput(text))
    {
        std::cout << "Текст не соответствует требованиям. Попробуйте снова." << std::endl;
        return getText();
    }

    return text;
}

InputHandler::InputMode InputHandler::selectInputMode()
{
    std::cout << "Выберите способ ввода:" << std::endl;
    std::cout << "1. Клавиатура" << std::endl;
    std::cout << "2. Файл" << std::endl;
    std::cout << "Ваш выбор: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    return (choice == 2) ? FILE : KEYBOARD;
}

std::string InputHandler::getFromKeyboard()
{
    std::cout << "Введите текст (закончите точкой):" << std::endl;
    std::string text;
    std::getline(std::cin, text);
    return text;
}

std::string InputHandler::getFromFile()
{
    std::cout << "Введите имя файла: ";
    std::string filename;
    std::getline(std::cin, filename);

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return getFromFile();
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

bool InputHandler::validateInput(const std::string &text)
{
    if (text.empty() || text.back() != '.')
    {
        std::cout << "Текст должен заканчиваться точкой!" << std::endl;
        return false;
    }

    std::istringstream iss(text);
    std::string word;
    int wordCount = 0;

    while (iss >> word)
    {
        std::string cleanWord;
        for (char c : word)
        {
            if (c != '.')
            {
                cleanWord += c;
            }
        }

        if (!cleanWord.empty())
        {
            wordCount++;
            if (cleanWord.length() > 10)
            {
                std::cout << "Слово \"" << cleanWord << "\" содержит более 10 символов!" << std::endl;
                return false;
            }
        }
    }

    if (wordCount < 1 || wordCount > 50)
    {
        std::cout << "Количество слов должно быть от 1 до 50! (найдено: " << wordCount << ")" << std::endl;
        return false;
    }

    return true;
}