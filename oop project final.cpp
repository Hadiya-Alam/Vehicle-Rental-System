#include<iostream>
#include<fstream>
#include"string"
using namespace std;
class Error
{
private:
string message;
public:
Error(string s)
{
this->message=s;
}
string display_error()
{
return message;
}
};
class vehicle
{
  string vehicleModel;
  int rentedDays;
  static int TotalNumberofVehiclesRented;
public:
  virtual int CalculateRentalCost()=0;
  virtual int getrentalrate()=0;
  vehicle()
  {
     vehicleModel="invalid";
     rentedDays=0;
  }
  vehicle(string model,int days)
  {
    vehicleModel=model;
    rentedDays=days;
    TotalNumberofVehiclesRented++;
  }
string getvehiclemodel()
  {
   return vehicleModel;
  }
int getrenteddays()
  {
    return rentedDays;
  }
void returnVehicle()
{
  rentedDays=0;
}
static int getTotalRentedVehicles()
{ 
  cout<<"Total Vehicles Rented : ";
 return TotalNumberofVehiclesRented;
}
 void setTotalVehiclesRented(int i)
{
  TotalNumberofVehiclesRented=i;
}
};
int vehicle::TotalNumberofVehiclesRented=0;
class car:public vehicle
{
int rentalRate;
public:
car()
{
rentalRate=0;
}
car(string m,int d,int r):vehicle(m,d)
{
rentalRate=r;
}
int getrentalrate()override 
{
return rentalRate;
}
int CalculateRentalCost()override
{
return getrenteddays()*rentalRate;
}
};
class truck:public vehicle
{
int rentalrate;
public:
truck()
{
rentalrate=0;
}
truck(string m,int d,int r):vehicle(m,d)
{
rentalrate=r;
}
int getrentalrate()override
{
return rentalrate;
}
int CalculateRentalCost()override
{
return getrenteddays()*rentalrate;
}
}; 
class bike:public vehicle
{
int Rentalrate;
public:
bike()
{
Rentalrate=0;
}
bike(string m,int d,int r):vehicle(m,d)
{
Rentalrate=r;
}
int getrentalrate()override
{
return Rentalrate;
}
int CalculateRentalCost()override
{
return getrenteddays()*Rentalrate;
}
}; 
class customer
{
string name;
vehicle&v1;
public:
customer(string n,vehicle&v):name(n),v1(v){}
void display()
{
cout << "Customer name: "<<name<< endl;
cout << "Vehicle Model: "<<v1.getvehiclemodel()<< endl;
cout << "Rental Days: "<<v1.getrenteddays() << endl;
cout << "Rental Rate per day: "<<v1.getrentalrate() << endl;
cout << "Total cost: "<<v1.CalculateRentalCost()<<endl;
saveToFile();
cout << "--------------------------------------" << endl;
}
void saveToFile()
{
ofstream file("/storage/emulated/0/Download/rent.txt",ios::app);
if(!file.is_open())
cout << "file not created" << endl;
file << "Customer Name: " << name << "\n";
file << "Vehicle Model: " << v1.getvehiclemodel() << "\n";
file << "Rental Days: " << v1.getrenteddays() << "\n";
file << "Rental Rate per day: " << v1.getrentalrate() << "\n";
file << "Total Cost: " << v1.CalculateRentalCost() << "\n";
file << "-------------------------------\n";
file.close();
cout<<"data added to file successfully"<< endl;
}
};
void readfromfile()
{
string line;
ifstream f1;
f1.open("/storage/emulated/0/Download/rent.txt",ios::in);
while(getline(f1,line)) 
{
cout <<line<< endl;
}
f1.close();
}
void deleteCustomerRecord(string customerName)
{
ifstream file("/storage/emulated/0/Download/rent.txt",ios::in);
ofstream tempFile("/storage/emulated/0/Download/temp.txt");
string line;
bool found = false;
if(file.is_open() && tempFile.is_open())
{
while(getline(file, line))
{
if(line.find("Customer Name: " + customerName) != string::npos)
{
found=true;
for(int i = 0; i < 5; i++)
getline(file, line);
}
else
{
tempFile << line << "\n";
}
}
file.close();
tempFile.close();
// Replace the old file with the updated file
remove("/storage/emulated/0/Download/rent.txt");
rename("/storage/emulated/0/Download/temp.txt", "/storage/emulated/0/Download/rent.txt");
if(found)
cout << "Customer " << customerName << " deleted successfully.\n";
else
cout << "Customer " << customerName << " not found.\n";
}
else
{
cout << "Error: Unable to open the file.\n";
}
}

void rentvehicle()
{
int choice,r,d;
string m,n;
cout << "\nSelect Vehicle for Rent : " << endl;
cout << "1.Car" << endl;
cout << "2.Bike" << endl;
cout << "3.Truck" << endl;
while(true)
{
try
{
cout<<"enter choice:";
cin>>choice;
if(choice<=0 || choice>3)
throw Error("Invalid choice selected\n       valid choices(1-3):");
break;
}
catch(Error r)
{
cout << "Error: "<<r.display_error()<< endl;
}
}
cout << "Enter model name:";
cin>>m;
cout<<endl;
while(true)
{
try
{
cout << "Enter rental days:";
cin>>r;
if(r<=0)
throw Error("Rental days cannot be 0 or less than 0");
break;
}
catch(Error r)
{
cout << "Error:" <<r.display_error()<< endl;
}
}
cout<<endl;
while(true)
{
try
{
cout<<"Enter rental rate per day:";
cin>>d;
if(d<=0)
throw Error("Rental rate cannot be less than 0");
break;
}
catch(Error r)
{
cout << "Error: "<<r.display_error()<< endl;
}
}
cout<<endl;
cout<<"Enter customer name:";
cin>>n;
cout<<endl;
if(choice==1)
{
car Car(m,r,d);
customer c1(n,Car);
c1.display();
}
else if(choice==2)
{
bike Bike(m,r,d);
customer c1(n,Bike);
c1.display();
}
else if(choice==3)
{
truck Truck(m,r,d);
customer c1(n,Truck);
c1.display();
}
else
{
cout << "invalid choice" << endl;
}
}

int main()
{
char m,n;
string c;
char more='y';
do
{
rentvehicle();
cout << "Do you want to rent more vehicles(y/n): " << endl;
cin>>more;
}
while(more=='y'||more=='Y');
cout<<vehicle::getTotalRentedVehicles()<<endl;
cout<<"Do you want to see all vehicles rented(y/n):";
cin>>m;
if(m=='y'||m=='Y')
readfromfile();
do
{
cout << "Do you want to delete any record(y/n):" << endl;
cin>>n;
if(n=='y'||n=='Y')
cout << "Enter customer name : ";
cin>>c;
deleteCustomerRecord(c);
}while(n=='y'||n=='Y');
return 0;
}
    