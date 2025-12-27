#pragma once
#include <string>

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    std::string getText();

private:
    enum InputMode
    {
        KEYBOARD,
        FILE
    };

    InputMode selectInputMode();
    std::string getFromKeyboard();
    std::string getFromFile();
    bool validateInput(const std::string &text);
};