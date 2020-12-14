/*
Author: Aiden Tracy
CSI230
Final Project

Purpose: Provide an Interface for a dnd dungeon master to control enemies in combat.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

struct attack
{
    //Defines Data needed to classify different kinds of attacks.
    string name;
    int toHit; //An attack's "to hit modifier" in DND describes a bonus that attack has to deal damage.
    int hitDice; //What kind of dice are rolled when that attack deals damage.
    int hitDiceCount; //How many Dice?
    string hitType; //Is the attack Melee or Ranged? is it spell based?
};

struct enemy
{
    //Defines data needed to define an enemy.
    ~enemy()
    {
        int i;
        for (i = 0; i < int(attacks.size()); i++)
        {
            delete attacks[i];
        }
    }
    string name;
    string effectiveName;
    int str; //Stregth, one of 6 dnd attributes that all characters have.
    int dex; //Dexterity
    int con; //Constitution
    int itl; //Intelligence. This is the only one who's abbreviation is different than the standard, as the standard abbreviation is reserved (int)
    int wis; //Wisdom
    int cha; //Charisma
    int ac; //Armor Class. Attacks must roll "to hit" against this number.
    int hp; //Maximum HP.
    int effectiveHP; //Current HP
    vector<attack*> attacks; //All Available Attacks.
    vector<string> traits; //All traits, such as damage immunities, saving throw bonuses, or languages spoken.
    vector<string> actions; //Extra combat actions.
};

void usage();
enemy* makeEnemy (string inFile);
