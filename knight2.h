<<<<<<< HEAD
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum ItemType {ANTIDOTE = 0,PHOENIXDOWN,PHOENIXDOWNI,PHOENIXDOWNII,
                PHOENIXDOWNIII,PHOENIXDOWNIV};
enum OpponentType {MADBEAR = 1,BANDIT = 2,LORDLUPIN = 3,ELF = 4,
                    TROLL = 5,TORNBERY = 6,QUEENOFCARDS = 7,NINADERINGS = 8,
                    DURIANGARDEN = 9, OMEGAWEAPON = 10,
                    HADES = 11};
// #define DEBUG
class BaseItem;
class Events;
class BaseKnight;
class ArmyKnights;
class BaseOpponent;
class BaseBag;
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    virtual ~BaseKnight() = default;
    virtual bool fight(BaseOpponent *opponent) = 0;


    virtual int getID() const { return id; }
    virtual int getHP() const { return hp; }
    virtual int getMaxHP() const { return maxhp; }
    int getLevel() const { return level; }
    int getGil() const { return gil; }
    int getAntidote() const { return antidote; }
    BaseBag * getBag() const { return bag; }
    KnightType getKnightType() const { return knightType; }
    void setHP(int hp) { this->hp = hp; }
    
    void setLevel(int level) { this->level = level; }
    void setGil(int gil) { this->gil = gil; }
    virtual void LoseTornbery();
    void HandleHP();
    
};




class BaseItem {
protected:
    ItemType itemType;
    int count;
public:
    BaseItem * next = nullptr;
    ItemType getItemType() const { return itemType; }
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual string toString() const = 0;
};

class PhoenixDownI : public BaseItem {
    public:
    PhoenixDownI(){
        this->itemType = PHOENIXDOWNI;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() <= 0) return true;
        else return false;
    }
    void use ( BaseKnight * knight ){
        knight->setHP(knight->getMaxHP());
    }
    string toString() const {
        return "PhoenixI";
    }
};

class PhoenixDownII: public BaseItem{
    public:
    PhoenixDownII(){
        this->itemType = PHOENIXDOWNII;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() < knight->getMaxHP()/4) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        knight->setHP(knight->getMaxHP());
    }
    string toString() const {
        return "PhoenixII";
    }
};

class PhoenixDownIII: public BaseItem{
    public:
    PhoenixDownIII(){
        this->itemType = PHOENIXDOWNIII;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() < knight->getMaxHP()/2) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        if(knight->getHP()<=0) knight->setHP(knight->getMaxHP()/3);
        else knight->setHP(knight->getHP()+knight->getMaxHP()/4);
    }
    string toString() const {
        return "PhoenixIII";
    }
};

class PhoenixDownIV: public BaseItem{
    public:
    PhoenixDownIV(){
        this->itemType = PHOENIXDOWNIV;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() < knight->getMaxHP()*3/4) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        if (knight->getHP()<=0) knight->setHP(knight->getMaxHP()/2);
        else knight->setHP(knight->getHP()+knight->getMaxHP()/5);
    }
    string toString() const {
        return "PhoenixIV";
    }
};

class Antidote:public BaseItem{
    public:
    Antidote(){
        this->itemType = ANTIDOTE;
    };
    bool canUse ( BaseKnight * knight ){
        return true;
    }
    void use(BaseKnight * knight){
     return;
    }
    string toString() const {
        return "Antidote";
    }
};
class BaseBag {
private:
    int antidote = 0;
    int phoenixdown = 0;
    int max_size = 0;
    BaseItem * head = nullptr;
public:
    BaseBag(int antidote, int phoenixdownI, int max_size){
        this->antidote = antidote;
        this->phoenixdown = phoenixdownI;
        this->max_size = max_size;
        for(int i = 0; i < phoenixdownI; i++){
            BaseItem * item = new PhoenixDownI();
            insertFirst(item);
        }
        for(int i = 0; i < antidote; i++){
            BaseItem * item = new Antidote();
            insertFirst(item);
        }
    };
    virtual ~BaseBag() = default;
    virtual bool insertFirst(BaseItem * item);
    virtual string toString() const ;
    virtual void removeFirst();
    virtual BaseItem * getHead() const { return head; }
    virtual BaseItem * takePhoenixDownExcept(ItemType);
    virtual BaseItem * takeAnyPhoenixDown();
    virtual BaseItem * takeAntidote();
    int getAntidote() const { return antidote; }
    int getPhoenixDown() const { return phoenixdown; }
    void decreaseAntidote() {antidote--; }
    void decreasePhoenixDown() {phoenixdown--; }
    void increaseAntidote() {antidote++; }
    void increasePhoenixDown() {phoenixdown++; }
    bool isfull() const { return count() == max_size; }
    bool isempty() const { return count() == 0; }
    int count() const{ return phoenixdown+antidote;}
};

class BaseOpponent{
    protected:
    int gil;
    int level;
    int basedamage;
    OpponentType opponentType;
    public:
    virtual ~BaseOpponent() = default;
    OpponentType getOpponentType() const { return opponentType; }
    int getGil() const { return gil; }
    int getLevel() const { return level; }
    int getBasedamage() const { return basedamage; }
};

class MadBear : public BaseOpponent{
    public:
    MadBear(int level){
        this->gil = 100;
        this->basedamage = 10;
        this->level = level;
        this->opponentType = MADBEAR;
    };
};

class Bandit : public BaseOpponent{
    public:
    Bandit(int level){
        this->gil = 150;
        this->basedamage = 15;
        this->level = level;
        this->opponentType = BANDIT;
    };
};

class LordLupin :public BaseOpponent{
    public:
    LordLupin(int level){
        this->gil = 450;
        this->basedamage = 45;
        this->level = level;
        this->opponentType = LORDLUPIN;
    };
};

class Elf :public BaseOpponent{
    public:
    Elf(int level){
        this->gil = 750;
        this->basedamage = 75;
        this->level = level;
        this->opponentType = ELF;
    };
};

class Troll : public BaseOpponent{
    public:
    Troll(int level){
        this->gil = 800;
        this->basedamage = 95;
        this->level = level;
        this->opponentType = TROLL;
    };
};

class Tornbery : public BaseOpponent{
    public:
    Tornbery(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = TORNBERY;
    };
};

class QueenOfCards : public BaseOpponent{
    public:
    QueenOfCards(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = QUEENOFCARDS;
    };
};

class NinaDeRings : public BaseOpponent{
    public:
    NinaDeRings(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = NINADERINGS;
    };
};

class DurianGarden : public BaseOpponent{
    public:
    DurianGarden(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = DURIANGARDEN;
    };
};

class OmegaWeapon : public BaseOpponent{
    public:
    OmegaWeapon(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = OMEGAWEAPON;
    };
};

class Hades : public BaseOpponent{
    public:
    Hades(int level){
        this->opponentType = HADES;
        this->gil = 0;
        this->basedamage = 0;
        this->level = 0;
    };
};


class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = antidote;
        this->bag = new BaseBag(antidote, phoenixdownI,65535);
        this->knightType = PALADIN;
    };
    bool fight(BaseOpponent *opponent);
};

class LancelotKnight : public BaseKnight {

public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = antidote;
        this->bag = new BaseBag(antidote, phoenixdownI,16);
        this->knightType = LANCELOT;
    };
    bool fight(BaseOpponent *opponent);
};

class DragonKnight : public BaseKnight {

public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = 0;
        this->bag = new BaseBag(antidote, phoenixdownI,14);
        this->knightType = DRAGON;
    };
    bool fight(BaseOpponent *opponent);
};

class NormalKnight : public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = antidote;
        this->bag = new BaseBag(antidote, phoenixdownI,19);
        this->knightType = NORMAL;
    };
    bool fight(BaseOpponent *opponent);
};


class ArmyKnights {
protected:
    bool OmegaWeapon = false;
    bool Hades = false;
    bool PaladinShield = false;
    bool LancelotSpear = false;
    bool GuinevereHair = false;
    bool ExcaliburSword = false;
    int num_of_knight = 0 ;
    BaseKnight ** knight = nullptr;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights() = default;
    bool adventure (Events * events);
    bool HandleEvent (int,int);
    
    bool meet_NinaDeRing();
    bool meet_DurianGarden();
    bool fight_OmegaWeapon();
    bool fight_Hades();
    bool fight_Ultimecia();
    int count() const{return num_of_knight;};
    BaseKnight * lastKnight() const;
    void deletelastKnight();

    bool hasPaladinShield() const{return PaladinShield;};
    bool hasLancelotSpear() const{return LancelotSpear;};
    bool hasGuinevereHair() const{return GuinevereHair;};
    bool hasExcaliburSword() const{return ExcaliburSword;};
    void PassItem(BaseItem* item, int index);
    void getPhoenixDown(int);
    void printInfo() const;
    void printResult(bool win) const;
    void PassGil(int gil, int index);
    void PassAntidote_Dragon(int index){};
    void deleteArmy();
    bool fight(BaseOpponent *opponent);
};



class Events {
private:
int event_length = 0;
public:
    //Constructor
    Events (const string & file_event){
        ifstream file_in(file_event);
        if (file_in.is_open()){
            file_in >> event_length;
            event = new int[event_length];
            for (int i = 0; i < event_length; i++){
                file_in >> event[i];
            }
        }
        file_in.close();
    }
    //Destructor
     ~Events () = default;
    int count() const{
        return event_length;
    }
    int get(int i) const{
        return event[i];
    }
    private:
    int* event = nullptr;
    
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

=======
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum ItemType {ANTIDOTE = 0,PHOENIXDOWN,PHOENIXDOWNI,PHOENIXDOWNII,
                PHOENIXDOWNIII,PHOENIXDOWNIV};
enum OpponentType {MADBEAR = 1,BANDIT = 2,LORDLUPIN = 3,ELF = 4,
                    TROLL = 5,TORNBERY = 6,QUEENOFCARDS = 7,NINADERINGS = 8,
                    DURIANGARDEN = 9, OMEGAWEAPON = 10,
                    HADES = 11};
// #define DEBUG
class BaseItem;
class Events;
class BaseKnight;
class ArmyKnights;
class BaseOpponent;
class BaseBag;
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    virtual ~BaseKnight() = default;
    virtual bool fight(BaseOpponent *opponent) = 0;


    virtual int getID() const { return id; }
    virtual int getHP() const { return hp; }
    virtual int getMaxHP() const { return maxhp; }
    int getLevel() const { return level; }
    int getGil() const { return gil; }
    int getAntidote() const { return antidote; }
    BaseBag * getBag() const { return bag; }
    KnightType getKnightType() const { return knightType; }
    void setHP(int hp) { this->hp = hp; }
    
    void setLevel(int level) { this->level = level; }
    void setGil(int gil) { this->gil = gil; }
    virtual void LoseTornbery();
    void HandleHP();
    
};




class BaseItem {
protected:
    ItemType itemType;
    int count;
public:
    BaseItem * next = nullptr;
    ItemType getItemType() const { return itemType; }
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual string toString() const = 0;
};

class PhoenixDownI : public BaseItem {
    public:
    PhoenixDownI(){
        this->itemType = PHOENIXDOWNI;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() <= 0) return true;
        else return false;
    }
    void use ( BaseKnight * knight ){
        knight->setHP(knight->getMaxHP());
    }
    string toString() const {
        return "PhoenixI";
    }
};

class PhoenixDownII: public BaseItem{
    public:
    PhoenixDownII(){
        this->itemType = PHOENIXDOWNII;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() < knight->getMaxHP()/4) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        knight->setHP(knight->getMaxHP());
    }
    string toString() const {
        return "PhoenixII";
    }
};

class PhoenixDownIII: public BaseItem{
    public:
    PhoenixDownIII(){
        this->itemType = PHOENIXDOWNIII;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() < knight->getMaxHP()/2) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        if(knight->getHP()<=0) knight->setHP(knight->getMaxHP()/3);
        else knight->setHP(knight->getHP()+knight->getMaxHP()/4);
    }
    string toString() const {
        return "PhoenixIII";
    }
};

class PhoenixDownIV: public BaseItem{
    public:
    PhoenixDownIV(){
        this->itemType = PHOENIXDOWNIV;
    };
    bool canUse ( BaseKnight * knight ){
        if (knight->getHP() < knight->getMaxHP()*3/4) return true;
        else return false;
    }
    void use(BaseKnight * knight){
        if (knight->getHP()<=0) knight->setHP(knight->getMaxHP()/2);
        else knight->setHP(knight->getHP()+knight->getMaxHP()/5);
    }
    string toString() const {
        return "PhoenixIV";
    }
};

class Antidote:public BaseItem{
    public:
    Antidote(){
        this->itemType = ANTIDOTE;
    };
    bool canUse ( BaseKnight * knight ){
        return true;
    }
    void use(BaseKnight * knight){
     return;
    }
    string toString() const {
        return "Antidote";
    }
};
class BaseBag {
private:
    int antidote = 0;
    int phoenixdown = 0;
    int max_size = 0;
    BaseItem * head = nullptr;
public:
    BaseBag(int antidote, int phoenixdownI, int max_size){
        this->antidote = antidote;
        this->phoenixdown = phoenixdownI;
        this->max_size = max_size;
        for(int i = 0; i < phoenixdownI; i++){
            BaseItem * item = new PhoenixDownI();
            insertFirst(item);
        }
        for(int i = 0; i < antidote; i++){
            BaseItem * item = new Antidote();
            insertFirst(item);
        }
    };
    virtual ~BaseBag() = default;
    virtual bool insertFirst(BaseItem * item);
    virtual string toString() const ;
    virtual void removeFirst();
    virtual BaseItem * getHead() const { return head; }
    virtual BaseItem * takePhoenixDownExcept(ItemType);
    virtual BaseItem * takeAnyPhoenixDown();
    virtual BaseItem * takeAntidote();
    int getAntidote() const { return antidote; }
    int getPhoenixDown() const { return phoenixdown; }
    void decreaseAntidote() {antidote--; }
    void decreasePhoenixDown() {phoenixdown--; }
    void increaseAntidote() {antidote++; }
    void increasePhoenixDown() {phoenixdown++; }
    bool isfull() const { return count() == max_size; }
    bool isempty() const { return count() == 0; }
    int count() const{ return phoenixdown+antidote;}
};

class BaseOpponent{
    protected:
    int gil;
    int level;
    int basedamage;
    OpponentType opponentType;
    public:
    virtual ~BaseOpponent() = default;
    OpponentType getOpponentType() const { return opponentType; }
    int getGil() const { return gil; }
    int getLevel() const { return level; }
    int getBasedamage() const { return basedamage; }
};

class MadBear : public BaseOpponent{
    public:
    MadBear(int level){
        this->gil = 100;
        this->basedamage = 10;
        this->level = level;
        this->opponentType = MADBEAR;
    };
};

class Bandit : public BaseOpponent{
    public:
    Bandit(int level){
        this->gil = 150;
        this->basedamage = 15;
        this->level = level;
        this->opponentType = BANDIT;
    };
};

class LordLupin :public BaseOpponent{
    public:
    LordLupin(int level){
        this->gil = 450;
        this->basedamage = 45;
        this->level = level;
        this->opponentType = LORDLUPIN;
    };
};

class Elf :public BaseOpponent{
    public:
    Elf(int level){
        this->gil = 750;
        this->basedamage = 75;
        this->level = level;
        this->opponentType = ELF;
    };
};

class Troll : public BaseOpponent{
    public:
    Troll(int level){
        this->gil = 800;
        this->basedamage = 95;
        this->level = level;
        this->opponentType = TROLL;
    };
};

class Tornbery : public BaseOpponent{
    public:
    Tornbery(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = TORNBERY;
    };
};

class QueenOfCards : public BaseOpponent{
    public:
    QueenOfCards(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = QUEENOFCARDS;
    };
};

class NinaDeRings : public BaseOpponent{
    public:
    NinaDeRings(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = NINADERINGS;
    };
};

class DurianGarden : public BaseOpponent{
    public:
    DurianGarden(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = DURIANGARDEN;
    };
};

class OmegaWeapon : public BaseOpponent{
    public:
    OmegaWeapon(int level){
        this->gil = 0;
        this->basedamage = 0;
        this->level = level;
        this->opponentType = OMEGAWEAPON;
    };
};

class Hades : public BaseOpponent{
    public:
    Hades(int level){
        this->opponentType = HADES;
        this->gil = 0;
        this->basedamage = 0;
        this->level = 0;
    };
};


class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = antidote;
        this->bag = new BaseBag(antidote, phoenixdownI,65535);
        this->knightType = PALADIN;
    };
    bool fight(BaseOpponent *opponent);
};

class LancelotKnight : public BaseKnight {

public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = antidote;
        this->bag = new BaseBag(antidote, phoenixdownI,16);
        this->knightType = LANCELOT;
    };
    bool fight(BaseOpponent *opponent);
};

class DragonKnight : public BaseKnight {

public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = 0;
        this->bag = new BaseBag(antidote, phoenixdownI,14);
        this->knightType = DRAGON;
    };
    bool fight(BaseOpponent *opponent);
};

class NormalKnight : public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        this->id = id;
        this->maxhp = maxhp;
        this->hp = maxhp;
        this->gil = gil;
        this->level = level;
        this->antidote = antidote;
        this->bag = new BaseBag(antidote, phoenixdownI,19);
        this->knightType = NORMAL;
    };
    bool fight(BaseOpponent *opponent);
};


class ArmyKnights {
protected:
    bool OmegaWeapon = false;
    bool Hades = false;
    bool PaladinShield = false;
    bool LancelotSpear = false;
    bool GuinevereHair = false;
    bool ExcaliburSword = false;
    int num_of_knight = 0 ;
    BaseKnight ** knight = nullptr;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights() = default;
    bool adventure (Events * events);
    bool HandleEvent (int,int);
    
    bool meet_NinaDeRing();
    bool meet_DurianGarden();
    bool fight_OmegaWeapon();
    bool fight_Hades();
    bool fight_Ultimecia();
    int count() const{return num_of_knight;};
    BaseKnight * lastKnight() const;
    void deletelastKnight();

    bool hasPaladinShield() const{return PaladinShield;};
    bool hasLancelotSpear() const{return LancelotSpear;};
    bool hasGuinevereHair() const{return GuinevereHair;};
    bool hasExcaliburSword() const{return ExcaliburSword;};
    void PassItem(BaseItem* item, int index);
    void getPhoenixDown(int);
    void printInfo() const;
    void printResult(bool win) const;
    void PassGil(int gil, int index);
    void PassAntidote_Dragon(int index){};
    void deleteArmy();
    bool fight(BaseOpponent *opponent);
};



class Events {
private:
int event_length = 0;
public:
    //Constructor
    Events (const string & file_event){
        ifstream file_in(file_event);
        if (file_in.is_open()){
            file_in >> event_length;
            event = new int[event_length];
            for (int i = 0; i < event_length; i++){
                file_in >> event[i];
            }
        }
        file_in.close();
    }
    //Destructor
     ~Events () = default;
    int count() const{
        return event_length;
    }
    int get(int i) const{
        return event[i];
    }
    private:
    int* event = nullptr;
    
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

>>>>>>> 1f099db9bb1ab522c66f1fb0c43911a7e898ae30
#endif // __KNIGHT2_H__