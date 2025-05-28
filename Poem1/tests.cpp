#include <cassert>
#include <iostream>
#include <sstream>
#include <memory>
#include "main.cpp"

void testPoemCreation() {
    HaikuPoem poem("Test Haiku", "Line one\nLine two\nLine three\nLine four");
    assert(poem.getTitle() == "Test Haiku");

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf()); 
    poem.display();
    std::cout.rdbuf(oldCout);  

    std::string output = oss.str();
    assert(output.find("Line one") != std::string::npos);
    assert(output.find("Line four") == std::string::npos);  
}

void testAuthorPoemByIndex() {
    Author author("Author A");
    author.addPoem(std::make_shared<FreeVersePoem>("Poem 1", "Content 1"));
    author.addPoem(std::make_shared<FreeVersePoem>("Poem 2", "Content 2"));

    auto poem = author.getPoemByIndex(2);
    assert(poem != nullptr);
    assert(poem->getTitle() == "Poem 2");

    auto invalid = author.getPoemByIndex(10);
    assert(invalid == nullptr);
}
void testLibraryLoad() {
    PoemLibrary library;
    library.loadFromFile("poems_tagged.txt");
}