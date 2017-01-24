#include <iostream>

using namespace std;

void prtRotors(bool* availRotors);
void selectRotors(int* rotorOrder, bool* availRotors, int order);
void rotateRing(int* rotor, int &count);
void rotateArray(int* array, int size);
void decrementArray(int* array, int size);
void invertArray(int* array, int size);
char encrypt(char In, int** rotors, int* rotorOrder, bool reflector, int** reflectors);

int main() {
    int rotor1[26] = {4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9};
    int rotor2[26] = {0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4};
    int rotor3[26] = {1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14};
    int rotor4[26] = {4,18,14,21,15,25,9,0,24,16,20,8,17,7,23,11,13,5,19,6,10,3,2,12,22,1};
    int rotor5[26] = {21,25,1,17,6,8,19,24,20,15,18,3,13,7,11,23,0,22,12,9,16,14,5,4,2,10};

    int reflectB[26] = {24,17,20,7,16,18,11,3,15,23,13,6,14,10,12,8,4,1,5,25,2,22,21,9,0,19};
    int reflectC[26] = {17,3,14,1,9,13,19,10,21,4,7,12,11,5,2,22,25,0,23,6,24,8,15,18,20,16};

    int rotorStep[5] = {17, 5, 22, 10, 0};

    int* rotors[5] = {rotor1, rotor2, rotor3, rotor4, rotor5};
    int* reflectors[2] = {reflectB, reflectC};
    
    bool availRotors[5] = {true, true, true, true, true};
    //Stores 3 rotors selected by the user
    int rotorOrder[3] = {-1, -1, -1};
    
    //Integers to keep track of rotor position for stepping motion
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    
    cout << "Select First Rotor:\n";
    prtRotors(availRotors);
    selectRotors(rotorOrder, availRotors, 1);
    
    cout << "Select Second Rotor:\n";
    prtRotors(availRotors);
    selectRotors(rotorOrder, availRotors, 2);
    
    cout << "Select Last Rotor:\n";
    prtRotors(availRotors);
    selectRotors(rotorOrder, availRotors, 3);
    
    cout << "Your rotor selections : ";
    for(int i=0; i<3; ++i){
        cout << rotorOrder[i]+1 << "  ";
    }
    cout << "\n-----------------------------------------------------\n";
    
    cout << "Select reflectors.\n";
    cout << "Available reflectors : B C\n";
    cout << "Default reflector is type B. ";
    bool reflector = true;
    while(true){
        char input;
        cin >> input;
        if(!(input == 'b' or input == 'c' or input == 'B' or input =='C')){
            cout << "Invalid Response\n";
            cin.clear();
            cin.ignore(512, '\n');
            continue;
        }
        else{
            if(!(input == 'b' or input == 'B'))
                reflector = false;
            break;
        }
    }
    cout << "\n-----------------------------------------------------\n";
    cout << "Select initial ring positions.\nRotor1 : ";
    rotateRing(rotors[rotorOrder[0]], count1);
    cout << "\nRotor2 : ";
    rotateRing(rotors[rotorOrder[1]], count2);
    cout << "\nRotor3 : ";
    rotateRing(rotors[rotorOrder[2]], count3);
    cout << "\n-----------------------------------------------------\n";

    
    cout << "Enter message to be encrypted/decrypted.\n";
    string input;
    cin.ignore(512, '\n');
    getline(cin, input, '\n');
    cin.ignore(512, '\n');
    

    
    cout << "Resulting message\n";
    for(int i=0; i<input.length(); ++i){
        char temp = input[i];
        int temp2 = (int)temp;
        if(!((temp2 >= 65 and temp2 <= 90) or (temp2 >= 97 and temp2 <= 122))){
            cout << temp;
            continue;
        }
        rotateArray(rotors[rotorOrder[0]], 26);
        decrementArray(rotors[rotorOrder[0]], 26);
        ++count1;
        count1 %= 26;
        if(count1 == rotorStep[rotorOrder[0]]){
            rotateArray(rotors[rotorOrder[1]], 26);
            decrementArray(rotors[rotorOrder[1]], 26);
            ++count2;
            count2 %= 26;
        }
        if(count2 == rotorStep[rotorOrder[1]] or count2 == (rotorStep[rotorOrder[1]]+1)){
            rotateArray(rotors[rotorOrder[2]], 26);
            decrementArray(rotors[rotorOrder[2]], 26);
            ++count3;
            count3 %= 26;
        }
        cout << encrypt(temp, rotors, rotorOrder, reflector, reflectors);
    }
    
    cout << "\n";
    return 0;
}

void prtRotors(bool* availRotors){
    cout << "Available Rotors : ";
    for(int i=0; i<5; ++i){
        if(availRotors[i])
            cout << (i+1) << "  ";
    }
    cout << "\n";
}

void selectRotors(int* rotorOrder, bool* availRotors, int order){
    while(true){
        int selection;
        cin >> selection;
        if(!((selection == 1) or (selection == 2) or (selection == 3) or (selection == 4) or (selection == 5))){
            cout << "Invalid Response.\n";
            cin.clear();
            cin.ignore(512, '\n');
            continue;
        }
        else{
            if(!(availRotors[selection-1])){
                cout << "You have already selected this rotor. Try another.\n";
                cin.clear();
                cin.ignore(512, '\n');
                continue;
            }
            else{
                availRotors[selection-1] = false;
                rotorOrder[order-1] = selection-1;
                break;
            }
        }
    }
    return;
}

void rotateRing(int* rotor, int &count){
    while(true){
        char selection;
        int serialize;
        cin >> selection;
        serialize = (int) (selection);
        if(!((serialize >= 65 and serialize <= 90) or (serialize >= 97 and serialize <= 122))){
            cout << "Invalid Choice : Select an alphabet.\n";
            continue;
        }
        else{
            if(serialize >= 65 and serialize <= 90)
                serialize -= 65;
            else
                serialize -= 97;
            for(int i=0; i< serialize; ++i){
                rotateArray(rotor, 26);
                decrementArray(rotor, 26);
                ++count;
                if(count == 26)
                    count -= 26;
            }
            break;
        }
    }
    return;
}


void rotateArray(int* array, int size){
    int temp = *array;
    for(int i=0; i<size-1; ++i){
        *(array+i) = *(array+i+1);
    }
    *(array+(size-1)) = temp;
    return;
}

void decrementArray(int* array, int size){
    for(int i=0; i<size; ++i){
        *(array+i) -= 1;
        if(*(array+i) < 0)
            *(array+i) += 26;
    }
    return;
}

void invertArray(int* array, int size){
    int temp[size];
    for(int i=0; i<size; ++i){
        temp[*(array+i)] = i;
    }
    
    for(int i=0; i<size; ++i)
        *(array+i) = *(temp+i);
        
    return;
}

char encrypt(char In, int** rotors, int* rotorOrder, bool reflector, int** reflectors){
    int temp = (int)In;
    if(temp >= 65 and temp <= 90)
        temp -= 65;
    else if(temp >= 97 and temp <= 122)
        temp -= 97;
    else
        return In;
        
    int firstPass = 0;
    int reflect = 1;
    int secondPass = 0;
    int* rotorFirst = *(rotors+(*(rotorOrder)));
    int* rotorSecond = *(rotors+(*(rotorOrder+1)));
    int* rotorThird = *(rotors+(*(rotorOrder+2)));
    
    firstPass = *(rotorFirst+temp);
    firstPass = *(rotorSecond+firstPass);
    firstPass = *(rotorThird+firstPass);

    if(reflector)
        reflect = *((*(reflectors))+firstPass);
    else
        reflect = *((*(reflectors+1))+firstPass);
        

    invertArray(rotorFirst, 26);
    invertArray(rotorSecond, 26);    
    invertArray(rotorThird, 26);
    secondPass = *(rotorThird+reflect);
    secondPass = *(rotorSecond+secondPass);
    secondPass = *(rotorFirst+secondPass);

    invertArray(rotorFirst, 26);
    invertArray(rotorSecond, 26);    
    invertArray(rotorThird, 26);
    
    return (char)(secondPass+65);
}
