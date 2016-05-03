#include "BaseballStats.h"

BaseballStats::BaseballStats()
{
    ///Initialize the array of Top 10
    for(int i=0; i<10; i++){
        Player *startingPlayer = new Player;
        startingPlayer->battingAverage = 0;
        startingPlayer->OBP = 0;
        startingPlayer->atBats = 0;
        startingPlayer->hits = 0;
        startingPlayer->strikeouts = 0;
        startingPlayer->walks = 0;
        startingPlayer->name = "No Player";
        startingPlayer->team = " ";
        startingPlayer->next = NULL;
        startingPlayer->previous = NULL;
        top10[i] = startingPlayer;
    }
}

BaseballStats::~BaseballStats()
{
    //dtor
}
void BaseballStats::addTeam(string teamName){
    ///Create new variables to search and add
    Team *temp = head;
    Team *newTeam = new Team;
    newTeam->name = teamName;
    newTeam->numPlayers = 0;
    newTeam->next = NULL;
    newTeam->previous = NULL;
    newTeam->player = NULL;
    ///Check if temp(head) is NULL
    if(temp == NULL){
        ///Set head to the team being added
        head = newTeam;
    }
    ///If temp(head) is not NULL
    else{
        ///Loop to reach the end of the Team list
        while(temp->next != NULL){
            temp = temp->next;
        }
        ///Insert new team at the end
        temp->next = newTeam;
        newTeam->previous = temp;
    }
}

void BaseballStats::removeTeam(string teamName){
    ///Create variable to search the team list
    Team *temp = head;
    bool found = false;//tells the user if the team they inputted exists
        
    while(temp != NULL){
        ///Check if the name of temp is the wanted name
        if(temp->name == teamName){
            found = true;
            ///Reset temp's previous and next variables to take it out
            if(temp == head){
                if(temp->next == NULL){
                    head = NULL;
                }
                else{
                    temp->next->previous = NULL;
                    head = temp->next;
                }
            }
            else{
                if(temp->next == NULL){
                    temp->previous->next = NULL;
                }
                else{
                    temp->next->previous = temp->previous;
                    temp->previous->next = temp->next;
                }
            }
            ///Delete temp
            delete temp;
            cout << teamName << " has been removed." << endl;//tells user what happened 
            break;
        }
        temp = temp->next;
    }
    
    if (!found) { //checks if a team was removed (team name existed)
        cout << "There is no team by the name '" << teamName << "'." << endl;
    }
    
}

void BaseballStats::addPlayer(string teamName, string playerName, int atBats, int hits, int walks, int strikeouts, string position){
    ///Create new player with attributes given by the user
    Player *newPlayer = new Player;
    newPlayer->name = playerName;
    newPlayer->team = teamName;
    newPlayer->position = position;
    newPlayer->atBats = atBats;
    newPlayer->hits = hits;
    newPlayer->walks = walks;
    newPlayer->strikeouts = strikeouts;
    newPlayer->next = NULL;
    newPlayer->previous = NULL;
    ///Calculate the BA and OBP
    calculateBattingAverage(newPlayer);
    calculateOBP(newPlayer);
    ///Create search variable to find the team
    Team *temp = head;
    ///Loop to find team
    while(temp != NULL){
        if(temp->name == teamName){
            break;
        }
        temp = temp->next;
    }
    ///Create Player search variable equal to the team->player
    Player *temp2 = temp->player;
    ///Check if temp2 variable is NULL
    if(temp2 == NULL){
        ///Set the team->player to new player
        temp->player = newPlayer;
    }
    ///If temp2 is not NULL
    else{
        ///Search through the list of players
        while(temp2 != NULL){
            ///If the BA of new player is greater than the current player
            if(newPlayer->battingAverage > temp2->battingAverage){
                if(temp->player == temp2){
                    temp->player = newPlayer;
                    temp2->previous = newPlayer;
                    newPlayer->next = temp2;
                }
                else{
                    newPlayer->previous = temp2->previous;
                    temp2->previous->next = newPlayer;
                    temp2->previous = newPlayer;
                    newPlayer->next = temp2;
                }
                break;
            }
            ///If the BA of new player is equal to the current player
            else if(newPlayer->battingAverage == temp2->battingAverage){
                ///Check if new player's OBP is greater as a tie breaker
                if(newPlayer->OBP > temp2->OBP){
                    if(temp->player == temp2){
                        temp->player = newPlayer;
                        temp2->previous = newPlayer;
                        newPlayer->next = temp2;
                    }
                    else{
                        newPlayer->previous = temp2->previous;
                        temp2->previous->next = newPlayer;
                        temp2->previous = newPlayer;
                        newPlayer->next = temp2;
                    }
                    break;
                }
            }
            temp2 = temp2->next;
        }
        ///If the new player didn't fit anywhere in the list, puts it at the end
        if(newPlayer->next == NULL && newPlayer->previous == NULL){
            temp2 = temp->player;
            while(temp2->next != NULL){
                temp2 = temp2->next;
            }
            temp2->next = newPlayer;
            newPlayer->previous = temp2;
        }
    }
    temp->numPlayers++;
    ///Check if the new player belongs in the Top 10
    for(int i=0; i<10; i++){
        if(top10[i]->name == "No Player"){
            top10[i] = newPlayer;
            break;
        }
        else if(top10[i]->battingAverage < newPlayer->battingAverage){
            for(int j=10; j>i; j--){
                top10[j] = top10[j-1];
            }
            top10[i] = newPlayer;
            break;
        }
        else if(top10[i]->battingAverage == newPlayer->battingAverage){
            if(top10[i]->OBP < newPlayer->OBP){
                for(int j=10; j>i; j--){
                    top10[j] = top10[j-1];
                }
                top10[i] = newPlayer;
                break;
            }
        }
    }
}

void BaseballStats::editPlayerStats(string teamName, string playerName, int atBats, int hits, int walks, int strikeouts){
    ///Find team
    Team *temp = head;
    while(temp != NULL){
        if(temp->name == teamName){
            break;
        }
        temp = temp->next;
    }
    ///Find player
    Player *temp2 = temp->player;
    while(temp2 != NULL){
        if(temp2->name == playerName){
            break;
        }
        temp2 = temp2->next;
    }
    
    ///Update player stats
    temp2->atBats = temp2->atBats + atBats;
    temp2->hits = temp2->hits + hits;
    temp2->walks = temp2->walks + walks;
    temp2->strikeouts = temp2->strikeouts + strikeouts;
    calculateBattingAverage(temp2);
    calculateOBP(temp2);
    ///Remove player from the list to have him reinserted to the correct spot
    if(temp2 == temp->player){
        temp->player = temp2->next;
        temp2->next->previous = NULL;
    }
    else if(temp2->next == NULL){
        temp2->previous->next = temp2->next;
    }
    else{
        temp2->previous->next = temp2->next;
        temp2->next->previous = temp2->previous;
    }
    ///Remove from Top 10 array if he is in it
    for(int i=0; i<10; i++){
        if(top10[i]->name == temp2->name){
            for(int j=i+1; j<10; j++){
                top10[j-1] = top10[j];
            }
            break;
        }
    }
    ///Find the new player to fill the bottom slot until player is re-added
    temp = head;
    Player *highestPlayer = new Player;
    Player *stockPlayer = new Player;
    stockPlayer->battingAverage = 0;
    stockPlayer->OBP = 0;
    stockPlayer->atBats = 0;
    stockPlayer->hits = 0;
    stockPlayer->strikeouts = 0;
    stockPlayer->walks = 0;
    stockPlayer->name = "Stock";
    stockPlayer->team = " ";
    stockPlayer->next = NULL;
    stockPlayer->previous = NULL;
    top10[9] = stockPlayer;
    while(temp != NULL){
        highestPlayer = temp->player;
        while(highestPlayer != NULL){
            if(highestPlayer->battingAverage < top10[8]->battingAverage && highestPlayer->battingAverage > top10[9]-> battingAverage){
                top10[9] = highestPlayer;
            }
            else if(highestPlayer->battingAverage == top10[8]->battingAverage && highestPlayer->OBP < top10[8]->OBP){
                top10[9] = highestPlayer;
            }
            highestPlayer = highestPlayer->next;
        }
        temp = temp->next;
    }
    ///Re-add the updated player to the team
    addPlayer(temp2->team, temp2->name, temp2->atBats, temp2->hits, temp2->walks, temp2->strikeouts, temp2->position);
    delete temp2;
    
}

void BaseballStats::calculateBattingAverage(Player *player){
    if(player->atBats == 0){
        player->battingAverage = 0;
    }
    ///Calculate BA by dividing hits by at bats
    else{
        player->battingAverage = player->hits/(double)player->atBats;
    }
}

void BaseballStats::printTeamStats(string teamName){
    ///Find team
    Team *temp = head;
    while(temp != NULL){
        if(temp->name == teamName){
            break;
        }
        temp = temp->next;
    }
    cout<<"-----"<<temp->name<<"-----"<<endl;
    Player *temp2 = temp->player;
    ///Print each player with their stats
    while(temp2 != NULL){
        cout<<temp2->name<<"("<<temp2->position<<"):"<<temp2->team<<" - BA: "<<temp2->battingAverage<<", OBP: "<<temp2->OBP<<", K: "<<temp2->strikeouts<<", BB: "<<temp2->walks<<endl;
        temp2 = temp2->next;
    }
}

void BaseballStats::printTop10(){
    ///Print contents of Top 10
    for(int i=0; i<10; i++){
        cout<<top10[i]->name<<"("<<top10[i]->position<<"):"<<top10[i]->team<<" - BA: "<<top10[i]->battingAverage<<", OBP: "<<top10[i]->OBP<<", K: "<<top10[i]->strikeouts<<", BB: "<<top10[i]->walks<<endl;
    }
}

void BaseballStats::printTeams(){
    ///Print all the teams in the league with their number of players
    Team *temp = head;
    if(temp == NULL){
        cout<<"No teams in league"<<endl;
    }
    while(temp != NULL){
        if(temp->numPlayers == 1){
            cout<<temp->name<<" : "<<temp->numPlayers<<" Player"<<endl;
        }
        else{
            cout<<temp->name<<" : "<<temp->numPlayers<<" Players"<<endl;
        }
        temp = temp->next;
    }
}

void BaseballStats::calculateOBP(Player *player){
    double OBP;
    int plateAppearances;
    int onBase;
    ///Find plate appearances by adding at bats with walks
    plateAppearances = player->atBats + player->walks;
    ///Find on base by adding the hits with walks
    onBase = player->hits + player->walks;
    if(plateAppearances == 0){
        OBP = 0;
    }
    ///Calculate OBP by dividing on base by plate appearances
    else{
        OBP = onBase/(double)plateAppearances;
    }
    player->OBP = OBP;
}

bool BaseballStats::leagueIsEmpty() {
    if (head == NULL) {
        return true; //if there are teams the function returns true
    }
    return false;
}

bool BaseballStats::checkPlayExists(string playerName, string teamName) {
    
    Team *temp = head;
    
    while (temp->name != teamName) {//I can use this check because we know the team exists
        temp = temp->next;
    }
    
    Player *find = temp->player;
    
    while (find != NULL) {
        if (find->name == playerName) {
            return true;
        }
    }
    return false;
    
}

bool BaseballStats::checkTeamExists(string teamName){
    ///Search through the teams to find if the team name exists
    bool check = false;
    Team *temp = head;
    while(temp != NULL){
        if(temp->name == teamName){
            check = true;
            break;
        }
        temp = temp->next;
    }
    return check;
}
