//类模板实现一个简单的array模板
#if 0
#include<iostream>
#include<string>

template<typename T>
class Array {
	int size;
	T *data;
public:
	Array(int i) {
		size = i;
		data = new T[i];
	}
	~Array() {
		delete[] data;
	}
	T& operator [](int i) {
		return data[i];
	}
};

int main(void) {
	int n;
	std::cin >> n;
	std::cout << n << std::endl;
	Array<std::string> arr(n);
	arr[0] = "111";
	arr[1] = "222";
	arr[2] = arr[0] + arr[1];
	std::cout << arr[2] << std::endl;
	return 10;
}
#endif

//简单使用vector+string=动态字符串数组
#if 0
#include<string>
#include<iostream>
#include<vector>
int main(void )
{
    std::vector<std::string> names;
    int num ;
    std::cin >> num;
    names.resize(num);
    names[0] = "gzf";
    names[1] = "lf";
    names[1] = "lfhh";
    //for循环迭代vector
    for (std::vector<std::string>::size_type i = 0; i < num; ++i) {
        std::cout << names[i]<<std::endl;
    }
    //使用迭代器遍历vector
    for (std::vector<std::string>::iterator j= names.begin();j!= names.end() ;j++) {
        std::cout << *j << std::endl;
    }
    return 0;
}
#endif

//简单的类和继承
#if 0
#include<iostream>
#include <string>
using namespace std;
class A{
    string name;
public:
    A(string name);
    void print();
};

class B: public A{
    int age;
public:
    B(string name,int age);
    void print();
};

A::A(string name):name(name) {

}

void A::print() {
    cout << name << endl;
}

B::B(string name,int age):A(name),age(age){

}

void B::print() {
//    cout << age << "\t" << name;//子类的方法不能直接访问父类的属性
    cout << age << "\t";
    A::print();//子类的方法可以调用父类方法，从而调用父类里的属性
}
//错误，基类的属性只能通过基类去实例化
//B::B(string name,int age):name(name),age(age){
//
//}
int main(void){
    A a("gzf");
    a.print();
    B b("lf",22);
    b.print();
    return 0;
}
#endif

//虚函数和多态
#if 0
#include<iostream>
#include <string>
using namespace std;
class A{
    string name;
public:
    A(string name);
    virtual void print();
};

class B: public A{
    int age;
public:
    B(string name,int age);
    virtual void print();
};

A::A(string name):name(name) {

}

void A::print() {
    cout << name << endl;
}

B::B(string name,int age):A(name),age(age){

}

void B::print() {
    cout << age << "\t";
    A::print();
}

int main(void){
    A a("gzf");
    B b("lf",22);
    a.print();
    b.print();
    A *p = &a;
    A *q = &b;//子类的指针自动转化为父类指针
    p->print();
    q->print();//调用时，因为父类的print生命了virtual，指针调用时会调用子类的print方法，从而实现了多态
    return 0;
}
#endif

//实现简单的string  使用拷贝构造函数 运算符重载 输出流运算符重载 析构函数
#if 0
#include<iostream>
#include<cstring>
using namespace std;
class String{
    char *data;
    int size;
public:
    //构造函数
    String(const char *str=0){
        if(str==0){
            data = 0;
            size = 0;
            return;
        }
        size = strlen(str);
        data = new char[size+1];
        for(int i = 0;i < size;i++){
            data[i] = str[i];
        }
        data[size] = '\0';
    }
    //拷贝构造函数
    String(const String &s){
        cout << "copy construct" << endl;
        size = s.size;
        data = new char[size+1];
        strcpy(data,s.data);
    }
    //移动构造函数
    String(String &&s){
        if(s.data!=NULL){
            data = s.data;
            s.data = NULL;
        }
    }
    //移动赋值运算符
    String& operator=(String &&s){
        if(this!=&s){
            delete[] data;
            data = s.data;
            s.data = NULL;
        }
        return *this;
    }
    //[]运算符重载
    char &operator[](int i)const{  //const的作用，编译器检查函数里面不能修改对象的成员变量，比如size和data的指向，但是data指针指向的数据内容可以改变
        if(i<0||i>=size){
            throw "下标非法";
        }
        return data[i];
    }
    //=运算符重载
    String &operator=(const String &other){  //const的作用，编译器检查函数里面不能修改对象的成员变量，比如size和data的指向，但是data指针指向的数据内容可以改变
        if(this == &other){
            return *this;
        }
        delete[] data;
        int length = strlen(other.data);
        data = new char[length+1];
        if(data!=NULL){
            strcpy(data,other.data);
        }else{
            exit(-1);
        }
        return *this;
    }
    int stringSize(){
        return size;
    }
    //析构函数
    ~String(){
        if(data){
            delete[] data;
        }
    }
};
//类的标准输出运算重载  只能写在类外    第二个参数String &s则不会调用String的拷贝构造函数，而如果是String s则会调用拷贝构造函数
ostream &operator<<(ostream &o,String &s){
    for(int i = 0;i < s.stringSize();i++){
        cout<<s[i];
    }
    return o;
}

void func(){
    String str1,str2("gzf666");
    str2[4] = '8';
    cout<<str2<<endl;
    String str3 = str2;
    cout<<str3<<endl;
    str3[1] = 'g';
    cout<<str2<<endl;
    cout<<str3<<endl;
}

int main(void){

    func();
    return 0;
}
#endif

//实现简单的vector类模版
#if 0
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Vector{
public:
    Vector(int n = 3){
        data = new T[n];
        max_size = n;
        size = 0;
    }
    //拷贝构造函数  调用时机：
    // 1.以同类对象进行初始化，包括 Vector<string> t = source; Vector<string> t(source)两种形式的初始化
    // 2.以值传递的方式传入某方法或函数
    // 3.以值传递的方式传出某方法或函数
    Vector(const Vector<T> &source){
        max_size = source.max_size;
        size = source.size;
        data = new T[max_size];
        for (int i = 0; i < size; ++i) {
            data[i] = source[i];
        }
        cout << "copy construct" << endl;
    }
    void push_back(T e){
        if(size==max_size){
            cout << "max_size dilatation" << endl;
            //空间满了，扩容
            T *p = new T[2 * max_size];
            if(p){
                for (int i = 0; i < size; ++i) {
                    p[i] = data[i];
                }
                delete[] data;
                max_size = 2 * max_size;
                data = p;
            }else{
                return;
            }
        }
        data[size] = e;
        size++;
    }
    T &operator[](int i)const{
        if(i<0||i>=size){
            throw "下标非法";
        }
        return data[i];
    }
    void operator=(const Vector<T> &source){
        max_size = source.max_size;
        size = source.size;
        data = new T[max_size];
        for (int i = 0; i < size; ++i) {
            data[i] = source[i];
        }
    }
    int getSize(){
        return size;
    }
    ~Vector(){
        cout << "~Vector" << endl;
        delete[] data;
    }

private:
    T *data;//动态
    int max_size;//容量
    int size;//当前元素数量
};

//标准输出重定向 输出vector里的所有数据
template<typename T>
ostream &operator<<(ostream &o,Vector<T> &v){
    for (int i = 0; i < v.getSize(); ++i) {
        cout << v[i] << endl;
    }
    return o;
}

//标准输入重定向  往vector里添加数据
template<typename T>
istream &operator>>(istream &i,Vector<T> &v){
    T *temp = new T;
    cin >> *temp;
    v.push_back(*temp);
    return i;
}

void func(){
    Vector<string> v;
    v.push_back("gzf");
    v.push_back("lf");
    v.push_back("gy");
    v.push_back("666");
//    Vector<string> t;
//    t = v;
//    cout << t;
//    cin >> t;
//    cout << t;
//    Vector<string> g(t);
//    cout << g;
    Vector<int> list;
    cin >> list >> list;
    cout << list;

}

int main(void){
    func();
    return 0;
}
#endif

//文件的操作
#if 0
#include<iostream>
#include<fstream>
using namespace std;
int main(void)
{
    fstream file;
    file.open("./test.txt",ios::app);
    if(!file){
       cout << "open fail" << endl;
    }

    file << "gzf666" << endl;
    file.close();
    return 0;
}
#endif

//复制二进制文件
#if 0
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

static const int bufferLen = 2048;
//bool CopyFile(const char* src, const char* dst)这样也可以
bool CopyFile(const string& src, const string& dst)
{
    //以读方式打开源文件和以写方式打开目标文件 ifstream和ofstream可以替换成fstream
    ifstream in(src.c_str(), ios::in | ios::binary);//string.c_str()方法获取指向字符串的指针
    ofstream out(dst.c_str(), ios::out | ios::binary | ios::trunc);

    //判断文件是否打开成功
    if (!in || !out) {
        return false;
    }
    //从源文件中读数据，写到目标文件，以EOF判断是否读到了源文件末尾
    char temp[bufferLen];
    while (!in.eof()) {
        in.read(temp, bufferLen);//最大读书bufferLen个字节到temp所在的内存
        streamsize count =  in.gcount();//最后一次读取的字节长度
        out.write(temp, count);//写入文件
    }

    in.close();
    out.close();
}
int main(void)
{
    CopyFile("a.mp4", "b.mp4");
    return 0;
}
#endif

//单例模式
#if 0
#include "myInstance.h"
using namespace std;
int main(){
    myInstance* my = myInstance::getInstance();
    my->print();
    return 0;
}
#endif

//stl序列容器基本使用
#if 0
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;
int main(void)
{
    int iArr[] = {1,2,3,4,5};
    vector<int> iVector(iArr,iArr+4);//动态数组
    list<int> iList(iArr,iArr+4); //双向链表
    deque<int> iDeque(iArr,iArr+4);//上面的特性
    queue<int> iQueue(iDeque); //queue是deque适配实现的，可以直接用deque实例化
    stack<int> iStack(iDeque); //stack是deque适配实现的，可以直接用deque实例化
    priority_queue<int>iPQueue(iArr,iArr+4); //优先队列，按优先权

    //for_each遍历
    for_each(iVector.begin(),iVector.end(),[](int &num){
       cout << num << "";
    });
    cout << endl;
    //迭代器遍历
    list<int>::iterator lIter;
    for (lIter = iList.begin(); lIter != iList.end() ; ++lIter) {
        cout << *lIter << "";
    }
    cout << endl;
    for_each(iDeque.begin(),iDeque.end(),[](int &num){
        num++;
    });
    //使用for循环
    for(auto num : iDeque){
        cout << num << "";
    }
    cout << endl;
    //队列的遍历
    while (!iQueue.empty()){
        cout << iQueue.front() << "";//输出当前队头数据
        iQueue.pop(); //弹出当前队头数据
    }
    cout << endl;
    //栈的遍历
    while (!iStack.empty()){
        cout << iStack.top() << "";//输出当前栈顶数据
        iStack.pop();//弹出当前栈顶数据
    }
    cout << endl;
    //优先级队列的遍历
    while (!iPQueue.empty()){
        cout << iPQueue.top() << "";
        iPQueue.pop();
    }
    cout << endl;
    return 0;

}
#endif

//stl关联容器map基本使用
#if 0
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
struct Display{
    void operator()(pair<string,double> info){
        cout << info.first << ":" << info.second << endl;
    }
};
int main(void)
{
     map<string,double> student;
     student["gzf"] = 66.66;
     student["lf"] = 0.85;
     student["gy"] = 100.00;
     student.insert(pair<string,double>("zzz",33.33));
     student.insert(make_pair("hhh",44.33));
     student.insert(map<string,double>::value_type("ggg",222));
     student["hhh"] = 100.00;
     for_each(student.begin(),student.end(),Display());//不是按照定义的顺序进行输出，而是会根据键进行排序

     map<string,double>::iterator iter;
     iter = student.find("asd");//查找key元素，如果没找到，迭代器会指向end
     if(iter != student.end()){
         cout << iter->second << endl;
     }else{
         cout << "find end" << endl;
     }

     //使用迭代器完成遍历查找  迭代器的end()表示容器最后一个元素后面的位置，是不存在的，所以用end来判断是否遍历完成
     iter = student.begin();
     while (iter!= student.end()){
         if(iter->second<95.0){
             iter = student.erase(iter); //通过erase删除容器中的元素，传入一个迭代器。注意，删除元素后，这个迭代器可能会失效（被删除），因为迭代器指向的元素已经被删除。
         }else{
             iter++;
         }
     }
    for_each(student.begin(),student.end(),Display());//不是按照定义的顺序进行输出，而是会根据键进行排序

    student.erase("zzz");//直接根据key删除，成功删除返回1
}
#endif


//迭代器的使用
#if 0
#include <list>
#include <iostream>
using namespace std;
int main(void)
{
    list<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_front(2);
    v.push_front(1);
    //正向遍历
    list<int>::const_iterator it = v.begin();
    while (it!=v.end()){
        cout << *it << endl;
        it++;
    }
    //反向遍历
    list<int>::const_reverse_iterator  it2 = v.rbegin();
    while (it2!=v.rend()){
        cout << *it2 << endl;
        it2++;
    }
    return 0;
}
#endif

//多线程
#if 0
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;
mutex lock1;//排他锁
void T1()
{
    while (1){
        lock1.lock();
        cout << "hello" << endl;
        lock1.unlock();
    }
}
void T2(const char* str)
{
    while (1) {
        lock1.lock();
        cout << str << endl;
        lock1.unlock();
    }
}
int main()
{
    thread t1(T1);
    thread t2(T2,"gzf");
    cout << "ssss" << endl;
    t1.join();
    t2.join();
}
#endif

//多线程 排它锁
#if 0
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;


int main()
{
    mutex lock1;
    int money = 1000;
    thread t1([&]()->void{
        for (int i = 0; i < 100; ++i) {
            lock1.lock();
            money++;
            lock1.unlock();
        }
    });
    thread t2([&]()->void{
        for (int i = 0; i < 100; ++i) {
            lock1.lock();
            money = money - 2;
            lock1.unlock();
        }
    });
    t1.join();
    t2.join();
    cout << money << endl;
    return 0;
}
#endif

//编程练习题start
//字符串翻转 原地翻转
#if 0
#include <cstring>
#include <iostream>
void reversalChar(char* str){
    int strLength = strlen(str);
    int times = strLength/2;
    int temp = 0;
    for (int i = 0; i < times; ++i) {
        temp = str[i];
        str[i] = str[strLength-1-i];
        str[strLength-1-i] = temp;
    }
}
int main(void)
{
    char str[] = "12";
    reversalChar(str);
    std::cout << str << std::endl;
    return 0;
}
#endif

//实现将整数型字符串转换为整型数
#if 0
#include <cstring>
#include <cmath>
#include <iostream>
/**
 * 单个数字字符转化为int型
 * @param ch
 * @return
 */
int ctoi(const char ch){
    return ch - '0';
}

/**
 * 实现将整数型字符串转换为整型数
 * @param data 要转化的数字字符串
 * @param type 数字字符串的类型 2就是二进制 10就是十进制
 * @return
 */
long long stoi(const char* data,int type){
    long long res = 0;
    while (*data){
        res = res * type + ctoi(*data);
        data++;
    }
    return res;
}

int main(void)
{
    const char * data = "11110";
    long long res = stoi(data,2);
    std::cout << res << std::endl;
    return 0;
}
#endif


//整数转化成字符串
#if 0
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
void reversalChar(char* str){
    int strLength = strlen(str);
    int times = strLength/2;
    int temp = 0;
    for (int i = 0; i < times; ++i) {
        temp = str[i];
        str[i] = str[strLength-1-i];
        str[strLength-1-i] = temp;
    }
}
/**
 * @param num
 * @param type 代表多少进制 2是二进制 10是十进制
 * @return
 */
string* intToString(int num,int type){
    string *str = new string();
    while (num > 0){
        (*str).push_back(num % type + '0');
        num /= type;
    }
    return str;
}

int main()
{
    char* res = const_cast<char *>(intToString(6,2)->c_str());
    reversalChar(res);
    cout << res << endl;
    return 0;
}
#endif

//实现字符串拷贝函数strcpy strncpy
#if 0
#include <iostream>
//缺陷，如果src的长度大于dest，会造成越界，修改了栈空间其他变量的数据
char* strcopy(char* dest,const char* src)
{
    while (*src){
        *dest++ = *src++;
    }
    *dest = '\0';
    return dest;
}

//传递一个dest数组的长度，则可以避免越界
char* strcopy2(char* dest,const char* src,int dest_len)
{
    int len = 0;
    while (*src){
        *dest++ = *src++;
        len++;
        if(len==dest_len){
            break;
        }
    }
    *dest = '\0';
    return dest;
}


int main(void)
{
    long long a = 10;
    char data[20];
    char data1[20];
    long long b = 10;
    const char* src = "guzhifuailiufangdasdasdd13123asddsada12123";
//    strcopy(data,src);
    strcopy2(data1,src,sizeof(data1));
//    std::cout << data << std::endl;
    std::cout << data1 << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

#endif

//实现strstr，在一个字符串里面寻找另一个字符串是否存在,存在返回所在位置，不存在返回-1
#if 0
#include <iostream>
int mystrstr(const char* desc,const char* src){
    int where = 0;
    while (*desc){
        const char* point = desc;
        const char* src_first = src;
        int is_search = 1;
        while (*src_first){
            if(*point==0){
                //父串长度已经小于子串，确定找不到了
                return -1;
            }
            if(*src_first++ != *point++){
                is_search = 0;
                break;
            }
        }
        if(is_search){
            return where;
        }
        where++;
        desc++;
    }
    return -1;
}

int main(void)
{
    const char* src1 = "guzhiflf+66";
    const char* src2 = "+6";
    int i = mystrstr(src1,src2);
    std::cout << i << std::endl;
}

#endif

//删除字符串右边的特定字符
#if 0
#include <iostream>
#include <cstring>
void delrchr(char *str,const char ch = ' '){
    char *point = 0;
    while (*str){
        if(*str != ch){
            point = 0;
        }else{
            point = point == 0 ? str :point;
        }
        str++;
    }
    if(point != 0){
        *point = '\0';
    }
}

//删除字符串左边的特定字符
void dellchr(char *str,const char ch = ' '){
    char *point = str;
    while (*point==ch){
        point++;
    }
    //把point指针指向的size字节的数据覆盖到str所在的内存空间，不用memcpy的原因是str和point指向的内存有重叠
    memmove(str,point,strlen(str)-(str-point)+1);
}


//删除字符串中的某字符串
void delchr(char *str,const char* ch){
    char * copy_str = str;
    int ch_length = strlen(ch);
    int str_length = strlen(str);
    while (*copy_str){
        char *point = copy_str;
        const char * old_ch = ch;
        int is_find_ch = 1;//是否找到了ch字符串
        while (*old_ch){
            if(*point++!=*old_ch++){
                is_find_ch = 0;
                break;
            }
        }
        if(is_find_ch){
            //找到了子串，把子串删除
            memmove(copy_str,point,str_length-ch_length);
        }else{
            //找不到子串
            copy_str++;
        }
    }
}


int main(void)
{
    char str[] = "gzf6666444  ";
    char str1[] = "ggggzf6666444  ";
    char str2[] = "ggggzf6666444";
    delrchr(str,'6');
    dellchr(str1,'g');
    delchr(str2,"66");
    std::cout << str << "--" << std::endl;
    std::cout << str1 << "--" << std::endl;
    std::cout << str2 << "--" << std::endl;
    return 0;
}
#endif

//统计字符串中的字数
#if 0
#include <iostream>
#include <cstring>

/**
 * 统计字符串中的字数
 * @param str
 * @return
 */
int get_word_num(const char* str)
{
    int num = 0;
    while (*str){
        unsigned char th = (unsigned char)(*str);
        if(th<128){
            str++;
            num++;
        }else{
            str = str + 2; //GBK中文是2个字符，UTF8是3个
            num++;
        }
    }
    return num;
}

int main(void)
{
    const char* str = "古支付爱lf";
    std::cout << strlen(str) << std::endl;
    std::cout << get_word_num(str) << std::endl;
    return 0;
}

#endif

//分割字符串
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;
/**
 * 分割字符串
 * @param str
 * @param str_arr
 */
void str_split(const char* str,const char ch,vector<string> &str_arr){
    const char* left_point = str;
    const char* right_point = str;
     while (true){
        if((*right_point == ch) || (*right_point == '\0')){
            str_arr.push_back(string(left_point,right_point-left_point));
            if(*right_point == '\0'){
                return;
            }
            left_point = right_point+1;
        }
        right_point++;
     }
}


int main(void)
{
    const char* str = ",,aa,bb,cc,dd,";
//    const char* str = "cc";
    vector<string> str_arr;
    str_split(str,',',str_arr);
    vector<string>::iterator arr_ite = str_arr.begin();
    while (arr_ite != str_arr.end()){
        cout << *arr_ite << "-" << endl;
        arr_ite++;
    }
    return 0;
}
#endif


#if 0
#include <iostream>
#include <cstring>
/**
 * 解析xml
 * @param str 需要解析的xml字符串
 * @param field 需要的字段
 * @param value 字段的值存放在这
 */
void xmlParse(const char* str,const char* field,char* value)
{

}


int main(void)
{
}

#endif



//编程练习题end

//数据结构和算法start
#if 0
//静态顺序表
#include <iostream>
#include <cstring>
using namespace std;
#define MAXSIZE 100
typedef int ElemType;

struct SeqList{
    ElemType list[MAXSIZE];
    size_t size;
};

/**
 * 初始化为0
 * @param list
 */
void ClearList(SeqList& list){
    list.size = 0;
    memset(&list,0,sizeof(SeqList) * MAXSIZE);
}

/**
 * 插入元素
 * @param list
 * @param pos 第几个位置插入
 * @param elem
 * @return
 */
bool insert(SeqList& seq,size_t pos,const ElemType& elem){
    if(seq.size >= MAXSIZE){
        cout << "顺序表已满" << endl;
        return false;
    }
    if((pos > seq.size+1) || (pos < 1)){
        cout << "插入的位置不对" << endl;
        return false;
    }
    if(pos < seq.size + 1){
        //把pos位置和后面的数据往后移
        memcpy(seq.list+pos,seq.list+pos-1,(seq.size-pos+1) * sizeof(ElemType));
    }

    //在pos的位置插入
//    memcpy(seq.list[pos-1],&elem,sizeof(ElemType)); //c语言中，结构体不可以直接赋值，所以用memcpy

    //c++中，结构体可以直接赋值
    seq.list[pos-1] = elem;

    seq.size++;
    return true;

}


int main(void)
{
    SeqList list;
    ClearList(list);
    return 0;
}




#endif




//数据结构和算法end

//多线程和互斥锁的使用
#if 0
#include <thread>
#include <mutex>
#include <iostream>
class BankAccount{
public:
    BankAccount(int money):money(money){}
    ~BankAccount(){}
    void changeMoney(int c_money){
        money -= c_money;
    }
    int getMoney(){
        return money;
    }
//    void lock(){
//        m_lock.lock();
//    }
//    void unlock(){
//        m_lock.unlock();
//    }
    std::mutex& getLock(){
        return m_lock;
    }
private:
    int money;
    std::mutex m_lock;
};

void exchangeMoney(BankAccount& A,BankAccount& B,int money){
//    A.lock();
//    B.lock();
    std::lock(A.getLock(),B.getLock());
    std::lock_guard<std::mutex> lo(A.getLock(),std::adopt_lock);
    std::lock_guard<std::mutex> lo1(B.getLock(),std::adopt_lock);
    A.changeMoney(money);
    B.changeMoney(-money);
//    A.unlock();
//    B.unlock();
}

int main()
{
    BankAccount A(60);
    BankAccount B(-60);
    std::thread t1([&]{
        for (int i = 0; i < 20000; ++i) {
            exchangeMoney(A,B,20);
        }
    });
    std::thread t2([&]{
        for (int i = 0; i < 20000; ++i) {
            exchangeMoney(B,A,20);
        }
    });
    t1.join();
    t2.join();
    std::cout << A.getMoney() << "  " << B.getMoney() << std::endl;
}
#endif


//构造函数和作用域测试
#if 0
#include<iostream>
#include<thread>
#include<chrono>
#include<vector>
class Test{
public:
    Test(int num):num(new int(num)){
        std::cout << "default construct" << std::endl;
    }
    Test(const Test& t){
        this->num = new int(*(t.num));
        std::cout << "copy construct" << std::endl;
    }
    Test(Test&& t) noexcept {
        this->num = t.num;
        t.num = nullptr;
        delete t.num;
        std::cout << "move construct" << std::endl;
    }
    ~Test(){
        if(this->num == nullptr)
        {
            std::cout << "null" << std::endl;
            return;
        }
        this->num = nullptr;
        delete this->num;
        std::cout << "destruct" << std::endl;
    }
private:
    int* num;
};

int main(){
//    while(true){
//        std::cout << "start" << std::endl;
//        Test t;//循环一次调用一次析构
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//        std::cout << "end" << std::endl;
//    }
    std::vector<Test> t_list;
    //下面的代码，push到容器中时会调用移动构造函数转移资源，扩容时每个元素调用移动构造函数转移资源到新空间，然后调用每个元素的析构函数
//    Test t1(1);
//    t_list.push_back(std::move(t1));
//    Test t2(2);
//    t_list.push_back(std::move(t2));
//    Test t3(3);
//    t_list.push_back(std::move(t3));
//    Test t4(4);
//    t_list.push_back(std::move(t4));
    //下面的代码，push到容器中时会调用拷贝构造函数生成资源，扩容时每个元素调用移动构造函数转移资源到新空间，然后调用每个元素的析构函数
    Test t1(1);
    t_list.push_back(t1);
    Test t2(2);
    t_list.push_back(t2);
    Test t3(3);
    t_list.push_back(t3);
    Test t4(4);
    t_list.push_back(t4);
    return 0;
}
#endif


//虚函数相关测试
#if 0
#include <iostream>
class Test{
public:
    Test(int num):num(num){
        std::cout << "default construct" << std::endl;
    }

    void static_test(){
        std::cout << "static_test" << std::endl;
    }

    virtual void dynamics_test()
    {
        std::cout << "dynamics_test" << std::endl;
    }

    ~Test(){
        std::cout << "destruct" << std::endl;
    }
private:
    int num;
};

class TestChild:public Test{
public:
    TestChild(int num1, int num) : Test(num1), c_num(num) {
        std::cout << "child default construct" << std::endl;
    }

    void static_test(){
        std::cout << "child static_test" << std::endl;
    }

    void dynamics_test()
    {
        std::cout << "child dynamics_test" << std::endl;
    }

    void c_test()
    {
        std::cout << "c_test" << std::endl;
    }

    ~TestChild(){
        std::cout << "child destruct" << std::endl;
    }
private:
    int c_num;
};

int main()
{
    Test t(1);//因为Test存在虚函数，所以t对象的内存中除了成员num=1之外，还有一个虚函数指针（指针位置通常在对象的最前面，也就是该对象一共有4+8个字节大小），指向该类在只读数据段中的虚函数表，虚函数表里面存的是该类所有虚函数的地址
    Test *pt = &t;
    /**
     * 静态绑定,调用这个方法时发现是普通函数，直接调用该指针对应的类方法的地址 对应汇编call 0x555555555396 <Test::m_test()>
     */
    pt->static_test();
    /**
     * 动态绑定，调用这个方法时发现是虚函数，通过对象的虚函数指针找到虚函数表中对应函数的地址，放到寄存器中，再进行调用。
     * 因为是运行时动态获取调用地址，所以叫做动态绑定。对应汇编 mov -0x38(%rbp),%rax  mov %rax,%rdi  call *%rdx
     */
    pt->dynamics_test();


    //下面是继承的情况
    /**
     * 如果继承的类中有虚函数，则子类对象的相应方法自动成为虚函数（不管有没用声明为virtual），也会有它的虚函数表
     */
    TestChild tc(1,2);
    //Test t1 = tc;//t1只能调用Test中的方法，相当于tc隐式转换为Test类的对象
    //t1.static_test();//调用的是Test中的static_test
    Test *pt1 = &tc;
    /**
     * 静态绑定,调用这个方法时发现是普通函数，直接调用该指针对应的类方法的地址 对应汇编call 0x555555555396 <Test::m_test()>
     */
    pt1->static_test();
    /**
     * 动态绑定，调用这个方法时发现是虚函数，通过对象的虚函数指针找到虚函数表中对应函数的地址，放到寄存器中，再进行调用。
     * 因为是运行时动态获取调用地址，所以叫做动态绑定。对应汇编 mov -0x38(%rbp),%rax  mov %rax,%rdi  call *%rdx
     */
    pt1->dynamics_test();
    return 0;
}

#endif

#include <iostream>

class Test {
public:
    Test(int n) : num(new int(n)) {
        std::cout << "default construct" << std::endl;
    }

    Test(const Test &t) {
        this->num = new int(*(t.num));
        std::cout << "copy construct" << std::endl;
    }

    Test &operator=(const Test &t) {
        delete this->num;
        this->num = new int(*(t.num));
        std::cout << "operator =" << std::endl;
        return *this;
    }

    Test(Test &&t) {
        this->num = t.num;
        t.num = nullptr;
        std::cout << "move construct" << std::endl;
    }

    Test &operator=(Test &&t) {
        this->num = t.num;
        t.num = nullptr;
        std::cout << "move =" << std::endl;
    }

    int getNum() const {
        return *(this->num);
    }

    ~Test() {
        delete num;
    }

private:
    int *num = nullptr;
};

Test getTest() {
    Test t(9);
    return t;
}

void printTest(Test &&t) {
    std::cout << t.getNum() << std::endl;
}

int main() {
//    Test t1(5);//默认构造被调用
//    Test t2 = t1;//拷贝构造被调用
    Test t3(3);
//    t3 = t1;//赋值=被调用
//    Test t4 = getTest();//如果定义了移动构造函数则被调用，否则调用拷贝构造函数
    Test t5 = std::move(t3);//如果定义了移动构造函数则被调用，否则调用拷贝构造函数
    printTest(std::move(t5));//右值引用 t5被函数形参引用了，不会调用拷贝构造函数和移动构造函数
//    Test&& t6 = std::move(t1);//右值引用 t6相当于t1的别名，不会调用移动构造函数，只是引用
//    Test t7(5);
//    Test t8(3);
//    t7 = std::move(t8);
    return 0;
}





