#ifndef JOUEUR_H
#define JOUEUR_H
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include "Equipe.h"
#include <iomanip>
using namespace std;
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
enum class joueurSORT
{
    BUTS,
    BUTSMATCH,
};
class Joueur
{

public:
    //Constructor without arguement
    Joueur();
    /**
     * Constructor @param playerName, @param TeamName
     */
    Joueur(string, string);
    //copy constructor
    Joueur(const Joueur &);
    //assignement operator
    Joueur &operator=(const Joueur &);
    //destrutor
    ~Joueur();
    // table of all players, shared over instances
    static vector<Joueur> Joueurs;
    // sorting criteria
    static joueurSORT sortedBy;
    /**
     * check if we have already a player x instance.
     * @param string playerName, string teamName
     */
    static void estJoueurExist(string, string);
    /**
     * check if the player is CSC
     */
    static bool estContreSonCamp(string);
    /**
     * sorting methode
     * @param none, but use a static attribute \sortedBy
     */
    static void sortJoueurs();
    /**
     * print all players stored in the static vector
     * @param int numbre of result to be printed
     */
    static void print(int);

    // calculate ratio
    float getRatio() const;
    // print operator
    friend std::ostream &operator<<(std::ostream &, const Joueur &);
    // add one goal
    Joueur &operator++(int);
    //compare two players object using playerName
    bool operator==(const string &) const;
    // Attributes, Getters, Setters
    SetGetMacro(Name, string);
    SetGetMacro(Buts, int);
    SetGetMacro(nomEquipe, string);
};
#endif