# C++ Primer Chapter2:C++基础2.5-2.6

## 处理类型

* 程序的复杂性体现在两方面：一方面是一些类型难以“拼写”，名字及即容易写错，又无法明确表达其真实目的和含义。二是有时候根本搞不清楚我们需要什么，不得不从程序的上下文寻求帮助。

### 类型别名

* `类型别名(type alias)`是一个名字，他是某种类型的同义词。类型别名让复杂的类型名字变得简单明了、易于理解和使用，还有助于清楚地知道使用该类型的真实目的。
* 两种方法可用于定义类型别名，一是使用关键字typedef。其中关键字typedef作为`声明语句中的基本数据类型的一部分`（与后面真正的基本数据类型共同组成数据类型）出现。含有typedef的声明语句定义的不再是变量而是类型别名。这里的声明符也可以包含类型修饰，所以也能够从基本数据类型构造出复合类型。
* 另一种新方法是使用`别名声明(alias declaration)`来定义类型的别名:

        using SI=Sales_item;//SI是Sales_item的同义词

* using关键字作为别名声明的开始，其后跟别名，目的是把等号左侧的名字规定成等号右边类型的别名。
* 类型别名和类型的名字等价，只要是类型的名字能出现的地方，就能使用类型别名。

### 指针、常量和类型别名

* 如果类型别名代替的是符合类型或者常量，那么就会产生意想不到的效果，例如以下的声明语句用到了类型pstring，它实际上是类型char*的别名。

        typedef char *pstring;
        const pstring catr=0;//cstr是指向char的常量指针
        const pstring *ps;//ps是一个指针，它的对象时指向char的常量指针。

* const是对类型的修饰，pstring是指向char的指针，因此，const pstring就是指向char的常量指针，而非指向字符常量的指针。
* 把类型别名替换成他本来的样子，这样的思想是错误的。

## auto类型说明符
* 有时我们需要把表达式的值赋给变量，这要求知道表达式的类型，有时候难以分析，甚至分析不了。c++11引入了`auto`类型说明符，可以让编译器代替我们去分析表达式所属的类型，auto定义的变量必须有初始值：

        //由val1和val2相加的结果可以推断出item的类型
        auto item=val1+val2;//item初始化为val1和val2相加的结果

* auto也能在一条语句中声明多个变量，但是变量的初始基本数据类型都必须一样。

### 符合类型、常量和auto
* 编译器推断出的auto类型有时候和初始值类型并不完全一样。编译器会适当地改变结果类型。比如，当引用被用作初始值时，真正参与初始化的其实是引用对象的值。此时编译器一引用对象的类型作为auto的类型。

        int i=0,&r=i;
        auto a=r;//a是一个整数(r是i的别名，而i是一个整数)

* 其次auto一般会忽略掉顶层const,同时底层const则会保留下来，比如当初始值是一个纸箱常量的指针时：

        const int ci=i,&cr=ci;
        auto b=ci;//b是一个整数(ci的顶层const特性被忽略掉了)
        auto c=cr;//c是一个整数(cr是ci的别名，ci本身是一个顶层const)
        auto d=&i;//d是一个整型指针(整数的地址就是指向整数的指针)
        auto e=&ci;//e是一个指向整数常量的指针(对常量对象取地址是一种底层const)

* 如果希望推断出的auto类型是一个顶层const，需要明确指出：

        const auto f=ci;//ci的推演类型是int，f是const int

* 还可以将引用的类型设为auto，此时原来的初始化规则仍然使用：

        auto &g=ci;//g是一个整型常量引用，绑定到ci
        auto &h=42;//错误：不能为非常量引用绑定字面值
        const auto &j=42;//正确：可以为常量引用绑定字面值

* 设置一个类型为auto的引用时，初始值中的顶层常量属性仍然保留，如果我们给初始值绑定一个引用，则此时的常量就不是顶层常量了。


## decltyoe类型指示符
* 又是希望从表达式的类型推断出要定义的变量的类型，但是不想用该表达式的值初始化变量，这是可以使用第二种类型说明符`decltype`，它的作用是选择并返回操作数的数据类型。在此过程中，编译器分析表达式并得到它的类型，却不切实际计算表达式的值：

        decltype(f()) sum=x;//sum的类型就是函数f的返回类型
* 编译器并不实际调用函数f，而是使用当调用发生时f的返回值类型作为sum的类型。
* 如果decltype使用的表达式是一个变量，则decltype返回该变量的类型(包括顶层const和引用在内)：

        const int ci=0,&cj=ci;
        decltype(ci) x=0;//x的类型是const int
        decltype(cj) y=x;//y的类型是const int &，y绑定到变量x
        decltype(cj) z;//错误：z是一个引用，必须初始化

* 引用从来都作为其所指的对象的通一次出现，只有用在decltype处是一个例外。


### decltype和引用
* 如果decltype使用的表达式不是一个变量，则decltype返回表达式结果对应的类型。有些表达式奖项decltype返回一个引用类型。一般来说当这种情况发生时，意味着表达式的结果对象能作为一条赋值语句的左值：

        //decltype的结果可以是引用类型
        int i=42,*p=&i,&r=i;
        deltype(r+0) b;//正确：加法的结果是int，所以b是一个未被初始化的int
        decltype(*p) c;c是int&，必须初始化

* 如果表达式的内容是解引用操作，则decltype将得到这个引用类型。解引用指针可以得到指针所指的对象，而且还能给这个对象赋值，所以，decltype(*p)的结果类型就是int &，而非int。
* decltyep和auto的另一处重要区别是，decltype的结果类型与表达式形式密切相关，有一种情况要特别注意：对于decltype所用的表达式来说，如果变量名加上了一对括号，则得到的类型与不加括号是会有所不同，如果decltype使用的是一个不叫括号的变量，则得到的结果就是该变量的类型：如果给变量加上了一层或多层括号，编译器就会把他当成是一个表达式。变量是一种可以作为复制语句坐直的特殊表达式，所以这样的decltype就会得到引用类型：

        //decltype的表达式如果是加上了括号的变量，结果将是引用
        decltype((i)) d;//错误：d是int&，必须初始化
        decltype(i) e;//正确，e是一个未初始化的int

* `切记：decltype((variable))（注意是双层括号）的结果永远是引用，而decltype(variable)结果只有当variable本身就是一个引用时才是引用。`


## 自定义数据结构
* 数据结构就是把一组相关的数据元素组织起来使用它们的策略和方法。举个例子，之前用的Sales_item类就是一个数据结构。


### 定义Sales_date类型
* 初步的想法是用户能直接访问其中的数据元素，也能实现一些基本操作。Sales_date的初步定义如下：

        struct Sales_date
        {
            std::string bookNo;
            unsigned unites_sold=0;
            double revenue=0.0;
        };
* 我们的类以关键字struct开始，紧跟着类名和类体(其中类体部分可以为空)。类体形成了新的作用域。类内部定义的名字必须唯一，但可以与外部定义的名字重复。
* 分号必不可少：

        struct Sales_date{/*...*/}accum,trans,*salesptr;
        //与上一条语句等价但可能更好一些
        struct Sales_date{/*...*/};
        Sales_date accum,trans,*salesptr;

* 分号表示声明符（通常为空）的结束，一般来说，最好不要把对象的定义和类的定义放在一起，，这么做无异于把两种不同的实体放在一个语句里，一会定义类，一会定义变量，显然这是一种不被建议的行为。


### 类数据成员
* 类体定义类的成员，我们的类只有`数据成员(date member)`，类的数据成员定义了类的对象的具体内容，每个对象有自己的一份数据成员拷贝。修改一个对象的数据成员，不会影响其他Sales_date的对象。
* 定义数据成员的方法：首先说明一个基本类型，随后紧跟一个或多个说明符。我们的类有三个数据成员：一个名为bookNO的string成员，一个名为unites_sold的unsigned成员和一个名为revenue的double成员。之后每个Sales_date对象都将包含这三个数据成员。
* c++11新标准规定，可以为数据成员提供一个`类内初始值(in-class initializer)`。创建对象时，类内初始值将用于初始化数据成员，没有初始值的成员江北默认初始化为类内初始值。比如我们定义的Sales_date类中的空字符串、0、0.0都是类内初始值。
* 不能使用圆括号，要使用花括号。


## 使用Sales_date类
* 和Sales_item类不同的是，我们自己创建的类没有提供任何操作，使用者要向执行操作就必须自己实现。

### 添加两个Sales-date类
* 我们要自己编写代码实现输入、输出和相加的功能。总的来说，程序的结构如下：

        #include<ioostream>
        #include<string>
        #include"Sales_date.h"
        int main()
        {
            Sales_date date1,date2;
            //读入date1和date2的代码
            //检查date1和date2的ISBN码是否相同的代码
            //如果相同，求date1和date2的总和
        }

* 包含头文件string，因为我们的代码中要用到string类型的成员变量bookNo。


### Sales_date对象读入数据
* string类型其实就是字符的序列，它的操作有>>、<<和==等，功能分别是读入字符串、写出字符串、比较字符串。这样我们就能书写代码读入第一笔交易了：

        double price=0;//书的单价，用于计算销售收入
        //读入第一笔交易：ISBN、销售数量、单价
        std::cin>>date1.bookNo>>date1.unites_sold>>price;
        //计算销售收入
        date1.revenue=date1.unites_sold*price;
        //读入第二笔交易
        std::cin>>date2.bookNo>>date2.unites_sold>>price;
        date2.revenue=date2.unites_sold*price;

### 输出两个Sales_date对象的和
* 接下来的工作是检查两笔交易涉及的ISBN编号是否相同：

        if(date1.bookNo==date2.bookNo)
        {
            unsigned totalCnt=date1.unites_sold+date2.unites_sold;
            double totalRevenue=date1.revenue+date2.revenue;
            //输出ISBN、总销售量、总销售额、平均价格
            std::cout<<date1.bookNo<<" "<<totalCnt
            <<" "<<totalRevenue<<" ";
            if(totalCnt!=0)
            {
                std::cout<<totalRevenue/totalCnt<<std::endl;
            }
            else
            {
                std::cout<<"(no sales!)"<<std::endl;
            }
        }
        else
        {
            //两笔交易的ISBN不一样
            std::cerr<<"Date Must Refer To The Same ISBN"<<std::endl;
            return -1; //表示着失败   
        }



## 编写自己的头文件
* 尽管之前讲过可以再函数体内定义类，但是这样的类毕竟受到了一些限制，所以，类一般都不定义在函数体内。挡在函数体外部定义类时，在各个指定的文件中可能只有着一处该类的定义。如果要在不同的文件中使用同一个类，类的定义就必须保持一致。
* 类通常被定义在头文件中，而且类所在的头文件的名字应与类的保持一致。
* 头文件通常包含哪些只能被定义一次的实体，如类、const和constptr变量等。头文件也通常用到其他头文件的功能。头文件一旦改变，相关的源文件必须重新编译以获取更新过的声明。

### 预处理器概述
* 确保头文件多次包含仍能正常工作的常用技术是`预处理器(preprocess)`,它由c++语言从c语言继承而来。预处理器实在编译之前执行的一段程序，可以部分的改变我们缩写的程序。当预处理器看到#include标记时就会用指定的头文件的内容代替#include.
* c++程序还会用到的一项与处理功能是`头文件保护符(header guard)`，头文件保护符依赖于预处理变量。预处理变量有两种状态：已定义和未定义。#define指令把一个名字设为预处理变量，两外两个指令则分别检查某个指定的预处理变量是否已经定义：#ifdef当且仅当变量一定意识为真，#ifdef当且仅当变量为定义是为真。则执行后续操作直至遇到#endif指令为止。
* 使用这些功能就能有效防止重复包含发生：

                #ifdef SALES_DATE_H
                #define SALES_DATE_H
                #incldue<string>
                struct Sales_date
                {
                        std::string bookNo;
                        unsigned unites_sold=0;
                        double revenue=0.0;
                };
                #endif

* 第一次包含Sales_date.h时，#ifdef的检查结果为真预处理器将顺序执行后面的操作直到遇到#endif为止。此时，预处理变量SALES_DATE_H的只将变为已定义，而且Sales_date.h也会被拷贝到我们的城西中来。后面如果再一次包含Sales_date.h，则#ifdef的检查结果将为假。编译器将忽略这一部分
* 预处理变量无视c++语言中关于作用域的规则。