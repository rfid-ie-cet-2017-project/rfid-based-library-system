class ident
{
public:
    char rfid[12];
    int status;
};
class idtag
{
    public:
    char rfid[12];
    char name[24];
    char regd[16];
    int books;
    char book1[12];
    char book2[12];
    idtag()
    {
        books=0;
        strcpy(book1,"\0");
        strcpy(book2,"\0");
    }

};
class booktag
{
    public:
    char rfid[12];
    char name[16],author[24];
    char position[4];
    int status;
    char id[12];
    booktag()
    {
        status=0;
        strcpy(id,"\0");
    }
};
class BK
{
    public:
    char rfid[12];
    char name[16],author[24];
    char position[4];
    int status;
    char id[12];
    long bookpos;
    BK(booktag buffer,long b_bkpos)//booktag -> BK
    {
        strcpy(rfid,buffer.rfid);
        strcpy(name,buffer.name);
        strcpy(author,buffer.author);
        strcpy(position,buffer.position);
        strcpy(id,buffer.id);
        status=buffer.status;
        bookpos=b_bkpos;

    }
    BK()
    {

    };
    booktag convert()//BK->booktag
    {
        booktag temp;
        strcpy(temp.rfid,rfid);
        strcpy(temp.name,name);
        strcpy(temp.author,author);
        strcpy(temp.position,position);
        strcpy(temp.id,id);
        temp.status=status;
        return (temp);
    }

};


class ID
{
    public:
    char rfid[12];
    char name[24],regd[16];
    int books;
    char book1[12],book2[12];
    long idpos;
    ID(idtag buffer,long b_idpos)
    {
        strcpy(rfid,buffer.rfid);
        strcpy(name,buffer.name);
        strcpy(regd,buffer.regd);
        strcpy(book1,buffer.book1);
        strcpy(book2,buffer.book2);
        books=buffer.books;
        idpos=b_idpos;

    }
    idtag convert()
    {
        idtag temp;
        strcpy(temp.rfid,rfid);
        strcpy(temp.name,name);
        strcpy(temp.regd,regd);
        strcpy(temp.book1,book1);
        strcpy(temp.book2,book2);
        temp.books=books;
        return (temp);
    }
    ID()
    {

    };

};

long search_book_name(char* , long );  // return the position of file with given book name and current position of file

BK search_book(long );  // return the book class with given position of file


/*
void write_id(char *,char *,char *);  // receives rfid , name , regd of student and stores to file
void write_book(char *,char *,char *);//receives rfid , name, author of books and write to file
ID search_id(char*);// rec rfid id to be searched and returns details with status of search (-1 for not found else  position if found at idpos) , returns as ID object
BK search_book(char*);// same
void modify_id(ID);//recs ID object, with students updated details and position from the ID object and writes at that posn
void modify_book(BK);//same
int status(char*);
long search_id_pos(char*);       // search for the pos  id
long search_book_pos(char*);     // search foor the pos of the book
*/
