//student.h
//gpa和studytime是保护成员, 无法直接访问修改, 只能通过成员函数来间接修改.
#include <iostream>
#include <cstring>
using namespace std;

class Student
{
    static int student_count;   //静态成员变量, 用于统计学生人数. 只能在类外部初始化.

    public:
        Student(){
            student_count++;

            gpa = 0;
            study_time = 0;
            cout<<"Student created. Total students: "<<student_count<<endl;
        }

        Student(char* pname){
            student_count++;

            strncpy(name, pname, sizeof(name));//拷贝字符串. strncpy()是strcpy()的安全版本, 后者没有第三个参数size, 有拷贝溢出的危险.
            cout<<"Student created. Total students: "<<student_count<<endl;
        }

        ~Student(){
            student_count--;
            cout<<"Student destroyed. Total students: "<<student_count<<endl;
        }


        float GetGpa()
        {
            return gpa;
        }
        int GetStudyTime()
        {
            return study_time;
        }

        void AddCourse(int hours, float score)   //增加某个课程(课时为hours, 该课程成绩为score )
        {      
            gpa=(gpa * study_time + hours * score) / (study_time + hours);//更新gpa(即一个加权平均数)
            study_time += hours; //更新study_time
        }  

        
        protected:
            int study_time;
            float gpa;

        private:
            char name[20];



};

//继承: GraduateStudent类是以public方式继承了Student类的子类.
//public继承(默认): 子类可以访问基类的`public和protected成员`, 不能访问`private成员`. 用于表示"is a"关系, 即子类是基类的一种特殊类型.
//protected继承:    基类的`public成员和protected成员`变成子类的`protected成员`, 不能访问`private成员`. 用于表示
//private继承:      基类的`public成员和protected成员`变成子类的`private成员`, 不能访问`public和protected成员`.

class GraduateStudent : public Student//以public方式继承
{

};








class Animal
{
    public:
        void eat()
        {cout<<"yum yum"<<endl;}
        void sleep()
        {cout<<"zzzz"<<endl;}
    
    p

};










