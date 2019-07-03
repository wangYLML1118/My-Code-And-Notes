# C++ Primer Chapter2:C++基础 2.3-2.4
## const限定符
* 有时我们希望定义这样一类变量，当我们觉得变量的值不合适时可以进行调整，另一方面，为了防止程序改变了这一变量的值。我们可以用const对这个变量的类型加以限定。
* 任何试图为被`const限定变量类型的变量`赋值的行为都将引发错误
* 因为const对象一旦创建后其值就不能在改变，所以const对象必须被初始化，初始值可以是任意复杂的表达式。

        const int i=get_size();//正确，运行时初始化
        const int j=42;//正确，编译时初始化
        const int k;//错误：k是一个未经初始化的常量

### 初始化和const
* 对象的类型决定了其上的操作。与非const类型所能参与的操作相比，const类型的对象能完成其中一大部分，但也不是所有的操作都适用。主要的限制是只能在const类型上执行`不改变其值`的操作。
* 在不改变const对象操作中有一种是初始化，如果利用一个对象去初始化另一个对象，则他们是不是const都无所谓。

        int i=42;
        const int ci=i;//正确，i的值被拷贝给了ci
        int j=ci;//正确，ci的值被拷贝给了j

* ci的const特性只有在执行改变ci的操作时才会起作用。拷贝一个对象的值并不会改变他，一旦拷贝完成，新的对象和原来的对象就没什么联系了。

### 默认状态下，const对象仅在文件内有效
* 当以编译时初始化的方式定义一个const对象时，编译器将在编译时把用到该变量的地方都替换成对应的值。所以编译器必须知道该变量的初始值。如果程序包含了多个文件，则每个用了const对象的文件都必须得能访问到它的初始值才行。所以每一个用到变量的文件中都要包含对他的定义。为了避免同一变量的重复定义，默认情况下，const对象被设为仅在文件中有效。所以当多个文件中出现了同名的const变量是，相当于在不同文件中分别定义了独立的变量。
* 如果想只在一个文件中定义const，而在其他文件中声明并使用，那么需要，对于const变量，不管是定义还是声明它都在前加上`extern关键字`。即如果想在多个文件之间共享const对象，就必须在变量的定义前添加extern关键字。

## const的引用
* 可以把引用绑定到const对象身上，就想绑定到其他对象身上，称之为`对常量的引用(reference to const)`。对常量的引用不能被用作修改它所绑定的对象。

        常量引用是对const的引用：
        经常把词组“对const的引用”简称为常量引用，严格来说，并不存在常量引用，因为引用并不是一个对象，所以我们没法让引用本身恒定不变。事实上，由于c++原因并不允许随意修改引用对象，所以从这层意思上理解所有的引用有都算是常量，引用的对喜爱那个是常量还是非常量可以决定其所能参与的操作，却无论如何多不会影响到引用和对象本身的绑定关系。

### 初始化和对const的引用
* 之前提到，引用的类型必须与其所引用的对象的类型保持一致，但是有两种例外。第一种就是在初始化常量引用时允许使用任意表达式作为初始值，只要该结果的表达式能转换成引用的类型即可。尤其，允许为一个常量引用绑定非常量的对象、字面值甚至是一般表达式。

        int i=42;
        const int &r1=i;//允许将const int&绑定到一个普通的int对象上
        const int &r2=42;//正确r1是一个常量引用
        const int &r3=r1*2;//正确，r3是一个常量引用
        int &r4=r1*2;//错误：r4是一个普通的费常量引用(非const)
* 要理解这种里外发生的原因，首先要了解当一个常量引用被绑定到另外一种类型上是发生了什么。

        double dval=3.14；
        const int &r1=dval；

* 此处r1引用了一个int类型的数，对r1的操作应该是整数运算，但dval却是一个双精度浮点数，所以编译器把上述代码变成了如下形式：

        const int temp=dval;//由双精度浮点数生成一个临时整型常量
        const int &r1=temp;//让r1绑定这个临时量

* 在这种情况下，r1绑定了一个`临时量(temporary)`对象。就是当编译器需要一个空间来暂存表达式的求值结果时，临时创建的一个未命名的对象。常称为临时量。

### 对const的引用可能引用一个并非const的对象
* 常量引用仅对引用可参与的操作进行了限定，对于引用的对象本身是不是一个常量未作限定，因为对象也可能是个非常量，所以允许通过其他途径改变它的值：

        int i=42;
        int &r1=i;//引用r1绑定对象1
        const int &r2=i;//r2也绑定对象i，但是不允许通过引用r2修改对象i的值
        r1=0;//r1并非常量，i的值修改为0
        r2=0;//错误：r2是常量引用

## 指针和const
* 与引用一样，也可以令指针指向常量或非常量。类似于常量引用(如上),`指向常量的指针(pointer yo const)`不能用于改变其所指对象的值。要想存放常量对象的地址，只能使用指向常量的指针。

        const double pi=3.14;//pi 是个常量他的值不能改变
        double *ptr=&pi;//错误：ptr是一个普通指针
        const double *cptr=&pi;//正确：cptr可以指向一个双精度常量
        *cptr=42;//错误：不能给cptr赋值，因为是指向常量的指针

* 前面提到，指针的类型必须与其所指对象的类型一样，但是有两个例外。第一种例外是允许令一个指向常量的指针指向一个非常量对象：

        double dval=3.14;//dval是一个双精度浮点数
        cptr=&dval;//正确，但是不能通过cptr改变dval的值。
        
* 试试这样想：所谓指指向常量的指针或引用，都是指针或引用自以为指向了常量，所以自觉地不去改变所值对象的值。

### const指针
* 指针是对象而引用不是，因此就像其他对象类型一样，允许把指针本身定为常量。`常量指针(const pointer)`必须初始化，而且一旦初始化完成，则它的值(也就是存放在指针中的那个地址)就不能再改变。把`*`放在`const关键字`之前用以说明指针是一个常量。`不变的是指针本身的值而非指向的那个值`:

        int errNumb=0;
        int *const curErr=errNumb;//curErr将一直指向errNumb
        const double p1=3.14159;
        const double *const pip=&pi;//pip是一个指向常量对象的常量指针

* 弄清楚这些声明的含义最行之有效的方法是从右往左阅读。
* 指针本身是一个常量并不意味着不能通过指针修改其所指对象的值，能否这样做完全依赖于所指对象的类型。

## 顶层const
* 指针本身是一个对象，它又可以指向另外一个对象。因此，指针本身是不是常量以及指针所指的是不是一个常量就是两个相互独立的问题。用名词`顶层const(top-level const)`表示指针本身是个常量，而用名词`底层const(low-level const)`表示指针所指的对象是一个常量。
* 顶层const可以表示任意的对象是常量，这一点对于任何数据类型都适用，如算数类型、类、指针等。底层const则与指针和引用等符合类型的基本类型部分有关。指针类型既可以是顶层const，又可以是底层const。
* 当执行对象的拷贝操作时，常量是顶层const还是底层const区别明显，其中顶层const不受什么影响。执行拷贝操作并不会改变被拷贝对象的值。拷入和拷出的对象是否是常量都没什么影响。
* 底层const的限制不能忽视。当执行对象的拷贝操作时，拷入和拷出的对象不需具有相同的底层const资格，或者两个对象的数据类型必须能转换。一般来说，非常量可以转换成常量，反之则不行：

        int *p=p3;//错误：p3包含底层const的定义，而p没有
        p2=p3;//正确：p2和p3都是底层const
        p2=&i;//正确：int *能转换成const int *
        int &r=ci;//错误：普通的int&不能绑定到int常量上
        const int &r2=i;//正确：const int&可以绑定到一个普通int上


## constexpr和常量表达式
* `常量表达式(const expression)`是指值不会改变并且在`编译过程`就能得到计算结果的表达式。显然，字面值属于常量表达式，用常量表达式初始化的const对象也是常量表达式。
* 一个对象(或表达式)是不是常量表达式由他的数据类型和初始值共同决定，

        const int max_files=20;//max_files是常量表达式
        const int limit=max_files+1;//limit是常量表达式
        int staff_size=27;//staff_size不是常量表达式
        const int sz=get_size();//sz不是常量表达式
* 尽管staff的初始值是个字面值常量，但由于他的数据类型只是一个普通的int，所以它不属于常量表达式，另一方面，尽管sz本身是一个常量，但他的具体值知道运行时才能获得。

### constexpr变量
* c++11新标准允许将变量声明为constexpr类型以便由编译器
来验证变量的值是否是常量表达式，声明为constexpr的变量一定是一个常量，而且必须用常量表达式来初始化。

        constexpr int mf=20;//20是常量表达式
        constexpr int limit=mf+1;//mf+1是常量表达式
        constexpr int sz=size();//只有当size是一个constexpr函数是才是一条正确的声明语句

* 一般来说，如果你认为变量是一个常数表达式，那就把他声明长constexpr类型。


### 字面值类型
* 常量表达式的值要在编译时得到计算，所以对声明constexpr时用到的类型必须有所限制。`字面值类型(literal type)`一般比较简单。值也显而易见、容易得到。
* 目前，算术类型、引用和指针都属于字面值类型。自定义类Sales_item、IO库、string类型则不属于字面值类型，也就不能被定义成constexpr。其他字面值将在以后介绍
* 尽管指针和引用都能定义成constexpr，但他们的初始值收到严格限制，一个constexpr指针的初始值必须是nullptr或者0。或是存储于某个固定地址中的对象。

### 指针和constextr
* 在constexpr生命中如果定义了一个指针，限定符constexpr仅对指针有效，与指针所指的对象无关。

        const int *p=nullptr;//p是一个指向整型常量的指针
        constexpr int *q=nullptr;//q是一个指向整数的常量指针

* p和q的类型相差甚远，p是一个指向常量的指针，而q是一个常量指针。其中的关键在于constexpr把他所定义的对象置为了顶层const。与其他常量指针相似，constexpr指针既可以指向常量也可以指向非常量。

        constexpr int *np=nullptr;//np是一个指向整数的常量指针，其值为空
        int j=0;
        constexpr int i=42;//i的类型是整型常量
        //i、j都必须定义在函数体之外
        constexpr const int *p=&i;//p是常量指针指向整型常量i
        constexpr int *p1=&j;//p1是常量指针，指向整数j