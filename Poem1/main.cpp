#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
class Poem {
protected:
    std::string title;
    std::string content;

public:
    Poem(const std::string& title, const std::string& content)
        : title(title), content(content) {
    }

    virtual void display() const = 0;
    std::string getTitle() const { return title; }
};
class ConcretePoem : public Poem {
public:
    ConcretePoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "Title: " << title << "\n" << content << "\n";
    }
};