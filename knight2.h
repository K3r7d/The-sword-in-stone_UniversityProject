#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {/* TODO: */
    ANTIDOTE = 0,
    PHOENIXDOWN
};
enum EVENTS{
    meet_MadBear = 1,
    meet_Bandit,
    meet_LordLupin,
    meet_Elf,
    meet_Troll,
    meet_Tornbery,
    meet_QueenOfCards,
    meet_NinaDeRings,
    meet_DurianGarden,
    meet_OmegaWeapon,
    meet_Hades,
    meet_PHOENIXDOWN_I = 112,
    meet_PHOENIXDOWN_II = 113,
    meet_PHOENIXDOWN_IV = 114,
    meet_PaladinShield = 95,
    meet_LancelotSpear = 96,
    meet_GuivenereHair = 97,
    meet_Excalibur = 98,
    meet_Ultidemacia = 99,
};

enum gils{
    MadBear_gil = 100,
    Bandit_gil = 150,
    LordLupin_gil = 450,
    Elf_gil = 750,
    Troll_gil = 800,
};

enum basedame{
    MadBear_basedame = 10,
    Bandit_basedame = 15,
    LordLupin_basedame = 45,
    Elf_basedame = 75,
    Troll_basedame = 95,
};
class BaseOpponent{
protected:
    int gil;
    int basedamage;
    int level;
    int id;
public:
    BaseOpponent(int id,int gil,int basedamage,int level){
        this->id=id;
        this->gil=gil;
        this->basedamage=basedamage;
        this->level=level;
    };
    int getType(){return id;};
    int getLevel(){return level;};
    int getGil(){return gil;};
    int getBasedame(){return basedamage;};
    bool HpDown()
};
class BaseBag {
protected:
    int antidote;
    int phoenixdown;
    BaseItem * items[2];
    int count;
public:
    BaseBag(int antidote, int phoe);
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    int count() const{return count;};
};



enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
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
    virtual bool fight ( BaseOpponent * opponent ) = 0;
    bool HpDown(){
        if (hp <= 0) return true;
        else return false;
    }

    int getid() const{return id;};

    int changeGil(int gil){this->gil = gil;};
    int getGil() const{return gil;};

    int gethp() const{return hp;};
    void changehp(int changeHp){this->hp= changeHp;};
    int getmaxhp() const{return maxhp;};
    
    int getlevel() const{return level;};
    void changelv(int changeLv){this->level= changeLv;};
    
    int get_knights_gil() const{return gil;};
    void change_knights_gil(int changeGil){this->gil= changeGil;};
    
    int get_antidote() const{return antidote;};
    void change_antidote(int changeAntidote){this->antidote= changeAntidote;};
    
    KnightType get_knight_type() const{return knightType;};
    BaseBag * get_bag() const{return bag;};
    bool knight_is_dead() {return hp <= 0;};
protected:
    virtual void WinCreeps(BaseOpponent * opponent){
        this ->gil += opponent->getGil() ;
    }
    virtual void LoseCreeps(BaseOpponent * opponent){
        int damage = opponent->getBasedame()*(opponent->getLevel()-this->level);
        this->hp -= damage;
    }
    virtual void WinTornbery(){
        (this->level <10) ? (this->level += 1): (this->level = 10);
    }
    virtual void LoseTorbery(){
        if (antidote > 0){
            --antidote;
            bag->useItem(ANTIDOTE,this);
        }else{
            for(int i = 0;i<3;i++) bag->droplastItem();
            hp-=10;

        }
    }
    virtual void WinQueenofCard(){
        this->gil *= 2;
    }
    virtual void LoseQueenofCard(){
        this->gil /= 2;
    }

    
};

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
    bool fight(BaseOpponent*opponent) {
    
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
    bool fight(BaseOpponent*opponent);
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
    bool fight(BaseOpponent*opponent);
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
    bool fight(BaseOpponent*opponent);
};


class ArmyKnights {
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    void delete_last_knight();

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
    void passGils(int gils, int order_of_knight);
    bool event_process(int event_ordered, int event_id);

    //fight
    bool fight_1_to_5(int event_ordered, int event_id);
    bool fight_Tornbery(int event_ordered);
    bool fight_QueenOfCards(int event_ordered);    
    void meet_NinaDeRings();
    void meet_DurianGarden();
    bool fight_OmegaWeapon(int event_ordered);
    bool fight_Hades(int event_ordered);
    bool fight_Ultimecia(int event_ordered);
private:
    int num_of_knight;
    BaseKnight ** knights;
};

class BaseItem {
protected:
    ItemType itemType;
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote : public BaseItem {
public:
    Antidote() {
        itemType = ANTIDOTE;
    }
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

class PhoenixDown : public BaseItem {
protected:
    int typeofphoenixdown;
public:
    PhoenixDown(int typeofphoenixdown) {
        this->typeofphoenixdown = typeofphoenixdown;
        itemType = PHOENIXDOWN;
    }   
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class Events {
public:
    int count() const;
    int get(int i) const;
    
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



#endif // __KNIGHT2_H__