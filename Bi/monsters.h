int getDiet(){
    //1 mananca orice, 2 vegetarian, 3 flexitarian
    int random = rand() % 3;
    if (random == 0)
        return 1;
        else if (random == 1)
            return 2;
            else return 3;
}

/// cum retin monstrii generati vector de clasa?
class Monster {
    public:
        int makeupPrice;
        int diet;
        string name;
        string role;

        Monster() {}

        void getDetails(){

            cout << "\n" << "Numele actorului: " << name << ", rolul: " << role << ", dieta: " << diet << ", pretul machiajului pe zi: " << makeupPrice << "\n\n";
        }
};

class Human : public Monster {
   public: 

        Human(string name, string role) {
            
            this->name = name;
            this->role = role;
            this->makeupPrice = 55;
            this->diet = getDiet();
        }
};

class Vampire : public Monster {
    public:

        Vampire(string name, string role){
            
            this->name = name;
            this->role = role;
            this->makeupPrice = 230;
            this->diet = getDiet();
        }
};

class Werewolf : public Monster {
    public:

        Werewolf(string name, string role){
            
            this->name = name;
            this->role = role;
            this->makeupPrice = 555;
            this->diet = getDiet();
        }
};

class Siren : public Monster {
    public:

        Siren(string name, string role){
            
            this->name = name;
            this->role = role;
            this->makeupPrice = 345;
            this->diet = getDiet();
        }
};

class Clairvoyant : public Monster {
    public:

        Clairvoyant(string name, string role){
            
            this->name = name;
            this->role = role;
            this->makeupPrice = 157;
            this->diet = getDiet();
        }
};

//monsters[i]->getDetails();