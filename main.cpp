#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<conio.h>

using namespace std;

class game_play{

private:
    char question[80];
    char answer[40];
    char temp_all_ans[180];
    char ans_1[40];
    char ans_2[40];
    char ans_3[40];

    int i_ans;
    char mov_arrow;

public:
    int r_ans=0;

    void show();
    void load_file();
    void get_ques(ifstream& in);
    void get_ans(ifstream& in);
    void add_ans(ifstream& in);
    void int_ques();
    int play_game();
    void rest_arr();
};
int main()
{
    int a;
    char rep;
    while(1)
    {
        int end_game=0;
        system("cls");
        game_play* game=new game_play;
        game->show();
        while(end_game<10)
        {
            a=0;
            game->load_file();
            a=game->play_game();
            if(a)
                game->r_ans+=10;
            game->rest_arr();
            end_game++;
        }
        cout<<"your score is : "<<game->r_ans<<endl<<endl;
        cout<<"want play again? y/t"<<endl;
        cin>>rep;
        if(rep=='t')
            break;
        else
            delete game;
    }
    system("cls");
    cout<<"thank for playing\n";
    getch();
    return 0;
}

void game_play::load_file()//load ranom file
{
    srand(time(0));
    int rand_fil;
    char* get_file;
    ifstream infile;

    rand_fil=rand()%4+1;
    switch(rand_fil)
    {
        case 1:
        {
            get_file="./history/question.txt";
            infile.open(get_file);
            get_ques(infile);
            infile.close();
            get_file="./history/answer.txt";
            infile.open(get_file);
            get_ans(infile);
            add_ans(infile);
            infile.close();
        }
        break;

        case 2:
        {
            get_file="./hotel/question.txt";
            infile.open(get_file);
            get_ques(infile);
            infile.close();
            get_file="./hotel/answer.txt";
            infile.open(get_file);
            get_ans(infile);
            add_ans(infile);
            infile.close();
        }
        break;

        case 3:
        {
            get_file="./programing/question.txt";
            infile.open(get_file);
            get_ques(infile);
            infile.close();
            get_file="./programing/answer.txt";
            infile.open(get_file);
            get_ans(infile);
            add_ans(infile);
            infile.close();
        }
        break;

        case 4:
            int_ques();
        break;

        default:
            cout<<"invalid input\n";

    }
}

void game_play::get_ques(ifstream& in)//get question from file txt
{

    char* t_q_word=new char[70];
    int rand_ques;
    int con=0;
    int i=0;

    while(!in.eof())//count of how many question list
    {
        char* te_word=new char [200];
        i++;
        in.getline(te_word,400);
        delete te_word;
    }
    in.clear();
    in.seekg(0,ios::beg);//reset flag true of eof

    srand(time(0));
    rand_ques=rand()%i+1;//get indeks question
    while(!in.eof())//get random question from file
    {
        con++;
        char* te_word=new char[120];
        if(con!=rand_ques)
            in.getline(te_word,400);
        else if(con==rand_ques)
            in.getline(t_q_word,70);
        delete te_word;
    }
    for(int j=0;j<strlen(t_q_word);j++)//fix word and assign to classs variable
    {
        if(j==0||t_q_word[j]=='.')
            continue;
        else
            this->question[j-2]=t_q_word[j];
    }
    i_ans=rand_ques;//safe indeks question and use to indeks answer
}

void game_play::get_ans(ifstream& in)
{

    int con=0;
    char* tem_ans=new char[150];
    int i;

    int mor_one=0;
    int i_mor_ans=1;

    srand(time(0));

    while(!in.eof())
    {
        con++;
        in.getline(tem_ans,150);
        if(con==this->i_ans)
            break;
    }

    for(i=0;i<strlen(tem_ans);i++)//check if ther is more one answer
    {
        if(tem_ans[i]==',')
        {
            mor_one=1;
            i_mor_ans++;
        }
    }
    /////////////////
    if(!mor_one)
    {
        for(i=0;i<strlen(tem_ans);i++)
        {
            if(i==0||tem_ans[i]=='.')
                continue;
            else
                answer[i-2]=tem_ans[i];
        }
    }
    else
    {
        int count_ans=1;
        for(i=0;i<strlen(tem_ans);i++)//count of answer
            if(tem_ans[i]==',')
                count_ans++;

        int rand_ans;
        rand_ans=rand()%count_ans+1;
        count_ans=1;
        char t[20];
        int ind=0;
        for(i=0;i<strlen(tem_ans);i++)//get one answer
        {
            if(tem_ans[i]==',')
                count_ans++;
            if(count_ans==rand_ans)
            {
                t[ind]=tem_ans[i];
                ind++;
            }
        }
        t[ind]='\0';

        if(rand_ans==1)//assign to answer
        {
            for(i=0;i<strlen(t);i++)
            {
                if(i==0||t[i]=='.')
                    continue;
                else
                    answer[i-2]=t[i];
            }
        }
        else
        {
             for(i=0;i<strlen(t);i++)
                answer[i]=t[i+1];
        }

    }
    in.clear();
    in.seekg(0,ios::beg);
    delete[] tem_ans;
}

void game_play::add_ans(ifstream& in)
{

    char temp[100];
    int stInd;
    int a=1;

    int i;
    int j;
    while(!in.eof())
    {
        if(strcmp(temp,"random choose:")==0||a>1)//start from mark to get add answer
        {
            in.getline(temp,100);
            if(a==i_ans)//stop in right indeks from answer
                break;
            a++;
            continue;
        }
        in.getline(temp,100);
    }
    a=1;
    for(i=0;i<strlen(temp);i++)//assign to and fix the word and count of another answer
    {
        if(temp[i]==',')
            a++;
        if(i==0||temp[i]=='.')
            continue;
        temp_all_ans[i-2]=temp[i];
    }
    srand(time(0));
    if(a>3)
        stInd=rand()%a+1;

    if(a>3)
    {
        if(stInd>=3)
        {
            int con=stInd;
            for(j=3;j>0;j--)
            {

                int inc=0;
                a=1;
                for(i=0;i<strlen(temp_all_ans);i++)
                {
                    if(temp_all_ans[i]==',')
                    {
                        a++;
                        continue;
                    }
                    if(a==con)
                    {
                        if(j==1)
                        {
                            ans_1[inc]=temp_all_ans[i];
                            inc++;
                        }
                        else if(j==2)
                        {
                            ans_2[inc]=temp_all_ans[i];
                            inc++;
                        }
                        else if(j==3)
                        {
                            ans_3[inc]=temp_all_ans[i];
                            inc++;
                        }
                    }
                }
            con--;
            }
        }

        else if(stInd<3)
        {
            int con=stInd;
            for(j=0;j<3;j++)
            {
                int inc=0;
                a=1;
                for(i=0;i<strlen(temp_all_ans);i++)
                {
                    if(temp_all_ans[i]==',')
                    {
                        a++;
                        continue;
                    }
                    if(a==con)
                    {
                        if(j==0)
                        {
                            ans_1[inc]=temp_all_ans[i];
                            inc++;
                        }
                        else if(j==1)
                        {
                            ans_2[inc]=temp_all_ans[i];
                            inc++;
                        }
                        else if(j==2)
                        {
                            ans_3[inc]=temp_all_ans[i];
                            inc++;
                        }
                    }
                }
                con++;
            }
        }
    }

    else
    {
        int con=0;
        a=1;
        for(i=0;i<strlen(temp_all_ans);i++)
        {
            if(temp_all_ans[i]==',')
            {
                con=0;
                a++;
                continue;
            }
            if(a==1)
            {
                ans_1[con]=temp_all_ans[i];
                con++;
            }
            else if(a==2)
            {
                ans_2[con]=temp_all_ans[i];
                con++;
            }
            else if(a==3)
            {
                ans_3[con]=temp_all_ans[i];
                con++;
            }
        }
    }
}

int game_play::play_game()
{
char* arrow1="->";
    char* arrow2="<-";
    int i;
    int i_exc=0;
    static int ind_ex=0;
    int w_or_l=0;
    int con_arrow=0;
    int ans_ind=0;
    char* ans_arr[3];
    int hnd_err=0;
    //-----------------------initial word first
    srand(time(0));
    hnd_err=rand()%3;
    ans_ind=hnd_err;
    ans_arr[0]=ans_1;
    ans_arr[1]=ans_2;
    ans_arr[2]=ans_3;
    ans_arr[3]=answer;

    for(i=0;i<4;i++)//second is insert random answer among another choose
    {
        if(ans_ind==i)
        {
            ans_arr[3]=ans_arr[i];
            ans_arr[i]=answer;
        }
    }
    system("cls");
    while(1)
    {
        cout<<endl<<endl<<'\t'<<ind_ex<<". "<<question<<"\n\n\n";
        for(i=0;i<4;i++)
        {
            if(i==1)
            {
                if(con_arrow==i)
                {
                    cout<<'\t'<<arrow1;
                    cout<<ans_arr[i]<<arrow2<<endl<<endl;
                }
                else
                    cout<<'\t'<<ans_arr[i]<<endl<<endl;
            }
            else if(con_arrow==i)
            {
                cout<<'\t'<<arrow1;
                cout<<ans_arr[i]<<arrow2<<'\t';
            }
            else
                cout<<'\t'<<ans_arr[i]<<'\t';

        }
        cout<<"\n\n\n\nscore : "<<r_ans<<endl;
        cout<<endl<<endl;
        mov_arrow=getch();
        if(con_arrow>=0&&con_arrow<4)
        {
            if(con_arrow==0)
            {
                if(mov_arrow=='s')
                    con_arrow+=2;
                else if(mov_arrow=='d')
                    con_arrow+=1;
            }
            else if(con_arrow==1)
            {
                if(mov_arrow=='a')
                    con_arrow-=1;
                else if(mov_arrow=='s')
                    con_arrow+=2;
            }
            else if(con_arrow==2)
            {
                if(mov_arrow=='w')
                    con_arrow-=2;
                else if(mov_arrow=='d')
                    con_arrow+=1;
            }
            else if(con_arrow==3)
            {
                if(mov_arrow=='w')
                    con_arrow-=2;
                else if(mov_arrow=='a')
                    con_arrow-=1;
            }
        }

        if(mov_arrow==0xD)
        {
            if(ans_ind==con_arrow)
            {
                w_or_l=1;
                break;
            }
            else
                break;
        }
        system("cls");
    }

    ind_ex++;
    return w_or_l;
}

void game_play::int_ques()
{

    srand(time(0));
    char ch_op;
    char temp_num1[6];
    char temp_num2[5];

    int a=0;
    int b=0;
    int c=0;
    int num_1=0;
    int num_2=0;
    int ans;
    int op;
    int len12;
    int i;
    int j=0;
    op=rand()%3+0;
    num_1=rand()%10000+1;
    num_2=rand()%1000+1;

    a=rand()%1000+1;
    b=rand()%1000+1;
    c=rand()%10000+1;

    switch(op)
    {
        case 0:
        {
            ans=num_1+num_2;
            ch_op='+';
        }
        break;

        case 1:
        {
            ans=num_1-num_2;
            ch_op='-';
        }
        break;

        case 2:
        {
            ans=num_1*num_2;
            ch_op='*';
        }
        break;

        case 3:
        {
            ans=num_1/num_2;
            ch_op=':';
        }
    }

    itoa(num_1,temp_num1,10);
    itoa(num_2,temp_num2,10);
    itoa(ans,answer,10);

    itoa(a,ans_1,10);
    itoa(b,ans_2,10);
    itoa(c,ans_3,10);

    len12=3+(strlen(temp_num1)+strlen(temp_num2));
    for(i=0;i<len12;i++)
    {
        if(i<strlen(temp_num1))
            question[i]=temp_num1[i];
        else if(i==strlen(temp_num1))
            question[i]=ch_op;
        else if(i>strlen(temp_num1)&&i<=(strlen(temp_num1)+strlen(temp_num2)))
        {
            question[i]=temp_num2[j];
            j++;
        }
        else if(i==(strlen(temp_num1)+strlen(temp_num2))+1)
            question[i]='?';
        else
            question[i]='\0';
    }

}

void game_play::rest_arr()
{

    memset(question,0,80);
    memset(answer,0,40);
    memset(temp_all_ans,0,180);
    memset(ans_1,0,40);
    memset(ans_2,0,40);
    memset(ans_3,0,40);
}

void game_play::show()
{
 cout<<"                       _                                    _\n";
 cout<<"    (_)               | |                                  | |"<<endl;
 cout<<" ___ _ _ __ ___  _ __ | | ___      ___ ___  _ __  ___  ___ | |  _"<<endl;
 cout<<"/ __| | '_ ` _ \\| '_ \\| |/ _ \\    / __/ _ \\| '_ \\/ __|/ _ \\| |/ _ \\ "<<endl;
 cout<<"\\\__ \\ | | | | | | |_) | |  __/   | (_| (_) | | | \\__ \\ (_) | |  __/ "<<endl;
 cout<<"|___/_|_| |_|_|_| .__/|_|\\___|    \\___\\___/|_| |_|___/\\___/|_|\\___| "<<endl;
 cout<<"            (_) | |\n";
 cout<<"  __ _ _   _ _ _|_|   __ _  __ _ _ __ ___   ___"<<endl;
 cout<<" / _` | | | | |_  /  / _` |/ _` | '_ ` _ \\ / _ \\"<<endl;
 cout<<"| (_| | |_| | |/ /  | (_| | (_| | | | | | |  __/\ "<<endl;
 cout<<" \\__, |\\__,_|_/___|  \\__, |\\__,_|_| |_| |_|\\___|\  "<<endl;
 cout<<"    | |               __/ |"<<endl;
 cout<<"    |_|              |___/"<<endl;

 system("pause");
 system("cls");
}






























