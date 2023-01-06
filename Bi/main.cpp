#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#include "monsters.h"

fstream file;
fstream newCastFile;
fstream menu;
ifstream namesFile;
ifstream rolesFile;

struct persoana {
    string name;
    string function;
};

struct menu {
    string soup;
    string mainDish;
    string dessert;
};


persoana persoane[868];

float getBusses(int choise) {
    if (choise == 1)
        return 868 / 50 + 1;
    else
        return (868 / 50 + 1) * 5680 * 2;
}

// Generate random monsters (Human,)
vector<Monster *> generateMonsters(int n) {
    vector<Monster *> monsters;
    for (int i = 0; i < n; i++) {
        int random = rand() % 5;

        // Create a monster
        Monster *monster;

        // create a new monster based on the random number and add it to the vector (new Human(persoane[i].name, persoane[i].function))
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

        // add the monster to the vector
        monsters.push_back(monster);
    }
    // return an array of monsters
    return monsters;
}

// make generateMonsters() return an array of monsters
// and then call the function in main

string getLine(string numeFisier) {

    ifstream randomFileLiner;
    randomFileLiner.open(numeFisier, ios::in);
    int randomLine = rand() % 10;
    int numberOfLine = 0;
    string line;
    cout << "ok\n";

    while (getline(randomFileLiner, line)) {
        numberOfLine++;
        cout << "mmm\n";
        if (numberOfLine == randomLine)
            return line;
    }

    randomFileLiner.close();
}

void writeMenu(string type, string s1, string s2, string s3, int ok, int i, int choise) {

    menu.open("Meniu.csv", ios::in | ios::out | ios::binary | ios::app);

    if (choise == 1){

        if(ok == 0) 
            menu << "Meniu for day " << i + 1 << "\n";

        menu << type << "\n";
        menu << "Soup:"<< "," << s1 << "\n";
        menu << "Main dish:"<< "," << s2 << "\n";
        menu << "Dessert:"<< "," << s3 << "\n";
        menu << "\n";
    }
    else if (choise == 2){
        if(ok == 0) 
            menu << "Meniul pentru ziua " << i + 1 << "\n";

        menu << type << "\n";
        menu << "Supa:"<< "," << s1 << "\n";
        menu << "Fel principal:"<< "," << s2 << "\n";
        menu << "Desert:"<< "," << s3 << "\n";
        menu << "\n";
    }
  
    menu.close();
}

void generateMenu(int choise) {
    // generate a single soup, vegetarian and flexitarian main dish and a dessert
    for(int i = 0; i< 3; i++){

        if (choise == 1){
        
            string goodsoup = getLine("soups.csv");
            string goodn = getLine("mainDishNormal.csv");
            string goodv = getLine("mainDishVeg.csv");
            string goodf = getLine("mainDishFlex.csv");
            string gooddess = getLine("desserts.csv");

            writeMenu("Normal Menu", goodsoup, goodn, gooddess, 0, i, choise);
            writeMenu("Vegetarian Menu", goodsoup, goodv, gooddess, 1, i, choise);
            writeMenu("Flexitarian Menu", goodsoup, goodf, gooddess, 1, i, choise);
        }
        else if (choise == 2){

            string goodsoup = getLine("supe.csv");
            cout << goodsoup;
            string goodn = getLine("felPrincipalNormal.csv");
            string goodv = getLine("felPrincipalVeg.csv");
            string goodf = getLine("fePrincipalFlex.csv");
            string gooddess = getLine("deserturi.csv");

            writeMenu("Meniu normal", goodsoup, goodn, gooddess, 0, i, choise);
            writeMenu(" Meniu vegetarian", goodsoup, goodv, gooddess, 1, i, choise);
            writeMenu("Meniu flexitarian", goodsoup, goodf, gooddess, 1, i, choise);
        }
    }

}

int numberOfActorss() {
    newCastFile.open("CastFinal.csv", ios::in | ios::out | ios::binary | ios::app);

    int m = 0;
    while (!newCastFile.eof()) {
        string line;
        getline(newCastFile, line);
        m++;
    }

    newCastFile.close();
    return m;
}

long getRoomCost(int days, int initialCast, int figure){

    long costForRoomsPerNight = 0;
    costForRoomsPerNight += initialCast/2 + 1*(initialCast % 2);
    costForRoomsPerNight += figure/3 + 1*(figure % 3);

    return costForRoomsPerNight * days;
}

long double getWaterCost(int days, int totalPersons){
    int oneLWater = 3;
    int halfLCoffe = 15;
    double juice = 3.2;

    return days * (oneLWater + halfLCoffe + juice) * totalPersons;
}

// Calculate makeup price for all monsters for x days
long getMakeupCost(int days, vector<Monster *> monsters){
    
    long makeupPrice = 0;
    for (int i = 0; i < monsters.size(); i++) {
        makeupPrice += monsters[i]->makeupPrice;
    }
    return makeupPrice * days;
}

int getCantacuzino(int days) {

    long cantacuzinoPerDay = 10000;
    long price = days * cantacuzinoPerDay;
    double procent;

    if (days % 10 == 0)
        procent = days / 10 * 0.02;
    else
        procent = days / 10 * 0.02 + 0.01;

    price -= price * procent;

    return price;
}

long getFoodCost(int days, vector<Monster *> monsters, int otherCast){

    long foodCost = 0;
    for (int i = 0; i < monsters.size(); i++) {
        if(monsters[i]->diet == 1)
            foodCost += 40;
        else if(monsters[i]->diet == 2)
            foodCost += 33;
        else if(monsters[i]->diet == 3)
            foodCost += 46;
    }

    for (int i = 0; i < otherCast; i++){
        int random = rand() % 3;
        if(random == 0)
            foodCost += 40;
        else if(random == 1)
            foodCost += 33;
        else if(random == 2)
            foodCost += 46;
    }

    return foodCost * days;
}

long double leiToDollars(long lei) {
    double dollars = double(lei) / 4.64;
    return dollars;
}


void getTotalCost(string fileName,int initialCast, int figure, vector<Monster *> monsters, int otherCast, int totalCast, int choise) {
    
    fstream finalCost;
    finalCost.open(fileName, ios::in | ios::out | ios::binary | ios::app);

    finalCost << fixed << showpoint << setprecision(4);


    if (choise == 1){
        finalCost << "Price for 30 days:\n";
        finalCost << "Transport:" << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Accommodation:" << "," << leiToDollars(getRoomCost(30, initialCast, figure)) << "$\n";
        finalCost << "Makeup:" << "," << leiToDollars(getMakeupCost(30, monsters)) << "$\n";
        finalCost << "Food and water:" << "," << leiToDollars(getFoodCost(30, monsters, otherCast)) << "," << leiToDollars(getWaterCost(30, totalCast)) << "$\n";
        finalCost << "Cantacuzino Castel:" << "," << leiToDollars(getCantacuzino(30)) << "$\n\n";

        finalCost << "Price for 45 days:\n";
        finalCost << "Transport:" << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Accommodation:" << "," << leiToDollars(getRoomCost(45, initialCast, figure)) << "$\n";
        finalCost << "Makeup:" << "," << leiToDollars(getMakeupCost(45, monsters)) << "$\n";
        finalCost << "Food and water:" << "," << leiToDollars(getFoodCost(45, monsters, otherCast)) << "," << leiToDollars(getWaterCost(45, totalCast)) << "$\n";
        finalCost << "Cantacuzino Castel:" << "," << leiToDollars(getCantacuzino(45)) << "$\n\n";

        finalCost << "Price for 60 days:\n";
        finalCost << "Transport:" << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Accommodation:" << "," << leiToDollars(getRoomCost(60, initialCast, figure)) << "$\n";
        finalCost << "Makeup:" << "," << leiToDollars(getMakeupCost(60, monsters)) << "$\n";
        finalCost << "Food and water:" << "," << leiToDollars(getFoodCost(60, monsters, otherCast)) << "," << leiToDollars(getWaterCost(60, totalCast)) << "$\n";
        finalCost << "Cantacuzino Castel:" << "," << leiToDollars(getCantacuzino(60)) << "$\n\n";
 
        finalCost << "Price for 100 days:\n";
        finalCost << "Transport:" << "," << getBusses(2) << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Accommodation:" << "," << leiToDollars(getRoomCost(100, initialCast, figure)) << "$\n";
        finalCost << "Makeup:" << "," << leiToDollars(getMakeupCost(100, monsters)) << "$\n";
        finalCost << "Food and water:" << "," << leiToDollars(getFoodCost(100, monsters, otherCast)) << "," << leiToDollars(getWaterCost(100, totalCast)) << "$\n";
        finalCost << "Cantacuzino Castel:" << "," << leiToDollars(getCantacuzino(100)) << "$\n\n";
    }
    else if(choise == 2){

        finalCost << "Pret pentru 30 de zile:\n";
        finalCost << "Transport:" << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Cazare:" << "," << leiToDollars(getRoomCost(30, initialCast, figure)) << "$\n";
        finalCost << "Machiaj:" << "," << leiToDollars(getMakeupCost(30, monsters)) << "$\n";
        finalCost << "Mancare si bautura:" << "," << leiToDollars(getFoodCost(30, monsters, otherCast)) << "," << leiToDollars(getWaterCost(30, totalCast)) << "$\n";
        finalCost << "Castelul Cantacuzino:" << "," << leiToDollars(getCantacuzino(30)) << "$\n\n";

        finalCost << "Pret pentru 45 de zile:\n";
        finalCost << "Transport:" << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Cazare:" << "," << leiToDollars(getRoomCost(45, initialCast, figure)) << "$\n";
        finalCost << "Machiaj:" << "," << leiToDollars(getMakeupCost(45, monsters)) << "$\n";
        finalCost << "Mancare si bautura:" << "," << leiToDollars(getFoodCost(45, monsters, otherCast)) << "," << leiToDollars(getWaterCost(45, totalCast)) << "$\n";
        finalCost << "Castelul Cantacuzino:" << "," << leiToDollars(getCantacuzino(45)) << "$\n\n";

        finalCost << "Pret pentru 60 de zile:\n";
        finalCost << "Transport:" << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Cazare:" << "," << leiToDollars(getRoomCost(60, initialCast, figure)) << "$\n";
        finalCost << "Machiaj:" << "," << leiToDollars(getMakeupCost(60, monsters)) << "$\n";
        finalCost << "Mancare si bautura:" << "," << leiToDollars(getFoodCost(60, monsters, otherCast)) << "," << leiToDollars(getWaterCost(60, totalCast)) << "$\n";
        finalCost << "Castelul Cantacuzino:" << "," << leiToDollars(getCantacuzino(60)) << "$\n\n";
 
        finalCost << "Pret pentru 100 de zile:\n";
        finalCost << "Transport:" << "," << getBusses(2) << "," << leiToDollars(getBusses(2)) << "$\n";
        finalCost << "Cazare:" << "," << leiToDollars(getRoomCost(100, initialCast, figure)) << "$\n";
        finalCost << "Machiaj:" << "," << leiToDollars(getMakeupCost(100, monsters)) << "$\n";
        finalCost << "Mancare si bautura:" << "," << leiToDollars(getFoodCost(100, monsters, otherCast)) << "," << leiToDollars(getWaterCost(100, totalCast)) << "$\n";
        finalCost << "Castelul Cantacuzino:" << "," << leiToDollars(getCantacuzino(100)) << "$\n\n";
    }
    
    finalCost.close();

}


int main() {
    file.open("CastInitial.csv", ios::in);
    newCastFile.open("CastFinal.csv", ios::in | ios::out | ios::binary | ios::app);
    namesFile.open("Names.txt");
    rolesFile.open("Roles.txt");

    
    int n = 0, m = 0;
    int initialCast;

    while (!file.eof()) {
            string line;
            string rname, rfunction;
            getline(file, line);
            stringstream ss(line);
            getline(ss, rname, ',');
            getline(ss, rfunction, ',');

            if (rfunction == "actor/actress" || rfunction == "actor/actrita") {
            
                persoane[n].name = rname;
                persoane[n].function = rfunction;
                newCastFile << persoane[n].name << "," << persoane[n].function << "\n";
                n++;
            }
            else m++;
            initialCast++;
        }

        while (!namesFile.eof() && !rolesFile.eof()) {
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

    int choise;
    cout << "Select language:\n1.En\n2.Ro\n";
    cin >> choise;
    
    // generate monsters and display them using getDetails()
    vector<Monster *> monsters = generateMonsters(n);
    int totalCast = n + m;

    getTotalCost("Cost.csv", initialCast, 132, monsters, m, totalCast, choise);

    generateMenu(choise);
    
    


    file.close();
    newCastFile.close();
    namesFile.close();
    rolesFile.close();
    return 0;
}
