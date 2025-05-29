#pragma once

#ifndef DISC_HPP
#define DISC_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "product.hpp"

class Disk : public Product
{
protected:
    int _duration;

public:

    Disk() = default;
    Disk(const int& quantity, const float& price, const int& duration);
    virtual ~Disk() = default;

    int getDuration() const;
    void setDuration(const int& duration);

    virtual PTYPE typeOf() const override;

    friend std::ostream& operator<<(std::ostream& os, const Disk& disc);
    friend std::istream& operator>>(std::istream& is, Disk& disc);
};

class MusicDisk : public Disk
{
private:
    std::string _album;
    std::vector<std::string> _artists;

public:

    MusicDisk() = default;
    MusicDisk(const int& quantity, const float& price, const int& duration, const std::string& album, const std::vector<std::string>& artists);
    virtual ~MusicDisk() = default;

    std::string getAlbum() const;
    std::vector<std::string> getArtists() const;
    void setAlbum(const std::string& album);
    void setArtists(const std::vector<std::string>& artists);

    virtual PTYPE typeOf() const override;

    friend std::ostream& operator<<(std::ostream& os, const MusicDisk& disc);
    friend std::istream& operator>>(std::istream& is, MusicDisk& disc);
};

class MovieDisk : public Disk
{
private:
    std::string _name;
    std::string _genre;

public:

    MovieDisk() = default;
    MovieDisk(const int& quantity, const float& price, const int& duration, const std::string& name, const std::string& genre);
    virtual ~MovieDisk() = default;

    std::string getName() const;
    std::string getGenre() const;
    void setName(const std::string& name);
    void setGenre(const std::string& genre);

    virtual PTYPE typeOf() const override;

    friend std::ostream& operator<<(std::ostream& os, const MovieDisk& disc);
    friend std::istream& operator>>(std::istream& is, MovieDisk& disc);
};

#endif // DISC_HPP