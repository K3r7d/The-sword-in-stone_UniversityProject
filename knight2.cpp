#include "knight2.h"

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




/* * * BEGIN implementation of class BaseBag * * */
bool BaseBag::insertFirst(BaseItem * Item){
    if(this->count()==max_size) return false;
    if (this->count() == 0){
        Item->next = nullptr;
        head = Item;
        return true;
    }else{
        if (this->count() < max_size){
            Item->next = head;
            head = Item;
            return true;
        }else{
            return false;
        }
    }
}


void BaseBag::removeFirst(){
    if (count() == 0){
        return;
    }else{
        BaseItem * temp = head;
        head = head->next;
        delete temp;
        if (temp->getItemType()==ANTIDOTE) antidote--;
        else phoenixdown--;
    }
}

string BaseBag::toString() const {
    string result("");
    result+= "Bag[count="+to_string(count())+';';
    BaseItem * temp = head;
    while(temp != nullptr){
        result += temp->toString();
        temp = temp->next;
        if(temp != nullptr){
            result += ',';
        }
    }
    result+=']';
    return result;
}

BaseItem* BaseBag::takePhoenixDownExcept(ItemType type){
    BaseItem * temp = head;
    BaseItem * prev = nullptr;
    if(type == PHOENIXDOWNI){
    while(temp != nullptr){
        if(temp ->getItemType() != ANTIDOTE && temp ->getItemType() != PHOENIXDOWNI){
            if(prev == nullptr){
                head = temp->next;
            }else{
                prev->next = temp->next;
            }
            phoenixdown--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
    }else if(type == PHOENIXDOWNII){
    while(temp != nullptr){
        if(temp ->getItemType() != ANTIDOTE && temp ->getItemType() != PHOENIXDOWNII && temp ->getItemType() != PHOENIXDOWNI){
            if(prev == nullptr){
                head = temp->next;
            }else{
                prev->next = temp->next;
            }
            phoenixdown--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
    }else if(type == PHOENIXDOWNIII){
    while(temp != nullptr){
        if(temp ->getItemType() != ANTIDOTE && temp ->getItemType() != PHOENIXDOWNIII && temp ->getItemType() != PHOENIXDOWNII && temp ->getItemType() != PHOENIXDOWNI){
            if(prev == nullptr){
                head = temp->next;
            }else{
                prev->next = temp->next;
            }
            phoenixdown--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
}
    return nullptr;
    
}

BaseItem* BaseBag::takeAnyPhoenixDown(){
    BaseItem * temp = head;
    BaseItem * prev = nullptr;
    while(temp != nullptr){
        if(temp ->getItemType() != ANTIDOTE){
            if(prev == nullptr){
                head = temp->next;
            }else{
                prev->next = temp->next;
            }
            phoenixdown--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
    return nullptr;
    
}

BaseItem* BaseBag::takeAntidote(){
    BaseItem * temp = head;
    BaseItem * prev = nullptr;
    while(temp != nullptr){
        if(temp ->getItemType() == ANTIDOTE){
            if(prev == nullptr){
                head = temp->next;
            }else{
                prev->next = temp->next;
            }
            antidote--;
            return temp;
        }
        prev = temp;
        temp = temp->next;
    }
    return nullptr;
}



/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}


BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight * knight = nullptr;
    if (isPrime(maxhp)) {
        knight = new PaladinKnight(id, maxhp, level, gil, antidote,phoenixdownI);
    } else if (maxhp == 888) {
        knight = new LancelotKnight(id, maxhp, level, gil, antidote,phoenixdownI);
    } else if (isPythagorean(maxhp)) {
        knight = new DragonKnight(id, maxhp, level, gil, 0 ,phoenixdownI);
    } else {
        knight = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    return knight;
}

bool PaladinKnight::fight(BaseOpponent* opponent){
    int type = opponent->getOpponentType();
    if (type == OMEGAWEAPON){
        if((this->hp == this->maxhp) && (this->level == 10)){
            this->gil = 999;
            this->level = 10;
            return true;
        }else{
            this->hp = 0;
            HandleHP();
        };
    }


    if (type <=5){
        this->gil+= opponent->getGil();
    }
    if(this->level >=opponent->getLevel()){
        if(type == TORNBERY){
            this->level += 1;
            if(level>10) level = 10;
        }else if(type == QUEENOFCARDS){
            this->gil *=2;
        }
    }else{
        if(type == TORNBERY){
            LoseTornbery();
        }
    }
    return this->hp>0;
}

bool LancelotKnight::fight(BaseOpponent* opponent){
    int type = opponent->getOpponentType();
    if (type == OMEGAWEAPON){
        if((this->hp == this->maxhp) && (this->level == 10)){
            this->gil = 999;
            this->level = 10;
            return true;
        }else{
            this->hp = 0;
            HandleHP();
            return this->hp>0;
        };
    }
    if (type <=5){
        this->gil+= opponent->getGil();
    }
    if(this->level >=opponent->getLevel()){
        if(type == TORNBERY){
            this->level += 1;
            if(level>10) level = 10;
        }else if(type == QUEENOFCARDS){
            this->gil *=2;
        }
    }else{
        if(type == TORNBERY){
            LoseTornbery();
        }else if(type == QUEENOFCARDS){
            this->gil /=2;
        }
    }
    return this->hp>0;
}

bool DragonKnight::fight(BaseOpponent* opponent){
    int type = opponent->getOpponentType();
    if (type == OMEGAWEAPON){
        this->gil = 999;
        this->level = 10;
        return true;
        
    }
    if(this->level>=opponent->getLevel()){
        if (type <=5){
            this->gil += opponent->getGil();
        }
        if (type == TORNBERY){
            this->level += 1;
            if(level>10) level = 10;
        }
        if(type == QUEENOFCARDS){
            this->gil *=2;
        }
    }
    else{
        if (type <=5){
            this->hp -= opponent->getBasedamage()*(opponent->getLevel()-this->level);
            HandleHP();
        }
        if(type == QUEENOFCARDS){
            this->gil /=2;
        }
    }
    return this->hp>0;
}

bool NormalKnight::fight(BaseOpponent* opponent){
    int type = opponent->getOpponentType();
    if (type == OMEGAWEAPON){
        if((this->hp == this->maxhp) && (this->level == 10)){
            this->gil = 999;
            this->level = 10;
            return true;
        }else{
            this->hp = 0;
            HandleHP();
            return this->hp>0;
        };
    }

    if(type == HADES){
        if(this->level == 10){
            return true;
        }else{
            this->hp = 0;
            HandleHP();
        }
    }

    if(this->level>=opponent->getLevel()){
        if (type <=5){
            this->gil += opponent->getGil();
        }
        if (type == TORNBERY){
            this->level += 1;
            if(level>10) level = 10;
        }
        if(type == QUEENOFCARDS){
            this->gil *=2;
        }
    }
    else{
        if (type <=5){
            this->hp -= opponent->getBasedamage()*(opponent->getLevel()-this->level);
            HandleHP();
        }
        if (type == TORNBERY){
            LoseTornbery();
        }
        if(type == QUEENOFCARDS){
            this->gil /=2;
        }
    }
    return this->hp>0;
}

void BaseKnight::LoseTornbery(){
    if (bag->getAntidote()>0) {
           this->antidote--;
            bag->takeAntidote();
    }
        else{
            for(int i = 0;i<3;i++){
                bag->removeFirst();
            }
            this->hp-=10;
            HandleHP();
        }
}

void BaseKnight::HandleHP(){
    if (hp<=0){
        BaseItem* temp = bag->takeAnyPhoenixDown();
        if(temp != nullptr){
            temp->use(this);
            return;
        }
    }else if(hp<(maxhp/4)){
        BaseItem* temp = bag->takePhoenixDownExcept(PHOENIXDOWNI);
        if(temp != nullptr){
            temp->use(this);
            return;
        }
    }else if(hp<(maxhp/3)){
        BaseItem* temp = bag->takePhoenixDownExcept(PHOENIXDOWNII);
        if(temp != nullptr){
            temp->use(this);
            return;
        }
    }else if(hp<(maxhp/2)){
        BaseItem* temp = bag->takePhoenixDownExcept(PHOENIXDOWNIII);
        if(temp != nullptr){
            temp->use(this);
            return;
        }
    }
    if(hp<=0 && gil>=100){
        setHP(maxhp/2);
        setGil(gil-100);
    }
}

/* * * END implementation of class BaseKnight * * */

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
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

BaseKnight * ArmyKnights::lastKnight() const{
    if (num_of_knight>0){
        return knight[num_of_knight-1];
    }
    else return nullptr;
}

ArmyKnights::ArmyKnights(const string & file_armyknights): num_of_knight(0), knight(nullptr), OmegaWeapon(false), Hades(false), PaladinShield(false), LancelotSpear(false), GuinevereHair(false), ExcaliburSword(false){
    ifstream ifs(file_armyknights);
    if (!ifs) {
        cout << "Cannot open file: " << file_armyknights << endl;
        return;
    }

    ifs >> num_of_knight;
    knight = new BaseKnight*[num_of_knight];
    for(int i = 0;i<num_of_knight;i++){
        int maxhp, level, gil, antidote, phoenixdownI;
        ifs >> maxhp >> level >> phoenixdownI >> gil >> antidote ;
        knight[i] = BaseKnight::create(i+1, maxhp, level, gil, antidote, phoenixdownI);
    }
    ifs.close();
}



void ArmyKnights::PassGil(int gil, int index){
    while(gil>=0 && index>=0){
    int gilz = gil;
    int gil = 0;
    if (gilz>999){
        gil = gilz-999;
        gilz = 999;
    }
    knight[index]->setGil(gilz);
    index--;
    }
}



bool ArmyKnights::fight_Ultimecia(){
    if(hasExcaliburSword()) return true;
    else if(hasGuinevereHair()&&hasLancelotSpear()&&hasPaladinShield()){
        int HP_Ultimecia = 5000;
        double knight_base_dmg[] = {0.05,0.06,0.75};
        for(int i = num_of_knight-1;i>=0;i--){
            KnightType type = knight[i]->getKnightType();
            int knight_level = knight[i]->getLevel();
            int knight_HP = knight[i]->getHP();
            if(type == LANCELOT) HP_Ultimecia -= knight_base_dmg[0]*knight_level*knight_HP;
            else if(type == PALADIN) HP_Ultimecia -= knight_base_dmg[1]*knight_level*knight_HP;
            else if(type == DRAGON) HP_Ultimecia -= knight_base_dmg[2]*knight_level*knight_HP;
            if (HP_Ultimecia >=0) {
                deletelastKnight();
            }
            
            if(num_of_knight==0) {
                printInfo();
                return false;
            }
        }
        if( HP_Ultimecia <= 0 )return true;
        else {deleteArmy();
        printInfo();return false;}
    } else{deleteArmy();
    printInfo(); return false;}   
    return false;
}

void ArmyKnights::PassItem(BaseItem* item,int index){
    for(int i = index;i>=0;i--){
        if(knight[i]->getBag()->insertFirst(item)) return;
    }
}
void ArmyKnights::deleteArmy(){
    for(int i = num_of_knight-1;i>=0;i--){
        delete knight[i];
    }
    delete[] knight;
    num_of_knight = 0;
}
void ArmyKnights::getPhoenixDown(int type){
    BaseItem * temp = nullptr;
    if (type == 1) temp = new PhoenixDownI();
    if (type == 2) temp = new PhoenixDownII();
    if (type == 3) temp = new PhoenixDownIII();
    if (type == 4) temp = new PhoenixDownIV();
    for(int i = num_of_knight -1 ;i>=0;i--){
        if(knight[i]->getBag()->insertFirst(temp)) {;
            knight[i]->getBag()->increasePhoenixDown();
            return;}
        else if(i!=0){PassItem(temp,i-1);}
    }
    delete temp;
    return;
}

bool ArmyKnights::meet_NinaDeRing(){
    for(int i = 0;i<num_of_knight;i++){
        int type = knight[i]->getKnightType();
        if(type == PALADIN && knight[i]->getHP()<(knight[i]->getMaxHP())/3){
            knight[i]->setHP(knight[i]->getHP()+(knight[i]->getMaxHP()/5));
        }else{
            if(knight[i]->getGil()>=50 && knight[i]->getHP()<(knight[i]->getMaxHP())/3){
                knight[i]->setHP(knight[i]->getHP()+(knight[i]->getMaxHP()/5));
                knight[i]->setGil(knight[i]->getGil()-50);
            }
        }
    }
    return true;
}

bool ArmyKnights::meet_DurianGarden(){
    for(int i = 0;i<num_of_knight;i++){
        knight[i]->setHP(knight[i]->getMaxHP());
    }
    return true;
}

bool ArmyKnights::fight(BaseOpponent * opponent){
    if (opponent->getOpponentType() == OMEGAWEAPON && OmegaWeapon) return true;
    if (opponent->getOpponentType() == HADES && Hades) return true;
    if (opponent->getOpponentType() == NINADERINGS) return meet_NinaDeRing();
    if (opponent->getOpponentType() == DURIANGARDEN) return meet_DurianGarden();

    for(int i = num_of_knight-1;i>=0;i--){
        if(knight[i]->fight(opponent)){
            if(knight[i]->getGil()>999){
                PassGil(knight[i]->getGil()-999,i-1);
                knight[i]->setGil(999);
            }
            return true;
        }else{
            deletelastKnight();
            
            if(num_of_knight==0) {
            printInfo();
            return false;
        }else return true;
        }
        if(num_of_knight==0) {
            printInfo();
            return false;
        }
    }
    return num_of_knight>0;
}
bool ArmyKnights::fight_OmegaWeapon(){
    if(OmegaWeapon)return true;
    for (int i = num_of_knight-1;i>=0;i--){
        if(knight[i]->getKnightType()==DRAGON || (knight[i]->getLevel()==10 && knight[i]->getHP()== knight[i]->getMaxHP())){
            OmegaWeapon = true;
            knight[i]->setLevel(10);
            knight[i]->setGil(999);
            return true;
        }
        else{
            OmegaWeapon = true;
            knight[i]->setHP(0);
            knight[i]->HandleHP();
            if(knight[i]->getHP()<=0) {
                deletelastKnight();
                if(num_of_knight==0) {
                    printInfo();
                    return false;
                }
                return true;
            }
            if(num_of_knight==0){
                printInfo();
                 return false;} else return true;
        }
    }
    return true;
}

bool ArmyKnights::fight_Hades(){
    if(Hades) return true;
    for(int i = num_of_knight-1;i>=0;i--){
        if((knight[i]->getKnightType() == PALADIN && knight[i]->getLevel()>=8)|| knight[i]->getLevel()==10){
            Hades = true;
            PaladinShield = true;
            return true;
        }else{
            Hades = true;
            knight[i]->setHP(0);
            knight[i]->HandleHP();
            if(knight[i]->getHP()<=0) {
                deletelastKnight();
                if(num_of_knight==0) {
                    printInfo();
                    return false;
                }else return true;
            }
            if(num_of_knight==0){ 
                printInfo();
                return false;
            }else return true;
        }
    }
    return true;
}


bool ArmyKnights::HandleEvent(int event_ordered, int event_id){
    int LvO = (event_ordered+event_id)%10 +1;
    BaseOpponent * opponent = nullptr;
    if(event_id == 1){
        opponent = new MadBear(LvO);

    }else if(event_id == 2){
        opponent = new Bandit(LvO);
    }else if(event_id == 3){
        opponent = new LordLupin(LvO);
    }else if(event_id == 4){
        opponent = new Elf(LvO);
    }else if(event_id == 5){
        opponent = new Troll(LvO);
    }else if(event_id == 6){
        opponent = new Tornbery(LvO);
    }else if(event_id == 7){
        opponent = new QueenOfCards(LvO);
    }else if(event_id == 8){
        opponent = new NinaDeRings(LvO);
    }else if(event_id == 9){
        opponent = new DurianGarden(LvO);
    }else if(event_id == 10){
        return fight_OmegaWeapon();
    }else if(event_id == 11){
        return fight_Hades();
    }else if(event_id == 95){
        PaladinShield = true;
        return true;
    }else if(event_id == 96){
        LancelotSpear = true;
        return true;
    }else if(event_id == 97){
        GuinevereHair = true;
        return true;
    }else if(event_id == 98 ){
        if(PaladinShield && LancelotSpear && GuinevereHair){
        ExcaliburSword = true;
        }
        return true;
    }else if(event_id == 99){
        return fight_Ultimecia();
    }else if(event_id == 112){
        getPhoenixDown(2);
        return true;
    }else if(event_id == 113){
        getPhoenixDown(3);
        return true;
    }else if(event_id == 114){
        getPhoenixDown(4);
        return true;
    }
    return fight(opponent);
}

bool ArmyKnights::adventure(Events * events){
    for(int i=0;i<events->count();i++){
        int event_id = events->get(i);
        if(HandleEvent(i,event_id)) printInfo();
        else return 0;
    }
    return true;
}

void ArmyKnights::deletelastKnight(){
    delete knight[num_of_knight-1];
    num_of_knight--;
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

void KnightAdventure::loadEvents(const string& file_events){
    events = new Events(file_events);
}

void KnightAdventure::loadArmyKnights(const string& file_army){
    armyKnights = new ArmyKnights(file_army);
}

void KnightAdventure::run(){
    armyKnights -> adventure(events);
    armyKnights -> printResult(armyKnights ->count());
}
/* * * END implementation of class KnightAdventure * * */