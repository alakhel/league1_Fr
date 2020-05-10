#ifndef EQUIPE_H
#define EQUIPE_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <functional>
#define SetGetMacro(name, type) \
private:                        \
    type name;                  \
                                \
public:                         \
    type get##name() const      \
    {                           \
        return this->name;      \
    };                          \
    void set##name(type value)  \
    {                           \
        this->name = value;     \
    }

using namespace std;
enum class equiSORT
{
    POINTS,
    VICTOIRES,
    DEFAITES,
    NULS,
    ATTAQUE,
    DEFENSE,
    GOALAVERAGE
};
class Equipe
{
public:
    //Constructor without argument
    Equipe();
    /**
     * Constructor : @param string teamName, int selfScore, int adversaireScore
     */
    Equipe(string, int, int);
    //copy constructor
    Equipe(const Equipe &);
    //assignement operator
    Equipe &operator=(const Equipe &);
    //destructor
    ~Equipe();
    // table of all teams, shared over instances
    static vector<Equipe> Equipes;
    // sorting criteria
    static equiSORT sortedBy;
    /**
     * check if we have already a team x instance.
     * @param teamName, @param selfScore, @param advScore
     */
    static void estEquipeExist(string, int, int);
    /**
     * get number of played match by a team
     * @param string teamName
     * @return int nPlayedMatch
     */
    static int findNombreMatchesByName(string);
    /**
     * sorting methode
     * @param none, but use a static attribute \sortedBy
     */
    static void sortEquipes();
    /**
     * print all teams stored in the static vector
     * @param int numbre of result to be printed
     */
    static void print(int);

    /**
     * used to update team data depending on a new played match result
     * @param int selfScore, int adversaireScore
     */
    void playedMatch(int, int);
    // will change attributes; points+3, victoires+1, nombreMatches+1
    void ajoutVictoire();
    // will change attributes; defaites+1, nombreMatches+1
    void ajoutDefaite();
    // will change attributes; points+1, nuls+1, nombreMatches+1
    void ajoutNul();
    //print operator
    friend std::ostream &operator<<(std::ostream &, const Equipe &);
    //compare two team Objects based on teamName
    bool
    operator==(const string &) const;
    //act as ajoutVictoie()
    Equipe &operator++();
    //act as ajoutVictoie()
    Equipe &operator--();

    // Attributes, Getters, Setters
    SetGetMacro(Name, string);
    SetGetMacro(NombreMatches, int);
    SetGetMacro(Points, int);
    SetGetMacro(Victoires, int);
    SetGetMacro(Defaites, int);
    SetGetMacro(Nuls, int);
    SetGetMacro(Attaque, int);
    SetGetMacro(Defense, int);
    SetGetMacro(Goalaverage, int);
};
#endif