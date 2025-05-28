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
    virtual ~Poem() {}
    std::string getTitle() const { return title; }
};

class HaikuPoem : public Poem {
public:
    HaikuPoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Haiku] " << title << ":\n";
        std::istringstream iss(content);
        std::string line;
        int count = 0;
        while (std::getline(iss, line) && count < 3) {
            std::cout << line << "\n";
            ++count;
        }
    }
};

class SonnetPoem : public Poem {
public:
    SonnetPoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Sonnet] " << title << ":\n";
        std::istringstream iss(content);
        std::string line;
        int lines = 0;
        while (std::getline(iss, line)) {
            std::cout << line << "\n";
            ++lines;
        }
        if (lines != 14) {
            std::cout << "(Warning: not exactly 14 lines)\n";
        }
    }
};

class FreeVersePoem : public Poem {
public:
    FreeVersePoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Free Verse] " << title << ":\n" << content << "\n";
    }
};

class NarrativePoem : public Poem {
public:
    NarrativePoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Narrative] " << title << ":\n" << content << "\n";
    }
};

class LyricPoem : public Poem {
public:
    LyricPoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Lyric] " << title << ":\n" << content << "\n";
    }
};

class ReligiousPoem : public Poem {
public:
    ReligiousPoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Religious] " << title << " (may God bless us):\n" << content << "\n";
    }
};

class PatrioticPoem : public Poem {
public:
    PatrioticPoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Patriotic] " << title << " 🇺🇦\n" << content << "\n";
    }
};

class EpicPoem : public Poem {
public:
    EpicPoem(const std::string& title, const std::string& content)
        : Poem(title, content) {
    }

    void display() const override {
        std::cout << "[Epic] " << title << ":\n" << content << "\n--- [End of Epic]\n";
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

    std::shared_ptr<Poem> createPoemByType(const std::string& type, const std::string& title, const std::string& content) {
        if (type == "haiku")     return std::make_shared<HaikuPoem>(title, content);
        if (type == "sonnet")    return std::make_shared<SonnetPoem>(title, content);
        if (type == "narrative") return std::make_shared<NarrativePoem>(title, content);
        if (type == "epic")      return std::make_shared<EpicPoem>(title, content);
        if (type == "lyric")     return std::make_shared<LyricPoem>(title, content);
        if (type == "religious") return std::make_shared<ReligiousPoem>(title, content);
        if (type == "patriotic") return std::make_shared<PatrioticPoem>(title, content);
        return std::make_shared<FreeVersePoem>(title, content); 
    }

public:
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Could not open file." << std::endl;
            return;
        }

        std::string line, authorName, title, type, content;
        while (std::getline(file, line)) {
            if (line.rfind("@Author:", 0) == 0) {
                authorName = line.substr(8);
            }
            else if (line.rfind("@Title:", 0) == 0) {
                title = line.substr(7);
            }
            else if (line.rfind("@Type:", 0) == 0) {
                type = line.substr(6);
                type.erase(0, type.find_first_not_of(" \t\r\n"));
                type.erase(type.find_last_not_of(" \t\r\n") + 1);
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
                it->addPoem(createPoemByType(type, title, content));
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

//int main() {
//    PoemLibrary library;
//    library.loadFromFile("poems_tagged.txt");
//    library.runInteractiveSession();
//    return 0;
//}
