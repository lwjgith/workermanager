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
	cout << "ְ�����" << this->m_ID
		<< "\tְ������" << this->m_Name
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ��:����ϰ�����,�·���Ա��" << endl;
}

string Manager::getDeptName()
{
	return string("����");
}