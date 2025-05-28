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

void testSonnetPoemDisplayWarning() {
    std::string shortSonnet =
        "Line 1\nLine 2\nLine 3\nLine 4\nLine 5\nLine 6\nLine 7\n"
        "Line 8\nLine 9\nLine 10\nLine 11\nLine 12"; 

    SonnetPoem sonnet("Short Sonnet", shortSonnet);

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());  
    sonnet.display();
    std::cout.rdbuf(oldCout);  

    std::string output = oss.str();
    assert(output.find("Short Sonnet") != std::string::npos);
    assert(output.find("Line 12") != std::string::npos);
    assert(output.find("Warning: not exactly 14 lines") != std::string::npos);
}

int main() {
    testPoemCreation();
    testAuthorPoemByIndex();
    testLibraryLoad();
    testSonnetPoemDisplayWarning();
    std::cout << "All tests passed!\n";
    return 0;
}