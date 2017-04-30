#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;
#include "serialr.h"
#include "mon.h"
#include "database.h"


char* getString(void)
{
    char* input = (char* )malloc(25);
    do
    {
        gets(input);
    }while(strlen(input) == 0);
    return input;
}
// return current time
time_t date_time()
{
    time_t rawtime1;
    // current time
    time(&rawtime1);
    return rawtime1;
}

int lib_fine(time_t t1, time_t t2)
{
    double sec;
    sec = difftime(t2, t1); // returns difference in time in seconds
    return ((int) round(sec / (24 * 3600)));
}

char rfid[12];
char null[12];            // for checking null arrays
char regd[16],iname[24];
char bname[16],author[24];
char position[6];
time_t timing;
char c;
int temp1 , temp2 ;


int main(void)
{
    initr();
    char last[12];
    int  s, temp, k, iscan, j, p, x;
    int iss,ret;
    int cost1, cost2;      // fine amount
    char ch;
    BK is[2],re[2],b[4];
    ID i;
while(1)
{

    start:
        system("cls");
        cout<<"                             Welcome to Library                  "<<'\n';
    j=0;//no.of books scanned
    iscan=0;
    iss=0;//books to be isuued
    ret=0;//books to be returned

    while(1)
    {
        start1:
        cout<<"scan rfid tags... scan ID card in the end..."<<endl;
        strncpy(last, rfid, 12);
        while(!strncmp(last, rfid, 12))
            serialr(rfid);
        s=status(rfid);

        if(s==0)
        {
            iscan++;
            i=search_id(rfid);
            // check
            if((i.books+iss-ret)>2) // iss == 1 means one book to be issued and iss == 0 means no books to be issued
            {
                cout<<" Remove extra book and retry ";
                system("pause");
                goto start;
            }
            if(iscan)   // flag = 1;         // print id details
            {
                system("cls");
                std::cout<<'\n'<<"  Student details ";
                std::cout<<'\n'<<"  Student Name    :"<<i.name;
                std::cout<<'\n'<<"  Student Registration no.    :"<<i.regd;
                //goto issue;
                break;
            }
        }
        else if(s==1)
        {
            b[j]=search_book(rfid);
            puts(b[j].name);
            if(b[j].status)
            {
                re[ret]=b[j];
                ret++;
            }//assigning return books
            else
            {
                is[iss]=b[j];
                iss++;
            }//assigning issue books
            j++;
        }
        else
        {
            std::cout<<'\n'<<" TAG NOT IN DATABASE . RETRY "<<'\n';
            goto start1;
        }

        // print tag details scanned until now
        //system("cls");
    }

        std::cout<<'\n'<<"BOOK NAME     "<<'\t'<<"    BOOK Author    "<<'\t'<<"       TASK     "<<'\n';// headings

        for(k = 0; k < j; k++)                       // book details
        {
            std::cout<<"  "<<b[k].name<<'\t'<<b[k].author<<'\t';
            if(b[k].status)
                std::cout<<"To be Returned"<<'\n';
            else
                std::cout<<"To be Issued"<<'\n';
        }
        //if(iscan&&j)
        //std::cout<<'\n'<<"scan id card";
        //if((kbhit()&&(iscan&&j))||iscan&&(j==4))// atleast one id and book scanned when key is pressed or one id and 4 books scanned
            //goto issue;
        //issue:


        // for display variables
        temp1=ret;
        temp2=iss;
        x = 0;
        cost1 = 0;
        cost2 = 0;

        //return proccess
        while(ret)
        {
            k=ret;
            if(!strncmp(i.book1, re[x].rfid, 12))
            {
                i.books--;
                strncpy(i.book1, i.book2, 12);
                //strcpy(i.book2,"\0");
                for(p = 0; p < 12; p++)
                    i.book2[p] = '\0';
                re[x].status = 0;
                strncpy(re[x].id, null, 12);
                timing = date_time();
                cost1 = lib_fine(re[x].ti, timing);
                cout<<"days : "<<cost1<<endl;
                if(cost1 > 15)
                {
                Beep(1000,1000);
                cout<<"Penalty Fine : "<<cost1 - 15<<" rupees "<<endl;
                }
                re[x].ti = timing;
                modify_book(re[x]);
                modify_id(i);
                ret--;
                x++;
            }
            if(!strncmp(i.book2, re[x].rfid, 12))
            {
                i.books--;
                //strcpy(i.book2,"\0");
                for(p = 0; p < 12; p++)
                    i.book2[p] = '\0';
                re[x].status = 0;
                strncpy(re[x].id, null, 12);
                timing = date_time();
                cost2 = lib_fine(re[x].ti, timing);
                cout<<"days : "<<cost2<<endl;
                if(cost2 > 15)
                {
                Beep(1000,1000);
                cout<<"Penalty Fine : "<<cost2 - 15<<" rupees "<<endl;
                }
                re[x].ti = timing;
                modify_book(re[x]);
                modify_id(i);
                ret--;
                x++;
            }
            if(ret==k)// none of the return processed
            {
              std::cout<<'\n'<<" Wrong book scanned for return process , Restart";
              system("pause");
              goto start;
            }
        }
        if(temp1)
            cout<<'\n'<<temp1<<" returned "<<endl;
        // issue process
        x = 0;
        while(iss)
        {
            if(i.books<2)
            {
                if(!strncmp(i.book1, null, 12))
                {
                    strncpy(i.book1, is[x].rfid, 12);
                    i.books++;
                    is[x].status=1;
                    strncpy(is[x].id, i.rfid, 12);
                    is[x].ti = date_time();
                    modify_book(is[x]);
                    modify_id(i);
                }
                else if(!strncmp(i.book2, null, 12))
                {
                    strncpy(i.book2, is[x].rfid, 12);
                    i.books++;
                    is[x].status=1;
                    strncpy(is[x].id, i.rfid, 12);
                    is[x].ti = date_time();
                    modify_book(is[x]);
                    modify_id(i);
                }
                else
                {
                    std::cout<<'\n'<<" Error in book issue ";
                    system("pause");
                    goto start;
                }

            }
            else
            {
                std::cout<<'\n'<<" Book limit reached , Next Plz ";
                system("pause");
                goto start;
            }
            iss--;
            x++;
        }
        if(temp2)
            std::cout<<'\n'<<temp2<<" issued "<<endl;
        cout<<"Press enter to continue"<<endl;
        system("pause");

    }
}
