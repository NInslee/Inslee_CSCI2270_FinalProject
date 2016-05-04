#include <iostream>
#include "BaseballStats.h"

int main()
{
    ///Create instance of the class
    BaseballStats League;
    bool quit = false;
	std::string choice;

    while(!quit){//keep running the program until user wants to quit.
		League.menu();//display menu
		getline(std::cin, choice);
        if(choice == "1"){
            std::string teamName;
            League.choiceDisplay("Add Team", "Enter Team Name: ");//ask user for team name
			getline(std::cin, teamName);
            League.addTeam(teamName);
        }
        else if(choice == "2"){
            std::string teamName;
            League.choiceDisplay("Remove Team", "Enter Team Name: ");
			getline(std::cin, teamName);
            League.removeTeam(teamName);
        }
        else if(choice == "3"){
			std::string teamName;
            League.choiceDisplay("Edit Team", "Enter Team Name: ");
			getline(std::cin, teamName);
            bool teamExists = League.checkTeamExists(teamName);//check if team exists
			std::string choice;
			bool returnBack = false;
            if(teamExists){
                std::string playerName;
                std::string position;
                int hits;
                int atBats;
                int strikeouts;
                int walks;
				while(!returnBack){
					League.choiceDisplay("Edit Team", "1. Add Player\n2. Edit Player Stats\n3. Back");
					getline(std::cin, choice);
					if(choice == "1" || choice == "2"){
						std::cout<<"======Add Player======\n";
						///Receive user inputs
						std::cout<<"Enter Player Name:\n";
						getline(std::cin, playerName);
						if(choice == "1"){
                            std::cout<<"Enter Player Position(P,C,1B,2B,SS,3B,LF,CF,RF):\n";
                            getline(std::cin, position);
						}
						std::cout<<"Enter Number of Hits:\n";
						std::cin>>hits;
						std::cout<<"Enter Number of At Bats:\n";
						std::cin>>atBats;
						std::cout<<"Enter Number of Strikeouts:\n";
						std::cin>>strikeouts;
						std::cout<<"Enter Number of Walks:\n";
						std::cin>>walks;
						///Run class function
						if(choice == "1"){
                            League.addPlayer(teamName,playerName,atBats,hits,walks,strikeouts,position);
                        }
                        else{
                            League.editPlayerStats(teamName,playerName,atBats,hits,walks,strikeouts);
                        }
					}
                    else if(choice == "3"){
                        returnBack == true;
                        League.menu();//show the menu
                    }
				}
            }
            ///If team does not exist
            else{
                std::cout<<"Sorry, team does not exist\n";
			}
        }
        else if(choice == "4"){
            std::string teamName;
            League.choiceDisplay("Check Team Stats", "Enter Team Name: ");
			getline(std::cin, teamName);
            League.printTeamStats(teamName);
        }
        else if(choice == "5"){
            std::cout<<"======Top 10======\n";
            League.printTop10();
        }
        else if(choice == "6"){
            std::cout<<"==Teams in League==\n";
            League.printTeams();
        }
		else if(choice == "7"){
			quit == true;
			std::cout << "Goodbye!\n";
		}
		else{
			std::cout <<"Wrong choice.\n";
		}
    }
	return 0;
}
