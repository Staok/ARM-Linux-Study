# CMake 记录备查



寻找TODO



## 优秀 Github 仓库 / 基础参考

- 资料收集 [fenneishi/CMake-Summary-of-documentation-chinese-: CMake 资料总结，持续更新 (github.com)](https://github.com/fenneishi/CMake-Summary-of-documentation-chinese-)。
- 教程 [SFUMECJF/cmake-examples-Chinese: 快速入门CMake,通过例程学习语法。在线阅读地址：https://sfumecjf.github.io/cmake-examples-Chinese/](https://github.com/SFUMECJF/cmake-examples-Chinese)。
- 书 [xiaoweiChen/CMake-Cookbook: :book: 作为对《CMake Cookbook》的中文翻译。 (github.com)](https://github.com/xiaoweiChen/CMake-Cookbook)。



- 最基础 [CMake入门教程：从零开始构建C/C++项目 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/631933368)。

- 基础函数 [VScode C++ 开发 （六）：CMake_vscode 中.cmake 是什么文件_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/122220168)。

  基础语法 比较全，各种函数，判断语句，循环语句

  -  [CMake 基本常用语法 CMakeLists.txt_Rayyyyyyyyy的博客-CSDN博客](https://blog.csdn.net/q345911572/article/details/105250633)
  - [CMake学习笔记——CMake语法_cmake格式_Crs_小蔡的博客-CSDN博客](https://blog.csdn.net/cairongshou/article/details/128008872)。
  - [【cmake】CMakeList添加库|添加头文件|添加路径|add_executable、add_library、target_link_libraries|添加编译选项|宏开关_cmake 增加链接库_VincentPH的博客-CSDN博客](https://blog.csdn.net/Vincent20111024/article/details/129327542)。




## 函数记录

- `cmake_minimum_required()`、`project()`、`set()`、`add_executable()`。 

- 添加 头文件目录（相当于 gcc 的（大写的 i） `-I <头文件路径>`）`target_include_directories()`、`include_directories()`。

  二者的区别，前者只为确定的目标添加头文件路径，后者为整个工程加（若工程内含多个目标，且有互相引用头文件的现象时候用，为本工程所有目标添加头文件路径） [include_directories和target_include_directories_持续学习，不断沉淀的博客-CSDN博客](https://blog.csdn.net/qq_33726635/article/details/121896441)。

- 添加库的搜索路径（相当于 gcc 的 `-L <库路径>`）`target_link_directories()`、`link_directories()`。

  对于 添加自己生成的库文件，与下面 添加具体库文件同时使用，先添加库路径，再添加库名。

- 链接具体的库文件（相当于 gcc 的（小写的 L） `-l<库名>`） `target_link_libraries()`、`link_libraries()`。

  使用 `target_link_libraries()`，必须把 `add_executable()` 放到前面，而 `link_libraries()` 不必！其实 `add_executable()` 是创建 `target`。

  添加库 [CMake学习(5): 链接静(动)态库_cmakelist 链接静态库_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131069948)。

  > - PUBLIC：在 public 后面的库会被 Link 到前面的 target 中，并且里面的符号也会被导出，提供给第三方使用。
  > - PRIVATE：在 private 后面的库仅被 link 到前面的 target 中，并且终结掉，第三方不能感知你调了啥库
  > - INTERFACE：在 interface 后面引入的库不会被链接到前面的 target 中，只会导出符号。

  [CMake的链接选项：PRIVATE，INTERFACE，PUBLIC - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/493493849)。

  > 以下的解释主要场景是linux中，windows不存在这种关系，无需考虑。
  >
  > 我们来解释下，假设我们有一个程序 A  , A调用库B, B调用库C. 
  >
  > A -> B -> C
  >
  > A link B时不管是private还是public都没关系，毕竟A不需要导出符号，也没有人以API方式调用它。
  >
  > 现在主要问题就是B这个库用private还是public.  C是动态库。
  >
  > 如果B是动态或静态库，C是动态库，这个问题就会有影响。同样，如果B、C同为静态库时也会有问题。 
  >
  > B用private link C,  此时A link B,但是不知道B->C这层关系，可以正常link B. 运行时，A->B->C 时，B找不到C中的函数。linux下没有直接依赖关系，所有的B/C的依赖都会转到到A下，可以用LDD命令验证，此时A只依赖于B, 不见C, 当B中的函数调用C中的函数时，因为没有加载C, 所以报找不到符号错误。解决的办法就是在A link B时，同样也写上C. 但是因为private的原因，A是不知道C中的符号这事，只能强制 link C到A才能解决。
  >
  > 如果B link C时用public 指示， 当编译A时，就会检查到C中的符号没有实现，此时你就会知道要把C link到A来解决这个问题了。
  >
  > 其实private/public 解决的是指示问题，本质上可以使用public 来解决， 可以减少坑。

  若链接的是自己生成的库并放在了某个路径下，那么 cmake 文件里面需要先 `target_link_directories()` / `link_directories()` 指定链接的库的路径，再链接具体的库。

- 添加子 cmake 目录 `add_subdirectory()`。

  添加 子 cmake 目录 [CMake学习(7): CMake的嵌套_cmakelist嵌套_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131158601)。

  > 父节点中定义的变量是可以被子节点使用的（父节点定义的这些变量是全局变量，在子节点中定义的变量称为局部变量）。

  但我个人认为，为了良好的通用性和移植性，便携式的，每个 子 cmake 目录可以尽量保证独立，少依赖 其它 cmake 目录。

- 生成库 `add_library()`，通常用于子项目、库程序。

  [CMake学习(4):制作库文件——静态库/动态库_cmake 生成静态库_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131057947)。

  [模块化项目管理：CMake中的子目录和模块化构建 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/648590757)。

  > - `推荐`: 在`源文件非常多，推荐生成动态库；在源文件比较少的情况，推荐生成静态库`。
  > - 如果生成`动态库`,它所对应的源代码是不会打包的可执行文件中的，如果是`静态库`则会`打包`到可执行文件的内部。如果我们最终要求，生成的可执行文件非常小，那么我们就可以把这些源文件生成一个动态库，然后再发布应用程序时，一定要把该动态库提供给程序的使用者；如果我们对生成可执行文件的大小没有要求，并且要求使用比较简便，我们就可以把这些源文件生成静态库，生成静态库之后这些源文件就会打包到可执行文件中，所以在发布的时候只要发布一个可执行程序就可以了，不需要发布额外的库文件了。
  > - 使用`静态库的缺点`是最终生成的`可执行文件会比较大`，另外如果启动多个可执行程序，它占用的`物理内存`也比动态库要`大`。因为如果程序使用的是`动态库`，不管启动多少个可执行程序，在`内存中动态库有且只有一份`,是`共享的`。

- 添加编译选项 `add_compile_options()` / `target_compile_options()`。

  [CMAKE语法：add_definitions、add_compile_options_cmake add_definitions-CSDN博客](https://blog.csdn.net/qq_33726635/article/details/121896506)。

  [【cmake篇】选择编译器及设置编译参数_cmake_c_compiler-CSDN博客](https://blog.csdn.net/challenglistic/article/details/130200669)。

  - 全局生效 `add_compile_options`（针对包括c和c++编译器，增加编译选项） 和 设置变量 `CMAKE_CXX_FLAGS` 或 `CMAKE_C_FLAGS`（这两个各自针对c++或c）。

  - 针对某一个 target 生效 `target_compile_options(target PRIVATE ${compile_flags})`（为指定 target 增加编译选项）。

  - 一些通用的编译选项如：`-O2 -Wall -Wextra` （如果debug模式则加 `-g -ggdb`）可以对全局生效。

  - 一些比较严格的检查如：`-pedantic -Wpedantic`（一些严格的检查）（以及 `-Werror` 有任何警告则终止编译），可以针对某些库 target，不便 全局生效，因为不是所有 target 都能过这些 options。

  - 编译选项汇总：

    [CMake: 设置编译选项_cmake 添加编译选项-CSDN博客](https://blog.csdn.net/jjjstephen/article/details/130773977)。

    [gcc 编译 选项 汇总](https://zhuanlan.zhihu.com/p/347611674)。

  - file 文件读写命令：

    [cmake之file：文件处理](https://zhuanlan.zhihu.com/p/645350929)。

  - 例子：

  ```cmake
  add_compile_options(-std=c++11)
  # or
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}-Werror ")
  ```

- 向程序中添加宏， `add_definitions()` / `add_compile_definitions()` / `target_compile_definitions()`.

  > - `add_definitions & add_compile_definitions：` 为当前以下层路径的所有源文件和`target`增加编译选项，看下面例子即可
  > - `target_compile_definitions`：为指定target增加编译定义
  >
  > ```cmake
  > add_definitions(-DFOO)  
  > add_compile_definitions(FOO) 这个已经替代 add_definitions()
  > target_compile_definitions(target PUBLIC FOO) 
  > ```

  本质是 通过编译器 向程序中添加宏，如下，即也可以通过添加编译指令来添加宏：

  > `gcc test.c -DDEBUG -o app`
  >
  > 在 `gcc/g++ ` 命令中通过参数 `-D` 指定出要定义的 `宏的名字`，这样就相当于在代码中定义了一个宏，其名字为 `DEBUG`。

- 添加目录下所有源文件，符合规则的文件。

  用来匹配指定路径下所有符合通配符条件的文件 `file(GLOB <存储文件路径列表的变量> <路径以及文件名匹配符>)` 和 `file(GLOB_RECURSE <...> <...>)`，前者添加当前目录下所有匹配的文件，后者添加所有匹配文件包括子目录。类似于 `aux_source_directory()`（指定目录下所有源文件添加到指定的变量），[CMake 中，‘file(GLOB_RECURSE)‘含义及用法_创景彭于晏的博客-CSDN博客](https://blog.csdn.net/qq_21118315/article/details/130540302)。

  > 需要注意的是，使用 `file(GLOB_RECURSE)` 命令来自动查找文件是方便的，但不是最佳实践。这是因为它会在每次生成时重新扫描文件系统，这可能会导致不必要的重新编译，特别是当新的源文件被添加或删除时。**最好的做法是手动列出源文件，以确保只有真正需要的文件被编译**。

- 指定编译器。[【cmake】CMakeList添加库|添加头文件|添加路径|add_executable、add_library、target_link_libraries|添加编译选项|宏开关_VincentPH的博客-CSDN博客](https://blog.csdn.net/Vincent20111024/article/details/129327542)。

  首先需要环境变量
  
  ```bash
  export CC=/usr/local/bin/gcc
  export CXX=/usr/local/bin/g++
  
  # 可能还需要
  
  export LD_LIBRARY_PATH=/usr/local/gcc-xxx/lib:$LD_LIBRARY_PATH
  
  # /usr/local/gcc-xxx/lib 是你的新gcc的lib位置
  
  # 环境变量可以添加到这里
  vim ~/.bashrc
  # 再生效
  source ~/.bashrc
  ```
  
  再 makelist 里面
  
  ```cmake
  SET(CMAKE_C_COMPILER "/usr/local/bin/gcc")
  SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
  ```
  
  
  
- cmake 一些内置宏。

  > | 宏                                                           | 含义                                                         |
  > | :----------------------------------------------------------- | ------------------------------------------------------------ |
  > | **PROJECT_NAME**                                             | 返回通过 project() 定义的项目名称                            |
  > | **CMAKE_C_FLAGS** 设置C编译选项<br/>**CMAKE_CXX_FLAGS** 设置C++编译选项 | 例如：<br />set(CMAKE_C_FLAGS"-O3 -fopenmp -fPIC -Wno-deprecated -Wenum-compare -std=c++14")<br />set(CMAKE_CXX_FLAGS "-O3 -fopenmp -fPIC -Wno-deprecated -Wenum-compare -std=c++14")<br />另外<br />set(CMAKE_CXX_STANDARD 11)<br/>set(CMAKE_CXX_STANDARD_REQUIRED True) |
  > | BUILD_SHARED_LIBS                                            | 控制默认的库编译方式。<br/>注：如果未进行设置,使用ADD_LIBRARY时又没有指定库类型,默认编译生成的库都是静态库。 |
  > | **PROJECT_SOURCE_DIR**                                       | 使用cmake命令后紧跟的目录，一般是工程的根目录<br />工程源文件一般都在 `${PROJECT_SOURCE_DIR}/src/...` 里<br />头文件都在 `${PROJECT_SOURCE_DIR}/inc/...` 里，或者其它目录 |
  > | **PROJECT_BINARY_DIR**                                       | 执行cmake命令的目录，一般是 `${PROJECT_SOURCE_DIR}/build/` 目录 |
  > | CMAKE_CURRENT_SOURCE_DIR                                     | 当前处理的CMakeLists.txt所在的路径                           |
  > | CMAKE_CURRENT_BINARY_DIR                                     | target编译目录                                               |
  > | **EXECUTABLE_OUTPUT_PATH**                                   | 重新定义目标二进制可执行文件的存放位置<br />比如：<br />`set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)` |
  > | **LIBRARY_OUTPUT_PATH**                                      | 重新定义目标链接库文件的存放位置<br />比如：<br />`set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)`<br/>`set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)` |
  > | **CMAKE_INSTALL_PREFIX**                                     | `SET(CMAKE_INSTALL_PREFIX /usr/local)`<br />在外部构建情况下执行make install命令时，make会将生成的可执行文件拷贝到/usr/local/bin目录下。<br />当然，可执行文件的安装路径CMAKE_INSTALL_PREFIX也可以在执行cmake命令的时候指定，cmake参数如下：<br />`cmake -DCMAKE_INSTALL_PREFIX=/usr ..`<br />如果cmake参数和CMakeLists.txt文件中都不指定该值的话，则该值为默认的/usr/local。 |
  > | CMAKE_BINARY_DIR                                             | 项目实际构建路径，假设在 build 目录进行的构建，那么得到的就是这个目录的路径 |
  > | CMAKE_CURRENT_LIST_FILE                                      | 输出调用该变量的CMakeLists.txt的完整路径                     |
  > | CMAKE_CURRENT_LIST_LINE                                      | 输出该变量所在的行                                           |
  > | CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS                            | 用来控制IF…ELSE…语句的书写方式                               |
  > | CMAKE_MAJOR_VERSION 主版本号,如2.8.6中的2<br/>CMAKE_MINOR_VERSION 次版本号,如2.8.6中的8<br/>CMAKE_PATCH_VERSION 补丁等级,如2.8.6中的6 |                                                              |
  > | CMAKE_SYSTEM 系统名称,例如Linux-2.6.22<br/>CMAKE_SYSTEM_NAME 不包含版本的系统名,如Linux<br/>CMAKE_SYSTEM_VERSION 系统版本,如2.6.22<br/>CMAKE_SYSTEM_PROCESSOR 处理器名称,如i686 |                                                              |
  > |                                                              |                                                              |
  > | ...                                                          | ...                                                          |


- cmake 打印信息 和 添加宏 [CMake学习(6): 打印日志信息及宏定义_cmake 打印_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131157381)。

  ```cmake
  message([STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR] "message to display" ...)
  
  # example
  message("#### current cmake version: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
  ```

- 添加 / 获取属性 `set_target_properties()` / `get_target_property()`。

  [【cmake学习】set_target_properties 常见属性以及获取target 属性-CSDN博客](https://blog.csdn.net/challenglistic/article/details/130130789)。

  [cmkae命令set_target_properties_物随心转的博客-CSDN博客](https://blog.csdn.net/sinat_31608641/article/details/121712590)。

  [CMake中set_target_properties/get_target_property的使用_fengbingchun的博客-CSDN博客](https://blog.csdn.net/fengbingchun/article/details/128258041)。

  > 设置目标的某些属性，改变它们构建的方式。格式：
  >
  > ```cmake
  > SET_TARGET_PROPERTIES(target1 target2 ...
  >       PROPERTIES prop1 value1 prop2 value2 ...)
  > ```
  >
  > 该指令为一个目标设置属性，语法是列出所有用户想要变更的文件，然后提供想要设置的值。用户可以使用任何想用的属性与对应的值，并在随后的代码中调用GET_TARGET_PROPERTY命令取出属性的值。
  > 影响目标输出文件的属性PROPERTIES详述如下：
  >
  > **(1) PREFIX, SUFFIX**
  >
  > PREFIX覆盖了默认的目标名前缀（如lib）；
  >
  > SUFFIX覆盖了默认的目标名后缀（如.so）。
  >
  > **(2) IMPORT_PREFIX, IMPORT_PREFIX**
  >
  > 与PREFIX, SUFFIX是等价的属性，但针对的是DLL导入库（即共享库目标）。
  >
  > **(3) OUTPUT_NAME**
  >
  > 构建目标时，OUTPUT_NAME用来设置目标的真实名称.
  >
  > **(4) LINK_FLAGS**
  >
  > 为一个目标的链接阶段添加额外标志。
  >
  > LINK_FLAGS_< CONFIG >将为配置< CONFIG >添加链接标志，如DEBUG, RELEASE, MINSIZEREL, RELWITHDEBINFO。
  >
  > **(5) COMPILE_FLAGS**
  >
  > 设置附加的编译器标志，在构建目标内的源文件时被用到。
  >
  > **(6) LINKER_LANGUAGE**
  >
  > 改变链接可执行文件或共享库的工具。默认值是设置与库中文件相匹配的语言。
  >
  > CXX与C是该属性的公共值。
  >
  > **(7) VERSION, SOVERSION**
  > VERSION指定构建的版本号，SOVERSION指定构建的API版本号。
  >
  > 构建或安装时，如果平台支持符号链接，且链接器支持so名称，那么恰当的符号链接将会被创建。如果只指定两者中的一个，缺失的另一个假定为具有相同版本号。
  >
  > 例1：`SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")`
  >
  > 例2：`SET_TARGET_PROPERTIES(hello PROPERTEIES VERSION 1.2 SOVERSION 1)`
  >
  >
  > 该指令用于控制版本，VERSION指代动态库版本，SOVERSION指代API版本。

- 添加选项、添加 install()、添加测试（CTest）、添加安装包（CPack）、项目迁移 [全网最细的CMake教程！(强烈建议收藏) - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/534439206)。

  添加 install() 和 安装包，比较全 [CMake 安装与打包_cmake 打包_爱钓鱼的歪猴的博客-CSDN博客](https://blog.csdn.net/weixin_45824067/article/details/130809767)。

  [cmake应用：安装和打包 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/377131996)。

  > //执行make install的时候 把static_lib 放到bin
  >
  > install(TARGETS static_lib DESTINATION bin)
  >
  > //也可以使用变量
  >
  > install(TARGETS static_lib DESTINATION ${your_path})
  >
  > //还可以一次指定多个对象，并按类型指定放入的目的地
  >
  > install(TARGETS static_lib shared_lib exe //static_lib shared_lib exe 这个三个对象
  >       RUNTIME DESTINATION bin //可执行文件放在`bin`目录
  >       LIBRARY DESTINATION lib   //共享库文件放在`lib`目录
  >       ARCHIVE DESTINATION lib) //静态库文件放在`lib`目录
  >
  > 
  >
  > 命令第一个参数`TARGETS`指定需要安装的构建目标的列表，可以是静态库文件、动态库文件、可执行文件；安装时常常按照文件类型安装到不同的子目录，比如库文件放在`lib`目录，可执行文件放在`bin`目录。
  >
  > 针对不同文件类型，比如（`RUNTIME`, `ARCHIVE`, `LIBRARY`，`PUBLIC_HEADER`），可以分开进行配置，比如分别指定安装路径（`DESTINATION`）、设置文件权限（`PERMISSIONS`）；如果不是在某个类别下的单独配置，那么就是针对所有类型。
  >
  > 值得一提的是，`ARCHIVE`一般是指静态库，`LIBRARY`则是指共享库，在不同平台上，略有差异，实际应用感觉不符合预期时查看一下官方文档即可，问题不大。

- 将文件夹下所有头文件所在目录添加。

  如果 一个库中，所有头文件都在一个比如 inc 文件夹，那么直接添加这一个文件夹就好了，可是实际有的库或文件夹里面包含好几层文件夹且头文件分散其中，又不想一个一个添加，那么下面的方法可以做到，但是感觉比较怪。

  [cmake自动添加所有源文件和头文件_cmake添加目录下所有的文件-CSDN博客](https://blog.csdn.net/sep4075/article/details/120001415) 这是整了个函数，实测 这个会有问题，不好使，，

  所以，用三方库，要么在 cmake 里面头文件目录一个一个加，要么 cmake 里面加根目录 然后 .c 里面 用到哪个就 写相对路径 include。

- 执行一个程序 `execute_process()`。[CMAKE语法：add_definitions、add_compile_options_cmake add_definitions-CSDN博客](https://blog.csdn.net/qq_33726635/article/details/121896506)。

  > ```cmake
  > execute_process(COMMAND <cmd1> [args1...]] [WORKING_DIRECTORY <directory>])  
  > 
  > # 在${AA_PATH}/ABC路径下执行test1.py脚本
  > execute_process(COMMAND python ${ABC_PATH}/test1.py WORKING_DIRECTORY ${AA_PATH}/ABC)  
  > ```

- 寻找库 `find_library()` /  `find_package()`。

  find_library()

  [Cmake命令之find_library介绍](https://www.jianshu.com/p/8a64c77343cb)。下面具体各个项含义看这个链接。

  > **find_library ( <VAR> name** | NAMES name1 [name2 ...] [NAMES_PER_DIR] 
  > **[HINTS [path | ENV var]... ]** 
  > **[PATHS [path | ENV var]... ]** 
  > [PATH_SUFFIXES suffix1 [suffix2 ...]] 
  > [DOC "cache documentation string"] 
  > [NO_CACHE] **[REQUIRED]** 
  > **[NO_DEFAULT_PATH]** 
  > [NO_PACKAGE_ROOT_PATH] 
  > [NO_CMAKE_PATH] 
  > [NO_CMAKE_ENVIRONMENT_PATH] 
  > [NO_SYSTEM_ENVIRONMENT_PATH] 
  > [NO_CMAKE_SYSTEM_PATH] 
  > [CMAKE_FIND_ROOT_PATH_BOTH | ONLY_CMAKE_FIND_ROOT_PATH | NO_CMAKE_FIND_ROOT_PATH] **)**

  > - REQUIRED：当包没有被找到时，停止处理，及cmake停止继续运行。
  > - COMPONENTS：指定要查找的组件列表，一般一个包可能有很多组件组成（例如一个库生成需要很多其他的依赖库），通常找到这些全部组件才认为包被找到。
  > - OPTIONAL_COMPONENTS：指定要查找的组件列表，与COMPONENTS的区别是，不要求这些组件必须存在。不影响CMake的执行。
  > - **默认搜索**路径包含`cmake`定义的以`CMAKE`开头的一些变量（例如`CMAKE_LIBRARY_ARCHITECTURE`、`CMAKE_PREFIX_PATH`、`CMAKE_LIBRARY_PATH`、`CMAKE_FRAMEWORK_PATH`）、标准的系统环境变量（例如系统环境变量`LIB`和`PATH`定义的路径）、系统的默认的库安装路径（例如`/usr`、`/usr/lib`等）。
  > - **附加搜索路径**即`find_library`命令中通过`HINTS`或`PATHS`指定的路径。
  > - 当指定`NO_DEFAULT_PATH`选项时，默认搜索路径不会生效，只会用到附加搜索路径。
  > - `NO_CACHE`：该选项将`<var>`变量当成一个普通变量而不是一个缓存条目，需要`cmake 3.21及以上`的版本支持。默认`<var>`变量会写入`CMakeCache.txt`文件，在不清除`CMakeCache.txt`文件的情况下，每次执行`cmake`都会先从`CMakeCache.txt`载入该变量的值。

  例子：

  > ```cmake
  > find_library (libvar mymath ./mymath)
  > find_library (libvar mymath PATHS ./mylib REQUIRED)
  > ```

  

  find_package()

  [find_package深度解析及实例应用](https://blog.csdn.net/qq_39466755/article/details/130912344)。

  [“轻松搞定 CMake”系列之 find_package 用法详解](https://blog.csdn.net/itworld123/article/details/128671771)。

  [Cmake命令之find_package介绍](https://www.jianshu.com/p/a0915895dbbc)。下面具体各个项含义看这个链接。

  > 基础命令
  >
  > **find_package(<PackageName>** [version] [EXACT] [QUIET] [**MODULE**]
  >           [**REQUIRED**] [[**COMPONENTS**] **[components...]**]
  >           [OPTIONAL_COMPONENTS components...]
  >           [REGISTRY_VIEW  (64|32|64_32|32_64|HOST|TARGET|BOTH)]
  >           [GLOBAL]
  >           [NO_POLICY_SCOPE]
  >           [BYPASS_PROVIDER]**)**
  >
  > - module模式和config模式都支持该命令格式。
  >
  > - version：请求与该包兼容的版本。有两种可能的形式可以指定它:
  >
  >   (1):格式为major[.minor[.patch]的单一版本,例如：每个部分都是一个数字，均为可选：0.0.0.0或0.0.0或0.0.
  >
  >   (2):格式为versionMin…[<]versionMax，其中versionMin和versionMax具有与单个版本相同的格式和对整数组件的约束（例如：0.0.0.0...1.1.1.1）。默认情况下，包括两个端点。通过指定<，将排除上结束点。版本范围仅支持CMake 3.19或更高版本。
  >
  > - EXACT: 选项要求精确匹配版本。此选项与版本范围的规格不兼容(版本的第二种格式)。
  >
  > - MODULE：只是用module模式进行查找，不进行config模式查找，如果没指定的话，优先使用module模式搜索，如果未找到在进行config模式搜索。
  >
  > - QUIET：禁用信息消息。正常情况当找到包时，CMake会打印一些信息，指定该选项时会禁止掉这些打印。如果找不到包，仍然会输出错误信息并终止执行过程。
  >
  > - REQUIRED：当包没有被找到时，停止处理，及cmake停止继续运行。
  >
  > - COMPONENTS：指定要查找的组件列表，一般一个包可能有很多组件组成（例如一个库生成需要很多其他的依赖库），通常找到这些全部组件才认为包被找到。
  >
  > - OPTIONAL_COMPONENTS：指定要查找的组件列表，与COMPONENTS的区别是，不要求这些组件必须存在。不影响CMake的执行。
  >
  > 
  >
  > 完整命令
  >
  > **find_package(<PackageName>** [version] [EXACT] [QUIET]
  >              [**REQUIRED**] [[**COMPONENTS**] **[components...]**]
  >              [OPTIONAL_COMPONENTS components...]
  >              [**CONFIG|NO_MODULE**]
  >              [GLOBAL]
  >              [NO_POLICY_SCOPE]
  >              [BYPASS_PROVIDER]
  >              [NAMES name1 [name2 ...]]
  >              [CONFIGS config1 [config2 ...]]
  >              **[HINTS path1 [path2 ... ]]**
  >              **[PATHS path1 [path2 ... ]]**
  >              [REGISTRY_VIEW  (64|32|64_32|32_64|HOST|TARGET|BOTH)]
  >              [PATH_SUFFIXES suffix1 [suffix2 ...]]
  >              [NO_DEFAULT_PATH]
  >              [NO_PACKAGE_ROOT_PATH]
  >              [NO_CMAKE_PATH]
  >              [NO_CMAKE_ENVIRONMENT_PATH]
  >              [NO_SYSTEM_ENVIRONMENT_PATH]
  >              [NO_CMAKE_PACKAGE_REGISTRY]
  >              [NO_CMAKE_BUILDS_PATH] # Deprecated; does nothing.
  >              [NO_CMAKE_SYSTEM_PATH]
  >              [NO_CMAKE_INSTALL_PREFIX]
  >              [NO_CMAKE_SYSTEM_PACKAGE_REGISTRY]
  >              [CMAKE_FIND_ROOT_PATH_BOTH |
  >               ONLY_CMAKE_FIND_ROOT_PATH |
  >               NO_CMAKE_FIND_ROOT_PATH]**)**
  >
  > - CONFIG/NO_MODULE：这两个选项二选一即可，表示强制find_package命令使用config模式搜索，忽略module模式搜索。
  >
  > - NAMES：默认情况下find_package命令会查找名为的包。如果NAMES指定了名称，则会使用这些名字来查找包而忽略参数。
  >
  > - PATHS/HINTS：config模式下指定.cmake文件的搜索路径。

  搜索模式：两种搜索模式 Module 和 Config，默认 前者。[Cmake之find_package指令](https://blog.csdn.net/wzj_110/article/details/116464149)。

  > **Module 模式**：
  >
  > 搜索'CMAKE_MODULE_PATH'指定路径下的'FindXXX.cmake'文件，'执行该文件'从而'找到XXX库'
  >
  > 备注： 具体'查找库'并给XXX_INCLUDE_DIRS和XXX_LIBRARIES两个'变量赋值的操作'由FindXXX.cmake模块完成
  >
  > ++++++++++++++'CMAKE_MODULE_PATH'指定的路径++++++++++++++
  >
  > 1）<CMAKE_ROOT>/share/cmake-x/Mdodules 
  >
  > 备注1：x表示'大'版本号,centos7中如果是'2.x.x'系列,则不指定;'3.x.x'系列指定为'3'
  >
  > ++++++++++++++'CMAKE_ROOT'的路径++++++++++++++
  >
  > 1）其中'CMAKE_ROOT'是你在'安装cmake'的时候的'系统路径'
  >
  > 2）如果'没有指定'安装路径,则是'系统默认'的路径,在我的系统中(Centos7.7)系统的默认路径是'/usr/local'
  >
  > 3）如果你在安装的过程中使用了'cmake -DCMAKE_INSTALL_PREFIX=自己dir路径' ,那么此时'CMAKE_ROOT'就代表那个你'写入'的路径 
  >
  > 备注： '$CMAKE_ROOT'的具体值可以通过CMake中'message命令'输出
  >
  > 小结： 这称为'模块(Module)'模式,也是'默认'的模式
  >
  > ++++++++++++++'实践'++++++++++++++
  >
  > set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
  >
  > 说明： 基于'原来的','添加'一个'查找'路径-->'列表'
  >
  > 
  >
  > **Config 模式**：
  >
  > 搜索'XXX_DIR'指定路径下的'XXXConfig.cmake'文件,'执行'该文件从而'找到'XXX库
  >
  > 备注： 其中具体查找库'并给XXX_INCLUDE_DIRS'和'XXX_LIBRARIES'两个变量'赋值的操作'由'XXXConfig.cmake'模块完成
  >
  > +++++++++++Config '搜索路径'+++++++++++
  >
  > 1）搜索xxx_DIR '指定'的路径
  >
  > 2）如果在CMakeLists.txt中'没有设置'这个cmake变量,也就是说'没有下面的指令': 
  >
  >  set(xxx_DIR "xxxConfig.cmkae文件所在的路径")那么Cmake'就不会搜索'xxx_DIR指定的路径
  >
  > 3）Cmake 会在'/usr/local/lib/cmake/xxx/'、 '/usr/local/share/xxx' 中的xxxConfig.cmake文件
  >
  > 备注： 这个路径'不同的操作系统'存在差异,当前'Centos7.7'是'/usr/share/cmake{,3}/Modules/'

  

  - [Cmake中find_package命令的搜索模式之配置模式(Config mode)](https://www.jianshu.com/p/c6d1c31e77b8)。

  - [Cmake中find_package命令的搜索模式之模块模式(Module mode)](https://www.jianshu.com/p/f983a90bcf91)。
    - [pkg-config用法详解](https://www.jianshu.com/p/0faea1f431ec)。

  

  例子：一般大型开源库比如 openCV、QT 等官网文档会给出链接库的参考 cmake~参考之

  > ```cmake
  > find_package(Threads REQUIRED)
  > find_package(OpenCV 3 REQUIRED)
  > find_package(Python3 COMPONENTS Interpreter REQUIRED)
  > 
  > find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
  > find_package(Qt5 COMPONENTS Core Gui Quick QuickWidgets QuickControls2 REQUIRED)
  > ```

- `add_custom_target()` 添加自定义命令，执行 `cmake -xxx` 添加自己的自定义选项。 



## 控制语句 / 函数 / 宏



[cmake(十六)Cmake条件判断指令_cmake 条件判断-CSDN博客](https://blog.csdn.net/wzj_110/article/details/116105719)。

`if()/elseif()/else()/endif()` / `while / endwhile` / `foreach / endforeach`



```cmake
function(<name> [<arg1> ...])
    <commands>
endfunction()
```



```cmake
macro(<name> [<arg1> ...])
    <commands>
endmacro()
```



这一块现学现用