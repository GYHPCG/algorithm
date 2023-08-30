#include<iostream>
#include<cstring>
#include<cstdlib>
#include<iomanip>
using namespace std;

constexpr int N = 10000;

int disk_block[N];
int disk_empty;

typedef struct UFD		//�洢�ļ���Ϣ
{
	char name[10];		//�ļ���
	int attribute;		//����
	int length;			//����
	int address;
	string str;      //��ŵ��ַ�����
	int a[10];		//Ϊ�ļ��������10���ռ�
	int* p1;			//һ��������100���ռ�
	int(*p2)[100];		//����������100*100���ռ�
	struct UFD* next;
}UFD;

typedef struct MFD		//�洢Ŀ¼��Ϣ
{
	MFD* above;			//��һ���
	char name[10];
	int length;
	MFD* next;			//��һ���
	UFD* File_head;		//��Ŀ¼�µ��ļ�ָ��
	MFD* MFD_head;		//��Ŀ¼��Ŀ¼����ָ��
	int address;
	int protect_code;
}MFD;

class manager				//��������û�Ŀ¼����
{
	MFD* now;			//��ǰĿ¼
	UFD* Fhead;			//�ļ���ͷ���
	MFD* Dhead;			//��Ŀ¼��Ŀ¼��ͷ���
	char code[10];		//����
	char name[10];		//�û���
	int length;			//�û��ռ��С
	int status;			//�Ƿ��ÿռ�
public:
	int write(string file);
	void set_status(int);
	int dis_file(string file);		//��ʾ�ļ���ռ�����
	int dis_MFD(MFD* d);//��ǰ·��
	int get_length();
	char const* get_name();
	char const* get_code();
	int get_status();
	int set_user(char*, char*);//�����û���������
	MFD* get_now();
	int dele_file(UFD* f);		//ɾ���ļ�
	int dele_MFD(MFD*);			//ɾ��Ŀ¼
	manager();						//����
	~manager();					//����
	int goback();				//�����ϼ�
	int dis_now();				//��ʾ��ǰĿ¼
	int new_file(string file);
	int new_MFD(string file);
	int open_MFD(string file);
	int open_file();
	int first_dele_file(string file);		//ɾ���ļ���ǰ���ֹ���
	int first_dele_MFD(string file);		//ɾ��Ŀ¼��ǰ���ֹ���
	int set_code();
};

class Cdisk {					//�û���
public:
	manager user[5];		//�û��������Ϊ5
	char code[10];
	int new_user();				//�鿴��ǰ�û������ռ�ʹ��������󴴽����û�
	int login(char);				//��½
	Cdisk();
	virtual~Cdisk();			//�麯��������
};

Cdisk::Cdisk()		//������̵��࣬���캯��
{
	int i = 0;
	char code[10] = "123456";
	for (i = 0; i < N; i++)		//��ʼ�����д��̿�Ϊ����
		disk_block[i] = 0;
	//this->user[0].set_user("student","123");//Ĭ��һ���û�
	disk_empty = N;
	cout.setf(ios::left);	//���������ʽ
}
Cdisk::~Cdisk()		//����
{
}
int Cdisk::login(char b)		//��½
{
	char n[10], c[10];
	int i;

	if (!user[0].get_status())	//��ǰ�������û�
	{
		i = 0;
		cout << "��ǰ�û�Ϊ�գ���ӭע�ᣡ" << endl;
		user[i].set_status(1);		//Ϊ���û�����Ȩ��
		cout << "�������û�����";
		cin >> n;
		cout << "���������룺";
		cin >> c;
		user[i].set_user(n, c);		//����manager�ĳ�Ա�����������û���������

		cout << "��ϲ�������û��ɹ���" << endl;
		return i;
	}
	else
	{
		cout << "�û���:";
		cin >> n;
		cout << "���룺";
		cin >> c;
		cout << endl;
		for (i = 0; i < 5; i++)	//�����Ƿ���ڴ��û�
		{
			if (user[i].get_status())		//���ڷ��Ƚ�
				if (!strcmp(n, user[i].get_name()))	//���ʱΪ0�����ж�Ϊƥ��
					if (!strcmp(c, user[i].get_code()))		//����ƥ��
					{
						cout << "��½�ɹ���" << endl;
						cout << "��ӭ" << user[i].get_name() << "��½" << endl;
						return i;
					}
					else
					{
						cout << "�������" << endl;
						return -1;
					}
		}
		cout << "���û������ڣ���Ҫ�������û���YES/NO" << endl;
		string op;
		cin >> op;
		if (op == "YES") new_user();
		return -1;
	}
}

int Cdisk::new_user()		//׼���������û�
{
	char n[10], c[10];
	int i = 0, j;
	for (i = 0; i < 5; i++)
		if (user[i].get_status() == 0)		//�Ƿ��д��û�������δ����
			break;
	if (i == 5)
	{
		cout << "�Ѿ��ﵽ����û�5���������ٴ�����" << endl;
		return 0;
	}
	user[i].set_status(1);		//Ϊ���û�����Ȩ��
	cout << "�������û�����" << endl;
	cin >> n;
	if (i > 0)			//���������û�����
	{
		for (j = 0; j < i - 1; j++)
			if (!strcmp(user[j].get_name(), n))
			{
				cout << "���û����Ѵ��ڣ�" << endl;
				return 0;
			}
	}
	cout << "���������룺" << endl;
	cin >> c;
	user[i].set_user(n, c);		//����manager�ĳ�Ա�����������û���������
	cout << "��ϲ�������û��ɹ���" << endl;
	return 1;
}

manager::manager()		//���캯������ʼ����Ա
{
	status = 0;
	length = 0;
	now = 0;
	Fhead = 0;
	Dhead = 0;
}

manager::~manager()		//�������������ռ�õ��ڴ�
{
	disk_empty += length;
	length = 0;
	UFD* f = Fhead;
	MFD* d = Dhead;
	while (f != 0)
	{
		if (f->next == 0)
		{
			this->dele_file(f);
			f = 0;
			break;
		}
		while (f->next->next != 0)
			f = f->next;
		this->dele_file(f->next);
		f->next = 0;
		f = Fhead;
	}
	while (d != 0)		//Ŀ¼
	{
		if (d->next == 0)
		{
			this->dele_MFD(d);
			d = 0;
			break;
		}
		while (d->next->next != 0)
			d = d->next;
		this->dele_MFD(d->next);
		d->next = 0;
		d = Dhead;
	}
}

int manager::new_file(string file)		//�������ļ�
{
	int i = 0, j = 0;
	UFD* f, * p = 0;
	MFD* D;

	p = new UFD;				//����һ���µ��ļ��ṹ��
	srand((int)time(NULL));
	p->address =   rand();
	if (p == 0)
	{
		cout << "�޿����ڴ�ռ䣬�����ļ�ʧ�ܣ�" << endl;
		return 1;
	}
	strcpy(p->name,file.c_str());
	if (now == 0)			//��Ŀ¼�µ��ļ���
		f = Fhead;
	else				//��ǰĿ¼�µ��ļ���
		f = now->File_head;
	while (f != 0)			//����Ƿ��ļ�����
	{
		if (!strcmp(p->name, f->name))
		{
			cout << "���ļ��Ѵ��ڣ�" << endl;
			return 0;	//�˳�
		}
		f = f->next;
	}
	cout << "���ȣ�";
	cin >> p->length;
	cout << "����(0��ֻ����1����д)��";
	cin >> p->attribute;
	cout << endl;
	if (p->length > disk_empty)		//�ռ䲻��
	{
		cout << "�ļ�̫�󣬿ռ䲻�㣬��ǰ�ռ�Ϊ��" << disk_empty << endl;
		delete p;
		return 0;
	}
	disk_empty = disk_empty - p->length;	//ʣ������̿�
	//
	for (i = 0; i < p->length && i < 10; i++)		//�ļ���Сʱ��ֱ�ӵ�ַ���ļ������̿��
		for (j; j < N; j++)				//λʾͼ��
			if (disk_block[j] == 0)		//����
			{
				p->a[i] = j;				//�õ��˿ռ�
				disk_block[j] = 1;		//���Ϊ�ѷ����ȥ
				j++;
				break;					//����Ѱ�ң�Ϊ�ļ�������һ�ռ�
			}
	p->p1 = 0;					//һ������
	p->p2 = 0;					//��������
	if (p->length > 10)			//����10����һ������
	{
		p->p1 = new int[100];		//Ϊһ����������100���ռ�
		for (i = 10; i < p->length && i < 110; i++)
			for (j; j < N; j++)		//j������ǰ���ֵ
				if (disk_block[j] == 0)
				{
					(p->p1)[i - 10] = j;
					disk_block[j] = 1;
					j++;
					break;
				}
		if (p->length > 110)			//����110�����ö�������
		{
			p->p2 = new int[100][100];	//��һ�������Ļ����ϣ�2ά
			for (i = 110; i < p->length; i++)
				for (j; j < N; j++)		//j������ǰ���ֵ
					if (disk_block[j] == 0)
					{
						int m = (i - 110) / 100;		//��
						int k = (i - 110) % 100;		//��
						p->p2[m][k] = j;
						disk_block[j] = 1;
						j++;
						break;
					}
		}
	}
	if (now == 0)	//��Ŀ¼�µ��ļ�
	{
		p->next = Fhead;	//��̽��ָ��ͷ������ָ����ǰ
		Fhead = p;	//�½����ͷ
	}
	else
	{
		p->next = now->File_head;
		now->File_head = p;
	}
	length += p->length;	//�û��ܿռ��С����
	if (now != 0)			//��Ŀ¼�¿ռ��С����
	{
		now->length += p->length;
		D = now->above;	//��һ��Ŀ¼
		while (D != 0)		//�ϼ�Ŀ¼����Ŀ¼��ʵ�֣��ռ�����
		{
			D->length += p->length;
			D = D->above;		//������
		}
	}

	return 0;
}

int manager::new_MFD(string file)		//������Ŀ¼
{
	MFD* p, * h;
	p = new MFD;
	strcpy(p->name,file.c_str());
	srand((int)(time(NULL)));
	p->address = rand();
	p->protect_code =  rand() % 7;
	p->MFD_head = 0;		//Ŀ¼�µ�Ŀ¼��Ϊ��
	p->length = 0;		//
	p->File_head = 0;		//Ŀ¼�µ��ļ�Ϊ��
	if (now == 0)			//��ǰΪ��Ŀ¼
		h = Dhead;	//��һ��ʱ��h=0��ָ��Ŀ¼��
	else
		h = now->MFD_head;//��ǰ��Ŀ¼��
	while (h != 0)	//��Ŀ¼�´���������Ŀ¼
	{
		if (!strcmp(h->name, p->name))
		{
			cout << "��Ŀ¼�Ѵ��ڣ�" << endl;
			return 0;
		}
		h = h->next;
	}
	if (now == 0)		//��ǰΪ��Ŀ¼
	{
		p->above = 0;		//��Ŀ¼��Ŀ¼����һ���Ϊ0
		p->next = Dhead;		//��ԭĿ¼������Ŀ¼���棨Dhead��ʼΪ0��
		Dhead = p;		//Dheadʼ��ָ������Ŀ¼���
	}
	else
	{
		p->above = now;		//��ǰĿ¼Ϊ��Ŀ¼����һ���
		p->next = now->MFD_head;	//���������Ŀ¼
		now->MFD_head = p;	//����Ŀ¼��
	}
	cout << "Ŀ¼�����ɹ�" << endl;
	return 1;
}

int manager::goback()		//���Ϸ���
{
	if (now == 0)
	{
		return 0;
	}
	now = now->above;		//��һ���
	return 1;
}

int manager::open_MFD(string file)	//��Ŀ¼
{
	char name[10];
	MFD* p;
	if (now == 0)	//��ǰ��Ŀ¼
		p = Dhead;
	else
		p = now->MFD_head;	//pָ��Ŀ¼��
	strcpy(name,file.c_str());
	while (p != 0)
	{
		if (strcmp(p->name, name) == 0)
		{
			now = p;	//�ҵ�Ŀ¼��now���
			return 1;
		}
		p = p->next;
	}
	cout << "��ǰû��Ŀ¼" << endl;
	return 0;
}

int manager::first_dele_file(string file)	//ɾ���ļ���ǰ�湤��
{
	char temp[10], a[5];
	strcpy(temp,file.c_str());
	UFD* f = Fhead;	//�����ļ�ͷָ��
	UFD* above = 0;
	if (now != 0)
		f = now->File_head;	//��ǰĿ¼�µ������ļ�
	while (f != 0)
	{
		if (!strcmp(f->name, temp))
			break;	//�ҵ�������
		above = f;	//��ǵ�һ���ļ�
		f = f->next;
	}
	if (f == 0)
	{
		cout << "���ļ�������" << endl;
		return 0;
	}
	disk_empty += f->length;	//���մ������ļ��Ŀռ��С
	if (now == 0)	//��Ŀ¼
	{
		if (f == Fhead)
			Fhead = Fhead->next;
		else
			above->next = f->next;
	}
	else
	{
		MFD* d = now;
		while (d != 0)
		{
			d->length = f->length;
			d = d->above;
		}
		if (f == now->File_head)
			now->File_head = now->File_head->next;
		else
			above->next = f->next;
	}
	length -= f->length;
	this->dele_file(f);
	cout << "ɾ���ɹ�" << endl;
	return 1;
}

int manager::dele_file(UFD* f)	//����ʵ��ɾ���ļ�
{
	int i = 0, m;
	for (i = 0; i < 10 && i < f->length; i++)	//�����ļ�����ռ䣬���ÿ���
	{
		m = f->a[i];
		disk_block[m] = 0;
	}
	if (f->p1 != 0)	//����һ������
	{
		for (i = 10; i < 110 && i < f->length; i++)
		{
			m = f->p1[i - 10];
			disk_block[m] = 0;
		}
		delete[](f->p1);
	}
	if (f->p2 != 0)	//���ն�������
	{
		for (i = 110; i < f->length; i++)
		{
			m = (f->p2)[(i - 110) / 100][(i - 110) % 100];
			disk_block[m] = 0;
		}
		delete[](f->p2);
		delete f;
	}
	f = 0;	//Ҫɾ�����ļ�Ϊ����
	return 1;
}

int manager::first_dele_MFD(string file)	//ɾ��Ŀ¼��ǰ��
{
	char n[10];
	char c;
	MFD* p, * above = 0;
	p = Dhead;	//ָ���Ŀ¼�µ�Ŀ¼��
	if (now != 0)
		p = now->MFD_head;	//ָ��ǰĿ¼�µ�Ŀ¼��
	strcpy(n,file.c_str());
	while (p != 0)
	{
		if (!strcmp(p->name, n))
			break;	//�ҵ�Ҫɾ����Ŀ¼������
		above = p;	//����ǰһ���
		p = p->next;
	}
	if (p == 0)
	{
		cout << "û�����Ŀ¼��" << endl;
		return 0;
	}
	disk_empty += p->length;	//���մ��̿ռ�
	if (now == 0)
	{
		if (p == Dhead)	//����Ǹ�Ŀ¼��ͷ��㣬ֱ���ƶ�Dhead
			Dhead = Dhead->next;
		else
			above->next = p->next;//�м���Ŀ��
	}
	else
	{
		if (p == now->MFD_head)
			now->MFD_head = now->MFD_head->next;
		else
			above->next = p->next;
		above = now;	//��ǰĿ¼
		while (above != 0)
		{
			above->length -= p->length;//��above��ǵ�ǰĿ¼�����д�С����
			above = above->above;	//����һ��
		}
	}
	length -= p->length;	//��Ŀ¼��С����
	this->dele_MFD(p);
	p = 0;
	cout << "ɾ���ɹ���" << endl;
	return 1;
}

int manager::dele_MFD(MFD* p)	//����ʵ��ɾ��Ŀ¼�Ĺ���
{
	int flag = 0;
	MFD* d = p->MFD_head;	//��ǰĿ¼�µ�Ŀ¼����
	UFD* f = p->File_head;	//��ǰĿ¼�µ��ļ���
	if (f != 0)
	{
		while (p->File_head->next != 0)//ɾ��Ŀ¼����ļ�
		{
			f = p->File_head;
			while (f->next->next != 0)
				f = f->next;
			this->dele_file(f->next);
			f->next = 0;
		}
		if (p->File_head->next == 0)
		{
			this->dele_file(p->File_head);//ɾ��ͷ�ļ�
			p->File_head = 0;
		}
	}
	if (d != 0)	//ɾ��Ŀ¼�µ�Ŀ¼
	{
		while (p->MFD_head->next != 0)
		{
			d = p->MFD_head;
			while (d->next->next != 0)
				d = d->next;
			this->dele_MFD(d->next);
			d->next = 0;
		}
		if (p->MFD_head->next == 0)
		{
			this->dele_MFD(p->MFD_head);//ɾ��Ŀ¼��ͷ���
			p->MFD_head = 0;
		}
	}
	delete p;	//�ͷ�pռ�õ��ڴ�
	p = 0;		//��0
	return 1;
}

int manager::dis_now()	//��ʾ��ǰĿ¼
{
	MFD* d = Dhead;
	UFD* f = Fhead;
	if (now != 0)
	{
		d = now->MFD_head;	//��ǰĿ¼�µ�Ŀ¼��
		f = now->File_head;
	}
	if (d == 0 && f == 0)
	{
		cout << "��ǰĿ¼Ϊ��" << endl;
		return 0;
	}
	if (d == 0)
		cout << "��ǰĿ¼��û��Ŀ¼" << endl;
	else
	{
		cout << "��ǰĿ¼�°�������Ŀ¼��" << endl;
		cout << setw(14) << "Ŀ¼����" << setw(14) << "Ŀ¼��С" << setw(14) << "������" << setw(14) <<"��ַ" << endl;
		while (d != 0)
		{
			cout << setw(14) << d->name << setw(14) << d->length << setw(14)<< d->protect_code << setw(14) << d->address<< endl;
			d = d->next;
		}
	}
	if (f == 0)
		cout << "��ǰĿ¼��û���ļ�" << endl;
	else
	{
		cout << "��ǰĿ¼�°��������ļ�:" << endl;
		cout << setw(14) << "�ļ�����" << setw(14) << "�ļ���С" << setw(14) << "�ļ�Ȩ��" << setw(14)<< "��ַ"<< endl;
		while (f != 0)
		{
			cout << setw(14) << f->name << setw(14) << f->length << setw(14) << f->attribute << f->address << endl;
			f = f->next;
		}
	}
	return 1;
}

int manager::open_file()	//���ļ�
{
	char n[10];
	cout << "������Ҫ�򿪵��ļ���" << endl;
	cin >> n;
	UFD* f = Fhead;	//�ļ�ͷָ��
	if (now != 0)
		f = now->File_head;	//ָ���ļ�
	while (f != 0)
	{
		if (!strcmp(f->name, n))
		{
			cout << "�ļ��򿪳ɹ�" << endl;
			return 1;
		}
		f = f->next;
	}
	cout << "��ǰĿ¼�޴��ļ�" << endl;
	return 0;
}

MFD* manager::get_now()	//�õ���ǰĿ¼·��
{
	return now;
}

int manager::set_user(char* n, char* c)//�����û�������
{
	strcpy(name, n);
	strcpy(code, c);
	status = 1;
	return 1;
}

void manager::set_status(int b)//��Ƿ���
{
	status = b;
}

int manager::get_status()//̽ȡ�Ƿ����
{
	return status;
}

const char* manager::get_code()//�õ�����
{
	return code;
}

const char* manager::get_name()//�õ�����
{
	return name;
}

int manager::get_length()//�õ�����
{
	return length;
}

int manager::dis_MFD(MFD* d)//��ʾĿ¼
{
	if (d == 0)
	{
		cout << "/~: ";
		return 0;
	}

	if (d->above != 0)
		this->dis_MFD(d->above);//�ݹ���ô˹���
	cout << "/~/" << d->name << ": ";
	return 0;
}

int manager::dis_file(string file)//�鿴�ļ�
{
	int i;
	char n[10];
	UFD* f = Fhead;
	if (now != 0)
		f = now->File_head;
	strcpy(n,file.c_str());
	while (f != 0)
	{
		if (!strcmp(n, f->name))	//�ҵ����ļ�������
			break;
		f = f->next;
	}
	if (f == 0)
	{
		cout << "��ǰĿ¼��û���ļ�" << endl;
		return 0;
	}
	if (f->attribute == 0)
		cout << "�ļ����ͣ�ֻ���ļ�\n";
	else
		cout << "�ļ����ͣ���д�ļ�\n";
	cout << "�ļ�����:" << f->length << "\n";
	cout << "��ŵ����ݣ�" << f->str;
	cout << endl;
	return 1;
}

int manager::write(string file)//д�ļ�
{
	int i;
	char n[10];
	UFD* f = Fhead;
	if (now != 0)
		f = now->File_head;
	strcpy(n,file.c_str());
	while (f != 0)
	{
		if (!strcmp(n, f->name))	//�ҵ����ļ�������
			break;
		f = f->next;
	}
	if (f == 0)
	{
		cout << "��ǰĿ¼��û���ļ�" << endl;
		return 0;
	}
	if (f->attribute == 0) {
		cout << "�ļ����ͣ�ֻ���ļ�������д\n";
		return 0;
	}
	else {
		cout << "����Ҫд������\n";
	}
	getchar();
	getline(cin, f->str);
}
int main()
{
	char c;
	Cdisk D;
	int i = 1, n, flag = 1, t = 0;

	while (flag)
	{
		cout << "-----------------�����ļ�ϵͳ------------------------------" << endl;
		cout << endl;
		cout << "                 1.�û���½" << endl;
		cout << "                 2.�˳�ϵͳ" << endl;
		cout << endl;
		cout << "-----------------------------------------------------------" << endl;

		cout << "\n������ѡ��";
		cin >> c;
		switch (c)
		{
		case '1':
			n = D.login(c);
			if (n == -1)
				break;
			cout << "*************************************************************" << endl;
			cout << "\t touch �����ļ�" << endl;
			cout << "\t rmfile ɾ���ļ�" << endl;
			cout << "\t vim д�ļ�" << endl;
			cout << "\t cat ���ļ�" << endl;
			cout << "\t mkdir ����Ŀ¼" << endl;
			cout << "\t rmdir ɾ��Ŀ¼" << endl;
			cout << "\t cd/ ��Ŀ¼" << endl;
			cout << "\t cd. ������һ��Ŀ¼" << endl;
			cout << "\t ls �鿴��ǰĿ¼" << endl;
			cout << "\t exit ��ȫ�˳�" << endl;
			cout << "*************************************************************" << endl;
			while (flag)
			{
				cout << D.user[n].get_name();
				D.user[n].dis_MFD(D.user[n].get_now());
				string op;
				string file;
				cin >> op >> file;

				cout << endl;
				if (op == "touch")
					D.user[n].new_file(file);
				else if(op == "rmfile")
					D.user[n].first_dele_file(file);
				else if(op == "vim")
					D.user[n].write(file);
				else if(op == "cat")
					D.user[n].dis_file(file);
				else if (op == "mkdir")
					D.user[n].new_MFD(file);
				else if (op == "rmdir")
					D.user[n].first_dele_MFD(file);
				else if (op == "cd/")
					D.user[n].open_MFD(file);
				else if (op == "cd.")
					D.user[n].goback();
				else if (op == "ls")
					D.user[n].dis_now();
				else  if (op == "exit")
				{
					flag = 0;
					system("cls");
				}
				cout << endl;
			}
			flag = 1;
			break;
		case '2':
			flag = 0;
			break;
		}
	}
	return 0;
}
