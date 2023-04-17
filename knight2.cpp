#include "knight2.h"

/*Some functions to use*/
bool isPrime(int num) {
    if(num <= 1) {
        return false;
    }
    for(int i=2; i*i<=num; i++) {
        if(num % i == 0) {
            return false;
        }
    }
    return true;
}
bool isPythagorean(int num) {
    int a = num / 100;
    int b = (num / 10) % 10;
    int c = num % 10;
    if(a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a) {
        return true;
    } else {
        return false;
    }
}


/*----------------------------------------------------*/
/* * * BEGIN implementation of class BaseBag * * */
class BaseBag {
public:
    BaseBag(int antidote, int phoe){
        
    };
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + "hp:" + to_string(hp) 
        + "maxhp:" + to_string(maxhp)
        + "level:" + to_string(level)
        + "gil:" + to_string(gil)
        + bag->toString()
        + "knight_type:" + typeString[knightType]
        + "]";
    return s;
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight* knight = nullptr;
    if (isPrime(maxhp)) {
        return new PaladinKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    } else if (maxhp == 888) {
        knight = new LancelotKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    } else if (isPythagorean(maxhp)) {
        knight = new DragonKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    } else {
        knight = new NormalKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    }
    return knight;
}
class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil, BaseBag* bag) {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = bag;
        this->knightType = PALADIN;
    }
    bool fight(BaseOpponent*opponent) override {
        
    };
};

class LancelotKnight : public BaseKnight {
public:
    LancelotKnight(int id, int maxhp, int level, int gil, BaseBag* bag) {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = bag;
        this->knightType = LANCELOT;
    }
    bool fight(BaseOpponent*opponent) override{
        return true;
    };
};

class DragonKnight : public BaseKnight {
public:
    DragonKnight(int id, int maxhp, int level, int gil, BaseBag* bag) {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = bag;
        this->knightType = DRAGON;
    }
    bool fight(BaseOpponent*opponent) override{
        return true;
    };
};

class NormalKnight : public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil, BaseBag* bag) {
        this->id = id;
        this->maxhp = maxhp;
        this->level = level;
        this->gil = gil;
        this->bag = bag;
        this->knightType = NORMAL;
    }
    bool fight(BaseOpponent*opponent) override{
        return true;
    };
};

/* * * END implementation of class BaseKnight * * */

/* * * class Base opponent * * */
class BaseOpponent{
    public:
    BaseOpponent(int event, int event_now,int gil,int basedamage){

    };

};

class MadBear:public BaseOpponent{
    public:
    {
        
    }
};
class Bandit:public BaseOpponent{
    public:
};
class LordLupin:public BaseOpponent{};
class Elf:public BaseOpponent{};
class Troll:public BaseOpponent{};
class Tornbery:public BaseOpponent{};
class QueenOfCards:public BaseOpponent{};
class NinaDeRings:public BaseOpponent{};
class DurianGarden:public BaseOpponent{};
class OmegaWeapon:public BaseOpponent{};
class Hades:public BaseOpponent{};
/* * * class Base opponent * * */


/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string('-', 50) << endl;
}

ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream file_in(file_armyknights);
    file_in>>num_of_knight;
    BaseKnight*knight = 
    for(int i =0;i<num_of_knight;i++){

    }
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure(){
    delete[] armyKnights;
    delete[] events;
}

/* * * END implementation of class KnightAdventure * * */
 
/* * * Class Event * * */

class Events {

public:
    //Constructor
    Events (const string & file_event){
        ifstream file_in(file_event);
        int event_code;
        while (file_in >> event_code){
            event_length++;
            //Allocate the dynamic event array 
            int* new_event = new int[event_length];
            for (int i = 0; i < event_length - 1; i++) {
                new_event[i] = event[i];
            }
            new_event[event_length-1] = event_code;
            //delete event to prevent the memory leak
            delete[] event;
            //assign the value to event
            event = new_event;
        }
        file_in.close();
    }
    //Destructor
     ~Events (){
        delete[] event;
    }
    int count() const{
        return event_length;
    }
    int get(int i) const{
        return event[i];
    }
    private:
    int* event = nullptr;
    int event_length = 0;
};
/* * * Class Event * * */


