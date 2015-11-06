#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>

struct flights
{
char fl_no[30];
char fl_name[100];
int n_o_bs;
int n_o_es;
int n_o_fs;
float pbs;
float pes;
float pfs;
char dest[40];
char time[10];
}f;

struct dates
{
int d,m,y;
};

struct schedule
{
char fl_no[30];
dates d1;
int n_o_ba;
int n_o_ea;
int n_o_fa;
}s;

struct reserve
{
char fl_no[30];
char pass_name[80];
char pass_class[25];
long tel_no;
dates d2;
char status;
}r;

void search(char flno[],int &flag);
void del();
void title();
void display_menu();
int ct=0;
void search_sc(char flno[],dates st, int &flag2);

void intro()
{textcolor(6);
int i;
clrscr();
gotoxy(25,4);
for(i=0;i<30;i++)
cprintf("*");
gotoxy(25,5);
cprintf("*                            *");
gotoxy(25,6);
cprintf("*                            *");
textcolor(10);
gotoxy(25,7);
cprintf("*      COMPUTER SCIENCE      *");
gotoxy(25,8);
cprintf("*           PROJECT          *");
textcolor(6);
gotoxy(25,9);
cprintf("*                            *");
gotoxy(25,10);
cprintf("*                            *");
textcolor(9);
gotoxy(25,11);
cprintf("*     AIRLINE RESERVATION    *");
gotoxy(25,12);
cprintf("*           SYSTEM           *");
textcolor(6);

gotoxy(25,13);
cprintf("*                            *");
gotoxy(25,14);
cprintf("*        PRESENTED BY :-     *");
gotoxy(25,15);
cprintf("*                            *");
textcolor(12);
gotoxy(25,16);
cprintf("*     RONNY GEORGE MATHEW    *");
textcolor(15);
gotoxy(25,17);
cprintf("*        CLASS:XII-A         *");
textcolor(6);
gotoxy(25,18);
cprintf("*                            *");
gotoxy(25,19);
cprintf("*                            *");
gotoxy(25,20);
for(i=0;i<30;i++)
cprintf("*");

}

void border()
{
clrscr();
textcolor(15);
gotoxy(20,5);
for (int i=0;i<18;i++)
{cprintf("*");
gotoxy(20,5+i);
}
for (int j=18;j>0;j--)
{cprintf("*");
gotoxy(62,4+j);
}
gotoxy(20,5);
for (int k=0;k<22;k++)
{cprintf("* ");
}
gotoxy(20,23);
for (int m=22;m>0;m--)
{cprintf("* ");
}
}

void add_flight()
{

char fno[30];
int flag;
ofstream outfile1,outfile2;
char ch1,ch2;
do
{textcolor(13);
clrscr();
title();
flag=0;
textcolor(13);
gotoxy(1,5);
cprintf("\n\n Enter the flight number                             ");
gets(fno);
strupr(fno);
search(fno,flag);
if (flag==0)
{textcolor(13);
strcpy(f.fl_no,fno);
cprintf("\n Enter the flight name                               ");
gets(f.fl_name);
strupr(f.fl_name);
cprintf("\n Enter the destination                               ");
gets(f.dest);
strupr(f.dest);
cprintf("\n Enter the number of first class seats               ");
cin>>f.n_o_fs;
cprintf("\n Enter the number of business class seats            ");
cin>>f.n_o_bs;
cprintf("\n Enter the number of economy class seats             ");
cin>>f.n_o_es;
cprintf("\n Enter the price of first class seats ($)            ");
cin>>f.pfs;
cprintf("\n Enter the price of business class seats ($)         ");
cin>>f.pbs;
cprintf("\n Enter the price of economy class seats ($)          ");
cin>>f.pes;
cprintf("\n Enter the time of departure (hrs:min)               ");
cin>>f.time;
outfile1.open("flight.dat",ios::binary|ios::app);
outfile1.write((char*)&f,sizeof(f));
outfile1.close();
do
{textcolor(13);
int flag2=0;
strcpy(s.fl_no,f.fl_no);
s.n_o_ba=f.n_o_bs;
s.n_o_fa=f.n_o_fs;
s.n_o_ea=f.n_o_es;
cprintf("\n Enter the date (dd mm yyyy)                         ");
cin>>s.d1.d>>s.d1.m>>s.d1.y;
search_sc(fno,s.d1,flag2);
if(flag2==0)
{
outfile2.open("schedule.dat",ios::binary|ios::app);
outfile2.write((char*)&s,sizeof(s));
outfile2.close();
}
else
{textcolor(10);
cprintf("\n You have already added a schedule for this date");
cprintf("\n Do you want to add another schedule(y/n)            ");
cin>>ch1;}
}
while((ch1=='y')||(ch1=='Y'));
}
else
{textcolor(10);
cprintf("\n This flight already exists                          ");
getch();
cprintf("\n\n Do you want to add another flight detail(y/n)       ");
cin>>ch2;}
}
while((ch2=='y')||(ch2=='Y'));
}

void add_schedule()
{

char fno[25],ch;
int flag=0;
clrscr();
title();
textcolor(13);
ofstream outfile;
gotoxy(1,5);
cprintf("\n\n Enter the flight number                  ");
gets(fno);
strupr(fno);
search(fno,flag);
if (flag==1)
{
do
{
int flag2=0;
strcpy(s.fl_no,fno);
s.n_o_ba=f.n_o_bs;
s.n_o_fa=f.n_o_fs;
s.n_o_ea=f.n_o_es;
cprintf("\n Enter the date (dd mm yyyy)                ");
cin>>s.d1.d>>s.d1.m>>s.d1.y;
search_sc(fno,s.d1,flag2);
if(flag2==0)
{
outfile.open("schedule.dat",ios::binary|ios::app);
outfile.write((char*)&s,sizeof(s));
outfile.close();
}
else
cprintf("\n You have already added a schedule for this date");
cprintf("\n Do you want to add another schedule(y/n) ");
cin>>ch;
}
while((ch=='y')||(ch=='Y'));
}
else
{textcolor(10);
cprintf("\n Such a flight does not exists");
getch();
}
}

void search(char flno[],int &flag)
{
ifstream infile;
infile.open("flight.dat",ios::binary);
if(!infile)
flag=0;
else
{
infile.read((char*)&f,sizeof(f));
while(!infile.eof())
{if (strcmp(f.fl_no,flno)==0)
{flag=1;
break;}
infile.read((char*)&f,sizeof(f));
}
}
infile.close();
}

void search_sc(char flno[],dates st, int &flag2)
{
schedule sc;
ifstream infile;
infile.open("schedule.dat",ios::binary);
if(!infile)
flag2=0;
else
{
infile.read((char*)&sc,sizeof(sc));
while(!infile.eof())
{if ((strcmp(sc.fl_no,flno)==0)&&(sc.d1.d==st.d)&&(sc.d1.m==st.m)&&(sc.d1.y==st.y))
{flag2=1;
break;}
infile.read((char*)&sc,sizeof(sc));
}
}
infile.close();
}

void display()
{int x;
clrscr();
ifstream infile1,infile2;
infile1.open("flight.dat",ios::binary);

infile1.read((char*)&f,sizeof(f));
textcolor(11);
gotoxy(1,2);
cprintf("Flight");
gotoxy(3,3);
cprintf("No");
gotoxy(14,2);
cprintf("Flight");
gotoxy(15,3);
cprintf("Name");
gotoxy(27,2);
cprintf("Time");
gotoxy(32,2);
cprintf("Destination");
gotoxy(45,2);
cprintf("Price of");
gotoxy(44,3);
cprintf("FC");
gotoxy(48,3);
cprintf("BC");
gotoxy(52,3);
cprintf("EC");
gotoxy(56,2);
cprintf("Scheduled");
gotoxy(58,3);
cprintf("for");
gotoxy(66,2);
cprintf("Seats available");
gotoxy(68,3);
cprintf("FC");
gotoxy(73,3);
cprintf("BC");
gotoxy(78,3);
cprintf("EC");
int row=5;
while(!infile1.eof())
{
gotoxy(1,row);
cout<<f.fl_no;
gotoxy(9,row);
cout<<f.fl_name;
gotoxy(27,row);
cout<<f.time;
gotoxy(33,row);
cout<<f.dest;
gotoxy(44,row);
cout<<f.pfs;
gotoxy(48,row);
cout<<f.pbs;
gotoxy(52,row);
cout<<f.pes;
infile2.open("schedule.dat",ios::binary);
infile2.read((char*)&s,sizeof(s));
while (!infile2.eof())
{
if (strcmp(s.fl_no,f.fl_no)==0)
{
gotoxy(56,row);
cout<<s.d1.d<<"/"<<s.d1.m<<"/"<<s.d1.y;
gotoxy(68,row);
cout<<s.n_o_fa;
gotoxy(73,row);
cout<<s.n_o_ba;
gotoxy(78,row);
cout<<s.n_o_ea;
row++;
if (row==23)
{
getch();
clrscr();
textcolor(11);
gotoxy(1,2);
cprintf("Flight");
gotoxy(3,3);
cprintf("No");
gotoxy(14,2);
cprintf("Flight");
gotoxy(15,3);
cprintf("Name");
gotoxy(27,2);
cprintf("Time");
gotoxy(32,2);
cprintf("Destination");
gotoxy(45,2);
cprintf("Price of");
gotoxy(44,3);
cprintf("FC");
gotoxy(48,3);
cprintf("BC");
gotoxy(52,3);
cprintf("EC");
gotoxy(56,2);
cprintf("Scheduled");
gotoxy(58,3);
cprintf("for");
gotoxy(66,2);
cprintf("Seats available");
gotoxy(68,3);
cprintf("FC");
gotoxy(73,3);
cprintf("BC");
gotoxy(78,3);
cprintf("EC");
row=4;
}
}
infile2.read((char*)&s,sizeof(s));
}
infile2.close();
row+=2;
if(row==23)
{
getch();
clrscr();
textcolor(11);
gotoxy(1,2);
cprintf("Flight");
gotoxy(3,3);
cprintf("No");
gotoxy(14,2);
cprintf("Flight");
gotoxy(15,3);
cprintf("Name");
gotoxy(27,2);
cprintf("Time");
gotoxy(32,2);
cprintf("Destination");
gotoxy(45,2);
cprintf("Price of");
gotoxy(44,3);
cprintf("FC");
gotoxy(48,3);
cprintf("BC");
gotoxy(52,3);
cprintf("EC");
gotoxy(56,2);
cprintf("Scheduled");
gotoxy(58,3);
cprintf("for");
gotoxy(66,2);
cprintf("Seats available");
gotoxy(68,3);
cprintf("FC");
gotoxy(73,3);
cprintf("BC");
gotoxy(78,3);
cprintf("EC");
 row=4;
}
infile1.read((char*)&f,sizeof(f));
}
getch();
}
int flight_display(char dest[],dates d)
{
int flag=0;
int x;
clrscr();
ifstream infile1,infile2;
infile1.open("flight.dat",ios::binary);
infile1.read((char*)&f,sizeof(f));
textcolor(11);
gotoxy(1,2);
cprintf("Flight");
gotoxy(3,3);
cprintf("No");
gotoxy(14,2);
cprintf("Flight");
gotoxy(15,3);
cprintf("Name");
gotoxy(27,2);
cprintf("Time");
gotoxy(32,2);
cprintf("Destination");
gotoxy(45,2);
cprintf("Price of");
gotoxy(44,3);
cprintf("FC");
gotoxy(48,3);
cprintf("BC");
gotoxy(52,3);
cprintf("EC");
gotoxy(56,2);
cprintf("Scheduled");
gotoxy(58,3);
cprintf("for");
gotoxy(66,2);
cprintf("Seats available");
gotoxy(68,3);
cprintf("FC");
gotoxy(73,3);
cprintf("BC");
gotoxy(78,3);
cprintf("EC");
int row=5;
while(!infile1.eof())
{
if(strcmp(f.dest,dest)==0)
{
infile2.open("schedule.dat",ios::binary);
infile2.read((char*)&s,sizeof(s));
while (!infile2.eof())
{
if (strcmp(s.fl_no,f.fl_no)==0)
{
if ((s.d1.d==d.d)&&(s.d1.m==d.m)&&(s.d1.y==d.y))
{
flag=1;
gotoxy(1,row);
cout<<f.fl_no;
gotoxy(8,row);
cout<<f.fl_name;
gotoxy(23,row);
cout<<f.time;
gotoxy(30,row);
cout<<f.dest;
gotoxy(42,row);
cout<<f.pfs;
gotoxy(46,row);
cout<<f.pbs;
gotoxy(50,row);
cout<<f.pes;
gotoxy(55,row);
cout<<s.d1.d<<"/"<<s.d1.m<<"/"<<s.d1.y;
gotoxy(67,row);
cout<<s.n_o_fa;
gotoxy(72,row);
cout<<s.n_o_ba;
gotoxy(77,row);
cout<<s.n_o_ea;
row++;
ct++;
}
}
infile2.read((char*)&s,sizeof(s));
}
infile2.close();
row+=2;
}
infile1.read((char*)&f,sizeof(f));
}
return(flag);
}

void search_flight(char fno[])
{
int x;
int flag=0;
clrscr();
ifstream infile1,infile2;
infile1.open("flight.dat",ios::binary);
infile1.read((char*)&f,sizeof(f));
gotoxy(2,2);
cout<<"Flight";
gotoxy(2,3);
cout<<"No";
gotoxy(10,2);
cout<<"Flight";
gotoxy(10,3);
cout<<"Name";
gotoxy(24,2);
cout<<"Destination";
gotoxy(39,2);
cout<<"Price of";
gotoxy(38,3);
cout<<"FC";
gotoxy(42,3);
cout<<"BC";
gotoxy(46,3);
cout<<"EC";
gotoxy(51,2);
cout<<"Scheduled";
gotoxy(51,3);
cout<<"for";
gotoxy(62,2);
cout<<"Seats available";
gotoxy(64,3);
cout<<"FC";
gotoxy(69,3);
cout<<"BC";
gotoxy(74,3);
cout<<"EC";
int row=4;
while(!infile1.eof())
{
if(strcmp(f.fl_no,fno)==0)
{
flag=1;
gotoxy(2,row);
cout<<f.fl_no;
gotoxy(10,row);
cout<<f.fl_name;
gotoxy(24,row);
cout<<f.dest;
gotoxy(38,row);
cout<<f.pfs;
gotoxy(42,row);
cout<<f.pbs;
gotoxy(46,row);
cout<<f.pes;
infile2.open("schedule.dat",ios::binary);
infile2.read((char*)&s,sizeof(s));
while (!infile2.eof())
{
if (strcmp(s.fl_no,f.fl_no)==0)
{
gotoxy(51,row);
cout<<s.d1.d<<"/"<<s.d1.m<<"/"<<s.d1.y;
gotoxy(64,row);
cout<<s.n_o_fa;
gotoxy(69,row);
cout<<s.n_o_ba;
gotoxy(74,row);
cout<<s.n_o_ea;
row++;
}
infile2.read((char*)&s,sizeof(s));
}
infile2.close();
row+=2;
}
infile1.read((char*)&f,sizeof(f));
}



if(flag==0)
{clrscr();
cout<<"\nThis flight does not exist";
getch();}
else
getch();
}


void check(char fno[],dates d,char cl[],int seats,int &flag,int &ns)
{
int p;
char ch;
fstream infile;
infile.open("schedule.dat",ios::binary|ios::in|ios::out);
infile.read((char*)&s,sizeof(s));
while(!infile.eof())
{
if((strcmp(s.fl_no,fno)==0)&&(s.d1.d==d.d)&&(s.d1.m==d.m)&&(s.d1.y==d.y))
{
if (strcmp(cl,"FIRST")==0)
{
if (s.n_o_fa==0)
{
cout<<"\nSeats not available";
getch();
flag=0;
}
else
if (s.n_o_fa-seats>=0)
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
s.n_o_fa=s.n_o_fa-seats;
cout<<"\nBooking confirmed";
getch();
infile.write((char*)&s,sizeof(s));
flag=1;
}
else
{
cout<<"\nSeats not available for all passengers";
cout<<"\nDo you wish to continue booking? (y/n)";
cin>>ch;
if ((ch=='y')||(ch=='Y'))
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
ns=s.n_o_fa;
s.n_o_fa=0;
infile.write((char*)&s,sizeof(s));
flag=2;
}
else
flag=3;
}
}
if (strcmp(cl,"BUSINESS")==0)
{
if (s.n_o_ba==0)
{
cout<<"\nSeats not available";
flag=0;
}
else
if (s.n_o_ba-seats>=0)
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
s.n_o_ba=s.n_o_ba-seats;
cout<<"\nBooking confirmed";
getch();
infile.write((char*)&s,sizeof(s));
flag=1;
}
else
{
cout<<"\nSeats not available for all passengers";
cout<<"\nDo you wish to continue booking? (y/n)";
cin>>ch;
if ((ch=='y')||(ch=='Y'))
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
ns=s.n_o_ba;
s.n_o_ba=0;
infile.write((char*)&s,sizeof(s));
flag=2;
}
else
flag=3;
}
}
if (strcmp(cl,"ECONOMY")==0)
{
if (s.n_o_ea==0)
{
cout<<"\nSeats not available";
getch();
flag=0;
}
else
if (s.n_o_ea-seats>=0)
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
s.n_o_ea=s.n_o_ea-seats;
cout<<"\nBooking confirmed";
getch();
infile.write((char*)&s,sizeof(s));
flag=1;
}
else
{
cout<<"\nSeats not available for all passengers";
cout<<"\n\nDo you wish to continue booking? (y/n)";
cin>>ch;
if ((ch=='y')||(ch=='Y'))
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
ns=s.n_o_ea;
s.n_o_ea=0;
infile.write((char*)&s,sizeof(s));
flag=2;
}
else
flag=3;
}
}
}
infile.read((char*)&s,sizeof(s));
}
infile.close();
}

void booking()
{
clrscr();
title();
int f,seats=0,flag=0,ns=0,d,m,y,fl=0;
char dest[40],fl_no[30],pass_class[25],ans1='n',ans2,ans3;
dates d3;
ofstream outfile;
outfile.open("reserve.dat",ios::binary|ios::app);
cout<<"\n\nEnter the destination                ";
cin>>dest;
strupr(dest);
do
{
	cout<<"\nEnter date of travel (dd mm yyyy)    ";
	cin>>d3.d>>d3.m>>d3.y;
	ct=0;
	f=flight_display(dest,d3);

	if (f==1)
	{
		do
		{  getch();
       begin:   clrscr();
		if(ans1=='y')
		f=flight_display(dest,d3);
		cout<<"\n\nEnter the flight number            ";
		cin>>fl_no;
		strupr(fl_no);
		search(fl_no,fl);
		if (fl==0)
		goto end;

		cout<<"\nEnter the class you want to travel ";
		cin>>pass_class;
		strupr(pass_class);
		cout<<"\nEnter the number of seats          ";
		cin>>seats;
		check(fl_no,d3,pass_class,seats,flag,ns);
		if (flag==1)
		{
			for (int i=1;i<=seats;i++)
			{cout<<"\n\nEnter the passenger name           ";
			cin>>r.pass_name;
			strupr(r.pass_name);
			cout<<"\nEnter the telephone number         ";
			cin>>r.tel_no;
			strcpy(r.fl_no,fl_no);
			strcpy(r.pass_class,pass_class);
			r.d2.d=d3.d;
			r.d2.m=d3.m;
			r.d2.y=d3.y;
			r.status='C';
			outfile.write((char*)&r,sizeof(r));
			}
			ans1='n';
		}
		else
		if (flag==2)
		{
			for (int i=1;i<=ns;i++)
			{
			cout<<"\n\nEnter the passenger name            ";
			cin>>r.pass_name;
			strupr(r.pass_name);
			cout<<"\nEnter the telephone number         ";
			cin>>r.tel_no;
			strcpy(r.fl_no,fl_no);
			strcpy(r.pass_class,pass_class);
			r.d2.d=d3.d;
			r.d2.m=d3.m;
			r.d2.y=d3.y;
			r.status='C';
			outfile.write((char*)&r,sizeof(r));
			}
			for (int i=1;i<=seats-ns;i++)
			{
			cout<<"\n\nEnter the passenger name           ";
			cin>>r.pass_name;
			strupr(r.pass_name);
			cout<<"\nEnter the telephone number         ";
			cin>>r.tel_no;
			strcpy(r.fl_no,fl_no);
			strcpy(r.pass_class,pass_class);
			r.d2.d=d3.d;
			r.d2.m=d3.m;
			r.d2.y=d3.y;
			r.status='W';
			outfile.write((char*)&r,sizeof(r));
			}
			ans1='n';
		}
		else
		if(flag==3)
		ans1=' ';
		else
		{
		ans1='n';
		if(ct>1)
		{
		cout<<"\nDo you wish to fly by another flight? (y/n) ";
		cin>>ans1;
		}
		if ((ans1=='n')||(ans1=='N'))
		{cout<<"\nDo you want to stay on waiting list? (y/n) ";
		cin>>ans2;
		if ((ans2=='Y')||(ans2=='y'))
		{
		for (int i=1;i<=seats;i++)
		{
		cout<<"\n\nEnter the passenger name           ";
		cin>>r.pass_name;
		strupr(r.pass_name);
		cout<<"\nEnter the telephone number         ";
		cin>>r.tel_no;
		strcpy(r.fl_no,fl_no);
		strcpy(r.pass_class,pass_class);
		r.d2.d=d3.d;
		r.d2.m=d3.m;
		r.d2.y=d3.y;
		r.status='W';
		outfile.write((char*)&r,sizeof(r));
		}
		}
		}
		}
		}
		while ((ans1=='y')||(ans1=='Y'));
		ans3='n';
	}
	else
	{
	clrscr();
	cout<<"\nThere is no flight for this destination on this date ";
	cout<<"\n\nDo you wish to change date? (y/n) ";
	cin>>ans3;
	}
}
while ((ans3=='y')||(ans3=='Y'));
if(ans3=='N'||ans3=='n')
goto bottom;

end:
if(fl==0)
{
cout<<"\nInvalid Flight Number";
getch();
goto begin;
}
bottom:
}

void modi_seats(char fl_no[],dates d4,char cl[],int ct)
{int p;
fstream infile;
infile.open("schedule.dat",ios::binary|ios::in|ios::out);
infile.read((char*)&s,sizeof(s));
while(!infile.eof())
{
if
((strcmp(fl_no,s.fl_no)==0)&&(d4.d==s.d1.d)&&(d4.m==s.d1.m)&&(d4.y==s.d1.y))
{
p=infile.tellg();
infile.seekg(p-sizeof(s));
if (strcmp (cl,"FIRST")==0)
{
s.n_o_fa +=ct;
infile.write((char*)&s,sizeof(s));
}
else
if (strcmp (cl,"BUSINESS")==0)
{s.n_o_ba +=ct;
infile.write((char*)&s,sizeof(s));
}
else
{s.n_o_ea +=ct;
infile.write((char*)&s,sizeof(s));
}
}
infile.read((char*)&s,sizeof(s));
}
}

void cancel()
{
clrscr();
title();
int ct=0,p,found=0,flag=0;
char fl_no[30],name[80],cl[25],ans;
dates d5;
fstream infile;
infile.open("reserve.dat",ios::binary|ios::out|ios::in);
cout<<"\n\nEnter the flight number                  ";
cin>>fl_no;
strupr(fl_no);
search(fl_no,flag);
if (flag==1)
{
cout<<"\nEnter the date of travel(dd mm yyyy)     ";
cin>>d5.d>>d5.m>>d5.y;
do
{
cout<<"\nEnter the passenger name                 ";
cin>>name;
strupr(name);
found=0;
infile.seekg(0);
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
if
((strcmp(fl_no,r.fl_no)==0)&&(d5.d==r.d2.d)&&(d5.m==r.d2.m)&&(d5.y==r.d2.y)&&(strcmp(name,r.pass_name)==0))
{
p=infile.tellg();
infile.seekg(p-sizeof(r));
if(r.status=='C')
{
strcpy(cl,r.pass_class);
ct++;
found=1;
}
r.status='X';
infile.write((char*)&r,sizeof(r));
break;
}
infile.read((char*)&r,sizeof(r));
}
infile.close();
if(found==1)
{
infile.open("reserve.dat",ios::binary|ios::out|ios::in);

infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
if
((strcmp(fl_no,r.fl_no)==0)&&(d5.d==r.d2.d)&&(d5.m==r.d2.m)&&(d5.y==r.d2.y)&&(strcmp(r.pass_class,cl)==0)&&(r.status=='W'))
{
p=infile.tellg();
infile.seekg(p-sizeof(r));
r.status='C';
ct--;
infile.write((char*)&r,sizeof(r));
break;
}
infile.read((char*)&r,sizeof(r));
}
}
cout<<"\nAny more passengers to be canceled? (y/n) ";
cin>>ans;
}
while((ans=='y')||(ans=='Y'));
infile.close();
modi_seats(fl_no,d5,cl,ct);
del();
}
else
{
cout<<"\nInvalid Flight Number";
getch();
}
}

void del()
{
clrscr();
title();
int rmn;

ifstream infile("reserve.dat",ios::binary);
ofstream outfile("temp.dat",ios::binary);
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
if(r.status!='X')
outfile.write((char*)&r,sizeof(r));
infile.read((char*)&r,sizeof(r));
}

infile.close();
outfile.close();
infile.open("temp.dat",ios::binary);
outfile.open("reserve.dat",ios::binary);
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
outfile.write((char*)&r,sizeof(r));
infile.read((char*)&r,sizeof(r));
}
}


void display_chart()
{char fl_no[30];
dates d6;
ifstream infile;
int flag=0;
clrscr();
title();
infile.open("reserve.dat",ios::binary);
cout<<"\n\nEnter the flight number              ";
cin>>fl_no;
strupr(fl_no);
cout<<"\nEnter the date of travel(dd mm yyyy) ";
cin>>d6.d>>d6.m>>d6.y;
cout<<"\n\tPassenger Name\tTelephone number"
<<"\tClass"<<"\tStatus";
infile.read((char*)&r,sizeof(r));
while(!infile.eof())
{
if((strcmp(fl_no,r.fl_no)==0)&&(d6.d==r.d2.d)&&(d6.m==r.d2.m)&&(d6.y==r.d2.y))
{
flag=1;
cout<<"\n\t"<<r.pass_name;
cout<<"\t\t"<<r.tel_no;
cout<<"\t\t\t"<<r.pass_class;
cout<<"\t"<<r.status;
}
infile.read((char*)&r,sizeof(r));
}
if(flag==0)
{
clrscr();
cout<<"\n\n\t\tNo passengers on this flight";
getch();}
else
getch();
}

void modify()
{
clrscr();
title();
int flag=0,choice,p;
char fl_no[30];
float price;
dates d7,d8;
fstream infile;
infile.open("flight.dat",ios::binary|ios::in|ios::out);
cout<<"\n\nEnter the flight number                               ";
gets(fl_no);
strupr(fl_no);
infile.read((char*)&f,sizeof(f));
while(!infile.eof())
{
if (strcmp(fl_no,f.fl_no)==0)
{
flag=1;
do
{         clrscr();
	  cout<<"\n\n\n\t\t\t\tModify Menu";
	  cout<<"\n\t\t\t\t------ ----";
	  cout<<"\n\n\t\t\t1.Price of economy class";
	  cout<<"\n\t\t\t2.Price of business class";
	  cout<<"\n\t\t\t3.Price of first class";
	  cout<<"\n\t\t\t4.Reschedule flight";
	  cout<<"\n\t\t\t5.Return to Main Menu";
	  cout<<"\n\n\n\t\t\tEnter your choice ";
	  cin>>choice;
	  switch(choice)
	  {
	  case 1:{
	      cout<<"\n\tEnter the new price ";
		    cin>>price;
		    p=infile.tellg();
		    infile.seekg(p-sizeof(f));
		    f.pes=price;
		    infile.write((char*)&f,sizeof(f));
		    break;
		    }

	  case 2:{
	      cout<<"\n\tEnter the new price ";
		    cin>>price;
		    p=infile.tellg();
		    infile.seekg(p-sizeof(f));
		    f.pbs=price;
		    infile.write((char*)&f,sizeof(f));
		    break;
		    }

	  case 3:{
	      cout<<"\n\tEnter the new price ";
		    cin>>price;
	      p=infile.tellg();
		    infile.seekg(p-sizeof(f));
		    f.pfs=price;
		    infile.write((char*)&f,sizeof(f));
		    break;
		    }

	  case 4:{
		 cout<<"\nEnter the date to be rescheduled(dd mm yyyy)";
		 cin>>d7.d>>d7.m>>d7.y;
		 cout<<"\nEnter the new date(dd mm yyyy) ";

	      cin>>d8.d>>d8.m>>d8.y;
		    fstream infile1;
		 infile1.open("schedule.dat",ios::binary|ios::in|ios::out);
		    infile1.read((char*)&s,sizeof(s));
		    while (!infile1.eof())
		    {
		    if((strcmp(s.fl_no,fl_no)==0)&& (d7.d==s.d1.d)
		    &&(d7.m==s.d1.m)&&(d7.y==s.d1.y))
		    {
	      p=infile1.tellg();
		    infile1.seekg(p-sizeof(s));
		    s.d1.d=d8.d;
		    s.d1.m=d8.m;
		    s.d1.y=d8.y;
		    infile1.write((char*)&s,sizeof(s));
		 }
		    infile1.read((char*)&s,sizeof(s));
		    }
		    }
	  case 5:break;
	  default:{
	       cout<<"\n\t\t\tInvalid Choice";
			getch();
	       }
}
}while(choice!=5);
}
infile.read((char*)&f,sizeof(f));
}
if(flag==0)
{
cout<<"\nSuch a flight number does not exists";
getch();
}
}

void title()
{gotoxy(27,2);
textcolor(5);
cprintf("INTERCONTINENTAL TRAVELS");
gotoxy(26,4);
textcolor(12);
cprintf("AIRLINE RESERVATION SYSTEM");
}
void display_menu()
{int ch=0;
char fno[30];
clrscr();
title();
dispmenu:cout<<"\n\n\n\t\t\t\tDisplay Menu";
cout<<"\n\t\t\t\t------- ----";
cout<<"\n\n\t\t\t1.All Flight Details ";
cout<<"\n\t\t\t2.Particular Flight Detail";
cout<<"\n\t\t\t3.Return to Main Menu";
cout<<"\n\n\t\t\tEnter your choice ";
cin>>ch;
switch(ch)
{case 1:{
	clrscr();
	display();
	break;
	}
case 2:{
	clrscr();
	cout<<"\nEnter the flight number ";
	cin>>fno;
	strupr(fno);
	search_flight(fno);
	break;
	}
case 3:break;

default:{
	cout<<"\n\t\t\tInvalid choice";
	getch();
        clrscr();
        goto dispmenu;
	}
	}
	}


void main()
{
intro();
getch();
int choice=0;
menu:clrscr();
border();
textcolor(12);
gotoxy(28,2);
cprintf("AIRLINE RESERVATION SYSTEM");
gotoxy(35,3);
cprintf("------------");
gotoxy(39,7);
cprintf("Menu");
gotoxy(39,8);
cprintf("----");
gotoxy(25,10);
textcolor(14);
cprintf("1. Add flight details");
gotoxy(25,11);
cprintf("2. Add flight schedules");
gotoxy(25,12);
cprintf("3. Display flight details");
gotoxy(25,13);
cprintf("4. Modify flight details");
gotoxy(25,14);
cprintf("5. Booking of seats");
gotoxy(25,15);
cprintf("6. Cancelation of seats");
gotoxy(25,16);
cprintf("7. Display reservation chart");
gotoxy(25,17);
cprintf("8. Instructions For This program");
gotoxy(25,18);
cprintf("9. Exit");
gotoxy(25,20);
cprintf("Enter your choice ");
gotoxy(50,20);
cin>>choice;
switch(choice)
     {case 1:{
              add_flight();
     	      break;
             }
      case 2:{
	      add_schedule();
	      break;
	     }
      case 3:{
	      display_menu();
              break;
              }
      case 4:{
	      modify();
	      break;
	     }
      case 5:{
              booking();
	      break;
	     }
      case 6:{
              cancel();
	      break;
	     }
      case 7:{
              display_chart();
	      break;
	     }
      case 8:{clrscr();
             gotoxy(30,8);
             textcolor(5);
             cprintf("iNsTrUcTiOnS");
             gotoxy(8,11);
             textcolor(10);
             cprintf("1. This Program is Available In Both DOS and WIN32 versions");
             gotoxy(8,12);
             cprintf("2. Both Uppercase and Lowercase characters can be used");
             gotoxy(8,13);
             cprintf("3. DO NOT use space (IN DOS VERSION)");
             getche();
      }
      case 9:exit(0);

      default:{
               textcolor(10+128);
	       gotoxy(35,21);
	       cprintf("Invalid choice");
               getch();
               textcolor(11);
	       }
     }
goto menu;
}





