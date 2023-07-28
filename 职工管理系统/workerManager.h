#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "emFile.txt"


class WorkerManager
{
public:
	WorkerManager();

	void Show_Menu();

	void exitSystem();

	int m_EmpNum;

	Worker **m_EmpArray;

	void add_Emp();

	void save();

	bool m_FileIsEmpty;

	int get_EmpNum();

	void init_Emp();

	void Show_Emp();

	void Del_Emp();

	int IsExit(int id);

	void Mod_Emp();

	void Find_Emp();

	void Sort_Emp();

	void Clean_File();

	~WorkerManager();
};