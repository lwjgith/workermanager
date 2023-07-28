#pragma once
#include"manager.h"


Manager::Manager(int id, string name, int deptID)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = deptID;
}

void Manager::showInfo()
{
	cout << "职工编号" << this->m_ID
		<< "\t职工姓名" << this->m_Name
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责:完成老板任务,下发给员工" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}