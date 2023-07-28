#include"workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	//cout << "职工人数为" << num << endl;
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker*[this->m_EmpNum];
	this->init_Emp();
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dID;

	int num=0;
	while (ifs >> id && ifs >> name && ifs >> dID)
	{
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dID;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dID)
	{
		Worker * worker = NULL;
		/*if (dID == 1)
		{
			worker = new Employee(id, name, dID);
		}
		else if (dID == 2)
		{
			worker = new Manager(id, name, dID);
		}
		else
		{
			worker = new Boss(id, name, dID);
		}*/
		switch (dID)
		{
		case 1:
			worker = new Employee(id, name, dID);
			break;
		case 2:
			worker = new Manager(id, name, dID);
			break;
		case 3:
			worker = new Boss(id, name, dID);
			break;
		default:
			break;
		}
		this->m_EmpArray[index++] = worker;
	}
	ifs.close();
}

void WorkerManager::Show_Menu()
{
	cout << "欢迎使用职工管理系统" << endl;
	cout << "0.退出管理程序" << endl;
	cout << "1.增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除离职员工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空所有文档" << endl;
}

void WorkerManager::exitSystem()
{
	cout << "欢迎下一次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::add_Emp()
{
	cout << "请输入添加职工数量" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace =  new Worker*[newSize];

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
			cin >> id;
			int ret = this->IsExit(id);
			while (ret != -1)
			{
				cout << "职工编号已存在，请重新输入" << endl;
				cin >> id;
				ret = this->IsExit(id);
			}
			cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
			cin >> name;
			cout << "请选择该职工岗位" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->save();
		this->m_FileIsEmpty = false;
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else
	{
		cout << "数据有误" << endl;
		return;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入删除职工编号" << endl;
		int id = 0;
		cin >> id;
		int index  = this->IsExit(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "职工编号不存在" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExit(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (id == this->m_EmpArray[i]->m_ID)
		{
			index = i;
			break;
		}
	}
	return index;
}

//void WorkerManager::Mod_Emp()
//{
//	if (this->m_FileIsEmpty)
//	{
//		cout << "文件不存在或记录为空";
//	}
//	else
//	{
//		int id;
//		int newID;
//		string newName;
//		int newDeptID;
//		cout << "请输入修改职工的编号";
//		cin >> id;
//		int index = this->IsExit(id);
//		if (index != -1)
//		{
//			delete this->m_EmpArray[index];
//			cout << "请输入职工的编号" << endl;
//			cin >> newID;
//			cout << "请输入职工的名字" << endl;
//			cin >> newName;
//			cout << "请选择该职工岗位" << endl;
//			cout << "1.普通员工" << endl;
//			cout << "2.经理" << endl;
//			cout << "3.老板" << endl;
//			cin >> newDeptID;
//			this->m_EmpArray[index]->m_ID = newID;
//			this->m_EmpArray[index]->m_Name = newName;
//			this->m_EmpArray[index]->m_DeptID = newDeptID;
//			this->save();
//			cout << "修改成功" << endl;
//		}
//		else
//		{
//			cout << "职工编号有误" << endl;
//		}
//	}
//	system("pause");
//	system("cls");
//}


void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号" << endl;
		int id;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newID;
			string newName;
			int newDeptID;
			cout << "请输入新的编号" << endl;
			cin >> newID;
			cout << "请输入新姓名" << endl;
			cin >> newName;
			cout << "请输入岗位" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> newDeptID;
			Worker * worker = NULL;
			switch (newDeptID)
			{
			case 1:
				worker = new Employee(newID, newName, newDeptID);
				break;
			case 2:
				worker = new Manager(newID, newName, newDeptID);
				break;
			case 3:
				worker = new Boss(newID, newName, newDeptID);
				break;
			default :
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;
			this->save();
		}
		else
		{
			cout << "修改失败,查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号:" << endl;
			cin >> id;
			int ret = IsExit(id);
			if (ret != -1)
			{
				cout << "查找成功,信息如下" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			bool flag = false;
			cout << "请输入查找的姓名" << endl;
			cin >> name;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为"
						<< this->m_EmpArray[i]->m_ID
						<< "号职工信息如下" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查无此人" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式" << endl;
		cout << "1.按职工号进行升序" << endl;
		cout << "2.按职工号进行降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minOrMax]->m_ID > this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_ID < this->m_EmpArray[j]->m_ID)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker *temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File()
{
	cout << "确定清空?" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	ofs.close();
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}