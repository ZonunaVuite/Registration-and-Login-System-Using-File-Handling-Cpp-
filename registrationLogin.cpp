#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

//DECPORATE
int decorate(int head)
{
    system("cls");
    cout<<    "\t\t\t_________________________________________________________________________________\n\n\n";
    switch(head)
    {
    case 1:
        cout<< "\t\t\t                                                                   morning_world\n";
        cout<< "\t\t\t                                  LOGIN\n";
        cout<< "\t\t\t                                  -----\n";
        break;
    case 2:
        cout<< "\t\t\t                                                                   morning_world\n";
        cout<< "\t\t\t                            WELCOME TO REGISTRATION PAGE\n";
        cout<< "\t\t\t                            ----------------------------\n";
        break;
    case 3:
        cout<< "\t\t\t                                                                   morning_world\n";
        cout<< "\t\t\t                                FORGOT PASSWORD PAGE\n";
        cout<< "\t\t\t                                --------------------\n";
        break;

    }
    cout<<     "\t\t\t||                                                                            ||\n";
    cout<<     "\t\t\t||                                                                            ||\n";
    cout<<     "\t\t\t||                                                                            ||\n\n\n";

    return 1;

}
bool validatePassword(string rPassword)
{
    if(rPassword.length() < 8)
    {
        return false;
    }
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for(char cha : rPassword)
    {
        if(isupper(cha))
        {
            hasUpper = true;
        }
        else if(islower(cha))
        {
            hasLower = true;
        }
        else if(isdigit(cha))
        {
            hasDigit = true;
        }
        else if(!isalnum(cha))
        {
            hasSpecial = true;
        }
        if(hasUpper && hasLower && hasDigit && hasSpecial)
        {
            break;
        }

    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}


//LOGIN
void login()
{
    int count = 0, head = 1, result;
    char a;
    string userId, password, id, pass;
    do{
    system("cls");
    result = decorate(head);
    cout<< "\t\t\tPlease enter your username and password:\n\n";
    cout<< "\t\t\tUsername : ";
    cin>>userId;
    cout<< "\t\t\tPassword : ";
    cin>>password;

    ifstream input("record.txt");

    while(input>>id>>pass)
    {
        if(id==userId && pass == password)
        {
            count = 1;
            system("cls");
        }
    }
    input.close();
    if(count==1)
    {
        cout<< "\t\t\tYour LOGIN is successful."<<endl<<endl<<endl;
    }
    else
    {
        cout<< "\t\t\tIncorrect username or password. Do you want to enter again ? (y/n) : ";
        cin>>a;
        if(a=='y'|| a == 'Y')
        {
            system("cls");
            continue;
        }
        else
        {
            cout<< "\t\t\tDo you want to go for REGISTRATION ? (y/n) : ";
            cin>>a;
            if(a=='y'|| a == 'Y')
            {
                system("cls");

            }
            else
            {

            }
        }
    }
    }while(a=='y'|| a == 'Y');
}



//GENERATE ID
string generateUserId()
{
    ifstream idFile("id.txt");
    int lastId = 0;

    if(idFile.is_open())
    {
        idFile >> lastId;
        idFile.close();
    }

    lastId++;

    ofstream outFile("id.txt", ios::trunc);
    if(outFile.is_open())
    {
        outFile << lastId;
        outFile.close();
    }

    string numericId = to_string(lastId);
    numericId = string(7 - numericId.length(), '0') + numericId;


    return "MRW" + numericId;
}


//REGISTRATION
bool registration()
{
    string rUserId, rPassword, rId, rPass, rPassC, usedUserId;
    bool registrationSuccess = false;
    int head = 2,result,count = 0;

    do{
    system("cls");
    result = decorate(head);

    cout<< "\t\t\tEnter your username : ";
    cin>>rUserId;

    ifstream f2("record.txt");
    while(f2>>usedUserId)
    {
        string dummyId, dummyPass;
        f2 >> dummyId >> dummyPass;

        if(usedUserId == rUserId)
        {
            count = 1;
            break;
        }
    }
    f2.close();
    if(count == 1)
    {
        cout<< "\t\t\t "<< rUserId<< " has been taken, try another one.";
        Sleep(3000);
        count = 0;
        continue;

    }
    cout<<endl;

    cout<< "\t\t\tYour password characters should be at least 8 characters.\n\t\t\tIt should contain Upper Case, Lower Case, Number and Special Character."<<endl;
    cout<<endl;
    cout<< "\t\t\tEnter your password : ";
    cin>>rPassword;

    //confirm password
    cout<< "\t\t\tConfirm your password : ";
    cin>>rPassC;

    if(rPassword != rPassC)
    {
        cout<< "\t\t\tPassword and Confirm Password does not match!"<<endl<<endl;
        Sleep(3000);
        system("cls");
        continue;
    }
    //CHECK
    if(!validatePassword(rPassword))
    {
        cout<< "\t\t\tYour password does not match the requirement. Please enter more strong password."<<endl<<endl;
        Sleep(3000);
        system("cls");
        continue;
    }

    string newUserId = generateUserId();



    ofstream f1("record.txt", ios::app);
    f1<< newUserId << " " << rUserId<< " "<<rPassword<<endl<<endl;
    f1.close();

    cout<< "\t\t\tYour User Id is "<< newUserId << endl<<endl;


    registrationSuccess = true;




    if(registrationSuccess){
        cout<< "\t\t\t REGISTRATION is successful."<<endl<<endl;
        char s;
        cout<< "Do you want to go the login page (y/n): ";
        cin>>s;
        if(s == 'y' && s == 'Y')
        {
            login();
        }
        else
        {
            return 1;
        }
    }



    }while(!registrationSuccess);

    return registrationSuccess;
}

void forgot()
{
    int option, result,head = 3;
    bool account = false;


    do
    {
        result = decorate(head);
        cout<< "\t\t\tYou forgot the password ?\n\n";
        cout<< "\t\t\tPress '1' to search your account using your USERNAME. "<<endl;
        cout<< "\t\t\tPress '2' to go back to the main menu. "<<endl<<endl;
        cout<< "\t\t\tEnter your choice: ";
        cin>> option;

        switch(option)
        {
        case 1:
            {
                int count = 0;
                string sUserId, sId, sPass;
                cout<< "\n\n\t\t\tEnter your USERNAME : ";
                cin>>sUserId;

                ifstream f2("record.txt");
                while(f2>>sId>>sPass)
                {
                    if(sId == sUserId)
                    {
                        count = 1;
                        break;
                    }
                }
                f2.close();
                if(count == 1)
                {
                    cout<< "\n\n\n\t\t\tYour account is found.\n";
                    cout<< "\n\t\t\tYour password is : "<< sPass<<endl<<endl;
                    account = true;
                    Sleep(3000);
                    break;

                }
                else
                {
                    cout<< "\t\t\tYour account is not found.\n";
                    Sleep(4000);
                    system("cls");
                    continue;
                }
            }
        case 2:
            {
                account = true;
                break;
            }
        default:
            {
                cout << "\t\t\tInvalid option. Please try again.\n";
                Sleep(2000);
                system("cls");
                continue;
            }
        }
    }while(!account);

}


int confirmExit() // Change name and return type to int
{
    system("cls");

    char a;
    cout << "\t\t\tAre you really want to exit (y/n): "; // Fixed prompt format
    cin >> a;

    if (a == 'y' || a == 'Y')
    {
        system("cls");
        return 0; // Indicates exit
    }
    else
    {
        return 1; // Indicates not exiting
    }
}



void byebye()
{

    cout<<endl<<endl;
    cout<< "\t\t\t                                 THANK YOU!\n";
    cout<< "\t\t\t                                 ----------";
}

int main()
{
    int choice,count;
    char a;
    do{
    cout<< "\t\t\t_________________________________________________________________________________\n\n\n";
    cout<< "\t\t\t                        M O R N I N G       W  O  R  L  D\n\n";
    cout<< "\t\t\t                                      MENU\n";
    cout<< "\t\t\t                                      ----\n\n\n";
    cout<< "\t\t\t|| 1. Press '1' to LOGIN                                                          ||\n";
    cout<< "\t\t\t|| 2. Press '2' to REGISTER                                                       ||\n";
    cout<< "\t\t\t|| 3. Press '3' if you forgot your PASSWORD                                       ||\n";
    cout<< "\t\t\t|| 4. Press '4' to EXIT                                                           ||\n\n\n";

    cout<< "\t\t\tPlease enter your choice : ";
    cin>>choice;

    switch(choice)
    {
    case 1:
        login();
        break;
    case 2:
        registration();
        break;
    case 3:
        forgot();
        break;
    case 4:
        {
            if(confirmExit() == 0)
            {
                byebye();
                return 0;
            }
            break;
        }
    default:
        cout<<endl<<endl;
        cout<< "\t\t\tPlease enter valid option!.\n\n";
    }

    cout<< endl;
    cout<< "\t\t\tDo you want to enter your choice again ? (y/n) : ";
    cin>>a;

    system("cls");
    }while(a == 'y' || a == 'Y');
    byebye();

    return 0;
}
