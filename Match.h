#ifndef MATCH_H
#define MATCH_H
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include "Equipe.h"
#include "Joueur.h"

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
typedef struct t_equipe
{
    string nomEquipe;
    int nbuts;                            // goals scored
    vector<pair<string, string>> butteur; // player , minute
} t_equipe;

class Match
{
public:
    Match();
    //copy constructor
    Match(const Match &);
    //assignement operator
    Match &operator=(const Match &);
    //destructor
    ~Match();
    void operator<<(string);
    //get teams names
    string getNomEquipeHost() const;
    string getNomEquipeGuest() const;

    // print operator
    friend std::ostream &operator<<(std::ostream &, const Match &);

private:
    /**
     *  helper func : analyse & get data from a string
     *  @param searchCriteria, @param target 
     *  @return result found
     */
    string parse(string, string &);
    // Attributes, Getters, Setters
    SetGetMacro(EquipeHost, t_equipe);
    SetGetMacro(EquipeGuest, t_equipe);
};
#endif
