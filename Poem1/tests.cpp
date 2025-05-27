//#include <cassert>
//#include <iostream>
//#include <sstream>
//#include <memory>
//#include "main.cpp"
//void testPoemCreation() {
//    ConcretePoem poem("Test Title", "This is a test content.");
//    assert(poem.getTitle() == "Test Title");
//    std::ostringstream oss;
//    poem.display();
//}
//void testAuthorPoemByIndex() {
//    Author author("Author A");
//    author.addPoem(std::make_shared<ConcretePoem>("Poem 1", "Content 1"));
//    author.addPoem(std::make_shared<ConcretePoem>("Poem 2", "Content 2"));
//
//    auto poem = author.getPoemByIndex(2);
//    assert(poem != nullptr);
//    assert(poem->getTitle() == "Poem 2");
//
//    auto invalid = author.getPoemByIndex(10);
//    assert(invalid == nullptr);
//}
//void testLibraryLoad() {
//    PoemLibrary library;
//    library.loadFromFile("poems_cleaned.txt");
//}
//
//int main() {
//    testPoemCreation();
//    testAuthorPoemByIndex();
//    testLibraryLoad();
//    std::cout << "All tests passed!\n";
//    return 0;
//}