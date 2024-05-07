#include <iostream>
#include <iomanip>

using namespace std;
const int MAX_CUST = 100;
const double ST = 0.06;

class PackageChoice;
class History;
////////////////////////////////////////////////////////////////////////

class Customer
{
    protected:
    string name, phone, nationalID, email;
    int age;

    public:
    void inputdata()
    {
        cout<<"Enter Name         : ";
        cin.sync();
        getline(cin, name);
        
        cout<<"Enter Age          : ";
        cin>>age;
        
        cout<<"Enter NRIC         : ";
        cin.sync();
        getline(cin, nationalID);
        
        cout<<"Enter Phone Number : ";
        getline(cin, phone);

        cout<<"Enter Email        : ";
        cin.sync();
        getline(cin, email);
    }
    void displaydetails()
    {
        cout<<" Name   : "<<name<<endl<<" Age    : "<<age<<endl<<" NRIC   : "<<nationalID<<endl<<" Phone  : "<<phone<<endl<<" Email  : "<<email<<endl;
    }
    friend class Calculations;
    void friend Display_Tickets(Customer *, int );
};

class Booker:public Customer
{
    int BookerIndex;
    public:
    void setIndex(int i)
    {
        BookerIndex = i;
    }
    friend class History;
};


class Package1
{
    private:
    string location = "Singapore & Malaysia Summer Tour Package";
    double price = 2116.00;
    const int pack = 1;
    public:
    void display()
    {
        cout<<fixed<<setprecision(2)<<"\n    Package 1\n    ---------"<<endl<<"    "<<location<<"                                |RM "<<price<<"/Pax"<<endl;
    }
    friend class PackageChoice;
    void friend EditLocation(History &, PackageChoice &, int);
    
}Loc1;

class Package2: public Package1
{
    private:
    string location = "Kuala Lumpur, Penang and Langkawi Package";
    double price = 1345.00;
    const int pack = 2;
    public:
    void display()
    {
        cout<<fixed<<setprecision(2)<<"\n    Package 2\n    ---------"<<endl<<"    "<<location<<"                               |RM "<<price<<"/Pax"<<endl;
    }
    friend class PackageChoice;
}Loc2;

class Package3: public Package1
{
    private:
    string location = "Oriental Magic Group Tour in Thailand, Malaysia & Singapore";
    double price =  6378.00;
    const int pack = 3;
    
    public:
    void display()
    {
        cout<<fixed<<setprecision(2)<<"\n    Package 3\n    ---------"<<endl<<"    "<<location<<"             |RM "<<price<<"/Pax"<<endl;
    }
    friend class PackageChoice;
}Loc3;

class PackageChoice
{
    private:
    string location;
    double price;
    int pack;
    
    public:
    void display()
    {
        cout<<fixed<<setprecision(2)<<"Package "<<pack<<"\n---------"<<endl<<location<<setw(21)<<"|RM "<<price<<"/Pax"<<endl<<endl;
    }
    void CopyPackageDetails(Package1 &a)
    {
        location = a.location;
        price = a.price;
        pack = a.pack;
    }
    void CopyPackageDetails(Package2 &a)
    {
        location = a.location;
        price = a.price;
        pack = a.pack;
    }
    void CopyPackageDetails(Package3 &a)
    {
        location = a.location;
        price = a.price;
        pack = a.pack;
    }
    friend class Calculations;
    friend class History;
};

class Calculations
{
    protected:
    double price, tax, total;
    int pax, index;
    public:
    Calculations():price(0), tax(0), total(0){}
    void Calculate(PackageChoice &Package, int pax, int index)
    {
        price = Package.price;
        tax = (Package.price * pax) * ST;
        total = (Package.price * pax) + tax;
        this->pax = pax;
        this->index = index; 
    }
    void Display()
    {
        cout<<price<<endl<<tax<<endl<<total<<endl;
    }
    friend class History;
};


class History : protected Calculations
{
    string Location, Bookername, Email;
    public:
    void copy(Calculations &c, PackageChoice &p, Booker &b)
    {
        Bookername = b.name;
        Location = p.location;
        price = c.price;
        tax = c.tax;
        total =  c.total;
        pax = c.pax;
        index = c.index;
        Email = b.email;
    }
    void edit(Calculations &c, PackageChoice &p)
    {
        Location = p.location;
        price = c.price;
        tax = c.tax;
        total =  c.total;
    }
    void clear()
    {
        Location = "";
        price=0;
        tax=0;
        total=0;
        pax=0;
        index=0;
    }
    void friend PrintHistory(History *, int );
    void friend EditLocation(History &, PackageChoice &, int);
    void friend EditandRecalculate(History *, int , int);
    void friend DeleteBooking(History *, int );
    void friend Display_Receipt(History &);

};
void PrintHistory(History *H, int index)
{
    cout<<"\n\n|-------------------------------------------------------------------------------------------------------------------------------------------|\n";
    cout<<"| B.Num |"<<" Booker Name                                 "<<"| Package Location"<<"                                             "<<"| Total Price    "<<"| Pax |"<<endl;
    cout<<"|-------------------------------------------------------------------------------------------------------------------------------------------|\n";
    for(int i = 0 ; i < index; i++)
    {
        if(H[i].index != 0)
        cout<<"    "<<H[i].index<<"     "<<setw(46)<<left<<H[i].Bookername<<setw(63)<<H[i].Location<<"RM "<<setw(15)<<H[i].total<<H[i].pax<<endl;
    }
}
void EditLocation(History &H, PackageChoice &P,int x)
{
    Calculations CD;
    CD.Calculate(P, H.pax ,x);
    H.edit(CD, P);
}
void thanks();
void tickettext();
void receipt();
void options();
void inputChoice(int &);
void inputPax(int &);
void option1(int , int , PackageChoice &, Customer *);
void password(int *x);
void EnterToComtinue();
void DisplayAllLocs();
//MAIN PROGRAM//
////////////////////////////////////////////////////////////
int main()
{
    History H[MAX_CUST];
    Booker Book[MAX_CUST];
    int wrongchoice = 0; // 1 is yes, 0 is no
    
    int choice, index = 0;
    
    while(true)
    {   
        PackageChoice Picked;
        int pax = 0;
        options();
        if(wrongchoice == 1)
        {
            cout<<"\n\nNo Purchase History. You can only use this Choice when a purchase has been made.\nPlease input your choice again."<<endl;
            wrongchoice = 0;
        }
        else if(wrongchoice == 2 && choice != 99)
        {
            cout<<"\n\nPlease Input within the number 1 to 4.\nPlease input your choice again."<<endl;
            wrongchoice = 0;
        }
        cout<<"\nEnter Choice: ";
        cin>>choice;
        cin.sync();
        if(choice == 99)
        {
            int *back = new int{0}; 
            password(back);
            if(*back == 0)
            {
                delete back;
                cout<<"\nProgram Exited Successfully."<<endl;
                thanks();
                break;
            }
        }

            while(choice >= 0)
            {
                if(choice==1)
                {
                    int *a = new int;
                    cout<<"--------------------"<<endl;
                    cout<<"|--Booker Details--|"<<endl;
                    cout<<"--------------------"<<endl;
                    cout<<"Please provide your information for future references.\nYou may proceed to type your information again in the registration process.\n";
                    Book[index].inputdata();
                    Book[index].setIndex(index);
                    cout<<"\n|--------------------------------------------------------------------------------------------|"<<endl;
                    cout<<"                        SOUTH EAST ASIA TOURIST BOOKING SELECTION\n             These are the packages that are currently available for purchase!";
                    DisplayAllLocs();
                    inputChoice(choice);
                    inputPax(pax);
                    Calculations CD;
                    Customer Cust[pax];
                    option1(choice,pax,Picked,Cust);
                    CD.Calculate(Picked, pax,(index+1));
                    H[index].copy(CD, Picked, Book[index]);
                    Display_Receipt(H[index]);
                    index++;
                    cout<<"\n[PRESS ENTER TO DISPLAY TICKETS]";
                    *a = getchar();
                    cin.sync();
                    Display_Tickets(Cust, pax);
                    EnterToComtinue();
                    delete a;
                    break;
                }
                else if (choice == 2)
                {
                    if (choice == 2 && index == 0)
                    {
                        wrongchoice = 1;
                        break;
                    }
                    else
                    {
                        int *back = new int{0};
                        password(back); 
                        if(*back == 1)
                        {break;}
                        delete back;
                        int e;
                        PrintHistory(H,index);
                        cout<<"\n!!!!--[TYPE '99' TO EXIT LOCATION EDITING MODE]--!!!!\n";
                        cout<<"\nEnter the index that you wish to EDIT.\n\nPlease type the correct value on displayed above.\nInxed Value? : ";
                        cin>>e;
                        if(e == 99)
                        {break;}
                        EditandRecalculate(H, e, index);
                        PrintHistory(H,index);
                        cout<<"\n\n!!!!--[LOCATION EDITING COMPLETE]--!!!!"<<endl;
                        EnterToComtinue();
                        break;
                        }
                }
                else if (choice == 3)
                {
                    if (choice == 3 && index == 0)
                    {
                        wrongchoice = 1;
                        break;
                    }
                    else 
                    {
                        int *back = new int{0};
                        password(back);
                        if(*back == 1)
                        {break;}
                        delete back;
                        int d;
                        PrintHistory(H,index);
                        cout<<"\n!!!!--[TYPE '99' TO EXIT DELETION MODE]--!!!!\n";
                        cout<<"\nEnter the index that you wish to DELETE.\n\nPlease type the correct value on displayed above.\nInxed Value? : ";
                        cin>>d;
                            if(d == 99)
                            {break;}
                        DeleteBooking(H,d);
                        PrintHistory(H,index);
                        cin.sync();
                        cout<<"\n\n!!!!--[DELETION COMPLETE]--!!!!"<<endl;
                        EnterToComtinue();
                        break;
                    }
                }
                else if (choice == 4)
                {
                    if (choice == 4 && index == 0)
                    {
                        wrongchoice = 1;
                        break;
                    }
                    else
                    {
                    PrintHistory(H,index);
                    EnterToComtinue();
                    break;
                    }
                }
                else
                {
                    if(choice != 99)
                    {
                    wrongchoice = 2;
                    break;
                    }
                    else
                    break;
                }
            }
    }
    return 0;
}
void options()
{
    cout<<"  |---------------------------|\n           WELCOME TO"<<endl;
    cout<<"   --SOUTH EAST ASIA TOURISM--\n  |---------------------------|"<<endl;
    cout<<"\n|-------------------------------|";
    cout<<"\n      1) New Booking\n\n      2) Edit Travel Location\n\n      3) VOID Travel\n\n      4) View Receipt History\n\n      99) Exit Program\n";
    cout<<"|-------------------------------|"<<endl; 
}
void DisplayAllLocs()
{
    cout<<"\n|--------------------------------------------------------------------------------------------|";
    Loc1.display();
    Loc2.display();
    Loc3.display();
    cout<<"|--------------------------------------------------------------------------------------------|"<<endl;
}
void inputChoice(int &c)
{
    do{
    cout<<"\nEnter Choice: ";
    cin>>c;
    cin.sync();
    if(c == 0 || c > 3)
    {
        DisplayAllLocs();
        cout<<"\nWrong Choice. Please enter your choice again.\n";
    }
    }while(c == 0 || c > 3);
}
void inputPax(int &p)
{
    cout<<"\nEnter Pax   : ";
    cin>>p;
}
void option1(int choice, int pax, PackageChoice &Picked, Customer *Cust)
{
    if(choice == 1)
        {
            Picked.CopyPackageDetails(Loc1);
        }
        else if(choice == 2)
        {
            Picked.CopyPackageDetails(Loc2);
        }
        else if(choice == 3)
        {
            Picked.CopyPackageDetails(Loc3);
        }
        
        for(int i = 0 ; i < pax ; i++)
        {
            cout<<"\nTourist #"<<i+1<<endl;
            cout<<"----------"<<endl<<endl;
            Cust[i].inputdata();
        }
}
void Display_Tickets(Customer *C, int pax)
{

    for(int i = 0; i < pax ; i++)
    {
        cout<<"\n\n|--------------------------------|"<<endl;
        tickettext();
        cout<<"|--------------------------------|"<<endl;
        
        cout<<"Tourist #"<<i+1<<"'s Info"<<endl;
        cout<<"|--------------------------------|"<<endl;
        C[i].displaydetails();
        cout<<"**********************************"<<endl;
    }
}
void EditandRecalculate(History *H, int x, int index)  //x is the index that the user wants to delete
{
    PackageChoice *PC = new PackageChoice;
    int a;

    DisplayAllLocs();
    cout<<"\n\nPlease input the new Package.";
    inputChoice(a);

    if(a == 1)
        {
            PC->CopyPackageDetails(Loc1);
        }
        else if(a == 2)
        {
            PC->CopyPackageDetails(Loc2);
        }
        else if(a == 3)
        {
            PC->CopyPackageDetails(Loc3);
        }

    for(int i = 0; ;i++)
    {
        if(H[i].index == x)
        {
            EditLocation(H[i], *PC, x);
            break;
        }
    }
    delete PC;
}
void DeleteBooking(History *H, int x)
{
    for(int i = 0; ;i++)
    {
        if(H[i].index == x)
        {
            H[i].clear();
            break;
        }
    }
}
void password(int *x)
{
    string *ps = new string;
    int *wrongps = new int{0};
    do
    {
        if(*wrongps == 1)
        {
        cout<<"\n\nWrong Password...";
        }
        cout<<"\nEnter Admin Password to Proceed. (Input 0 to go back to MAIN)\n\nEnter Password : ";
        getline(cin,*ps);
        cin.sync();
            if(*ps == "password")
            {
                delete ps;
                delete wrongps;
                break;
            }
            else if(*ps == "0")
            {
                delete ps;
                delete wrongps;
                *x = 1;
                break;
            }
        *wrongps = 1;
    }while(*ps != "password");
}
void receipt()
{
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
    cout<<"                         _____  ______ _____ ______ _____ _____ _______ "<<endl;
    cout<<"                        |  __ \\|  ____/ ____|  ____|_   _|  __ |__   __|"<<endl;
    cout<<"                        | |__) | |__ | |    | |__    | | | |__) | | |   "<<endl;
    cout<<"                        |  _  /|  __|| |    |  __|   | | |  ___/  | |   "<<endl;
    cout<<"                        | | \\ \\| |___| |____| |____ _| |_| |      | |   "<<endl;
    cout<<"                        |_|  \\_|______\\_____|______|_____|_|      |_|   "<<endl;
}
void  Display_Receipt(History &H)
{
    receipt();
    cout<<"\n|---------------------------------------------------------------------------------------------|"<<endl;
    cout<<"|Booking Number   : "<<H.index<<endl;
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
    cout<<"|Travel Package   : "<<H.Location<<endl;
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
    cout<<"|Bookername       : "<<H.Bookername<<endl;
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
    cout<<"|Email            : "<<H.Email<<endl;
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
    for(int j=5;j>0;j--)
    {
        for(int i=0;i<48;i++)
        {
                cout<<"* ";
        }
        cout<<"\n";
    }
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
    cout<<setw(-4)<<right<<"|Pax:"<<H.pax<<setw(79)<<right<<"Total price : RM "<<H.total<<endl;
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;
    cout<<setw(-12)<<right<<"|Price: RM "<<H.price<<setw(62)<<"TAX (6%)"<<": RM "<<H.tax<<endl;
    cout<<"|---------------------------------------------------------------------------------------------|"<<endl;   
}
void tickettext()
{
cout<<"|  _____ _      _        _       |"<<endl;
cout<<"| |_   _(_) ___| | _____| |_ ___ |"<<endl;
cout<<"|   | | | |/ __| |/ / _ \\ __/ __||"<<endl;
cout<<"|   | | | | (__|   <  __/ |_\\__ \\|"<<endl;
cout<<"|   |_| |_|\\___|_|\\_\\___|\\__|___/|"<<endl;
}
void thanks()
{
    cout<<"  __  __           _                   ____                                   "<<endl;
    cout<<" |  \\/  | __ _  __| | __ _ _ __ ___   |  _ \\ _   _ ______ _ _ __  _ __   __ _ "<<endl;
    cout<<" | |\\/| |/ _` |/ _` |/ _` | '_ ` _ \\  | |_) | | | |_  / _` | '_ \\| '_ \\ / _` |"<<endl;
    cout<<" | |  | | (_| | (_| | (_| | | | | | | |  _ <| |_| |/ / (_| | | | | | | | (_| |"<<endl;
    cout<<" |_|  |_|\\__,_|\\__,_|\\__,_|_| |_| |_| |_| \\_ \\__,_/___\\__,_|_| |_|_| |_|\\__,_|"<<endl;
    cout<<"                  ____ _                _           ____  _     "<<endl;
    cout<<"                 / ___(_)_   _____     / \\    _    |  _ \\| |___ "<<endl;
    cout<<"                | |  _| \\ \\ / / _ \\   / _ \\ _| |_  | |_) | / __|"<<endl;
    cout<<"                | |_| | |\\ V /  __/  / ___ \\_   _| |  __/| \\__ \\"<<endl;
    cout<<"                 \\____|_| \\_/ \\___| /_/   \\_\\|_|   |_|   |_|___/"<<endl;
}
void EnterToComtinue()
{
    char *a = new char;
    cout<<"\n[PRESS ENTER TO CONTINUE]";
    *a = getchar();
    delete a;
}