#include"employee.h"

Employee::Employee(int id, string name, int dID)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Employee::showInfo()
{
	cout << "ְ�����" << this->m_ID
		<< "\tְ������" << this->m_Name
		<< "\t��λ:" << this->getDeptName()
		<< "\t��λְ��:��ɾ�������" << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}