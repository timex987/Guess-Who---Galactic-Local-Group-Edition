#pragma once


#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;



//   Number:					Galaxy Number
//
//   Name:						[NAME]
//
//   Type:						Barred Spiral, Spheroidal, Magellanic Spiral, Elliptical, Irregular, Spiral
//
//   Size:						Dwarf, Non-dwarf
//
//   Distance from Milky Way:	0 - 1 mly, 1 - 2.5 mly, 2.5 - 5 mly
//
//   Color:						White, Unknown, Lavender, Rainbow, Orange, Purple, Blue, Brown, Red, Yellow
//
//   Sattelite of:				None, Milky Way, Andromeda, Triangulum



class object
{
private:

	int number;
	string name, type, size, distFrMW, color, sattlOf;
	


public:

	object()
	{
		number = -1;
		name = "n/a";
		type = "n/a";
		size = "n/a";
		distFrMW = "n/a";
		color = "n/a";
		sattlOf = "n/a";
	}

	object(int number_, string name_, string type_, string size_, string distFrMW_,
		   string color_, string sattlOf_)
	{
		number = number_;
		name = name_;
		type = type_;
		size = size_;
		distFrMW = distFrMW_;
		color = color_;
		sattlOf = sattlOf_;
	}


	void operator= (const object& two)
	{
		number = two.number;
		name = two.name;
		type = two.type;
		size = two.size;
		distFrMW = two.distFrMW;
		color = two.color;
		sattlOf = two.sattlOf;
	}

	void display()
	{
		cout << "     ";
		cout << setw(4);
		cout << left << number;

		cout << setw(27);
		cout << left << name;

		cout << setw(20);
		cout << left << type;

		cout << setw(13);
		cout << left << size;

		cout << setw(18);
		cout << left << distFrMW;

		cout << setw(12);
		cout << left << color;

		cout << setw(15);
		cout << left << sattlOf << endl;
	}

	//   Returns the Galaxy Number
	int getNumber()
	{return number;}
	
	//   Returns the Galaxy Name
	string getName()
	{return name;}

	//   Returns the Galaxy Type
	string getType()
	{return type;}

	//   Returns the Galaxy Size
	string getSize()
	{return size;}

	//   Returns how far the Galaxy is from the Milky Way
	string getDistFrMW()
	{return distFrMW;}

	//   Returns the Galaxy Color
	string getColor()
	{return color;}

	//   Returns what Galaxy it orbits, if it does
	string getSattlOf()
	{return sattlOf;}
};





