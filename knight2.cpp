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
        this->antidote = antidote;
        this->phoenixdown = phoe;
    };
    virtual bool insertFirst(BaseItem * item){
    };
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};
/* * * END implementation of class BaseBag * * */


/* * * BEGIN implementation of class BaseItem * * */
bool PhoenixDown::canUse(BaseKnight *knight){
    int hp = knight->gethp();
    int maxhp = knight->getmaxhp();
    if(typeofphoenixdown == 1){
        if(hp<=0) return true;
        else return false;
    } else if (typeofphoenixdown ==2){
        if(hp<maxhp/4) return true;
        else return false;
    } else if(typeofphoenixdown ==3){
        if(hp<maxhp/3) return true;
        else return false;
    } else if(typeofphoenixdown ==4){
        if(hp<maxhp/2) return true;
        else return false;
}

void PhoenixDown::use(BaseKnight * knight){
    int hp = knight->gethp();
    int maxhp = knight->getmaxhp();
    if(canuse(knight)){
        if(typeofphoenixdown == 1 ){
            knight->changehp(maxhp);
        } else if (typeofphoenixdown ==2){
            knight->changehp(maxhp);
        } else if(typeofphoenixdown ==3){
            if (hp<=0) knight->changehp(maxhp/3);
            else knight->changehp(hp+maxhp/4);
        } else if(typeofphoenixdown ==4){
            if(hp<=0) knight->changehp(maxhp/2);
            else knight->changehp(hp+maxhp/5);
        }
    }
}



/* * * END implementation of class BaseItem * * */

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
};


BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight * knight = nullptr;
    if (isPrime(maxhp)) {
        knight = new PaladinKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    } else if (maxhp == 888) {
        knight = new LancelotKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    } else if (isPythagorean(maxhp)) {
        knight = new DragonKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    } else {
        knight = new NormalKnight(id, maxhp, level, gil, new BaseBag(antidote, phoenixdownI));
    }
    return knight;
}

bool PaladinKnight::fight(BaseOpponent * opponent) {
    int type = opponent->getType();
    if (type<=5 && type>=1) {
        WinCreeps(opponent);
        
        }
    else if (this->level >= opponent->getLevel()){
        if(type==meet_Tornbery){
            WinTornbery();
        
        }else WinQueenofCard();
    }else if(type == meet_Tornbery){
        LoseTornbery();
    }
    HpDown();
    return this->hp>0 ? true : false;
}

bool LancelotKnight::fight(BaseOpponent * opponent) {
    int type = opponent->getType();
    if (type<=5 && type>=1) {
        WinCreeps(opponent);
        }
    else if(this->level >= opponent->getLevel()){
        if(type==meet_Tornbery){
            WinTornbery();
        }else WinQueenofCard();
    }else if(type == meet_Tornbery){
        LoseTornbery();
    }
    HpDown();
    return this->hp>0 ? true : false;
    
        
} 

bool DragonKnight::fight(BaseOpponent * opponent) {
    int type = opponent->getType();
    if(this->level >= opponent->getLevel()){
        if(type<=5)
        
        if(type==meet_Tornbery){
            WinTornbery();
        }else WinQueenofCard();
    }else if(type == meet_Tornbery){
        LoseTornbery();
    } 
}

bool BaseKnight::HpDown()
{
    if (bag->useItem(PhoenixDown, this)) return true;
    if (this->gil >= 100)
    {
        this->hp = this->maxhp / 2;
        this->gil -= 100;
        return true;
    }
    return false;
}

/* * * END implementation of class BaseKnight * * */

/* * * class Base opponent * * */

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
//Constructor ArmyKnights
ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream file_in(file_armyknights);
    file_in>>num_of_knight;
    file_in.ignore(999,'/n');
    knights = new BaseKnight*[num_of_knight];
    for(int i =0;i<num_of_knight;i++){
        int maxhp,level,gil,antidote,phoenixdown;
        file_in >> maxhp >>level >>phoenixdown>> gil >> antidote;
        knights[i] = BaseKnight::create(i+1,maxhp,level,gil,antidote,phoenixdown);
    }
}
//Destructor ArmyKnights
ArmyKnights::~ArmyKnights(){
    for(int i =0;i<num_of_knight;i++){
        delete knights[i];
    }
    delete[] knights;
    knights = nullptr;
    num_of_knight = 0;
}

int ArmyKnights::count() const{
    return num_of_knight;
};

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

void delete_last_knight(){
    delete knights[num_of_knight-1];
    num_of_knight--;
}

bool ArmyKnights::fight_1_to_5(int event_ordered, int event_id){
    int type = opponent->getType();
    int lvO = (event_ordered+event_id)%10+1;
    Baseopponent * opponent = new BaseOpponent(event_id, gils[event_id], basedames[event_id], lvO);
    for(int i =num_of_knight;i>=0;i--){
        if(knight[i]->fight(opponent)){
            int gil = knight[i]->getGil();
            if (gil>999){
                knight[i]->changeGil(999);
                passGil(gil-999,i);
                break;
            }else delete_last_knight();
        };
    }
    delete opponent;
    return num_of_knight>0 ? true : false;
};

bool ArmyKnights::fight_Tornbery(int event_ordered){
    int type = opponent->getType();
    int lvO = (event_ordered+6)%10+1;
    Baseopponent * opponent = new BaseOpponent(meet_Tornbery,0,0, lvO);
    for(int i =num_of_knight;i>=0;i--){
        if(knight[i]->fight(opponent)){
            int gil = knight[i]->getGil();
            if (gil>999){
                knight[i]->changeGil(999);
                passGil(gil-999,i);
                break;
            }else delete_last_knight();
        };
    }
    delete opponent;
    return num_of_knight>0 ? true : false;
};


bool ArmyKnights::fight_QueenOfCards(int event_ordered){
    int type = opponent->getType();
    int lvO = (event_ordered+7)%10+1;
    Baseopponent * opponent = new BaseOpponent(meet_QueensOfCards,0,0, lvO);
    for(int i =num_of_knight;i>=0;i--){
        if(knight[i]->fight(opponent)){
            int gil = knight[i]->getGil();
            if (gil>999){
                knight[i]->changeGil(999);
                passGil(gil-999,i);
                break;
            }else delete_last_knight();
        };
    }
    delete opponent;
    return num_of_knight>0 ? true : false;
};

void meet_NinaDeRings(){
    for(int i = 0;i<num_of_knight;i++){
    int type = knight[i]->getType();
    if (type == PALADIN && knight[i]->gethp()==knight[i]<(knight[i]->getmaxhp())/3){
        knight[i]->changehp(knight[i]+(knight[i]->getmaxhp())/5);
    }else{
        if (knight[i]->getGil()>=50 && knight[i]->gethp()==knight[i]<(knight[i]->getmaxhp())/3){
            knight[i]->changeGil(-50);
            knight[i]->changehp(knight[i]+(knight[i]->getmaxhp())/5);
            }
        }
    }
}

void meet_DurianGarden(){
    for(int i =0;i<num_of_knight;i++){
        knight[i]->changehp(knight[i]->getmaxhp());
    }
}


bool fight_OmegaWeapon(int event_ordered);


bool fight_Hades(int event_ordered);


bool fight_Ultimecia(int event_ordered){};


bool ArmyKnights::adventure(Events * events){
    int numofevent = events->count();
    for(int i= 0;i<numofevent;i++){
        int event_id = events->get(i);
        bool temp = event_process(i,event_id);
        if(temp){ 
            printInfo();
        }else return 0;
    }
};


int ArmyKnights::count() const{
    return num_of_knight;
};

BaseKnight * ArmyKnights::lastKnight() const{
    if(num_of_knight == 0)
        return nullptr;
    else
        return knights[num_of_knight-1];
}

bool ArmyKnights::event_process(int event_ordered, int event_id ){
    if (event_ordered<=5) return fight_1_to_5(event_ordered, event_id);
    else if (event_ordered == 6) return fight_Tornbery(event_ordered);
    else if (event_ordered == 7) return fight_QueenOfCards(event_ordered);
    else if (event_ordered == 8) return fight_NinaDeRings(event_ordered);
    else if (event_ordered == 9) return fight_DurianGarden(event_ordered);
    else if (event_ordered == 10) return fight_OmegaWeapon(event_ordered);
    else if (event_ordered == 11) return fight_Hades(event_ordered);
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


