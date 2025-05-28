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

