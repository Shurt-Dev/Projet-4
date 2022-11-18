#include "BabyBottle.h"
#include <string>

using namespace std;

//retourne la notification
string BabyBottle::Label() {
    return this->label;
};

//ajout d'une heure de prise de bib
void BabyBottle::Add_hour(int hour) {
    this->taking_hour = hour;
    cout << "a taking hour has been added" << endl;
};

//ajout d'un interval de temps jusqu'à la prochaine prise
void BabyBottle::Add_interval(int interval) {
    this->remider_interval = interval;
    cout << "an interval between the taking times has been added" << endl;
};

//modifier le volume max du bib
void BabyBottle::Change_bottle_max_amount(int amount_max) {
    this->max_amount = amount_max;
    cout << "the maximum quantity has been changed" << endl;
};

//modifier le volume max du bib
void BabyBottle::Change_bottle_min_amount(int amount_min) {
    this->min_amount = amount_min;
    cout << "the minimum quantity has been changed" << endl;
};

//modifier le volume du biberon donner ou a donner
void BabyBottle::Change_bottle_volume(int new_bottle_volume) {
    this->bottle_volume = new_bottle_volume;
    cout << "the bottle volume has been changed" << endl;
};    

//effectue un demande pour savoir si le bébé a vomis
void BabyBottle::Regurgitate(bool reg) {
    this->regurgitate = reg;
    cout << "the baby has regurgitate" << endl;
};