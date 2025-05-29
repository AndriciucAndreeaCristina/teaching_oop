#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>

#include "include/book.hpp"
#include "include/disk.hpp"
#include "include/product.hpp"
#include "include/collectable.hpp"

// Prints a Product* on the screen according to the type actually pointed to
void showProduct(Product* const& product)
{
    switch(product->typeOf())
    {
    case PTYPE::BOOK:
        std::cout << "[CARTE]\t\t | " << *static_cast<Book*>(product);
        break;
    case PTYPE::MUSIC_DISK:
        std::cout << "[DVD_MUZICA]\t | " << *static_cast<MusicDisk*>(product);
        break;
    case PTYPE::MOVIE_DISK:
        std::cout << "[DVD_FILME]\t | " << *static_cast<MovieDisk*>(product);
        break;
    case PTYPE::FIGURINE:
        std::cout << "[FIGURINA]\t | " << *static_cast<Figurine*>(product);
        break;
    case PTYPE::POSTER:
        std::cout << "[POSTER]\t | " << *static_cast<Poster*>(product);
        break;
    default:
        // Should never happen
        // If the product type is unknown, throw an exception
        throw std::runtime_error("Unsupported product type");
    }
}

// Reads a product and either creates a new Product object or edits an existing one with the read data
void readProduct(Product*& product, const std::string& productType, bool isEditing = false)
{
    if(productType == "CARTE")
    {
        std::cout << "Formatul este: CANTITATE, PRET, TITLU, EDITURA, AUTORI\n";
        std::cout << "Fiecare camp se trece pe o linie separata\n";
        std::cout << "Lista autorilor se separa prin virgula\n";
        std::cout << "INTRODUCETI PRODUSUL:\n";

        // Not editing, so creating object
        if(!isEditing)
            product = new Book();
        
        std::cin >> *static_cast<Book*>(product);
    }
    else if(productType == "DVD_MUZICA")
    {
        std::cout << "Formatul este: CANTITATE, PRET, DURATA, ALBUM, ARTISTI\n";
        std::cout << "Fiecare camp se trece pe o linie separata\n";
        std::cout << "Lista artistilor se separa prin virgula\n";
        std::cout << "INTRODUCETI PRODUSUL:\n";

        if(!isEditing)
            product = new MusicDisk();

        std::cin >> *static_cast<MusicDisk*>(product);
    }
    else if(productType == "DVD_FILME")
    {
        std::cout << "Formatul este: CANTITATE, PRET, DURATA, NUME, GEN\n";
        std::cout << "Fiecare camp se trece pe o linie separata\n";
        std::cout << "INTRODUCETI PRODUSUL:\n";

        if(!isEditing)
            product = new MovieDisk();

        std::cin >> *static_cast<MovieDisk*>(product);
    }
    else if(productType == "FIGURINA")
    {
        std::cout << "Formatul este: CANTITATE, PRET, DENUMIRE, CATEGORIE, MARCA, MATERIAL\n";
        std::cout << "Fiecare camp se trece pe o linie separata\n";
        std::cout << "INTRODUCETI PRODUSUL:\n";

        if(!isEditing)
            product = new Figurine();

        std::cin >> *static_cast<Figurine*>(product);
    }
    else if(productType == "POSTER")
    {
        std::cout << "Formatul este: CANTITATE, PRET, DENUMIRE, FORMAT\n";
        std::cout << "Fiecare camp se trece pe o linie separata\n";
        std::cout << "INTRODUCETI PRODUSUL:\n";

        if(!isEditing)
            product = new Poster();

        std::cin >> *static_cast<Poster*>(product);
    }
    else
        // If it gets here, it's likely the user inputted an invalid product type 
        throw std::runtime_error("Unsupported product type");
}

// Converts a PTYPE to a string
std::string typeString(const PTYPE& ptype)
{
    switch(ptype)
    {
    case PTYPE::BOOK:
        return "CARTE";
    case PTYPE::MUSIC_DISK:
        return "DVD_MUZICA";
    case PTYPE::MOVIE_DISK:
        return "DVD_FILME";
    case PTYPE::FIGURINE:
        return "FIGURINA";
    case PTYPE::POSTER:
        return "POSTER";
    default:
        throw std::runtime_error("Unsupported product type");
    }
}

int main()
{
    // Some products added initially since it's easier to test this way
    std::vector<Product*> products = {
        new MovieDisk(15, 10.45, 120, "The Shawshank Redemption", "Drama"),
        new MovieDisk(20, 15.05, 180, "The Godfather", "Drama"),
        new MovieDisk(40, 20.55, 150, "The Dark Knight", "Action"),
        new Book(10, 10.90, "The Catcher in the Rye", "Little, Brown and Company", {"J.D. Salinger"}),
        new Book(25, 15.45, "The Great Gatsby", "Scribner", {"F. Scott Fitzgerald"}),
        new Book(35, 12.35, "To Kill a Mockingbird", "Harcourt Brace", {"Harper Lee"}),
        new MusicDisk(10, 10.85, 180, "The Dark Side of the Moon", {"Pink Floyd"}),
        new MusicDisk(40, 15.75, 180, "The Wall", {"Pink Floyd"}),
        new Figurine(30, 15.75, "The Mandalorian", "Movies", "Star Wars", "Plastic"),
        new Figurine(20, 18.35, "Darth Vader", "Movies", "Star Wars", "Plastic"),
        new Poster(5, 9.25, "Star Wars", "A3"),
        new Poster(12, 10.25, "Star Wars", "A4")
    };

    int action = 0;

    do
    {
        system("clear");
        std::cout << "MENIU INTERACTIV\n";
        std::cout << "[0]: Iesire program\n";
        std::cout << "[1]: Citire produse\n";
        std::cout << "[2]: Afisare produse\n";
        std::cout << "[3]: Editare produs\n";
        std::cout << "[4]: Ordonare produse dupa pret\n";
        std::cout << "[5]: Cautare carte dupa titlu\n";
        std::cout << "[6]: Afisare produse cu cantitate maxima\n";
        std::cout << "ALEGERE: ";
        std::cin >> action;

        bool validAction = true;

        if(action == 1)
        {
            int n;
            std::cout << "Introduceti numarul de produse: ";
            std::cin >> n;
            std::cin.get();

            for(int i = 0; i < n; i++)
            {
                system("clear");
                Product* product = nullptr;
                std::cout << "Alegeti dintre CARTE, DVD_MUZICA, DVD_FILME, FIGURINA, POSTER:\n";
                std::cout << "Tipul produsului " << i + 1 << "/" << n << ": ";
                std::string productType;
                std::getline(std::cin, productType);

                try 
                {
                    readProduct(product, productType);
                    products.push_back(product);
                }
                catch(const std::runtime_error& e)
                {
                    validAction = false;
                    std::cout << "Runtime error: " << e.what() << '\n';
                    std::cout << "Tipul de produs nu e recunoscut, nu s-a produs nicio modificare\n";
                    break;
                }
            }
        }
        else if(action == 2)
        {
            std::cout << "Avem inregistrate " << Product::getCount() << " produse\n";
            for(Product* const& product : products)
            {
                try 
                {
                    showProduct(product);
                }
                catch(const std::runtime_error& e)
                {
                    std::cout << "Runtime error: " << e.what() << '\n';
                    std::cout << "Exista un tip de produs nerecunoscut, se sare peste\n";
                }
                std::cout << '\n';
            }
        }
        else if(action == 3)
        {
            int id;
            std::cout << "Ce ID are produsul pe care il editezi: ";
            std::cin >> id;

            for(Product*& product : products)
            {
                if(product->getId() == id)
                {
                    try 
                    {
                        readProduct(product, typeString(product->typeOf()), true);
                    }
                    catch(const std::runtime_error& e)
                    {
                        std::cout << "Runtime error: " << e.what() << '\n';
                        std::cout << "Tipul de produs nu e recunoscut, nu s-a produs nicio modificare\n";
                    }
                    break;
                }
            }
        }
        else if(action == 4)
        {
            std::sort(products.begin(), products.end(),
            [](Product* const& lhs, Product* const& rhs)
            {
                // Deafult comparison of Product is by price, so it's enough just to dereference pointers here
                return *lhs < *rhs;
            });

            std::cout << "Produsele au fost sortate, afisarea lor va fi in ordine acum\n";
        }
        else if(action == 5)
        {
            std::string title;
            std::cout << "Introduceti titlul cartii pe care o cautati: ";
            std::cin.get();
            std::getline(std::cin, title);

            for(Product* const& product : products)
            {
                // If there is a type match, and then there is a title match
                // C++ shortcircuits ands, so we won't misinterpret something else as a Book
                if(product->typeOf() == PTYPE::BOOK && static_cast<Book*>(product)->getTitle() == title)
                {
                    showProduct(product);
                    std::cout << '\n';
                }
            }
        }
        else if(action == 6)
        {
            int maxQuantity = 0;

            // Find the max quantity
            for(Product* const& product : products)
            {
                maxQuantity = std::max(maxQuantity, product->getQuantity());
            }

            // For every product with the max quantity, show it
            for(Product* const& product : products)
            {
                if(product->getQuantity() == maxQuantity)
                {
                    showProduct(product);
                    std::cout << '\n';
                }
            }
        }
        else if(action == 0)
        {
            std::cout << "Se va iesi din program\n";
        }

        std::cout << "Actiune finalizata\n";
        std::cout << "Apasati orice tasta pentru a continua\n";
        std::getchar();
        std::getchar();
    } 
    while(action != 0);

    for(Product* const& product : products)
        delete product;

    return 0;
}