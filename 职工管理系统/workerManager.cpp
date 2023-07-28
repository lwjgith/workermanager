#include"workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
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
		//cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ" << num << endl;
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
	cout << "��ӭʹ��ְ������ϵͳ" << endl;
	cout << "0.�˳��������" << endl;
	cout << "1.����ְ����Ϣ" << endl;
	cout << "2.��ʾְ����Ϣ" << endl;
	cout << "3.ɾ����ְԱ��" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.���ձ������" << endl;
	cout << "7.��������ĵ�" << endl;
}

void WorkerManager::exitSystem()
{
	cout << "��ӭ��һ��ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::add_Emp()
{
	cout << "���������ְ������" << endl;
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
			cout << "�������" << i + 1 << "����ְ�����:" << endl;
			cin >> id;
			int ret = this->IsExit(id);
			while (ret != -1)
			{
				cout << "ְ������Ѵ��ڣ�����������" << endl;
				cin >> id;
				ret = this->IsExit(id);
			}
			cout << "�������" << i + 1 << "����ְ������:" << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
	}
	else
	{
		cout << "��������" << endl;
		return;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "������ɾ��ְ�����" << endl;
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
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ְ����Ų�����" << endl;
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
//		cout << "�ļ������ڻ��¼Ϊ��";
//	}
//	else
//	{
//		int id;
//		int newID;
//		string newName;
//		int newDeptID;
//		cout << "�������޸�ְ���ı��";
//		cin >> id;
//		int index = this->IsExit(id);
//		if (index != -1)
//		{
//			delete this->m_EmpArray[index];
//			cout << "������ְ���ı��" << endl;
//			cin >> newID;
//			cout << "������ְ��������" << endl;
//			cin >> newName;
//			cout << "��ѡ���ְ����λ" << endl;
//			cout << "1.��ͨԱ��" << endl;
//			cout << "2.����" << endl;
//			cout << "3.�ϰ�" << endl;
//			cin >> newDeptID;
//			this->m_EmpArray[index]->m_ID = newID;
//			this->m_EmpArray[index]->m_Name = newName;
//			this->m_EmpArray[index]->m_DeptID = newDeptID;
//			this->save();
//			cout << "�޸ĳɹ�" << endl;
//		}
//		else
//		{
//			cout << "ְ���������" << endl;
//		}
//	}
//	system("pause");
//	system("cls");
//}


void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı��" << endl;
		int id;
		cin >> id;
		int ret = this->IsExit(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newID;
			string newName;
			int newDeptID;
			cout << "�������µı��" << endl;
			cin >> newID;
			cout << "������������" << endl;
			cin >> newName;
			cout << "�������λ" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
		else
		{
			cout << "�޸�ʧ��,���޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "��������ҵ�ְ�����:" << endl;
			cin >> id;
			int ret = IsExit(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�,��Ϣ����" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			bool flag = false;
			cout << "��������ҵ�����" << endl;
			cin >> name;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ"
						<< this->m_EmpArray[i]->m_ID
						<< "��ְ����Ϣ����" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "���޴���" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ" << endl;
		cout << "1.��ְ���Ž�������" << endl;
		cout << "2.��ְ���Ž��н���" << endl;
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
		cout << "����ɹ�" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File()
{
	cout << "ȷ�����?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
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
		cout << "��ճɹ�" << endl;
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