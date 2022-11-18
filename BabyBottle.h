#pragma once

#include <iostream>
#include <string>

using namespace std;

class BabyBottle {

protected:
    string label;
    int taking_hour;
    int remider_interval;
    int max_amount;
    int min_amount;
    int bottle_volume;
    bool regurgitate = false;

public:
    string Label();
    void Add_hour(int hour);
    void Add_interval(int interval);
    void Change_bottle_max_amount(int amount_max);
    void Change_bottle_min_amount(int amount_min);
    void Change_bottle_volume(int new_bottle_volume);
    void Regurgitate(bool reg);
};

/*
* objectif: rajouter une heure de prise
* si heure actu = heure_de prise + intervalle_de_rappel alors
* afficcher("c'est lheure de donner le bib")
*/