//This Document was Written by Aiden Tracy.
//Please see Parse.h for this code's purpose.

#include "../../include/parse.h"
 
int main(int argc, char* argv[])
{
    //declare variables
    ifstream fileInput;
    string temp;
    int i, j, k;
    int dice;
    int count;
    int sum;
    int temp2;
    int choice, choice2, choice3;
    char charChoice;
    string strChoice;
    bool running = true;
    bool choiceValid = true;
    bool choice2Valid = true;
    bool choice3Valid = true;
    vector<enemy*> enemyList;

    //Validate Argumenhts
    if (argc != 3)
    {
        usage();
        return 1;
    }
    if(strcmp(argv[i],"-i")==0)
    {
        usage();
        return 1;
    }

    fileInput.open(argv[2]);
    if(!fileInput)
    {
        cout << "ERROR: File not readable." << endl;
        return 1;
    }
    else
    {
        //Read in other files, since valid file argument was passed.
        while(fileInput && !(fileInput.eof()))
        {
            getline(fileInput, temp);
            temp += ".txt";
            enemyList.push_back(makeEnemy(temp));
        }
    }
    //close file handle.
    fileInput.close();
    //provide functionality
    srand(time(NULL));
    while(running)
    {
        //List Enemies, Ask Which one the user would like to work with.
        choiceValid = false;
        system("clear");
        for(i = 0; i < enemyList.size(); i++)
        {
            cout << i << ". " << (*enemyList[i]).effectiveName << " (" << (*enemyList[i]).name << ")" << endl;
        }
        cout << "Please input the number of the enemy you wish to modify or input " << i << " to Quit Program." << endl;

        while(!choiceValid)
        {
            cin >> choice;
            cout << endl;
            if (choice < i && choice >= 0)
            {
                //List Enemy information and ask what information the user would like to use or modify.
                choiceValid = true;
                system("clear");
                cout << (*enemyList[choice]).effectiveName << " (" << (*enemyList[choice]).name << ")" << endl;
                cout << (*enemyList[choice]).effectiveHP << "/" << (*enemyList[choice]).hp << " Hit Points" << endl;
                cout << (*enemyList[choice]).ac << " AC"<< endl;
                choice2Valid = false;
                cout << "Please choose an action from the list below." << endl;
                cout << "0. Do Nothing." << endl;
                cout << "1. View/Perform Attacks" << endl;
                cout << "2. Make Saving Throw" << endl;
                cout << "3. Take Damage" << endl;
                cout << "4. Restore HP" << endl;
                cout << "5. View Traits and Special Abilities" << endl;
                cout << "6. View Actions" << endl;
                cout << "7. Change Name" << endl;
                while(!choice2Valid)
                {
                    choice2Valid = true;
                    cin >> choice2;
                    cout << endl;
                    switch(choice2)
                    {
                        case 0:
                            //If the user would like to do nothing, exit back to the enemy list.
                        break;
                        case 1:
                            //List attacks and ask which one the user would like to use.
                            choice3Valid = false;
                            cout << "Which Attack?" << endl;
                            for(j = 0; j < (*enemyList[choice]).attacks.size(); j++)
                            {
                                cout << j << ". " << (*(*enemyList[choice]).attacks[j]).name << ", " << (*(*enemyList[choice]).attacks[j]).hitType << " +" << (*(*enemyList[choice]).attacks[j]).toHit << " to hit, " << (*(*enemyList[choice]).attacks[j]).hitDiceCount << "d" << (*(*enemyList[choice]).attacks[j]).hitDice << " damage." << endl;
                            }
                            cout << j << ". Never Mind." << endl;
                            while(!choice3Valid)
                            {
                                cin >> choice3;
                                cout << endl;
                                if(choice3 < j && choice3 >= 0)
                                {
                                    //If the user chose an attack, perform it and display the results.
                                    strChoice = "";
                                    temp2 = rand() % 20 + 1;
                                    sum = temp2 + (*(*enemyList[choice]).attacks[choice3]).toHit;
                                    strChoice += to_string(temp2);
                                    strChoice += " + ";
                                    strChoice += to_string((*(*enemyList[choice]).attacks[choice3]).toHit);
                                    strChoice += " = ";
                                    strChoice += to_string(sum);
                                    strChoice += " To hit, ";
                                    sum = 0;
                                    for(k = 0; k < (*(*enemyList[choice]).attacks[choice3]).hitDiceCount; k++)
                                    {
                                        if(k != 0)
                                        {
                                            strChoice += " + ";
                                        }
                                        temp2 = rand() % (*(*enemyList[choice]).attacks[choice3]).hitDice + 1;
                                        strChoice += to_string(temp2);
                                        sum += temp2;
                                    }
                                    strChoice += " = ";
                                    strChoice += to_string(sum);
                                    strChoice += " Damage.";
                                    cout << strChoice << endl;
                                    cout << "Input Anything to continue." << endl;
                                    cin >> strChoice;
                                    choice3Valid = true;
                                }
                                else if(choice3 == j)
                                {
                                    //If the user chose to not perform an attack, exit
                                    choice3Valid = true;
                                }
                                else
                                {
                                    //If the user input an ivalid response, repeat input.
                                    cout << "Invalid Choice." << endl;
                                } 
                            }
                        break;
                        case 2:
                            //If the user wants to make a saving throw, display the stat list.
                            choice3Valid = false;
                            cout << "Which Stat? (Make sure to check abilities for additonal modifiers!)" << endl;
                            cout << "0. Never Mind." << endl;
                            cout << "1. STR" << endl;
                            cout << "2. DEX" << endl;
                            cout << "3. CON" << endl;
                            cout << "4. INT" << endl;
                            cout << "5. WIS" << endl;
                            cout << "6. CHA" << endl;
                            while(!choice3Valid)
                            {
                                choice3Valid = true;
                                cin >> choice3;
                                cout << endl;
                                switch(choice3)
                                {
                                    //if they chose a stat, make the saving throw for that stat, then display the results.
                                    case 0:
                                    break;
                                    case 1:
                                        dice = rand() % 20 + 1;
                                        cout << dice << " + " << (*enemyList[choice]).str << " = " << (dice + (*enemyList[choice]).str) << endl;
                                    break;
                                    case 2:
                                        dice = rand() % 20 + 1;
                                        cout << dice << " + " << (*enemyList[choice]).dex << " = " << (dice + (*enemyList[choice]).dex) << endl;
                                    break;
                                    case 3:
                                        dice = rand() % 20 + 1;
                                        cout << dice << " + " << (*enemyList[choice]).con << " = " << (dice + (*enemyList[choice]).con) << endl;
                                    break;
                                    case 4:
                                        dice = rand() % 20 + 1;
                                        cout << dice << " + " << (*enemyList[choice]).itl << " = " << (dice + (*enemyList[choice]).itl) << endl;
                                    break;
                                    case 5:
                                        dice = rand() % 20 + 1;
                                        cout << dice << " + " << (*enemyList[choice]).wis << " = " << (dice + (*enemyList[choice]).wis) << endl;
                                    break;
                                    case 6:
                                        dice = rand() % 20 + 1;
                                        cout << dice << " + " << (*enemyList[choice]).cha << " = " << (dice + (*enemyList[choice]).cha) << endl;
                                    break;
                                    default:
                                    //If the user put something invalid, repeat input.
                                        cout << "Invalid Choice." << endl;
                                        choice3Valid = false;
                                    break;
                                }
                            }
                            cout << "Input Anything to continue." << endl;
                            cin >> strChoice;
                        break;
                        case 3:
                        //If they chose to deal damage, ask how much, then perform the calculations.
                        cout << "How much?" << endl;
                            cin >> choice3;
                            cout << endl;
                            (*enemyList[choice]).effectiveHP -= choice3;
                            //Minimum HP is 0.
                            if((*enemyList[choice]).effectiveHP < 0)
                            {
                                (*enemyList[choice]).effectiveHP = 0;
                            }
                        break;
                        case 4:
                        //If they chose to restore health, ask how much, then perform the calculations.
                            cout << "How much?" << endl;
                            cin >> choice3;
                            cout << endl;
                            (*enemyList[choice]).effectiveHP += choice3;
                            //observe maximum health.
                            if((*enemyList[choice]).effectiveHP > (*enemyList[choice]).hp)
                            {
                                (*enemyList[choice]).effectiveHP = (*enemyList[choice]).hp;
                            }
                        break;
                        case 5:
                        //If they chose to list traits, list them.
                        for(j = 0; j < ((*enemyList[choice])).traits.size(); j++)
                            {
                                cout << (*enemyList[choice]).traits[j] << endl;
                            }
                        cout << "Input Anything to continue." << endl;
                        cin >> strChoice;
                        break;
                        case 6:
                        //If they chose to list actions, list them.
                            for(j = 0; j < ((*enemyList[choice])).actions.size(); j++)
                            {
                                cout << (*enemyList[choice]).actions[j] << endl;
                            }
                        cout << "Input Anything to continue." << endl;
                        cin >> strChoice;
                        break;
                        case 7:
                        //If they chose to change the name, ask for what to change it to, then perform the modification.
                            cout << "What should it's name be?" << endl;
                            cin.ignore();
                            getline(cin,strChoice);
                            cout << endl;
                            (*enemyList[choice]).effectiveName = strChoice;
                        break;
                        default:
                        //If the choice was invalid, make another selection.
                            cout << "Invalid Choice." << endl;
                            choice2Valid = false;
                        break;
                    }
                }
            }
            else if (choice == i)
            {
                //If they chose to quit, ask if they are sure. If they say yes, prepare to quit.
                choiceValid = true;
                choice2Valid = false;
                cout << "Are you sure you would like to quit? (y/n)" << endl;
                while(!choice2Valid)
                {
                    cin >> charChoice;
                    cout << endl;
                    if(charChoice == 'y' || charChoice == 'Y')
                    {
                        running = false;
                        choice2Valid = true;
                    }
                    else if(charChoice == 'n' || charChoice == 'N')
                    {
                        choice2Valid = true;
                    }
                    else
                    {
                        //If the choice was invalid, make another selection.
                        cout << "Invalid Choice. Please try again." << endl;
                    }
                    
                }

            }
            else
            {
                //If the choice was invalid, make another selection.
                cout << "Invalid Choice. Please try again." << endl;
            }
            
        }
        
    }

    //clean up memory and exit.
    for(i = 0; i < enemyList.size(); i++)
    {
        delete enemyList[i];
    }
    return 0;
}
