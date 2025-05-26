#include <cassert>
#include <iostream>
#include <sstream>
#include <memory>
#include "main.cpp"
void testPoemCreation() {
    ConcretePoem poem("Test Title", "This is a test content.");
    assert(poem.getTitle() == "Test Title");
    std::ostringstream oss;
    poem.display();
}
