# MinGW、mingw64、GCC、gcc、g++

VScode只是一个编辑器，没有编译调试功能，用户可以根据自身需求来配置特定的编译器和插件

## mingw64

MinGW（Minimalist GNU for Windows）是一个为 Windows 系统提供 GCC（GNU Compiler Collection）的编译器系统。它包括了 C、C++ 和 Fortran 的编译器以及其他相关工具。

MinGW-w64 是 MinGW 的一个分支，它支持 32 位和 64 位 Windows 系统。

mingw64 是 MinGW-w64 分发版的一部分，它提供了针对 Windows 64 位系统的交叉编译工具链，包含了 GCC 和 G++ 编译器的特定版本，这些版本被配置为交叉编译环境，用于生成 Windows 平台上的可执行文件。

总结来说，mingw64 使得在 Windows 上进行原生编译成为可能，不需要依赖于 Windows 的 Visual C++ 工具链。

## gcc 和 g++

gcc 和 g++ 都是 GNU 编译器集合（GNU Compiler Collection，简称 GCC）的一部分，但它们用于编译不同类型的程序。

gcc：最初是 GNU C Compiler 的缩写，它是用于编译 C 语言程序的编译器。随着 GCC 的发展，它现在支持多种编程语言，包括 C、Objective-C、Fortran、Ada 等，因此现在通常被称为 GNU Compiler Collection。对于 C 程序，你会使用 gcc 命令来编译。

g++：是 GCC 的一部分，专门用于编译 C++ 程序。它支持 C++ 语言的所有特性，包括类、继承、模板等。当你编写 C++ 代码时，应该使用 g++ 而不是 gcc，因为 g++ 理解 C++ 的特定语法和特性。

简而言之，gcc 用于编译 C 语言程序，而 g++ 用于编译 C++ 程序。尽管 g++ 可以编译 C 语言代码（因为它兼容 C 的语法），但最好还是使用 gcc 来编译 C 代码，以避免不必要的混淆和潜在的问题。对于 C++ 代码，应该使用 g++，因为它提供了对 C++ 特性的完整支持。

## 命令行操作

### 第一步编译：g++ .\九九乘法表.cpp    /mingw32-make.exe(使用cmake编译生成可执行文件的命令)
  
这个命令会经历以下步骤：

编译：g++ 编译器会将 九九乘法表.cpp 文件中的人类可读的 C++ 代码转换成机器代码。

链接：编译器还会链接该程序可能依赖的任何库，以生成一个完整的可执行文件。

生成可执行文件：如果编译和链接过程没有错误，g++ 会生成一个可执行文件（在 Windows 上可能会是 九九乘法表.exe）。
如果想要指定生成的可执行文件的名称，可以使用 -o 选项: g++ .\九九乘法表.cpp -o 九九乘法表.exe

### 第二步执行：.\九九乘法表.exe   /  .\九九乘法表

如果编译成功，可以通过在命令行中输入生成的可执行文件的名称来运行程序

### 输出调试：g++ -g .\九九乘法表.cpp -o MyDeBugTest

和第一步过程一样，但输出的可执行文件带了调试信息，并且指定了名称

## Tips

1、通过 ls 命令查看当前文件夹下所有文件的名称、类型、字节数、最后修改时间
2、对文件编译和调试，需要在文件的父级文件夹目录下进行，注意不能是祖父级
9、在运行和调试时，相关配置和命令行操作能直接写文件名字的说明该文件直属于项目文件夹，是项目文件夹的子级，如果该文件是项目文件夹的孙级或者非子级，则需要指明路径，例如 main.cpp 和 Multi_Func/Func.cpp 的区别
3、使用 camke.. 命令时，也需要在父级文件夹下操作（cd .\build\）
4、cd ..进入父级文件夹
5、launch.json 文件用于配置调试信息，包括显示信息和编译器选择，C语言用gcc，C++用g++，该文件不影响Code Run
6、task.json 文件一般在launch.json 之前执行，用于生成.exe 文件，launch.json 可配置其是否执行，task.json 文件不影响Code Run
7、settings.json 文件是VS Code众多配置文件中的一个，可以对VS Code进行页面风格、代码格式、字体颜色大小等 的编辑设置，例如:自动保存、字体、文件编码等，该文件能影响Code Run
在设置->工作区->搜索 code run–>选择 Code-runner:Executor Map 设置编译参数，点击编辑，会在 .vscode 生成 settings.json
8、vscode设置界面分用户区和工作区
用户区：会应用于该用户打开的所有的工程，配置一些基础、常用、共用的配置。
工作区：仅适用于vscdoe打开的当前目录。
9、运行时额外编译特定文件操作：settings.json 中 "cpp": "cd $dir && g++ $fileName -IFunc Func/Func.cpp -o $fileNameWithoutExt &&      $dir$fileNameWithoutExt"
g++ main.cpp -IMulti_Func Multi_Func/Func.cpp -o main
10、调试时也需要先编译所有相关代码文件，然后输出可执行文件，该过程由task.json 控制
如果要调试多文件，则需在task.json 中配置要编译的额外文件
11、按下F1，弹出设置栏
12、build文件夹是cmake运行产生的中间文件,cmake 调试时产生的可执行文件就位于该文件夹下
13、cmake 调试和g++ 调试是两码事，这是两个不同的工具，前者通过下方工具栏调试，通过CMakeLists.txt 进行配置，后者通过右上角按钮调试，通过task.json 和 launch.json 配置
14、使用cmake ..命令重新构建工程，会重新建立build文件夹及其子项
15、mingw32-make.exe：在build文件夹下生成可执行文件
16、rm * 删除终端当前所在目录下的所有文件，eg：PS D:\A_Project\C++\Code\C++_study>
