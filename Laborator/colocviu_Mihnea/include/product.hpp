#pragma once

#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <iostream>

// Enum of all product types known to the program
enum class PTYPE
{
    PRODUCT,
    BOOK,
    DISK,
    MUSIC_DISK,
    MOVIE_DISK,
    COLLECTABLE,
    FIGURINE,
    POSTER
};

class Product
{
private:
    static int autoId;
    static int liveCount;

protected:
    int _id;
    int _quantity;
    float _price;

public:

    static int getCount();

    Product();
    Product(const int& quantity, const float& price);
    Product(const Product& product);
    virtual ~Product();

    int getId() const;
    int getQuantity() const;
    float getPrice() const;
    void setQuantity(const int& quantity);
    void setPrice(const float& price);

    virtual PTYPE typeOf() const;

    bool operator<(const Product& product);
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
    friend std::istream& operator>>(std::istream& is, Product& product);
};

#endif // PRODUCT_HPP