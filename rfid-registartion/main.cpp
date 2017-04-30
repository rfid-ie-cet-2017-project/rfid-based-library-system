#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <time.h>
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

char rfid[12];
char regd[16],iname[24];
char bname[16],author[24];
char position[6];
time_t timing;
char c;

int main(void)
{
    initr();
    int ch, s, temp, k;
    char last[12];
    BK b;
    ID i;
    while(1)
    {
        std::cout<<'\n'<<" 1 - Add new rfid "<<endl;
        std::cin>>ch;
        if(ch==1)
        {
            system("cls");
            std::cout<<'\n'<<"Scan new rfid"<<endl;
            //strcpy(rfid,"\0");
            strncpy(last, rfid, 12);
            while(!strncmp(last, rfid, 12))
                serialr(rfid);
            puts(rfid);
            std::cout<<'\n'<<" 0 - ID"<<'\n'<<" 1 - BOOK";
            std::cin>>s;
            if(s==0)
            {
                std::cout<<'\n'<<"Name :";
                strcpy(iname, getString());
                std::cout<<'\n'<<"Regd :";
                //std::cin>>regd;
                strcpy(regd, getString());
                write_id(rfid,iname,regd);
                // clear all array
                //for(k = 0; k < 12; k++)
                    //rfid[k] = '\0';
                for(k = 0; k < 16; k++)
                    regd[k] = '\0';
                for(k = 0; k < 24; k++)
                    iname[k] = '\0';
            }
            else
            {
                //std::cout<<'\n'<<"BOOK Rfid :";
                //std::cin>>rfid;
                std::cout<<'\n'<<"BOOK Name :";
                //std::cin>>bname;
                strcpy(bname, getString());
                std::cout<<'\n'<<"BOOK Author :";
                //std::cin>>author;
                strcpy(author, getString());
                std::cout<<'\n'<<"BOOK Position :";
                //std::cin>>position;
                strcpy(position, getString());
                write_book(rfid,bname,author,position);
                // clear all array
                //for(k = 0; k < 12; k++)
                    //rfid[k] = '\0';
                for(k = 0; k < 16; k++)
                    bname[k] = '\0';
                for(k = 0; k < 24; k++)
                    author[k] = '\0';
                for(k = 0; k < 6; k++)
                    position[k] = '\0';
            }

        }
        /*
        else if(ch==2)
        {
            system("cls");
            k = 0;
            do
            {
                last = arr[k].rfids[11];
                while(arr[k].rfids[11] == last)
                serialr(arr[k].rfids);
                puts(arr[k].rfids);
                k++;
                for(i = 0; i < 1000; i++)
                {
                    if((value = kbhit()) == 1)
                        break;
                }
            }while(value == 0)

            Retry1:
            system("cls");
            std::cout<<'\n'<<"Scan rfid"<<endl;
            //strcpy(rfid,"\0");
            last = rfid[11];
            while(rfid[11] == last)
            serialr(rfid);
            puts(rfid);
            s=status(rfid);
            std::cout<<s;
            temp=s;
            std::cout<<'\n'<<"Details : ";
            if(s == 1)
            {
                b=search_book(rfid);
                std::cout<<'\n'<<b.name;
            }
            else if(s == 0)
            {
                i=search_id(rfid);
                std::cout<<'\n'<<i.name;
            }
            else
            {
                cout<<"Retry the previous"<<endl;
                goto Retry1;
            }
            //for(k = 0; k < 12; k++)
                //rfid[k] = '\0';
            Retry2:
            std::cout<<'\n'<<"Scan another rfid";
            //strcpy(rfid,"\0");
            last = rfid[11];
            while(rfid[11] == last)
            serialr(rfid);
            puts(rfid);
            s=status(rfid);
            std::cout<<s;
             std::cout<<'\n'<<"Details : ";
            if(s == 1)
            {
                b=search_book(rfid);
                std::cout<<'\n'<<b.name;
            }
            else if(s == 0)
            {
                i=search_id(rfid);
                std::cout<<'\n'<<i.name<<'\n';
            }
            else
            {
                cout<<"Retry the previous"<<endl;
                goto Retry2;
            }
            //for(k = 0; k < 12; k++)
                //rfid[k] = '\0';

            if(strcmp(i.book1,"\0"))
            {
                BK b1=search_book(i.book1);
                //puts(b1.name);
            }
            if(strcmp(i.book2,"\0"))
            {
                BK b2=search_book(i.book2);
                //puts(b2.name);
            }


            if(temp==s)
            {
                std::cout<<'\n'<<"Same type rfid detected ";
                break;
            }



            // prcesssing of issue / return

    if(b.status==0&&i.books<2)
    {
        b.status=1;
        strcpy(b.id,i.rfid);
        if(i.books==0)
            strcpy(i.book1,b.rfid);
        else
            strcpy(i.book2,b.rfid);
        i.books++;
    std::cout<<'\n'<<"BOOK issued"<<endl;
    std::cout<<"Press ENTER to continue"<<endl;
    while(!kbhit());
    }
    else
    if(b.status==1&&i.books>0)
    {
        b.status=0;
        strcpy(b.id,"\0");
        if(!strcmp(i.book1,b.rfid))
            {
                std::cout<<i.book2;
                strcpy(i.book1,i.book2);
                strcpy(i.book2,"\0");
            }
        else
            strcpy(i.book2,"\0");
        i.books--;
    std::cout<<'\n'<<"BOOK returned"<<endl;
    std::cout<<"Press ENTER to continue"<<endl;
    while(!kbhit());
    }

    //find file position
    //id_pos = search_id_pos(i);
    //book_pos = search_book_pos(b);

    // modification in database
    modify_id(i);
    modify_book(b);
    //getch();

       }
       */
        else
        break;
    //getch();
    system("cls");
    }
    //getch();

}
