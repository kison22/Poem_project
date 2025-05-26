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
class Author {
    std::string name;
    std::vector<std::shared_ptr<Poem>> poems;

public:
    Author(const std::string& name) : name(name) {}

    void addPoem(const std::shared_ptr<Poem>& poem) {
        poems.push_back(poem);
    }

    const std::string& getName() const {
        return name;
    }

    void listPoemTitles() const {
        for (size_t i = 0; i < poems.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << poems[i]->getTitle() << "\n";
        }
    }

    std::shared_ptr<Poem> getPoemByIndex(size_t index) const {
        if (index < 1 || index > poems.size()) return nullptr;
        return poems[index - 1];
    }
};