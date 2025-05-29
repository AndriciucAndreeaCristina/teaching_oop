#include "../include/collectable.hpp"

Collectable::Collectable(const int& quantity, const float& price, const std::string& name)
: Product(quantity, price), 
  _name(name)
{}

// Getter for name
std::string Collectable::getName() const
{
    return _name;
}

// Setter for name
void Collectable::setName(const std::string& name)
{
    _name = name;
}

PTYPE Collectable::typeOf() const
{
    return PTYPE::COLLECTABLE;
}

std::ostream& operator<<(std::ostream& os, const Collectable& collectable)
{
    os << static_cast<const Product&>(collectable);
    os << ", nume: " << collectable._name;
    return os;
}

std::istream& operator>>(std::istream& is, Collectable& collectable)
{
    is >> static_cast<Product&>(collectable);
    is.get(); // Clear newline remaining after reading integers/floats
    
    std::getline(is, collectable._name);
    return is;
}

Figurine::Figurine(const int& quantity, const float& price, const std::string& name, const std::string& category, const std::string& brand, const std::string& material)
: Collectable(quantity, price, name), 
  _category(category),
  _brand(brand),
  _material(material)
{}

// Getter for category
std::string Figurine::getCategory() const
{
    return _category;
}

// Getter for brand
std::string Figurine::getBrand() const
{
    return _brand;
}   

// Getter for material
std::string Figurine::getMaterial() const
{
    return _material;
}

// Setter for category
void Figurine::setCategory(const std::string& category)
{
    _category = category;
}

// Setter for brand
void Figurine::setBrand(const std::string& brand)
{
    _brand = brand;
}

// Setter for material
void Figurine::setMaterial(const std::string& material)
{
    _material = material;
}

PTYPE Figurine::typeOf() const
{
    return PTYPE::FIGURINE;
}

std::ostream& operator<<(std::ostream& os, const Figurine& figurine)
{
    os << static_cast<const Collectable&>(figurine);
    os << ", categorie: " << figurine._category << ", marca: " << figurine._brand << ", material: " << figurine._material;
    return os;
}

std::istream& operator>>(std::istream& is, Figurine& figurine)
{
    is >> static_cast<Collectable&>(figurine);

    std::getline(is, figurine._category);
    std::getline(is, figurine._brand);
    std::getline(is, figurine._material);

    return is;
}

Poster::Poster(const int& quantity, const float& price, const std::string& name, const std::string& format)
: Collectable(quantity, price, name), 
  _format(format)
{}

// Getter for format
std::string Poster::getFormat() const
{
    return _format;
}

// Setter for format
void Poster::setFormat(const std::string& format)
{
    _format = format;
}

PTYPE Poster::typeOf() const
{
    return PTYPE::POSTER;
}

std::ostream& operator<<(std::ostream& os, const Poster& poster)
{
    os << static_cast<const Collectable&>(poster);
    os << ", format: " << poster._format;
    return os;
}

std::istream& operator>>(std::istream& is, Poster& poster)
{
    is >> static_cast<Collectable&>(poster);
    std::getline(is, poster._format);
    return is;
}