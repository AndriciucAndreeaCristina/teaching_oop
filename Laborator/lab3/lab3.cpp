#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>


class Masina
{

    std::string marca;
    std::string model;
    bool disponibila;
public:

    Masina(const std::string &m, const std::string &mod, bool disp)
    {
        marca = m;
        model = mod;
        disponibila = disp;
    }
    void setMarca(const std::string &newMarca)
    {
        marca = newMarca;
    }
    void setModel(const std::string &newModel)
    {
        model = newModel;
    }
    void setDisponibila(bool newDisponibila)
    {
        disponibila = newDisponibila;
    }
    std::string getMarca() const
    {
        return marca;
    }
    std::string getModel() const
    {
        return model;
    }
    bool isDisponibila() const
    {
        return disponibila;
    }
};
class Client
{
    std::string nume;
    int id;
    std::vector<Masina> masiniInchiriate;
public:


    Client(const std::string &n, int i)
    {
        nume = n;
        id = i;
    }
    void setNume(const std::string &newNume)
    {
        nume = newNume;
    }
    void setId(int newId)
    {
        id = newId;
    }
    void adaugaMasina(const Masina &masina)
    {
        masiniInchiriate.push_back(masina);
    }
    void setMasiniInchiriate(const std::vector<Masina> &masini)
    {
        masiniInchiriate = masini;
    }
    std::string getNume() const
    {
        return nume;
    }
    int getId() const
    {
        return id;
    }
    std::vector<Masina> getMasiniInchiriate() const
    {
        return masiniInchiriate;
    }
    int getNumarMasiniInchiriate() const
    {
        return masiniInchiriate.size();
    }
};
class Agentie
{

    std::vector<Masina> masini;
    std::vector<Client> clienti;
public:
    Agentie() { }
    Agentie(const std::vector<Masina> &m, const std::vector<Client> &c)
    {
        masini = m;
        clienti = c;
    }

    void setMasini(const std::vector<Masina> &m)
    {
        masini = m;
    }
    void setClienti(const std::vector<Client> &c)
    {
        clienti = c;
    }
    void adaugaMasina(const Masina &masina)
    {
        masini.push_back(masina);
    }
    void adaugaClient(const Client &client)
    {
        clienti.push_back(client);
    }
    std::vector<Masina> getMasini() const
    {
        return masini;
    }
    std::vector<Client> getClienti() const
    {
        return clienti;
    }
};



int doarcifre(const std::string &prompt) // Functie  pentru citirea unui nr valid
{
    std::string input;
    int num;
    bool valid = false;

    while (!valid)
    {
        std::cout << prompt;
        std::cin >> input;

        valid = true;
        for (int i = 0; i < input.length(); i++)
        {
            if (!isdigit(input[i]))
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            num = 0;
            for (int i = 0; i < input.length(); i++)
            {
                num = num * 10 + (input[i] - '0');
            }
        }
        else
        {
            std::cout << "Input invalid. Va rugam sa introduceti doar cifre.\n";
        }
    }

    return num;
}



std::string doarlitere(const std::string &prompt) //Functie pt citirea unui sir valid
{
    std::string str;
    while (true)
    {
        std::cout << prompt;
        std::cin >> str;
        bool valid = true;
        for (char c : str)
        {
            if (!std::isalpha(c))
            {
                valid = false;
                break;
            }
        }
        if (valid)
            break;
        else
            std::cout << "Input invalid. Va rugam sa introduceti doar litere.\n";
    }
    return str;
}






void loadAgentie(Agentie &agentie) // incarcare info in fisier
{
    std::ifstream fin("data.out");
    if (!fin.is_open())
    {
        std::cout << "Fisierul data.out nu a putut fi deschis. Se va crea unul nou la salvare.\n";
        return;
    }
    std::string header;
    fin >> header;
    if (header != "Masini")
    {
        std::cout << "Fisierul are format incorect.\n";
        fin.close();
        return;
    }
    int nrMasini;
    fin >> nrMasini;
    std::vector<Masina> masini;
    for (int i = 0; i < nrMasini; i++)
    {
        std::string marca, model;
        int disp;
        fin >> marca >> model >> disp;
        masini.push_back(Masina(marca, model, (disp == 1))); // Cream obiectul Masina si il adaugam in vector
    }
    agentie.setMasini(masini);

    fin >> header;
    if (header != "Clienti")
    {
        std::cout << "Fisierul are format incorect.\n";
        fin.close();
        return;
    }
    int nrClienti;
    fin >> nrClienti;
    std::vector<Client> clienti;
    for (int i = 0; i < nrClienti; i++)
    {
        std::string nume;
        int id, nrMasiniInchiriate;
        fin >> nume >> id >> nrMasiniInchiriate;
        Client client(nume, id);
        for (int j = 0; j < nrMasiniInchiriate; j++)  // Pentru fiecare masina inchiriata de client, citim detaliile si o adaugam in lista clientului
        {
            std::string marca, model;
            int disp;
            fin >> marca >> model >> disp;
            client.adaugaMasina(Masina(marca, model, (disp == 1)));
        }
        clienti.push_back(client);
    }
    agentie.setClienti(clienti);
    fin.close();
}


void saveAgentie(const Agentie &agentie) //salvare date dupa rulare
{
    std::ofstream fout("data.out");
    if (!fout.is_open())
    {
        std::cout << "Nu s-a putut deschide fisierul pentru salvare.\n";
        return;
    }
    std::vector<Masina> masini = agentie.getMasini(); // Obtinem lista de masini din agentie
    fout << "Masini\n" << masini.size() << "\n";
    for (size_t i = 0; i < masini.size(); i++) // Parcurgem fiecare masina si scriem detaliile acesteia in fisier
    {
        fout << masini[i].getMarca() << " "<< masini[i].getModel() << " "<< (masini[i].isDisponibila() ? 1 : 0) << "\n";
    }
    std::vector<Client> clienti = agentie.getClienti(); // Obtinem lista de clienti din agentie
    fout << "Clienti\n" << clienti.size() << "\n";
    for (size_t i = 0; i < clienti.size(); i++)   // Parcurgem fiecare client
    {
        fout << clienti[i].getNume() << " "<< clienti[i].getId() << " "<< clienti[i].getNumarMasiniInchiriate() << "\n";
        std::vector<Masina> masiniClient = clienti[i].getMasiniInchiriate();
        for (size_t j = 0; j < masiniClient.size(); j++)  // Parcurgem fiecare masina inchiriata si scriem detaliile acesteia in fisier
        {
            fout << masiniClient[j].getMarca() << " "<< masiniClient[j].getModel() << " "<< (masiniClient[j].isDisponibila() ? 1 : 0) << "\n";
        }
    }
    fout.close();
}

void afisareMasiniDisponibile(const Agentie &agentie)
{
    std::cout << "\nMasini disponibile pentru inchiriere:\n";
    std::vector<Masina> masini = agentie.getMasini();
    for (size_t i = 0; i < masini.size(); i++)
    {
        if (masini[i].isDisponibila())
            std::cout << masini[i].getMarca() << " " << masini[i].getModel() << "\n";
    }
}


void adaugareMasina(Agentie &agentie)
{
    std::string marca = doarlitere("\nIntroduceti marca masinii: ");
    std::string model;
    std::cout << "Introduceti modelul masinii: ";
    std::cin >> model;
    Masina m(marca, model, true);
    agentie.adaugaMasina(m);
    std::cout << "Masina a fost adaugata.\n";
    saveAgentie(agentie);
}


void stergereMasina(Agentie &agentie)
{
    std::string marca = doarlitere("\nIntroduceti marca masinii de sters: ");
    std::string model;
    std::cout << "Introduceti modelul masinii de sters: ";
    std::cin >> model;
    std::vector<Masina> masini = agentie.getMasini();
    bool gasita = false;
    for (size_t i = 0; i < masini.size(); )
    {
        if (masini[i].getMarca() == marca && masini[i].getModel() == model)
        {
            masini.erase(masini.begin() + i);
            gasita = true;
            std::cout << "Masina a fost stearsa.\n";
            break;
        }
        else
        {
            i++;
        }
    }
    if (!gasita)
        std::cout << "Masina nu a fost gasita.\n";
    agentie.setMasini(masini);
    saveAgentie(agentie);
}


void afisareMasiniClient(Agentie &agentie)
{
    std::vector<Client> clienti = agentie.getClienti();
    if (clienti.empty()) // Verificăm dacă lista de clienți este goală
    {
        std::cout << "Nu exista clienti in sistem.\n";
        return;
    }
    std::cout << "Clientii disponibili:\n";
    for (size_t i = 0; i < clienti.size(); i++) // Afișăm toți clienții disponibili, cu ID-ul și numele fiecăruia
    {
        std::cout << "ID: " << clienti[i].getId()<< " - Nume: " << clienti[i].getNume() << "\n";
    }
    int id = doarcifre("\nIntroduceti ID-ul clientului: ");
    bool gasit = false;
    for (size_t i = 0; i < clienti.size(); i++) // Parcurgem lista de clienți pentru a găsi clientul cu ID-ul introdus
    {
        if (clienti[i].getId() == id)
        {
            int nrMasini = clienti[i].getNumarMasiniInchiriate(); // Obținem numărul de mașini închiriate de clientul respectiv
            std::cout << "Clientul " << clienti[i].getNume()<< " a inchiriat " << nrMasini << " "<< (nrMasini == 1 ? "masina" : "masini") << ".\n";
            gasit = true;
            std::string raspuns;
            std::cout << "Afisam masinile inchiriate de clientul "<< clienti[i].getNume() << "? (da/nu): ";
            std::cin >> raspuns;
            if (raspuns == "da" || raspuns == "Da" || raspuns == "DA")
            {
                std::vector<Masina> masiniClient = clienti[i].getMasiniInchiriate();
                for (size_t j = 0; j < masiniClient.size(); j++)
                {
                    std::cout << "Masina " << j + 1 << ": "<< masiniClient[j].getMarca() << " "<< masiniClient[j].getModel() << "\n";
                }
            }
            break;
        }
    }
    if (!gasit)
        std::cout << "Clientul cu ID-ul " << id << " nu a fost gasit.\n";
}


void adaugareClient(Agentie &agentie)
{
    std::string nume = doarlitere("\nIntroduceti numele clientului: ");
    int newId = 1;
    std::vector<Client> clienti = agentie.getClienti();
    // Parcurgem lista de clienți și stabilim newId ca fiind mai mare decât orice id existent
    for (size_t i = 0; i < clienti.size(); i++) //generare id client nou
    {
        if (clienti[i].getId() >= newId)
            newId = clienti[i].getId() + 1;
    }
    Client client(nume, newId); // Creăm obiectul Client cu numele și id-ul generat
    std::cout << "Clientul " << nume << " a fost salvat cu id-ul " << newId << ".\n";
    std::string raspuns;
    std::cout << "Adaugam vreo masina la acesta? (da/nu): ";
    std::cin >> raspuns;
    if (raspuns == "da" || raspuns == "Da" || raspuns == "DA")
    {
        std::string adaugaMaiMulte; // am schimbat de la char la string
        // Ciclu do-while pentru a permite adăugarea mai multor mașini
        do
        {
            std::vector<Masina> allMasini = agentie.getMasini(); // creare vector local cu masini
            std::vector<int> availableIndices;
            std::cout << "Masinile disponibile:\n";
            int counter = 1;
            for (size_t i = 0; i < allMasini.size(); i++) // Parcurgem lista de mașini și afișăm doar cele disponibile
            {
                if (allMasini[i].isDisponibila())
                {
                    std::cout << counter << ". "<< allMasini[i].getMarca() << " "<< allMasini[i].getModel() << "\n";
                    availableIndices.push_back(i);
                    counter++;
                }
            }
            if (availableIndices.empty())
            {
                std::cout << "Nu exista masini disponibile.\n";
                break;
            }
            int index = doarcifre("Introduceti indexul masinii pe care doriti sa o adaugati la client: ");
            if (index < 1 || index > static_cast<int>(availableIndices.size()))
            {
                std::cout << "Index invalid.\n";
            }
            else
            {
                int masinaIndex = availableIndices[index - 1];  // Obținem indexul real al mașinii în vectorul de mașini
                std::vector<Masina> masiniAgentie = agentie.getMasini();
                masiniAgentie[masinaIndex].setDisponibila(false); // Marcăm mașina ca indisponibilă deoarece va fi închiriată de client
                agentie.setMasini(masiniAgentie); // Actualizăm lista de mașini în agenție
                client.adaugaMasina(masiniAgentie[masinaIndex]); // Adăugăm mașina selectată la lista de mașini închiriate de client
                std::cout << "Masina "<< masiniAgentie[masinaIndex].getMarca() << " "<< masiniAgentie[masinaIndex].getModel()<< " a fost adaugata clientului " << nume << ".\n";
            }
            std::cout << "Doriti sa adaugati o alta masina? (da/nu): ";
            std::cin >> adaugaMaiMulte;
        }
        while (adaugaMaiMulte == "da" || adaugaMaiMulte == "Da" || adaugaMaiMulte == "DA");
    }
    agentie.adaugaClient(client);
    saveAgentie(agentie);
}


void stergereClient(Agentie &agentie)
{
    std::vector<Client> clienti = agentie.getClienti();
    if (clienti.empty())
    {
        std::cout << "Nu exista clienti in sistem.\n";
        return;
    }
    std::cout << "Clientii disponibili:\n";
    for (size_t i = 0; i < clienti.size(); i++)
    {
        std::cout << "ID: " << clienti[i].getId()
                  << " - Nume: " << clienti[i].getNume() << "\n";
    }
    int id = doarcifre("Introduceti ID-ul clientului de sters: ");
    bool gasit = false;
    std::vector<Client> clientiUpdated;
    for (size_t i = 0; i < clienti.size(); i++)
    {
        if (clienti[i].getId() == id)
        {
            gasit = true;
            std::vector<Masina> rentedCars = clienti[i].getMasiniInchiriate(); // creare vector nou cu masini inchiriate de un anumit client
            std::vector<Masina> masiniAgentie = agentie.getMasini(); // creare vector cu lista masinilor disponibile
            for (size_t j = 0; j < rentedCars.size(); j++) // facem toate masinile inchiriate de client inapoi disponibile in flota
            {
                for (size_t k = 0; k < masiniAgentie.size(); k++)
                {
                    if (masiniAgentie[k].getMarca() == rentedCars[j].getMarca() && masiniAgentie[k].getModel() == rentedCars[j].getModel())
                    {
                        masiniAgentie[k].setDisponibila(true);
                        break;
                    }
                }
            }
            agentie.setMasini(masiniAgentie);
            std::cout << "Clientul cu ID-ul " << id << " a fost sters.\n";
        }
        else
        {
            clientiUpdated.push_back(clienti[i]);
        }
    }
    if (!gasit)
        std::cout << "Clientul cu ID-ul " << id << " nu a fost gasit.\n";
    else
        agentie.setClienti(clientiUpdated);
    saveAgentie(agentie);
}


void stergereMasinaDeLaClient(Agentie &agentie)
{
    std::vector<Client> clienti = agentie.getClienti();
    if (clienti.empty())
    {
        std::cout << "Nu exista clienti in sistem.\n";
        return;
    }
    std::cout << "Clientii disponibili:\n";
    for (size_t i = 0; i < clienti.size(); i++)
    {
        std::cout << "ID: " << clienti[i].getId()<< " - Nume: " << clienti[i].getNume() << "\n";
    }
    int id = doarcifre("Introduceti ID-ul clientului: ");
    bool clientFound = false;
    std::vector<Client> allClients = agentie.getClienti();
    for (size_t i = 0; i < allClients.size(); i++) // Parcurgem lista de clienți pentru a găsi clientul cu ID-ul specificat
    {
        if (allClients[i].getId() == id)
        {
            clientFound = true;
            std::vector<Masina> rentedCars = allClients[i].getMasiniInchiriate(); // Obținem lista de mașini inchiriate de client
            if (rentedCars.empty())
            {
                std::cout << "Clientul nu are masini inchiriate.\n";
            }
            else
            {
                std::cout << "Masinile inchiriate de clientul "<< allClients[i].getNume() << ":\n";
                for (size_t j = 0; j < rentedCars.size(); j++)
                {
                    std::cout << j + 1 << ". "<< rentedCars[j].getMarca() << " "<< rentedCars[j].getModel() << "\n";
                }
                int index = doarcifre("Introduceti indexul masinii pe care doriti sa o stergeti: ");
                if (index < 1 || index > static_cast<int>(rentedCars.size())) // Verificăm dacă indexul introdus este valid
                {
                    std::cout << "Index invalid.\n";
                }
                else
                {
                    Masina carToRemove = rentedCars[index - 1]; // Salvăm mașina care urmează să fie ștearsă pentru a putea actualiza starea acesteia în flota agenției
                    rentedCars.erase(rentedCars.begin() + (index - 1)); // Ștergem mașina din lista mașinilor inchiriate de client

                    allClients[i].setMasiniInchiriate(rentedCars); // Actualizăm lista de mașini inchiriate a clientului
                    agentie.setClienti(allClients);
                    std::vector<Masina> allCars = agentie.getMasini(); // Obținem lista completă de mașini din agenție pentru a actualiza starea mașinii
                    bool updated = false;
                    for (size_t k = 0; k < allCars.size(); k++) // Parcurgem lista de mașini pentru a găsi mașina respectivă și a o marca ca disponibila
                    {
                        if (!allCars[k].isDisponibila() && allCars[k].getMarca() == carToRemove.getMarca() && allCars[k].getModel() == carToRemove.getModel())

                        {
                            allCars[k].setDisponibila(true);
                            updated = true;
                            break;
                        }
                    }
                    if (updated)
                    {
                        agentie.setMasini(allCars);
                        std::cout << "Masina a fost stearsa de la clientul "
                                  << allClients[i].getNume() << ".\n";
                    }
                    else
                    {
                        std::cout << "Nu s-a putut actualiza starea masinii in flota.\n";
                    }
                }
            }
            break;
        }
    }
    if (!clientFound)
        std::cout << "Clientul cu ID-ul " << id << " nu a fost gasit.\n";
    saveAgentie(agentie);
}


void adaugareMasinaLaClient(Agentie &agentie)
{
    std::vector<Client> clienti = agentie.getClienti();
    if (clienti.empty())
    {
        std::cout << "Nu exista clienti in sistem.\n";
        return;
    }
    std::cout << "Clientii disponibili:\n";
    for (size_t i = 0; i < clienti.size(); i++)
    {
        std::cout << "ID: " << clienti[i].getId()<< " - Nume: " << clienti[i].getNume() << "\n";
    }
    int clientId = doarcifre("Introduceti ID-ul clientului la care doriti sa adaugati o masina: ");
    bool clientFound = false;
    int clientIndex = -1;
    for (size_t i = 0; i < clienti.size(); i++) // Căutăm clientul în lista de clienți
    {
        if (clienti[i].getId() == clientId)
        {
            clientFound = true;
            clientIndex = i;
            break;
        }
    }
    if (!clientFound)
    {
        std::cout << "Clientul cu ID-ul " << clientId << " nu a fost gasit.\n";
        return;
    }


    std::vector<Masina> masini = agentie.getMasini(); // Obtinem lista de mașini din agenție
    std::vector<int> availableIndices;
    std::cout << "Masinile disponibile:\n";
    int counter = 1;
    for (size_t j = 0; j < masini.size(); j++)
    {
        if (masini[j].isDisponibila())
        {
            std::cout << counter << ". " << masini[j].getMarca()<< " " << masini[j].getModel() << "\n";
            availableIndices.push_back(j);
            counter++;
        }
    }
    if (availableIndices.empty()) // Dacă nu există mașini disponibile, afișăm un mesaj
    {
        std::cout << "Nu exista masini disponibile in flota.\n";
        return;
    }
    int carOption = doarcifre("Introduceti indexul masinii pe care doriti sa o adaugati la client: ");
    if (carOption < 1 || carOption > static_cast<int>(availableIndices.size()))
    {
        std::cout << "Index invalid.\n";
        return;
    }
    int carIndex = availableIndices[carOption - 1];

    // Marcăm mașina ca indisponibilă și o adăugăm la client
    masini[carIndex].setDisponibila(false);
    agentie.setMasini(masini);
    clienti[clientIndex].adaugaMasina(masini[carIndex]);

    // Actualizăm lista de clienți în agenție
    std::vector<Client> allClients = agentie.getClienti();
    for (size_t i = 0; i < allClients.size(); i++)
    {
        if (allClients[i].getId() == clientId)
        {
            allClients[i] = clienti[clientIndex];
            break;
        }
    }
    agentie.setClienti(allClients);

    std::cout << "Masina " << masini[carIndex].getMarca() << " " << masini[carIndex].getModel()<< " a fost adaugata clientului " << clienti[clientIndex].getNume() << ".\n";
    saveAgentie(agentie);
}


void menu()
{
    Agentie agentie;
    loadAgentie(agentie);
    int mainOption = 0;
    do
    {
        std::cout << "\n----- Meniu Principal -----\n";
        std::cout << "1. Afisare masini disponibile\n";
        std::cout << "2. Operatii masini\n";
        std::cout << "3. Operatii clienti\n";
        std::cout << "4. Operatii masini clienti\n";
        std::cout << "5. Iesire\n";
        mainOption = doarcifre("Optiune: ");
        switch (mainOption)
        {
        case 1:
            afisareMasiniDisponibile(agentie);
            break;
        case 2:
        {
            int subOption = 0;
            do
            {
                std::cout << "\n----- Operatii masini -----\n";
                std::cout << "1. Adaugare masina\n";
                std::cout << "2. Stergere masina din flota\n";
                std::cout << "3. Revenire la meniul principal\n";
                subOption = doarcifre("Optiune: ");
                switch (subOption)
                {
                case 1:
                    adaugareMasina(agentie);
                    break;
                case 2:
                    stergereMasina(agentie);
                    break;
                case 3:
                    std::cout << "Revenire la meniul principal...\n";
                    break;
                default:
                    std::cout << "Optiune invalida.\n";
                    break;
                }
            }
            while (subOption != 3);
            break;
        }
        case 3:
        {
            int subOption = 0;
            do
            {
                std::cout << "\n----- Operatii clienti -----\n";
                std::cout << "1. Adaugare client\n";
                std::cout << "2. Stergere client\n";
                std::cout << "3. Revenire la meniul principal\n";
                subOption = doarcifre("Optiune: ");
                switch (subOption)
                {
                case 1:
                    adaugareClient(agentie);
                    break;
                case 2:
                    stergereClient(agentie);
                    break;
                case 3:
                    std::cout << "Revenire la meniul principal...\n";
                    break;
                default:
                    std::cout << "Optiune invalida.\n";
                    break;
                }
            }
            while (subOption != 3);
            break;
        }
        case 4:
        {
            int subOption = 0;
            do
            {
                std::cout << "\n----- Operatii masini clienti -----\n";
                std::cout << "1. Afisare masini inchiriate de un client\n";
                std::cout << "2. Stergere masina de la client\n";
                std::cout << "3. Adaugare masina la client existent\n";
                std::cout << "4. Revenire la meniul principal\n";
                subOption = doarcifre("Optiune: ");
                switch (subOption)
                {
                case 1:
                    afisareMasiniClient(agentie);
                    break;
                case 2:
                    stergereMasinaDeLaClient(agentie);
                    break;
                case 3:
                    adaugareMasinaLaClient(agentie);
                    break;
                case 4:
                    std::cout << "Revenire la meniul principal...\n";
                    break;
                default:
                    std::cout << "Optiune invalida.\n";
                    break;
                }
            }
            while (subOption != 4);
            break;
        }
        case 5:
            std::cout << "Iesire din program...\n";
            break;
        default:
            std::cout << "Optiune invalida. Incercati din nou.\n";
            break;
        }
    }
    while (mainOption != 5);
    saveAgentie(agentie);
}

int main()
{
    menu();
    return 0;
}






