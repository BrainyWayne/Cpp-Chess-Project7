#include <iostream>
#include <fstream>
#include "Opening.h"
#include "Game.h"
#include <stdlib.h>
#include <iomanip>
#include <sstream>

using namespace std;
int GetNumOpenings();
void CompareOpenings(Opening openings[], int numOpenings);
string DetectOpening(Game *game, Opening opening);
string GetString();
void Menu();
void ReadOpenings(Opening arr[], int size);
void PrintOpenings(Opening arr[], int size);


int main()
{
    Menu();
    return 0;
}
void Menu(){
    int numOpenings = 0;
    numOpenings = GetNumOpenings();

    Opening openings[numOpenings];
    ReadOpenings(openings, numOpenings);

    while(true){
        int action;
        cout<<"Print Stored Openings (1)"<<endl;
        cout<<"Load Game File (2)"<<endl;
        cout<<"Exit (0)"<<endl<<endl;
        cout<<"Enter action:";
        cin>>action;
        cin.ignore();
        cout<<endl;
        switch(action){
            case 0:
                cout<<"Exit Selected"<<endl;
                break;
            case 1:
                PrintOpenings(openings, numOpenings);
                break;
            case 2:
                CompareOpenings(openings, numOpenings);
                break;
            default:
                cout<<"Invalid Action"<<endl;
        }
        if(action == 0)break;
    }
}
string GetString(){
    string filename;
    cout<<"Please enter game filename:";
    cin>>filename;
    cin.ignore();
    return filename;
}

int GetNumOpenings(){
    ifstream infile;
    infile.open("openings.txt");
    int numOpenings;
    infile>>numOpenings;
    infile.close();
    return numOpenings;
}
void CompareOpenings(Opening openings[], int numOpenings){
    //FILL IN
    char oc;
    int ms, i;
    string filename = GetString();
    string app;
    Game* game = new Game();
    ifstream file;
    file.open("game1.txt");
    string str;
    file >> oc;
    game->outcome = oc;
    file >> ms;
    game->outcome = ms;
    while (file >> str) {
        game->moves[i++] = str;
    }
    file.close();
    string detectedOpening = "";
    for (i = 0; i < numOpenings; i++) {
        detectedOpening = DetectOpening(game, openings[i]);
        if (detectedOpening != "") {
            break;
        }
    }
    i--;
    //app = "(" + to_string(openings[i].white_percent) + to_string(openings[i].draw_percent) + to_string(openings[i].black_percent) + ")";
    cout << "Detected Opening:" << detectedOpening << "\t\t\t\t" << "(" << openings[i].white_percent << "," << openings[i].draw_percent << "," << openings[i].black_percent << ")" << "\n";

}
string DetectOpening(Game *game, Opening opening){
    //FILL IN
    string detect = "";
    bool flag = true;
    for (int i = 0; i < 3 && opening.moves[i] != ""; i++) {
        //cout << "om = " << opening.moves[i] << " gm = " << game->moves[i] << "\n";
        if (opening.moves[i] != game->moves[i]) {
            flag = false;
            break;
        }
    }
    if (flag) detect = opening.name;
    //detect += "(" + to_string(opening.white_percent) + to_string(opening.draw_percent) + to_string(opening.black_percent) + ")";
    //remove this return statement
    return detect;
}
void PrintOpenings(Opening arr[], int size){
    //FILL IN
    cout << "NAME\t\t\t\t\tMOVES\t\t\t\tWIN PERCENTAGES\t\tTIMES PLAYED\n";
    for (int i = 0; i < size; i++) {
        cout << arr[i].name << "\t\t\t\t\t";

        for (int j = 0; j < 6; j++) cout << left << setw(4) << arr[i].moves[j] << " ";
        cout << "\t";
        cout << left << setw(4) << arr[i].white_percent << "," << left << setw(4) << arr[i].draw_percent << "," << left << setw(4) << arr[i].black_percent << "\t\t";
        cout << arr[i].official << "\n";
    }
}
void ReadOpenings(Opening arr[], int size){
    //FILL IN
    string str;
    stringstream ss;
    int ign;
    ifstream infile;
    infile.open("openings.txt");
    //if (infile.good()) cout << "Good\n";
    getline(infile, str);
    cout << "size = " << size << "\n";
    for (int i = 0; i < size; i++) {
        getline(infile, str);
        arr[i].name = str;
        getline(infile, str);
        ign = stoi(str);
        getline(infile, str);
        ss << str;
        for (int j = 0; j < ign; j++)
            ss >> arr[i].moves[j];
        getline(infile, str);
        arr[i].official = str;
        getline(infile, str);
        ss << str;
        ss >> arr[i].white_percent;
        ss >> arr[i].draw_percent;
        ss >> arr[i].black_percent;
    }
    infile.close();
}