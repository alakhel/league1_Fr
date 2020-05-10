
#include "Joueur.h"
#include <regex>
Joueur::Joueur() {}
Joueur::Joueur(string name, string nomEquipe)
{
    this->setName(name);
    this->setnomEquipe(nomEquipe);
    this->setButs(1);
}
Joueur::Joueur(const Joueur &j)
{
    this->setName(j.getName());
    this->setButs(j.getButs());
    this->setnomEquipe(j.getnomEquipe());
}
Joueur &Joueur::operator=(const Joueur &j)
{
    if (this != &j)
    {
        this->setName(j.getName());
        this->setButs(j.getButs());
        this->setnomEquipe(j.getnomEquipe());
    }
    return *this;
}
Joueur::~Joueur() {}
float Joueur::getRatio() const
{
    return static_cast<float>(this->getButs()) / static_cast<float>(Equipe::findNombreMatchesByName(this->getnomEquipe()));
}
bool Joueur::estContreSonCamp(string joueurName)
{
    regex csc("(CSC.)");
    smatch result;
    return regex_search(joueurName, result, csc);
}
void Joueur::sortJoueurs()
{
    auto sortComparator = [](Joueur const &joueur, Joueur const &joueurNext) -> bool {
        switch (Joueur::sortedBy)
        {
        case joueurSORT::BUTS:
            if (joueur.getButs() != joueurNext.getButs())
                return joueur.getButs() > joueurNext.getButs();
            return joueur.getName() < joueurNext.getName();
            break;
        case joueurSORT::BUTSMATCH:
            if (joueur.getRatio() != joueurNext.getRatio())
                return joueur.getRatio() > joueurNext.getRatio();
            return joueur.getName() < joueurNext.getName();
            break;
        default:
            return joueur.getName() < joueurNext.getName();
            break;
        }
    };
    sort(Joueur::Joueurs.begin(), Joueur::Joueurs.end(), sortComparator);
}
void Joueur::print(int maxAffichage)
{
    map<joueurSORT, string> enumToString = {
        {joueurSORT::BUTS, "buts"},
        {joueurSORT::BUTSMATCH, "buts/match"}};
    cout << endl
         << "Liste des joueurs : trié par " << enumToString[Joueur::sortedBy] << endl;
    cout << setfill(' ') << left << setw(4) << "#";
    cout << setfill(' ') << left << setw(30) << "nom Joueur";

    cout << setfill(' ') << right << setw(6) << enumToString[Joueur::sortedBy] << endl;

    int i = 0;
    for (auto it = Joueur::Joueurs.cbegin(); it != Joueur::Joueurs.cend() && ++i <= maxAffichage; it++)
    {
        cout << setfill(' ') << left << setw(4) << i;
        cout << *it;
        auto aux = it;
        aux++;
        while (it->getButs() == aux->getButs() && i >= maxAffichage && aux != Joueur::Joueurs.cend()) //ce code n'exécute pas, que si maxAffichag est déja atteint
        {
            cout << setfill(' ') << left << setw(4) << ++i;
            cout << *aux;
            aux++;
        }
    }
}
std::ostream &operator<<(std::ostream &print, const Joueur &j)
{
    print << setfill(' ') << left << setw(30) << j.getName() + " (" + j.getnomEquipe() + ")";
    switch (Joueur::sortedBy)
    {
    case joueurSORT::BUTS:
        print << setfill(' ') << right << setw(6) << j.getButs();
        break;
    case joueurSORT::BUTSMATCH:
        print << setfill(' ') << left << setw(6) << setprecision(2) << j.getRatio();
        break;
    default:
        cerr << "critères d'affichage non trouvés" << endl;
    }
    print << endl;
    return print;
}

Joueur &Joueur::operator++(int)
{
    this->Buts++;
    return *this;
}
void Joueur::estJoueurExist(string joueurName, string nomEquipe)
{
    if (!Joueur::estContreSonCamp(joueurName))
    {
        auto it = Joueur::Joueurs.begin();
        for (; it != Joueur::Joueurs.end(); it++)
            if (*it == joueurName)
                break;

        if (it != Joueur::Joueurs.end())
        {
            it->setButs(it->getButs() + 1);
        }
        else
        {
            Joueur j(joueurName, nomEquipe);
            Joueur::Joueurs.push_back(j);
        }
    }
}
bool Joueur::operator==(const string &nomJoueur) const
{
    return this->getName() == nomJoueur;
}
