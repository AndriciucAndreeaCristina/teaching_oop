#include "../include/book.hpp"

Book::Book(const int& quantity, const float& price, const std::string& title, const std::string& publisher, const std::vector<std::string>& authors)
: Product(quantity, price), 
  _title(title), 
  _publisher(publisher), 
  _authors(authors) 
{}

// Getter for title
std::string Book::getTitle() const
{
    return _title;
}

// Getter for publisher
std::string Book::getPublisher() const
{
    return _publisher;
}

// Getter for authors
std::vector<std::string> Book::getAuthors() const
{
    return _authors;
}

// Setter for title
void Book::setTitle(const std::string& title)
{
    _title = title;
}

// Setter for publisher
void Book::setPublisher(const std::string& publisher)
{
    _publisher = publisher;
}

// Setter for authors
void Book::setAuthors(const std::vector<std::string>& authors)
{
    _authors = authors;
}

PTYPE Book::typeOf() const
{
    return PTYPE::BOOK;
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << static_cast<const Product&>(book);
    os << ", titlu: " << book._title << ", editura: " << book._publisher << ", autori: ";

    for(const std::string& author : book._authors)
    {
        // Don't leave a trailing comma on the last author
        if(author != book._authors.back())
            os << author << ",";
        else
            os << author;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Book& book)
{
    is >> static_cast<Product&>(book);
    is.get(); // Clear newline remaining after reading integers/floats

    std::getline(is, book._title);
    std::getline(is, book._publisher);

    std::string authorsLine;
    std::string author;
    std::getline(is, authorsLine); // Read all the authors
    std::stringstream ss(authorsLine); // Make the string read this way into a stream

    while(std::getline(ss, author, ',')) // The stream separator is a comma
                                         // Read tokens in the author variable
    {
        book._authors.push_back(author); // Append them to the result list
    }

    return is;
}