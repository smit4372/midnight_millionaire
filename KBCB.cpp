#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

int qNumber;
int points;
int lifeLineNumber;
string lifeLineChoices[5];
string arrayABC[] = {"A.", "B.", "C.", "D."};
bool gameLost;
class question{
    public:
    string question;
    string choice[4];
    string theCorrectChoice;
    char answerChoice;
    bool lifeLineUsed;
    bool correctGiven;
    void readQuestionFromFile(int z);
    void displayQuestion();
    void answer();
    //function for increasing points, cause with every level our points earned our different
    void lifeline();   
    void correctAnswer(string answerChoice);
    

};



void introduction(){
    cout<<"\t\t\t\t\t\tWelcome to our Game\n\t\t\t\t\t\tMidnight Millionaire\n\n- There are 15 levels in this game, each level you will be asked"
    "\na question with multiple choices for the answer."
    "\n\n- Every correct answer you will earn positive points and \n  every wrong answer will result in negative points."
    "\n\n- Each point equals $1000, With levels increasing, points awarded will also increase\n"
    "- After completing level 10, you will be asked if you want to save and quit the game."
    "\nOr you want to continue playing, if so every level after 10 will be a do or die"
    "\n\n- If a correct answer is given, you will be taken to the next level"
    "\n\n- If a wrong answer is given you will lose all your points and will be kicked out of the game."
    "n\n- You will be given 4 life-lines, each you can only use once in the game:" 
    "\n\n1. Audience Poll\n2. 50:50\n3. Double Dip\n4. Skip the question"<<endl;
}

void negativePoints(){
    if(qNumber<6){
        points = points - qNumber*(30 + qNumber);
        cout<<"You lost "<<qNumber*(30 + qNumber)<<" points"<<endl;

    }else if(qNumber>5 && qNumber<11){

        points = points - qNumber*(50 +qNumber);
        cout<<"You lost "<<qNumber*(50 + qNumber)<<" points"<<endl;
    }
}

void positivePoints(){
    if(qNumber<6){
        points = points + qNumber*(50 + qNumber);
        cout<<"\nYou have earned "<<qNumber*(50 + qNumber)<<" points"<<endl;

    }else if(qNumber>5 && qNumber<11){
        points = points + qNumber*(70+qNumber);
        cout<<"\nYou have earned "<<qNumber*(70 + qNumber)<<" points"<<endl;
    }
}




void question::answer(){
    
    cout<<"\nEnter your choice(A, B, C, D, L):";
    cin>>answerChoice;
    answerChoice = (char) toupper(answerChoice);

    switch (answerChoice)
    {
    case 'A':
        correctAnswer(choice[0]);
        break;

    case 'B':
        correctAnswer(choice[1]);
        break;

    case 'C':
        correctAnswer(choice[2]);
        break;

    case 'D':
        correctAnswer(choice[3]);
        break;
    
    case 'L': 
        if(lifeLineNumber>0){
            cout<<"\nYou have following life lines: \n"<<endl;
            for(int i = 0; i < lifeLineNumber; i++){
                cout<<i+1<<" "<<lifeLineChoices[i]<<endl;
            }
            lifeline();
        }else{
            cout<<"You have used all your life lines"<<endl;
            cout<<"Your choices are - A, B, C, D"<<endl;
            answer();
        }
        break;

    default:
        //cout<<"Your choices are - A, B, C, D, L";
        answer();
        break;
    }
}

void question::lifeline(){
    int lifeLineChoice;
    int choiceYes = 1;
    int choiceNo = 1;
    lifeLineNumber--;
    
    srand(time(0));
    
    
    cout<<"\nChose from the following(Enter the number in front of the lifeLine to select that lifeLine):";
    cin>>lifeLineChoice;
    cout<<"\n";
    
    if(lifeLineChoices[lifeLineChoice-1] == "Audience Poll"){
        for(int i = 0; i<4; i++){
            if(choice[i] == theCorrectChoice){
                cout<<arrayABC[i]<<" "<<choice[i]<<" "<<rand()%20 + 50<<"% "<<endl;
            }else{
                cout<<arrayABC[i]<<" "<<choice[i]<<" "<<rand()%((i+1)*10)<<"% "<<endl;
            }
        }
        answer();
        for(int i = (lifeLineChoice-1); i<4; i++){
            lifeLineChoices[i] = lifeLineChoices[i+1];
        }
    }else if(lifeLineChoices[lifeLineChoice-1] == "50:50"){
        cout<<"Your new choices are: "<<endl;
        for(int i = 0; i<4; i++){
            if(choiceYes>0 && choice[i] == theCorrectChoice){
                cout<<arrayABC[i]<<" "<<choice[i]<<endl;
                choiceYes--;
            }else if (choiceNo>0){
                cout<<arrayABC[i]<<" "<<choice[i]<<endl;
                choiceNo--;
            }
        }
        
        answer();

        for(int i = (lifeLineChoice-1); i<4; i++){
            lifeLineChoices[i] = lifeLineChoices[i+1];
        }

    }else if(lifeLineChoices[lifeLineChoice-1] == "Double Dip"){
        lifeLineUsed = true;
        answer();
        for(int i = (lifeLineChoice-1); i<4; i++){
            lifeLineChoices[i] = lifeLineChoices[i+1];
        }
    }else if(lifeLineChoices[lifeLineChoice-1] == "Skip the question"){
        for(int i = (lifeLineChoice-1); i<4; i++){
            lifeLineChoices[i] = lifeLineChoices[i+1];
        }
    }
}

void question::correctAnswer(string answerChoice){
    if(answerChoice == theCorrectChoice && qNumber<= 10){
        
        cout<<"Correct Answer";
        positivePoints();
        cout<<"\nYour Total points are: "<<points<<endl;
        correctGiven = true;
        lifeLineUsed = false;
    }else if(answerChoice == theCorrectChoice && qNumber == 15){
        points = 5000;
        cout<<"Congratulations on completing the game succefully"
        "You have earned the amount ₹5,00,00,000"<<endl;
        
        
        correctGiven = true;
        lifeLineUsed = false;
    }else if (answerChoice == theCorrectChoice && (qNumber>10 && qNumber<15)){
        cout<<"\nCorrect Answer\nScore available after Level 15\n"<<endl;
        correctGiven = true;
        lifeLineUsed = false;
    }else if( answerChoice != theCorrectChoice ){
        correctGiven = false;
        if(qNumber<= 10){
            cout<<"\nIncorrect Answer\n";
            if(lifeLineUsed == true){
                cout<<"You have a second chance to select answer\n"<<endl;
                lifeLineUsed = false;
                answer();
            }else{
                negativePoints();
                cout<<"Your current points are: "<<points<<endl;
            }
            
            if(points < 0){
                cout<<"You have negative points: "<<points<<"\nGood efforts, hope we see you back.\nThank you for playing with us.";

                gameLost = true;
            }
            
        }else{
            cout<<"\nIncorrect Answer\n";
            if(lifeLineUsed == true ){
                lifeLineUsed = false;
                if(correctGiven == false){
                    cout<<"You have a second chance to select answer\n"<<endl;
                    answer();
                }
                
            }else{
                gameLost = true;
                points = 0;
                cout<<"Sorry to see you lose at this far in the game.\nGood efforts, hope we see you back.\nThank you for playing with us.\n";
            }
            
            
        }
        
    }

}


void options(){
    cout<<"\n\n"<<endl;
    cout<<"To continue to the next level press 'N'\n"
    "To know your score, press 'S'\nTo revise the rules, press 'R'"
    "\nTo stop playing and quit the game, press 'Q'\n"
    "To repeat the options, press 'O'\nEnter your choice: ";
}


void question::displayQuestion(){
    cout<<"\nQ"<<qNumber<<" "<<question<<endl;
    cout<<"\n";
    srand(time(0));
    string temp;
    
    for(int j = 4; j>0; j--){
        int z = rand()%j;
        temp = choice[j-1];
        choice[j-1] = choice[z];
        choice[z] = temp;
    }
    
    cout<<"A. "<<choice[0]<<endl;
    cout<<"B. "<<choice[1]<<endl;
    cout<<"C. "<<choice[2]<<endl;
    cout<<"D. "<<choice[3]<<endl;
    cout<<"\nFor Life Lines press L"<<endl;

};




void game(){
    
    char ch;
    int z;
    int temp;
    srand(time(0));
    lifeLineChoices[0] = "Audience Poll";
    lifeLineChoices[1] = "50:50";
    lifeLineChoices[2] = "Double Dip";
    lifeLineChoices[3] = "Skip the question";
    qNumber = 1; //assigning value 
    points = 0;
    lifeLineNumber = 4;
    //Making a random number List, to access random question file

    int listOfQuestionNumber[31]; //we will given numbers to list of 30 questions
    for(int i = 0; i<31; i++){
        listOfQuestionNumber[i] = i+1;
    }
    //making a random list form a simple 1-30 list
    for(int j = 31; j>0; j-- ){
        z = rand()%j;
        temp =  listOfQuestionNumber[j-1];
        listOfQuestionNumber[j-1] = listOfQuestionNumber[z];
        listOfQuestionNumber[z] = temp;
    }

    
    question qList[31];
    question q;
    ifstream qFile("questions.txt");
    int j = 0;
    while(qFile.is_open()&&qFile.good()&&j<31){

        getline(qFile, q.question);
        for(int i = 0; i<4; i++){
            getline(qFile, q.choice[i]);
        }
        getline(qFile, q.theCorrectChoice);
        qList[j] = q;
        j++;

    }
    cout<<"Less Go\nLevel "<<qNumber<<"\n";
    //q = qList[listOfQuestionNumber[qNumber-1]]
    qList[listOfQuestionNumber[qNumber-1]].displayQuestion();
    qList[listOfQuestionNumber[qNumber-1]].correctGiven = false;
    qList[listOfQuestionNumber[qNumber-1]].lifeLineUsed = false;
    qList[listOfQuestionNumber[qNumber-1]].answer();
    while(qNumber<15 && gameLost == false){
        options();
        cin>>ch;
        ch = (char) toupper(ch);
        switch (ch)
        {
            case 'N':
                qNumber++;
                cout<<"\nLevel "<<qNumber<<"\n";
                qList[listOfQuestionNumber[qNumber-1]].displayQuestion();
                qList[listOfQuestionNumber[qNumber-1]].correctGiven = false;
                qList[listOfQuestionNumber[qNumber-1]].lifeLineUsed = false;
                qList[listOfQuestionNumber[qNumber-1]].answer();
                break;
            
            case 'R':
                introduction();
                break;
            
            case 'S':
                cout<<"Your current score is: "<<points<<"\nIf you have crossed Level 10, your final score will be available after completing final Level"<<endl;
                break;
            
            case 'Q' :
                if(qNumber<11){
                    
                    cout<<"Your total score is "<<points<<endl;
                    cout<<"Thank you for playing with us"<<endl;

                }else{
                    points = 0;
                    cout<<"We feel sad that you want to quit at this point"
                    "You have earned $0 "
                    "\nThank you for playing with us"<<endl;
                }
                        
                break;
            
            case 'O':
                options();
                break;

            default:
                cout<<"Your choices are N, R, S, Q, O. Select from the following: ";
                break;
        }

        if(ch == 'Q'){
            break;
        }
    
    }
    
    
    

};


int main(){
    
    char ch1;
    string playerName;
    introduction();
    
    

    do{
        cout<<"\n\nTo start the game press S"
        "\nTo exit code press, E\n";
        cin>>ch1;
        ch1 = (char) toupper(ch1);
        switch (ch1)
        {
        case 'S':
            cout<<"\nEnter your name: ";
            cin>>playerName;
            cout<<"\nWelcome "<<playerName<<"\n"<<endl;
            game();
            break;
        
        case 'E':
            
            break;

        default:
            cout<<"Invalid Selection\n";
            break;
        }
        
    }while(ch1!= 'E');
}