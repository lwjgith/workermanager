#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Employee:public Worker
{
public:
	Employee(int id,string name,int dID);

	virtual void showInfo();

	virtual string getDeptName();
};
