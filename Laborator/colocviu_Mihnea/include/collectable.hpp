#pragma once

#ifndef COLLECTABLE_HPP
#define COLLECTABLE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "product.hpp"

class Collectable : public Product
{
protected:
    std::string _name;

public:

    Collectable() = default;
    Collectable(const int& quantity, const float& price, const std::string& name);
    virtual ~Collectable() = default;

    std::string getName() const;
    void setName(const std::string& name);

    virtual PTYPE typeOf() const override;

    friend std::ostream& operator<<(std::ostream& os, const Collectable& collectable);
    friend std::istream& operator>>(std::istream& is, Collectable& collectable);
};

class Figurine : public Collectable
{
private:
    std::string _category;
    std::string _brand;
    std::string _material;

public:

    Figurine() = default;
    Figurine(const int& quantity, const float& price, const std::string& name, const std::string& category, const std::string& brand, const std::string& material);
    virtual ~Figurine() = default;

    std::string getCategory() const;
    std::string getBrand() const;
    std::string getMaterial() const;
    void setCategory(const std::string& category);
    void setBrand(const std::string& brand);
    void setMaterial(const std::string& material);

    virtual PTYPE typeOf() const override;

    friend std::ostream& operator<<(std::ostream& os, const Figurine& figurine);
    friend std::istream& operator>>(std::istream& is, Figurine& figurine);
};

class Poster : public Collectable
{
private:
    std::string _format;

public:

    Poster() = default;
    Poster(const int& quantity, const float& price, const std::string& name, const std::string& format);
    virtual ~Poster() = default;

    std::string getFormat() const;
    void setFormat(const std::string& format);

    virtual PTYPE typeOf() const override;

    friend std::ostream& operator<<(std::ostream& os, const Poster& poster);
    friend std::istream& operator>>(std::istream& is, Poster& poster);
};

#endif // COLLECTABLE_HPP