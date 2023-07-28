#include"employee.h"

Employee::Employee(int id, string name, int dID)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_DeptID = dID;
}

void Employee::showInfo()
{
	cout << "职工编号" << this->m_ID
		<< "\t职工姓名" << this->m_Name
		<< "\t岗位:" << this->getDeptName()
		<< "\t岗位职责:完成经理任务" << endl;
}

string Employee::getDeptName()
{
	return string("员工");
}