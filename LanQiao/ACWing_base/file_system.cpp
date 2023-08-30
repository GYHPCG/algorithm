#include<iostream>
#include<cstring>
#include<cstdlib>
#include<iomanip>
using namespace std;

constexpr int N = 10000;

int disk_block[N];
int disk_empty;

typedef struct UFD		//存储文件信息
{
	char name[10];		//文件名
	int attribute;		//属性
	int length;			//长度
	int address;
	string str;      //存放的字符串；
	int a[10];		//为文件本身分配10个空间
	int* p1;			//一级索引，100个空间
	int(*p2)[100];		//二级索引，100*100个空间
	struct UFD* next;
}UFD;

typedef struct MFD		//存储目录信息
{
	MFD* above;			//上一结点
	char name[10];
	int length;
	MFD* next;			//下一结点
	UFD* File_head;		//此目录下的文件指针
	MFD* MFD_head;		//此目录下目录链表指针
	int address;
	int protect_code;
}MFD;

class manager				//定义管理用户目录的类
{
	MFD* now;			//当前目录
	UFD* Fhead;			//文件的头结点
	MFD* Dhead;			//根目录的目录链头结点
	char code[10];		//密码
	char name[10];		//用户名
	int length;			//用户空间大小
	int status;			//是否获得空间
public:
	int write(string file);
	void set_status(int);
	int dis_file(string file);		//显示文件所占外存块号
	int dis_MFD(MFD* d);//当前路径
	int get_length();
	char const* get_name();
	char const* get_code();
	int get_status();
	int set_user(char*, char*);//设置用户名与密码
	MFD* get_now();
	int dele_file(UFD* f);		//删除文件
	int dele_MFD(MFD*);			//删除目录
	manager();						//构造
	~manager();					//析构
	int goback();				//返回上级
	int dis_now();				//显示当前目录
	int new_file(string file);
	int new_MFD(string file);
	int open_MFD(string file);
	int open_file();
	int first_dele_file(string file);		//删除文件的前部分工作
	int first_dele_MFD(string file);		//删除目录的前部分工作
	int set_code();
};

class Cdisk {					//用户类
public:
	manager user[5];		//用户个数最多为5
	char code[10];
	int new_user();				//查看当前用户与外存空间使用情况，后创建新用户
	int login(char);				//登陆
	Cdisk();
	virtual~Cdisk();			//虚函数，析构
};

Cdisk::Cdisk()		//管理磁盘的类，构造函数
{
	int i = 0;
	char code[10] = "123456";
	for (i = 0; i < N; i++)		//初始化所有磁盘块为空闲
		disk_block[i] = 0;
	//this->user[0].set_user("student","123");//默认一个用户
	disk_empty = N;
	cout.setf(ios::left);	//设置输出方式
}
Cdisk::~Cdisk()		//析构
{
}
int Cdisk::login(char b)		//登陆
{
	char n[10], c[10];
	int i;

	if (!user[0].get_status())	//当前不存在用户
	{
		i = 0;
		cout << "当前用户为空，欢迎注册！" << endl;
		user[i].set_status(1);		//为新用户分配权利
		cout << "请输入用户名：";
		cin >> n;
		cout << "请输入密码：";
		cin >> c;
		user[i].set_user(n, c);		//调用manager的成员函数，传递用户名与密码

		cout << "恭喜，创建用户成功！" << endl;
		return i;
	}
	else
	{
		cout << "用户名:";
		cin >> n;
		cout << "密码：";
		cin >> c;
		cout << endl;
		for (i = 0; i < 5; i++)	//查找是否存在此用户
		{
			if (user[i].get_status())		//存在方比较
				if (!strcmp(n, user[i].get_name()))	//相等时为0，此判断为匹配
					if (!strcmp(c, user[i].get_code()))		//密码匹配
					{
						cout << "登陆成功！" << endl;
						cout << "欢迎" << user[i].get_name() << "登陆" << endl;
						return i;
					}
					else
					{
						cout << "密码错误" << endl;
						return -1;
					}
		}
		cout << "此用户不存在！需要创建新用户吗？YES/NO" << endl;
		string op;
		cin >> op;
		if (op == "YES") new_user();
		return -1;
	}
}

int Cdisk::new_user()		//准备创建新用户
{
	char n[10], c[10];
	int i = 0, j;
	for (i = 0; i < 5; i++)
		if (user[i].get_status() == 0)		//是否有此用户，此尚未存在
			break;
	if (i == 5)
	{
		cout << "已经达到最大用户5个，不能再创建！" << endl;
		return 0;
	}
	user[i].set_status(1);		//为新用户分配权利
	cout << "请输入用户名：" << endl;
	cin >> n;
	if (i > 0)			//已有其它用户存在
	{
		for (j = 0; j < i - 1; j++)
			if (!strcmp(user[j].get_name(), n))
			{
				cout << "此用户名已存在！" << endl;
				return 0;
			}
	}
	cout << "请输入密码：" << endl;
	cin >> c;
	user[i].set_user(n, c);		//调用manager的成员函数，传递用户名与密码
	cout << "恭喜，创建用户成功！" << endl;
	return 1;
}

manager::manager()		//构造函数，初始化成员
{
	status = 0;
	length = 0;
	now = 0;
	Fhead = 0;
	Dhead = 0;
}

manager::~manager()		//析构，清除程序占用的内存
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
	while (d != 0)		//目录
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

int manager::new_file(string file)		//建立新文件
{
	int i = 0, j = 0;
	UFD* f, * p = 0;
	MFD* D;

	p = new UFD;				//开辟一个新的文件结构体
	srand((int)time(NULL));
	p->address =   rand();
	if (p == 0)
	{
		cout << "无可用内存空间，创建文件失败！" << endl;
		return 1;
	}
	strcpy(p->name,file.c_str());
	if (now == 0)			//根目录下的文件链
		f = Fhead;
	else				//当前目录下的文件链
		f = now->File_head;
	while (f != 0)			//检查是否文件重名
	{
		if (!strcmp(p->name, f->name))
		{
			cout << "此文件已存在！" << endl;
			return 0;	//退出
		}
		f = f->next;
	}
	cout << "长度：";
	cin >> p->length;
	cout << "属性(0：只读，1：读写)：";
	cin >> p->attribute;
	cout << endl;
	if (p->length > disk_empty)		//空间不足
	{
		cout << "文件太大，空间不足，当前空间为：" << disk_empty << endl;
		delete p;
		return 0;
	}
	disk_empty = disk_empty - p->length;	//剩余空闲盘块
	//
	for (i = 0; i < p->length && i < 10; i++)		//文件较小时，直接地址，文件数据盘块号
		for (j; j < N; j++)				//位示图法
			if (disk_block[j] == 0)		//空闲
			{
				p->a[i] = j;				//得到此空间
				disk_block[j] = 1;		//标记为已分配出去
				j++;
				break;					//跳出寻找，为文件分配下一空间
			}
	p->p1 = 0;					//一级索引
	p->p2 = 0;					//二级索引
	if (p->length > 10)			//超过10，用一级索引
	{
		p->p1 = new int[100];		//为一级索引分配100个空间
		for (i = 10; i < p->length && i < 110; i++)
			for (j; j < N; j++)		//j，继续前面的值
				if (disk_block[j] == 0)
				{
					(p->p1)[i - 10] = j;
					disk_block[j] = 1;
					j++;
					break;
				}
		if (p->length > 110)			//超过110，得用二级索引
		{
			p->p2 = new int[100][100];	//在一级索引的基础上，2维
			for (i = 110; i < p->length; i++)
				for (j; j < N; j++)		//j，继续前面的值
					if (disk_block[j] == 0)
					{
						int m = (i - 110) / 100;		//行
						int k = (i - 110) % 100;		//列
						p->p2[m][k] = j;
						disk_block[j] = 1;
						j++;
						break;
					}
		}
	}
	if (now == 0)	//根目录下的文件
	{
		p->next = Fhead;	//后继结点指向头，即新指点在前
		Fhead = p;	//新结点在头
	}
	else
	{
		p->next = now->File_head;
		now->File_head = p;
	}
	length += p->length;	//用户总空间大小增加
	if (now != 0)			//子目录下空间大小增加
	{
		now->length += p->length;
		D = now->above;	//上一级目录
		while (D != 0)		//上级目录（根目录已实现）空间增加
		{
			D->length += p->length;
			D = D->above;		//逐级向上
		}
	}

	return 0;
}

int manager::new_MFD(string file)		//建立新目录
{
	MFD* p, * h;
	p = new MFD;
	strcpy(p->name,file.c_str());
	srand((int)(time(NULL)));
	p->address = rand();
	p->protect_code =  rand() % 7;
	p->MFD_head = 0;		//目录下的目录链为空
	p->length = 0;		//
	p->File_head = 0;		//目录下的文件为空
	if (now == 0)			//当前为主目录
		h = Dhead;	//第一次时，h=0；指向目录链
	else
		h = now->MFD_head;//当前的目录链
	while (h != 0)	//此目录下存在其它子目录
	{
		if (!strcmp(h->name, p->name))
		{
			cout << "此目录已存在！" << endl;
			return 0;
		}
		h = h->next;
	}
	if (now == 0)		//当前为主目录
	{
		p->above = 0;		//主目录里目录的上一结点为0
		p->next = Dhead;		//把原目录接入新目录后面（Dhead初始为0）
		Dhead = p;		//Dhead始终指向最新目录结点
	}
	else
	{
		p->above = now;		//当前目录为新目录的上一结点
		p->next = now->MFD_head;	//反序插入新目录
		now->MFD_head = p;	//更新目录链
	}
	cout << "目录创建成功" << endl;
	return 1;
}

int manager::goback()		//向上返回
{
	if (now == 0)
	{
		return 0;
	}
	now = now->above;		//上一结点
	return 1;
}

int manager::open_MFD(string file)	//打开目录
{
	char name[10];
	MFD* p;
	if (now == 0)	//当前主目录
		p = Dhead;
	else
		p = now->MFD_head;	//p指向目录链
	strcpy(name,file.c_str());
	while (p != 0)
	{
		if (strcmp(p->name, name) == 0)
		{
			now = p;	//找到目录，now标记
			return 1;
		}
		p = p->next;
	}
	cout << "当前没此目录" << endl;
	return 0;
}

int manager::first_dele_file(string file)	//删除文件的前面工作
{
	char temp[10], a[5];
	strcpy(temp,file.c_str());
	UFD* f = Fhead;	//数据文件头指针
	UFD* above = 0;
	if (now != 0)
		f = now->File_head;	//当前目录下的数据文件
	while (f != 0)
	{
		if (!strcmp(f->name, temp))
			break;	//找到，跳出
		above = f;	//标记第一个文件
		f = f->next;
	}
	if (f == 0)
	{
		cout << "此文件不存在" << endl;
		return 0;
	}
	disk_empty += f->length;	//回收此数据文件的空间大小
	if (now == 0)	//根目录
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
	cout << "删除成功" << endl;
	return 1;
}

int manager::dele_file(UFD* f)	//具体实现删除文件
{
	int i = 0, m;
	for (i = 0; i < 10 && i < f->length; i++)	//回收文件具体空间，重置空闲
	{
		m = f->a[i];
		disk_block[m] = 0;
	}
	if (f->p1 != 0)	//回收一级索引
	{
		for (i = 10; i < 110 && i < f->length; i++)
		{
			m = f->p1[i - 10];
			disk_block[m] = 0;
		}
		delete[](f->p1);
	}
	if (f->p2 != 0)	//回收二级索引
	{
		for (i = 110; i < f->length; i++)
		{
			m = (f->p2)[(i - 110) / 100][(i - 110) % 100];
			disk_block[m] = 0;
		}
		delete[](f->p2);
		delete f;
	}
	f = 0;	//要删除的文件为空了
	return 1;
}

int manager::first_dele_MFD(string file)	//删除目录的前奏
{
	char n[10];
	char c;
	MFD* p, * above = 0;
	p = Dhead;	//指向根目录下的目录链
	if (now != 0)
		p = now->MFD_head;	//指向当前目录下的目录链
	strcpy(n,file.c_str());
	while (p != 0)
	{
		if (!strcmp(p->name, n))
			break;	//找到要删除的目录，跳出
		above = p;	//保存前一结点
		p = p->next;
	}
	if (p == 0)
	{
		cout << "没有这个目录！" << endl;
		return 0;
	}
	disk_empty += p->length;	//回收磁盘空间
	if (now == 0)
	{
		if (p == Dhead)	//如果是根目录下头结点，直接移动Dhead
			Dhead = Dhead->next;
		else
			above->next = p->next;//中间抽掉目标
	}
	else
	{
		if (p == now->MFD_head)
			now->MFD_head = now->MFD_head->next;
		else
			above->next = p->next;
		above = now;	//当前目录
		while (above != 0)
		{
			above->length -= p->length;//用above标记当前目录，进行大小更新
			above = above->above;	//向上一级
		}
	}
	length -= p->length;	//根目录大小更新
	this->dele_MFD(p);
	p = 0;
	cout << "删除成功！" << endl;
	return 1;
}

int manager::dele_MFD(MFD* p)	//具体实现删除目录的工作
{
	int flag = 0;
	MFD* d = p->MFD_head;	//当前目录下的目录链表
	UFD* f = p->File_head;	//当前目录下的文件链
	if (f != 0)
	{
		while (p->File_head->next != 0)//删除目录里的文件
		{
			f = p->File_head;
			while (f->next->next != 0)
				f = f->next;
			this->dele_file(f->next);
			f->next = 0;
		}
		if (p->File_head->next == 0)
		{
			this->dele_file(p->File_head);//删除头文件
			p->File_head = 0;
		}
	}
	if (d != 0)	//删除目录下的目录
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
			this->dele_MFD(p->MFD_head);//删除目录链头结点
			p->MFD_head = 0;
		}
	}
	delete p;	//释放p占用的内存
	p = 0;		//置0
	return 1;
}

int manager::dis_now()	//显示当前目录
{
	MFD* d = Dhead;
	UFD* f = Fhead;
	if (now != 0)
	{
		d = now->MFD_head;	//当前目录下的目录链
		f = now->File_head;
	}
	if (d == 0 && f == 0)
	{
		cout << "当前目录为空" << endl;
		return 0;
	}
	if (d == 0)
		cout << "当前目录下没有目录" << endl;
	else
	{
		cout << "当前目录下包含如下目录：" << endl;
		cout << setw(14) << "目录名称" << setw(14) << "目录大小" << setw(14) << "保护码" << setw(14) <<"地址" << endl;
		while (d != 0)
		{
			cout << setw(14) << d->name << setw(14) << d->length << setw(14)<< d->protect_code << setw(14) << d->address<< endl;
			d = d->next;
		}
	}
	if (f == 0)
		cout << "当前目录下没有文件" << endl;
	else
	{
		cout << "当前目录下包含如下文件:" << endl;
		cout << setw(14) << "文件名称" << setw(14) << "文件大小" << setw(14) << "文件权限" << setw(14)<< "地址"<< endl;
		while (f != 0)
		{
			cout << setw(14) << f->name << setw(14) << f->length << setw(14) << f->attribute << f->address << endl;
			f = f->next;
		}
	}
	return 1;
}

int manager::open_file()	//打开文件
{
	char n[10];
	cout << "请输入要打开的文件名" << endl;
	cin >> n;
	UFD* f = Fhead;	//文件头指针
	if (now != 0)
		f = now->File_head;	//指向文件
	while (f != 0)
	{
		if (!strcmp(f->name, n))
		{
			cout << "文件打开成功" << endl;
			return 1;
		}
		f = f->next;
	}
	cout << "当前目录无此文件" << endl;
	return 0;
}

MFD* manager::get_now()	//得到当前目录路径
{
	return now;
}

int manager::set_user(char* n, char* c)//建立用户与密码
{
	strcpy(name, n);
	strcpy(code, c);
	status = 1;
	return 1;
}

void manager::set_status(int b)//标记分配
{
	status = b;
}

int manager::get_status()//探取是否分配
{
	return status;
}

const char* manager::get_code()//得到密码
{
	return code;
}

const char* manager::get_name()//得到名字
{
	return name;
}

int manager::get_length()//得到长度
{
	return length;
}

int manager::dis_MFD(MFD* d)//显示目录
{
	if (d == 0)
	{
		cout << "/~: ";
		return 0;
	}

	if (d->above != 0)
		this->dis_MFD(d->above);//递归调用此功能
	cout << "/~/" << d->name << ": ";
	return 0;
}

int manager::dis_file(string file)//查看文件
{
	int i;
	char n[10];
	UFD* f = Fhead;
	if (now != 0)
		f = now->File_head;
	strcpy(n,file.c_str());
	while (f != 0)
	{
		if (!strcmp(n, f->name))	//找到此文件，跳出
			break;
		f = f->next;
	}
	if (f == 0)
	{
		cout << "当前目录下没此文件" << endl;
		return 0;
	}
	if (f->attribute == 0)
		cout << "文件类型：只读文件\n";
	else
		cout << "文件类型：读写文件\n";
	cout << "文件长度:" << f->length << "\n";
	cout << "存放的内容：" << f->str;
	cout << endl;
	return 1;
}

int manager::write(string file)//写文件
{
	int i;
	char n[10];
	UFD* f = Fhead;
	if (now != 0)
		f = now->File_head;
	strcpy(n,file.c_str());
	while (f != 0)
	{
		if (!strcmp(n, f->name))	//找到此文件，跳出
			break;
		f = f->next;
	}
	if (f == 0)
	{
		cout << "当前目录下没此文件" << endl;
		return 0;
	}
	if (f->attribute == 0) {
		cout << "文件类型：只读文件，不可写\n";
		return 0;
	}
	else {
		cout << "输入要写的内容\n";
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
		cout << "-----------------二级文件系统------------------------------" << endl;
		cout << endl;
		cout << "                 1.用户登陆" << endl;
		cout << "                 2.退出系统" << endl;
		cout << endl;
		cout << "-----------------------------------------------------------" << endl;

		cout << "\n请输入选择：";
		cin >> c;
		switch (c)
		{
		case '1':
			n = D.login(c);
			if (n == -1)
				break;
			cout << "*************************************************************" << endl;
			cout << "\t touch 创建文件" << endl;
			cout << "\t rmfile 删除文件" << endl;
			cout << "\t vim 写文件" << endl;
			cout << "\t cat 读文件" << endl;
			cout << "\t mkdir 创建目录" << endl;
			cout << "\t rmdir 删除目录" << endl;
			cout << "\t cd/ 打开目录" << endl;
			cout << "\t cd. 返回上一层目录" << endl;
			cout << "\t ls 查看当前目录" << endl;
			cout << "\t exit 安全退出" << endl;
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
