#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "monsters.h"

fstream file;
fstream newCastFile;
fstream menu;
ifstream namesFile;
ifstream rolesFile;
ifstream soups;
ifstream mainNormal;
ifstream mainFlex;
ifstream mainVeg;
ifstream dessert;

struct persoana {
    string name;
    string function;
};

struct menu {
    string soup;
    string mainDish;
    string dessert;
};

// imi retine ce salvez daca il las global?
persoana persoane[868];

int getBusses (int choise){
    
    if(choise == 1)
        return 868/50 + 1;
    else 
        return (868/50 + 1) * 5680 * 2; 
}

void generateMonsters(int n){

    Monster* monsters[n];
        for(int i = 0; i < n; i++){
            int random =  rand() % 5;

            Monster* monster;
            
            if (random == 0)
                monster = new Human(persoane[i].name, persoane[i].function);
            else if (random == 1)
                 monster = new Vampire(persoane[i].name, persoane[i].function);
                 else if (random == 2)
                         monster = new Werewolf(persoane[i].name, persoane[i].function);
                         else if (random == 3)
                                monster = new Siren(persoane[i].name, persoane[i].function);
                                else if (random == 4)
                                        monster = new Clairvoyant(persoane[i].name, persoane[i].function);
            
            monsters[n] = monster;
        }
}


char geLine(ifstream* FILE ){//fisier????? asa?

    int randomLine = rand() % 10;
    int numberOfLine = 0;
    string line;

    while(getline(FILE, line)){
        numberOfLine++;
        if( numberOfLine == randomLine )
            return line;
    }
}

void writeMenu(string type, string s1, string s2, string s3){

    menu << type << "\n";
    menu << "Soup:" << "," << s1 << "\n";
    menu << "Main dish:" << "," << s2 << "\n";
    menu << "Dessert:" << "," << s3 << "\n";
}

void generateMenu(){

    soups.open("soups.csv", ios::in | ios::out | ios::binary | ios::app);
    mainNormal.open("mainDishNormal.csv", ios::in | ios::out | ios::binary | ios::app);
    mainVeg.open("mainDishVeg.csv", ios::in | ios::out | ios::binary | ios::app);
    mainFlex.open("mainDishFlex.csv", ios::in | ios::out | ios::binary | ios::app);
    dessert.open("desserts.csv", ios::in | ios::out | ios::binary | ios::app);
    menu.open("Meniu.csv", ios::in | ios::out | ios::binary | ios::app);

    string goodsoup, goodn, goodv, goodf, gooddess;

    goodsoup = getline(soups);
    goodn = getline(mainNormal);
    goodv = getline(mainVeg);
    goodf = getline(mainFlex);
    gooddess = getline(dessert);

    writeMenu("Normal Menu", goodsoup, goodn, gooddess);
    writeMenu("Vegetarian Menu", goodsoup, goodv, gooddess);
    writeMenu("Flexitarian Menu", goodsoup, goodf, gooddess);


    soups.close();
    mainNormal.close();
    mainVeg.close();
    mainFlex.close();
    menu.close();
}

/*
int numberOfActorss(){
    newCastFile.open("CastFinal.csv", ios::in | ios::out | ios::binary | ios::app);

    int m = 0;
    while(!newCastFile.eof()){
        string line;
        getline(newCastFile, line);
        m++;
    }
    
    newCastFile.close();
    return m;
}

int getCantacuzino(int days){

    long cantacuzinoPerDay = 10000;
    long price = days * cantacuzinoPerDay;
    double procent;

    if(days % 10 == 0)
        procent = days/10 * 0.02;
    else procent =  days/10 * 0.02 + 0.01; 

    price = price - price * procent;

    return price;
}

void getCost(){

    int bussesCost = getBusses(2);

    

}

double leiToDollars(int lei){

    double dollars = lei / 4.68;
    return dollars;
}
*/
int main(){
    
    file.open("CastInitial.csv", ios::in);
    newCastFile.open("CastFinal.csv", ios::in | ios::out | ios::binary | ios::app);
    namesFile.open("Names.txt");
    rolesFile.open("Roles.txt");
    
    //persoana persoane[868];
    int n = 0;

    while(!file.eof()){
        string line;
        string rname, rfunction;
        getline(file, line);
        stringstream ss(line);
        getline(ss, rname, ',');
        getline(ss, rfunction, ',');
    

        if ( rfunction == "actor/actress" ){
            persoane[n].name = rname;
            persoane[n].function = rfunction;
            newCastFile << persoane[n].name << "," << persoane[n].function << "\n";
            n++;
        }
        
    }

    while(!namesFile.eof() && !rolesFile.eof()){
        string name;
        string role;
        string line;
        getline(namesFile, line);
        persoane[n].name = line;
        getline(rolesFile, line);
        persoane[n].function = line;

        newCastFile << persoane[n].name << "," << persoane[n].function << "\n";

        n++;
    } 

    ///generateMonsters(n);


    file.close();
    newCastFile.close();
    namesFile.close();
    rolesFile.close();
    return 0;
}
