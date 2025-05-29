#pragma once

#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "product.hpp"

class Book : public Product
{
private:
    std::string _title;
    std::string _publisher;
    std::vector<std::string> _authors;

public:

    Book() = default;
    Book(const int& quantity, const float& price, const std::string& title, const std::string& publisher, const std::vector<std::string>& authors);
    virtual ~Book() = default;

    std::string getTitle() const;
    std::string getPublisher() const;
    std::vector<std::string> getAuthors() const;
    void setTitle(const std::string& title);
    void setPublisher(const std::string& publisher);
    void setAuthors(const std::vector<std::string>& authors);

    virtual PTYPE typeOf() const override;

    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
};

#endif // BOOK_HPP