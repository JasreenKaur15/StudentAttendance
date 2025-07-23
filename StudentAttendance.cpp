#include <iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
class student
{
    public:
    char name[50];
    char fname[50];
    char degree[50];
    int semester;
    int rollno;
    
    friend void remove_student();
    friend void edit_student();
    void accept()
    {
        cout<<endl<<"enter roll number";
        cin>>rollno;
        cout<<endl<<"enter name";
        cin>>name;
        cout<<endl<<"enter father name";
        cin>>fname;
        cout<<endl<<"enter degree";
        cin>>degree;
        cout<<endl<<"enter semester";
        cin>>semester;
        
    }
    void display()
    {
        cout<<endl;
        cout<<setw(5)<<rollno;
        cout<<setw(15)<<name;
        cout<<setw(15)<<fname;
        cout<<setw(15)<<degree;
        cout<<setw(10)<<semester;
    }
};
student s1;//global object
void add_student()
{
    s1.accept();
    fstream wr;
    wr.open("mystudent.txt",ios::app);
    wr.write((char*)&s1,sizeof(s1));
    wr.close();
    cout<<endl<<"student data written successfully";

}
void remove_student()
{
    fstream rd;
    rd.open("mystudent.txt",ios::in);
    int size;
    rd.seekg(0,ios::end);
    size=rd.tellg();
    rd.seekg(0,ios::beg);
    int number_student=size/sizeof(s1);
    int rno;
    fstream wr;
    wr.open("temp.txt",ios::out);
    cout<<endl<<"enter the roll number to be searched and removed";
    cin>>rno;
    for(int i=1;i<=number_student;i++)
    {
        rd.read((char*)&s1,sizeof(s1));
        if(s1.rollno==rno)
        {
            cout<<"removed";
        }
        else
        {
            cout<<endl<<"writing roll number"<<s1.rollno;
            wr.write((char*)&s1,sizeof(s1));
        }
    }
    wr.close();
    rd.close();
    
    remove("mystudent.txt");
    rename("temp.txt","mystudent.txt");

}
void edit_student()
{
    fstream rd;
    rd.open("mystudent.txt",ios::in);
    int size;
    rd.seekg(0,ios::end);
    size=rd.tellg();
    rd.seekg(0,ios::beg);
    int number_student=size/sizeof(s1);
    fstream wr;
    wr.open("temp.txt",ios::out);
    int rno;
    cout<<endl<<"enter roll number to edit";
    cin>>rno;
    
    for(int i=0;i<number_student;i++)
    {
        rd.read((char*)&s1,sizeof(s1));
        if(s1.rollno ==rno)
        {
            s1.accept();
            wr.write((char*)&s1,sizeof(s1));   
        }
        else
        {
            wr.write((char*)&s1,sizeof(s1));
        }
    }
    rd.close();
    wr.close();
    remove("mystudent.txt");
    rename("temp.txt","mystudent.txt");
}



void show_student()
{
    fstream rd;
    rd.open("mystudent.txt",ios::in);
    int size;
    rd.seekg(0,ios::end);
    size=rd.tellg();
    rd.seekg(0,ios::beg);
    cout<<endl<<setw(5)<<"Rollno";
    cout<<setw(15)<<"Name";
    cout<<setw(15)<<"Fname";
    cout<<setw(15)<<"Degree";
    cout<<setw(10)<<"semester";
    cout<<endl<<".........................................................";
    for(int i=0;i<size/sizeof(s1);i++)
    {
        rd.read((char*)&s1,sizeof(s1));
        s1.display();
    }
    
}
class mark_attendance
{
    friend void view_attendancedate();
    friend void view_attendancerollno();
    
    int dd,mm,yy;
    int rollno;
    public:
    void init(int d,int m,int y,int r)
    {
        dd=d;
        mm=m;
        yy=y;
        rollno=r;
    }
    void display()
    {
        cout<<endl<<dd<<"-"<<mm<<"-"<<yy;
        
        fstream rd;
        rd.open("mystudent.txt",ios::in);
        rd.seekg(0,ios::end);
        int size=rd.tellg()/sizeof(s1);
        rd.seekg(0,ios::beg);        
    
        for(int i=1;i<=size;i++)
        {
            rd.read((char*)&s1,sizeof(s1));
            if(rollno==s1.rollno )
            {
                cout<<setw(10)<<s1.rollno<<setw(15)<<s1.name<<setw(15)<<s1.fname<<setw(15)<<s1.degree<<setw(15)<<s1.semester;
            }
        }
    }
    void display(char*p,int s)
    {
        cout<<endl<<dd<<"-"<<mm<<"-"<<yy;
        fstream rd;
        rd.open("mystudent.txt",ios::in);
        rd.seekg(0,ios::end);
        int size=rd.tellg()/sizeof(s1);
        rd.seekg(0,ios::beg);
        for(int k=1;k<=size;k++)
        {
            rd.read((char*)&s1,sizeof(s1));
            if(s==s1.semester&&strcmp(p,s1.degree)==0)
            {
                cout<<setw(10)<<s1.rollno<<setw(15)<<s1.name<<setw(15)<<s1.fname<<setw(15)<<s1.degree<<setw(15)<<s1.semester;
            }
        }

    }
};
mark_attendance m1;
class attendance
{
    int dd,mm,yy;
    int arr[50];
    public:
    void accept()
    {
        int p;
        int count=0;
        cout<<endl<<"enter date,month,year";
        cin>>dd>>mm>>yy;
        cout<<endl<<"enter roll no of present students followed by -1";
        for(int i=1;i<=50;i++)
        {
            cin>>p;
            if(p==-1)
            {
                break;
            }
            arr[i]=p;
            count++;
        }
        fstream wr;
        wr.open("attendance_data.txt",ios::app);
        for(int j=1;j<=count;j++)
        {
            m1.init(dd,mm,yy,arr[j]);
            wr.write((char*)&m1,sizeof(m1));

        }
        wr.close();
    }
};
void view_attendance()
{
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    cout<<endl<<"number of students are : "<<size;
    rd.seekg(0,ios::beg);
    for(int i=1;i<=size;i++)
    {
        rd.read((char*)&m1,sizeof(m1));
        m1.display();

    }
}
void view_attendancedate()
{
    int d,m,y;
    
    cout<<endl<<"enter date,month,year";
    cin>>d>>m>>y;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    rd.seekg(0,ios::beg);
    for(int i=1;i<=size;i++)
    {
        rd.read((char*)&m1,sizeof(m1));
        if(m1.dd==d&&m1.mm==m&&m1.yy==y)
        {
            m1.display();
            
        }
    }
    
}
void view_attendancerollno()
{
    int rno;
    cout<<"enter roll number";
    cin>>rno;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    rd.seekg(0,ios::beg);
    for(int j=0;j<size;j++)
    {
        rd.read((char*)&m1,sizeof(m1));
        if(m1.rollno==rno)
        {
            m1.display();
        }
    }
}
void view_attendancedegree()
{
    char deg[50];
    int sem;
    cout<<endl<<"enter degree and semester";
    cin>>deg>>sem;
    fstream rd;
    rd.open("attendance_data.txt",ios::in);
    rd.seekg(0,ios::end);
    int size=rd.tellg()/sizeof(m1);
    rd.seekg(0,ios::beg);
    for(int j=0;j<size;j++)
    {
        rd.read((char*)&m1,sizeof(m1));
        m1.display(deg,sem);
        
    }
}

int main()
{
    int e=0;
    while(e==0)
    {
        cout<<endl<<"************WELCOME TO STUDENT ATTENDANCE PROJECT***********";
        cout<<endl<<"PRESS 1 TO ADD STUDENT";
        cout<<endl<<"PRESS 2 TO EDIT STUDENT";
        cout<<endl<<"PRESS 3 TO  REMOVE STUDENT";
        cout<<endl<<"PRESS 4 TO SHOW STUDENTS";
        cout<<endl<<"PRESS 5 TO MARK ATTENDANCE";
        cout<<endl<<"PRESS 6 TO VIEW ATTENDANCE";
        cout<<endl<<"PRESS 7 TO VIEW ATTENDANCE BY DATE";
        cout<<endl<<"PRESS 8 TO VIEW ATTENDANCE BY ROLL NUMBER";
        cout<<endl<<"PRESS 9 TO VIEW ATTENDANCE BY DEGREE AND SEMESTER";
        cout<<endl<<"PRESS 10 TO EXIT";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            add_student();
        }
        else if(choice==2)
        {
            edit_student();
        }
        else if(choice==3)
        {
            remove_student();
        }
        else if(choice==4)
        {
            show_student();
        }
        else if(choice==5)
        {
            attendance obj;
            obj.accept();
        }
        else if(choice==6)
        {
            view_attendance();
        }
        else if(choice==7)
        {
            view_attendancedate();
        }
        else if(choice==8)
        {
            view_attendancerollno();
        }
        else if(choice==9)
        {
            view_attendancedegree();
        }
        
        else if(choice==10)
        {
            cout<<endl<<"############    THANK YOU     #############";
            e=1;
        }
        else
        {
            cout<<"invalid choice";
        }
    }

}