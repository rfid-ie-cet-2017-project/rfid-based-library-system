#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
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


//char rfid[12];
//char regd[16],iname[24];
char bname[16],author[24];
//char c;

int main(void)
{

    //int ch, s, temp, k;
    int k, stat = -1;
    //char last;
    BK b;
    //ID i;

    long pos = 0;
    //char confirm;

    initm();

    while(1)
    {

        monr(bname);
        puts(bname);

        monr(author);
        puts(author);


        pos = search_book_name(bname, pos);

        while(pos != -1)
        {
            b = search_book(pos);

            if(strcmp(author, b.author) == 0)
            {
                if(b.status == 0)
                {
                    stat = 0;            // book is in list and available
                    monw(b.position);
                    break;
                }
                else
                    stat = 1;          // book is in list but currently not available
            }
            pos = search_book_name(bname, ++pos);       // get the next book name if it exists
        }

        if(stat == 1)
            monw("CURRENTLY NOT AVAILABLE");
        if(stat == -1)
            monw("INCORRECT DATA ENTERED");


        for(k = 0; k < 16; k++)
        {
           bname[k] = '\0';
        }
        for(k = 0; k < 24; k++)
        {
           author[k] = '\0';
        }
    }
}


/*
pos = search_book_name(bname, pos);
*/


/*
        std::cout<<'\n'<<" 1 - Add new rfid "<<'\n'<<" 2 - Issue / return ";
        std::cin>>ch;
        if(ch==1)
        {
            system("cls");   // ???????
            std::cout<<'\n'<<"Scan new rfid"<<endl;
            //strcpy(rfid,"\0");
            last = rfid[11];
            while(rfid[11] == last)     // ???????
            serialr(rfid);             // ???????
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
                write_book(rfid,bname,author);
                // clear all array
                //for(k = 0; k < 12; k++)
                    //rfid[k] = '\0';
                for(k = 0; k < 16; k++)
                    bname[k] = '\0';
                for(k = 0; k < 24; k++)
                    author[k] = '\0';
            }

        }
        else if(ch==2)
        {
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
            /*if(s)
            b=search_book(rfid);
            else
            i=search_id(rfid);*/



            // prcesssing of issue / return
/*
    if(b.status==0&&i.books<2)
    {
        b.status=1;
        strcpy(b.id,i.rfid);
        if(i.books==0)
            strcpy(i.book1,b.rfid);
        else
            strcpy(i.book2,b.rfid);
        i.books++;
    std::cout<<'\n'<<"BOOK issued";
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
    std::cout<<'\n'<<"BOOK returned";
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
        else
        break;
    //getch();
    system("cls");
    }
    //getch();

}


/*
int main(void)
{

for(int j=0;j<2;j++)
    {
        std::cout<<'\n'<<"Rfid :";
        std::cin>>rfid;
        std::cout<<'\n'<<"Name :";
        std::cin>>iname;
        std::cout<<'\n'<<"Regd :";
        std::cin>>regd;
        write_id(rfid,iname,regd);

    }
for(int j=0;j<2;j++)
    {
        std::cout<<'\n'<<"BOOK Rfid :";
        std::cin>>rfid;
        std::cout<<'\n'<<"BOOK Name :";
        std::cin>>bname;
        std::cout<<'\n'<<"BOOK Autho :";
        std::cin>>author;
        write_book(rfid,bname,author);

    }
    std::cout<<'\n'<<"Rfid Scanned :";
    std::cin>>rfid;
    int s;
    BK b;
    ID i;
    s=status(rfid);
    if(s)
    b=search_book(rfid);
    else
    i=search_id(rfid);
    std::cout<<'\n'<<"Rfid Scanned :";
    std::cin>>rfid;
    s=status(rfid);
    if(s)
    b=search_book(rfid);
    else
    i=search_id(rfid);
    if(b.status==0&&i.books<2)
    {
        b.status=1;
        strcpy(b.id,i.rfid);
        if(i.books==0)
            strcpy(i.book1,b.rfid);
        else
            strcpy(i.book2,b.rfid);
        i.books++;
    std::cout<<'\n'<<"BOOK issued";
    }
    else
    if(b.status==1&&i.books>0)
    {
        b.status=0;
        strcpy(b.id,"\0");
        if(!strcmp(i.book1,b.rfid))
            {
                std::cout<<" giusg "<<i.book2;
                strcpy(i.book1,i.book2);
                strcpy(i.book2,"\0");
            }
        else
            strcpy(i.book2,"\0");
        i.books--;
    std::cout<<'\n'<<"BOOK returned";
    }
    modify_id(i);
    modify_book(b);
        std::cout<<'\n'<<"ID card rfid to  details display :";
    std::cin>>rfid;
    i=search_id(rfid);
    std::cout<<'\n'<<"BOOKS : ";
    if(!strcmp(i.book1,"\0"))
    {
        BK b1=search_book(i.book1);
        puts(b1.name);
    }
    if(!strcmp(i.book2,"\0"))
    {
        BK b2=search_book(i.book2);
        puts(b2.name);
    }

}
*/
