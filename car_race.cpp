//constructor,friend function,operator overloading,inheritance,pure virutal,abstract class,templates,stl(vector,sorting),file handling
#include<bits/stdc++.h>
#include<algorithm>
#include<conio.h>
#include<direct.h>//directory handling
#include<string.h>
#include<windows.h>//HANDLE,COORD,CursorPosition,SetConsoleCursorPosition,DWORD,CONSOLE_CURSOR_INFO,lpCursor,Sleep
#include<time.h>//to get and manipulate date and time info
#include<fstream>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70//window width
using namespace std;
fstream outputFile1("easyScores.txt",ios::in | ios::out | ios::app);
fstream outputFile2("mediumScores.txt",ios::in | ios::out | ios::app);
fstream outputFile3("hardScores.txt",ios::in | ios::out | ios::app);
fstream outputFile4("feedbacks.txt",ios::in | ios::out | ios::app);
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//a key an OS uses to identify all objects contained in it
COORD CursorPosition;// coordinates of a character cell in a console screen buffer.
int carPos = WIN_WIDTH/2;
int score = 0;
const char car[4][4] = {' ', '±', '±', ' ',
                        '±', '*', '*', '±',
                        ' ', '*', '*', ' ',
                        '±', '*', '*', '±',
                       };
int enemyY[5];
int enemyX[5];
int enemyFlag[3];
void gotoxy(int x, int y)//for positioning car,enemy car & others
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void getMenu();
void setcursor(bool visible, DWORD size)//dword double word specific to windows
{
    if(size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;//percentage  of the character cell that is filled by the cursor
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo (console, &lpCursor);
}
void gameover()
{
    system("cls");
    cout << "\n\n\t\t\tGAME OVER.";
    getch();
}
void instructions()
{
    system("cls");//clear screen
    gotoxy(50,5);//to move the cursor on the screen to the desired location
    cout << " ------------------- ";
    gotoxy(50,6);
    cout << " |     CAR GAME    |";
    gotoxy(50,7);
    cout << " ------------------- ";
    gotoxy(40,9);
    cout << "Avoid the cars by moving left (A) and right (D)" << endl;
    gotoxy(40,14);
    cout << "Press any key to continue";
    getch();
}
class GameMode
{
public:
    virtual void updateScore()=0;
};
class easyClass:public GameMode
{
    string name;
    int score;
public:
    easyClass()
    {
        name="";
    }
    easyClass(string name)
    {
        this->name=name;
    }
    void genEnemy(int ind)
    {
        enemyX[ind] = 17 + rand()%(33);
    }

    void drawEnemy(int ind)
    {

        if(enemyFlag[ind] == true)
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "|  |";
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "±**±";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout << " ** ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout << "±**±";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout << " ** ";
        }
    }
    void eraseEnemy(int ind)
    {
        if(enemyFlag[ind] == true)
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout << "     ";
        }
    }
    void resetEnemy(int ind)
    {
        eraseEnemy(ind);
        enemyY[ind] = 1;
        genEnemy(ind);
    }
    void drawBorder()
    {
        for(int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for(int j = 0; j < 17; j++)
            {
                gotoxy(0+j, i);
                cout << "±";
                gotoxy(WIN_WIDTH-j, i);
                cout << "±";
            }
        }
        for(int i = 0; i < SCREEN_HEIGHT; i++)
        {
            gotoxy(SCREEN_WIDTH, i);
            cout << "±";
        }
    }
    int collision()
    {
        if((enemyY[0]) + 4 >= 23)// checks if the enemy is close to the bottom of the screen
        {
            if(enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)//
            {
                return 1;
            }
        }
        return 0;
    }
    void updateScore()
    {
        gotoxy(WIN_WIDTH + 7, 5);
        cout << "Score: " << score << endl;
    }
    void drawCar()
    {
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout << car[i][j];
            }
        }
    }
    void eraseCar()
    {
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout << " ";
            }
        }
    }
    void enterScore(int a);
    void easyPlay()
    {
        carPos = -1 + WIN_WIDTH/2;
        score = 0;
        enemyFlag[0] = 1;
        enemyFlag[1] = 0;
        enemyY[0] = enemyY[1] = 1;
        system("cls");
        drawBorder();
        updateScore();
        genEnemy(0);
        genEnemy(1);
        gotoxy(WIN_WIDTH + 7, 2);
        cout << "THE CAR GAME";
        gotoxy(WIN_WIDTH + 6, 4);
        cout << "---------";
        gotoxy(WIN_WIDTH + 7, 12);
        cout << "CONTROLS:";
        gotoxy(WIN_WIDTH + 7, 13);
        cout << "---------";
        gotoxy(WIN_WIDTH + 2, 14);
        cout << "A - Left";
        gotoxy(WIN_WIDTH + 2, 15);
        cout << "D - Right";
        gotoxy(WIN_WIDTH + 2, 16);
        cout << "E - Exit";
        gotoxy(18, 5);
        cout << "Press any key to begin";
        getch();
        gotoxy(18, 5);
        cout << "                        ";
        while(1)
        {
            if(kbhit())
            {
                char ch = getch();
                if( ch == 'a' || ch == 'A')
                {
                    // Change speed of left
                    if( carPos > 18 )
                        carPos -= 4;
                }
                if( ch == 'd' || ch == 'D')
                {
                    // Change speed of right
                    if( carPos < 50 )
                        carPos += 4;
                }
                if( ch == 'e' || ch == 'E')
                {
                    getMenu();
                    break;
                }
                if(ch==27)
                {
                    break;
                }
            }
            drawCar();
            drawEnemy(0);
            drawEnemy(1);
            if ( collision() == 1)
            {
                EasyenterScore(score);
                gameover();
                return;
            }
            Sleep(50);
            eraseCar();
            eraseEnemy(0);
            eraseEnemy(1);
            if (enemyY[0] == 10)
                if( enemyFlag[1] == 0 )
                    enemyFlag[1] = 1;
            // speed of enemy
            if(enemyFlag[0] == 1)
                enemyY[0] += 1;

            if ( enemyFlag[1] == 1)
                enemyY[1] += 1;
            if(enemyY[0] > SCREEN_HEIGHT - 4)
            {
                resetEnemy(0);
                score++;
                updateScore();
            }
            if( enemyY[1] > SCREEN_HEIGHT- 4)
            {
                resetEnemy(1);
                score++;
                updateScore();
            }
        }
    }
    void EasyenterScore(int a)
    {
        system("cls");
        if(!outputFile1.is_open())
        {
            cerr<<"Error opening the file!"<<endl;
            exit(1);
        }
        score=a;
        cout<<"Enter your name :";
        cin>>name;
        outputFile1<<name<<" "<<score<<endl;
        outputFile1.close();
        // Read lines into a vector of strings
        outputFile1.open("easyScores.txt",ios::in | ios::out | ios::app);
        vector<string> lines;
        string line;
        while (getline(outputFile1, line))
        {
            lines.push_back(line);
        }
        sort(lines.begin(),lines.end());
        outputFile1.close();
        outputFile1.open("easyScores.txt", ios::out | ios::trunc);
        int no=lines.size();
        // Write the sorted lines back to the file
        for (int i=no-1; i>=0; i--)
        {
            outputFile1 << lines[i] << endl;
        }

        outputFile1.close();
    }

    void showLeaderboard()
    {
        system("cls");
        cout<<"****Leaderboard(Easy)****"<<endl;
        ifstream file1("easyScores.txt");
        string line;
        while(getline(file1,line))
        {
            cout<<line<<endl;
        }
        file1.close();
        cout<<"\n\nPress any key to go back";
        getch();
    }
};
class mediumClass:public GameMode
{
    string name;
    int score;
public:
    mediumClass()
    {
        name="";
    }
    mediumClass(string name)
    {
        this->name=name;
    }
    void genEnemy(int ind)
    {
        enemyX[ind] = 17 + rand()%(33);
    }
    void drawEnemy(int ind)
    {
        if(enemyFlag[ind] == true)
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "|  |";
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "0**0";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout << " ** ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout << "0**0";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout << " vv ";
        }
    }
    void eraseEnemy(int ind)
    {
        if(enemyFlag[ind] == true)
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout << "     ";
        }
    }
    void resetEnemy(int ind)
    {
        eraseEnemy(ind);
        enemyY[ind] = 1;
        genEnemy(ind);
    }
    void drawBorder()
    {
        for(int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for(int j = 0; j < 17; j++)
            {
                gotoxy(0+j, i);
                cout << "±";
                gotoxy(WIN_WIDTH-j, i);
                cout << "±";
            }
        }
        for(int i = 0; i < SCREEN_HEIGHT; i++)
        {
            gotoxy(SCREEN_WIDTH, i);
            cout << "±";
        }
    }
    int collision()
    {
        if((enemyY[0]) + 4 >= 23)
        {
            if(enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
            {
                return 1;
            }
        }
        return 0;
    }
    void updateScore()
    {
        gotoxy(WIN_WIDTH + 7, 5);
        cout << "Score: " << score << endl;
    }
    void drawCar()
    {
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout << car[i][j];
            }
        }
    }
    void eraseCar()
    {
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout << " ";
            }
        }
    }
    void mediumPlay()
    {
        system("color f");
        carPos = -1 + WIN_WIDTH/2;
        score = 0;
        enemyFlag[0] = 1;
        enemyFlag[1] = 0;
        enemyY[0] = enemyY[1] = 1;
        system("cls");
        drawBorder();
        updateScore();
        genEnemy(0);
        genEnemy(1);
        gotoxy(WIN_WIDTH + 7, 2);
        cout << "THE CAR GAME";
        gotoxy(WIN_WIDTH + 6, 4);
        cout << "---------";
        gotoxy(WIN_WIDTH + 7, 12);
        cout << "CONTROLS:";
        gotoxy(WIN_WIDTH + 7, 13);
        cout << "---------";
        gotoxy(WIN_WIDTH + 2, 14);
        cout << "A - Left";
        gotoxy(WIN_WIDTH + 2, 15);
        cout << "D - Right";
        gotoxy(WIN_WIDTH + 2, 16);
        cout << "E - Exit";
        gotoxy(18, 5);
        cout << "Press any key to begin";
        getch();
        gotoxy(18, 5);
        cout << "                        ";
        while(1)
        {
            if(kbhit())
            {
                char ch = getch();
                if( ch == 'a' || ch == 'A')
                {
                    // Change speed of left
                    if( carPos > 18 )
                        carPos -= 4;
                }
                if( ch == 'd' || ch == 'D')
                {
                    // Change speed of right
                    if( carPos < 50 )
                        carPos += 4;
                }
                if( ch == 'e' || ch == 'E')
                {
                    getMenu();
                    break;
                }
                if(ch==27)
                {
                    break;
                }
            }
            drawCar();
            drawEnemy(0);
            drawEnemy(1);
            if ( collision() == 1)
            {
                MediumenterScore(score);
                gameover();
                return;
            }
            Sleep(50);
            eraseCar();
            eraseEnemy(0);
            eraseEnemy(1);
            if (enemyY[0] == 10)
                if( enemyFlag[1] == 0 )
                    enemyFlag[1] = 1;
            // speed of enemy
            if(enemyFlag[0] == 1)
                enemyY[0] += 2;

            if ( enemyFlag[1] == 1)
                enemyY[1] += 1;
            if(enemyY[0] > SCREEN_HEIGHT - 4)
            {
                resetEnemy(0);
                score++;
                updateScore();
            }
            if( enemyY[1] > SCREEN_HEIGHT- 4)
            {
                resetEnemy(1);
                score++;
                updateScore();
            }
        }
    }
    void MediumenterScore(int a)
    {
        system("cls");
        if(!outputFile2.is_open())
        {
            cerr<<"Error opening the file!"<<endl;
            exit(1);
        }
        score=a;
        cout<<"Enter your name :";
        cin>>name;
        outputFile2<<name<<" "<<score<<endl;
        outputFile2.close();
    }
    void showLeaderboard()
    {
        system("cls");
        cout<<"****Leaderboard(Medium)****"<<endl;
        ifstream file2("mediumScores.txt");
        string line;
        while(getline(file2,line))
        {
            cout<<line<<endl;
        }
        file2.close();
        cout<<"\n\nPress any key to go back";
        getch();
    }
};
class hardClass
{
    string name;
    int score;
public:
    hardClass()
    {
        name="";
        score=0;
    }
    hardClass(string a,int b=0)
    {
        name=a;
    }
    void genEnemy(int ind)
    {
        enemyX[ind] = 17 + rand()%(33);
    }
    void drawEnemy(int ind)
    {
        if(enemyFlag[ind] == true)
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "|  |";
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "±UU±";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout << " ±± ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout << "±±±±";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout << " vv ";
        }
    }
    void eraseEnemy(int ind)
    {
        if(enemyFlag[ind] == true)
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout << "     ";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout << "     ";
        }
    }
    void resetEnemy(int ind)
    {
        eraseEnemy(ind);
        enemyY[ind] = 1;
        genEnemy(ind);
    }
    void drawBorder()
    {
        for(int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for(int j = 0; j < 17; j++)
            {
                gotoxy(0+j, i);
                cout << "±";
                gotoxy(WIN_WIDTH-j, i);
                cout << "±";
            }
        }
        for(int i = 0; i < SCREEN_HEIGHT; i++)
        {
            gotoxy(SCREEN_WIDTH, i);
            cout << "±";
        }
    }
    int collision()
    {
        if((enemyY[0]) + 4 >= 23)
        {
            if(enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
            {
                return 1;
            }
        }
        return 0;
    }
    void updateScore()
    {
        gotoxy(WIN_WIDTH + 7, 5);
        cout << "Score: " << score << endl;
    }
    void drawCar()
    {
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout << car[i][j];
            }
        }
    }
    void eraseCar()
    {
        for(int i = 0; i<4; i++)
        {
            for(int j = 0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout << " ";
            }
        }
    }
    void hardPlay()
    {
        system("color 6");
        carPos = -1 + WIN_WIDTH/2;
        score = 0;
        enemyFlag[0] = 1;
        enemyFlag[1] = 0;
        enemyY[0] = enemyY[1] = 1;
        system("cls");
        drawBorder();
        updateScore();
        genEnemy(0);
        genEnemy(1);
        genEnemy(2);
        genEnemy(3);
        gotoxy(WIN_WIDTH + 7, 2);
        cout << "THE CAR GAME";
        gotoxy(WIN_WIDTH + 6, 4);
        cout << "---------";
        gotoxy(WIN_WIDTH + 7, 12);
        cout << "CONTROLS:";
        gotoxy(WIN_WIDTH + 7, 13);
        cout << "---------";
        gotoxy(WIN_WIDTH + 2, 14);
        cout << "A - Left";
        gotoxy(WIN_WIDTH + 2, 15);
        cout << "D - Right";
        gotoxy(WIN_WIDTH + 2, 16);
        cout << "E - Exit";
        gotoxy(18, 5);
        cout << "Press any key to begin";
        getch();
        gotoxy(18, 5);
        cout << "                        ";
        while(1)
        {
            if(kbhit())
            {
                char ch = getch();
                if( ch == 'a' || ch == 'A')
                {
                    // Change speed of left
                    if( carPos > 18 )
                        carPos -= 4;
                }
                if( ch == 'd' || ch == 'D')
                {
                    // Change speed of right
                    if( carPos < 50 )
                        carPos += 4;
                }
                if( ch == 'e' || ch == 'E')
                {
                    getMenu();
                    break;
                }
                if(ch==27)
                {
                    break;
                }
            }
            drawCar();
            drawEnemy(0);
            drawEnemy(1);
            drawEnemy(2);
            drawEnemy(3);
            if ( collision() == 1)
            {
                HardenterScore(score);
                gameover();
                return;
            }
            Sleep(50);
            eraseCar();
            eraseEnemy(0);
            eraseEnemy(1);
            eraseEnemy(2);
            eraseEnemy(3);
            if (enemyY[0] == 10)
                if( enemyFlag[1] == 0 )
                    enemyFlag[1] = 1;
            // speed of enemy
            if(enemyFlag[0] == 1)
                enemyY[0] += 3;
            if ( enemyFlag[1] == 1)
                enemyY[1] += 3;
            if ( enemyFlag[2] == 1)
                enemyY[2] += 3;
            if ( enemyFlag[3] == 1)
                enemyY[3] += 3;
            if(enemyY[0] > SCREEN_HEIGHT - 4)
            {
                resetEnemy(0);
                score++;
                updateScore();
            }
            if( enemyY[1] > SCREEN_HEIGHT- 4)
            {
                resetEnemy(1);
                score++;
                updateScore();
            }
            if( enemyY[2] > SCREEN_HEIGHT- 4)
            {
                resetEnemy(2);
                score++;
                updateScore();
            }
            if( enemyY[3] > SCREEN_HEIGHT- 4)
            {
                resetEnemy(3);
                score++;
                updateScore();
            }
        }
    }
    void HardenterScore(int a)
    {
        system("cls");
        if(!outputFile3.is_open())
        {
            cerr<<"Error opening the file!"<<endl;
            exit(1);
        }
        score=a;
        cout<<"Enter your name :";
        cin>>name;
        outputFile3<<name<<" "<<score<<endl;
        outputFile3.close();
    }
    void showLeaderboard()
    {
        system("cls");
        cout<<"****Leaderboard(Hard)****"<<endl;
        ifstream file3("hardScores.txt");
        string line;
        while(getline(file3,line))
        {
            cout<<line<<endl;
        }
        file3.close();
        cout<<"\n\nPress any key to go back";
        getch();
    }
};
class Feedback
{
    string feedback;
public:
    Feedback()
    {
        feedback="";
    }
    Feedback(string a)
    {
        feedback=a;
    }
    friend istream& operator >>(istream& inp,Feedback &F)//operator overloading and friend function
    {
        system("color A");
        string name;
        cout<<"Enter your name: ";
        cin>>name;
        cout<<"Enter your feedback(Good/Bad/NotBad): ";
        inp>>F.feedback;
        outputFile4<<name<<"'s response->"<<F.feedback<<endl;
        return inp;
    }
};
void modes()
{
    easyClass eC;
    mediumClass mC;
    hardClass hc;
    setcursor(0,0);
    srand((unsigned)time(NULL));
    do
    {
        system("cls");
        system("color A");
        gotoxy(50,5);
        cout << " ------------------- ";
        gotoxy(50,6);
        cout << " |     CAR GAME    |";
        gotoxy(50,7);
        cout << " ------------------- ";
        gotoxy(50,9);
        cout << "1. 	EASY MODE    	";
        gotoxy(50,10);
        cout << "2. 	MEDIUM MODE	";
        gotoxy(50,11);
        cout << "3. 	HARD MODE			";
        gotoxy(50,12);
        cout << "4. 	BACK			";
        gotoxy(50,14);
        cout << ">>> CHOICE:		";
        char op = getche();
        switch(op)
        {
        case '1':
            eC.easyPlay();
            break;
        case '2':
            mC.mediumPlay();
            break;
        case '3':
            hc.hardPlay();
            break;
        case '4':
            getMenu();
            break;
        default:
            cout << "Invalid! Try again";
            Sleep(888);
            break;
        }
    }
    while (1);
}
void ThreeLeaderboard()
{
    easyClass ecc;
    mediumClass mcc;
    hardClass hcc;
    setcursor(0,0);
    srand((unsigned)time(NULL));
    do
    {
        system("cls");
        system("color A");
        gotoxy(50,5);
        cout << "1.   Easy   ";
        gotoxy(50,6);
        cout << "2.   Medium  ";
        gotoxy(50,7);
        cout << "3.   Hard    ";
        gotoxy(50,8);
        cout << "4. 	BACK			";
        gotoxy(50,11);
        cout << ">>> CHOICE:		";
        char op = getche();
        switch(op)
        {
        case '1':
            ecc.showLeaderboard();
            break;
        case '2':
            mcc.showLeaderboard();
            break;
        case '3':
            hcc.showLeaderboard();
            break;
        case '4':
            getMenu();
            break;
        default:
            cout << "Invalid! Try again";
            Sleep(888);
            break;
        }
    }
    while(1);
}
template<class T>
void showage(T a)
{
    cout<<"The number is "<<a<<endl;
}
void getMenu()
{
    setcursor(0,0);
    srand((unsigned)time(NULL));
    Feedback fd;
    do
    {
        system("cls");
        system("color A");
        gotoxy(50,5);
        cout << " ------------------- ";
        gotoxy(50,6);
        cout << " |     CAR GAME    |";
        gotoxy(50,7);
        cout << " ------------------- ";
        gotoxy(50,9);
        cout << "1.	PLAY      	";
        gotoxy(50,10);
        cout << "2. 	INSTRUCTIONS	";
        gotoxy(50,11);
        cout<<"3.    LeaderBoard      ";
        gotoxy(50,12);
        cout<<"4.    Feedback       ";
        gotoxy(50,13);
        cout<<"5.    System Testing      ";
        gotoxy(50,14);
        cout << "6. 	QUIT			";
        gotoxy(50,15);
        cout << ">>> CHOICE:		";
        char op = getche();
        switch(op)
        {
        case '1':
            modes();
            break;
        case '2':
            instructions();
            break;
        case '3':
            ThreeLeaderboard();
        case '4':
            system("cls");
            cin>>fd;
            cout<<"Feedback collected!"<<endl;
            cout<<"Press any key to go back to menu.."<<endl;
            getch();
            getMenu();
        case '5':
            system("cls");
            cout<<"Enter a number to make sure this program is working fine:";
            int num;
            cin>>num;
            showage(num);
            cout<<"Press any key to go back to menu.."<<endl;
            getch();
            getMenu();
            break;
        case '6':
            exit(0);
        default:
            cout << "Invalid! Try again";
            break;
        }
    }
    while (1);
}
int main()
{
    getMenu();
}
