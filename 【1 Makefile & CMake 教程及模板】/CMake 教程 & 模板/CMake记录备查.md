# CMake 记录备查



优秀 Github 仓库：

- 资料收集 [fenneishi/CMake-Summary-of-documentation-chinese-: CMake 资料总结，持续更新 (github.com)](https://github.com/fenneishi/CMake-Summary-of-documentation-chinese-)。
- 教程 [SFUMECJF/cmake-examples-Chinese: 快速入门CMake,通过例程学习语法。在线阅读地址：https://sfumecjf.github.io/cmake-examples-Chinese/](https://github.com/SFUMECJF/cmake-examples-Chinese)。
- 书 [xiaoweiChen/CMake-Cookbook: :book: 作为对《CMake Cookbook》的中文翻译。 (github.com)](https://github.com/xiaoweiChen/CMake-Cookbook)。



参考 / 记录：

- 最基础 [CMake入门教程：从零开始构建C/C++项目 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/631933368)。

- 基础函数 [VScode C++ 开发 （六）：CMake_vscode 中.cmake 是什么文件_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/122220168)。

  基础语法 比较全 [CMake 基本常用语法 CMakeLists.txt_Rayyyyyyyyy的博客-CSDN博客](https://blog.csdn.net/q345911572/article/details/105250633)

  [CMake学习笔记——CMake语法_cmake格式_Crs_小蔡的博客-CSDN博客](https://blog.csdn.net/cairongshou/article/details/128008872)。

- `cmake_minimum_required()`、`project()`、`set()`、`add_executable()`、`aux_source_directory()`。 

  - 生成库 `add_library()`。

  - 添加 头文件目录（相当于 gcc 的（大写的 i） -I <头文件路径>）`target_include_directories()`、`include_directories()`。

    二者的区别，前者只为确定的目标添加头文件路径，后者为整个工程加（若工程内含多个目标，且有互相引用头文件的现象时候用，为本工程所有目标添加头文件路径） [include_directories和target_include_directories_持续学习，不断沉淀的博客-CSDN博客](https://blog.csdn.net/qq_33726635/article/details/121896441)。

  - 添加库文件目录（相当于 gcc 的 -L<库路径>）`target_link_directories()`、`link_directories()`。

    对于 添加自己生成的库文件，与下面 添加具体库文件同时使用，先添加库路径，再添加库名。

  - 链接具体的库文件（相当于 gcc 的（小写的 L） -l<库名>） `target_link_libraries()`、`link_libraries()`。

    使用 `target_link_libraries()`，必须 `add_executable()` 放到前面，而 `link_libraries()` 不必！其实 `add_executable()` 是创建 `target`。

  - 添加子 cmake 目录 `add_subdirectory()`。

  - 通过编译器向程序中添加宏 `add_compile_definitions()`，可以添加多个。

  - 用来匹配指定路径下所有符合通配符条件的文件 `file(GLOB <存储文件路径列表的变量> <路径以及文件名匹配符>)` 和 `file(GLOB_RECURSE <...> <...>)`，前者添加当前目录下所有匹配的文件，后者添加所有匹配文件包括子目录。类似于 `aux_source_directory()`，[CMake 中，‘file(GLOB_RECURSE)‘含义及用法_创景彭于晏的博客-CSDN博客](https://blog.csdn.net/qq_21118315/article/details/130540302)。

    > 需要注意的是，使用 `file(GLOB_RECURSE)` 命令来自动查找文件是方便的，但不是最佳实践。这是因为它会在每次生成时重新扫描文件系统，这可能会导致不必要的重新编译，特别是当新的源文件被添加或删除时。最好的做法是手动列出源文件，以确保只有真正需要的文件被编译。

  - 

- 生成库、指定输出库文件路径

  [CMake学习(4):制作库文件——静态库/动态库_cmake 生成静态库_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131057947)。

  [模块化项目管理：CMake中的子目录和模块化构建 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/648590757)。

- 添加库 [CMake学习(5): 链接静(动)态库_cmakelist 链接静态库_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131069948)。

- 添加 子 cmake 目录 [CMake学习(7): CMake的嵌套_cmakelist嵌套_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131158601)。

  > 父节点中定义的变量是可以被子节点使用的（父节点定义的这些变量是全局变量，在子节点中定义的变量称为局部变量）。

- cmake 打印信息 和 添加宏 [CMake学习(6): 打印日志信息及宏定义_cmake 打印_@BangBang的博客-CSDN博客](https://blog.csdn.net/weixin_38346042/article/details/131157381)。

- 添加选项、添加 install()、添加测试（CTest）、添加安装包（CPack）、项目迁移 [全网最细的CMake教程！(强烈建议收藏) - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/534439206)。

- 添加 install() 和 安装包，比较全 [CMake 安装与打包_cmake 打包_爱钓鱼的歪猴的博客-CSDN博客](https://blog.csdn.net/weixin_45824067/article/details/130809767)。