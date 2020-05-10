#include "Match.h"
using namespace std;

Match::Match() {}
Match::~Match() {}
Match::Match(const Match &m)
{
    this->EquipeHost = m.EquipeHost;
    this->EquipeGuest = m.EquipeGuest;
}
Match &Match::operator=(const Match &m)
{
    if (this != &m)
    {
        this->EquipeHost = m.EquipeHost;
        this->EquipeGuest = m.EquipeGuest;
    }
    return *this;
}
string Match::parse(string criteria, string &target)
{
    try
    {
        smatch result;
        regex regex(criteria);
        regex_search(target, result, regex);
        string res = result.str();
        target = result.suffix().str();
        return res;
    }
    catch (const std::regex_error &error)
    {
        std::cerr << error.what() << '\n';
        cout << "an error occured";
        exit(1);
    }
}
/**
 * manage to add data parsed from line, to static lists.
 * @param line a parsed line from the file
 * @return void 
 */
void Match::operator<<(string line)
{
    regex regexFormat("^ *[a-zA-Z-]+ *: *[a-zA-Z-]+ *[[:d:]]+ *- *[[:d:]]+ *(([a-zA-Z-]+ *\\. *[a-zA-Z-]+ *[[:d:]]+ *\\/?) *)*:? *(([a-zA-Z-]+ *\\. *[a-zA-Z-]+ *[[:d:]]+ *\\/?) *)*$");
    if (!regex_search(line, regexFormat))
    {
        cerr << "Format invalide: " << line << endl;
        exit(1);
    }
    this->EquipeHost.nomEquipe = this->parse("[a-zA-Z-]+", line);
    this->parse("(:)([[:s:]]*)", line);

    this->EquipeGuest.nomEquipe = this->parse("[a-zA-Z-]+", line);
    /***/
    try
    {
        this->EquipeHost.nbuts = stoi(this->parse("([[:d:]])", line));
        this->EquipeGuest.nbuts = stoi(this->parse("([[:d:]])", line));
    }
    catch (const exception &err)
    {
        cout << "Match score conversion error : \n"
             << err.what() << endl;
    }
    Equipe::estEquipeExist(this->EquipeHost.nomEquipe, this->EquipeHost.nbuts, this->EquipeGuest.nbuts);
    Equipe::estEquipeExist(this->EquipeGuest.nomEquipe, this->EquipeGuest.nbuts, this->EquipeHost.nbuts);
    /**
     * @butteur
     */
    string regexJoueur = "([a-zA-Z-]+ *\\. *[a-zA-Z-]+)";
    regex rgx("([[:s:]]*)(\\.)([[:s:]]*)");
    for (int i = 0; i < this->EquipeHost.nbuts; i++)
    {
        string joueurName = regex_replace(this->parse(regexJoueur, line), rgx, ". ");
        Joueur::estJoueurExist(joueurName, this->EquipeHost.nomEquipe);
        this->EquipeHost.butteur.push_back(make_pair(joueurName, this->parse("[[:d:]]+", line)));
    }

    for (int i = 0; i < this->EquipeGuest.nbuts; i++)
    {
        string joueurName = regex_replace(this->parse(regexJoueur, line), rgx, ". ");
        Joueur::estJoueurExist(joueurName, this->EquipeGuest.nomEquipe);
        this->EquipeGuest.butteur.push_back(make_pair(joueurName, this->parse("[[:d:]]+", line)));
    }
}
string Match::getNomEquipeHost() const
{
    return this->EquipeHost.nomEquipe;
}
string Match::getNomEquipeGuest() const
{
    return this->EquipeGuest.nomEquipe;
}
std::ostream &operator<<(std::ostream &print, const Match &match)
{
    print << match.getNomEquipeHost()
          << " " << match.EquipeHost.nbuts
          << " - " << match.EquipeGuest.nbuts
          << " " << match.getNomEquipeGuest();

    if (match.EquipeHost.butteur.size() > 0)
    {
        print << "\n\tButteur";
        if (match.EquipeHost.butteur.size() > 1)
            print << "s";
        print << " " << match.EquipeHost.nomEquipe << " : ";
    }
    for (auto it = match.EquipeHost.butteur.begin(); it != match.EquipeHost.butteur.end(); it++)
        print << it->first << " (" << it->second << ") ";
    if (match.EquipeGuest.butteur.size() > 0)
    {
        print << "\n\tButteur";
        if (match.EquipeGuest.butteur.size() > 1)
            print << "s";
        print << " " << match.EquipeGuest.nomEquipe << " : ";
    }

    for (auto it = match.EquipeGuest.butteur.begin(); it != match.EquipeGuest.butteur.end(); it++)
        print << it->first << " (" << it->second << ") ";
    print << "\n";
    return print;
}
