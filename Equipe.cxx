#include "Equipe.h"
Equipe::Equipe() {}
Equipe::~Equipe() {}
Equipe::Equipe(string name, int selfScore, int advScore)
{
    this->setName(name);
    this->setAttaque(selfScore);
    this->setDefense(advScore);
    this->setNombreMatches(1);
    this->setGoalaverage(selfScore - advScore);
    if (selfScore > advScore)
    {
        this->setPoints(3);
        this->setVictoires(1);
        this->setNuls(0);
        this->setDefaites(0);
    }
    else if (selfScore == advScore)
    {
        this->setPoints(1);
        this->setVictoires(0);
        this->setNuls(1);
        this->setDefaites(0);
    }
    else
    {
        this->setPoints(0);
        this->setVictoires(0);
        this->setNuls(0);
        this->setDefaites(1);
    }
}
Equipe::Equipe(const Equipe &e)
{
    this->setName(e.getName());
    this->setPoints(e.getPoints());
    this->setVictoires(e.getVictoires());
    this->setDefaites(e.getDefaites());
    this->setNuls(e.getNuls());
    this->setDefense(e.getDefense());
    this->setAttaque(e.getAttaque());
    this->setGoalaverage(e.getGoalaverage());
    this->setNombreMatches(e.getNombreMatches());
}
Equipe &Equipe::operator=(const Equipe &e)
{
    if (this != &e)
    {
        this->setName(e.getName());
        this->setPoints(e.getPoints());
        this->setVictoires(e.getVictoires());
        this->setDefaites(e.getDefaites());
        this->setNuls(e.getNuls());
        this->setDefense(e.getDefense());
        this->setAttaque(e.getAttaque());
        this->setGoalaverage(e.getGoalaverage());
        this->setNombreMatches(e.getNombreMatches());
    }
    return *this;
}
void Equipe::playedMatch(int selfScore, int advScore)
{
    this->setNombreMatches(this->getNombreMatches() + 1);
    this->setAttaque(this->getAttaque() + selfScore);
    this->setDefense(this->getDefense() + advScore);
    if (selfScore > advScore)
        ++*this;
    else if (selfScore == advScore)
        this->ajoutNul();
    else
        --*this;
    this->setGoalaverage(this->getAttaque() - this->getDefense());
}
int Equipe::findNombreMatchesByName(string nomEquipe)
{
    auto it = Equipe::Equipes.begin();
    for (; it != Equipe::Equipes.end(); it++)
        if (*it == nomEquipe)
            break;
    if (it != Equipe::Equipes.cend())
        return it->getNombreMatches();
    return -1;
}
void Equipe::estEquipeExist(string nomEquipe, int selfScore, int advScore)
{
    auto it = Equipe::Equipes.begin();
    for (; it != Equipe::Equipes.end(); it++)
        if (*it == nomEquipe)
            break;
    if (it != Equipe::Equipes.end())
    {
        it->playedMatch(selfScore, advScore);
    }
    else
    {
        Equipe equipe(nomEquipe, selfScore, advScore);
        Equipe::Equipes.push_back(equipe);
    }
}
void Equipe::sortEquipes()
{
    auto sortComparator = [](Equipe const &equipe, Equipe const &equipeNext) -> bool {
        switch (Equipe::sortedBy)
        {
        case equiSORT::POINTS:
            if (equipe.getPoints() != equipeNext.getPoints())
                return equipe.getPoints() > equipeNext.getPoints();
            return equipe.getName() < equipeNext.getName();
            break;
        case equiSORT::VICTOIRES:
            if (equipe.getVictoires() != equipeNext.getVictoires())
                return equipe.getVictoires() > equipeNext.getVictoires();
            return equipe.getName() < equipeNext.getName();
            break;
        case equiSORT::DEFAITES:
            if (equipe.getDefaites() != equipeNext.getDefaites())
                return equipe.getDefaites() < equipeNext.getDefaites();
            return equipe.getName() < equipeNext.getName();
            break;
        case equiSORT::NULS:
            if (equipe.getNuls() != equipeNext.getNuls())
                return equipe.getNuls() > equipeNext.getNuls();
            return equipe.getName() < equipeNext.getName();
            break;
        case equiSORT::ATTAQUE:
            if (equipe.getAttaque() != equipeNext.getAttaque())
                return equipe.getAttaque() > equipeNext.getAttaque();
            return equipe.getName() < equipeNext.getName();
            break;
        case equiSORT::DEFENSE:
            if (equipe.getDefense() != equipeNext.getDefense())
                return equipe.getDefense() > equipeNext.getDefense();
            return equipe.getName() < equipeNext.getName();
            break;
        case equiSORT::GOALAVERAGE:
            if (equipe.getGoalaverage() != equipeNext.getGoalaverage())
                return equipe.getGoalaverage() > equipeNext.getGoalaverage();
            return equipe.getName() < equipeNext.getName();
            break;
        default:
            return equipe.getName() < equipeNext.getName();
            break;
        }
    };
    sort(Equipe::Equipes.begin(), Equipe::Equipes.end(), sortComparator);
}
void Equipe::print(int maxAffichage)
{
    int i = 0;
    map<equiSORT, string> enumToString = {
        {equiSORT::POINTS, "points"},
        {equiSORT::ATTAQUE, "attaque"},
        {equiSORT::VICTOIRES, "victoires"},
        {equiSORT::DEFENSE, "defense"},
        {equiSORT::DEFAITES, "defaites"},
        {equiSORT::GOALAVERAGE, "goalaverage"},
        {equiSORT::NULS, "nuls"},
    };
    cout << endl
         << "Liste des equipes : trié par "
         << enumToString[Equipe::sortedBy]
         << endl;
    cout << setfill(' ') << left << setw(3) << "#";
    cout << setfill(' ') << left << setw(14) << "Nom d'Equipe";
    cout << setfill(' ') << left << setw(11) << enumToString[Equipe::sortedBy] << endl;

    for (auto it = Equipe::Equipes.cbegin(); it != Equipe::Equipes.cend() && ++i <= maxAffichage; it++)
    {
        cout << setfill(' ') << left << setw(3) << i;
        cout << " " << *it;
        auto aux = it;
        aux++;
        //mauvaise version
        while (it->getPoints() == aux->getPoints() && i >= maxAffichage)
            //la bonne version
            while (it->getPoints() == aux->getPoints() && i >= maxAffichage && aux != Equipe::Equipes.cend()) //ce code n'exécute pas, que si maxAffichag est déja atteint
            {
                cout << setfill(' ') << left << setw(3) << ++i;
                cout << " " << *aux;
                aux++;
            }
    }
}
std::ostream &operator<<(std::ostream &print, const Equipe &equipe)
{
    print << setfill(' ') << left << setw(14) << equipe.getName();
    switch (Equipe::sortedBy)
    {
    case equiSORT::POINTS:
        cout << setfill(' ') << left << setw(11) << equipe.getPoints();
        break;
    case equiSORT::VICTOIRES:
        cout << setfill(' ') << left << setw(11) << equipe.getVictoires();
        break;
    case equiSORT::DEFAITES:
        cout << setfill(' ') << left << setw(11) << equipe.getDefaites();
        break;
    case equiSORT::NULS:
        cout << setfill(' ') << left << setw(11) << equipe.getNuls();
        break;
    case equiSORT::ATTAQUE:
        cout << setfill(' ') << left << setw(11) << equipe.getAttaque();
        break;
    case equiSORT::DEFENSE:
        cout << setfill(' ') << left << setw(11) << equipe.getDefense();
        break;
    case equiSORT::GOALAVERAGE:
        cout << setfill(' ') << left << setw(11) << equipe.getGoalaverage();
        break;
    default:
        cerr << "critères d'affichage non trouvés" << endl;
    }
    cout << endl;

    return print;
}
void Equipe::ajoutVictoire()
{
    this->setVictoires(this->getVictoires() + 1);
    this->setPoints(this->getPoints() + 3);
}
void Equipe::ajoutDefaite()
{
    this->setDefaites(this->getDefaites() + 1);
}
void Equipe::ajoutNul()
{
    this->setNuls(this->getNuls() + 1);
    this->setPoints(this->getPoints() + 1);
}
Equipe &Equipe::operator++()
{
    this->setVictoires(this->getVictoires() + 1);
    this->setPoints(this->getPoints() + 3);
    return *this;
}

Equipe &Equipe::operator--()
{
    this->setDefaites(this->getDefaites() + 1);
    return *this;
}
bool Equipe::operator==(const string &nomEquipe) const
{
    return this->getName() == nomEquipe;
}
