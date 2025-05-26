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
class PoemLibrary {
    std::vector<Author> authors;

public:
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Could not open file." << std::endl;
            return;
        }

        std::string line, authorName, title, content;
        while (std::getline(file, line)) {
            if (line.rfind("@Author:", 0) == 0) {
                authorName = line.substr(8);
            }
            else if (line.rfind("@Title:", 0) == 0) {
                title = line.substr(7);
            }
            else if (line.rfind("@Content:", 0) == 0) {
                content.clear();
                while (std::getline(file, line) && line != "---") {
                    content += line + "\n";
                }

                auto it = std::find_if(authors.begin(), authors.end(),
                    [&](const Author& a) { return a.getName() == authorName; });
                if (it == authors.end()) {
                    authors.emplace_back(authorName);
                    it = authors.end() - 1;
                }
                it->addPoem(std::make_shared<ConcretePoem>(title, content));
            }
        }
    }

    void runInteractiveSession() {
        std::cout << "Available authors:\n";
        for (size_t i = 0; i < authors.size(); ++i) {
            std::cout << i + 1 << ". " << authors[i].getName() << "\n";
        }

        std::cout << "Choose an author by number: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice < 1 || choice > authors.size()) {
            std::cout << "Invalid choice." << std::endl;
            return;
        }

        const Author& selected = authors[choice - 1];

        std::cout << "\nPoems by " << selected.getName() << ":\n";
        selected.listPoemTitles();

        std::cout << "\nChoose a poem by number: ";
        int poemIndex;
        std::cin >> poemIndex;

        auto poem = selected.getPoemByIndex(poemIndex);
        if (poem) {
            std::cout << "\n--- Poem Content ---\n";
            poem->display();
        }
        else {
            std::cout << "Invalid poem choice.\n";
        }
    }
};