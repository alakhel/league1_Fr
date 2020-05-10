#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <dirent.h>
#include <algorithm>
#include "Match.h"
#include "Equipe.h"

using namespace std;
#define USAGE()                                                                                                                                              \
    {                                                                                                                                                        \
        printf("Usage: %s -d <databaseFolder> [-j buts|buts/match][-e points|victoires|defaites|nuls|attaque|defense|goalaverage][-n <nombre>]\n", argv[0]); \
        exit(1);                                                                                                                                             \
    }

/**
 * DataStructers 
 */
vector<Equipe> Equipe::Equipes;                 //static list will contains teams
vector<Joueur> Joueur::Joueurs;                 //static list will contains players
equiSORT Equipe::sortedBy = equiSORT::POINTS;   //sort criteria for teams, initialized with POINTS
joueurSORT Joueur::sortedBy = joueurSORT::BUTS; //sort criteria for players, initialized with BUTS
int main(int argc, char *argv[])
{
    /**
     * Configuration variables
     */
    int maxAffichage = 10;      // max printed result, by default 10.
    bool afficheEquipe = false; //will print team list or not, by default no.
    bool afficheJoueur = false; //will print players list or not, by default no.
    string databaseFolder = "";

    /**
     * Software execution parameters
     */
    char opt;
    while ((opt = getopt(argc, argv, "d:j:e:n:")) != -1)
    {
        switch (opt)
        {
        case 'd': //database
            databaseFolder = optarg;
            break;
        case 'j': //player options
            if (string(optarg) == "buts")
                Joueur::sortedBy = joueurSORT::BUTS;
            else if (string(optarg) == "buts/match")
                Joueur::sortedBy = joueurSORT::BUTSMATCH;
            else
                USAGE();
            afficheJoueur = true;
            break;
        case 'e': //team options
            if (string(optarg) == "points")
                Equipe::sortedBy = equiSORT::POINTS;
            else if (string(optarg) == "victoires")
                Equipe::sortedBy = equiSORT::VICTOIRES;
            else if (string(optarg) == "defaites")
                Equipe::sortedBy = equiSORT::DEFAITES;
            else if (string(optarg) == "nuls")
                Equipe::sortedBy = equiSORT::NULS;
            else if (string(optarg) == "attaque")
                Equipe::sortedBy = equiSORT::ATTAQUE;
            else if (string(optarg) == "defense")
                Equipe::sortedBy = equiSORT::DEFENSE;
            else if (string(optarg) == "goalaverage")
                Equipe::sortedBy = equiSORT::GOALAVERAGE;
            else
                USAGE();
            afficheEquipe = true;
            break;
        case 'n': // set max print
            maxAffichage = atoi(optarg);
            if (maxAffichage > 0)
                break;
            USAGE();
        default:
            USAGE();
        }
    }

    if (databaseFolder.empty()) // set the database param as mandatory
        USAGE();
    if (!afficheJoueur && !afficheEquipe) // if the user didn't lunch the software with -e & -j, print this and quit
    {
        cout << "La base de données est chargé correctement" << endl;
        return 0;
    }

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(databaseFolder.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            string files = ent->d_name;
            //check if it's a Jxx.txt file
            regex regexDoc("^J[[:digit:]][[:digit:]].txt$");
            if (!regex_search(files, regexDoc))
                continue; // will ignore the file if its not Jxx.txt
            string path = databaseFolder + '/' + string(ent->d_name);
            ifstream istrm(path);
            if (istrm.is_open())
            {
                int maxLine = 0;
                for (string line; getline(istrm, line) && maxLine < 10; maxLine++) //parse line by line, until 10.
                {
                    if (line.length() < 10) // if the software find a line that contains less than 10c will print error
                    {
                        cerr << "Erreur, ligne vide ou incomplete" << endl;
                        exit(1);
                    }
                    Match m{};
                    m << line;
                }
            }
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
    if (Equipe::Equipes.size() == 0 && Joueur::Joueurs.size() == 0)
    {
        cerr << "La base de données est vide!" << endl;
        cerr << "vérifier que vous avez des fichiers sous format Jxx.txt, ou xx correspond à des chiffres." << endl;
        return 1;
    }

    //Check if we have to print team or not
    if (afficheEquipe)
    {
        Equipe::sortEquipes();
        Equipe::print(maxAffichage);
    }
    //Check if we have to print player or not
    if (afficheJoueur)
    {
        Joueur::sortJoueurs();
        Joueur::print(maxAffichage);
    }

    cout << endl;
}
