#pragma once
#include"boss.h"

Boss::Boss(int id, string name, int deptID)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = deptID;

}

void Boss::showInfo()
{
	cout << "职工编号" << this->m_ID
		<< "\t职工姓名" << this->m_Name
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责:管理公司所有事务" << endl;
}

string Boss::getDeptName()
{
	return string("老板");
}