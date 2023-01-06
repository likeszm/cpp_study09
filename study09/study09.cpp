/*
* 名称： 时间库、输入输出、结构体测试
* 
* 
* 收获：
*   1、cerr 和 clog 函数使用效果虽然和 cout 一样
*   但是面对大型工程还是用这两个会方便调试
* 
* 存疑代码：
*   1、char *ctime(const time_t *timer) 参数被const修饰？
* 
*/

#include <iostream>
#include <ctime>
#include <windows.h>         //Sleep()函数


struct book_struct
{                       //注意全是;结尾, 可以设定初始值
    std::string title = "NULL";
    std::string author = "NULL";
    std::string subject = "NULL";
    int id = -1;
};


void time_lib_test(void);
void cerr_clog_test(void);
void struct_test(void);
void struct_as_parameter(book_struct book);
void typedef_test(void);


int main()
{
    //time_lib_test();
    //cerr_clog_test();
    //struct_test();

    //book_struct book_test = { "自深深处" , "王尔德" , "文学" , 1112 };
    //struct_as_parameter(book_test);

    //typedef_test();


    std::cout << "\n测试完成\n";
    return 0;
}

void time_lib_test(void)
{
    std::time_t time_test = 0;


    std::wcout << "当前时间: time(&time_test) = " << time(&time_test) << std::endl;
    std::wcout << "\ttime_test =\t" << time_test << std::endl;
    std::wcout << std::endl;


    time_test -= 3600;       //通过这一句可以发现ctime_s函数本质上只是实现格式转换
    char time_data_array[40];
    std::wcout << "当前时间: ctime_s(time_data_array,sizeof(time_data_array),&time_test) = " << ctime_s(time_data_array,sizeof(time_data_array),&time_test) << std::endl;
    std::wcout << "\ttime_test =\t" << time_test << std::endl;
    std::wcout << "\time_data_array =\t" << time_data_array << std::endl;
    std::wcout << std::endl;

    //类似的函数:    gmtime() 用来获取格林尼治标准时间（GMT）
    time_test -= 3600;      //通过这一句可以发现localtime_s函数本质上只是实现格式转换
    std::tm time_data_struct;
    std::wcout << "当地时间: localtime_s(&time_data_struct ,&time_test) = " << localtime_s(&time_data_struct ,&time_test) << std::endl;
    std::wcout << "\ttime_test =\t" << time_test << std::endl;
    std::wcout << "\time_data_struct.tm_year + 1900 =\t" << time_data_struct.tm_year + 1900 << std::endl;
    std::wcout << "\time_data_struct.tm_yday =\t" << time_data_struct.tm_yday << std::endl;
    std::wcout << "\time_data_struct.tm_wday =\t" << time_data_struct.tm_wday << std::endl;
    std::wcout << "\time_data_struct.tm_hour =\t" << time_data_struct.tm_hour << std::endl;
    std::wcout << "\time_data_struct.tm_isdst =\t" << time_data_struct.tm_isdst << std::endl;
    std::wcout << "\time_data_struct.tm_mday =\t" << time_data_struct.tm_mday << std::endl;
    std::wcout << "\time_data_struct.tm_min =\t" << time_data_struct.tm_min << std::endl;
    std::wcout << "\time_data_struct.tm_mon =\t" << time_data_struct.tm_mon << std::endl;
    std::wcout << "\time_data_struct.tm_sec =\t" << time_data_struct.tm_sec << std::endl;
    std::wcout << std::endl;


    std::wcout << "CPU时间1: clock() = " << clock() << std::endl;
    std::wcout << "CPU时间2: clock() = " << clock() << std::endl;
    std::wcout << "休眠5个时钟 " << std::endl;
    Sleep(5);
    std::wcout << "CPU时间3: clock() = " << clock() << std::endl;
    std::wcout << "CPU时间4: clock() = " << clock() << std::endl;
    std::wcout << std::endl;


    time_test -= 3600;      //通过这一句可以发现asctime_s函数本质上只是实现格式转换
    std::wcout << "时间: asctime_s(time_data_array, sizeof(time_data_array), &time_data_struct)  = " << asctime_s(time_data_array, sizeof(time_data_array), &time_data_struct) << std::endl;
    std::wcout << "\time_data_array =\t" << time_data_array << std::endl;
    std::wcout << std::endl;


    //反向格式转换
    std::wcout << "当前秒数: mktime(&time_data_struct) = " << mktime(&time_data_struct) << std::endl;
    std::wcout << std::endl;

    time_t time_test_1, time_test_2;
    std::wcout << "当前时间: time(&time_test_1) = " << time(&time_test_1) << std::endl;
    std::wcout << "休眠500个时钟 " << std::endl;
    Sleep(500);
    std::wcout << "当前时间: time(&time_test_2) = " << time(&time_test_2) << std::endl;
    std::wcout << "差距: difftimedifftime(time_test_2, time_test_1) = " << difftime(time_test_2, time_test_1) << std::endl;
    std::wcout << std::endl;


    //仍然是一个格式转换函数，不过自定义程度高
    strftime(time_data_array, sizeof(time_data_array), "%Y-%m-%d %H:%M:%S", &time_data_struct);
    std::wcout << "格式化的日期 & 时间 : | " << time_data_array << " |\n";


}

void cerr_clog_test(void)
{
    //cerr
    char str[] = "Unable to read....";

    std::cerr << "Error message : " << str << std::endl;


    //clog
    char str1[] = "Unable to read1....";

    std::clog << "Error message : " << str1 << std::endl;
}

void struct_test(void)
{
    std::cout << "结构体创建并初始化" << std::endl;

    book_struct book_1 = { "自深深处" , "王尔德" , "文学" , 1112 };
    book_struct book_2;
    book_2.title = "人间失格";
    book_2.author = "太宰治";
    book_2.subject = "文学";
//    book_2.id = 1234;             //测试初始值是否有效

    std::cout << "尝试访问：" << std::endl;

    std::cout << "书名：" << book_1.title << std::endl;
    std::cout << "作者：" << book_1.author << std::endl;
    std::cout << "类别：" << book_1.subject << std::endl;
    std::cout << "编号：" << book_1.id << std::endl;

    std::cout << std::endl;

    book_struct* p_book_2 = &book_2;

    std::cout << "书名：" << p_book_2->title << std::endl;
    std::cout << "作者：" << p_book_2->author << std::endl;
    std::cout << "类别：" << p_book_2->subject << std::endl;
    std::cout << "编号：" << p_book_2->id << std::endl;

    std::cout << std::endl;

}

void struct_as_parameter(book_struct book)
{
    std::cout << "尝试访问：" << std::endl;

    std::cout << "书名：" << book.title << std::endl;
    std::cout << "作者：" << book.author << std::endl;
    std::cout << "类别：" << book.subject << std::endl;
    std::cout << "编号：" << book.id << std::endl;
}

void typedef_test(void)
{
    typedef int* pint;
    int test = 10;
    pint p_test = &test;

    std::cout << "test = " << test << std::endl
        << "&test = " << &test << std::endl;
    std::cout << "pint类型的 p_test = " << p_test << std::endl
        << "*p_test = " << *p_test << std::endl;

}
