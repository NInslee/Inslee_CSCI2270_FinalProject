#include <iostream>
#include "BaseballStats.h"

using namespace std;

void menuDisplay();
void choice1Display();
void choice2Display();
void choice3Display1();
void choice3Display2();
void choice4Display();

int main()
{
    ///Create instance of the class
    BaseballStats League;
    ///Initialize variables
    int menuChoice = 0;
    int menuChoice2 = 0;
    while(menuChoice != 7){//fixed this for your eyes
        ///If choice 1
        if(menuChoice == 1){
            ///Initialize variable
            string teamName;
            ///Display for choice 1
            choice1Display();
            ///Receive user input
            getline(cin, teamName);
            getline(cin, teamName);
            ///Run class function
            League.addTeam(teamName);
        }
        ///If choice 2
        else if(menuChoice == 2){
            ///Initialize variable
            string teamName;
            ///Display for choice 2
            if (!League.leagueIsEmpty()) { //checks before you remove if its empty
                choice2Display();
                ///Receive user input
                getline(cin, teamName);
                getline(cin, teamName);
                ///Run class function
                League.removeTeam(teamName);
            } else {
                cout << "There are no teams in this league." << endl;
            }
        }
        ///If choice 3
        else if(menuChoice == 3){
            ///Initialize variable
            string teamName;
            bool teamExists = true;
            ///First display asking for a team to edit
            if (!League.leagueIsEmpty()) {//checks if league is empty
                choice3Display1();
                ///Receive user input
                getline(cin, teamName);
                getline(cin, teamName);
                if (League.checkTeamExists(teamName)) { //checks if team exists
                    teamExists = false;
                }
                else {
                    cout << "Team does not exist." << endl;
                }
            } else {
                cout << "There are no teams in this league." << endl;
            }
            
            ///If the team exists
            if(!teamExists){
                while(menuChoice2 == 0 || menuChoice2 == 1 || menuChoice2 == 2){
                    ///If choice from edit menu is 1
                    if(menuChoice2 == 1){
                        ///Display
                        cout<<"======Add Player======"<<endl;
                        ///Initialize variables
                        string playerName;
                        string position;
                        int hits;
                        int atBats;
                        int strikeouts;
                        int walks;
                        ///Receive user inputs
                        cout<<"Enter Player Name:"<<endl;
                        getline(cin, playerName);
                        getline(cin, playerName);
                        cout<<"Enter Player Position(P,C,1B,2B,SS,3B,LF,CF,RF):"<<endl;
                        getline(cin, position);
                        cout<<"Enter Number of Hits:"<<endl;
                        cin>>hits;
                        cout<<"Enter Number of At Bats:"<<endl;
                        cin>>atBats;
                        cout<<"Enter Number of Strikeouts:"<<endl;
                        cin>>strikeouts;
                        cout<<"Enter Number of Walks:"<<endl;
                        cin>>walks;
                        ///Run class function
                        League.addPlayer(teamName,playerName,atBats,hits,walks,strikeouts,position);
                    }
                    ///If choice from edit menu is 2
                    else if(menuChoice2 == 2){
                        ///Display
                        cout<<"===Edit Player Stats==="<<endl;
                        ///Initialize variables
                        string playerName;
                        int hits;
                        int atBats;
                        int strikeouts;
                        int walks;
                        ///Receive user inputs
                        cout<<"Enter Player Name:"<<endl;
                        getline(cin, playerName);
                        getline(cin, playerName);
                        if (League.checkPlayExists(playerName, teamName)) { //makes sure player is there before you ask for stuff
                            cout<<"Enter New At Bats:"<<endl;
                            cin>>atBats;
                            cout<<"Enter New Hits:"<<endl;
                            cin>>hits;
                            cout<<"Enter New Strikeouts:"<<endl;
                            cin>>strikeouts;
                            cout<<"Enter New Walks:"<<endl;
                            cin>>walks;
                            ///Run class function
                            League.editPlayerStats(teamName,playerName,atBats,hits,walks,strikeouts);
                        } else { //player wasnt found
                            cout << "There is no one by the name " << playerName;
                            cout << " on the team " << teamName << "." << endl;
                        }
                    }
                    ///Display main display for choice 3
                    choice3Display2();
                    cin>>menuChoice2;
                }
                ///Reset variable to 0 so the loop can run again
                menuChoice2 = 0;
            }

        }
        ///If choice 4
        else if(menuChoice == 4){
            ///Initialize variable
            string teamName;
            ///Display for choice 4
            choice4Display();
            ///Receive user input
            getline(cin, teamName);
            getline(cin, teamName);
            ///Run class function if team exists
            if (League.checkTeamExists(teamName)) {
                League.printTeamStats(teamName);
            } else {
                cout << teamName << " does not exist." << endl;
            }
        }
        ///If choice 5
        else if(menuChoice == 5){
            ///Display
            cout<<"======Top 10======"<<endl;
            ///Run class function
            League.printTop10();
        }
        ///If choice 6
        else if(menuChoice == 6){
            ///Display
            cout<<"==Teams in League=="<<endl;
            ///Run class function
            League.printTeams();
        }
        ///Display main menu
        menuDisplay();
        ///Receive user input
        cin>>menuChoice;
    }
    
    cout << "Goodbye!" << endl;//:) be nice... lol
}
///Display main menu
void menuDisplay(){
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Add team"<<endl;
    cout<<"2. Remove team"<<endl;
    cout<<"3. Edit team"<<endl;
    cout<<"4. Check team stats"<<endl;
    cout<<"5. View top 10 players"<<endl;
    cout<<"6. View teams in league"<<endl;
    cout<<"7. Quit"<<endl;
}
///Display for choice 1
void choice1Display(){
    cout<<"======Add Team======"<<endl;
    cout<<"Enter Team Name:"<<endl;
}
///Display for choice 2
void choice2Display(){
    cout<<"=====Remove Team====="<<endl;
    cout<<"Enter Team Name:"<<endl;
}
///First display for choice 3
void choice3Display1(){
    cout<<"======Edit Team======"<<endl;
    cout<<"Enter Team Name:"<<endl;
}
///Second display for choice 3
void choice3Display2(){
    cout<<"======Edit Team======"<<endl;
    cout<<"1. Add player"<<endl;
    cout<<"2. Edit player stats"<<endl;
    cout<<"3. Back"<<endl;
}
///Display for choice 4
void choice4Display(){
    cout<<"===Check Team Stats==="<<endl;
    cout<<"Enter Team Name:"<<endl;
}
