#include "../include/disk.hpp"

Disk::Disk(const int& quantity, const float& price, const int& duration)
: Product(quantity, price), 
  _duration(duration)
{}

// Getter for duration
int Disk::getDuration() const
{
    return _duration;
}

// Setter for duration
void Disk::setDuration(const int& duration)
{
    _duration = duration;
}

PTYPE Disk::typeOf() const
{
    return PTYPE::DISK;
}

std::ostream& operator<<(std::ostream& os, const Disk& disc)
{
    os << static_cast<const Product&>(disc);
    os << ", durata (min): " << disc._duration;
    return os;
}

std::istream& operator>>(std::istream& is, Disk& disc)
{
    is >> static_cast<Product&>(disc);
    is >> disc._duration;
    return is;
}

MusicDisk::MusicDisk(const int& quantity, const float& price, const int& duration, const std::string& album, const std::vector<std::string>& artists)
: Disk(quantity, price, duration), 
  _album(album), 
  _artists(artists) 
{}

// Getter for album
std::string MusicDisk::getAlbum() const
{
    return _album;
}

// Getter for artists
std::vector<std::string> MusicDisk::getArtists() const
{
    return _artists;
}

// Setter for album
void MusicDisk::setAlbum(const std::string& album)
{
    _album = album;
}

// Setter for artists
void MusicDisk::setArtists(const std::vector<std::string>& artists)
{
    _artists = artists;
}

PTYPE MusicDisk::typeOf() const
{
    return PTYPE::MUSIC_DISK;
}

std::ostream& operator<<(std::ostream& os, const MusicDisk& disc)
{
    os << static_cast<const Disk&>(disc);
    os << ", album: " << disc._album << ", interpreti: "; 
    
    for(const std::string& artist : disc._artists) 
    {
        // Don't leave a trailing comma on the last artist
        if(artist != disc._artists.back())
            os << artist << ",";
        else
            os << artist;
    }

    return os;
}

std::istream& operator>>(std::istream& is, MusicDisk& disc)
{
    is >> static_cast<Disk&>(disc);
    is.get(); // Clear newline remaining after reading integers/floats

    std::getline(is, disc._album);

    std::string artistsLine;
    std::string artist;
    std::getline(is, artistsLine); // Read all the artists
    std::stringstream ss(artistsLine); // Make the string read this way into a stream

    while(std::getline(ss, artist, ',')) // The stream separator is a comma
                                         // Read tokens in the artist variable
    {
        disc._artists.push_back(artist); // Append them to the result list
    }

    return is;
}

MovieDisk::MovieDisk(const int& quantity, const float& price, const int& duration, const std::string& name, const std::string& genre)
: Disk(quantity, price, duration), 
  _name(name), 
  _genre(genre) 
{}

// Getter for name
std::string MovieDisk::getName() const
{
    return _name;
}    

// Getter for genre
std::string MovieDisk::getGenre() const
{
    return _genre;
}

// Setter for name
void MovieDisk::setName(const std::string& name)
{
    _name = name;
}

// Setter for genre
void MovieDisk::setGenre(const std::string& genre)
{
    _genre = genre;
}

PTYPE MovieDisk::typeOf() const
{
    return PTYPE::MOVIE_DISK;
}

std::ostream& operator<<(std::ostream& os, const MovieDisk& disc)
{
    os << static_cast<const Disk&>(disc);
    os << ", nume: " << disc._name << ", gen: " << disc._genre;
    return os;
}

std::istream& operator>>(std::istream& is, MovieDisk& disc)
{
    is >> static_cast<Disk&>(disc);
    is.get(); // Clear newline remaining after reading integers/floats

    std::getline(is, disc._name);
    std::getline(is, disc._genre);
    return is;
}
