#ifndef BASEBALLSTATS_H
#define BASEBALLSTATS_H
#include <iostream>

using namespace std;
///Create player struct
struct Player{
    string name;
    string team;
    string position;
    double OBP;
    double battingAverage;
    int atBats;
    int hits;
    int walks;
    int strikeouts;
    Player *next;
    Player *previous;
};
///Create team struct
struct Team{
    string name;
    int numPlayers;
    Team *next;
    Team *previous;
    Player *player;
};

class BaseballStats
{
    public:
        BaseballStats();
        virtual ~BaseballStats();
        void addTeam(string teamName);///Add a team
        void removeTeam(string teamName);///Remove a team
        void addPlayer(string teamName, string playerName, int atBats, int hits, int walks, int strikeouts,string position);///Add a player
        void editPlayerStats(string teamName, string playerName, int atBats, int hits, int walks, int strikeouts);///Edit a player
        void calculateBattingAverage(Player *player);///Calculate players Batting Average
        void calculateOBP(Player *player); ///Calculate players On Base Percentage
        void printTeamStats(string teamName);///Print the team stats
        void printTop10();///Print the top 10
        void printTeams();///Print the teams in the league
        bool checkTeamExists(string teamName);///Check if team exists
		void menu();//menu
		void choiceDisplay(std::string header, std::string aContent = NULL);//show user what to choose
    protected:
    private:
        Team *head = NULL;
        Player *top10[10];
};

#endif // BASEBALLSTATS_H
