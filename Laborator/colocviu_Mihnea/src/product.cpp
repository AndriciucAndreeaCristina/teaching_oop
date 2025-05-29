#include "../include/product.hpp"

// Unique IDs, increments every time a new product is made
int Product::autoId = 0;

// Tracker for the number of live (existing) Product objects
int Product::liveCount = 0;

Product::Product()
{
    // Increment the unique ID generator, then use the new ID
    _id = ++Product::autoId;
    // A new object has been created, update the counter
    Product::liveCount++;
}

Product::Product(const int& quantity, const float& price) 
: _quantity(quantity), 
  _price(price)
{
    _id = ++Product::autoId;
    Product::liveCount++;
}

Product::Product(const Product& product) 
: _quantity(product._quantity), 
  _price(product._price)
{
    _id = ++Product::autoId;
    Product::liveCount++;
}

// Virtual destructor
Product::~Product()
{
    // Keep count that an object has been destroyed
    liveCount--;
}

// Getter for the number of live objects
int Product::getCount()
{
    return liveCount;
}

// Getter for ID
int Product::getId() const
{
    return _id;
}

// Getter for quantity
int Product::getQuantity() const
{
    return _quantity;
}

// Getter for price
float Product::getPrice() const
{
    return _price;
}

// Setter for quantity
void Product::setQuantity(const int& quantity)
{
    _quantity = quantity;
}

// Setter for price
void Product::setPrice(const float& price)
{
    _price = price;
}

// Gets object type, will be overriden in derived classes to return the correct type
PTYPE Product::typeOf() const
{
    return PTYPE::PRODUCT;
}

// Object comparison is done by price
bool Product::operator<(const Product& product)
{
    return _price < product._price;
}

std::ostream& operator<<(std::ostream& os, const Product& product)
{
    os << "ID: " << product._id << ", cantitate: " << product._quantity << ", pret: " << product._price;
    return os;
}

std::istream& operator>>(std::istream& is, Product& product)
{
    is >> product._quantity >> product._price;
    return is;
}
