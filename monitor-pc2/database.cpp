#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "database.h"
using namespace std;



long idpos,bookpos;

void write_id(char *rfid,char *name,char *regd) // 1st time entry , rec details , store them to local class , write to file
{
idtag temp;
ident s;
strcpy(temp.rfid,rfid);
strcpy(s.rfid,rfid);s.status=0;
strcpy(temp.name,name);
strcpy(temp.regd,regd);
fstream fp1;
	fp1.open("id.txt", ios::app|ios::binary);
	while(fp1 == NULL)
    fp1.open("id.txt", ios::app|ios::binary);
fstream fp;
	fp.open("status.txt", ios::app|ios::binary);
	while(fp == NULL)
    fp.open("status.txt", ios::app|ios::binary);
fp1.write((char*)&temp, sizeof(temp));
fp.write((char*)&s, sizeof(s));
	fp1.seekg(0);
	fp1.close();
	fp.seekg(0);
	fp.close();
}

void write_book(char *rfid,char *name,char *author)
{
booktag temp;
class ident s;
strcpy(s.rfid,rfid);
s.status=1;
strcpy(temp.rfid,rfid);
strcpy(temp.name,name);
strcpy(temp.author,author);
fstream fp2;
	fp2.open("book.txt", ios::app|ios::binary);
	while(fp2 == NULL)
    fp2.open("book.txt", ios::app|ios::binary);
fstream fp;
	fp.open("status.txt", ios::app|ios::binary);
	while(fp == NULL)
    fp.open("status.txt", ios::app|ios::binary);
fp2.write((char*)&temp, sizeof(temp));
fp.write((char*)&s, sizeof(s));
fp2.seekg(0);
fp2.close();
fp.seekg(0);
fp.close();
}



ID search_id(char *rfid)// rec rfid tag to be searched , search rfid , return class with id details and it's positions
{
idtag buffer;
idpos=-1;
fstream fp3;
fp3.open("id.txt", ios::in|ios::binary);
while(fp3 == NULL)
    fp3.open("id.txt", ios::in|ios::binary);
fp3.seekg(0);
do
  {
      idpos=fp3.tellg();
      fp3.read((char*)&buffer, sizeof(buffer));
      //std::cout<<buffer.rfid<<'\t'<<strcmp(buffer.rfid,rfid)<<'\n';
      if(!strcmp(buffer.rfid,rfid))
      {
        break;
      }
      idpos=-1;
  }while(!fp3.eof());
fp3.close();
// create  a return class
ID ret(buffer,idpos);//if buffer not found idpos will be -1
return (ret);
}

BK search_book(char *rfid)
{
booktag buffer;
bookpos=-1;
fstream fp4;
fp4.open("book.txt", ios::in|ios::binary);
while(fp4 == NULL)
fp4.open("book.txt", ios::in|ios::binary);
fp4.seekg(0);
do
  {
      bookpos=fp4.tellg();
      fp4.read((char*)&buffer, sizeof(buffer));
      //std::cout<<buffer.rfid<<'\t'<<strcmp(buffer.rfid,rfid)<<'\n';
      if(!strcmp(buffer.rfid,rfid))
      {
        break;
      }
      bookpos=-1;
  }while(!fp4.eof());
fp4.close();
// create  a return class
BK ret(buffer,bookpos);//if buffer not found idpos will be -1     //???????????
return (ret);
}




void modify_id(ID rec)//rec class with id details and write position , convert to normal class , write to file
{
    idtag temp=rec.convert();
    //idpos = rec.idpos;
    idpos = search_id_pos(rec.rfid);
    fstream fp5;
	fp5.open("id.txt", ios::in | ios::out|ios::binary);
	while(fp5 == NULL)
    fp5.open("id.txt", ios::in | ios::out|ios::binary);
    fp5.seekg(idpos);
	fp5.write((char*)&temp, sizeof(temp));
	fp5.close();
}


void modify_book(BK rec)//rec class with id details and write position , convert to normal class , write to file
{
    booktag temp=rec.convert();
    //bookpos=rec.bookpos;
    bookpos = search_book_pos(rec.rfid);
    fstream fp6;
	fp6.open("book.txt", ios::in | ios::out|ios::binary);
	while(fp6 == NULL)
    fp6.open("book.txt", ios::in | ios::out|ios::binary);
    fp6.seekg(bookpos);
	fp6.write((char*)&temp, sizeof(temp));
	fp6.close();
}
int status(char * rfid)
{
class ident s;
fstream fp;
int a=-1;
fp.open("status.txt", ios::in|ios::binary);
while(fp == NULL)
fp.open("status.txt", ios::in|ios::binary);
fp.seekg(0);
do
  {
      fp.read((char*)&s, sizeof(s));
      /*std::cout<<"start\n";
      puts(s.rfid);
      std::cout<<"\t";
      puts(rfid);
      std::cout<<"end\n";*/
      if(!strncmp(s.rfid, rfid, 12))
      {
        a=s.status;
        break;
      }
  }while(!fp.eof());
fp.close();
return a;
}

long search_id_pos(char* data)
{
    idtag buffer;
    long position = -1;
    int flag = 0;
    fstream fp7;
    fp7.open("id.txt", ios::in | ios::out|ios::binary);
	while(fp7 == NULL)
    fp7.open("id.txt", ios::in | ios::out|ios::binary);

    fp7.seekg(0);
    do
    {
      position = fp7.tellg();
      fp7.read((char*)&buffer, sizeof(buffer));
      //std::cout<<buffer.rfid<<'\t'<<strcmp(buffer.rfid,rfid)<<'\n';
      if(!strncmp(buffer.rfid, data, 12))
      {
          flag = 1;
        break;
      }
      position = -1;
    }while(!fp7.eof());

    fp7.close();
    if(flag)
        return position;
    else
        return -1;
}

long search_book_author(char* data)
{
    booktag buffer;
    long position = -1;
    //int flag = 0;
    fstream fp8;
    fp8.open("book.txt", ios::in | ios::out|ios::binary);
	while(fp8 == NULL)
    fp8.open("book.txt", ios::in | ios::out|ios::binary);

    fp8.seekg(0);
    do
    {
      position = fp8.tellg();
      fp8.read((char*)&buffer, sizeof(buffer));
      //std::cout<<buffer.rfid<<'\t'<<strcmp(buffer.rfid,rfid)<<'\n';
      if(!strncmp(buffer.author, data, 12))
      {
        //flag = 1;
        break;
      }
      position = -1;
    }while(!fp8.eof());

    fp8.close();

    return position;
}


//******************************************START*********************************************************



/*  input : char array, file position
    search the file for respective class
    returns file position
*/
long search_book_name(char* data, long position)
{
    booktag buffer;
    //long position = -1;
    //int flag = 0;
    fstream fp8;
    fp8.open("book.txt", ios::in | ios::out|ios::binary);
	while(fp8 == NULL)
    fp8.open("book.txt", ios::in | ios::out|ios::binary);

    fp8.seekg(position);
    do
    {
      position = fp8.tellg();
      fp8.read((char*)&buffer, sizeof(buffer));
      //std::cout<<buffer.rfid<<'\t'<<strcmp(buffer.rfid,rfid)<<'\n';
      if(!strncmp(buffer.name, data, 12))
      {
        //flag = 1;
        break;
      }
      position = -1;
    }while(!fp8.eof());

    fp8.close();

    return position;
}


/*  input : file position
    returns book class at that position
*/
BK search_book(long bookpos)
{
booktag buffer;
fstream fp4;
fp4.open("book.txt", ios::in|ios::binary);
while(fp4 == NULL)
fp4.open("book.txt", ios::in|ios::binary);
fp4.seekg(bookpos);

fp4.read((char*)&buffer, sizeof(buffer));
std::cout<<buffer.name<<'\n';

fp4.close();
// create  a return class
BK ret(buffer,bookpos);//if buffer not found idpos will be -1     //???????????
return (ret);
}
