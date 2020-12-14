//This Document was Written by Aiden Tracy.
//Please see Parse.h for this code's purpose.

#include "../../include/parse.h"
 
void usage()
{
    //Provide the user with proper calling format.
    cout << "Usage: (call) -i (file)" << endl;
}

enemy* makeEnemy (string inFile)
{
    //Make an enemy from a file.
    ifstream fileInput;

    //Validate the Input File.
    fileInput.open(inFile);
    if(!fileInput)
    {
        cout << "ERROR: INVALID FILE " << inFile << endl;
        return nullptr;
    }

    //Start buiding the enemy.
    enemy* newEnemy = new enemy;
    string temp;
    string temp2;
    //The first line of a stat block will be the enemy's name.
    getline(fileInput,temp);
    (*newEnemy).name = temp;
    (*newEnemy).effectiveName = temp;
    //The next line of a stat block is the enemy's size and alignment, which will be stored as traits.
    getline(fileInput,temp);
    (*newEnemy).traits.push_back(temp);
    //The next line is blank.
    getline(fileInput,temp);
    //The next line has armor class. We need to remove the text, which is a fixed count of characters, then get the number.
    getline(fileInput,temp);
    temp = temp.substr(16,temp.length());
    (*newEnemy).ac = stoi(temp);
    //The next line has hit points, stored much the same There is now extra data at the end we must remove.
    getline(fileInput,temp);
    temp = temp.substr(15,temp.length());
    temp = temp.substr(0, temp.find(" "));
    (*newEnemy).hp = stoi(temp);
    (*newEnemy).effectiveHP = (*newEnemy).hp;
    //Next is speed, which we will store as a trait.
    getline(fileInput,temp);
    temp = temp.substr(4,temp.length());
    (*newEnemy).traits.push_back(temp);
    //The next line is blank.
    getline(fileInput,temp);
    //The next line Contains a useless identifer.
    getline(fileInput,temp);
    //The next line contains a stat, so we need to parse that line to get it.
    getline(fileInput,temp);
    temp = temp.substr(temp.find("("),temp.find(")"));
    temp = temp.substr(1,(temp.length()-2));
    (*newEnemy).str = stoi(temp);
    //The next line Contains a useless identifer.
    getline(fileInput,temp);
    //The next line contains a stat, so we need to parse that line to get it.
    getline(fileInput,temp);
    temp = temp.substr(temp.find("("),temp.find(")"));
    temp = temp.substr(1,(temp.length()-2));
    (*newEnemy).dex = stoi(temp);
    //The next line Contains a useless identifer.
    getline(fileInput,temp);
    //The next line contains a stat, so we need to parse that line to get it.
    getline(fileInput,temp);
    temp = temp.substr(temp.find("("),temp.find(")"));
    temp = temp.substr(1,(temp.length()-2));
    (*newEnemy).con = stoi(temp);
    //The next line Contains a useless identifer.
    getline(fileInput,temp);
    //The next line contains a stat, so we need to parse that line to get it.
    getline(fileInput,temp);
    temp = temp.substr(temp.find("("),temp.find(")"));
    temp = temp.substr(1,(temp.length()-2));
    (*newEnemy).itl = stoi(temp);
    //The next line Contains a useless identifer.
    getline(fileInput,temp);
    //The next line contains a stat, so we need to parse that line to get it.
    getline(fileInput,temp);
    temp = temp.substr(temp.find("("),temp.find(")"));
    temp = temp.substr(1,(temp.length()-2));
    (*newEnemy).wis = stoi(temp);
    //The next line Contains a useless identifer.
    getline(fileInput,temp);
    //The next line contains a stat, so we need to parse that line to get it.
    getline(fileInput,temp); 
    temp = temp.substr(temp.find("("),temp.find(")"));
    temp = temp.substr(1,(temp.length()-2));
    (*newEnemy).cha = stoi(temp);
    //The next lines asre no longer consistent. We have to sort though a variety of traits to find the attacks.
    getline(fileInput,temp);
    bool good = true;
    while (fileInput && !(fileInput.eof()) && good)
    {
        if(temp == "Actions")
        {
            //If we arrive at the Actions line, the data will once again have a consistent format.
            good = false;
        }
        else
        {
            //check if line is empty
            if(temp != "")
            {
                //Line contains a trait, so add it.
                (*newEnemy).traits.push_back(temp);
            }
            getline(fileInput,temp);
        }
        
    }
    //The next line is blank.
    getline(fileInput,temp);
    //The next lines contain attacks, but may also contain other actions or blank lines.
    getline(fileInput,temp);
    good = true;
    while (fileInput && !(fileInput.eof()) && good)
    {
        if(temp == "")
        {
            //If we find a blank line, we've seen all the attacks.
            good = false;
        }
        else
        {
            temp = temp.substr(4,temp.length());
            //If we find content, it will either be an attack or action.
            if(temp.find("Hit:") != temp.npos)
            {
                //If we find the word hit, we have an attack, so gather the data.
                attack* newAttack = new attack;
                temp2 = temp.substr(0,temp.find("."));
                cout << temp2 << endl;
                (*newAttack).name = temp2;
                temp2 = temp.substr(temp.find("."),temp.find(":"));
                temp2 = temp2.substr(2,(temp2.find(":")-1));
                cout << temp2 << endl;
                (*newAttack).hitType = temp2;
                temp2 = temp.substr(temp.find(":"), temp.find(" "));
                temp2 = temp2.substr(2,(temp2.length()-1));
                (*newAttack).toHit = stoi(temp2);
                temp = temp.substr(temp.find("("),temp.find(")"));
                temp2 = temp.substr(0,temp.find("d"));
                temp2 = temp2.substr(1,temp2.length());
                (*newAttack).hitDiceCount = stoi(temp2);
                temp2 = temp.substr(temp.find("("),temp.length());
                temp2 = temp2.substr(temp2.find("d"),temp2.find(")"));
                temp2 = temp2.substr(1,(temp2.length()-1));
                (*newAttack).hitDice = stoi(temp2);
                (*newEnemy).attacks.push_back(newAttack);
            }
            else
            {
                //It was an action, so add it.
                (*newEnemy).actions.push_back(temp);
            }
            getline(fileInput,temp);
        }  
    }
    //There still may be some actions, so find them.
    while (fileInput && !(fileInput.eof()))
    {
        if(temp.find("    ") != temp.npos)
        {
            (*newEnemy).actions.push_back(temp);
        }
        getline(fileInput,temp);
    }

    //close file input.
    fileInput.close();
    return newEnemy;
}