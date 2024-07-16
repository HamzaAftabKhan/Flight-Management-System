#include<conio.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include<unistd.h>
#include<time.h>
//#include<cmath>
//#include<ctime>
#include<stdlib.h>
#include"payment.h"
//#include<stdio.h>
using namespace std;

bool datecheck(int, int, int, int);
const char l_destination[5][20]={"LAHORE","ISLAMABAD","KARACHI","PESHAWAR","QUETTA"};	//local Destination
const char i_destination[11][20]={"LONDON","BERLIN","DUBAI","BEIJING","TOKYO","WASHINGTON" }; //International Destination

class passenger{
	private:
		const int BusinessClassSeats;
		const int EconomyClassSeats;
	protected:
		string firstName,lastName, phone, mealType, passport, address;
		int business, economy, datedeparture, payment;
		char origin[30];
		char destination[30];
	public:		
		passenger(string f_name, string l_name, string phone_no, string add="N/A", string pass_no="N/A", int dd=000000): BusinessClassSeats(10), EconomyClassSeats(50)
		{
			datedeparture=dd;
			firstName=f_name;      // constuctor to intialize the value of the function
			lastName=l_name;     // the class is an abstract class therfore all the function are virtual 
			address=add;
			phone=phone_no;
			passport=pass_no;
			business = BusinessClassSeats;
			economy = EconomyClassSeats;
		}
		
		virtual bool LocalDestination()=0;
		virtual bool InternationalDestination(string pass)=0;
		virtual void Seats()=0;
		virtual void Meals()=0;
		virtual void Registration()=0;
		virtual bool Display()=0;
		virtual void Drive()=0;
		
};

class booking:public passenger
{
	protected:
		int num,mun,k,no_of_seats,choice;
	public:                                  // booking is the inherited class that use the passenger class attributes
		
		booking(string f,string l,string numb,string add,string pass,int dd):passenger(f,l,add,numb,pass,dd)  //member intializer list
		{
			num=0;
			mun=0;
		}
		
	bool LocalDestination()
	{
		 // overriding of the function already declared in the passendger class
		cout<<endl<<"These are the local destinations where we are flying: \n";
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<20;j++)
			{
				cout<<l_destination[i][j];           //displaying the output of the array declared globally
			}
			cout<<"\n";
		}

		again:
		cout<<endl<<"Enter your origin(using BLOCK letters): ";
		cin>>origin;
		cout<<endl<<"Enter your destination(using BLOCK letters): ";      // taking input from the user to compare it and store it 
		cin>>destination;
		if(strcmp(origin,destination)==0)
		{
			cout<<"Invalid Origin and Destination Enter again\n";
			goto again;
		}
		else
		{
			for(int i=0;i<5;i++)
			{
				if(strcmp(l_destination[i],origin)==0)
					num++;
			}
			for(int j=0;j<5;j++)
			{
				if(strcmp(l_destination[j],destination)==0)
					mun++;
			}
			if(mun==1&&num==1)
			{
				payment = lpayment(origin, destination);
				cout<<endl<<"Price: "<<payment<<" Pkr/seat"<<endl;
				return true;
			}
			else 
				return false;
			
		}
	}
	
		bool InternationalDestination(string pass)        // same function but now using international flights data
	{
		passport = pass;
		cout<<endl<<"These are the international destinations where we are flying: \n";
		for(int i=0;i<11;i++)
		{
			for(int j=0;j<20;j++)
			{
				cout<<i_destination[i][j];
			}
			cout<<"\n";
		}
		again:
		cout<<endl<<"Enter your origin(using BLOCK letters): ";
		cin>>origin;                                             // taking inpput
		cout<<endl<<"Enter your destination(using BLOCK letters): ";
		cin>>destination;
		if(strcmp(origin,destination)==0)
		{
			cout<<"Invalid Origin and Destination Enter again\n";
			goto again;
		}
		else
		{
			for(int i=0;i<11;i++)
			{
				if(strcmp(i_destination[i],origin)==0)
					num++;
			}
			for(int j=0;j<11;j++)
			{
				if(strcmp(i_destination[j],destination)==0)
					mun++;
			}
			if(mun==1&&num==1)
			{
				payment = ipayment(origin, destination);
				cout<<endl<<"Price: "<<payment<<" Pkr/seat"<<endl;            // calculating the price of flight by comparing both the destination
				return true;
			}
			else 
				return false;
		}
	}

		
		void Seats()
		{
			bus_eco:
				if(business>0&&economy>0)   //taking input for seats
				{// we have two types economy and business
					cout<<endl<<"1.Business Class\n2.Economy Class\n";
					k = getch();
					switch(k)
					{
						case 49:
						{
							cout<<endl<<"Business Class";
							cout<<endl<<"Enter the number of seats: ";
							cin>>no_of_seats;
							payment=(payment*no_of_seats)+5000;               //taking the number of seats 
							if(no_of_seats<=business)                         //validating the seats and then sending payment
							{
								cout<<endl<<"Seats are available.\n\n";
								business=business-no_of_seats;
							}
							else
							{
								cout<<endl<<"Seats are not available.\n\n";
								cout<<"we have only "<<business<<" seats available.\n"<<endl;
								cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
								k = getch();
								if(k==49)
								{
									no_of_seats = business;
									payment=(payment*no_of_seats)+5000;
								 	cout<<"Seats are booked\n\n";
								 	business=0;
								}
								else
								{
									cout<<endl<<"See you again.\n";
									exit(0);
								}
							}
							break;
						}
						
					case 50:
						{
							cout<<endl<<"Economy Class";
							cout<<endl<<"Enter the number of seats: ";
							cin>>no_of_seats;
							payment=(payment*no_of_seats);
							if(no_of_seats<=economy)
							{                                        //same as above
								cout<<endl<<"Seats are available.\n\n";
								economy=economy-no_of_seats;
							}
							else
							{
								cout<<endl<<"Seats are not available.\n\n";
								cout<<"we have only "<<economy<<" seats available.\n"<<endl;
								cout<<"Do you wish to book remaining seats\nPress 1 for YES\nPress 2 for NO\n";
								k = getch();
								if(k==49)
								{
									no_of_seats = economy;
									payment=(payment*no_of_seats);
									cout<<endl<<"Seats are booked\n\n";
									economy=0;
								}
								else
								{//''''''''''''''''''''''''''''''
									cout<<endl<<"See you again.\n";
									exit(0);
								}
							}
							break;
						}
					
					default:
						{
							cout<<"Error!\n";
							goto bus_eco;
						}                      //;;;;;;;;;;;;;;;;;;
				}
			}
			else
			{
				cout<<endl<<"Sorry no seats available\nHave a nice day!";
				exit(0);
			}
		}
	//;;;;;;;;;;;;;;;;;;;;;;;
		
		void Meals()
		{
			meal:
			int n;
			cout<<endl<<"Available meal types:\n1.Vegetarian\n2.Non-Vegetarian\n";
			n = getch();
			if(n==49)//////////takinf meals value
				mealType="Vegetarian";
			else if(n==50)
				mealType="Non Vegetarian";
			else
			{
				cout<<"ERROR!!!"<<endl;
				goto meal;
			}
		}
		
		void Registration()
		{
			int ticket;
			srand (time(NULL));
			ticket = rand()%1000;
			if(k==49)
			{
				ofstream outfile;
				outfile.open("flight.txt");
				outfile<<"|TICKET INFORMATION:"<<endl<<endl
				<<"Name: "<<firstName<<" "<<lastName<<endl
				<<"Phone: "<<address<<endl
				<<"Address: "<<phone<<endl
				<<"Passport Number: "<<passport<<endl
				<<"Origin: "<<origin
				<<endl<<"Destination: "<<destination
				<<endl<<"Food: "<<mealType
				<<endl<<"Number of Seats: "<<no_of_seats
				<<endl<<"Class: Business"
				<<endl<<"Date of departure: "<<datedeparture
				<<endl<<"Time: 4.00 PM"
				<<endl<<"Ticket: HF"<<ticket
				<<endl<<"Bill(in pakistani rupees): "<<payment<<"/-"<<endl;				
				outfile.close();
			}
			else if(k==50)
			{
				ofstream outfile;
				outfile.open("flight.txt");
				outfile<<"|TICKET INFORMATION:"<<endl<<endl
				<<"Name: "<<firstName<<" "<<lastName<<endl
				<<"Phone: "<<address<<endl
				<<"Address: "<<phone<<endl
				<<"Passport Number: "<<passport<<endl
				<<"Origin: "<<origin
				<<endl<<"Destination: "<<destination
				<<endl<<"Food: "<<mealType
				<<endl<<"Number of Seats: "<<no_of_seats
				<<endl<<"Class: Economy"
				<<endl<<"Date of departure: "<<datedeparture
				<<endl<<"Time: 4.00 PM"
				<<endl<<"Ticket: HF"<<ticket
				<<endl<<"Bill(in pakistani rupees): "<<payment<<"/-"<<endl;
				outfile.close();
			}
		}
		
		bool Display()
		{
			bool ans;
			system("cls");
			string temp;
			ifstream infile;
			infile.open("flight.txt");
			while(!infile.eof())
			{
				getline(infile,temp);
				cout<<temp<<endl;
			}
			ans = Confirm();
			return ans;
		}
		
		bool Confirm()
		{
			char ch;
			confirm:
			cout<<endl<<endl<<"Do you wish to confirm your ticket?(y/n): ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl<<"|STATUS CONFIRMED";
				ofstream outfile;
				outfile.open("flight.txt",ios::app);
				outfile<<endl<<"|STATUS CONFIRMED";
				outfile.close();
				return true;
			}
			else if(ch=='N'||ch=='n')
			{
				ofstream outfile;
				outfile.open("flight.txt",ios::app);
				outfile<<endl<<"|BOOKING CANCELLED";
				cout<<endl<<endl<<"|BOOKING CANCELLED"
				<<endl<<"Going back to main page";
				sleep(3);
				outfile.close();
				return false;
			}
			else
			{
				cout<<endl<<"ERROR!!!";
				goto confirm;
			}
		}
		
		inline void Drive()
		{
			string pick;
			cout<<endl<<"Please enter your pickup point: ";
			cin.ignore();
			getline(cin,pick);             //taking dropof opton
			cout<<endl<<endl<<"Pickup Location: "<<pick;
			cout<<endl<<"Drop Off: "<<origin<<" Airport"
			<<endl<<"Fare: 300/-";
			cout<<endl<<endl<<"You will be contacted by our driver shortly\nHave a nice day!";
			fstream ofile;
			ofile.open("flight.txt",ios::app);
			ofile<<endl<<endl<<"Pick'n Drop: YES"<<endl<<endl
			<<"Pickup Location: "<<pick
			<<endl<<"Drop Off: "<<origin<<" Airport"
			<<endl<<"Fare: 300/-";
			ofile.close();
		}
};

class Manage
{//manage class to see the ticket and also reschedule the time
	private:
		string temp,y,c2;
		int option;
	public:
		int change()
		{	
			int i=0;
			
			ifstream file("flight.txt");
			if(file.is_open())
			{
			cout<<endl<<"Enter your Ticket Number or Press 0 to exit\nTicket Number: ";
			cin>>temp;
			if(temp=="0")
				return 1;
			string v("Ticket: "+temp);
			
			while(!file.eof())
			{
				getline(file,y);
				if(y==v)
				{
					file.seekg(0,ios::beg);
					while(!file.eof())
					{
						getline(file,temp);
						cout<<temp<<endl;
					}
					cout<<endl<<endl<<"1.Change date\n2.Cancel the flight\n3.Go Back\n";
					option = getch();
					switch(option)
					{
						case 49:
						{
							file.seekg(0,ios::beg);
							ofstream ofile("temp.txt");
							cout<<endl<<"Enter the new date of departure(DDMMYYYY): ";
							cin>>c2;
							string c1("Date of departure: "+c2);
							while(!file.eof())
							{
								getline(file,y);
								if(i==11)
								{
									i++;
									ofile<<c1<<endl;
								}
								else
								{
									i++;
									ofile<<y<<endl;//'''''''''''''''''''''''
								}
							}
							file.close();//'''''''''''''''''''''''
							ofile.close();//''''''''''''''''''''
							ofstream outfile;
							outfile.open("flight.txt");
							ifstream readfile("temp.txt");
							while(!readfile.eof())
							{
								getline(readfile,y);
								outfile<<y<<endl;
							}
							outfile.close();
							readfile.close();
							remove("temp.txt");
							cout<<endl<<"Date Changed!";
							return 1;
							break;
						}
					
						case 50:
						{
							file.close();
							ofstream ofli;
							ofli.open("flight.txt",ios::trunc);
							ofli.close();
							remove("flight.txt");
							system("cls");
							cout<<endl<<"Booking cancelled!\n\n";
							return 1;
							break;
						}
						case 51:
							system("cls");
							return 1;
					}
				}
			}
		}
		else if(!file.is_open())
		{
			cout<<endl<<endl<<"unable to find any record"<<endl;
			cout<<endl<<"going back to main page\n\n";
			file.close();
			return 1;
		}
	}
};


class about
{
	public:
		void Aboutus()
		{
			cout<<"Welcome to our flight system, dedicated to providing you with safe, comfortable, and reliable travel to destinations around the world.\n"
                  "At our flight system, we believe that air travel should be affordable and accessible to everyone, without compromising on quality or service.\n"
                  "Experience the convenience and ease of booking and managing your flights with our user-friendly online platform, available 24/7.\n"
                  "Our flight system is committed to reducing our environmental impact and promoting sustainable travel practices for a better future.\n"
                  "With a team of experienced and dedicated professionals, we are proud to offer a seamless and enjoyable travel experience from start to finish.\n"<<endl<<endl;
			cout<<"Press any key to continue...";
		}
	
};
class complain
{
	private:
		string f_name, l_name, p_num;
		int choice;
		string sentence;
		string types;              //complain class to check for complains
		char ch;
	public:
		complain(string f,string l,string num)
		{
			f_name = f;
			l_name = l;
			p_num = num;
		}
		
	void type()
	{
		back:
		cout<<endl<<endl<<"Enter the type of complain you want to register:\n1.Airport Handling\n2.Baggage Delivery\n3.Booking and ticketing\n4.Other\n";
		choice = getch();
		cin.ignore();
		cout<<"Enter your complain:\n";
		if(choice==49)
		{
			cout<<"Airport Handling: ";
			types = "Aiprort Handling: ";
		}
		else if(choice==50)
		{
			cout<<"Baggage Delivery: ";
			types = "Baggage Delivery: ";
		}
		else if(choice==51)
		{
			cout<<"Booking and Ticketing: ";
			types = "Booking and Ticketing: ";
		}
		else if(choice==52)
		{
			cout<<"Other: ";
			types = "Other: ";
		}
		getline(cin,sentence);
		cout<<endl<<"Do you want to edit your complain(y/n): ";
		ch=getch();
		if(ch=='Y'||ch=='y')
			goto back;
		else
		{
			cout<<endl<<"Complain noted!\n";
			ofstream outfile;
			outfile.open("complain.txt");
			outfile<<"Name: "<<f_name<<" "<<l_name<<endl
			<<"Phone: "<<p_num<<endl
			<<"Complain:\n"<<types<<sentence;
			outfile.close();
			sleep(3);		
		}
	}
};
class routes{
	public:
		bool print()
		{
			int i,j;
			char ch;
			cout<<"\n\n\n\n\tFollowing are the international flights available"<<endl;
			for(i=0;i<5;i++)
			{
				cout<<endl;
				for(j=0;j<5;j++)
				{
					if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<l_destination[i]<<" to "<<i_destination[j]<<endl;
					}
					
				}
			}
			cout<<"\n\n\n\n\tFollowing are the local flights available"<<endl;
			for(i=0;i<5;i++)
			{
				cout<<endl;
				for(j=0;j<5;j++)
				{
						if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<l_destination[i]<<" to "<<l_destination[j]<<endl;
					}
				}
			}
			cout<<endl<<"Do you want to book a flight(y/n) ";
			ch=getch();
			if(ch=='Y'||ch=='y')
			{
				cout<<endl<<endl;
				return true;
			}
			else
				return false;
		}
		
};
class Login{
	protected:
		string username;
        string password;
        string fullName;
        string email;
        int cnic[13];
        int a=0;
};
class User:public Login{
	public:
	void signUp() {
		user:
    cout << "Enter a username: ";
    cin >> username;

    cout << "Enter a password: ";
    cin >> password;

cout<<"Enter CNIC number:";
	while (cnic[a]!='\0')
	{
	cin>>cnic[a++];
	}
	if(a==12)
	cout<<"valid";
	else {
	cout<<"Invalid";
	goto user;
	}
    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, fullName);

    cout << "Enter your email address: ";
    cin >> email;

    // Append the new user to the file
    ofstream usersFile("users.txt", std::ios::app);
    if (usersFile.is_open()) {
        usersFile << username << " " << password<<" "<<cnic<<endl ;
        cout << "Account created successfully!" << endl;
    } else {
        cerr << "Unable to open users file!" << endl;
    }
    usersFile.close();
}

// Function to verify user credentials
bool verifyUser(string username, string password) {
    ifstream usersFile("users.txt");
    if (usersFile.is_open()) {
    	string user,pass;
    	while(usersFile>>user>>pass){
    		if(user==username&&pass==password){
    			usersFile.close();
    			return true;
			}
    }	
        }
        else{
        	usersFile.close();
		cerr << "Unable to open users file!" <<endl;
		}
    return false;
}

// Function to display the login menu
bool login() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your password: ";
    cin >> password;

    if (verifyUser(username, password)) {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Invalid username or password. Please try again." << endl;
    return false;
	}
}
};
class Admin:public Login{
	public:
		
	string username, password;
	int choice;
	bool login(){
	
    cout << "Enter your username: ";
    cin >> username;
    string password = "";
    char ch;
    cout << "Enter password: ";
    while ((ch = getch()) != '\r') { // loop until user presses enter key
        if (ch == '\b') { // if backspace key is pressed
            if (!password.empty()) { // check if password string is not empty
                password[password.length() - 1] = ' '; // overwrite last character with a space
                cout << "\b \b"; // erase last character from console
            }
        } else {
            password += ch;
            cout << '*'; // display asterisk for each character entered
        }
    }

    if (username=="admin"&&password=="123ha") {
        cout << "Login successful!" << endl;
        system("cls");
        login:
        cout<<"<<<<<<<<<<ADMIN PANEL>>>>>>>>>>"<<endl;
        cout<<"Press 1 to manage Complains"<<endl;
        cout<<"Press 3 to exit"<<endl;
        cin>>choice;
        cin.ignore();
        switch(choice){
        	case 1:
        		resolve_complain();
        		break;
			case 2:
					exit(0);
					break;
			default:
			cout<<	"Invalid Input"<<endl;
			goto login;
			break;
		}
        return true;
    } else {
        cout << "Invalid username or password. Please try again." << endl;
    return false;
	}
	}
	 void view_complains() {
            ifstream infile("complain.txt");
            if (infile.is_open()) {
                string line;
                while (getline(infile, line)) {
                    cout << line << endl;
                }
                infile.close();
            } else {
                cerr << "Unable to open file: "  << endl;
            }
        }

        void resolve_complain() {
            view_complains(); // Display all the complains

           string search_string; 
            cout << endl << "Enter the complain ID you want to mark as resolved: ";
    getline(cin, search_string);
ifstream infile("complain.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            if (line.find(search_string) != string::npos) {
                cout << "Resolved: " << line << endl;
            }
        }
        infile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

};
class HomePage{
	public:
		HomePage(){
		cout<<endl<<"<<<<<<<<<<Welcome to NUCES FLY Airline>>>>>>>>>>"<<endl;
	string f_name, l_name, add, pass_no,phone_no;
	int choice, datedep, date, month, year;
	bool ans;
	char ch;
	time_t t= time(NULL);
	tm* timePtr=localtime(&t);
	date=(timePtr->tm_mday);
	month=(timePtr->tm_mon)+1;
	year=(timePtr->tm_year)+1900;

	back2:
	cout<<endl<<"Press 1 for Booking"
	<<endl<<"Press 2 for Routes"
	<<endl<<"Press 3 for Ticket Information"
	<<endl<<"Press 4 for Complain"
	<<endl<<"Press 0 for Exit\n";
	cin>>choice;
	system("cls");
	switch(choice)
	{
		case 1:
			{
				my:
				cout<<">>>>>>>>>>BOOKING<<<<<<<<<<<\n";
				passenger *ptr;
				cout<<"Enter Your First Name: ";
				cin>>f_name;
				cin.ignore();
				cout<<"Enter Your Last Name: ";
				getline(cin,l_name);
				cout<<"Enter Your Address(Using Commas only): ";
				getline(cin,add);
				cout<<"Enter Your Phone Num(Without -): ";
				cin>>phone_no;
				date:
				cout<<"Enter date of departure(DDMMYYYY): ";
				cin>>datedep;
				booking obj1(f_name,l_name,phone_no,add,pass_no,datedep);
				ptr = &obj1;
				back:
				cout<<endl<<"1.Local Destination\n2.International Destination\n3.Back\n4.Exit\n";
				choice = getch();
				
				if(choice==49)
				{
					
					if(ptr->LocalDestination()==false)
					{
						cout<<endl<<"We donot fly to this place\nPlease Choose again\n";
						goto back;
					}
					else
					{
						cout<<endl<<"Yes we do fly\n";
						ptr->Seats();
						ptr->Meals();
						ptr->Registration();
						system("cls");
						ans = ptr->Display();
						if(ans==false)
						{
							system("cls");
							goto back2;
						}
						else if(ans==true)
						{
							cout<<endl<<"Thanks for Flying With Us"<<endl<<endl
							<<"Would you like to avail our Pick'n Drop facility?(y/n)";
							ch = getch();
							if(ch=='y'||ch=='Y')
							ptr->Drive();
							else if(ch=='n' || ch=='N')
							{
								ofstream ofile;
								ofile.open("flight.txt", ios::app);
								ofile<<endl<<endl<<"Pick'n Drop: NO";
								ofile.close();
							}
							getch();
							system("cls");
							goto back2;
						}
					}
				}
				else if(choice==50)
				{
					cout<<endl<<"Enter Your Passport Num(Without \"-\"): ";
					cin>>pass_no;
					ans = ptr->InternationalDestination(pass_no);
					if(ans==false)
					{
						cout<<endl<<"We donot fly to this place\n";
						goto back;
					}
					else
					{
						cout<<endl<<"Yes we do fly\n";
						ptr->Seats();
					ptr->Meals();
						ptr->Registration();
						system("cls");
						ans = ptr->Display();
						if(ans==false)
						{
							system("cls");
							goto back2;
						}
						else if(ans==true)
						{
							cout<<endl<<"Thanks for Flying With Us"<<endl<<endl
							<<"Would you like to avail our Pick'n Drop facility?(y/n)";
							ch = getch();
							if(ch=='y'||ch=='Y')
								ptr->Drive();
							else if(ch=='n' || ch=='N')
							{
								ofstream ofile;
								ofile.open("flight.txt", ios::app);
								ofile<<endl<<endl<<"Pick'n Drop: NO";
								ofile.close();
							}
							getch();
							system("cls");
							goto back2;
						}
					}
				}
				else if(choice==51)
				{
					system("cls");
					goto back2;
				}
				else
					exit(0);
				break;	
			}
			
			case 2:	//choice = 2
			{
				cout<<"<<<<<<<<<<ROUTES>>>>>>>>>>\n";
					routes obj;
					ans = obj.print();
					if(ans==true)
						goto back2;
					else if(ans==false)
					{
						cout<<endl;
						system("cls");
						goto back2;
					}
					break;
			}
			case 3:	//choice = 3
				{
					cout<<">>>>>>>>>>Ticket Information<<<<<<<<<<<\n";
					Manage pass;
					chnge:
					choice= pass.change();
					if (choice==1)
					{
						sleep(2);
						system("cls");
						goto back2;
					}
					else
					{
						cout<<"No record found\n";
						goto chnge;
					}
						
					break;
				}
				case 4:{
					cout<<">>>>>>>>>>COMPLAINT<<<<<<<<<<<\n";
					cout<<"Enter Your First Name: ";
					cin>>f_name;
					cin.ignore();
					cout<<"Enter Your Last Name: ";
					getline(cin,l_name);
					cout<<"Enter Your Phone Num(Without -): ";
					cin>>phone_no;
					complain obj(f_name,l_name,phone_no);
					obj.type();
					system("cls");
					goto back2;
					break;
				}
			case 0:	//choice = 0
				{
					exit(0);
				}
				
			default:
				cout<<endl<<endl<<"ERROR!!!";
				goto back2;
	}
}
};


int main()
{
	string f_name, l_name, add, pass_no,phone_no;
	int choice, datedep, date, month, year;
	bool ans;
	char ch;
	time_t t= time(NULL);
	tm* timePtr=localtime(&t);
	date=(timePtr->tm_mday);
	month=(timePtr->tm_mon)+1;
	year=(timePtr->tm_year)+1900;

int in,in2;
backto:
	cout<<"<<<<<<<<<<NUCES Airline Flight System>>>>>>>>>>"<<endl;
	cout<<"Press 1 for Flight Detail"<<endl;
	cout<<"Press 2 for About Us"<<endl;
	cout<<"Press 3 for Login"<<endl;
	cout<<"Press 4 for Exit"<<endl;
	cin>>choice;
	cin.ignore();
	system("cls");
	switch(choice){
		case 1:{
					cout<<"<<<<<<<<<<ROUTES>>>>>>>>>>\n";
					cout<<"\n\n\n\n\tFollowing are the international flights available"<<endl;
			for(int i=0;i<5;i++)
			{
				cout<<endl;
				for(int j=0;j<5;j++)
				{
					if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<l_destination[i]<<" to "<<i_destination[j]<<endl;
					}
					
				}
			}
			cout<<"\n\n\n\n\tFollowing are the local flights available"<<endl;
			for(int i=0;i<5;i++)
			{
				cout<<endl;
				for(int j=0;j<5;j++)
				{
						if(i==j)
					{
						continue;
					}
					else
					{
						cout<<"Flight from "<<l_destination[i]<<" to "<<l_destination[j]<<endl;
					}
				}
			} 
			getch();
			goto backto;
					break;
		}
		case 2:{
		cout<<"\t\t<<<<<<<<<<ABOUT US>>>>>>>>>>\n";
					about obj;
					obj.Aboutus();
					getch();
					system("cls");
					goto backto;
					break;
		}
		case 3:{
			lo:
			cout<<"<<<<<<<<<<LOGIN>>>>>>>>>>"<<endl;
			cout<<"Press 1 for Passenger Login"<<endl;
			cout<<"Press 2 for Admin Login"<<endl;
			cin>>in;
			cin.ignore();
			system("cls");
			me:
			if(in==1){
				cout<<"<<<<<<<<<<LOGIN/SIGN-UP>>>>>>>>>>"<<endl;
				cout<<"Press 1 for Login"<<endl;
				cout<<"Press 2 for Sign-Up"<<endl;
				cin>>in2;
				cin.ignore();
				system("cls");
				if(in2==1){
					into:
					cout<<"<<<<<<<<<<LOGIN>>>>>>>>>>"<<endl;
					 string username, password;
    cout << "Enter your username: ";
    cin >> username;
    char ch;
    cout << "Enter password: ";
    while ((ch = getch()) != '\r') { // loop until user presses enter key
        if (ch == '\b') { // if backspace key is pressed
            if (!password.empty()) { // check if password string is not empty
                password[password.length() - 1] = ' '; // overwrite last character with a space
                cout << "\b \b"; // erase last character from console
            }
        } else {
            password += ch;
            cout << '*'; // display asterisk for each character entered
        }
    }
User obj1;
    if (obj1.verifyUser(username, password)) {
        cout << "\nLogin successful!" << endl;
		HomePage obj;
    } else {
        cout << "\nInvalid username or password. Please try again." << endl;
        getch();
					goto me;
	}
}
				else if(in2==2){
					cout<<"<<<<<<<<<<SIGN-UP>>>>>>>>>>"<<endl;
					User obj4;
					obj4.signUp();
					system("cls");
					goto into;
				}
				else{
					cout<<"Invalid Input "<<endl;
					system("cls");
					goto me;
				}
			}
			else if(in==2){
				cout<<"<<<<<<<<<<LOGIN>>>>>>>>>>"<<endl;
				Admin obj2;
				obj2.login();
			}
			else
			{
				cout<<"Invalid Input"<<endl;
				goto lo; 
			}
			break;
		}
		case 4:{
			exit(0);
			break;
		}
			
	}
        return 0;

}

bool datecheck(int datedep, int date, int month, int year)
{
	if((datedep%10000)>2017&&(datedep%10000)==year)
		if(((datedep/10000)%100)>0 && ((datedep/10000)%100)<13&&((datedep/10000)%100)==month)
			if((datedep/1000000)>0 && (datedep/1000000)<32&&(datedep/1000000)>date&&(datedep/1000000)<(date+20))
				return true;
	else
		return false;
}

