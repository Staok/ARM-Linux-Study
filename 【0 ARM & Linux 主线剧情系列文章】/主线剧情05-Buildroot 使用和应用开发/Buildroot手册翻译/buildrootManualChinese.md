Buildroot 2025.05 手册，生成于 2025-06-09 20:23:58 UTC，基于 git 修订版 fcde5363aa

Buildroot 手册由 Buildroot 开发者编写。其授权协议为 GNU 通用公共许可证第 2 版（GNU General Public License, version 2）。完整协议内容请参见 Buildroot 源码中的 [COPYING](http://git.buildroot.org/buildroot/tree/COPYING?id=fcde5363aa35220a1f201159a05de652ec6f811f) 文件。

版权所有 © Buildroot 开发者 <[buildroot@buildroot.org](mailto:buildroot@buildroot.org)>

# 第一部分 入门

# 第 1 章 关于 Buildroot

Buildroot 是一个简化并自动化为嵌入式系统构建完整 Linux 系统流程的工具，采用交叉编译（cross-compilation）方式。

为实现这一目标，Buildroot 能够为目标设备生成交叉编译工具链（cross-compilation toolchain）、根文件系统（root filesystem）、Linux 内核镜像（Linux kernel image）以及引导加载程序（bootloader）。Buildroot 可用于上述任意组合（例如，你可以使用已有的交叉编译工具链，仅用 Buildroot 构建根文件系统）。

Buildroot 主要适用于嵌入式系统开发人员。嵌入式系统通常使用的处理器并非大家在 PC 上常见的 x86 处理器，而是 PowerPC 处理器（PowerPC processors）、MIPS 处理器（MIPS processors）、ARM 处理器（ARM processors）等。

Buildroot 支持众多处理器及其变种，并为多款现成开发板（off-the-shelf boards）提供了默认配置。此外，许多第三方项目基于 Buildroot 开发其 BSP（Board Support Package）或 SDK（Software Development Kit）。

------

[1] BSP：板级支持包（Board Support Package）

[2] SDK：软件开发工具包（Software Development Kit）

# 第 2 章 系统要求

Buildroot 设计用于 Linux 系统。

虽然 Buildroot 会自动构建大部分所需的主机端（host）软件包，但仍要求主机系统预先安装部分标准 Linux 工具。下表列出了必需和可选软件包（注意，不同发行版的软件包名称可能有所不同）。

## 2.1 必需软件包

- 构建工具（Build tools）：
  - `which`
  - `sed`
  - `make`（版本 3.81 或更高）
  - `binutils`
  - `build-essential`（仅限基于 Debian 的系统）
  - `diffutils`
  - `gcc`（版本 4.8 或更高）
  - `g++`（版本 4.8 或更高）
  - `bash`
  - `patch`
  - `gzip`
  - `bzip2`
  - `perl`（版本 5.8.7 或更高）
  - `tar`
  - `cpio`
  - `unzip`
  - `rsync`
  - `file`（必须位于 `/usr/bin/file`）
  - `bc`
  - `findutils`
  - `awk`
- 源码获取工具（Source fetching tools）：
  - `wget`

## 2.2 可选软件包

- 推荐依赖（Recommended dependencies）：

  Buildroot 的部分功能或工具（如 legal-info、图形生成工具等）需要额外依赖。虽然这些依赖对于简单构建并非强制，但仍强烈推荐安装：

  - `python`（版本 2.7 或更高）

- 配置界面依赖（Configuration interface dependencies）：

  对于这些库，你需要同时安装运行时和开发包（runtime and development data），在许多发行版中开发包通常以 *-dev* 或 *-devel* 结尾。

  - `ncurses5`（用于 *menuconfig* 界面）
  - `qt5`（用于 *xconfig* 界面）
  - `glib2`、`gtk2` 和 `glade2`（用于 *gconfig* 界面）

- 源码获取工具（Source fetching tools）：

  在官方源码树中，大多数软件包源码通过 `wget` 从 *ftp*、*http* 或 *https* 位置获取。部分软件包仅能通过版本控制系统（version control system）获取。此外，Buildroot 还支持通过 `git` 或 `scp` 等工具下载源码（详见[第 20 章 下载基础设施](https://buildroot.org/downloads/manual/manual.html#download-infra)）。如启用这些方式获取的软件包，需在主机系统安装相应工具：

  - `bazaar`
  - `curl`
  - `cvs`
  - `git`
  - `mercurial`
  - `scp`
  - `sftp`
  - `subversion`

- Java 相关软件包（Java-related packages），如需为目标系统构建 Java Classpath：

  - `javac` 编译器（compiler）
  - `jar` 工具（tool）

- 文档生成工具（Documentation generation tools）：

  - `asciidoc`，版本 8.6.3 或更高
  - `w3m`
  - `python`，需带有 `argparse` 模块（2.7+ 和 3.2+ 默认自带）
  - `dblatex`（仅生成 pdf 手册时需要）

- 图形生成工具（Graph generation tools）：

  - `graphviz`（用于 *graph-depends* 和 *<pkg>-graph-depends*）
  - `python-matplotlib`（用于 *graph-build*）

- 软件包统计工具（Package statistics tools，*pkg-stats*）：

  - `python-aiohttp`

# 第 3 章 获取 Buildroot

Buildroot 每 3 个月发布一次新版本，发布时间为 2 月、5 月、8 月和 11 月。版本号格式为 YYYY.MM，例如 2013.02、2014.08。

发布版压缩包可在 http://buildroot.org/downloads/ 获取。

为方便用户，Buildroot 源码树的 `support/misc/Vagrantfile` 提供了一个 [Vagrantfile](https://www.vagrantup.com/)，可快速搭建包含所需依赖的虚拟机环境。

如需在 Linux 或 Mac OS X 上搭建隔离的 buildroot 环境，请在终端粘贴以下命令：

```
curl -O https://buildroot.org/downloads/Vagrantfile; vagrant up
```

如在 Windows 上，请在 powershell 粘贴以下命令：

```
(new-object System.Net.WebClient).DownloadFile(
"https://buildroot.org/downloads/Vagrantfile","Vagrantfile");
vagrant up
```

如需跟进开发版，可使用每日快照（daily snapshots）或克隆 Git 仓库。更多详情请参见 Buildroot 官网的 [下载页面]([Buildroot - Making Embedded Linux Easy](https://buildroot.org/download.html))。

# 第 4 章 Buildroot 快速入门

***重要提示***：你可以且应当***以普通用户身份构建所有内容***。配置和使用 Buildroot 无需 root 权限。以普通用户身份运行所有命令，可以防止在编译和安装过程中因软件包异常行为而影响你的系统。

使用 Buildroot 的第一步是创建配置。Buildroot 提供了类似于 [Linux 内核](http://www.kernel.org/) 或 [BusyBox](http://www.busybox.net/) 的友好配置工具。

在 buildroot 目录下，运行：

```
 $ make menuconfig
```

以启动原始的基于 curses 的配置器，或

```
 $ make nconfig
```

以启动新的基于 curses 的配置器，或

```
 $ make xconfig
```

以启动基于 Qt 的配置器，或

```
 $ make gconfig
```

以启动基于 GTK 的配置器。

所有这些 "make" 命令都需要构建配置工具（包括界面），因此你可能需要为相关库安装“开发”软件包。详细信息请参见[第 2 章 系统要求](https://buildroot.org/downloads/manual/manual.html#requirement)，特别是[可选依赖](https://buildroot.org/downloads/manual/manual.html#requirement-optional)部分，以获取你喜欢的界面所需依赖。

在配置工具的每个菜单项中，你都可以找到相关帮助，说明该项的用途。关于部分具体配置内容，详见[第 6 章 Buildroot 配置](https://buildroot.org/downloads/manual/manual.html#configure)。

配置完成后，配置工具会生成一个 `.config` 文件，包含全部配置信息。该文件将被顶层 Makefile 读取。

要开始构建流程，只需运行：

```
 $ make
```

默认情况下，Buildroot 不支持顶层并行构建（top-level parallel build），因此无需使用 `make -jN`。不过，Buildroot 提供了实验性的顶层并行构建支持，详见[第 8.12 节 “顶层并行构建”](https://buildroot.org/downloads/manual/manual.html#top-level-parallel-build)。

`make` 命令通常会执行以下步骤：

- 下载所需源码文件；
- 配置、构建并安装交叉编译工具链，或直接导入外部工具链；
- 配置、构建并安装所选目标软件包；
- 构建内核镜像（如已选择）；
- 构建引导加载程序镜像（如已选择）；
- 以所选格式创建根文件系统。

Buildroot 的输出统一存放在 `output/` 目录下。该目录包含若干子目录：

- `images/`：存放所有镜像（内核镜像、引导加载程序和根文件系统镜像）。这些文件需要烧录到目标系统。
- `build/`：存放所有构建组件（包括 Buildroot 在主机上需要的工具和为目标编译的软件包）。该目录下每个组件对应一个子目录。
- `host/`：包含为主机构建的工具和目标工具链的 sysroot。前者是为主机编译、Buildroot 正常运行所需的工具（包括交叉编译工具链）；后者结构类似根文件系统，包含所有用户空间软件包的头文件和库（供其他软件包依赖）。但该目录*不*应作为目标设备的根文件系统：其中包含大量开发文件、未剥离（unstripped）二进制和库，体积过大，仅供交叉编译时依赖。
- `staging/`：指向 `host/` 目录下目标工具链 sysroot 的符号链接，仅为兼容历史保留。
- `target/`：包含*几乎*完整的目标根文件系统：除 `/dev/` 下的设备文件（Buildroot 不能创建，因为不以 root 运行且不建议以 root 运行）和部分权限（如 busybox 二进制的 setuid 权限）外，其他内容齐全。因此，***该目录不应直接用于目标设备***。应使用 `images/` 目录下生成的镜像文件。如需用于 NFS 启动的根文件系统解包镜像，请使用 `images/` 目录下生成的 tar 包，并以 root 权限解包。与 `staging/` 不同，`target/` 仅包含运行所选目标应用所需的文件和库：不含开发文件（头文件等），二进制已剥离。

这些命令 `make menuconfig|nconfig|gconfig|xconfig` 和 `make` 是最基本的命令，可帮助你快速生成满足需求的镜像，包含你启用的所有功能和应用。

关于 "make" 命令的更多用法，详见[第 8.1 节 “make 使用技巧”](https://buildroot.org/downloads/manual/manual.html#make-tips)。

# 第 5 章 社区资源

与所有开源项目一样，Buildroot 社区和外部有多种信息交流方式。

如果你需要帮助、想了解 Buildroot 或希望为项目做贡献，这些方式都值得关注。

- 邮件列表（Mailing List）

  Buildroot 拥有用于讨论和开发的邮件列表，是 Buildroot 用户和开发者的主要交流方式。只有订阅者才能向该列表发帖。你可以通过[邮件列表信息页面](http://lists.buildroot.org/mailman/listinfo/buildroot)订阅。发送到邮件列表的邮件也会被归档，可通过 [Mailman](http://lists.buildroot.org/pipermail/buildroot) 或 [lore.kernel.org](https://lore.kernel.org/buildroot/) 查看。

- IRC

  Buildroot 的 IRC 频道 [#buildroot](irc://irc.oftc.net/#buildroot) 托管在 [OFTC](https://www.oftc.net/WebChat/) 上。这里适合快速提问或讨论特定话题。提问时请使用 https://paste.ack.tf/ 等代码分享网站粘贴相关日志或代码片段。对于某些问题，邮件列表可能更合适，因为能覆盖更多开发者和用户。

- Bug 跟踪器（Bug tracker）

  Buildroot 的 bug 可通过邮件列表或 [Buildroot bugtracker](https://gitlab.com/buildroot.org/buildroot/-/issues) 报告。请在提交 bug 报告前参见[第 22.6 节 “报告问题/bug 或获取帮助”](https://buildroot.org/downloads/manual/manual.html#reporting-bugs)。

- Wiki

  [Buildroot wiki 页面](http://elinux.org/Buildroot) 托管在 [eLinux](http://elinux.org/) wiki 上，包含有用链接、往届和即将举行的活动概览及 TODO 列表。

- Patchwork

  Patchwork 是一个基于 Web 的补丁跟踪系统，便于开源项目的补丁贡献和管理。发送到邮件列表的补丁会被系统“捕获”，并显示在网页上，相关评论也会附在补丁页面。更多 Patchwork 信息见 http://jk.ozlabs.org/projects/patchwork/。Buildroot 的 Patchwork 网站主要供维护者确保补丁不被遗漏，也供补丁审核者使用（参见[第 22.3.1 节 “从 Patchwork 应用补丁”](https://buildroot.org/downloads/manual/manual.html#apply-patches-patchwork)）。此外，该网站以简洁明了的界面公开补丁及其评论，对所有 Buildroot 开发者都很有用。Buildroot 补丁管理界面见 https://patchwork.ozlabs.org/project/buildroot/list/。



# 第二部分 用户指南

# 第 6 章 Buildroot 配置

所有 `make *config` 的配置选项都带有帮助文本，详细说明该选项的作用。

`make *config` 命令还提供了搜索工具。具体用法请参见各前端菜单中的帮助信息：

- 在 *menuconfig* 中，按 `/` 调出搜索工具；
- 在 *xconfig* 中，按 `Ctrl` + `f` 调出搜索工具。

搜索结果会显示匹配项的帮助信息。在 *menuconfig* 中，左侧的数字为快捷方式，输入该数字可直接跳转到对应条目，若因依赖未满足该条目不可选，则跳转到包含该条目的菜单。

虽然菜单结构和帮助文本已较为自解释，但部分主题需要额外说明，详见下文。

## 6.1 交叉编译工具链（Cross-compilation toolchain）

编译工具链（compilation toolchain）是一组用于为你的系统编译代码的工具。它包括编译器（compiler，通常为 `gcc`）、二进制工具（binary utils，如汇编器 assembler 和链接器 linker，通常为 `binutils`）以及 C 标准库（C standard library，例如 [GNU Libc](http://www.gnu.org/software/libc/libc.html)、[uClibc-ng](http://www.uclibc-ng.org/)）。

你的开发主机系统通常已自带一套编译工具链，可用于编译在本机运行的应用程序。如果你使用 PC，则该工具链在 x86 处理器上运行并生成 x86 代码。在大多数 Linux 系统中，工具链使用 GNU libc（glibc）作为 C 标准库。此类工具链称为“主机编译工具链”（host compilation toolchain），其运行的机器称为“主机系统”（host system）[3]。

主机编译工具链由发行版提供，Buildroot 仅使用它来构建交叉编译工具链及其他主机端工具。

如上所述，主机自带的工具链只能为主机处理器生成代码。嵌入式系统通常使用不同的处理器，因此需要交叉编译工具链（cross-compilation toolchain）：即在*主机系统*上运行、为*目标系统*（target system）和目标处理器生成代码的工具链。例如，主机为 x86，目标为 ARM，则主机工具链在 x86 上运行并生成 x86 代码，而交叉编译工具链在 x86 上运行并生成 ARM 代码。

Buildroot 提供两种交叉编译工具链方案：

- ***内部工具链后端（internal toolchain backend）***，在配置界面中称为 `Buildroot toolchain`；
- ***外部工具链后端（external toolchain backend）***，在配置界面中称为 `External toolchain`。

可在 `Toolchain` 菜单的 `Toolchain Type` 选项中选择方案。选择后会出现相应配置选项，详见下文。

### 6.1.1 内部工具链后端（Internal toolchain backend）

*内部工具链后端* 指 Buildroot 自行构建交叉编译工具链，然后再为目标嵌入式系统构建用户空间应用和库。

该后端支持多种 C 库：[uClibc-ng](http://www.uclibc-ng.org/)、[glibc](http://www.gnu.org/software/libc/libc.html) 和 [musl](http://www.musl-libc.org/)。

选择该后端后，可配置以下重要选项：

- 更改用于构建工具链的 Linux 内核头文件（kernel headers）版本。此项需特别说明：在构建交叉编译工具链过程中，需要构建 C 库。C 库为用户空间应用与 Linux 内核的接口。为实现此接口，C 库需访问 *Linux 内核头文件*（即内核的 `.h` 文件），这些头文件定义了用户空间与内核的接口（系统调用、数据结构等）。由于该接口向后兼容，构建工具链时使用的内核头文件版本无需与目标设备实际运行的内核版本*完全一致*，只需不高于目标内核版本即可。如果头文件版本高于目标内核，则 C 库可能会使用目标内核不支持的接口。
- 更改 GCC 编译器、binutils 及 C 库的版本。
- 选择多项工具链选项（仅 uClibc）：如是否支持 RPC（主要用于 NFS）、宽字符（wide-char）、本地化（locale，国际化）、C++ 支持、线程支持等。不同选项会影响 Buildroot 菜单中可见的用户空间应用和库：许多应用和库依赖特定工具链选项。大多数软件包在需要特定工具链选项时会有提示。如需进一步自定义 uClibc 配置，可运行 `make uclibc-menuconfig`。但需注意，Buildroot 仅测试其自带的 uClibc 默认配置：如自行裁剪 uClibc 功能，部分软件包可能无法编译。

注意：每当修改上述选项之一时，需重新构建整个工具链和系统。详见[第 8.2 节 “何时需要全量重构”](https://buildroot.org/downloads/manual/manual.html#full-rebuild)。

该后端优点：

- 与 Buildroot 集成良好
- 构建速度快，仅构建必要部分

缺点：

- 执行 `make clean` 时需重建工具链，耗时较长。如需缩短构建时间，可考虑*外部工具链后端*。

### 6.1.2 外部工具链后端（External toolchain backend）

*外部工具链后端* 允许使用已有的预编译交叉编译工具链。Buildroot 已内置多款知名交叉编译工具链（如 [Linaro](http://www.linaro.org/) 针对 ARM，[Sourcery CodeBench](http://www.mentor.com/embedded-software/sourcery-tools/sourcery-codebench/editions/lite-edition/) 针对 ARM、x86-64、PowerPC 和 MIPS），可自动下载，或指定自定义工具链（本地或可下载）。

使用外部工具链有三种方式：

- 使用预定义外部工具链配置文件，由 Buildroot 自动下载、解压和安装工具链。Buildroot 已内置部分 CodeSourcery 和 Linaro 工具链配置，只需在 `Toolchain` 菜单中选择即可。这是最简单的方式。
- 使用预定义外部工具链配置文件，但不让 Buildroot 下载和解压，而是手动指定已安装的工具链路径。在 `Toolchain` 菜单中选择配置，取消勾选 `Download toolchain automatically`，并在 `Toolchain path` 填写交叉编译工具链路径。
- 使用完全自定义的外部工具链。适用于用 crosstool-NG 或 Buildroot 自行生成的工具链。选择 `Custom toolchain`，填写 `Toolchain path`、`Toolchain prefix` 和 `External toolchain C library`。然后需告知 Buildroot 该工具链的支持特性：如为 *glibc*，只需说明是否支持 C++ 及内置 RPC；如为 *uClibc*，则需说明是否支持 RPC、宽字符、本地化、程序调用、线程和 C++。Buildroot 启动时会校验所选项与工具链配置是否匹配。

Buildroot 的外部工具链支持已在 CodeSourcery、Linaro、crosstool-NG 及 Buildroot 自身生成的工具链上测试。一般来说，支持 *sysroot* 特性的工具链均可用。如遇问题请联系开发者。

不支持 OpenEmbedded 或 Yocto 生成的工具链或 SDK，因为这些并非纯工具链（即仅包含编译器、binutils、C/C++ 库），而是包含大量预编译库和程序，Buildroot 无法导入其 *sysroot*，否则会包含数百兆预编译库，这些库本应由 Buildroot 构建。

也不支持将发行版自带工具链（即发行版安装的 gcc/binutils/C 库）作为目标软件编译工具链。因为发行版工具链并非“纯”工具链，无法正确导入 Buildroot 构建环境。即使目标为 x86 或 x86_64，也需用 Buildroot 或 crosstool-NG 生成交叉编译工具链。

如需为项目生成可用作 Buildroot 外部工具链的自定义工具链，建议用 Buildroot（见[第 6.1.3 节 “用 Buildroot 构建外部工具链”](https://buildroot.org/downloads/manual/manual.html#build-toolchain-with-buildroot)）或 [crosstool-NG](http://crosstool-ng.org/) 构建。

该后端优点：

- 可用知名、成熟的交叉编译工具链
- 避免了交叉编译工具链的构建时间，通常在嵌入式 Linux 系统整体构建时间中占比很大

缺点：

- 如预编译外部工具链有 bug，除非自行用 Buildroot 或 Crosstool-NG 构建，否则难以获得修复

[3] 主机系统（host system）：即你工作的开发主机。



### 6.1.3 使用 Buildroot 构建外部工具链

Buildroot 的内部工具链选项可用于创建外部工具链。以下是构建内部工具链并将其打包以供 Buildroot（或其他项目）复用的步骤：

新建 Buildroot 配置，主要设置如下：

- 在 ***目标选项（Target options）*** 中选择合适的目标 CPU 架构；
- 在 ***工具链（Toolchain）*** 菜单中，保持 ***工具链类型（Toolchain type）*** 为默认的 ***Buildroot toolchain***，并按需配置工具链；
- 在 ***系统配置（System configuration）*** 菜单中，将 ***Init system*** 设为 ***None***，将 *** /bin/sh *** 设为 ***none***；
- 在 ***目标软件包（Target packages）*** 菜单中，禁用 ***BusyBox***；
- 在 ***文件系统镜像（Filesystem images）*** 菜单中，禁用 ***tar the root filesystem***。

然后，触发构建并让 Buildroot 生成 SDK，这会为你生成一个包含工具链的 tar 包：

```
make sdk
```

SDK tar 包会生成在 `$(O)/images` 目录下，文件名类似于 `arm-buildroot-linux-uclibcgnueabi_sdk-buildroot.tar.gz`。保存该 tar 包，即可在其他 Buildroot 项目中作为外部工具链复用。

在其他 Buildroot 项目中，在 ***工具链（Toolchain）*** 菜单：

- 设置 ***工具链类型（Toolchain type）*** 为 ***External toolchain***；
- 设置 ***Toolchain*** 为 ***Custom toolchain***；
- 设置 ***Toolchain origin*** 为 ***Toolchain to be downloaded and installed***；
- 设置 ***Toolchain URL*** 为 `file:///path/to/your/sdk/tarball.tar.gz`。

#### 外部工具链包装器（External toolchain wrapper）

使用外部工具链时，Buildroot 会生成一个包装程序（wrapper），自动为外部工具链程序传递合适参数（根据配置）。如需调试该包装器以检查实际传递的参数，可设置环境变量 `BR2_DEBUG_WRAPPER`，可选值如下：

- `0`、空或未设置：无调试输出；
- `1`：所有参数输出在一行；
- `2`：每行输出一个参数。

## 6.2 /dev 管理

在 Linux 系统中，`/dev` 目录包含特殊文件，称为*设备文件（device files）*，用于让用户空间应用访问由内核管理的硬件设备。没有这些*设备文件*，即使内核已识别硬件，用户空间应用也无法使用。

在 `System configuration` 的 `/dev management` 下，Buildroot 提供四种 `/dev` 目录管理方案：

- 第一种方案是 ***静态设备表（Static using device table）***。这是 Linux 早期管理设备文件的传统方式。设备文件持久存储在根文件系统中（重启后依然存在），不会因硬件增减自动创建或删除。Buildroot 会用*设备表（device table）*创建一组标准设备文件，默认表位于 Buildroot 源码的 `system/device_table_dev.txt`。该文件在生成最终根文件系统镜像时处理，因此*设备文件*不会出现在 `output/target` 目录。`BR2_ROOTFS_STATIC_DEVICE_TABLE` 选项可更改默认设备表或添加额外设备表，以便在构建时创建更多*设备文件*。如需添加设备文件，可新建 `board/<yourcompany>/<yourproject>/device_table_dev.txt`，并将 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 设为 `system/device_table_dev.txt board/<yourcompany>/<yourproject>/device_table_dev.txt`。设备表格式详见[第 25 章 Makedev 语法文档](https://buildroot.org/downloads/manual/manual.html#makedev-syntax)。
- 第二种方案是 ***仅用 devtmpfs 动态管理（Dynamic using devtmpfs only）***。*devtmpfs* 是内核 2.6.32 引入的虚拟文件系统（如用旧内核无法用此选项）。挂载到 `/dev` 后，内核会根据硬件增减自动动态创建和删除*设备文件*，但不会持久化。需启用内核配置 `CONFIG_DEVTMPFS` 和 `CONFIG_DEVTMPFS_MOUNT`。如 Buildroot 负责构建内核，会自动启用这两个选项；如在 Buildroot 外构建内核，需自行确保启用，否则 Buildroot 系统无法启动。
- 第三种方案是 ***devtmpfs + mdev 动态管理（Dynamic using devtmpfs + mdev）***。此法同样依赖上述 *devtmpfs*（同样需启用 `CONFIG_DEVTMPFS` 和 `CONFIG_DEVTMPFS_MOUNT`），但在其基础上增加了 BusyBox 的 `mdev` 用户空间工具。每当设备增减，内核会调用 `mdev`，其行为可通过 `/etc/mdev.conf` 配置，如设置设备文件权限、归属、调用脚本等。这样，*用户空间*可对设备事件做出反应。`mdev` 还可用于设备出现时自动加载内核模块，或为需固件的设备推送固件。`mdev` 是 `udev` 的轻量实现。详见 http://git.busybox.net/busybox/tree/docs/mdev.txt。
- 第四种方案是 ***devtmpfs + eudev 动态管理（Dynamic using devtmpfs + eudev）***。同样依赖 *devtmpfs*，但在其上运行 `eudev` 守护进程。`eudev` 是后台运行的守护进程，设备增减时由内核调用。比 `mdev` 更重，但更灵活。`eudev` 是 `udev` 的独立版本，`udev` 原为大多数桌面 Linux 发行版的用户空间守护进程，现已并入 Systemd。详见 http://en.wikipedia.org/wiki/Udev。

Buildroot 开发者建议优先使用 ***仅用 devtmpfs 动态管理（Dynamic using devtmpfs only）***，如需用户空间响应设备事件或需固件支持，则推荐 ***devtmpfs + mdev***。

注意：如选择 `systemd` 作为 init system，则 /dev 管理由 `systemd` 提供的 `udev` 完成。

## 6.3 init 系统

*init* 程序是内核启动的第一个用户空间程序（PID 为 1），负责启动用户空间服务和程序（如 Web 服务器、图形应用、网络服务等）。

Buildroot 支持三种 init 系统，可在 `System configuration` 的 `Init system` 选择：

- 第一种方案是 ***BusyBox***。BusyBox 除众多工具外，还实现了基本的 `init` 程序，足以满足大多数嵌入式系统。启用 `BR2_INIT_BUSYBOX` 后，BusyBox 会构建并安装其 `init` 程序（Buildroot 默认方案）。BusyBox 的 `init` 程序启动时读取 `/etc/inittab` 文件。该文件语法见 http://git.busybox.net/busybox/tree/examples/inittab（注意 BusyBox 的 inittab 语法特殊，请勿参考网络上其他 inittab 文档）。Buildroot 默认的 inittab 位于 `package/busybox/inittab`。除挂载重要文件系统外，默认 inittab 主要启动 `/etc/init.d/rcS` 脚本和 `getty`（登录提示）。
- 第二种方案是 ***systemV***。采用传统的 *sysvinit* 程序，Buildroot 打包于 `package/sysvinit`。该方案曾为大多数桌面 Linux 发行版所用，后被 Upstart、Systemd 等替代。`sysvinit` 也用 inittab 文件（语法与 BusyBox 略有不同），默认 inittab 位于 `package/sysvinit/inittab`。
- 第三种方案是 ***systemd***。`systemd` 是新一代 Linux init 系统，功能远超传统 *init*：支持激进的并行启动、基于 socket 和 D-Bus 的服务激活、按需启动守护进程、用 Linux 控制组跟踪进程、支持快照和恢复等。`systemd` 适用于较复杂的嵌入式系统（如需 D-Bus 及服务间通信）。需注意，`systemd` 依赖较多（如 `dbus`、`udev` 等）。详见 http://www.freedesktop.org/wiki/Software/systemd。

Buildroot 开发者推荐使用 ***BusyBox init***，足以满足大多数嵌入式系统。如需更复杂功能可选用 ***systemd***。

------

[3] 该术语与 GNU configure 不同，后者将 host 定义为应用实际运行的机器（通常即 target）。



# 第 7 章 其他组件的配置

在尝试修改下述任何组件前，请确保已配置好 Buildroot 本身，并已启用相应软件包。

- BusyBox

  如果已有 BusyBox 配置文件，可在 Buildroot 配置中通过 `BR2_PACKAGE_BUSYBOX_CONFIG` 直接指定该文件。否则，Buildroot 会从默认 BusyBox 配置文件开始。如需后续修改配置，可用 `make busybox-menuconfig` 打开 BusyBox 配置编辑器。也可通过环境变量指定 BusyBox 配置文件，但不推荐。详见[第 8.6 节 环境变量](https://buildroot.org/downloads/manual/manual.html#env-vars)。

- uClibc

  uClibc 的配置方式与 BusyBox 类似。可用配置变量 `BR2_UCLIBC_CONFIG` 指定已有配置文件，后续修改可用 `make uclibc-menuconfig`。

- Linux 内核

  如已有内核配置文件，可在 Buildroot 配置中通过 `BR2_LINUX_KERNEL_USE_CUSTOM_CONFIG` 直接指定。如无配置文件，可在 Buildroot 配置中用 `BR2_LINUX_KERNEL_USE_DEFCONFIG` 指定 defconfig，或新建空文件并指定为自定义配置文件（`BR2_LINUX_KERNEL_USE_CUSTOM_CONFIG`）。后续修改可用 `make linux-menuconfig`。

- Barebox

  Barebox 的配置方式与 Linux 内核类似。相关配置变量为 `BR2_TARGET_BAREBOX_USE_CUSTOM_CONFIG` 和 `BR2_TARGET_BAREBOX_USE_DEFCONFIG`。配置编辑器命令为 `make barebox-menuconfig`。

- U-Boot

  U-Boot（2015.04 及以上版本）配置方式同 Linux 内核。相关配置变量为 `BR2_TARGET_UBOOT_USE_CUSTOM_CONFIG` 和 `BR2_TARGET_UBOOT_USE_DEFCONFIG`。配置编辑器命令为 `make uboot-menuconfig`。

# 第 8 章 Buildroot 常用用法

## 8.1 *make* 使用技巧

以下是帮助你高效使用 Buildroot 的技巧。

**显示 make 执行的所有命令：**

```
 $ make V=1 <target>
```

**显示带 defconfig 的所有开发板列表：**

```
 $ make list-defconfigs
```

**显示所有可用目标：**

```
 $ make help
```

并非所有目标始终可用，`.config` 文件中的部分设置会隐藏某些目标：

- 仅启用 busybox 时可用 `busybox-menuconfig`；
- 仅启用 linux 时可用 `linux-menuconfig` 和 `linux-savedefconfig`；
- 仅选择内部工具链为 uClibc 时可用 `uclibc-menuconfig`；
- 仅启用 barebox 启动加载器时可用 `barebox-menuconfig` 和 `barebox-savedefconfig`；
- 仅启用 U-Boot 启动加载器且构建系统为 Kconfig 时可用 `uboot-menuconfig` 和 `uboot-savedefconfig`。

**清理：** 如更改体系结构或工具链配置选项，需显式清理。

删除所有构建产物（包括构建目录、host、staging 和 target 树、镜像和工具链）：

```
 $ make clean
```

**生成手册：** 当前手册源码位于 *docs/manual* 目录。生成手册命令：

```
 $ make manual-clean
 $ make manual
```

手册输出位于 *output/docs/manual*。

**注意**

- 构建文档需安装部分工具（见[第 2.2 节 可选软件包](https://buildroot.org/downloads/manual/manual.html#requirement-optional)）。

**为新目标重置 Buildroot：** 删除所有构建产物及配置：

```
 $ make distclean
```

**注意：** 如启用 `ccache`，运行 `make clean` 或 `distclean` 不会清空 Buildroot 使用的编译器缓存。清理方法见[第 8.13.3 节 Buildroot 中使用 ccache](https://buildroot.org/downloads/manual/manual.html#ccache)。

**导出 make 内部变量：** 可导出 make 已知变量及其值：

```
 $ make -s printvars VARS='VARIABLE1 VARIABLE2'
 VARIABLE1=value_of_variable
 VARIABLE2=value_of_variable
```

可通过变量调整输出：

- `VARS` will limit the listing to variables which names match the specified make-patterns - this must be set else nothing is printed
- `QUOTED_VARS`, if set to `YES`, will single-quote the value
- `RAW_VARS`, if set to `YES`, will print the unexpanded value

For example:

```
 $ make -s printvars VARS=BUSYBOX_%DEPENDENCIES
 BUSYBOX_DEPENDENCIES=skeleton toolchain
 BUSYBOX_FINAL_ALL_DEPENDENCIES=skeleton toolchain
 BUSYBOX_FINAL_DEPENDENCIES=skeleton toolchain
 BUSYBOX_FINAL_PATCH_DEPENDENCIES=
 BUSYBOX_RDEPENDENCIES=ncurses util-linux
 $ make -s printvars VARS=BUSYBOX_%DEPENDENCIES QUOTED_VARS=YES
 BUSYBOX_DEPENDENCIES='skeleton toolchain'
 BUSYBOX_FINAL_ALL_DEPENDENCIES='skeleton toolchain'
 BUSYBOX_FINAL_DEPENDENCIES='skeleton toolchain'
 BUSYBOX_FINAL_PATCH_DEPENDENCIES=''
 BUSYBOX_RDEPENDENCIES='ncurses util-linux'
 $ make -s printvars VARS=BUSYBOX_%DEPENDENCIES RAW_VARS=YES
 BUSYBOX_DEPENDENCIES=skeleton toolchain
 BUSYBOX_FINAL_ALL_DEPENDENCIES=$(sort $(BUSYBOX_FINAL_DEPENDENCIES) $(BUSYBOX_FINAL_PATCH_DEPENDENCIES))
 BUSYBOX_FINAL_DEPENDENCIES=$(sort $(BUSYBOX_DEPENDENCIES))
 BUSYBOX_FINAL_PATCH_DEPENDENCIES=$(sort $(BUSYBOX_PATCH_DEPENDENCIES))
 BUSYBOX_RDEPENDENCIES=ncurses util-linux
```

The output of quoted variables can be reused in shell scripts, for example:

```
 $ eval $(make -s printvars VARS=BUSYBOX_DEPENDENCIES QUOTED_VARS=YES)
 $ echo $BUSYBOX_DEPENDENCIES
 skeleton toolchain
```



## 8.2 何时需要全量重构

Buildroot 不会尝试自动检测在通过 `make menuconfig`、`make xconfig` 或其他配置工具更改系统配置后，哪些部分需要重建。有时应重建整个系统，有时只需重建部分软件包，但要完全可靠地检测这些情况非常困难，因此 Buildroot 开发者选择不做自动检测。

因此，用户需自行判断何时需要全量重构。以下经验法则可帮助你理解 Buildroot 的工作方式：

- 更改目标体系结构配置时，需全量重构。例如更改架构变体、二进制格式或浮点策略等会影响整个系统。
- 更改工具链配置时，通常也需全量重构。工具链配置变更通常涉及编译器版本、C 库类型或其配置等，这些都会影响整个系统。
- 新增软件包时，不一定需要全量重构。Buildroot 会检测到该包未被构建过并自动构建。但如该包为可被其他已构建包可选依赖的库，Buildroot 不会自动重建这些包。你需手动重建相关包，或全量重构。例如，已构建带 `ctorrent`、不带 `openssl` 的系统，后续启用 `openssl` 并重建，Buildroot 只会构建 `openssl`，不会自动重建 `ctorrent` 以启用 SSL。此时需手动重建 `ctorrent` 或全量重构。
- 移除软件包时，Buildroot 不会做特殊处理。不会从目标根文件系统或工具链 *sysroot* 中移除该包安装的文件。需全量重构才能彻底移除该包。但通常无需立即移除，可等下次完整构建时再处理。
- 更改软件包子选项时，Buildroot 不会自动重建该包。此时通常只需重建该包，除非新选项为其他已构建包提供了新特性。Buildroot 不追踪包的重建依赖：包一旦构建，除非显式指定，否则不会重建。
- 更改根文件系统 skeleton 时，需全量重构。但更改 rootfs overlay、post-build 脚本或 post-image 脚本时，无需全量重构，直接 `make` 即可生效。
- 当 `FOO_DEPENDENCIES` 中的软件包被重建或移除时，Buildroot 不会自动重建依赖该包的 `foo` 包。例如 `FOO_DEPENDENCIES = bar`，如更改 `bar` 配置，`foo` 不会自动重建。此时需手动重建所有依赖 `bar` 的包，或全量重构以确保依赖关系正确。

一般来说，如遇构建错误且不确定配置更改的影响，建议全量重构。若错误依旧，则可确定与部分重建无关。如为官方 Buildroot 包，欢迎报告问题！随着经验积累，你会逐步掌握何时需全量重构，从而节省时间。

全量重构命令如下：

```
$ make clean all
```

## 8.3 如何重建软件包

Buildroot 用户常问如何重建某个软件包或在不全量重构的情况下移除软件包。

Buildroot 不支持在不全量重构的情况下移除软件包。因为 Buildroot 不追踪各包在 `output/staging` 和 `output/target` 目录下安装了哪些文件，也不追踪哪些包会因其他包的可用性而编译出不同内容。

重建单个软件包最简单的方法是删除其在 `output/build` 下的构建目录。Buildroot 会重新解包、配置、编译并安装该包。可用 `make <package>-dirclean` 命令自动完成。

如只需从编译步骤重新构建包，可用 `make <package>-rebuild`，会重新编译和安装，但不会从头开始，仅重新构建有变更的文件。

如需从配置步骤重新构建包，可用 `make <package>-reconfigure`，会重新配置、编译和安装。

`<package>-rebuild` 隐含 `<package>-reinstall`，`<package>-reconfigure` 隐含 `<package>-rebuild`，这些目标及 `<package>` 只作用于该包本身，不会自动重建根文件系统镜像。如需重建根文件系统，需额外运行 `make` 或 `make all`。

Buildroot 内部用*标记文件（stamp files）*记录每个包的构建步骤，存于 `output/build/<package>-<version>/`，文件名为 `.stamp_<step-name>`。上述命令通过操作这些标记文件，强制 Buildroot 重新执行包的特定构建步骤。

更多包专用 make 目标详见[第 8.13.5 节 包专用 make 目标](https://buildroot.org/downloads/manual/manual.html#pkg-build-steps)。

## 8.4 离线构建

如需离线构建，仅想下载配置器（*menuconfig*、*nconfig*、*xconfig* 或 *gconfig*）中已选软件包的所有源码，可运行：

```
 $ make source
```

此后即可断网或将 `dl` 目录内容拷贝到构建主机。

## 8.5 树外构建（out-of-tree build）

默认情况下，Buildroot 构建的所有内容都存储在 Buildroot 树下的 `output` 目录。

Buildroot 也支持类似 Linux 内核的树外构建。用法是在 make 命令行加 `O=<目录>`：

```
 $ make O=/tmp/build menuconfig
```

或：

```
 $ cd /tmp/build; make O=$PWD -C path/to/buildroot menuconfig
```

所有输出文件都位于 `/tmp/build`。如 `O` 路径不存在，Buildroot 会自动创建。

***注意：*** `O` 路径可为绝对或相对路径，但如为相对路径，则相对于 Buildroot 源码主目录（而非当前工作目录）。

使用树外构建时，Buildroot 的 `.config` 和临时文件也存储在输出目录。这样可在同一源码树下并行运行多个构建，只需保证输出目录唯一。

为方便使用，Buildroot 会在输出目录生成 Makefile 包装器——首次运行后，无需再传递 `O=<…>` 和 `-C <…>`，只需在输出目录下直接运行：

```
 $ make <target>
```

## 8.6 环境变量

Buildroot 支持部分环境变量，可在调用 `make` 时传递或在环境中设置：

- `HOSTCXX`：主机 C++ 编译器
- `HOSTCC`：主机 C 编译器
- `UCLIBC_CONFIG_FILE=<path/to/.config>`：uClibc 配置文件路径（如构建内部工具链）。uClibc 配置文件也可在 Buildroot 配置界面设置，推荐用 `.config` 文件方式。
- `BUSYBOX_CONFIG_FILE=<path/to/.config>`：BusyBox 配置文件路径。也可在 Buildroot 配置界面设置，推荐用 `.config` 文件方式。
- `BR2_CCACHE_DIR`：覆盖 Buildroot 使用 ccache 时缓存文件的目录。
- `BR2_DL_DIR`：覆盖 Buildroot 下载/检索文件的目录。下载目录也可在 Buildroot 配置界面设置，推荐用 `.config` 文件方式。详见[第 8.13.4 节 下载包位置](https://buildroot.org/downloads/manual/manual.html#download-location)。
- `BR2_GRAPH_ALT`：如设置且非空，构建时图表使用备用配色方案。
- `BR2_GRAPH_OUT`：设置生成图表的文件类型，`pdf`（默认）或 `png`。
- `BR2_GRAPH_DEPS_OPTS`：为依赖关系图传递额外选项，详见[第 8.9 节 包依赖关系图](https://buildroot.org/downloads/manual/manual.html#graph-depends)。
- `BR2_GRAPH_DOT_OPTS`：原样传递给 `dot` 工具以绘制依赖关系图。
- `BR2_GRAPH_SIZE_OPTS`：为大小图传递额外选项，详见[第 8.11 节 文件系统大小图](https://buildroot.org/downloads/manual/manual.html#graph-size)。

示例：配置文件分别位于顶层目录和 $HOME：

```
 $ make UCLIBC_CONFIG_FILE=uClibc.config BUSYBOX_CONFIG_FILE=$HOME/bb.config
```

如需为主机端辅助二进制选择非默认 `gcc` 或 `g++` 编译器：

```
 $ make HOSTCXX=g++-4.3-HEAD HOSTCC=gcc-4.3-HEAD
```

## 8.7 高效处理文件系统镜像

文件系统镜像体积可能很大，取决于文件系统类型、软件包数量、预留空间等。但镜像中部分区域可能只是*空*（如长串零），这种文件称为*稀疏文件（sparse file）*。

大多数工具可高效处理稀疏文件，仅存储/写入非零部分。

例如：

- `tar` 支持 `-S` 选项，仅存储稀疏文件的非零块：
  - `tar cf archive.tar -S [files…]` 可高效打包稀疏文件
  - `tar xf archive.tar -S` 可高效解包稀疏文件
- `cp` 支持 `--sparse=WHEN` 选项（`WHEN` 可为 `auto`、`never` 或 `always`）：
  - `cp --sparse=always source.file dest.file` 如源文件有长零区，目标文件也会为稀疏文件

其他工具也有类似选项，详见各自 man 手册。

如需存储、传输文件系统镜像（如跨机传输或发给 QA），可用稀疏文件。

但注意：用 `dd` 的稀疏模式刷写镜像到设备可能导致文件系统损坏（如 ext2 的块位图损坏，或稀疏文件部分读回时非全零）。稀疏文件仅适用于构建机本地操作，不应用于实际设备刷写。

## 8.8 关于软件包的详细信息

Buildroot 可生成 JSON 格式的摘要，描述当前配置下已启用软件包的集合，包括其依赖关系、许可证及其他元数据。可通过 `show-info` make 目标生成：

```
make show-info
```

Buildroot 还可通过 `pkg-stats` make 目标生成软件包详细信息（HTML 和 JSON 格式）。其中包括当前配置下软件包是否受已知 CVE（安全漏洞）影响，以及是否有上游新版本。

```
make pkg-stats
```

## 8.9 软件包依赖关系图

Buildroot 负责管理软件包间的依赖关系，确保按正确顺序构建。这些依赖有时很复杂，理解某个包为何被 Buildroot 引入并不容易。

为帮助理解依赖关系、理清嵌入式 Linux 系统各组件作用，Buildroot 可生成依赖关系图。

生成全系统依赖关系图：

```
make graph-depends
```

生成的图位于 `output/graphs/graph-depends.pdf`。

如系统较大，依赖图可能过于复杂。可仅为某个包生成依赖图：

```
make <pkg>-graph-depends
```

生成的图位于 `output/graph/<pkg>-graph-depends.pdf`。

依赖关系图由 *Graphviz* 项目的 `dot` 工具生成，需预先安装（大多数发行版包名为 `graphviz`）。

默认输出为 PDF 格式。可通过 `BR2_GRAPH_OUT` 环境变量切换为 PNG、PostScript、SVG 等（所有 `dot` 工具 `-T` 选项支持的格式均可用）。

```
BR2_GRAPH_OUT=svg make graph-depends
```

`graph-depends` 行为可通过 `BR2_GRAPH_DEPS_OPTS` 环境变量设置。可用选项：

- `--depth N` 或 `-d N`：限制依赖深度为 N 层，默认 0 表示无限制。
- `--stop-on PKG` 或 `-s PKG`：在包 `PKG` 处停止绘制。`PKG` 可为包名、通配符、*virtual*（虚包）、*host*（主机包）。该包仍在图中，但不再展开其依赖。
- `--exclude PKG` 或 `-x PKG`：同 `--stop-on`，但图中不显示该包。
- `--transitive`、`--no-transitive`：是否绘制传递依赖。默认不绘制。
- `--colors R,T,H`：设置根包（R）、目标包（T）、主机包（H）的颜色，默认 `lightblue,grey,gainsboro`。

```
BR2_GRAPH_DEPS_OPTS='-d 3 --no-transitive --colors=red,green,blue' make graph-depends
```

## 8.10 构建时长分析图

如系统构建耗时较长，可分析各包构建耗时以优化构建速度。Buildroot 会收集每个包各步骤的构建时长，并可生成图表。

构建后生成时长分析图：

```
make graph-build
```

生成文件位于 `output/graphs`：

- `build.hist-build.pdf`：按构建顺序排列的各包构建时长直方图
- `build.hist-duration.pdf`：按时长降序排列的各包构建时长直方图
- `build.hist-name.pdf`：按包名排列的各包构建时长直方图
- `build.pie-packages.pdf`：各包构建时长饼图
- `build.pie-steps.pdf`：各步骤总耗时饼图

`graph-build` 目标需安装 Python Matplotlib 和 Numpy 库（大多数发行版为 `python-matplotlib` 和 `python-numpy`），如 Python 版本低于 2.7 还需 `argparse` 模块。

默认输出为 PDF 格式，可用 `BR2_GRAPH_OUT` 环境变量切换为 PNG：

```
BR2_GRAPH_OUT=png make graph-build
```

## 8.11 软件包对文件系统大小的贡献分析

随着目标系统体积增大，了解各 Buildroot 软件包对根文件系统总体积的贡献变得很有价值。为此，Buildroot 会收集每个包安装的文件数据，并据此生成图表和 CSV 文件，详细展示各包的体积贡献。

构建后生成这些数据：

```
make graph-size
```

将生成：

- `output/graphs/graph-size.pdf`：各包对根文件系统总体积贡献的饼图
- `output/graphs/package-size-stats.csv`：各包对根文件系统总体积贡献的 CSV 文件
- `output/graphs/file-size-stats.csv`：每个已安装文件对所属包及总体积贡献的 CSV 文件

`graph-size` 目标需安装 Python Matplotlib 库（大多数发行版为 `python-matplotlib`），如 Python 版本低于 2.7 还需 `argparse` 模块。

如同时长分析图，可用 `BR2_GRAPH_OUT` 环境变量调整输出格式。详见[第 8.9 节 包依赖关系图](https://buildroot.org/downloads/manual/manual.html#graph-depends)。

还可用环境变量 `BR2_GRAPH_SIZE_OPTS` 进一步控制生成的图表。可用选项：

- `--size-limit X` 或 `-l X`：将单个包贡献低于 X 百分比的包合并为 *Others*，默认 X=0.01（即低于 1% 的包合并）。取值范围 `[0.0..1.0]`。
- `--iec`、`--binary`、`--si`、`--decimal`：选择 IEC（二进制，1024 进制）或 SI（十进制，1000 进制，默认）前缀。
- `--biggest-first`：按包体积降序排列，而非升序。

**注意：** 文件系统体积数据仅在完全 clean 重构后才有意义。请先运行 `make clean all` 再用 `make graph-size`。

如需比较两次 Buildroot 编译的根文件系统体积（如调整配置或切换 Buildroot 版本后），可用 `size-stats-compare` 脚本。该脚本以两份 `file-size-stats.csv`（由 `make graph-size` 生成）为输入。详细用法见脚本帮助：

```
utils/size-stats-compare -h
```

## 8.12 顶层并行构建（Top-level parallel build）

**注意：** 本节介绍的为实验性功能，已知在部分常见场景下会出错，请谨慎使用。

Buildroot 一直支持包内并行构建：每个包用 `make -jN`（或等效命令）构建，默认并行度为 CPU 数 + 1，可通过 `BR2_JLEVEL` 配置调整。

直到 2020.02 版本，Buildroot 仍以串行方式构建各包：每次只构建一个包，包间无并行。自 2020.02 起，Buildroot 实验性支持***顶层并行构建***，可并行构建无依赖关系的包，显著缩短构建时间。但该功能仍为实验性，部分场景下已知不可用。

使用顶层并行构建需：

1. 在 Buildroot 配置中启用 `BR2_PER_PACKAGE_DIRECTORIES` 选项
2. 构建时用 `make -jN`

内部实现上，`BR2_PER_PACKAGE_DIRECTORIES` 会启用***每包独立目录（per-package directories）***机制，具体效果如下：

- 不再有全局 *target* 和 *host* 目录，每个包有独立的 *target* 和 *host* 目录，分别位于 `$(O)/per-package/<pkg>/target/` 和 `$(O)/per-package/<pkg>/host/`。这些目录在 `<pkg>` 构建前从依赖包目录同步。编译器和工具只能访问 `<pkg>` 显式依赖包安装的文件。
- 构建结束后，全局 *target* 和 *host* 目录才会被填充，分别位于 `$(O)/target` 和 `$(O)/host`。构建期间这两个目录为空，只有在构建结束时才填充。

## 8.13 高级用法

### 8.13.1 在 Buildroot 外部使用生成的工具链

你可能希望为目标设备编译 Buildroot 未打包的软件或自有程序。此时可直接使用 Buildroot 生成的工具链。

Buildroot 生成的工具链默认位于 `output/host/`。最简单的用法是将 `output/host/bin/` 加入 PATH，然后使用 `ARCH-linux-gcc`、`ARCH-linux-objdump`、`ARCH-linux-ld` 等。

另外，Buildroot 也可通过 `make sdk` 导出工具链及所有已选包的开发文件，生成 SDK。该命令会将 `output/host/` 内容打包为 `<TARGET-TUPLE>_sdk-buildroot.tar.gz`（可通过环境变量 `BR2_SDK_PREFIX` 覆盖），存放于 `output/images/`。

该 tar 包可分发给应用开发者，用于开发尚未打包为 Buildroot 包的应用。

解压 SDK tar 包后，用户需运行 SDK 顶层目录下的 `relocate-sdk.sh` 脚本，以更新所有路径。

如只需准备 SDK 而不打包（如仅移动 `host` 目录或自行打包），可用 `make prepare-sdk`。

如启用 `BR2_PACKAGE_HOST_ENVIRONMENT_SETUP`，`output/host/` 及 SDK 中会安装 `environment-setup` 脚本。可用 `. your/sdk/path/environment-setup` 导出一系列环境变量，便于用 Buildroot SDK 交叉编译项目：`PATH` 会包含 SDK 二进制，标准 autotools 变量会自动设置，`CONFIGURE_FLAGS` 包含 autotools 项目交叉编译的基本 `./configure` 选项，还提供部分实用命令。注意：sourcing 该脚本后，环境仅适用于交叉编译，不再适用于本地编译。

### 8.13.2 在 Buildroot 中使用 `gdb`

Buildroot 支持交叉调试：调试器运行在构建机，通过 `gdbserver` 与目标设备通信，控制程序执行。

操作步骤：

- 如用*内部工具链*（Buildroot 构建），需启用 `BR2_PACKAGE_HOST_GDB`、`BR2_PACKAGE_GDB` 和 `BR2_PACKAGE_GDB_SERVER`，确保交叉 gdb 和 gdbserver 均被构建，gdbserver 安装到目标设备。
- 如用*外部工具链*，应启用 `BR2_TOOLCHAIN_EXTERNAL_GDB_SERVER_COPY`，将外部工具链自带的 gdbserver 拷贝到目标。如外部工具链无交叉 gdb 或 gdbserver，也可让 Buildroot 构建，方法同内部工具链。

调试名为 `foo` 的程序时，目标设备运行：

```
gdbserver :2345 foo
```

此时 `gdbserver` 监听 2345 端口，等待交叉 gdb 连接。

主机端启动交叉 gdb：

```
<buildroot>/output/host/bin/<tuple>-gdb -ix <buildroot>/output/staging/usr/share/buildroot/gdbinit foo
```

注意：`foo` 需带调试符号，建议在其构建目录下运行该命令（`output/target/` 下的二进制已剥离）。

`<buildroot>/output/staging/usr/share/buildroot/gdbinit` 文件会告知交叉 gdb 目标库文件位置。

最后，在交叉 gdb 中连接目标：

```
(gdb) target remote <target ip address>:2345
```

### 8.13.3 在 Buildroot 中使用 `ccache`

[ccache](http://ccache.samba.org/) 是编译器缓存工具。它缓存每次编译生成的目标文件，后续相同源码（编译器及参数一致）可直接复用缓存，加快多次相似全量构建。

Buildroot 集成了 `ccache` 支持。只需在 `Build options` 启用“Enable compiler cache”，即可自动构建并为所有主机和目标编译启用 `ccache`。

缓存目录由 `BR2_CCACHE_DIR` 配置项指定，默认 `$HOME/.buildroot-ccache`。该目录位于 Buildroot 输出目录之外，便于多个 Buildroot 构建共享。如需清理缓存，直接删除该目录即可。

可用 `make ccache-stats` 查看缓存统计（大小、命中/未命中等）。

`ccache-options` make 目标和 `CCACHE_OPTIONS` 变量可用于通用 ccache 操作。例如：

```
# 设置缓存大小上限
make CCACHE_OPTIONS="--max-size=5G" ccache-options

# 清零统计计数器
make CCACHE_OPTIONS="--zero-stats" ccache-options
```

`ccache` 会对源码和编译参数做哈希。若编译参数不同，则不会复用缓存。许多编译参数包含绝对路径（如 staging 目录），因此更换输出目录会导致大量缓存未命中。

为避免此问题，Buildroot 提供“Use relative paths”选项（`BR2_CCACHE_USE_BASEDIR`），会将输出目录内的绝对路径重写为相对路径，从而更换输出目录时不影响缓存命中。

缺点是目标文件中的路径也变为相对路径，调试时需先切换到输出目录。

详见 [ccache 手册“在不同目录编译”章节](https://ccache.samba.org/manual.html#_compiling_in_different_directories)。

启用 `BR2_CCACHE=y` 后：

- Buildroot 构建过程会用 `ccache`
- 在 Buildroot 外部（如直接调用交叉编译器或用 SDK）不会用 `ccache`

可用 `BR2_USE_CCACHE` 环境变量覆盖此行为：设为 `1` 时启用（Buildroot 构建默认），未设或非 `1` 时禁用。



### 8.13.4 下载包的位置

Buildroot 下载的各类 tar 包均存储在 `BR2_DL_DIR`，默认是 `dl` 目录。如需保留一份与 tar 包配套、可复现的 Buildroot 版本，可直接复制该目录。这样可确保工具链和目标文件系统可用完全相同的源码重建。

如维护多个 Buildroot 树，建议用共享下载目录。可将 `BR2_DL_DIR` 环境变量指向该目录，此时会覆盖 Buildroot 配置中的 `BR2_DL_DIR`。可在 `<~/.bashrc>` 添加：

```
 export BR2_DL_DIR=<shared download location>
```

下载目录也可在 `.config` 文件用 `BR2_DL_DIR` 选项设置，但该值会被环境变量覆盖。

### 8.13.5 包专用 make 目标

运行 `make <package>` 会构建并安装该包及其依赖。

依赖 Buildroot 基础设施的软件包有许多专用 make 目标，可独立调用：

```
make <package>-<target>
```

包构建目标（按执行顺序）：

| 命令/目标         | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| `source`          | 获取源码（下载 tar 包、克隆源码仓库等）                      |
| `depends`         | 构建并安装构建该包所需的所有依赖                             |
| `extract`         | 将源码放入包构建目录（解包、复制源码等）                     |
| `patch`           | 应用补丁（如有）                                             |
| `configure`       | 运行配置命令（如有）                                         |
| `build`           | 运行编译命令                                                 |
| `install-staging` | ***目标包：*** 安装到 staging 目录（如有必要）               |
| `install-target`  | ***目标包：*** 安装到 target 目录（如有必要）                |
| `install`         | ***目标包：*** 运行前两步安装命令；***主机包：*** 安装到 host 目录 |

其他常用 make 目标：

| 命令/目标                 | 说明                                                         |
| ------------------------- | ------------------------------------------------------------ |
| `show-depends`            | 显示构建该包所需的一阶依赖                                   |
| `show-recursive-depends`  | 递归显示构建该包所需的所有依赖                               |
| `show-rdepends`           | 显示直接依赖该包的包（一阶反向依赖）                         |
| `show-recursive-rdepends` | 递归显示所有依赖该包的包（直接或间接）                       |
| `graph-depends`           | 生成该包的依赖关系图，详见[依赖关系图章节](https://buildroot.org/downloads/manual/manual.html#graph-depends) |
| `graph-rdepends`          | 生成该包的反向依赖关系图                                     |
| `graph-both-depends`      | 生成该包的正反向依赖关系图                                   |
| `dirclean`                | 删除整个包的构建目录                                         |
| `reinstall`               | 重新运行安装命令                                             |
| `rebuild`                 | 重新运行编译命令（仅适用于 OVERRIDE_SRCDIR 或直接修改构建目录源码） |
| `reconfigure`             | 重新运行配置命令并重编译（仅适用于 OVERRIDE_SRCDIR 或直接修改构建目录源码） |

### 8.13.6 开发阶段使用 Buildroot

Buildroot 正常流程为：下载 tar 包、解包、配置、编译、安装。源码解包到 `output/build/<package>-<version>`，该目录为临时目录，`make clean` 时会被删除并在下次 `make` 时重建。即使源码为 Git 或 SVN 仓库，Buildroot 也会先打包再解包，流程一致。

此流程适合 Buildroot 作为集成工具使用。但如需开发某组件，直接在 `output/build/<package>-<version>` 修改源码并不合适，因为 `make clean` 会删除该目录。

为此，Buildroot 提供 `<pkg>_OVERRIDE_SRCDIR` 机制。Buildroot 会读取 override 文件，允许用户指定某些包的源码路径。

override 文件默认位置为 `$(CONFIG_DIR)/local.mk`，由 `BR2_PACKAGE_OVERRIDE_FILE` 配置。`$(CONFIG_DIR)` 为 Buildroot `.config` 所在目录，即：

- 树内构建（未用 O=）时为 Buildroot 源码主目录
- 树外构建（用 O=）时为输出目录

如需自定义 override 文件位置，可用 `BR2_PACKAGE_OVERRIDE_FILE` 配置。

override 文件内容格式：

```
<pkg1>_OVERRIDE_SRCDIR = /path/to/pkg1/sources
<pkg2>_OVERRIDE_SRCDIR = /path/to/pkg2/sources
```

示例：

```
LINUX_OVERRIDE_SRCDIR = /home/bob/linux/
BUSYBOX_OVERRIDE_SRCDIR = /home/bob/busybox/
```

如为某包定义了 `<pkg>_OVERRIDE_SRCDIR`，Buildroot 不再下载、解包、打补丁，而是直接用指定目录源码，`make clean` 也不会影响该目录。这样可将 Buildroot 指向你用 Git、SVN 等管理的源码目录。Buildroot 会用 *rsync* 将 `<pkg>_OVERRIDE_SRCDIR` 下源码同步到 `output/build/<package>-custom/`。

此机制建议结合 `make <pkg>-rebuild` 和 `make <pkg>-reconfigure` 使用。`make <pkg>-rebuild all` 会用 rsync 同步源码（仅同步变更文件），并重启该包的构建流程。

如上例，开发者可在 `/home/bob/linux` 修改源码后运行：

```
make linux-rebuild all
```

几秒后即可在 `output/images` 得到更新的内核镜像。同理，修改 `/home/bob/busybox` 后：

```
make busybox-rebuild all
```

`output/images` 下的根文件系统镜像即包含更新后的 BusyBox。



# 第 9 章 项目定制

对于特定项目，你可能需要执行的典型操作包括：

- 配置 Buildroot（包括构建选项和工具链、引导加载程序、内核、软件包和文件系统镜像类型的选择）
- 配置其他组件，如 Linux 内核和 BusyBox（原文：BusyBox）
- 定制生成的目标文件系统
  - 在目标文件系统上添加或覆盖文件（使用 `BR2_ROOTFS_OVERLAY`）
  - 修改或删除目标文件系统上的文件（使用 `BR2_ROOTFS_POST_BUILD_SCRIPT`）
  - 在生成文件系统镜像前运行任意命令（使用 `BR2_ROOTFS_POST_BUILD_SCRIPT`）
  - 设置文件权限和所有权（使用 `BR2_ROOTFS_DEVICE_TABLE`）
  - 添加自定义设备节点（使用 `BR2_ROOTFS_STATIC_DEVICE_TABLE`）
- 添加自定义用户账户（使用 `BR2_ROOTFS_USERS_TABLES`）
- 在生成文件系统镜像后运行任意命令（使用 `BR2_ROOTFS_POST_IMAGE_SCRIPT`）
- 为某些软件包添加项目专属补丁（使用 `BR2_GLOBAL_PATCH_DIR`）
- 添加项目专属软件包

关于此类*项目专属*定制的重要说明：请仔细考虑哪些更改确实仅针对你的项目，哪些更改对项目外的开发者也有用。Buildroot 社区强烈建议并鼓励将改进、软件包和板级支持上游到官方 Buildroot 项目。当然，有时由于更改高度专用或专有，无法或不适合上游。

本章介绍如何在 Buildroot 中进行此类项目专属定制，以及如何以可复现的方式存储这些定制内容，即使在执行 *make clean* 后也能构建相同的镜像。按照推荐策略，你甚至可以使用同一个 Buildroot 树来构建多个不同的项目！

## 9.1 推荐的目录结构

在为你的项目定制 Buildroot 时，你将创建一个或多个项目专属文件，这些文件需要存放在某处。虽然大多数文件可以放在*任意*位置（因为其路径会在 Buildroot 配置中指定），但 Buildroot 开发者推荐采用本节描述的特定目录结构。

与该目录结构正交的是，你可以选择将其放置在 Buildroot 树内部，或通过 br2-external（原文：br2-external）树放在外部。这两种方式都可以，选择权在你。

```
+-- board/
|   +-- <company>/
|       +-- <boardname>/
|           +-- linux.config
|           +-- busybox.config
|           +-- <其他配置文件>
|           +-- post_build.sh
|           +-- post_image.sh
|           +-- rootfs_overlay/
|           |   +-- etc/
|           |   +-- <一些文件>
|           +-- patches/
|               +-- foo/
|               |   +-- <一些补丁>
|               +-- libbar/
|                   +-- <其他补丁>
|
+-- configs/
|   +-- <boardname>_defconfig
|
+-- package/
|   +-- <company>/
|       +-- Config.in（如果未使用 br2-external 树）
|       +-- <company>.mk（如果未使用 br2-external 树）
|       +-- package1/
|       |    +-- Config.in
|       |    +-- package1.mk
|       +-- package2/
|           +-- Config.in
|           +-- package2.mk
|
+-- Config.in（如果使用 br2-external 树）
+-- Makefile（如果使用自定义顶层 makefile）
+-- external.mk（如果使用 br2-external 树）
+-- external.desc（如果使用 br2-external 树）
```

上述文件的详细说明将在本章后续部分给出。

注意：如果你选择将该结构放在 Buildroot 树外部（即 br2-external 树），则 <company> 和可能的 <boardname> 组件可以省略。

### 9.1.1 分层定制的实现

用户经常会有多个相关项目，这些项目部分需要相同的定制。与其为每个项目重复这些定制，推荐采用分层定制方法，如本节所述。

Buildroot 提供的几乎所有定制方法（如 post-build 脚本和 root 文件系统覆盖）都支持以空格分隔的项目列表。指定的项目总是按顺序（从左到右）处理。通过创建多个项目（如一个用于通用定制，另一个用于项目专属定制），可以避免不必要的重复。每一层通常对应 `board/<company>/` 下的一个独立目录。根据你的项目情况，甚至可以引入多于两层。

例如，用户有两个定制层 *common* 和 *fooboard*，其目录结构如下：

```
+-- board/
    +-- <company>/
        +-- common/
        |   +-- post_build.sh
        |   +-- rootfs_overlay/
        |   |   +-- ...
        |   +-- patches/
        |       +-- ...
        |
        +-- fooboard/
            +-- linux.config
            +-- busybox.config
            +-- <其他配置文件>
            +-- post_build.sh
            +-- rootfs_overlay/
            |   +-- ...
            +-- patches/
                +-- ...
```

例如，用户将 `BR2_GLOBAL_PATCH_DIR` 配置项设置为：

```
BR2_GLOBAL_PATCH_DIR="board/<company>/common/patches board/<company>/fooboard/patches"
```

则会先应用 *common* 层的补丁，再应用 *fooboard* 层的补丁。

### 9.1.2 自定义顶层 Makefile（原文：Makefile）

通常你会从 buildroot 源码目录启动 Buildroot，指定 `BR2_EXTERNAL` 和 `O` 到正确的位置以进行构建。你可以通过在 br2-external 中添加一个 Makefile 来简化此过程，该文件设置这些变量并调用 buildroot。

你还可以为各种任务在此 Makefile 中添加自定义规则，例如将多个配置集成到单一镜像、上传到发布服务器或测试设备、包含多个 br2-external 配置等。

一个基础的 Makefile 如下。假设 buildroot 源码位于 `buildroot` 子目录（如作为 git 子模块）。它确保下载目录在不同构建间共享，并将输出目录组织在 `outputs/` 下。

```
# SPDX-License-Identifier: GPL-2.0

# 通过禁用默认规则避免意外
MAKEFLAGS += --no-builtin-rules
.SUFFIXES:

THIS_EXTERNAL_PATH := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

# 将下载内容放在此目录而不是 Buildroot 目录
ifeq ($(BR2_DL_DIR),)
BR2_DL_DIR = $(THIS_EXTERNAL_PATH)/dl
endif

OUTPUT_BASEDIR = $(THIS_EXTERNAL_PATH)/output
OUTPUT_DIR = $(OUTPUT_BASEDIR)/$(patsubst %_defconfig,%,$@)

MAKE_BUILDROOT = $(MAKE) -C $(THIS_EXTERNAL_PATH)/buildroot BR2_EXTERNAL=$(THIS_EXTERNAL_PATH)

%: $(THIS_EXTERNAL_PATH)/configs/%
        $(MAKE_BUILDROOT) O=$(OUTPUT_DIR) $@
        sed -i /^BR2_DL_DIR=.*/s%%BR2_DL_DIR=$(BR2_DL_DIR)% $(OUTPUT_DIR)/.config
```





## 9.2 保持定制内容在 Buildroot 之外

如[9.1节“推荐的目录结构”](https://buildroot.org/downloads/manual/manual.html#customize-dir-structure)中简要提到，你可以将项目专属定制内容放在两个位置：

- 直接放在 Buildroot 树内，通常通过版本控制系统的分支进行管理，这样升级到新版本 Buildroot 时会更方便。
- 放在 Buildroot 树外，使用 *br2-external*（原文：br2-external）机制。该机制允许将软件包配方、板级支持和配置文件放在 Buildroot 树外，同时又能很好地集成到构建逻辑中。我们称这个位置为 *br2-external 树*。本节将介绍如何使用 br2-external 机制以及 br2-external 树中需要提供哪些内容。

可以通过设置 `BR2_EXTERNAL` make 变量为 br2-external 树的路径（可以是一个或多个）来让 Buildroot 使用 br2-external 树。该变量可以在任何 Buildroot `make` 命令中传递。它会自动保存在输出目录下的隐藏文件 `.br2-external.mk` 中。因此，无需在每次 `make` 时都传递 `BR2_EXTERNAL`。当然，你可以随时通过传递新值来更改它，也可以通过传递空值来移除。

**注意**：br2-external 树的路径可以是绝对路径或相对路径。如果是相对路径，需要注意它是相对于 Buildroot 源码目录（***不是*** Buildroot 输出目录）来解释的。

**注意**：如果你使用的是 Buildroot 2016.11 之前的 br2-external 树，需要先进行转换，才能与 Buildroot 2016.11 及以后版本配合使用。转换方法见[27.2节“迁移到2016.11”](https://buildroot.org/downloads/manual/manual.html#br2-external-converting)。

一些示例：

```
buildroot/ $ make BR2_EXTERNAL=/path/to/foo menuconfig
```

从此以后，将会使用 `/path/to/foo` br2-external 树中的定义：

```
buildroot/ $ make
buildroot/ $ make legal-info
```

我们可以随时切换到另一个 br2-external 树：

```
buildroot/ $ make BR2_EXTERNAL=/where/we/have/bar xconfig
```

也可以同时使用多个 br2-external 树：

```
buildroot/ $ make BR2_EXTERNAL=/path/to/foo:/where/we/have/bar menuconfig
```

或者禁用所有 br2-external 树：

```
buildroot/ $ make BR2_EXTERNAL= xconfig
```

### 9.2.1 br2-external 树的布局

一个 br2-external 树至少要包含以下三个文件，后续章节会详细介绍：

- `external.desc`
- `external.mk`
- `Config.in`

除了这些必需文件外，br2-external 树中还可以有其他可选内容，如 `configs/` 或 `provides/` 目录。它们也会在后续章节中介绍。

后面还会有一个完整的 br2-external 树布局示例。

#### `external.desc` 文件

该文件描述 br2-external 树：*名称*和*描述*。

该文件为逐行格式，每行以关键字开头，后跟冒号和一个或多个空格，再跟要赋值的内容。目前识别两个关键字：

- `name`，必需，定义 br2-external 树的名称。该名称只能使用 ASCII 字符集 `[A-Za-z0-9_]`，其他字符均不允许。Buildroot 会设置变量 `BR2_EXTERNAL_$(NAME)_PATH` 为 br2-external 树的绝对路径，这样你可以用它来引用 br2-external 树。该变量在 Kconfig 和 Makefile 中都可用，因此你可以用它来引用 Kconfig 文件（见下文），也可以在 Makefile 中引用其他文件（如数据文件）。

  **注意**：由于可以同时使用多个 br2-external 树，这个名称会被 Buildroot 用来为每个树生成变量。该名称用于标识你的 br2-external 树，所以请尽量取一个有代表性的、相对唯一的名字，避免与其他 br2-external 树冲突，尤其是你打算与第三方共享或使用第三方 br2-external 树时。

- `desc`，可选，为 br2-external 树提供简短描述。应控制在一行内，内容较为自由（见下文），用于显示 br2-external 树相关信息（如在 defconfig 文件列表上方或 menuconfig 提示中）；因此应尽量简洁（建议不超过40个字符）。该描述会存储在变量 `BR2_EXTERNAL_$(NAME)_DESC` 中。

名称与变量示例：

- `FOO` → `BR2_EXTERNAL_FOO_PATH`
- `BAR_42` → `BR2_EXTERNAL_BAR_42_PATH`

以下示例假设名称为 `BAR_42`。

**注意**：`BR2_EXTERNAL_$(NAME)_PATH` 和 `BR2_EXTERNAL_$(NAME)_DESC` 在 Kconfig 和 Makefile 中都可用，也会导出到环境变量，因此在 post-build、post-image 和 in-fakeroot 脚本中也可用。

#### `Config.in` 和 `external.mk` 文件

这两个文件（可以为空）可用于定义软件包配方（即 `foo/Config.in` 和 `foo/foo.mk`，与 Buildroot 自带软件包类似）或其他自定义配置选项和 make 逻辑。

Buildroot 会自动包含每个 br2-external 树的 `Config.in`，使其出现在顶层配置菜单中，并包含每个 br2-external 树的 `external.mk`，与其他 makefile 逻辑一起处理。

主要用途是存放软件包配方。推荐写法如下：

`Config.in` 文件：

```
source "$BR2_EXTERNAL_BAR_42_PATH/package/package1/Config.in"
source "$BR2_EXTERNAL_BAR_42_PATH/package/package2/Config.in"
```

`external.mk` 文件：

```
include $(sort $(wildcard $(BR2_EXTERNAL_BAR_42_PATH)/package/*/*.mk))
```

然后在 `$(BR2_EXTERNAL_BAR_42_PATH)/package/package1` 和 `$(BR2_EXTERNAL_BAR_42_PATH)/package/package2` 下创建常规 Buildroot 软件包配方，具体方法见[第18章“向 Buildroot 添加新软件包”](https://buildroot.org/downloads/manual/manual.html#adding-packages)。如有需要，也可以按 <boardname> 分组。

你也可以在 `Config.in` 中定义自定义配置选项，在 `external.mk` 中定义自定义 make 逻辑。

#### `configs/` 目录

可以在 br2-external 树的 `configs` 子目录下存放 Buildroot defconfig 文件。Buildroot 会自动在 `make list-defconfigs` 输出中显示它们，并允许用常规 `make <name>_defconfig` 命令加载。它们会在 *make list-defconfigs* 输出中显示在 `External configs` 标签下，标签名为 br2-external 树的名称。

**注意**：如果同名 defconfig 文件在多个 br2-external 树中都存在，则以最后一个 br2-external 树中的为准。因此可以覆盖 Buildroot 自带或其他 br2-external 树中的 defconfig。



#### `provides/` 目录

对于某些软件包，Buildroot 提供了两个（或更多）API 兼容实现的选择。例如，可以选择 libjpeg 或 jpeg-turbo；可以选择 openssl 或 libressl；也可以选择已知的、预配置的工具链……

br2-external（原文：br2-external）可以通过提供一组定义这些替代项的文件来扩展这些选择：

- `provides/toolchains.in` 定义预配置工具链，将会在工具链选择中列出；
- `provides/jpeg.in` 定义 libjpeg 的替代实现；
- `provides/openssl.in` 定义 openssl 的替代实现；
- `provides/skeleton.in` 定义 skeleton（原文：skeleton）的替代实现；
- `provides/init.in` 定义 init 系统的替代实现，可用于为 init 选择默认 skeleton。

#### 自由格式内容

你可以在这里存放所有板级专属配置文件，如内核配置、root 文件系统覆盖或 Buildroot 允许设置位置的其他配置文件（通过 `BR2_EXTERNAL_$(NAME)_PATH` 变量）。例如，可以如下设置全局补丁目录、rootfs 覆盖和内核配置文件的路径（如通过 `make menuconfig` 填写这些选项）：

```
BR2_GLOBAL_PATCH_DIR=$(BR2_EXTERNAL_BAR_42_PATH)/patches/
BR2_ROOTFS_OVERLAY=$(BR2_EXTERNAL_BAR_42_PATH)/board/<boardname>/overlay/
BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE=$(BR2_EXTERNAL_BAR_42_PATH)/board/<boardname>/kernel.config
```

#### 额外的 Linux 内核扩展

可以通过在 br2-external 树根目录下的 `linux/` 目录中存放扩展，来添加额外的 Linux 内核扩展（详见[18.22.2节“linux-kernel-extensions”](https://buildroot.org/downloads/manual/manual.html#linux-kernel-ext)）。

#### 示例布局

以下是一个使用了 br2-external 所有特性的示例布局（为便于说明，相关文件的示例内容会在其上方展示，内容均为虚构）：

```
/path/to/br2-ext-tree/
  |- external.desc
  |     |name: BAR_42
  |     |desc: Example br2-external tree
  |     `----
  |
  |- Config.in
  |     |source "$BR2_EXTERNAL_BAR_42_PATH/toolchain/toolchain-external-mine/Config.in.options"
  |     |source "$BR2_EXTERNAL_BAR_42_PATH/package/pkg-1/Config.in"
  |     |source "$BR2_EXTERNAL_BAR_42_PATH/package/pkg-2/Config.in"
  |     |source "$BR2_EXTERNAL_BAR_42_PATH/package/my-jpeg/Config.in"
  |     |
  |     |config BAR_42_FLASH_ADDR
  |     |    hex "my-board flash address"
  |     |    default 0x10AD
  |     `----
  |
  |- external.mk
  |     |include $(sort $(wildcard $(BR2_EXTERNAL_BAR_42_PATH)/package/*/*.mk))
  |     |include $(sort $(wildcard $(BR2_EXTERNAL_BAR_42_PATH)/toolchain/*/*.mk))
  |     |
  |     |flash-my-board:
  |     |    $(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/flash-image \
  |     |        --image $(BINARIES_DIR)/image.bin \
  |     |        --address $(BAR_42_FLASH_ADDR)
  |     `----
  |
  |- package/pkg-1/Config.in
  |     |config BR2_PACKAGE_PKG_1
  |     |    bool "pkg-1"
  |     |    help
  |     |      Some help about pkg-1
  |     `----
  |- package/pkg-1/pkg-1.hash
  |- package/pkg-1/pkg-1.mk
  |     |PKG_1_VERSION = 1.2.3
  |     |PKG_1_SITE = /some/where/to/get/pkg-1
  |     |PKG_1_LICENSE = blabla
  |     |
  |     |define PKG_1_INSTALL_INIT_SYSV
  |     |    $(INSTALL) -D -m 0755 $(PKG_1_PKGDIR)/S99my-daemon \
  |     |                          $(TARGET_DIR)/etc/init.d/S99my-daemon
  |     |endef
  |     |
  |     |$(eval $(autotools-package))
  |     `----
  |- package/pkg-1/S99my-daemon
  |
  |- package/pkg-2/Config.in
  |- package/pkg-2/pkg-2.hash
  |- package/pkg-2/pkg-2.mk
  |
  |- provides/jpeg.in
  |     |config BR2_PACKAGE_MY_JPEG
  |     |    bool "my-jpeg"
  |     `----
  |- package/my-jpeg/Config.in
  |     |config BR2_PACKAGE_PROVIDES_JPEG
  |     |    default "my-jpeg" if BR2_PACKAGE_MY_JPEG
  |     `----
  |- package/my-jpeg/my-jpeg.mk
  |     |# 这是一个常规 package .mk 文件
  |     |MY_JPEG_VERSION = 1.2.3
  |     |MY_JPEG_SITE = https://example.net/some/place
  |     |MY_JPEG_PROVIDES = jpeg
  |     |$(eval $(autotools-package))
  |     `----
  |
  |- provides/init.in
  |     |config BR2_INIT_MINE
  |     |    bool "my custom init"
  |     |    select BR2_PACKAGE_MY_INIT
  |     |    select BR2_PACKAGE_SKELETON_INIT_MINE if BR2_ROOTFS_SKELETON_DEFAULT
  |     `----
  |
  |- provides/skeleton.in
  |     |config BR2_ROOTFS_SKELETON_MINE
  |     |    bool "my custom skeleton"
  |     |    select BR2_PACKAGE_SKELETON_MINE
  |     `----
  |- package/skeleton-mine/Config.in
  |     |config BR2_PACKAGE_SKELETON_MINE
  |     |    bool
  |     |    select BR2_PACKAGE_HAS_SKELETON
  |     |
  |     |config BR2_PACKAGE_PROVIDES_SKELETON
  |     |    default "skeleton-mine" if BR2_PACKAGE_SKELETON_MINE
  |     `----
  |- package/skeleton-mine/skeleton-mine.mk
  |     |SKELETON_MINE_ADD_TOOLCHAIN_DEPENDENCY = NO
  |     |SKELETON_MINE_ADD_SKELETON_DEPENDENCY = NO
  |     |SKELETON_MINE_PROVIDES = skeleton
  |     |SKELETON_MINE_INSTALL_STAGING = YES
  |     |$(eval $(generic-package))
  |     `----
  |
  |- provides/toolchains.in
  |     |config BR2_TOOLCHAIN_EXTERNAL_MINE
  |     |    bool "my custom toolchain"
  |     |    depends on BR2_some_arch
  |     |    select BR2_INSTALL_LIBSTDCPP
  |     `----
  |- toolchain/toolchain-external-mine/Config.in.options
  |     |if BR2_TOOLCHAIN_EXTERNAL_MINE
  |     |config BR2_TOOLCHAIN_EXTERNAL_PREFIX
  |     |    default "arch-mine-linux-gnu"
  |     |config BR2_PACKAGE_PROVIDES_TOOLCHAIN_EXTERNAL
  |     |    default "toolchain-external-mine"
  |     |endif
  |     `----
  |- toolchain/toolchain-external-mine/toolchain-external-mine.mk
  |     |TOOLCHAIN_EXTERNAL_MINE_SITE = https://example.net/some/place
  |     |TOOLCHAIN_EXTERNAL_MINE_SOURCE = my-toolchain.tar.gz
  |     |$(eval $(toolchain-external-package))
  |     `----
  |
  |- linux/Config.ext.in
  |     |config BR2_LINUX_KERNEL_EXT_EXAMPLE_DRIVER
  |     |    bool "example-external-driver"
  |     |    help
  |     |      Example external driver
  |     |---
  |- linux/linux-ext-example-driver.mk
  |
  |- configs/my-board_defconfig
  |     |BR2_GLOBAL_PATCH_DIR="$(BR2_EXTERNAL_BAR_42_PATH)/patches/"
  |     |BR2_ROOTFS_OVERLAY="$(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/overlay/"
  |     |BR2_ROOTFS_POST_IMAGE_SCRIPT="$(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/post-image.sh"
  |     |BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE="$(BR2_EXTERNAL_BAR_42_PATH)/board/my-board/kernel.config"
  |     `----
  |
  |- patches/linux/0001-some-change.patch
  |- patches/linux/0002-some-other-change.patch
  |- patches/busybox/0001-fix-something.patch
  |
  |- board/my-board/kernel.config
  |- board/my-board/overlay/var/www/index.html
  |- board/my-board/overlay/var/www/my.css
  |- board/my-board/flash-image
  `- board/my-board/post-image.sh
        |#!/bin/sh
        |generate-my-binary-image \
        |    --root ${BINARIES_DIR}/rootfs.tar \
        |    --kernel ${BINARIES_DIR}/zImage \
        |    --dtb ${BINARIES_DIR}/my-board.dtb \
        |    --output ${BINARIES_DIR}/image.bin
        `----
```

br2-external 树会在 menuconfig（原文：menuconfig）中显示（布局已展开）：

```
External options  --->
    *** Example br2-external tree (in /path/to/br2-ext-tree/)
    [ ] pkg-1
    [ ] pkg-2
    (0x10AD) my-board flash address
```

如果你使用了多个 br2-external 树，效果如下（布局已展开，第二个名称为 `FOO_27`，但 `external.desc` 没有 `desc:` 字段）：

```
External options  --->
    Example br2-external tree  --->
        *** Example br2-external tree (in /path/to/br2-ext-tree)
        [ ] pkg-1
        [ ] pkg-2
        (0x10AD) my-board flash address
    FOO_27  --->
        *** FOO_27 (in /path/to/another-br2-ext)
        [ ] foo
        [ ] bar
```

此外，jpeg 提供者会在 jpeg 选择项中显示：

```
Target packages  --->
    Libraries  --->
        Graphics  --->
            [*] jpeg support
                jpeg variant ()  --->
                    ( ) jpeg
                    ( ) jpeg-turbo
                        *** jpeg from: Example br2-external tree ***
                    (X) my-jpeg
                        *** jpeg from: FOO_27 ***
                    ( ) another-jpeg
```

工具链同理：

```
Toolchain  --->
    Toolchain ()  --->
        ( ) Custom toolchain
            *** Toolchains from: Example br2-external tree ***
        (X) my custom toolchain
```

**注意**：`toolchain/toolchain-external-mine/Config.in.options` 中的工具链选项不会出现在 `Toolchain` 菜单中。它们必须在 br2-external 顶层 `Config.in` 中显式包含，因此会出现在 `External options` 菜单中。



## 9.3 保存 Buildroot 配置

可以使用命令 `make savedefconfig` 保存 Buildroot 配置。

该命令会去除所有为默认值的配置选项，仅保留实际更改的内容，结果存储在名为 `defconfig` 的文件中。如需保存到其他位置，可在 Buildroot 配置中更改 `BR2_DEFCONFIG` 选项，或用 `make savedefconfig BR2_DEFCONFIG=<path-to-defconfig>` 指定路径。

推荐将 defconfig 文件存放在 `configs/<boardname>_defconfig`。这样配置会被 `make list-defconfigs` 列出，并可通过 `make <boardname>_defconfig` 恢复。

当然，也可以将该文件复制到任意位置，并用 `make defconfig BR2_DEFCONFIG=<path-to-defconfig-file>` 重新构建。

## 9.4 保存其他组件的配置

如对 BusyBox、Linux 内核、Barebox、U-Boot 和 uClibc 做了配置更改，也应保存其配置文件。Buildroot 为每个组件都提供了配置项用于指定输入配置文件路径，例如 `BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE`。要保存这些配置文件，先将配置项指向你希望保存的位置，然后用下述辅助目标实际保存配置。

如[第 9.1 节 推荐目录结构](https://buildroot.org/downloads/manual/manual.html#customize-dir-structure)所述，推荐将这些配置文件存放在 `board/<company>/<boardname>/foo.config`。

注意：请在更改 `BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE` 等选项*之前*先创建配置文件，否则 Buildroot 会尝试访问尚不存在的配置文件并报错。可通过 `make linux-menuconfig` 等命令创建配置文件。

Buildroot 提供了若干辅助目标，便于保存配置文件：

- `make linux-update-defconfig`：将 Linux 配置保存到 `BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE` 指定路径，并去除默认值（仅适用于 2.6.33 及以上内核，早期内核用 `make linux-update-config`）。
- `make busybox-update-config`：将 BusyBox 配置保存到 `BR2_PACKAGE_BUSYBOX_CONFIG` 指定路径。
- `make uclibc-update-config`：将 uClibc 配置保存到 `BR2_UCLIBC_CONFIG` 指定路径。
- `make barebox-update-defconfig`：将 Barebox 配置保存到 `BR2_TARGET_BAREBOX_CUSTOM_CONFIG_FILE` 指定路径。
- `make uboot-update-defconfig`：将 U-Boot 配置保存到 `BR2_TARGET_UBOOT_CUSTOM_CONFIG_FILE` 指定路径。
- 对于 at91bootstrap3，没有辅助命令，需手动将配置文件复制到 `BR2_TARGET_AT91BOOTSTRAP3_CUSTOM_CONFIG_FILE`。



## 9.5 定制生成的目标文件系统

除了通过 `make *config` 更改配置外，还有其他几种方式可以定制生成的目标文件系统。

推荐的两种方法（可共存）是 root 文件系统覆盖（overlay）和 post build 脚本。

- Root 文件系统覆盖（`BR2_ROOTFS_OVERLAY`）

  文件系统覆盖是一棵文件树，会在目标文件系统构建完成后直接拷贝到目标文件系统上。启用该功能需在“System configuration”菜单中设置 `BR2_ROOTFS_OVERLAY` 配置项为 overlay 根目录。你甚至可以指定多个 overlay，使用空格分隔。若指定相对路径，则相对于 Buildroot 根目录。版本控制系统的隐藏目录（如 `.git`、`.svn`、`.hg` 等）、名为 `.empty` 的文件和以 `~` 结尾的文件不会被拷贝。当启用 `BR2_ROOTFS_MERGED_USR` 时，overlay 不能包含 */bin*、*/lib* 或 */sbin* 目录，因为 Buildroot 会将它们创建为指向 */usr* 下相关文件夹的符号链接。此时，若 overlay 有程序或库，应放在 */usr/bin*、*/usr/sbin* 和 */usr/lib*。如[9.1节“推荐的目录结构”](https://buildroot.org/downloads/manual/manual.html#customize-dir-structure)所示，推荐 overlay 路径为 `board/<company>/<boardname>/rootfs-overlay`。

- Post-build 脚本（`BR2_ROOTFS_POST_BUILD_SCRIPT`）

  Post-build 脚本是在 Buildroot 构建所有选定软件后、生成 rootfs 镜像前调用的 shell 脚本。启用该功能需在“System configuration”菜单中将 `BR2_ROOTFS_POST_BUILD_SCRIPT` 配置项设置为 post-build 脚本列表（空格分隔）。若指定相对路径，则相对于 Buildroot 根目录。通过 post-build 脚本可以删除或修改目标文件系统中的任意文件，但应谨慎使用。如果某个软件包生成了错误或不需要的文件，建议修复该软件包，而不是用 post-build 脚本清理。如[9.1节“推荐的目录结构”](https://buildroot.org/downloads/manual/manual.html#customize-dir-structure)所示，推荐脚本路径为 `board/<company>/<boardname>/post_build.sh`。Post-build 脚本运行时，当前工作目录为 Buildroot 主目录，目标文件系统路径作为第一个参数传递。如果 `BR2_ROOTFS_POST_SCRIPT_ARGS` 不为空，这些参数也会传递给脚本。所有脚本接收相同参数，无法为每个脚本单独设置参数。`注意：+BR2_ROOTFS_POST_SCRIPT_ARGS+ 的参数也会传递给 post-image 和 post-fakeroot 脚本。如果只想为 post-build 脚本使用特定参数，可用 +BR2_ROOTFS_POST_BUILD_SCRIPT_ARGS+。`

此外，你还可以使用如下环境变量：

- `BR2_CONFIG`：Buildroot .config 文件路径
- `CONFIG_DIR`：包含 .config 文件的目录，即顶层 Buildroot Makefile 所在目录（适用于树内和树外构建）
- `HOST_DIR`、`STAGING_DIR`、`TARGET_DIR`：见[18.6.2节“generic-package 参考”](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)
- `BUILD_DIR`：软件包解压和构建目录
- `BINARIES_DIR`：所有二进制文件（镜像）存放目录
- `BASE_DIR`：输出基础目录
- `PARALLEL_JOBS`：并行进程数

下述三种定制目标文件系统的方法不推荐使用：

- 直接修改目标文件系统

  临时修改时，可以直接修改 `output/target/` 下的目标文件系统，然后运行 `make` 重新生成镜像。此方法可对目标文件系统做任意更改，但如果执行 `make clean`，这些更改会丢失。某些情况下需要清理 Buildroot 树，详见[8.2节“何时需要完全重建”](https://buildroot.org/downloads/manual/manual.html#full-rebuild)。因此该方法仅适用于快速测试：*更改不会在 `make clean` 后保留*。验证更改后，应通过 overlay 或 post-build 脚本使其持久化。

- 自定义目标 skeleton（`BR2_ROOTFS_SKELETON_CUSTOM`）

  根文件系统镜像是从目标 skeleton 创建的，所有软件包都在其上安装文件。skeleton 会在构建和安装任何软件包前复制到 `output/target` 目录。默认 skeleton 提供标准 Unix 文件系统布局和基础 init 脚本及配置文件。如果默认 skeleton（位于 `system/skeleton`）不满足需求，通常用 overlay 或 post-build 脚本调整即可。但如果默认 skeleton 与需求完全不同，可以使用自定义 skeleton。启用该功能需设置 `BR2_ROOTFS_SKELETON_CUSTOM` 并将 `BR2_ROOTFS_SKELETON_CUSTOM_PATH` 设为自定义 skeleton 路径，均在“System configuration”菜单中。若指定相对路径，则相对于 Buildroot 根目录。自定义 skeleton 不需要包含 */bin*、*/lib* 或 */sbin* 目录，这些会在构建时自动创建。启用 `BR2_ROOTFS_MERGED_USR` 时，自定义 skeleton 也不能包含这些目录，此时程序或库应放在 */usr/bin*、*/usr/sbin* 和 */usr/lib*。该方法不推荐，因为会复制整个 skeleton，无法利用 Buildroot 后续版本对默认 skeleton 的修复和改进。

- Post-fakeroot 脚本（`BR2_ROOTFS_POST_FAKEROOT_SCRIPT`）

  在聚合最终镜像时，部分过程需要 root 权限（如在 `/dev` 创建设备节点、设置文件和目录权限/所有权等）。为避免实际 root 权限，Buildroot 使用 `fakeroot` 模拟 root 权限。虽然不完全等同于 root，但已满足 Buildroot 需求。Post-fakeroot 脚本是在 fakeroot 阶段*结束时*、文件系统镜像生成器调用*前*执行的 shell 脚本，因此在 fakeroot 环境下运行。若需以 root 用户权限修改文件系统，可用 post-fakeroot 脚本。**注意：** 推荐使用现有机制设置文件权限或在 `/dev` 创建节点（见[9.5.1节“设置文件权限和所有权及添加自定义设备节点”](https://buildroot.org/downloads/manual/manual.html#customize-device-permission)），或创建用户（见[9.6节“添加自定义用户账户”](https://buildroot.org/downloads/manual/manual.html#customize-users)）。**注意：** post-build 脚本和 fakeroot 脚本的区别在于，post-build 脚本不在 fakeroot 环境下执行。**注意：** `fakeroot` 仅模拟文件访问权限、类型（常规、块/字符设备等）和 uid/gid，这些都是内存中模拟的。



### 9.5.1 设置文件权限和所有权及添加自定义设备节点

有时需要为文件或设备节点设置特定权限或所有权。例如，某些文件可能需要归 root 所有。由于 post-build 脚本不是以 root 身份运行，除非在脚本中显式使用 fakeroot，否则无法完成这些更改。

为此，Buildroot 提供了*权限表*（permission tables）功能。启用该功能需将 `BR2_ROOTFS_DEVICE_TABLE` 配置项设置为一个或多个权限表（空格分隔），这些表是遵循 [makedev 语法](https://buildroot.org/downloads/manual/manual.html#makedev-syntax)的普通文本文件。

如果你使用静态设备表（即未使用 `devtmpfs`、`mdev` 或 `(e)udev`），则可以用相同语法在*设备表*中添加设备节点。启用该功能需将 `BR2_ROOTFS_STATIC_DEVICE_TABLE` 配置项设置为一个或多个设备表（空格分隔）。

如[9.1节“推荐的目录结构”](https://buildroot.org/downloads/manual/manual.html#customize-dir-structure)所述，推荐将这些文件放在 `board/<company>/<boardname>/`。

需要注意的是，如果特定权限或设备节点与某个应用相关，建议在该软件包的 `.mk` 文件中设置 `FOO_PERMISSIONS` 和 `FOO_DEVICES` 变量（见[18.6.2节“generic-package 参考”](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)）。

## 9.6 添加自定义用户账户

有时需要在目标系统中添加特定用户。为此，Buildroot 提供了*用户表*（users tables）功能。启用该功能需将 `BR2_ROOTFS_USERS_TABLES` 配置项设置为一个或多个用户表（空格分隔），这些表是遵循 [makeusers 语法](https://buildroot.org/downloads/manual/manual.html#makeuser-syntax)的普通文本文件。

如[9.1节“推荐的目录结构”](https://buildroot.org/downloads/manual/manual.html#customize-dir-structure)所述，推荐将这些文件放在 `board/<company>/<boardname>/`。

需要注意的是，如果自定义用户与某个应用相关，建议在该软件包的 `.mk` 文件中设置 `FOO_USERS` 变量（见[18.6.2节“generic-package 参考”](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)）。

## 9.7 镜像生成后的定制

post-build 脚本（见[9.5节“定制生成的目标文件系统”](https://buildroot.org/downloads/manual/manual.html#rootfs-custom)）是在构建文件系统镜像、内核和引导加载程序*之前*运行的，***post-image 脚本***可用于在所有镜像生成*之后*执行特定操作。

post-image 脚本可用于自动将 root 文件系统 tar 包解压到 NFS 服务器导出的目录，或创建包含 root 文件系统和内核镜像的特殊固件镜像，或执行项目所需的其他自定义操作。

启用该功能需在“System configuration”菜单中将 `BR2_ROOTFS_POST_IMAGE_SCRIPT` 配置项设置为 post-image 脚本列表（空格分隔）。若指定相对路径，则相对于 Buildroot 根目录。

与 post-build 脚本类似，post-image 脚本运行时当前工作目录为 Buildroot 主目录，`images` 输出目录路径作为第一个参数传递。如果 `BR2_ROOTFS_POST_SCRIPT_ARGS` 不为空，这些参数也会传递给脚本。所有脚本接收相同参数，无法为每个脚本单独设置参数。

注意，`BR2_ROOTFS_POST_SCRIPT_ARGS` 的参数也会传递给 post-build 和 post-fakeroot 脚本。如果只想为 post-image 脚本使用特定参数，可用 `BR2_ROOTFS_POST_IMAGE_SCRIPT_ARGS`。

同样，post-image 脚本可访问环境变量 `BR2_CONFIG`、`HOST_DIR`、`STAGING_DIR`、`TARGET_DIR`、`BUILD_DIR`、`BINARIES_DIR`、`CONFIG_DIR`、`BASE_DIR` 和 `PARALLEL_JOBS`。

post-image 脚本会以执行 Buildroot 的用户身份运行，通常*不应*是 root 用户。因此，若脚本中有需要 root 权限的操作，需要特殊处理（如使用 fakeroot 或 sudo），具体由脚本开发者决定。

## 9.8 添加项目专属补丁和哈希

### 9.8.1 提供额外补丁

有时需要为软件包应用*额外*补丁（在 Buildroot 自带补丁基础上）。例如，为项目支持自定义功能，或开发新架构时。

`BR2_GLOBAL_PATCH_DIR` 配置项可用于指定一个或多个包含软件包补丁的目录（空格分隔）。

对于特定版本 `<packageversion>` 的特定软件包 `<packagename>`，补丁应用顺序如下：

1. 对于 `BR2_GLOBAL_PATCH_DIR` 中的每个目录 `<global-patch-dir>`，确定 `<package-patch-dir>`：
   - 若 `<global-patch-dir>/<packagename>/<packageversion>/` 存在，则使用该目录；
   - 否则，若 `<global-patch-dir>/<packagename>` 存在，则使用该目录。
2. 从 `<package-patch-dir>` 应用补丁：
   - 若目录下有 `series` 文件，则按 `series` 文件顺序应用补丁；
   - 否则，按字母顺序应用所有 `*.patch` 文件。为确保顺序，建议补丁文件命名为 `<number>-<description>.patch`，其中 `<number>` 表示应用顺序。

关于软件包补丁应用顺序，详见[19.2节“补丁应用顺序”](https://buildroot.org/downloads/manual/manual.html#patch-apply-order)。

`BR2_GLOBAL_PATCH_DIR` 是为软件包指定自定义补丁目录的首选方法。它可用于为 buildroot 中的任意软件包指定补丁目录，也应优先于 U-Boot、Barebox 等软件包的自定义补丁目录选项。这样用户可在顶层目录统一管理所有补丁。

唯一例外是 `BR2_LINUX_KERNEL_PATCH`，该选项用于指定可通过 URL 获取的内核补丁。***注意：*** `BR2_LINUX_KERNEL_PATCH` 指定的补丁会在 `BR2_GLOBAL_PATCH_DIR` 补丁之后应用（由 Linux 软件包的 post-patch hook 完成）。



### 9.8.2 提供额外哈希

Buildroot 自带一份[哈希列表](https://buildroot.org/downloads/manual/manual.html#adding-packages-hash)，用于校验下载归档文件或从 VCS 检出后本地生成的归档文件的完整性。但对于可自定义版本的软件包（如自定义版本号、远程 tarball URL 或 VCS 仓库及变更集），Buildroot 无法自带哈希。

如果你关心此类下载的完整性，可以为 Buildroot 提供一份额外哈希列表，用于校验任意下载文件。这些额外哈希的查找方式与额外补丁类似：对于 `BR2_GLOBAL_PATCH_DIR` 中的每个目录，Buildroot 会依次查找以下文件，找到第一个存在的文件用于校验：

- `<global-patch-dir>/<packagename>/<packageversion>/<packagename>.hash`
- `<global-patch-dir>/<packagename>/<packagename>.hash`

可以使用 `utils/add-custom-hashes` 脚本生成这些文件。

## 9.9 添加项目专属软件包

一般来说，任何新软件包都应直接添加到 `package` 目录并提交到 Buildroot 上游项目。如何向 Buildroot 添加软件包详见[第18章“向 Buildroot 添加新软件包”](https://buildroot.org/downloads/manual/manual.html#adding-packages)，此处不再赘述。但你的项目可能需要无法上游的专有软件包，本节介绍如何将此类项目专属软件包保存在项目专属目录。

如[9.1节“推荐的目录结构”](https://buildroot.org/downloads/manual/manual.html#customize-dir-structure)所示，推荐将项目专属软件包放在 `package/<company>/`。如果使用 br2-external 树（见[9.2节“保持定制内容在 Buildroot 之外”](https://buildroot.org/downloads/manual/manual.html#outside-br-custom)），推荐放在 br2-external 树下的 `package/` 子目录。

但 Buildroot 默认不会识别这些位置的软件包，需要额外操作。正如[第18章“向 Buildroot 添加新软件包”](https://buildroot.org/downloads/manual/manual.html#adding-packages)所述，Buildroot 的软件包主要由两个文件组成：`.mk` 文件（描述如何构建软件包）和 `Config.in` 文件（描述该软件包的配置选项）。

Buildroot 会自动包含 `package` 目录一级子目录下的 `.mk` 文件（模式为 `package/*/*.mk`）。如果希望 Buildroot 包含更深层目录（如 `package/<company>/package1/`）下的 `.mk` 文件，只需在一级子目录下添加一个 `.mk` 文件，将这些 `.mk` 文件包含进来。例如，在 `package/<company>/<company>.mk` 文件中写入如下内容（假设只多一级目录）：

```
include $(sort $(wildcard package/<company>/*/*.mk))
```

对于 `Config.in` 文件，在 `package/<company>/Config.in` 中依次包含所有软件包的 `Config.in` 文件。由于 kconfig 的 source 命令不支持通配符，需手动列出所有文件。例如：

```
source "package/<company>/package1/Config.in"
source "package/<company>/package2/Config.in"
```

建议将该新建的 `package/<company>/Config.in` 文件以公司专属菜单的方式包含到 `package/Config.in`，以便后续 Buildroot 升级时便于合并。

如果使用 br2-external 树，相关文件的写法见[9.2节“保持定制内容在 Buildroot 之外”](https://buildroot.org/downloads/manual/manual.html#outside-br-custom)。

## 9.10 项目专属定制内容存储快速指南

本章前文介绍了多种项目专属定制方法，本节将以步骤形式总结如何存储项目专属定制内容。与项目无关的步骤可跳过。

1. `make menuconfig` 配置工具链、软件包和内核。
2. `make linux-menuconfig` 更新内核配置，其他配置（如 busybox、uclibc 等）同理。
3. `mkdir -p board/<manufacturer>/<boardname>`
4. 将以下选项设置为 `board/<manufacturer>/<boardname>/<package>.config`（如有需要）：
   - `BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE`
   - `BR2_PACKAGE_BUSYBOX_CONFIG`
   - `BR2_UCLIBC_CONFIG`
   - `BR2_TARGET_AT91BOOTSTRAP3_CUSTOM_CONFIG_FILE`
   - `BR2_TARGET_BAREBOX_CUSTOM_CONFIG_FILE`
   - `BR2_TARGET_UBOOT_CUSTOM_CONFIG_FILE`
5. 写入配置文件：
   - `make linux-update-defconfig`
   - `make busybox-update-config`
   - `make uclibc-update-config`
   - `cp <output>/build/at91bootstrap3-*/.config board/<manufacturer>/<boardname>/at91bootstrap3.config`
   - `make barebox-update-defconfig`
   - `make uboot-update-defconfig`
6. 创建 `board/<manufacturer>/<boardname>/rootfs-overlay/`，将 rootfs 需要的额外文件放入，如 `board/<manufacturer>/<boardname>/rootfs-overlay/etc/inittab`。将 `BR2_ROOTFS_OVERLAY` 设为 `board/<manufacturer>/<boardname>/rootfs-overlay`。
7. 创建 post-build 脚本 `board/<manufacturer>/<boardname>/post_build.sh`，将 `BR2_ROOTFS_POST_BUILD_SCRIPT` 设为该脚本路径。
8. 如需设置 setuid 权限或创建设备节点，创建 `board/<manufacturer>/<boardname>/device_table.txt`，并将其路径加入 `BR2_ROOTFS_DEVICE_TABLE`。
9. 如需创建用户账户，创建 `board/<manufacturer>/<boardname>/users_table.txt`，并将其路径加入 `BR2_ROOTFS_USERS_TABLES`。
10. 若需为某些软件包添加自定义补丁，将 `BR2_GLOBAL_PATCH_DIR` 设为 `board/<manufacturer>/<boardname>/patches/`，并为每个软件包在以包名命名的子目录下添加补丁。每个补丁建议命名为 `<packagename>-<num>-<description>.patch`。
11. 针对 Linux 内核，也可用 `BR2_LINUX_KERNEL_PATCH` 选项（可从 URL 下载补丁），如无特殊需求，优先用 `BR2_GLOBAL_PATCH_DIR`。U-Boot、Barebox、at91bootstrap 和 at91bootstrap3 也有类似选项，但不如 `BR2_GLOBAL_PATCH_DIR` 统一，未来可能移除。
12. 如需添加项目专属软件包，创建 `package/<manufacturer>/`，将软件包放入该目录。创建 `<manufacturer>.mk` 文件包含所有 `.mk` 文件，创建 `Config.in` 文件依次 source 所有 `Config.in`，并将其包含到 Buildroot 的 `package/Config.in`。
13. `make savedefconfig` 保存 buildroot 配置。
14. `cp defconfig configs/<boardname>_defconfig`





# 第 10 章 集成

本章讨论了在系统层面上如何集成各种内容。Buildroot 具有高度可配置性，这里讨论的几乎所有内容都可以通过 [rootfs 覆盖或自定义 skeleton](https://buildroot.org/downloads/manual/manual.html#rootfs-custom) 配置进行更改或覆盖。

## 10.1 可配置的软件包（Configurable packages）

一些基础软件包，如 Busybox 和 uClibc，可以根据需要启用或禁用某些功能。在编写使用这些软件包的 Buildroot 代码时，贡献者可以假设 Buildroot 提供的配置中已启用相关选项。例如，`package/busybox/busybox.config` 设置了 `CONFIG_FEATURE_START_STOP_DAEMON_LONG_OPTIONS=y`，因此用于 Busybox init 的初始化脚本可以使用带有长选项的 `start-stop-daemon`。

如果用户使用自定义配置禁用了这些默认选项，则需要自行确保相关脚本/软件包仍然可用，如果不可用，则需要相应地进行调整。以 Busybox 为例，禁用长选项后，需要替换使用长选项的初始化脚本（可通过 overlay 覆盖）。

## 10.2 Systemd

本节描述了 Buildroot 集成 systemd 时所做的决策，以及如何实现各种用例。

### 10.2.1 DBus 守护进程（DBus daemon）

Systemd 需要一个 DBus 守护进程。有两种选择：传统 dbus（`BR2_PACKAGE_DBUS`）和 bus1 dbus-broker（`BR2_PACKAGE_DBUS_BROKER`）。必须至少选择其中之一。如果两者都包含在配置中，则 dbus-broker 将作为系统总线（system bus）使用，但传统的 dbus-daemon 仍会被安装，并可作为会话总线（session bus）使用。同时，其工具（如 `dbus-send`）也可用（systemd 本身有 `busctl` 作为替代）。此外，传统 dbus 软件包是唯一提供 `libdbus` 的软件包，许多软件包将其用作 dbus 集成库。

无论是 dbus 还是 dbus-broker，守护进程都以 `dbus` 用户身份运行。两者的 DBus 配置文件也完全相同。

为确保只有一个守护进程作为系统总线启动，当选择 dbus-broker 时，会移除 dbus 软件包的 systemd 激活文件（`dbus.socket` 和 `multi-user.target.wants` 目录下的 `dbus.service` 符号链接）。

## 10.3 在 Buildroot 中使用 SELinux

[SELinux](https://selinuxproject.org/) 是一个 Linux 内核安全模块，用于强制访问控制策略。除了传统的文件权限和访问控制列表外，`SELinux` 还允许为用户或进程访问特定资源（文件、套接字等）的功能编写规则。

*SELinux* 有三种运行模式：

- *禁用*（Disabled）：不应用策略
- *宽容*（Permissive）：应用策略，未授权操作仅被记录。此模式常用于 SELinux 问题的排查。
- *强制*（Enforcing）：应用策略，未授权操作被拒绝

在 Buildroot 中，运行模式由 `BR2_PACKAGE_REFPOLICY_POLICY_STATE_*` 配置选项控制。Linux 内核也有多个配置选项影响 `SELinux` 的启用方式（参见 Linux 内核源码中的 `security/selinux/Kconfig`）。

默认情况下，Buildroot 提供的 `SELinux` 策略来自上游 [refpolicy](https://github.com/SELinuxProject/refpolicy) 项目，通过启用 `BR2_PACKAGE_REFPOLICY` 实现。

### 10.3.1 启用 SELinux 支持

要在 Buildroot 生成的系统中正确支持 `SELinux`，必须启用以下配置选项：

- `BR2_PACKAGE_LIBSELINUX`
- `BR2_PACKAGE_REFPOLICY`

此外，文件系统镜像格式必须支持扩展属性（extended attributes）。

### 10.3.2 SELinux 策略调整（policy tweaking）

`SELinux refpolicy` 包含可在构建时启用或禁用的模块。每个模块都提供若干 `SELinux` 规则。在 Buildroot 中，非基础模块默认禁用，提供了多种方式启用这些模块：

- 软件包可通过 `<packagename>_SELINUX_MODULES` 变量，在 `refpolicy` 中启用一组 `SELinux` 模块。
- 软件包可通过在 `package/<packagename>/selinux/` 目录下放置 .fc、.if 和 .te 文件，提供额外的 `SELinux` 模块。
- 可通过 `BR2_REFPOLICY_EXTRA_MODULES_DIRS` 配置选项，添加额外的 `SELinux` 模块目录。
- 可通过 `BR2_REFPOLICY_EXTRA_MODULES_DEPENDENCIES` 配置选项，启用 `refpolicy` 中的其他模块。

Buildroot 还允许完全覆盖 `refpolicy`，即为特定系统提供完全自定义的策略。采用此方式时，上述所有机制均被禁用：不会向策略中添加额外的 `SElinux` 模块，且自定义策略中的所有可用模块都会被启用并编译进最终的二进制策略。自定义策略必须是官方 [refpolicy](https://github.com/SELinuxProject/refpolicy) 的分支。

要完全覆盖 `refpolicy`，需设置以下配置变量：

- `BR2_PACKAGE_REFPOLICY_CUSTOM_GIT`
- `BR2_PACKAGE_REFPOLICY_CUSTOM_REPO_URL`
- `BR2_PACKAGE_REFPOLICY_CUSTOM_REPO_VERSION`



# 第 11 章 常见问题与故障排查

## 11.1 启动卡在 *Starting network...* 后

如果启动过程在如下信息后似乎卡住（具体信息可能因所选软件包不同而略有差异）：

```
Freeing init memory: 3972K
Initializing random number generator... done.
Starting network...
Starting dropbear sshd: generating rsa key... generating dsa key... OK
```

这意味着系统已经运行，但没有在串口控制台上启动 shell。要让系统在串口控制台上启动 shell，需要进入 Buildroot 配置，在“系统配置（System configuration）”中，修改“启动后运行 getty（登录提示）”选项，并在“getty 选项”子菜单中设置合适的端口和波特率。这将自动调整生成系统的 `/etc/inittab` 文件，使 shell 能在正确的串口上启动。

## 11.2 为什么目标系统上没有编译器？

自 Buildroot-2012.11 版本起，已决定不再支持*目标系统上的本地编译器（native compiler）*，原因如下：

- 该功能既未维护也未测试，经常出错；
- 该功能仅适用于 Buildroot 工具链；
- Buildroot 主要面向*小型*或*超小型*目标硬件，资源有限（CPU、内存、存储），在目标上编译意义不大；
- Buildroot 旨在简化交叉编译，使目标上的本地编译变得不必要。

如果你确实需要在目标系统上有编译器，那么 Buildroot 并不适合你的需求。此时应选择如下“真正的发行版（distribution）”：

- [openembedded](http://www.openembedded.org/)
- [yocto](https://www.yoctoproject.org/)
- [Debian](https://www.debian.org/ports/)
- [Fedora](https://fedoraproject.org/wiki/Architectures)
- [openSUSE ARM](http://en.opensuse.org/Portal:ARM)
- [Arch Linux ARM](http://archlinuxarm.org/)
- ...

## 11.3 为什么目标系统上没有开发文件？

由于目标系统上没有编译器（见[11.2节“为什么目标系统上没有编译器？”](https://buildroot.org/downloads/manual/manual.html#faq-no-compiler-on-target)），因此没有必要浪费空间存放头文件或静态库。

因此，从 Buildroot-2012.11 版本起，这些文件始终会从目标系统中移除。

## 11.4 为什么目标系统上没有文档？

由于 Buildroot 主要面向*小型*或*超小型*目标硬件，资源有限（CPU、内存、存储），因此没有必要浪费空间存放文档数据。

如果你确实需要在目标系统上有文档数据，那么 Buildroot 并不适合你的需求，应选择“真正的发行版”（见[11.2节“为什么目标系统上没有编译器？”](https://buildroot.org/downloads/manual/manual.html#faq-no-compiler-on-target)）。

## 11.5 为什么有些软件包在 Buildroot 配置菜单中不可见？

如果某个软件包在 Buildroot 源码树中存在，但在配置菜单中不可见，通常是因为该软件包的某些依赖项未满足。

要了解软件包的依赖关系，可在配置菜单中搜索该软件包的符号（见[8.1节“make 技巧”](https://buildroot.org/downloads/manual/manual.html#make-tips)）。

然后，可能需要递归地启用多个选项（即未满足的依赖项），才能最终选择该软件包。

如果由于某些工具链选项未满足导致软件包不可见，则应进行完整重建（见[8.1节“make 技巧”](https://buildroot.org/downloads/manual/manual.html#make-tips)获取更多说明）。

## 11.6 为什么不能将 target 目录作为 chroot 目录使用？

有很多理由***不***要将 target 目录作为 chroot 目录，其中包括：

- 目标目录中的文件所有权、模式和权限未正确设置；
- 目标目录中未创建设备节点。

因此，通过 chroot 并将 target 目录作为新根目录运行的命令很可能会失败。

如果想在 chroot 或 NFS 根下运行目标文件系统，应使用 `images/` 目录下生成的 tarball 镜像，并以 root 身份解压。





## 11.7 为什么 Buildroot 不生成二进制软件包（.deb、.ipkg 等）？

在 Buildroot 邮件列表中经常讨论的一个功能是“软件包管理（package management）”的主题。简而言之，就是希望能够追踪 Buildroot 各软件包安装了哪些文件，目标包括：

- 当某个软件包在 menuconfig 中被取消选择时，能够删除该软件包安装的文件；
- 能够生成二进制软件包（如 ipk 或其他格式），可在目标系统上直接安装，而无需重新生成新的根文件系统镜像。

通常，大多数人认为这很容易：只需追踪每个软件包安装了哪些文件，在取消选择时删除即可。但实际上远比这复杂：

- 不仅仅是 `target/` 目录，还包括 `host/<tuple>/sysroot` 和 `host/` 目录本身。所有软件包在这些目录中安装的文件都必须被追踪；
- 当某个软件包在配置中被取消选择时，仅删除它安装的文件是不够的。还必须删除所有反向依赖（即依赖它的软件包），并重建这些软件包。例如，A 软件包可选依赖 OpenSSL 库。两者都被选中并构建，A 软件包会用 OpenSSL 支持构建。后来 OpenSSL 被取消选择，但 A 软件包仍然保留（因为 OpenSSL 是可选依赖）。如果只删除 OpenSSL 文件，A 软件包安装的文件就会出错：它们依赖的库已不在目标系统。虽然技术上可行，但会极大增加 Buildroot 的复杂性，这与 Buildroot 追求的简洁性背道而驰；
- 除了上述问题，还有一种情况是可选依赖甚至 Buildroot 并不知道。例如，A 软件包 1.0 版本从未用过 OpenSSL，但 2.0 版本如果检测到 OpenSSL 就会自动使用。如果 Buildroot 的 .mk 文件没有及时更新，A 软件包就不会被列为 OpenSSL 的反向依赖，在 OpenSSL 被移除时也不会被删除和重建。理论上 .mk 文件应及时修正，但在此期间就会出现不可复现的行为；
- 还有人希望 menuconfig 的更改能直接应用到输出目录，而无需全部重建。但要可靠地实现这一点非常困难：如果更改了软件包的子选项（需要检测并重建该包及其所有反向依赖），如果更改了工具链选项等。目前 Buildroot 的做法清晰简单，因此行为非常可靠，易于支持用户。如果配置更改后只需下一次 make 就能生效，那么必须保证所有场景都能正确工作，不能有奇怪的边角问题。否则会收到类似“我启用了 A、B、C，然后 make，后来禁用 C 启用 D 又 make，再启用 C 启用 E 又 make，结果构建失败”这样的 bug 报告。更糟的是“我做了一些配置，构建了，然后又改了点，构建了，又改了点，构建了……现在失败了，但我不记得都改了什么顺序”。这种情况将无法支持。

因此，结论是：为删除被取消选择的软件包或生成二进制软件包而追踪已安装文件，是非常难以可靠实现的，会极大增加复杂性。

在这个问题上，Buildroot 开发者的立场声明如下：

- Buildroot 致力于让生成根文件系统（root filesystem）变得简单（这也是 Buildroot 名字的由来）。我们希望 Buildroot 擅长的就是构建根文件系统；
- Buildroot 并不打算成为一个发行版（distribution）或发行版生成器。大多数 Buildroot 开发者认为这不是我们应追求的目标。我们认为有其他工具更适合生成发行版，比如 [Open Embedded](http://openembedded.org/) 或 [openWRT](https://openwrt.org/)；
- 我们更愿意推动 Buildroot 朝着更容易生成完整根文件系统的方向发展。这也是 Buildroot 能脱颖而出的原因之一；
- 我们认为对于大多数嵌入式 Linux 系统，二进制软件包并非必需，甚至有害。使用二进制包意味着系统可以被部分升级，这会带来大量可能的软件包版本组合，在升级前都需要测试。而通过整体升级根文件系统镜像，部署到嵌入式设备的镜像就是经过测试和验证的。

## 11.8 如何加快构建速度？

由于 Buildroot 经常需要完整重建整个系统，过程可能很长，下面提供一些加快构建速度的建议：

- 使用预构建的外部工具链（external toolchain），而不是默认的 Buildroot 内部工具链。比如 ARM 平台用 Linaro 工具链，ARM、x86、x86-64、MIPS 等可用 Sourcery CodeBench 工具链，这样每次完整重建时可节省 15-20 分钟的工具链构建时间。临时用外部工具链不影响后续切换回内部工具链（后者可高度定制），等系统其它部分调通后再切换；
- 使用 `ccache` 编译器缓存（见[8.13.3节“在 Buildroot 中使用 ccache”](https://buildroot.org/downloads/manual/manual.html#ccache)）；
- 学会只重建关心的少数软件包（见[8.3节“理解如何重建软件包”](https://buildroot.org/downloads/manual/manual.html#rebuild-pkg)），但有时还是必须完整重建（见[8.2节“理解何时需要完整重建”](https://buildroot.org/downloads/manual/manual.html#full-rebuild)）；
- 确保运行 Buildroot 的 Linux 系统不是虚拟机。大多数虚拟机技术会显著影响 I/O 性能，而 I/O 对源码构建非常重要；
- 确保只用本地文件：不要在 NFS 上构建，这会极大拖慢速度。Buildroot 下载目录也应本地化；
- 升级硬件。SSD 和大内存对加速构建非常关键；
- 尝试顶层并行构建（top-level parallel build），见[8.12节“顶层并行构建”](https://buildroot.org/downloads/manual/manual.html#top-level-parallel-build)。



## 11.9 Buildroot 如何支持 Y2038 问题？

有多种情况需要考虑：

- 在 64 位架构上，没有问题，因为 `time_t` 一直是 64 位；
- 在 32 位架构上，情况取决于 C 库：
  - 使用 *uclibc-ng* 时，自 1.0.46 版本起支持 32 位架构上的 64 位 `time_t`，因此在 32 位平台上使用 *uclibc-ng* 时，只要 UCLIBC_USE_TIME64 设为 y（1.0.49 及以后默认如此），系统就支持 Y2038；
  - 使用 *musl* 时，32 位架构上一直使用 64 位 `time_t`，因此在 32 位平台上使用 *musl* 的系统支持 Y2038；
  - 使用 *glibc* 时，32 位架构上的 64 位 `time_t` 由 Buildroot 选项 `BR2_TIME_BITS_64` 启用。启用后，32 位平台上使用 *glibc* 的系统支持 Y2038。

注意，上述仅说明 C 库的能力。即使在 Y2038 兼容的环境下，单个用户空间库或应用如果未正确使用时间相关 API 和类型，仍可能表现异常。

# 第 12 章 已知问题

- 如果 `BR2_TARGET_LDFLAGS` 选项中包含 `$` 符号，则无法通过该选项传递额外的链接器参数。例如：`BR2_TARGET_LDFLAGS="-Wl,-rpath='$ORIGIN/../lib'"` 会导致问题；
- `libffi` 软件包不支持 SuperH 2 和 ARMv7-M 架构；
- `prboom` 软件包在使用 Sourcery CodeBench 2012.09 版 SuperH 4 编译器时会触发编译失败。

# 第 13 章 法律声明与许可

## 13.1 遵守开源许可证

Buildroot 生成的所有最终产品（工具链、根文件系统、内核、引导加载程序）都包含开源软件，采用各种许可证发布。

使用开源软件让你可以自由构建丰富的嵌入式系统，选择多种软件包，但也带来一些你必须了解和遵守的义务。有些许可证要求你在产品文档中公布许可证文本，另一些要求你向产品接收者分发软件源代码。

每种许可证的具体要求都在各自软件包中有说明，你（或你的法务部门）有责任遵守这些要求。为方便你，Buildroot 可以为你收集一些你可能需要的材料。配置好 Buildroot（用 `make menuconfig`、`make xconfig` 或 `make gconfig`）后，运行：

```
make legal-info
```

Buildroot 会在输出目录下的 `legal-info/` 子目录中收集法律相关材料，包括：

- `README` 文件，汇总所收集材料，并提示 Buildroot 未能收集的内容；
- `buildroot.config`：Buildroot 配置文件，通常由 `make menuconfig` 生成，用于复现构建；
- 所有软件包的源代码，分别保存在 `sources/` 和 `host-sources/` 子目录（分别对应目标和主机软件包）。设置了 `<PKG>_REDISTRIBUTE = NO` 的包不会保存源码。应用的补丁也会保存，并有 `series` 文件记录补丁应用顺序。补丁与被修改文件采用相同许可证。注意：Buildroot 会对 autotools 类软件包的 Libtool 脚本应用额外补丁，这些补丁位于 Buildroot 源码的 `support/libtool`，由于技术原因不会和包源码一起保存，需手动收集；
- 清单文件（目标和主机各一份），列出已配置软件包、版本、许可证及相关信息。部分信息 Buildroot 未定义时会标记为“unknown”；
- 所有软件包的许可证文本，分别保存在 `licenses/` 和 `host-licenses/` 子目录（分别对应目标和主机软件包）。如果 Buildroot 未定义许可证文件，则不会生成，并在 `README` 中有警告。

请注意，Buildroot 的 `legal-info` 功能旨在收集所有与软件包许可证合规相关的材料。Buildroot 并不试图生成你必须公开的全部材料。实际上，生成的材料往往比严格合规所需的更多。例如，BSD 类许可证的软件包源码也会被收集，但你并不需要分发这些源码。

此外，由于技术限制，Buildroot 不会生成某些你需要或可能需要的材料，比如部分外部工具链的源码和 Buildroot 自身源码。运行 `make legal-info` 时，Buildroot 会在 `README` 文件中提示未能保存的相关材料。

最后，`make legal-info` 的输出基于各软件包 recipe 中的声明。Buildroot 开发者会尽力保证这些声明的准确性，但不排除有不准确或不完整之处。你（或你的法务部门）*必须*在使用 `make legal-info` 输出作为合规交付材料前自行核查。详见 Buildroot 根目录 `COPYING` 文件第 11、12 条 *无担保* 条款。





## 13.2 遵守 Buildroot 许可证

Buildroot 本身是开源软件，采用 [GNU 通用公共许可证第2版](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html) 或（可选）任何更高版本发布，除了下文所述的包补丁外。然而，作为构建系统，Buildroot 通常不会出现在最终产品中：如果你为设备开发根文件系统、内核、引导加载程序或工具链，Buildroot 代码只存在于开发主机，而不会存储在设备中。

尽管如此，Buildroot 开发者普遍认为，当你发布包含 GPL 许可软件的产品时，应一并发布 Buildroot 源码。这是因为 [GNU GPL](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html) 规定“*完整源码*”包括“*它包含的所有模块的源码、所有相关接口定义文件，以及用于控制可执行文件编译和安装的脚本*”。Buildroot 属于*用于控制可执行文件编译和安装的脚本*，因此被认为是必须一同分发的材料。

请注意，这只是 Buildroot 开发者的观点，如有疑问应咨询你的法务部门或律师。

### 13.2.1 软件包补丁（Patches to packages）

Buildroot 还包含补丁文件，这些补丁会应用到各个软件包的源码上。这些补丁不受 Buildroot 许可证约束，而是受被补丁所应用软件的许可证约束。如果该软件有多种许可证，Buildroot 补丁仅在公开可用的许可证下提供。

技术细节见[第19章“为软件包打补丁”](https://buildroot.org/downloads/manual/manual.html#patch-policy)。

# 第 14 章 超越 Buildroot

## 14.1 启动生成的镜像

### 14.1.1 NFS 启动（NFS boot）

要实现 NFS 启动，在“文件系统镜像（Filesystem images）”菜单中启用 *tar 根文件系统* 选项。

完整构建后，运行以下命令设置 NFS 根目录：

```
sudo tar -xavf /path/to/output_dir/rootfs.tar -C /path/to/nfs_root_dir
```

记得将该路径添加到 `/etc/exports`。

然后即可在目标机上通过 NFS 启动。

### 14.1.2 Live CD

要构建 Live CD 镜像，在“文件系统镜像”菜单中启用 *iso 镜像* 选项。注意，该选项仅在 x86 和 x86-64 架构下可用，且需用 Buildroot 构建内核。

Live CD 镜像可用 IsoLinux、Grub 或 Grub 2 作为引导加载程序，但只有 Isolinux 支持将该镜像同时作为 Live CD 和 Live USB（通过 *构建混合镜像* 选项）。

可用 QEMU 测试 Live CD 镜像：

```
qemu-system-i386 -cdrom output/images/rootfs.iso9660
```

如果是混合 ISO，也可作为硬盘镜像使用：

```
qemu-system-i386 -hda output/images/rootfs.iso9660
```

可用 `dd` 轻松写入 U 盘：

```
dd if=output/images/rootfs.iso9660 of=/dev/sdb
```

## 14.2 Chroot

如果你想在生成的镜像中 chroot，需要注意：

- 应从 *tar 根文件系统* 镜像设置新根目录；
- 目标架构要么与主机兼容，要么需用 `qemu-*` 二进制并正确设置 `binfmt` 属性，才能在主机上运行为目标构建的二进制文件；
- Buildroot 当前不提供已正确构建和设置的 `host-qemu` 和 `binfmt` 用于此类用途。

# 第三部分：开发者指南

# 第 15 章 Buildroot 的工作原理

如前所述，Buildroot 本质上是一组 Makefile，用于以正确的选项下载、配置和编译软件。它还包含了针对各种软件包的补丁，主要是交叉编译工具链（`gcc`、`binutils` 和 `uClibc`）相关的软件包。

基本上，每个软件包都有一个对应的 Makefile，文件扩展名为 `.mk`。Makefile 被划分为多个不同的部分。

- `toolchain/` 目录包含与交叉编译工具链相关的所有软件的 Makefile 及相关文件：`binutils`、`gcc`、`gdb`、`kernel-headers` 和 `uClibc`。
- `arch/` 目录包含 Buildroot 支持的所有处理器架构的定义。
- `package/` 目录包含 Buildroot 能够编译并添加到目标根文件系统中的所有用户空间工具和库的 Makefile 及相关文件。每个软件包有一个子目录。
- `linux/` 目录包含 Linux 内核的 Makefile 及相关文件。
- `boot/` 目录包含 Buildroot 支持的引导加载程序的 Makefile 及相关文件。
- `system/` 目录包含系统集成支持，例如目标文件系统 skeleton 和初始化系统的选择。
- `fs/` 目录包含与生成目标根文件系统镜像相关的软件的 Makefile 及相关文件。

每个目录至少包含两个文件：

- `something.mk` 是用于下载、配置、编译和安装 `something` 软件包的 Makefile。
- `Config.in` 是配置工具描述文件的一部分。它描述了与该软件包相关的选项。

主 Makefile 执行以下步骤（配置完成后）：

- 在输出目录（默认为 `output/`，也可通过 `O=` 指定其他值）中创建所有输出目录：`staging`、`target`、`build` 等。
- 生成工具链目标。当使用内部工具链时，这意味着生成交叉编译工具链。当使用外部工具链时，这意味着检查外部工具链的特性并将其导入 Buildroot 环境。
- 生成 `TARGETS` 变量中列出的所有目标。该变量由所有单独组件的 Makefile 填充。生成这些目标会触发用户空间软件包（库、程序）、内核、引导加载程序的编译，以及根文件系统镜像的生成，具体取决于配置。

# 第 16 章 代码风格

总体来说，这些代码风格规则旨在帮助你为 Buildroot 添加新文件或重构现有文件。

如果你只是对现有文件做了轻微修改，重要的是保持整个文件的风格一致，因此你可以：

- 遵循该文件中可能已过时的代码风格，
- 或者彻底重写，使其符合这些规则。

## 16.1 `Config.in` 文件

`Config.in` 文件包含 Buildroot 中几乎所有可配置项的条目。

一个条目的模式如下：

```
config BR2_PACKAGE_LIBFOO
        bool "libfoo"
        depends on BR2_PACKAGE_LIBBAZ
        select BR2_PACKAGE_LIBBAR
        help
          This is a comment that explains what libfoo is. The help text
          should be wrapped.

          http://foosoftware.org/libfoo/
```

- `bool`、`depends on`、`select` 和 `help` 行使用一个制表符缩进。
- 帮助文本本身应使用一个制表符和两个空格缩进。
- 帮助文本应换行以适应 72 列，其中制表符算作 8 个字符，因此文本本身为 62 个字符。

`Config.in` 文件是 Buildroot 所用配置工具的输入文件，该工具为常规 *Kconfig*。关于 *Kconfig* 语言的更多细节，请参阅 http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt。

## 16.2 `.mk` 文件

- 头部：文件以头部注释开始。内容为模块名，建议小写，位于 80 个 # 号组成的分隔符之间。头部后必须有一个空行：

  ```
  ################################################################################
  #
  # libfoo
  #
  ################################################################################
  ```

- 赋值：使用 `=`，前后各有一个空格：

  ```
  LIBFOO_VERSION = 1.0
  LIBFOO_CONF_OPTS += --without-python-support
  ```

  不要对齐 `=` 号。

- 缩进：只使用制表符：

  ```
  define LIBFOO_REMOVE_DOC
          $(RM) -r $(TARGET_DIR)/usr/share/libfoo/doc \
                  $(TARGET_DIR)/usr/share/man/man3/libfoo*
  endef
  ```

  注意，`define` 块中的命令应始终以制表符开头，这样 *make* 才能识别为命令。

- 可选依赖：

  - 推荐多行语法。

    推荐：

    ```
    ifeq ($(BR2_PACKAGE_PYTHON3),y)
    LIBFOO_CONF_OPTS += --with-python-support
    LIBFOO_DEPENDENCIES += python3
    else
    LIBFOO_CONF_OPTS += --without-python-support
    endif
    ```

    不推荐：

    ```
    LIBFOO_CONF_OPTS += --with$(if $(BR2_PACKAGE_PYTHON3),,out)-python-support
    LIBFOO_DEPENDENCIES += $(if $(BR2_PACKAGE_PYTHON3),python3,)
    ```

  - 保持配置选项和依赖项靠近。

- 可选钩子：将钩子定义和赋值放在同一个 if 块中。

  推荐：

  ```
  ifneq ($(BR2_LIBFOO_INSTALL_DATA),y)
  define LIBFOO_REMOVE_DATA
          $(RM) -r $(TARGET_DIR)/usr/share/libfoo/data
  endef
  LIBFOO_POST_INSTALL_TARGET_HOOKS += LIBFOO_REMOVE_DATA
  endif
  ```

  不推荐：

  ```
  define LIBFOO_REMOVE_DATA
          $(RM) -r $(TARGET_DIR)/usr/share/libfoo/data
  endef
  
  ifneq ($(BR2_LIBFOO_INSTALL_DATA),y)
  LIBFOO_POST_INSTALL_TARGET_HOOKS += LIBFOO_REMOVE_DATA
  endif
  ```



## 16.3 `genimage.cfg` 文件

`genimage.cfg` 文件包含 genimage 工具用于创建最终 .img 文件的输出镜像布局。

示例如下：

```
image efi-part.vfat {
        vfat {
                file EFI {
                        image = "efi-part/EFI"
                }

                file Image {
                        image = "Image"
                }
        }

        size = 32M
}

image sdimage.img {
        hdimage {
        }

        partition u-boot {
                image = "efi-part.vfat"
                offset = 8K
        }

        partition root {
                image = "rootfs.ext2"
                size = 512M
        }
}
```

- 每个 `section`（如 hdimage、vfat 等）、`partition` 必须使用一个制表符缩进。
- 每个 `file` 或其他 `subnode` 必须使用两个制表符缩进。
- 每个节点（`section`、`partition`、`file`、`subnode`）的左花括号必须与节点名在同一行，右花括号必须单独成行，且其后需换行（最后一个节点除外）。选项（如 `size`、`=`）同理。
- 每个 `option`（如 `image`、`offset`、`size`）的 `=` 号前后各有一个空格。
- 文件名必须至少以 genimage 前缀开头并以 .cfg 扩展名结尾，以便于识别。
- `offset` 和 `size` 选项允许的单位有：`G`、`M`、`K`（不支持小写 `k`）。如果无法用上述单位精确表示字节数，则使用十六进制 `0x` 前缀，或最后采用字节数。在注释中请使用 `GB`、`MB`、`KB`（不支持小写 `kb`）代替 `G`、`M`、`K`。
- 对于 GPT 分区，`partition-type-uuid` 的值必须为：EFI 系统分区用 `U`（*genimage* 会扩展为 `c12a7328-f81f-11d2-ba4b-00a0c93ec93b`），FAT 分区用 `F`（扩展为 `ebd0a0a2-b9e5-4433-87c0-68b6b72699c7`），根文件系统或其他文件系统用 `L`（扩展为 `0fc63daf-8483-4772-8e79-3d69d8477de4`）。虽然 `L` 是 *genimage* 的默认值，但我们建议在 `genimage.cfg` 文件中显式指定。最后，这些快捷方式应不加引号使用，例如 `partition-type-uuid = U`。如果指定了显式 GUID，字母应为小写。

`genimage.cfg` 文件是 Buildroot 用于生成最终镜像文件（如 sdcard.img）的 genimage 工具的输入文件。关于 *genimage* 语言的更多细节，请参阅 https://github.com/pengutronix/genimage/blob/master/README.rst。

## 16.4 文档

文档采用 [asciidoc](https://asciidoc-py.github.io/) 格式。

关于 asciidoc 语法的更多细节，请参阅 https://asciidoc-py.github.io/userguide.html。

## 16.5 支持脚本

`support/` 和 `utils/` 目录中的部分脚本采用 Python 编写，应遵循 [PEP8 Python 代码风格指南](https://www.python.org/dev/peps/pep-0008/)。

# 第 17 章 为特定开发板添加支持

Buildroot 为多种公开可用的硬件开发板提供了基础配置，方便这些开发板的用户轻松构建已知可用的系统。你也可以为 Buildroot 添加对其他开发板的支持。

为此，你需要创建一个普通的 Buildroot 配置，用于为硬件构建一个基础系统：包括（内部）工具链、内核、引导加载程序、文件系统和一个仅包含 BusyBox 的简单用户空间。不要选择特定的软件包：配置应尽可能精简，仅为目标平台构建一个可用的 BusyBox 基础系统。你当然可以为内部项目使用更复杂的配置，但 Buildroot 项目只会集成基础的开发板配置，因为软件包的选择高度依赖于具体应用。

一旦你有了已知可用的配置，运行 `make savedefconfig`。这将在 Buildroot 源码树根目录生成一个最小化的 `defconfig` 文件。将该文件移动到 `configs/` 目录，并重命名为 `<boardname>_defconfig`。

始终为各组件使用固定版本或提交哈希，而不是“最新”版本。例如，设置 `BR2_LINUX_KERNEL_CUSTOM_VERSION=y` 和 `BR2_LINUX_KERNEL_CUSTOM_VERSION_VALUE` 为你测试过的内核版本。如果你使用 Buildroot 工具链 `BR2_TOOLCHAIN_BUILDROOT`（默认选项），还需确保使用相同的内核头文件（`BR2_KERNEL_HEADERS_AS_KERNEL`，这也是默认值），并设置自定义内核头文件系列以匹配你的内核版本（`BR2_PACKAGE_HOST_LINUX_HEADERS_CUSTOM_*`）。

建议尽可能使用上游版本的 Linux 内核和引导加载程序，并尽量采用默认的内核和引导加载程序配置。如果这些配置对你的开发板不适用，或没有默认配置，欢迎你向相关上游项目提交修复补丁。

但在此期间，你可能希望存储针对目标平台的内核或引导加载程序配置或补丁。为此，请创建 `board/<manufacturer>` 目录和 `board/<manufacturer>/<boardname>` 子目录。你可以将补丁和配置存放在这些目录中，并在主 Buildroot 配置中引用。更多细节请参阅[第9章，*项目定制*](https://buildroot.org/downloads/manual/manual.html#customize)。

在提交新开发板补丁前，建议使用最新的 gitlab-CI docker 容器进行构建测试。为此可使用 `utils/docker-run` 脚本，并在其中执行如下命令：

```
 $ make <boardname>_defconfig
 $ make
```

默认情况下，Buildroot 开发者使用托管在 [gitlab.com registry](https://gitlab.com/buildroot.org/buildroot/container_registry/2395076) 的官方镜像，大多数场景下都很方便。如果你仍希望构建自己的 docker 镜像，可以在自己的 *Dockerfile* 的 `FROM` 指令中基于官方镜像：

```
FROM registry.gitlab.com/buildroot.org/buildroot/base:YYYYMMDD.HHMM
RUN ...
COPY ...
```

当前版本 *YYYYMMDD.HHMM* 可在 Buildroot 源码树顶层的 `.gitlab-ci.yml` 文件中找到；所有历史版本也可在上述 registry 中查阅。



# 第 18 章 向 Buildroot 添加新软件包

本节介绍如何将新的软件包（用户空间库或应用程序）集成到 Buildroot 中。它还展示了现有软件包是如何集成的，这对于修复问题或调整其配置也很有帮助。

当你添加新软件包时，请务必在各种条件下进行测试（参见[18.25.3节“如何测试你的软件包”](https://buildroot.org/downloads/manual/manual.html#testing-package)），并检查其代码风格（参见[18.25.2节“如何检查代码风格”](https://buildroot.org/downloads/manual/manual.html#check-package)）。

## 18.1 软件包目录（Package Directory）

首先，在 `package` 目录下为你的软件创建一个目录，例如 `libfoo`。

有些软件包已经按主题分组在子目录下：如 `x11r7`、`qt5` 和 `gstreamer`。如果你的软件包属于这些类别之一，请在相应目录下创建你的软件包目录。但不建议新建其他子目录。

## 18.2 配置文件（Config Files）

为了让软件包在配置工具中显示，你需要在软件包目录下创建配置文件。主要有两种类型：`Config.in` 和 `Config.in.host`。

### 18.2.1 `Config.in` 文件

对于目标（target）上使用的软件包，创建名为 `Config.in` 的文件。该文件包含与我们的 `libfoo` 软件相关的选项描述，会在配置工具中显示。基本内容如下：

```
config BR2_PACKAGE_LIBFOO
        bool "libfoo"
        help
          This is a comment that explains what libfoo is. The help text
          should be wrapped.

          http://foosoftware.org/libfoo/
```

`bool` 行、`help` 行以及其他关于配置选项的元数据信息都必须用一个制表符（Tab）缩进。帮助文本本身应使用一个制表符和两个空格缩进，且每行应换行以适应 72 列（Tab 算作 8 个字符，因此文本本身为 62 个字符）。帮助文本最后一行应在空行后注明该项目的上游网址。

Buildroot 的约定是，属性的顺序如下：

1. 选项类型：如 `bool`、`string` 等及其提示
2. 如有需要，`default` 默认值
3. 针对目标的依赖项，使用 `depends on`
4. 针对工具链的依赖项，使用 `depends on`
5. 针对其他软件包的依赖项，使用 `depends on`
6. 选择型依赖项，使用 `select`
7. `help` 关键字和帮助文本

你可以在 `if BR2_PACKAGE_LIBFOO ... endif` 语句中添加其他子选项，以配置你的软件的特定内容。可以参考其他软件包的例子。`Config.in` 文件的语法与内核 Kconfig 文件相同，相关文档见 http://kernel.org/doc/Documentation/kbuild/kconfig-language.txt。

最后，你需要将新的 `libfoo/Config.in` 添加到 `package/Config.in`（如果你的软件包放在某个类别子目录下，则添加到该类别的 Config.in）。这些文件在每个类别下按字母顺序排序，且*只*包含软件包的*裸*名称。

```
source "package/libfoo/Config.in"
```

### 18.2.2 `Config.in.host` 文件

有些软件包还需要为主机（host）系统构建。这里有两种情况：

- 主机软件包仅用于满足一个或多个目标软件包的构建时依赖。在这种情况下，将 `host-foo` 添加到目标软件包的 `BAR_DEPENDENCIES` 变量中。无需创建 `Config.in.host` 文件。

- 主机软件包需要用户在配置菜单中显式选择。在这种情况下，为该主机软件包创建 `Config.in.host` 文件：

  ```
  config BR2_PACKAGE_HOST_FOO
          bool "host foo"
          help
            This is a comment that explains what foo for the host is.
  
            http://foosoftware.org/foo/
  ```

  其代码风格和选项与 `Config.in` 文件相同。

  最后，你需要将新的 `libfoo/Config.in.host` 添加到 `package/Config.in.host`。这些文件按字母顺序排序，且*只*包含软件包的*裸*名称。

  ```
  source "package/foo/Config.in.host"
  ```

  这样主机软件包就会出现在 `Host utilities` 菜单中。

### 18.2.3 选择 `depends on` 还是 `select`

你的软件包的 `Config.in` 文件还必须确保依赖项被启用。通常，Buildroot 遵循以下规则：

- 对于库类依赖，使用 `select`。这些依赖通常不明显，因此让 kconfig 系统自动选择依赖项更合理。例如，*libgtk2* 软件包使用 `select BR2_PACKAGE_LIBGLIB2` 来确保该库也被启用。`select` 关键字表达的是反向依赖关系。
- 当用户需要明确知晓依赖关系时，使用 `depends on`。通常用于目标架构、MMU 支持和工具链选项的依赖（参见[18.2.4节“对目标和工具链选项的依赖”](https://buildroot.org/downloads/manual/manual.html#dependencies-target-toolchain-options)），或对“大型”依赖（如 X.org 系统）。`depends on` 关键字表达的是正向依赖关系。

**注意：** 目前 *kconfig* 语言的一个问题是，这两种依赖语义在内部并不关联。因此，可能会出现选择了某个软件包，但其某个依赖/要求未被满足的情况。

下面的例子展示了 `select` 和 `depends on` 的用法：

```
config BR2_PACKAGE_RRDTOOL
        bool "rrdtool"
        depends on BR2_USE_WCHAR
        select BR2_PACKAGE_FREETYPE
        select BR2_PACKAGE_LIBART
        select BR2_PACKAGE_LIBPNG
        select BR2_PACKAGE_ZLIB
        help
          RRDtool is the OpenSource industry standard, high performance
          data logging and graphing system for time series data.

          http://oss.oetiker.ch/rrdtool/

comment "rrdtool needs a toolchain w/ wchar"
        depends on !BR2_USE_WCHAR
```

注意，这两种依赖类型只在同类依赖之间具有传递性。

也就是说，在如下例子中：

```
config BR2_PACKAGE_A
        bool "Package A"

config BR2_PACKAGE_B
        bool "Package B"
        depends on BR2_PACKAGE_A

config BR2_PACKAGE_C
        bool "Package C"
        depends on BR2_PACKAGE_B

config BR2_PACKAGE_D
        bool "Package D"
        select BR2_PACKAGE_B

config BR2_PACKAGE_E
        bool "Package E"
        select BR2_PACKAGE_D
```

- 选择 `Package C` 时，只有在 `Package B` 被选中时才可见，而 `Package B` 只有在 `Package A` 被选中时才可见。
- 选择 `Package E` 时，会自动选择 `Package D`，进而选择 `Package B`，但不会检查 `Package B` 的依赖，因此不会选择 `Package A`。
- 由于 `Package B` 被选中但 `Package A` 没有，这就违反了 `Package B` 对 `Package A` 的依赖。因此，在这种情况下，必须显式添加传递依赖：

```
config BR2_PACKAGE_D
        bool "Package D"
        depends on BR2_PACKAGE_A
        select BR2_PACKAGE_B

config BR2_PACKAGE_E
        bool "Package E"
        depends on BR2_PACKAGE_A
        select BR2_PACKAGE_D
```

总体来说，对于库类依赖，建议优先使用 `select`。

注意，这样的依赖关系只会确保依赖项被启用，但不一定会在你的软件包之前构建。为此，还需要在软件包的 `.mk` 文件中表达该依赖。

更多格式细节请参见[代码风格](https://buildroot.org/downloads/manual/manual.html#writing-rules-config-in)。





### 18.2.4 对目标和工具链选项的依赖

许多软件包依赖于工具链的某些选项：如 C 库的选择、C++ 支持、线程支持、RPC 支持、wchar 支持或动态库支持。有些软件包只能在特定的目标架构上构建，或仅在处理器有 MMU 时可用。

这些依赖项必须在 Config.in 文件中用合适的 *depends on* 语句表达。此外，对于工具链选项的依赖，还应在未启用该选项时显示 `comment`，让用户知道为什么该软件包不可用。对于目标架构或 MMU 支持的依赖，则无需用注释显式提示：因为用户通常无法随意更换目标架构，所以没必要特别显示这些依赖。

`comment` 只应在 `config` 选项本身在工具链选项依赖满足时可见时才显示。这意味着，软件包的所有其他依赖（包括目标架构和 MMU 支持的依赖）都要在 `comment` 定义中重复。为保持清晰，建议将这些非工具链选项的 `depends on` 语句与工具链选项的 `depends on` 语句分开写。如果在同一文件中有对配置选项的依赖（通常是主软件包），建议使用全局 `if ... endif` 结构，而不是在注释和其他配置选项中重复写 `depends on`。

依赖注释的一般格式如下：

```
foo needs a toolchain w/ featA, featB, featC
```

例如：

```
mpd needs a toolchain w/ C++, threads, wchar
```

或

```
crda needs a toolchain w/ threads
```

注意，这些文本特意保持简短，以适应 80 字符终端。

本节其余部分列举了不同的目标和工具链选项、相应的配置符号以及注释文本：

- 目标架构（Target architecture）
  - 依赖符号：`BR2_powerpc`、`BR2_mips` 等（见 `arch/Config.in`）
  - 注释字符串：无需添加注释
- MMU 支持
  - 依赖符号：`BR2_USE_MMU`
  - 注释字符串：无需添加注释
- Gcc `*_sync**` 内建原子操作。不同架构支持不同字节数的原子操作，每种字节数有一个依赖符号：
  - 依赖符号：1字节用 `BR2_TOOLCHAIN_HAS_SYNC_1`，2字节用 `BR2_TOOLCHAIN_HAS_SYNC_2`，4字节用 `BR2_TOOLCHAIN_HAS_SYNC_4`，8字节用 `BR2_TOOLCHAIN_HAS_SYNC_8`
  - 注释字符串：无需添加注释
- Gcc `*_atomic**` 内建原子操作。
  - 依赖符号：`BR2_TOOLCHAIN_HAS_ATOMIC`
  - 注释字符串：无需添加注释
- 内核头文件（Kernel headers）
  - 依赖符号：`BR2_TOOLCHAIN_HEADERS_AT_LEAST_X_Y`（将 `X_Y` 替换为具体版本，见 `toolchain/Config.in`）
  - 注释字符串：`headers >= X.Y` 和/或 `headers <= X.Y`（将 `X.Y` 替换为具体版本）
- GCC 版本
  - 依赖符号：`BR2_TOOLCHAIN_GCC_AT_LEAST_X_Y`（将 `X_Y` 替换为具体版本，见 `toolchain/Config.in`）
  - 注释字符串：`gcc >= X.Y` 和/或 `gcc <= X.Y`（将 `X.Y` 替换为具体版本）
- 主机 GCC 版本
  - 依赖符号：`BR2_HOST_GCC_AT_LEAST_X_Y`（将 `X_Y` 替换为具体版本，见 `Config.in`）
  - 注释字符串：无需添加注释
  - 通常不是软件包本身要求主机 GCC 版本，而是其依赖的主机软件包有此要求。
- C 库（C library）
  - 依赖符号：`BR2_TOOLCHAIN_USES_GLIBC`、`BR2_TOOLCHAIN_USES_MUSL`、`BR2_TOOLCHAIN_USES_UCLIBC`
  - 注释字符串：对于 C 库，注释文本略有不同：`foo needs a glibc toolchain`，或 `foo needs a glibc toolchain w/ C++`
- C++ 支持
  - 依赖符号：`BR2_INSTALL_LIBSTDCPP`
  - 注释字符串：`C++`
- D 语言支持
  - 依赖符号：`BR2_TOOLCHAIN_HAS_DLANG`
  - 注释字符串：`Dlang`
- Fortran 支持
  - 依赖符号：`BR2_TOOLCHAIN_HAS_FORTRAN`
  - 注释字符串：`fortran`
- 线程支持
  - 依赖符号：`BR2_TOOLCHAIN_HAS_THREADS`
  - 注释字符串：`threads`（除非还需要 `BR2_TOOLCHAIN_HAS_THREADS_NPTL`，此时只需写 `NPTL`）
- NPTL 线程支持
  - 依赖符号：`BR2_TOOLCHAIN_HAS_THREADS_NPTL`
  - 注释字符串：`NPTL`
- RPC 支持
  - 依赖符号：`BR2_TOOLCHAIN_HAS_NATIVE_RPC`
  - 注释字符串：`RPC`
- wchar 支持
  - 依赖符号：`BR2_USE_WCHAR`
  - 注释字符串：`wchar`
- 动态库（dynamic library）
  - 依赖符号：`!BR2_STATIC_LIBS`
  - 注释字符串：`dynamic library`

### 18.2.5 对 Buildroot 构建的 Linux 内核的依赖

有些软件包需要 Buildroot 构建的 Linux 内核，通常是内核模块或固件。应在 Config.in 文件中添加注释表达此依赖，格式如下：

```
foo needs a Linux kernel to be built
```

如果同时依赖工具链选项和 Linux 内核，格式如下：

```
foo needs a toolchain w/ featA, featB, featC and a Linux kernel to be built
```

### 18.2.6 对 udev /dev 管理的依赖

如果软件包需要 udev /dev 管理，应依赖符号 `BR2_PACKAGE_HAS_UDEV`，并添加如下注释：

```
foo needs udev /dev management
```

如果同时依赖工具链选项和 udev /dev 管理，格式如下：

```
foo needs udev /dev management and a toolchain w/ featA, featB, featC
```

### 18.2.7 对虚拟软件包（virtual packages）特性依赖

有些特性可由多个软件包提供，如 openGL 库。

详见[18.12节“虚拟软件包基础设施”](https://buildroot.org/downloads/manual/manual.html#virtual-package-tutorial)。





## 18.3. `.mk` 文件

最后，这里是最难的部分。创建一个名为 `libfoo.mk` 的文件。它描述了该软件包应该如何被下载、配置、构建、安装等。

根据软件包类型，`.mk` 文件的编写方式不同，需要使用不同的基础架构：

- **通用软件包的 Makefile**（不使用 autotools 或 CMake）：这些基于与 autotools 软件包类似的基础架构，但开发者需要做更多工作。需要指定软件包的配置、编译和安装过程。所有不使用 autotools 作为构建系统的软件包都必须使用此基础架构。将来，可能会为其他构建系统编写专用基础架构。我们在[教程](https://buildroot.org/downloads/manual/manual.html#generic-package-tutorial)和[参考文档](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中有详细介绍。
- **基于 autotools 的软件包 Makefile**（autoconf、automake 等）：我们为此类软件包提供了专用基础架构，因为 autotools 是非常常见的构建系统。所有依赖 autotools 作为构建系统的新软件包*必须*使用此基础架构。详见[教程](https://buildroot.org/downloads/manual/manual.html#autotools-package-tutorial)和[参考文档](https://buildroot.org/downloads/manual/manual.html#autotools-package-reference)。
- **基于 cmake 的软件包 Makefile**：我们为此类软件包提供了专用基础架构，因为 CMake 越来越常用且行为标准化。所有依赖 CMake 的新软件包*必须*使用此基础架构。详见[教程](https://buildroot.org/downloads/manual/manual.html#cmake-package-tutorial)和[参考文档](https://buildroot.org/downloads/manual/manual.html#cmake-package-reference)。
- **Python 模块的 Makefile**：我们为使用 `flit`、`hatch`、`pep517`、`poetry`、`setuptools`、`setuptools-rust` 或 `maturin` 机制的 Python 模块提供了专用基础架构。详见[教程](https://buildroot.org/downloads/manual/manual.html#python-package-tutorial)和[参考文档](https://buildroot.org/downloads/manual/manual.html#python-package-reference)。
- **Lua 模块的 Makefile**：我们为通过 LuaRocks 网站提供的 Lua 模块提供了专用基础架构。详见[教程](https://buildroot.org/downloads/manual/manual.html#luarocks-package-tutorial)和[参考文档](https://buildroot.org/downloads/manual/manual.html#luarocks-package-reference)。

更多格式细节请参见[编写规则](https://buildroot.org/downloads/manual/manual.html#writing-rules-mk)。

## 18.4. `.hash` 文件

如果可能，你必须添加第三个文件，名为 `libfoo.hash`，其中包含 `libfoo` 软件包下载文件的哈希值。只有在无法校验哈希（如下载方式特殊）时，才可以不添加 `.hash` 文件。

当一个软件包有多个版本可选时，哈希文件可以存放在以版本号命名的子目录下，例如 `package/libfoo/1.2.3/libfoo.hash`。如果不同版本有不同的许可条款但存储在同一文件中，这一点尤其重要。否则，哈希文件应保留在软件包目录下。

该文件中存储的哈希用于校验下载文件和许可证文件的完整性。

该文件的格式为：每个需要校验哈希的文件一行，每行包含以下三个字段，字段之间用两个空格分隔：

- 哈希类型，取值为：
  - `md5`、`sha1`、`sha224`、`sha256`、`sha384`、`sha512`
- 文件的哈希值：
  - `md5` 为 32 个十六进制字符
  - `sha1` 为 40 个十六进制字符
  - `sha224` 为 56 个十六进制字符
  - `sha256` 为 64 个十六进制字符
  - `sha384` 为 96 个十六进制字符
  - `sha512` 为 128 个十六进制字符
- 文件名：
  - 对于源码归档包：文件的基本名（不含目录）
  - 对于许可证文件：在 `FOO_LICENSE_FILES` 中出现的路径

以 `#` 开头的行为注释，会被忽略。空行也会被忽略。

同一个文件可以有多条哈希记录，每条一行。这种情况下，所有哈希都必须匹配。

**注意：** 理想情况下，文件中的哈希应与上游（upstream）发布的哈希一致，例如在其官网、邮件公告等处。如果上游提供多种哈希（如 `sha1` 和 `sha512`），建议都写入 `.hash` 文件。如果上游未提供哈希或只提供 `md5`，则请自行计算至少一种强哈希（优先 `sha256`，不要只用 `md5`），并在哈希上方用注释说明。

**注意：** 许可证文件的哈希用于在软件包版本升级时检测许可证变更。哈希会在执行 make legal-info 目标时校验。对于有多个版本的软件包（如 Qt5），请在该软件包的 `<packageversion>` 子目录下创建哈希文件（参见[第 19.2 节，“补丁的应用顺序”](https://buildroot.org/downloads/manual/manual.html#patch-apply-order)）。

下面的例子定义了主 `libfoo-1.2.3.tar.bz2` 压缩包的上游 `sha1` 和 `sha256`，二进制文件的上游 `md5` 和本地计算的 `sha256`，下载补丁的 `sha256`，以及一个没有哈希的归档包：

```
# Hashes from: http://www.foosoftware.org/download/libfoo-1.2.3.tar.bz2.{sha1,sha256}:
sha1  486fb55c3efa71148fe07895fd713ea3a5ae343a  libfoo-1.2.3.tar.bz2
sha256  efc8103cc3bcb06bda6a781532d12701eb081ad83e8f90004b39ab81b65d4369  libfoo-1.2.3.tar.bz2

# md5 from: http://www.foosoftware.org/download/libfoo-1.2.3.tar.bz2.md5, sha256 locally computed:
md5  2d608f3c318c6b7557d551a5a09314f03452f1a1  libfoo-data.bin
sha256  01ba4719c80b6fe911b091a7c05124b64eeece964e09c058ef8f9805daca546b  libfoo-data.bin

# Locally computed:
sha256  ff52101fb90bbfc3fe9475e425688c660f46216d7e751c4bbdb1dc85cdccacb9  libfoo-fix-blabla.patch

# Hash for license files:
sha256  a45a845012742796534f7e91fe623262ccfb99460a2bd04015bd28d66fba95b8  COPYING
sha256  01b1f9f2c8ee648a7a596a1abe8aa4ed7899b1c9e5551bda06da6e422b04aa55  doc/COPYING.LGPL
```

如果 `.hash` 文件存在，并且其中包含一个或多个下载文件的哈希，Buildroot（下载后）计算的哈希必须与 `.hash` 文件中存储的哈希一致。如果有一个或多个哈希不匹配，Buildroot 会认为这是错误，删除下载的文件并中止。

如果 `.hash` 文件存在，但未包含某个下载文件的哈希，Buildroot 会认为这是错误并中止。但下载的文件会保留在下载目录，因为这通常表示 `.hash` 文件有误，但下载的文件可能没问题。

目前，Buildroot 会校验通过 http/ftp 服务器、Git 或 subversion 仓库、scp 复制和本地文件获取的文件的哈希。对于其他版本控制系统（如 CVS、mercurial），Buildroot 不会校验哈希，因为从这些系统获取源码时无法生成可复现的压缩包。

此外，对于可以指定自定义版本的软件包（如自定义版本字符串、远程 tarball URL 或 VCS 仓库位置和变更集），Buildroot 无法为这些情况提供哈希。不过可以[提供额外哈希列表](https://buildroot.org/downloads/manual/manual.html#customize-hashes)来覆盖这些情况。

只有保证文件内容稳定时，才应在 `.hash` 文件中添加哈希。例如，Github 自动生成的补丁不保证稳定，其哈希可能随时变化，因此不应下载此类补丁，而应将其本地添加到软件包文件夹。

如果缺少 `.hash` 文件，则不会进行任何校验。



## 18.5. `SNNfoo` 启动脚本

提供系统守护进程（daemon）的软件包通常需要在启动时以某种方式启动。Buildroot 支持多种初始化系统（init system），其中一些被视为一级支持（参见[第 6.3 节，“init system”](https://buildroot.org/downloads/manual/manual.html#init-system)），其他也可用但集成度不高。理想情况下，所有提供系统守护进程的软件包都应为 BusyBox/SysV init 提供启动脚本，并为 systemd 提供 unit 文件。

为保持一致性，启动脚本必须遵循参考样例 `package/busybox/S01syslogd` 的风格和结构。下面给出了这种风格的带注释示例。systemd unit 文件没有特定的编码风格，但如果软件包自带 unit 文件且兼容 buildroot，则优先使用。

启动脚本的命名由 `SNN` 和守护进程名组成。`NN` 是启动顺序号，需要谨慎选择。例如，需要网络服务的程序不能在 `S40network` 之前启动。脚本按字母顺序启动，因此 `S01syslogd` 会在 `S01watchdogd` 之前启动，`S02sysctl` 随后启动。

```sh
#!/bin/sh

DAEMON="syslogd"
PIDFILE="/var/run/$DAEMON.pid"

SYSLOGD_ARGS=""

# shellcheck source=/dev/null
[ -r "/etc/default/$DAEMON" ] && . "/etc/default/$DAEMON"

# BusyBox 的 syslogd 不会创建 pidfile，因此命令行需传递 "-n"，并用 "--make-pidfile" 让 start-stop-daemon 创建 pidfile。
start() {
        printf 'Starting %s: ' "$DAEMON"
        # shellcheck disable=SC2086 # 需要参数分割
        start-stop-daemon --start --background --make-pidfile \
                --pidfile "$PIDFILE" --exec "/sbin/$DAEMON" \
                -- -n $SYSLOGD_ARGS
        status=$?
        if [ "$status" -eq 0 ]; then
                echo "OK"
        else
                echo "FAIL"
        fi
        return "$status"
}

stop() {
        printf 'Stopping %s: ' "$DAEMON"
        start-stop-daemon --stop --pidfile "$PIDFILE" --exec "/sbin/$DAEMON"
        status=$?
        if [ "$status" -eq 0 ]; then
                echo "OK"
        else
                echo "FAIL"
                return "$status"
        fi
        while start-stop-daemon --stop --test --quiet --pidfile "$PIDFILE" \
                --exec "/sbin/$DAEMON"; do
                sleep 0.1
        done
        rm -f "$PIDFILE"
        return "$status"
}

restart() {
        stop
        start
}

case "$1" in
        start|stop|restart)
                "$1";;
        reload)
                # 没有真正的 "reload" 功能，直接重启。
                restart;;
        *)
                echo "Usage: $0 {start|stop|restart|reload}"
                exit 1
esac
```

脚本应尽量使用长选项以增强可读性。

### 18.5.1. 启动脚本配置

启动脚本和 unit 文件都可以从 `/etc/default/foo`（其中 `foo` 为 DAEMON 变量指定的守护进程名）读取命令行参数。一般来说，如果该文件不存在，不应阻止守护进程启动，除非有必须的站点特定参数。对于启动脚本，可以在脚本中为 `FOO_ARGS="-s -o -m -e -args"` 设定默认值，用户可通过 `/etc/default/foo` 覆盖。

### 18.5.2. PID 文件处理

PID 文件用于跟踪服务主进程。如何处理取决于服务是否自己创建 PID 文件，以及是否在关闭时删除。

- 如果服务不会自己创建 PID 文件，请以前台模式启动守护进程，并用 `start-stop-daemon --make-pidfile --background` 让 `start-stop-daemon` 创建 PID 文件。参见 `S01syslogd` 示例：

  ```sh
  start-stop-daemon --start --background --make-pidfile \
          --pidfile "$PIDFILE" --exec "/sbin/$DAEMON" \
          -- -n $SYSLOGD_ARGS
  ```

- 如果服务会自己创建 PID 文件，请将 `--pidfile` 选项同时传递给 `start-stop-daemon` **和守护进程本身**（或在配置文件中设置），确保两者一致。参见 `S45NetworkManager` 示例：

  ```sh
  start-stop-daemon --start --pidfile "$PIDFILE" \
          --exec "/usr/sbin/$DAEMON" \
          -- --pid-file="$PIDFILE" $NETWORKMANAGER_ARGS
  ```

- 如果服务在关闭时会删除 PID 文件，请在停止时用循环检测 PID 文件是否已消失，参见 `S45NetworkManager` 示例：

  ```sh
  while [ -f "$PIDFILE" ]; do
          sleep 0.1
  done
  ```

- 如果服务在关闭时不会删除 PID 文件，请用 `start-stop-daemon` 循环检测服务是否仍在运行，进程结束后再删除 PID 文件。参见 `S01syslogd` 示例：

  ```sh
  while start-stop-daemon --stop --test --quiet --pidfile "$PIDFILE" \
          --exec "/sbin/$DAEMON"; do
          sleep 0.1
  done
  rm -f "$PIDFILE"
  ```

  注意 `--test` 标志，它会让 `start-stop-daemon` 实际上不停止服务，而是测试是否可以停止，如果服务未运行则测试失败。

### 18.5.3. 停止服务

stop 函数在返回前应检查守护进程是否真正退出，否则 restart 可能失败，因为新实例可能在旧实例未完全退出前启动。具体做法取决于服务 PID 文件的处理方式（见上文）。建议所有 `start-stop-daemon` 命令都加上 `--exec "/sbin/$DAEMON"`，确保信号只发给与 `$DAEMON` 匹配的 PID。

### 18.5.4. 重新加载服务配置

支持某种方式重新加载配置（如 `SIGHUP`）的程序应提供类似于 stop() 的 reload() 函数。`start-stop-daemon` 支持 `--stop --signal HUP`。发送信号时请务必使用符号名而非信号编号，因为信号编号在不同 CPU 架构间可能不同，符号名也更易读。

### 18.5.5. 返回码

启动脚本的动作函数应返回成功（或失败）码，通常为相关 `start-stop-daemon` 操作的返回码。最后一个动作的返回码应作为整个启动脚本的返回码，便于自动检测成功与否（如被其他脚本调用时）。注意如果没有显式 `return`，脚本或函数的最后一条命令的返回码就是其返回码，因此并非总需要显式 return。

### 18.5.6. 日志

当服务进程 fork 到后台，或 `start-stop-daemon --background` 这样做时，stdout 和 stderr 通常会被关闭，服务写到这些的日志信息会丢失。建议尽可能配置服务日志到 syslog（优先），或专用日志文件。







## 18.6. 针对具有特定构建系统的软件包的基础设施

所谓“具有特定构建系统的软件包”，是指那些构建系统不是标准构建系统（如 autotools 或 CMake）的所有软件包。这通常包括基于手写 Makefile 或 shell 脚本的构建系统的软件包。

### 18.6.1. `generic-package` 教程

```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_LICENSE = GPL-3.0+
11: LIBFOO_LICENSE_FILES = COPYING
12: LIBFOO_INSTALL_STAGING = YES
13: LIBFOO_CONFIG_SCRIPTS = libfoo-config
14: LIBFOO_DEPENDENCIES = host-libaaa libbbb
15:
16: define LIBFOO_BUILD_CMDS
17:     $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D) all
18: endef
19:
20: define LIBFOO_INSTALL_STAGING_CMDS
21:     $(INSTALL) -D -m 0755 $(@D)/libfoo.a $(STAGING_DIR)/usr/lib/libfoo.a
22:     $(INSTALL) -D -m 0644 $(@D)/foo.h $(STAGING_DIR)/usr/include/foo.h
23:     $(INSTALL) -D -m 0755 $(@D)/libfoo.so* $(STAGING_DIR)/usr/lib
24: endef
25:
26: define LIBFOO_INSTALL_TARGET_CMDS
27:     $(INSTALL) -D -m 0755 $(@D)/libfoo.so* $(TARGET_DIR)/usr/lib
28:     $(INSTALL) -d -m 0755 $(TARGET_DIR)/etc/foo.d
29: endef
30:
31: define LIBFOO_USERS
32:     foo -1 libfoo -1 * - - - LibFoo daemon
33: endef
34:
35: define LIBFOO_DEVICES
36:     /dev/foo c 666 0 0 42 0 - - -
37: endef
38:
39: define LIBFOO_PERMISSIONS
40:     /bin/foo f 4755 foo libfoo - - - - -
41: endef
42:
43: $(eval $(generic-package))
```

该 Makefile 在第 7 至 11 行给出了元数据信息：软件包的版本（`LIBFOO_VERSION`）、包含该软件包的 tarball 文件名（`LIBFOO_SOURCE`，推荐使用 xz 压缩的 tarball）、tarball 可下载的互联网地址（`LIBFOO_SITE`）、许可证（`LIBFOO_LICENSE`）以及包含许可证文本的文件（`LIBFOO_LICENSE_FILES`）。所有变量都必须以相同的前缀开头，这里是 `LIBFOO_`。该前缀始终是软件包名称的大写形式（见下文了解软件包名称的定义位置）。

第 12 行指定该软件包需要向 staging 空间安装内容。对于库（library）来说，这通常是必需的，因为它们必须在 staging 空间安装头文件和其他开发文件。这将确保 `LIBFOO_INSTALL_STAGING_CMDS` 变量中列出的命令会被执行。

第 13 行指定需要对某些在 `LIBFOO_INSTALL_STAGING_CMDS` 阶段安装的 *libfoo-config* 文件进行修正。这些 *-config 文件是可执行的 shell 脚本，位于 *$(STAGING_DIR)/usr/bin* 目录下，被其他第三方软件包调用，用于获取该软件包的位置和链接参数。

问题在于，这些 *-config 文件默认给出的链接参数是主机系统的，无法用于交叉编译。

例如：*-I/usr/include* 而不是 *-I$(STAGING_DIR)/usr/include*，或 *-L/usr/lib* 而不是 *-L$(STAGING_DIR)/usr/lib*

因此需要用 sed 对这些脚本做一些处理，使其给出正确的参数。`LIBFOO_CONFIG_SCRIPTS` 的参数是需要修正的 shell 脚本文件名，这些名称都相对于 *$(STAGING_DIR)/usr/bin*，如有多个文件名可用空格分隔。

此外，`LIBFOO_CONFIG_SCRIPTS` 中列出的脚本会从 `$(TARGET_DIR)/usr/bin` 中移除，因为它们在目标系统上不需要。

**示例 18.1. 配置脚本：*divine* 软件包**

软件包 divine 安装 shell 脚本 *$(STAGING_DIR)/usr/bin/divine-config*。

因此其修正方式如下：

```
DIVINE_CONFIG_SCRIPTS = divine-config
```

**示例 18.2. 配置脚本：*imagemagick* 软件包：**

软件包 imagemagick 安装以下脚本：*$(STAGING_DIR)/usr/bin/{Magick,Magick++,MagickCore,MagickWand,Wand}-config*

因此其修正方式如下：

```
IMAGEMAGICK_CONFIG_SCRIPTS = \
   Magick-config Magick++-config \
   MagickCore-config MagickWand-config Wand-config
```

第 14 行指定该软件包依赖的软件包列表。这些依赖以小写包名列出，可以是目标（target）包（不带 `host-` 前缀）或主机（host）包（带 `host-` 前缀）。Buildroot 会确保所有这些依赖包在当前包开始配置前已构建并安装。

Makefile 的其余部分（第 16~29 行）定义了软件包配置、编译和安装各阶段应执行的操作。`LIBFOO_BUILD_CMDS` 指定构建该软件包应执行的步骤。`LIBFOO_INSTALL_STAGING_CMDS` 指定安装到 staging 空间应执行的步骤。`LIBFOO_INSTALL_TARGET_CMDS` 指定安装到目标空间应执行的步骤。

所有这些步骤都依赖于 `$(@D)` 变量，该变量包含软件包源码解压后的目录。

第 31~33 行定义了该软件包使用的用户（如以非 root 身份运行守护进程）（`LIBFOO_USERS`）。

在第 35~37 行，我们定义了该软件包使用的设备节点文件（`LIBFOO_DEVICES`）。

在第 39~41 行，我们定义了该软件包安装的特定文件需要设置的权限（`LIBFOO_PERMISSIONS`）。

最后，在第 43 行，我们调用了 `generic-package` 函数。该函数会根据前面定义的变量，自动生成所有让你的软件包能够正常工作的 Makefile 代码。



### 18.6.2. `generic-package` 参考

`generic-package` 有两种变体。`generic-package` 宏用于为目标（target）进行交叉编译的软件包。`host-generic-package` 宏用于主机（host）软件包，即为主机本地编译的软件包。在同一个 `.mk` 文件中可以同时调用这两个宏：一次用于生成目标包的规则，一次用于生成主机包的规则：

```
$(eval $(generic-package))
$(eval $(host-generic-package))
```

如果目标包的编译需要在主机上安装某些工具，这种做法会很有用。如果包名为 `libfoo`，那么目标包的名称也是 `libfoo`，而主机包的名称是 `host-libfoo`。如果其他软件包依赖于 `libfoo` 或 `host-libfoo`，应在其 DEPENDENCIES 变量中使用这些名称。

对 `generic-package` 和/或 `host-generic-package` 宏的调用***必须***在 `.mk` 文件的末尾、所有变量定义之后。若两者都调用，`host-generic-package` ***必须***在 `generic-package` 之后调用。

对于目标包，`generic-package` 使用 `.mk` 文件中以大写包名为前缀定义的变量：`LIBFOO_*`。`host-generic-package` 使用 `HOST_LIBFOO_*` 变量。对于*某些*变量，如果没有定义 `HOST_LIBFOO_` 前缀的变量，包基础设施会使用对应的 `LIBFOO_` 前缀变量。这适用于目标包和主机包值可能相同的变量。详见下文。

可以在 `.mk` 文件中设置以下变量来提供元数据信息（假设包名为 `libfoo`）：

- `LIBFOO_VERSION`，必填，必须包含软件包的版本。如果没有 `HOST_LIBFOO_VERSION`，则默认与 `LIBFOO_VERSION` 相同。对于直接从版本控制系统获取的软件包，也可以是修订号或标签。例如：

  - 发布版 tarball 的版本：`LIBFOO_VERSION = 0.1.2`

  - git 树的 sha1：`LIBFOO_VERSION = cb9d6aa9429e838f0e54faa3d455bcbab5eef057`

  - git 树的标签：`LIBFOO_VERSION = v0.1.2`

    **注意：** 不支持将分支名用作 `FOO_VERSION`，因为这实际上无法达到预期效果：

    1. 由于本地缓存，Buildroot 不会重新获取仓库，因此希望跟踪远程仓库的人会感到困惑和失望；
    2. 因为两次构建不可能完全同时进行，且远程仓库的分支可能随时有新提交，所以即使两个用户使用相同的 Buildroot 树和配置，也可能获取到不同的源码，导致构建结果不可复现，这也会让人感到困惑和失望。

- `LIBFOO_SOURCE` 可包含软件包 tarball 的名称，Buildroot 会用它从 `LIBFOO_SITE` 下载 tarball。如果未指定 `HOST_LIBFOO_SOURCE`，则默认与 `LIBFOO_SOURCE` 相同。如果都未指定，则默认值为 `libfoo-$(LIBFOO_VERSION).tar.gz`。例如：`LIBFOO_SOURCE = foobar-$(LIBFOO_VERSION).tar.bz2`

- `LIBFOO_PATCH` 可包含以空格分隔的补丁文件名列表，Buildroot 会下载并应用到软件包源码。如果条目中包含 `://`，Buildroot 会认为它是完整 URL 并用该地址下载补丁，否则会从 `LIBFOO_SITE` 下载补丁。如果未指定 `HOST_LIBFOO_PATCH`，则默认与 `LIBFOO_PATCH` 相同。注意，Buildroot 自带的补丁采用不同机制：所有在 Buildroot 软件包目录下的 `*.patch` 文件会在源码解压后自动应用（详见[补丁策略](https://buildroot.org/downloads/manual/manual.html#patch-policy)）。最后，`LIBFOO_PATCH` 变量中列出的补丁会在 Buildroot 包目录下的补丁之前应用。

- `LIBFOO_SITE` 提供软件包的位置，可以是 URL 或本地文件系统路径。支持 HTTP、FTP 和 SCP 等 URL 类型来获取 tarball。在这些情况下不要加结尾斜杠：Buildroot 会自动在目录和文件名之间添加斜杠。支持 Git、Subversion、Mercurial 和 Bazaar 等源码管理系统直接获取源码。还有辅助函数可简化从 GitHub 下载源码 tarball（详见[如何添加 GitHub 软件包](https://buildroot.org/downloads/manual/manual.html#github-download-url)）。文件系统路径可用于指定 tarball 或源码目录。更多检索细节见下文 `LIBFOO_SITE_METHOD`。注意，SCP URL 格式为 `scp://[user@]host:filepath`，其中 filepath 相对于用户主目录，因此如需绝对路径请加斜杠：`scp://[user@]host:/absolutepath`。SFTP 也同理。如果未指定 `HOST_LIBFOO_SITE`，则默认与 `LIBFOO_SITE` 相同。例如：`LIBFOO_SITE=http://www.libfoosoftware.org/libfoo` `LIBFOO_SITE=http://svn.xiph.org/trunk/Tremor` `LIBFOO_SITE=/opt/software/libfoo.tar.gz` `LIBFOO_SITE=$(TOPDIR)/../src/libfoo`

- `LIBFOO_DL_OPTS` 是传递给下载器的额外选项（以空格分隔）。适用于需要服务器端登录验证或代理的下载。所有 `LIBFOO_SITE_METHOD` 支持的下载方式都支持该选项，具体可查阅相应下载工具的 man 手册。对于 git，`FOO_DL_OPTS` 只会传递给 `git fetch`，不会传递给其他 git 命令（尤其不会传递给 `git lfs fetch` 或 `git submodule update`）。

- `LIBFOO_EXTRA_DOWNLOADS` 是 Buildroot 需要额外下载的文件列表（以空格分隔）。如果条目中包含 `://`，Buildroot 会认为它是完整 URL 并用该地址下载，否则会从 `LIBFOO_SITE` 下载。Buildroot 只负责下载这些文件，不会做其他处理：需要由包配方在 `$(LIBFOO_DL_DIR)` 中自行使用这些文件。



- `LIBFOO_SITE_METHOD` 用于指定获取或复制软件包源码的方法。在大多数情况下，Buildroot 会根据 `LIBFOO_SITE` 的内容自动判断方法，无需手动设置 `LIBFOO_SITE_METHOD`。如果未指定 `HOST_LIBFOO_SITE_METHOD`，则默认与 `LIBFOO_SITE_METHOD` 相同。`LIBFOO_SITE_METHOD` 可选值如下：

  - `wget`：用于通过 FTP/HTTP 下载 tarball。当 `LIBFOO_SITE` 以 `http://`、`https://` 或 `ftp://` 开头时默认使用。
  - `scp`：通过 SSH 的 scp 下载 tarball。当 `LIBFOO_SITE` 以 `scp://` 开头时默认使用。
  - `sftp`：通过 SSH 的 sftp 下载 tarball。当 `LIBFOO_SITE` 以 `sftp://` 开头时默认使用。
  - `svn`：从 Subversion 仓库获取源码。当 `LIBFOO_SITE` 以 `svn://` 开头时默认使用。如果 `LIBFOO_SITE` 指定了 `http://` 的 Subversion 仓库 URL，*必须*指定 `LIBFOO_SITE_METHOD=svn`。Buildroot 会执行 checkout 并将其保存为 tarball，后续构建会使用该 tarball 而不是重新 checkout。
  - `cvs`：从 CVS 仓库获取源码。当 `LIBFOO_SITE` 以 `cvs://` 开头时默认使用。下载的源码同样会被缓存为 tarball。默认使用匿名 pserver 模式，除非在 `LIBFOO_SITE` 中显式指定。`LIBFOO_SITE` *必须*包含源码 URL 及远程仓库目录，模块名为包名。`LIBFOO_VERSION` *必须*为标签、分支或日期（如 "2014-10-20"，详见 man cvs）。
  - `git`：从 Git 仓库获取源码。当 `LIBFOO_SITE` 以 `git://` 开头时默认使用。源码同样会被缓存为 tarball。
  - `hg`：从 Mercurial 仓库获取源码。当 `LIBFOO_SITE` 包含 Mercurial 仓库 URL 时，*必须*指定 `LIBFOO_SITE_METHOD=hg`。源码同样会被缓存为 tarball。
  - `bzr`：从 Bazaar 仓库获取源码。当 `LIBFOO_SITE` 以 `bzr://` 开头时默认使用。源码同样会被缓存为 tarball。
  - `file`：本地 tarball。当 `LIBFOO_SITE` 指定为本地文件名时应使用。适用于未公开发布或无版本控制的软件。
  - `local`：本地源码目录。当 `LIBFOO_SITE` 指定为本地源码目录时应使用。Buildroot 会将源码目录内容复制到包的构建目录。注意，`local` 包不会应用补丁。如需补丁可用 `LIBFOO_POST_RSYNC_HOOKS`，详见[POST_RSYNC 钩子用法](https://buildroot.org/downloads/manual/manual.html#hooks-rsync)。
  - `smb`：从 SMB 共享获取源码。当 `LIBFOO_SITE` 以 `smb://` 开头时默认使用，使用 `curl` 作为下载后端。语法：`LIBFOO_SITE=smb://<server>/<share>/<path>`。可能需要在 `LIBFOO_DL_OPTS` 中定义 -u 选项，详见 [curl 文档](https://curl.se/docs/tutorial.html)。

- `LIBFOO_GIT_SUBMODULES` 可设为 `YES`，表示为仓库中的 git 子模块创建归档，仅适用于 git 下载的软件包（即 `LIBFOO_SITE_METHOD=git`）。注意，如果子模块包含内置库，建议单独打包而非使用子模块。

- `LIBFOO_GIT_LFS` 若仓库使用 Git LFS 存储大文件，需设为 `YES`，仅适用于 git 下载的软件包。

- `LIBFOO_SVN_EXTERNALS` 可设为 `YES`，表示为 svn 外部引用创建归档，仅适用于 subversion 下载的软件包。

- `LIBFOO_STRIP_COMPONENTS` 指定 tar 解包时要去除的前导目录层数。大多数包的 tarball 有一级 `<pkg-name>-<pkg-version>` 目录，Buildroot 默认传递 --strip-components=1。若包结构不同，可设置此变量。默认值：1。

- `LIBFOO_EXCLUDES` 是解包时要排除的模式列表（以空格分隔），每项作为 tar 的 `--exclude` 选项。默认空。

- `LIBFOO_DEPENDENCIES` 指定当前目标包编译所需的依赖包（以包名表示）。这些依赖会在当前包配置前编译和安装。但依赖包配置变更不会强制重建当前包。`HOST_LIBFOO_DEPENDENCIES` 以类似方式指定主机包依赖。

- `LIBFOO_EXTRACT_DEPENDENCIES` 指定当前目标包解包前所需依赖（以包名表示）。这些依赖会在当前包解包前编译和安装。该变量仅供包基础设施内部使用，通常不建议包直接使用。

- `LIBFOO_PATCH_DEPENDENCIES` 指定当前包打补丁前所需依赖（以包名表示）。这些依赖会在当前包打补丁前被解包和打补丁（但不一定编译）。`HOST_LIBFOO_PATCH_DEPENDENCIES` 以类似方式指定主机包依赖。该变量很少用，通常应使用 `LIBFOO_DEPENDENCIES`。

- `LIBFOO_PROVIDES` 列出 `libfoo` 实现的所有虚拟包。详见[虚拟包基础设施](https://buildroot.org/downloads/manual/manual.html#virtual-package-tutorial)。

- `LIBFOO_INSTALL_STAGING` 可设为 `YES` 或 `NO`（默认）。若为 `YES`，则会执行 `LIBFOO_INSTALL_STAGING_CMDS` 变量中的命令，将包安装到 staging 目录。

- `LIBFOO_INSTALL_TARGET` 可设为 `YES`（默认）或 `NO`。若为 `YES`，则会执行 `LIBFOO_INSTALL_TARGET_CMDS` 变量中的命令，将包安装到目标目录。

- `LIBFOO_INSTALL_IMAGES` 可设为 `YES` 或 `NO`（默认）。若为 `YES`，则会执行 `LIBFOO_INSTALL_IMAGES_CMDS` 变量中的命令，将包安装到 images 目录。

- `LIBFOO_CONFIG_SCRIPTS` 列出 *$(STAGING_DIR)/usr/bin* 下需要特殊修正以支持交叉编译的文件名。可用空格分隔多个文件名，均为相对路径。`LIBFOO_CONFIG_SCRIPTS` 中的文件也会从 `$(TARGET_DIR)/usr/bin` 移除，因为目标系统不需要。

- `LIBFOO_DEVICES` 列出使用静态设备表时 Buildroot 需创建的设备文件，语法采用 makedevs 格式，详见[Makedev 语法文档](https://buildroot.org/downloads/manual/manual.html#makedev-syntax)。该变量为可选项。

- `LIBFOO_PERMISSIONS` 列出构建结束后需更改权限的文件，语法同样采用 makedevs 格式，详见[Makedev 语法文档](https://buildroot.org/downloads/manual/manual.html#makedev-syntax)。该变量为可选项。

- `LIBFOO_USERS` 列出该软件包需要创建的用户（如需以特定用户身份运行守护进程或定时任务）。语法与 makedevs 类似，详见[Makeusers 语法文档](https://buildroot.org/downloads/manual/manual.html#makeuser-syntax)。该变量为可选项。

- `LIBFOO_LICENSE` 定义软件包的许可证（或多种许可证）。该名称会出现在 `make legal-info` 生成的 manifest 文件中。如果许可证在 [SPDX License List](https://spdx.org/licenses/) 中，建议使用 SPDX 简称以统一 manifest 文件。否则请精确简明地描述许可证，避免使用如 `BSD` 这类模糊名称。该变量为可选项，若未定义则 manifest 文件中该包的 license 字段为 `unknown`。格式要求如下：

  - 若包的不同部分采用不同许可证，用逗号分隔（如 `LIBFOO_LICENSE = GPL-2.0+, LGPL-2.1+`）。如能明确区分各组件的许可证，可用括号注明（如 `LIBFOO_LICENSE = GPL-2.0+ (programs), LGPL-2.1+ (libraries)`）。
  - 若某些许可证依赖于子选项启用，则用逗号追加条件许可证（如 `FOO_LICENSE += , GPL-2.0+ (programs)`）；基础设施会自动去除逗号前的空格。
  - 若包为双重许可，用 `or` 关键字分隔（如 `LIBFOO_LICENSE = AFL-2.1 or GPL-2.0+`）。

- `LIBFOO_LICENSE_FILES` 是包 tarball 中包含许可证的文件列表（以空格分隔）。`make legal-info` 会将这些文件全部复制到 `legal-info` 目录。详见[法律声明与许可章节](https://buildroot.org/downloads/manual/manual.html#legal-info)。该变量为可选项，若未定义则会有警告，manifest 文件中 license files 字段为 `not saved`。

- `LIBFOO_ACTUAL_SOURCE_TARBALL` 仅适用于 `LIBFOO_SITE` / `LIBFOO_SOURCE` 指向的归档实际上不包含源码而是二进制代码的情况。这种情况极为罕见，主要用于外部工具链（已编译），理论上也可用于其他包。此时通常会有单独的源码归档。设置 `LIBFOO_ACTUAL_SOURCE_TARBALL` 后，Buildroot 会在执行 `make legal-info` 时下载并使用该源码归档收集法律相关材料。注意该文件不会在常规构建或 `make source` 时下载。

- `LIBFOO_ACTUAL_SOURCE_SITE` 指定实际源码归档的位置。默认值为 `LIBFOO_SITE`，若二进制和源码归档在同一目录无需设置。若未设置 `LIBFOO_ACTUAL_SOURCE_TARBALL`，则无需定义该变量。

- `LIBFOO_REDISTRIBUTE` 可设为 `YES`（默认）或 `NO`，用于指示该包源码是否允许再分发。对于非开源包请设为 `NO`，Buildroot 在收集 `legal-info` 时不会保存该包源码。

- `LIBFOO_FLAT_STACKSIZE` 定义以 FLAT 二进制格式构建的应用程序的堆栈大小。NOMMU 架构处理器的应用堆栈运行时无法扩展，FLAT 格式默认堆栈仅 4k 字节。如需更大堆栈可在此指定。

- `LIBFOO_BIN_ARCH_EXCLUDE` 是需在交叉编译二进制检查时忽略的路径列表（以空格分隔，相对于目标目录）。除非包在默认位置（如 `/lib/firmware`、`/usr/lib/firmware`、`/lib/modules`、`/usr/lib/modules`、`/usr/share`）外安装二进制 blob，否则很少需要设置。

- `LIBFOO_IGNORE_CVES` 是需 Buildroot CVE 跟踪工具忽略的 CVE 列表（以空格分隔）。通常用于补丁已修复或该 CVE 实际不影响 Buildroot 包的情况。每次添加 CVE 前必须有 Makefile 注释。例如：

  ```
  # 0001-fix-cve-2020-12345.patch
  LIBFOO_IGNORE_CVES += CVE-2020-12345
  # 仅在与 libbaz 一起构建时受影响，Buildroot 不支持 libbaz
  LIBFOO_IGNORE_CVES += CVE-2020-54321
  ```



- `LIBFOO_CPE_ID_*` 变量是一组用于定义软件包 [CPE 标识符](https://nvd.nist.gov/products/cpe) 的变量。可用变量如下：

  - `LIBFOO_CPE_ID_VALID`，若设为 `YES`，表示以下各变量的默认值均适用，并生成有效的 CPE ID。
  - `LIBFOO_CPE_ID_PREFIX`，指定 CPE 标识符的前缀（前三个字段）。未定义时默认值为 `cpe:2.3:a`。
  - `LIBFOO_CPE_ID_VENDOR`，指定 CPE 标识符的厂商部分。未定义时默认值为 `<pkgname>_project`。
  - `LIBFOO_CPE_ID_PRODUCT`，指定 CPE 标识符的产品部分。未定义时默认值为 `<pkgname>`。
  - `LIBFOO_CPE_ID_VERSION`，指定 CPE 标识符的版本部分。未定义时默认值为 `$(LIBFOO_VERSION)`。
  - `LIBFOO_CPE_ID_UPDATE`，指定 CPE 标识符的 *update* 部分。未定义时默认值为 `*`。

  如果定义了上述任一变量，则通用包基础设施会认为该包提供了有效的 CPE 信息，并据此定义 `LIBFOO_CPE_ID`。

  对于主机包（host package），若未定义其 `LIBFOO_CPE_ID_*` 变量，则会继承对应目标包的变量值。

推荐的定义方式如下：

```
LIBFOO_VERSION = 2.32
```

下面是构建流程各阶段可用的命令变量：

- `LIBFOO_EXTRACT_CMDS` 指定解包操作。一般无需设置，Buildroot 会自动处理 tarball。若包为非标准归档格式（如 ZIP、RAR）或 tarball 结构特殊，可用此变量覆盖默认行为。
- `LIBFOO_CONFIGURE_CMDS` 指定编译前的配置操作。
- `LIBFOO_BUILD_CMDS` 指定编译操作。
- `HOST_LIBFOO_INSTALL_CMDS` 指定主机包的安装操作。包需将所有文件（包括头文件等开发文件）安装到 `$(HOST_DIR)`，以便其他包可在其基础上编译。
- `LIBFOO_INSTALL_TARGET_CMDS` 指定目标包安装到目标目录的操作。包需将运行所需文件安装到 `$(TARGET_DIR)`，头文件、静态库和文档会在最终生成目标文件系统时移除。
- `LIBFOO_INSTALL_STAGING_CMDS` 指定目标包安装到 staging 目录的操作。包需将所有开发文件安装到 `$(STAGING_DIR)`，以便其他包编译时使用。
- `LIBFOO_INSTALL_IMAGES_CMDS` 指定目标包安装到 images 目录的操作。包需将二进制镜像（如内核、引导加载器、根文件系统镜像等）安装到 `$(BINARIES_DIR)`。仅适用于不属于 `TARGET_DIR` 但启动板卡所需的镜像文件。
- `LIBFOO_INSTALL_INIT_SYSV`、`LIBFOO_INSTALL_INIT_OPENRC` 和 `LIBFOO_INSTALL_INIT_SYSTEMD` 分别指定安装 systemV、openrc 或 systemd 启动脚本的操作。仅在配置了对应 init 系统时执行（如配置 systemd，仅执行 `LIBFOO_INSTALL_INIT_SYSTEMD`）。唯一例外是 openrc 作为 init 系统且未设置 `LIBFOO_INSTALL_INIT_OPENRC` 时，会调用 `LIBFOO_INSTALL_INIT_SYSV`，因 openrc 支持 sysv 脚本。使用 systemd 时，buildroot 会在镜像构建最后阶段自动启用所有服务（`systemctl preset-all`），如需禁止某服务自动启用可添加 preset 文件。
- `LIBFOO_HELP_CMDS` 指定打印包帮助信息的操作，会包含在主 `make help` 输出中。该变量极少用，除非确有自定义规则需求。***除非确有需要，否则不要使用此变量。***
- `LIBFOO_LINUX_CONFIG_FIXUPS` 指定构建和使用该包所需的 Linux 内核配置选项，否则包将无法正常工作。应为一组 kconfig 调整操作（如 `KCONFIG_ENABLE_OPT`、`KCONFIG_DISABLE_OPT`、`KCONFIG_SET_OPT`）。该变量极少用。
- `LIBFOO_BUSYBOX_CONFIG_FIXUPS` 指定使用该包（尤其在脚本中）所需或不需要的 Busybox 配置选项。应为一组 kconfig 调整操作。

推荐的定义方式如下：

```
define LIBFOO_CONFIGURE_CMDS
        action 1
        action 2
        action 3
endef
```

在操作定义中，可用如下变量：

- `$(LIBFOO_PKGDIR)`：包含 `libfoo.mk` 和 `Config.in` 的目录路径。用于安装 Buildroot 自带的文件（如运行时配置、开机画面等）。
- `$(@D)`：源码解压目录。
- `$(LIBFOO_DL_DIR)`：Buildroot 为 `libfoo` 下载的所有文件存放目录。
- `$(TARGET_CC)`、`$(TARGET_LD)` 等：目标交叉编译工具。
- `$(TARGET_CROSS)`：交叉编译工具链前缀。
- 当然还有 `$(HOST_DIR)`、`$(STAGING_DIR)`、`$(TARGET_DIR)`，用于正确安装包。这些变量指向全局 *host*、*staging*、*target* 目录，若启用 *per-package directory*，则指向当前包的目录。对包来说无差别，直接使用即可。详见[顶层并行构建](https://buildroot.org/downloads/manual/manual.html#top-level-parallel-build)。

最后，还可以使用钩子（hook）。详见[各构建阶段可用钩子](https://buildroot.org/downloads/manual/manual.html#hooks)。



## 18.7. 针对 autotools 构建系统的软件包基础设施

### 18.7.1. `autotools-package` 教程

首先，让我们通过一个例子，了解如何为基于 autotools 的软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_INSTALL_STAGING = YES
11: LIBFOO_INSTALL_TARGET = NO
12: LIBFOO_CONF_OPTS = --disable-shared
13: LIBFOO_DEPENDENCIES = libglib2 host-pkgconf
14:
15: $(eval $(autotools-package))
```

第 7 行声明了软件包的版本。

第 8、9 行声明了 tarball 的名称（推荐使用 xz 压缩的 tarball）及其在 Web 上的位置。Buildroot 会自动从该位置下载 tarball。

第 10 行告知 Buildroot 将软件包安装到 staging 目录。staging 目录位于 `output/staging/`，用于安装所有软件包及其开发文件等。默认情况下，软件包不会安装到 staging 目录，只有库（library）通常需要这样做，因为它们的开发文件会被其他依赖它们的库或应用编译时使用。启用 staging 安装后，默认通过 `make install` 命令安装。

第 11 行告知 Buildroot 不将该软件包安装到目标目录。目标目录包含将运行在目标上的根文件系统。对于纯静态库，无需安装到目标目录，因为运行时不会用到。默认情况下，目标安装是启用的；将此变量设为 NO 的情况极少。默认也是通过 `make install` 安装。

第 12 行指定了自定义的 configure 选项，会在配置和构建软件包前传递给 `./configure` 脚本。

第 13 行声明了依赖项，确保它们会在本包构建前被编译。

最后，第 15 行调用 `autotools-package` 宏，生成实际允许该包被构建的所有 Makefile 规则。

### 18.7.2. `autotools-package` 参考

autotools 包基础设施的主要宏是 `autotools-package`，其用法类似于 `generic-package` 宏。也支持目标包和主机包，主机包可用 `host-autotools-package` 宏。

与 generic 基础设施一样，autotools 基础设施通过在调用 `autotools-package` 宏前定义一系列变量来工作。

所有 [generic 包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference) 中存在的软件包元数据变量，在 autotools 基础设施中同样适用。

此外，还可以定义一些 autotools 基础设施特有的变量。许多变量仅在特定场景下有用，典型软件包只需用到其中少数几个。

- `LIBFOO_SUBDIR` 可指定包含 configure 脚本的子目录名称。如果主 configure 脚本不在 tarball 解压根目录时很有用。若未指定 `HOST_LIBFOO_SUBDIR`，则默认与 `LIBFOO_SUBDIR` 相同。
- `LIBFOO_CONF_ENV`，指定传递给 configure 脚本的额外环境变量。默认空。
- `LIBFOO_CONF_OPTS`，指定传递给 configure 脚本的额外参数。默认空。
- `LIBFOO_MAKE`，指定替代的 `make` 命令。通常用于配置启用了并行 make（`BR2_JLEVEL`）但该包不支持并行构建时。默认值为 `$(MAKE)`。如包不支持并行构建，应设为 `LIBFOO_MAKE=$(MAKE1)`。
- `LIBFOO_MAKE_ENV`，指定构建步骤中传递给 make 的额外环境变量，位于 make 命令前。默认空。
- `LIBFOO_MAKE_OPTS`，指定构建步骤中传递给 make 的额外变量，位于 make 命令后。默认空。
- `LIBFOO_AUTORECONF`，指定是否需要自动重新配置（即是否需重新运行 autoconf、automake、libtool 等生成 configure 脚本和 Makefile.in 文件）。可选值为 `YES` 或 `NO`，默认 `NO`。
- `LIBFOO_AUTORECONF_ENV`，如 `LIBFOO_AUTORECONF=YES`，则指定传递给 *autoreconf* 程序的额外环境变量。默认空。
- `LIBFOO_AUTORECONF_OPTS`，如 `LIBFOO_AUTORECONF=YES`，则指定传递给 *autoreconf* 程序的额外参数。默认空。
- `LIBFOO_AUTOPOINT`，指定是否需要 autopoint（即包是否需要 I18N 基础设施）。仅在 `LIBFOO_AUTORECONF=YES` 时有效。可选值为 `YES` 或 `NO`，默认 `NO`。
- `LIBFOO_LIBTOOL_PATCH`，指定是否应用 Buildroot 修复 libtool 交叉编译问题的补丁。可选值为 `YES` 或 `NO`，默认 `YES`。
- `LIBFOO_INSTALL_STAGING_OPTS`，指定安装到 staging 目录时的 make 选项。默认值为 `DESTDIR=$(STAGING_DIR) install`，适用于大多数 autotools 包。如需可覆盖。
- `LIBFOO_INSTALL_TARGET_OPTS`，指定安装到目标目录时的 make 选项。默认值为 `DESTDIR=$(TARGET_DIR) install`，适用于大多数 autotools 包。如需可覆盖。

对于 autotools 基础设施，构建和安装包所需的所有步骤都已定义，且对大多数 autotools 包都适用。但如有需要，仍可自定义任意步骤：

- 可添加后置操作钩子（extract、patch、configure、build 或 install 之后）。详见[各构建阶段可用钩子](https://buildroot.org/downloads/manual/manual.html#hooks)。
- 可覆盖某个步骤。例如，即使使用 autotools 基础设施，若包的 `.mk` 文件自定义了 `LIBFOO_CONFIGURE_CMDS` 变量，则会用自定义内容替换默认 autotools 行为。但此方法仅限特殊场景，一般不建议使用。





## 18.8. 基于CMake的软件包基础设施

### 18.8.1. `cmake-package` 教程

首先，让我们通过一个例子，看看如何为基于CMake的软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_INSTALL_STAGING = YES
11: LIBFOO_INSTALL_TARGET = NO
12: LIBFOO_CONF_OPTS = -DBUILD_DEMOS=ON
13: LIBFOO_DEPENDENCIES = libglib2 host-pkgconf
14:
15: $(eval $(cmake-package))
```

第7行，声明了软件包的版本。

第8和9行，声明了tarball（建议使用xz压缩包）的名称以及在Web上的下载地址。Buildroot会自动从该地址下载tarball。

第10行，告诉Buildroot将该软件包安装到staging目录。staging目录位于 `output/staging/`，是所有软件包（包括开发文件等）被安装的目录。默认情况下，软件包不会被安装到staging目录，因为通常只有库（library）才需要安装到staging目录：它们的开发文件用于编译依赖它们的其他库或应用程序。默认情况下，当启用staging安装时，软件包会通过 `make install` 命令安装到该位置。

第11行，告诉Buildroot不要将该软件包安装到target目录。该目录包含将来在目标设备上运行的根文件系统内容。对于纯静态库来说，没有必要安装到target目录，因为它们在运行时不会被使用。默认情况下，target安装是启用的；将该变量设置为NO几乎不需要。默认情况下，软件包会通过 `make install` 命令安装到该位置。

第12行，告诉Buildroot在配置软件包时传递自定义的CMake选项。

第13行，声明了依赖项，这样它们会在本软件包构建前被先行构建。

最后，第15行，调用 `cmake-package` 宏，生成实际允许软件包被构建的所有Makefile规则。

### 18.8.2. `cmake-package` 参考

CMake软件包基础设施的主要宏是 `cmake-package`。它与 `generic-package` 宏类似。也可以通过 `host-cmake-package` 宏支持目标（target）和主机（host）软件包。

与通用基础设施类似，CMake基础设施通过在调用 `cmake-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在CMake基础设施中同样适用。

此外，还可以定义一些CMake基础设施特有的变量。它们中的许多只在非常特定的情况下有用，典型的软件包通常只会用到其中的少数几个。

- `LIBFOO_SUBDIR` 可以包含包内包含主CMakeLists.txt文件的子目录名称。如果主CMakeLists.txt文件不在tarball解压后的根目录下，这会很有用。如果未指定 `HOST_LIBFOO_SUBDIR`，则默认为 `LIBFOO_SUBDIR`。
- `LIBFOO_CMAKE_BACKEND` 指定要使用的cmake后端，可以是 `make`（使用GNU Makefiles生成器，默认）或 `ninja`（使用Ninja生成器）。
- `LIBFOO_CONF_ENV`，用于指定传递给CMake的额外环境变量。默认值为空。
- `LIBFOO_CONF_OPTS`，用于指定传递给CMake的额外配置选项。默认值为空。CMake基础设施会设置许多常用CMake选项，因此通常不需要在包的 `*.mk` 文件中设置，除非需要覆盖它们：
  - `CMAKE_BUILD_TYPE` 由 `BR2_ENABLE_RUNTIME_DEBUG` 控制；
  - `CMAKE_INSTALL_PREFIX`；
  - `BUILD_SHARED_LIBS` 由 `BR2_STATIC_LIBS` 控制；
  - `BUILD_DOC`、`BUILD_DOCS` 被禁用；
  - `BUILD_EXAMPLE`、`BUILD_EXAMPLES` 被禁用；
  - `BUILD_TEST`、`BUILD_TESTS`、`BUILD_TESTING` 被禁用。
- `LIBFOO_BUILD_ENV` 和 `LIBFOO_BUILD_OPTS`，用于指定在构建时传递给后端的额外环境变量或命令行选项。
- `LIBFOO_SUPPORTS_IN_SOURCE_BUILD = NO`，当软件包不能在源码树内构建而需要单独的构建目录时应设置此项。
- `LIBFOO_MAKE`，用于指定备用的 `make` 命令。当配置中启用了并行make（使用 `BR2_JLEVEL`）但由于某些原因需要为该包禁用此功能时，这通常很有用。默认值为 `$(MAKE)`。如果该包不支持并行构建，则应设置为 `LIBFOO_MAKE=$(MAKE1)`。
- `LIBFOO_MAKE_ENV`，用于指定在构建步骤中传递给make的额外环境变量。这些变量会在 `make` 命令前传递。默认值为空。
- `LIBFOO_MAKE_OPTS`，用于指定在构建步骤中传递给make的额外变量。这些变量会在 `make` 命令后传递。默认值为空。
- `LIBFOO_INSTALL_OPTS`，包含用于将软件包安装到host目录的make选项。默认值为 `install`，对大多数CMake包来说是正确的，但仍可覆盖。
- `LIBFOO_INSTALL_STAGING_OPTS`，包含用于将软件包安装到staging目录的make选项。默认值为 `DESTDIR=$(STAGING_DIR) install/fast`，对大多数CMake包来说是正确的，但仍可覆盖。
- `LIBFOO_INSTALL_TARGET_OPTS`，包含用于将软件包安装到target目录的make选项。默认值为 `DESTDIR=$(TARGET_DIR) install/fast`。对大多数CMake包来说是正确的，但如有需要仍可覆盖。

使用CMake基础设施，构建和安装软件包所需的所有步骤都已定义好，并且对于大多数基于CMake的软件包来说都能很好地工作。然而，在需要时，仍然可以自定义某个特定步骤的行为：

- 通过添加后操作钩子（在提取、打补丁、配置、构建或安装之后）。详见[第18.23节，“各构建步骤可用的钩子”](https://buildroot.org/downloads/manual/manual.html#hooks)。
- 通过重写某个步骤。例如，即使使用了CMake基础设施，如果包的 `.mk` 文件定义了自己的 `LIBFOO_CONFIGURE_CMDS` 变量，则会使用自定义的而不是默认的CMake命令。但这种方法应仅限于非常特殊的情况。一般情况下不要使用。

## 18.9. 基于Python的软件包基础设施

该基础设施适用于使用标准Python setuptools、pep517、flit或maturin机制作为构建系统的Python软件包，通常可以通过 `setup.py` 脚本或 `pyproject.toml` 文件识别。

### 18.9.1. `python-package` 教程

首先，让我们通过一个例子，看看如何为Python软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # python-foo
04: #
05: ################################################################################
06:
07: PYTHON_FOO_VERSION = 1.0
08: PYTHON_FOO_SOURCE = python-foo-$(PYTHON_FOO_VERSION).tar.xz
09: PYTHON_FOO_SITE = http://www.foosoftware.org/download
10: PYTHON_FOO_LICENSE = BSD-3-Clause
11: PYTHON_FOO_LICENSE_FILES = LICENSE
12: PYTHON_FOO_ENV = SOME_VAR=1
13: PYTHON_FOO_DEPENDENCIES = libmad
14: PYTHON_FOO_SETUP_TYPE = setuptools
15:
16: $(eval $(python-package))
```

第7行，声明了软件包的版本。

第8和9行，声明了tarball（建议使用xz压缩包）的名称以及在Web上的下载地址。Buildroot会自动从该地址下载tarball。

第10和11行，给出了该软件包的许可信息（第10行为许可证类型，第11行为包含许可证文本的文件）。

第12行，告诉Buildroot在配置软件包时传递自定义选项给Python的 `setup.py` 脚本。

第13行，声明了依赖项，这样它们会在本软件包构建前被先行构建。

第14行，声明了所使用的Python构建系统类型。本例中使用的是 `setuptools`。目前支持的有 `flit`、`hatch`、`pep517`、`poetry`、`setuptools`、`setuptools-rust` 和 `maturin`。

最后，第16行，调用 `python-package` 宏，生成实际允许软件包被构建的所有Makefile规则。





### 18.9.2. `python-package` 参考

作为政策，仅提供Python模块的软件包在Buildroot中应全部命名为 `python-<something>`。其他使用Python构建系统但不是Python模块的软件包可以自由命名（Buildroot中已有的例子有 `scons` 和 `supervisor`）。

Python软件包基础设施的主要宏是 `python-package`。它与 `generic-package` 宏类似。也可以通过 `host-python-package` 宏创建Python主机软件包。

与通用基础设施类似，Python基础设施通过在调用 `python-package` 或 `host-python-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在Python基础设施中同样适用。

注意：

- 不需要在包的 `PYTHON_FOO_DEPENDENCIES` 变量中添加 `python` 或 `host-python`，因为这些基本依赖会被Python软件包基础设施自动添加。
- 同样，对于基于setuptools的软件包，也不需要在 `PYTHON_FOO_DEPENDENCIES` 中添加 `host-python-setuptools`，因为Python基础设施会根据需要自动添加。

有一个Python基础设施特有的变量是必须的：

- `PYTHON_FOO_SETUP_TYPE`，用于定义该包所使用的Python构建系统。支持的七种类型为 `flit`、`hatch`、`pep517`、`poetry`、`setuptools`、`setuptools-rust` 和 `maturin`。如果不确定包使用哪种类型，请查看包源码中的 `setup.py` 或 `pyproject.toml` 文件，看看是否有从 `flit` 或 `setuptools` 模块导入内容。如果包使用 `pyproject.toml` 文件且没有任何build-system requires，并且有本地in-tree backend-path，则应使用 `pep517`。

此外，还可以根据包的需要选择性地定义一些Python基础设施特有的变量。它们中的许多只在非常特定的情况下有用，典型的软件包通常只会用到其中的少数几个，甚至一个都不用。

- `PYTHON_FOO_SUBDIR` 可以包含包内包含主 `setup.py` 或 `pyproject.toml` 文件的子目录名称。如果主 `setup.py` 或 `pyproject.toml` 文件不在tarball解压后的根目录下，这会很有用。如果未指定 `HOST_PYTHON_FOO_SUBDIR`，则默认为 `PYTHON_FOO_SUBDIR`。
- `PYTHON_FOO_ENV`，用于指定传递给Python `setup.py` 脚本（对于setuptools包）或 `support/scripts/pyinstaller.py` 脚本（对于flit/pep517包）的额外环境变量，适用于构建和安装步骤。注意，基础设施会自动传递一些标准变量，这些变量在 `PKG_PYTHON_SETUPTOOLS_ENV`（针对setuptools目标包）、`HOST_PKG_PYTHON_SETUPTOOLS_ENV`（针对setuptools主机包）、`PKG_PYTHON_PEP517_ENV`（针对flit/pep517目标包）和 `HOST_PKG_PYTHON_PEP517_ENV`（针对flit/pep517主机包）中定义。
- `PYTHON_FOO_BUILD_OPTS`，用于指定传递给Python `python -m build` 调用的额外选项。要向构建后端传递额外选项，请使用 `build` 模块的 `--config-setting=`（`-C`）参数。
- `PYTHON_FOO_INSTALL_TARGET_OPTS`、`PYTHON_FOO_INSTALL_STAGING_OPTS`、`HOST_PYTHON_FOO_INSTALL_OPTS`，用于指定在目标安装、staging安装或主机安装步骤中传递给Python `setup.py` 脚本（对于setuptools包）或 `support/scripts/pyinstaller.py`（对于flit/pep517包）的额外选项。

使用Python基础设施，构建和安装软件包所需的所有步骤都已定义好，并且对于大多数基于Python的软件包来说都能很好地工作。然而，在需要时，仍然可以自定义某个特定步骤的行为：

- 通过添加后操作钩子（在提取、打补丁、配置、构建或安装之后）。详见[第18.23节，“各构建步骤可用的钩子”](https://buildroot.org/downloads/manual/manual.html#hooks)。
- 通过重写某个步骤。例如，即使使用了Python基础设施，如果包的 `.mk` 文件定义了自己的 `PYTHON_FOO_BUILD_CMDS` 变量，则会使用自定义的而不是默认的Python命令。但这种方法应仅限于非常特殊的情况。一般情况下不要使用。

### 18.9.3. 从PyPI仓库生成 `python-package`

如果你想为Buildroot创建的Python包在PyPI上有发布，可以使用 `utils/scanpypi` 工具（位于 `utils/` 目录下）来自动化该过程。

你可以在[这里](https://pypi.python.org/)找到现有PyPI包的列表。

`scanpypi` 需要你的主机上已安装Python的 `setuptools` 包。

在buildroot目录根下，直接执行：

```
utils/scanpypi foo bar -o package
```

如果 `foo` 和 `bar` 存在于 [https://pypi.python.org](https://pypi.python.org/) 上，这将会在package文件夹下生成 `python-foo` 和 `python-bar` 两个包。

找到 `external python modules` 菜单并将你的包插入其中。请注意，菜单中的条目应按字母顺序排列。

请记住，你很可能需要手动检查包是否有任何错误，因为有些内容生成器无法自动判断（例如对python核心模块如BR2_PACKAGE_PYTHON_ZLIB的依赖）。另外请注意，许可证和许可证文件是自动猜测的，必须手动检查。你还需要手动将包添加到 `package/Config.in` 文件中。

如果你的Buildroot包不在官方Buildroot树中，而是在br2-external树中，请使用如下的 -o 参数：

```
utils/scanpypi foo bar -o other_package_dir
```

这将在 `other_package_directory` 下生成 `python-foo` 和 `python-bar` 包，而不是在 `package` 目录下。

选项 `-h` 会列出可用选项：

```
utils/scanpypi -h
```

### 18.9.4. `python-package` CFFI后端

C Foreign Function Interface for Python（CFFI，C语言外部函数接口）为从Python调用用C编写的已编译代码提供了一种方便可靠的方式，接口声明采用C语言。依赖该后端的Python包可以通过其 `setup.py` 文件的 `install_requires` 字段中出现 `cffi` 依赖来识别。

此类包应：

- 添加 `python-cffi` 作为运行时依赖，以便在目标设备上安装已编译的C库包装器。可通过在包的 `Config.in` 文件中添加 `select BR2_PACKAGE_PYTHON_CFFI # runtime` 实现。

```
config BR2_PACKAGE_PYTHON_FOO
        bool "python-foo"
        select BR2_PACKAGE_PYTHON_CFFI # runtime
```

- 添加 `host-python-cffi` 作为构建时依赖，以便交叉编译C包装器。可通过在 `PYTHON_FOO_DEPENDENCIES` 变量中添加 `host-python-cffi` 实现。

```
################################################################################
#
# python-foo
#
################################################################################

...

PYTHON_FOO_DEPENDENCIES = host-python-cffi

$(eval $(python-package))
```





## 18.10. 基于LuaRocks的软件包基础设施

### 18.10.1. `luarocks-package` 教程

首先，让我们通过一个例子，看看如何为基于LuaRocks的软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # lua-foo
04: #
05: ################################################################################
06:
07: LUA_FOO_VERSION = 1.0.2-1
08: LUA_FOO_NAME_UPSTREAM = foo
09: LUA_FOO_DEPENDENCIES = bar
10:
11: LUA_FOO_BUILD_OPTS += BAR_INCDIR=$(STAGING_DIR)/usr/include
12: LUA_FOO_BUILD_OPTS += BAR_LIBDIR=$(STAGING_DIR)/usr/lib
13: LUA_FOO_LICENSE = luaFoo license
14: LUA_FOO_LICENSE_FILES = $(LUA_FOO_SUBDIR)/COPYING
15:
16: $(eval $(luarocks-package))
```

第7行，声明了软件包的版本（与rockspec中一致，由上游版本和rockspec修订号用连字符“-”拼接而成）。

第8行，声明该包在LuaRocks上的名称为“foo”。在Buildroot中，Lua相关包的名称以“lua”开头，因此Buildroot名称与上游名称不同。`LUA_FOO_NAME_UPSTREAM` 用于关联这两个名称。

第9行，声明了对本地库的依赖项，这样它们会在本软件包构建前被先行构建。

第11-12行，告诉Buildroot在构建包时向LuaRocks传递自定义选项。

第13-14行，指定了该包的许可条款。

最后，第16行，调用 `luarocks-package` 宏，生成实际允许软件包被构建的所有Makefile规则。

大多数这些细节都可以从 `rock` 和 `rockspec` 文件中获取。因此，可以通过在Buildroot目录下运行 `luarocks buildroot foo lua-foo` 命令自动生成此文件和Config.in文件。该命令会运行LuaRocks的Buildroot插件，自动生成Buildroot包。生成结果仍需手动检查和可能的修改。

- 需要手动更新 `package/Config.in` 文件以包含生成的Config.in文件。

### 18.10.2. `luarocks-package` 参考

LuaRocks是一个用于Lua模块的部署和管理系统，支持多种 `build.type`：`builtin`、`make` 和 `cmake`。在Buildroot中，`luarocks-package` 基础设施仅支持 `builtin` 模式。使用 `make` 或 `cmake` 构建机制的LuaRocks包应分别使用Buildroot的 `generic-package` 和 `cmake-package` 基础设施进行打包。

LuaRocks软件包基础设施的主要宏是 `luarocks-package`：与 `generic-package` 类似，通过定义一系列变量提供包的元数据信息，然后调用 `luarocks-package` 宏。

与通用基础设施类似，LuaRocks基础设施通过在调用 `luarocks-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在LuaRocks基础设施中同样适用。

其中有两个变量由LuaRocks基础设施自动填充（用于 `download` 步骤）。如果你的包不托管在LuaRocks镜像 `$(BR2_LUAROCKS_MIRROR)` 上，可以覆盖它们：

- `LUA_FOO_SITE`，默认值为 `$(BR2_LUAROCKS_MIRROR)`
- `LUA_FOO_SOURCE`，默认值为 `$(lowercase LUA_FOO_NAME_UPSTREAM)-$(LUA_FOO_VERSION).src.rock`

还可以定义一些LuaRocks基础设施特有的变量，在特定情况下可被覆盖：

- `LUA_FOO_NAME_UPSTREAM`，默认值为 `lua-foo`，即Buildroot包名
- `LUA_FOO_ROCKSPEC`，默认值为 `$(lowercase LUA_FOO_NAME_UPSTREAM)-$(LUA_FOO_VERSION).rockspec`
- `LUA_FOO_SUBDIR`，默认值为 `$(LUA_FOO_NAME_UPSTREAM)-$(LUA_FOO_VERSION_WITHOUT_ROCKSPEC_REVISION)`
- `LUA_FOO_BUILD_OPTS`，包含传递给 `luarocks build` 调用的额外构建选项。

## 18.11. 基于Perl/CPAN的软件包基础设施

### 18.11.1. `perl-package` 教程

首先，让我们通过一个例子，看看如何为Perl/CPAN包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # perl-foo-bar
04: #
05: ################################################################################
06:
07: PERL_FOO_BAR_VERSION = 0.02
08: PERL_FOO_BAR_SOURCE = Foo-Bar-$(PERL_FOO_BAR_VERSION).tar.gz
09: PERL_FOO_BAR_SITE = $(BR2_CPAN_MIRROR)/authors/id/M/MO/MONGER
10: PERL_FOO_BAR_DEPENDENCIES = perl-strictures
11: PERL_FOO_BAR_LICENSE = Artistic or GPL-1.0+
12: PERL_FOO_BAR_LICENSE_FILES = LICENSE
13: PERL_FOO_BAR_DISTNAME = Foo-Bar
14:
15: $(eval $(perl-package))
```

第7行，声明了软件包的版本。

第8和9行，声明了tarball的名称以及在CPAN服务器上的下载地址。Buildroot会自动从该地址下载tarball。

第10行，声明了依赖项，这样它们会在本软件包构建前被先行构建。

第11和12行，给出了该包的许可信息（第11行为许可证类型，第12行为包含许可证文本的文件）。

第13行，指定了分发名称，供 `utils/scancpan` 脚本（用于重新生成/升级这些包文件）使用。

最后，第15行，调用 `perl-package` 宏，生成实际允许软件包被构建的所有Makefile规则。

大多数数据可以从 https://metacpan.org/ 获取。因此，可以通过在Buildroot目录（或br2-external树）下运行 `utils/scancpan Foo-Bar` 脚本自动生成此文件和Config.in文件，并递归生成CPAN指定的所有依赖项。结果仍需手动编辑，特别需要检查以下内容：

- 如果Perl模块链接了由其他（非Perl）包提供的共享库，该依赖不会自动添加，需手动添加到 `PERL_FOO_BAR_DEPENDENCIES`。
- 需要手动更新 `package/Config.in` 文件以包含生成的Config.in文件。作为提示，`scancpan` 脚本会按字母顺序打印出所需的 `source "…"` 语句。

### 18.11.2. `perl-package` 参考

作为政策，提供Perl/CPAN模块的软件包在Buildroot中应全部命名为 `perl-<something>`。

该基础设施支持多种Perl构建系统：`ExtUtils-MakeMaker`（EUMM）、`Module-Build`（MB）和 `Module-Build-Tiny`。当包同时提供 `Makefile.PL` 和 `Build.PL` 时，默认优先使用 `Build.PL`。

Perl/CPAN软件包基础设施的主要宏是 `perl-package`。它与 `generic-package` 宏类似。也可以通过 `host-perl-package` 宏支持目标和主机软件包。

与通用基础设施类似，Perl/CPAN基础设施通过在调用 `perl-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在Perl/CPAN基础设施中同样适用。

注意，将 `PERL_FOO_INSTALL_STAGING` 设置为 `YES` 没有效果，除非定义了 `PERL_FOO_INSTALL_STAGING_CMDS` 变量。Perl基础设施不会定义这些命令，因为Perl模块通常不需要安装到 `staging` 目录。

还可以定义一些Perl/CPAN基础设施特有的变量。它们中的许多只在非常特定的情况下有用，典型的软件包通常只会用到其中的少数几个。

- `PERL_FOO_PREFER_INSTALLER`/`HOST_PERL_FOO_PREFER_INSTALLER`，指定首选的安装方式。可选值为 `EUMM`（基于 `Makefile.PL` 的ExtUtils-MakeMaker安装）和 `MB`（基于 `Build.PL` 的Module-Build安装）。仅当包同时提供两种安装方式时才使用此变量。
- `PERL_FOO_CONF_ENV`/`HOST_PERL_FOO_CONF_ENV`，用于指定传递给 `perl Makefile.PL` 或 `perl Build.PL` 的额外环境变量。默认值为空。
- `PERL_FOO_CONF_OPTS`/`HOST_PERL_FOO_CONF_OPTS`，用于指定传递给 `perl Makefile.PL` 或 `perl Build.PL` 的额外配置选项。默认值为空。
- `PERL_FOO_BUILD_OPTS`/`HOST_PERL_FOO_BUILD_OPTS`，用于指定在构建步骤中传递给 `make pure_all` 或 `perl Build build` 的额外选项。默认值为空。
- `PERL_FOO_INSTALL_TARGET_OPTS`，用于指定在安装步骤中传递给 `make pure_install` 或 `perl Build install` 的额外选项。默认值为空。
- `HOST_PERL_FOO_INSTALL_OPTS`，用于指定在安装步骤中传递给 `make pure_install` 或 `perl Build install` 的额外选项。默认值为空。



## 18.12. 虚拟软件包基础设施

在Buildroot中，虚拟软件包（virtual package）是指其功能由一个或多个包（称为“提供者”provider）实现的软件包。虚拟包管理是一种可扩展机制，允许用户选择在rootfs中使用的提供者。

例如，OpenGL ES是嵌入式系统上用于2D和3D图形的API。该API的实现因平台不同而异，如Allwinner Tech Sunxi和Texas Instruments OMAP35xx平台。因此，`libgles` 会是一个虚拟包，而 `sunxi-mali-utgard` 和 `ti-gfx` 则是其提供者。

### 18.12.1. `virtual-package` 教程

以下示例将说明如何添加一个新的虚拟包（something-virtual）及其一个提供者（some-provider）。

首先，创建虚拟包。

### 18.12.2. 虚拟包的 `Config.in` 文件

虚拟包 something-virtual 的 `Config.in` 文件应包含：

```
01: config BR2_PACKAGE_HAS_SOMETHING_VIRTUAL
02:     bool
03:
04: config BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL
05:     depends on BR2_PACKAGE_HAS_SOMETHING_VIRTUAL
06:     string
```

在该文件中，声明了两个选项，`BR2_PACKAGE_HAS_SOMETHING_VIRTUAL` 和 `BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL`，其值将被提供者使用。

### 18.12.3. 虚拟包的 `.mk` 文件

虚拟包的 `.mk` 文件只需调用 `virtual-package` 宏：

```
01: ################################################################################
02: #
03: # something-virtual
04: #
05: ################################################################################
06:
07: $(eval $(virtual-package))
```

同样支持目标和主机包，可使用 `host-virtual-package` 宏。

### 18.12.4. 提供者的 `Config.in` 文件

添加包作为提供者时，仅需修改其 `Config.in` 文件。

提供 something-virtual 功能的包 some-provider 的 `Config.in` 文件应包含：

```
01: config BR2_PACKAGE_SOME_PROVIDER
02:     bool "some-provider"
03:     select BR2_PACKAGE_HAS_SOMETHING_VIRTUAL
04:     help
05:       这里是对some-provider的说明注释。
06:
07:       http://foosoftware.org/some-provider/
08:
09: if BR2_PACKAGE_SOME_PROVIDER
10: config BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL
11:     default "some-provider"
12: endif
```

第3行选择了 `BR2_PACKAGE_HAS_SOMETHING_VIRTUAL`，第11行在被选中时将 `BR2_PACKAGE_PROVIDES_SOMETHING_VIRTUAL` 的值设为提供者名称。

### 18.12.5. 提供者的 `.mk` 文件

`.mk` 文件还应声明一个额外变量 `SOME_PROVIDER_PROVIDES`，包含其实现的所有虚拟包名称：

```
01: SOME_PROVIDER_PROVIDES = something-virtual
```

当然，不要忘记为该包添加正确的构建和运行时依赖！

### 18.12.6. 关于依赖虚拟包的说明

当添加一个需要某个虚拟包提供的 `FEATURE` 的包时，应使用 `depends on BR2_PACKAGE_HAS_FEATURE`，例如：

```
config BR2_PACKAGE_HAS_FEATURE
    bool

config BR2_PACKAGE_FOO
    bool "foo"
    depends on BR2_PACKAGE_HAS_FEATURE
```

### 18.12.7. 关于依赖特定提供者的说明

如果你的包确实需要特定的提供者，则必须让你的包 `depends on` 该提供者；不能用 `select` 选择提供者。

以有两个 `FEATURE` 提供者为例：

```
config BR2_PACKAGE_HAS_FEATURE
    bool

config BR2_PACKAGE_FOO
    bool "foo"
    select BR2_PACKAGE_HAS_FEATURE

config BR2_PACKAGE_BAR
    bool "bar"
    select BR2_PACKAGE_HAS_FEATURE
```

如果你要添加一个只需要 `foo` 提供的 `FEATURE` 的包，而不需要 `bar`，

如果用 `select BR2_PACKAGE_FOO`，用户仍然可以在menuconfig中选择 `BR2_PACKAGE_BAR`，这会导致配置不一致，即同一 `FEATURE` 的两个提供者同时被启用，一个是用户显式设置，另一个是你的 `select` 隐式设置。

因此，必须用 `depends on BR2_PACKAGE_FOO`，以避免隐式配置不一致。

## 18.13. 使用kconfig进行配置的软件包基础设施

许多软件包采用 `kconfig` 进行用户配置，如Linux内核、Busybox和Buildroot本身。`.config` 文件和 `menuconfig` 目标是kconfig被使用的典型特征。

Buildroot为使用kconfig进行配置的软件包提供了基础设施。该基础设施提供了必要的逻辑，将包的 `menuconfig` 目标暴露为Buildroot中的 `foo-menuconfig`，并正确处理配置文件的复制。

kconfig软件包基础设施的主要宏是 `kconfig-package`，与 `generic-package` 宏类似。

与通用基础设施类似，kconfig基础设施通过在调用 `kconfig-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在kconfig基础设施中同样适用。

要为Buildroot包使用 `kconfig-package` 基础设施，除了 `generic-package` 所需变量外，`.mk` 文件中至少要有：

```
FOO_KCONFIG_FILE = reference-to-source-configuration-file

$(eval $(kconfig-package))
```

该片段会创建如下make目标：

- `foo-menuconfig`，调用包的 `menuconfig` 目标
- `foo-update-config`，将配置复制回源配置文件（有fragment文件时不可用）
- `foo-update-defconfig`，将配置以只包含与默认值不同的选项的方式复制回源配置文件（有fragment文件时不可用）
- `foo-diff-config`，输出当前配置与Buildroot配置中该kconfig包定义的配置的差异，便于识别需要同步到配置片段的更改

并确保在合适时机将源配置文件复制到构建目录。

有两种方式指定要使用的配置文件：`FOO_KCONFIG_FILE`（如上例）或 `FOO_KCONFIG_DEFCONFIG`，必须提供其一：

- `FOO_KCONFIG_FILE` 指定要用于配置包的defconfig或完整配置文件的路径
- `FOO_KCONFIG_DEFCONFIG` 指定用于配置包的defconfig *make* 规则

此外，还可根据包需求设置如下可选变量：

- `FOO_KCONFIG_EDITORS`：支持的kconfig编辑器列表，默认*menuconfig*
- `FOO_KCONFIG_FRAGMENT_FILES`：要合并到主配置文件的配置片段文件列表
- `FOO_KCONFIG_OPTS`：调用kconfig编辑器时的额外选项，可能需包含*$(FOO_MAKE_OPTS)*，默认空
- `FOO_KCONFIG_FIXUP_CMDS`：复制配置文件或运行kconfig编辑器后需执行的shell命令列表，默认空
- `FOO_KCONFIG_DOTCONFIG`：`.config` 文件的路径（含文件名），相对于包源码树，默认`.config`
- `FOO_KCONFIG_DEPENDENCIES`：kconfig解析前需构建的包（多为host包）列表，默认空
- `FOO_KCONFIG_SUPPORTS_DEFCONFIG`：包的kconfig系统是否支持defconfig文件，默认*YES*



## 18.14. 基于rebar的软件包基础设施

### 18.14.1. `rebar-package` 教程

首先，让我们通过一个例子，看看如何为基于rebar的软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # erlang-foobar
04: #
05: ################################################################################
06:
07: ERLANG_FOOBAR_VERSION = 1.0
08: ERLANG_FOOBAR_SOURCE = erlang-foobar-$(ERLANG_FOOBAR_VERSION).tar.xz
09: ERLANG_FOOBAR_SITE = http://www.foosoftware.org/download
10: ERLANG_FOOBAR_DEPENDENCIES = host-libaaa libbbb
11:
12: $(eval $(rebar-package))
```

第7行，声明了软件包的版本。

第8和9行，声明了tarball（建议使用xz压缩包）的名称以及在Web上的下载地址。Buildroot会自动从该地址下载tarball。

第10行，声明了依赖项，这样它们会在本软件包构建前被先行构建。

最后，第12行，调用 `rebar-package` 宏，生成实际允许软件包被构建的所有Makefile规则。

### 18.14.2. `rebar-package` 参考

`rebar` 软件包基础设施的主要宏是 `rebar-package`。它与 `generic-package` 宏类似。也可以通过 `host-rebar-package` 宏支持主机包。

与通用基础设施类似，`rebar` 基础设施通过在调用 `rebar-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在 `rebar` 基础设施中同样适用。

还可以定义一些 `rebar` 基础设施特有的变量。它们中的许多只在非常特定的情况下有用，典型的软件包通常只会用到其中的少数几个。

- `ERLANG_FOOBAR_USE_AUTOCONF`，指定包在配置步骤中是否使用 *autoconf*。当该变量设为 `YES` 时，将使用 `autotools` 基础设施。

  **注意。** 你也可以使用 `autotools` 基础设施中的一些变量：`ERLANG_FOOBAR_CONF_ENV`、`ERLANG_FOOBAR_CONF_OPTS`、`ERLANG_FOOBAR_AUTORECONF`、`ERLANG_FOOBAR_AUTORECONF_ENV` 和 `ERLANG_FOOBAR_AUTORECONF_OPTS`。

- `ERLANG_FOOBAR_USE_BUNDLED_REBAR`，指定包是否自带 *rebar* 并且必须使用自带的。有效值为 `YES` 或 `NO`（默认）。

  **注意。** 如果包自带 *rebar* 工具，但可以使用Buildroot提供的通用版本，只需设为 `NO`（即不指定此变量）。只有在必须使用包自带 *rebar* 工具时才设置。

- `ERLANG_FOOBAR_REBAR_ENV`，用于指定传递给 *rebar* 工具的额外环境变量。

- `ERLANG_FOOBAR_KEEP_DEPENDENCIES`，指定是否保留rebar.config文件中描述的依赖项。有效值为 `YES` 或 `NO`（默认）。除非设为 `YES`，否则rebar基础设施会在post-patch钩子中移除这些依赖，以确保rebar不会下载或编译它们。

使用rebar基础设施，构建和安装软件包所需的所有步骤都已定义好，并且对于大多数基于rebar的软件包来说都能很好地工作。然而，在需要时，仍然可以自定义某个特定步骤的行为：

- 通过添加后操作钩子（在提取、打补丁、配置、构建或安装之后）。详见[第18.23节，“各构建步骤可用的钩子”](https://buildroot.org/downloads/manual/manual.html#hooks)。
- 通过重写某个步骤。例如，即使使用了rebar基础设施，如果包的 `.mk` 文件定义了自己的 `ERLANG_FOOBAR_BUILD_CMDS` 变量，则会使用自定义的而不是默认的rebar命令。但这种方法应仅限于非常特殊的情况。一般情况下不要使用。

## 18.15. 基于Waf的软件包基础设施

### 18.15.1. `waf-package` 教程

首先，让我们通过一个例子，看看如何为基于Waf的软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_CONF_OPTS = --enable-bar --disable-baz
11: LIBFOO_DEPENDENCIES = bar
12:
13: $(eval $(waf-package))
```

第7行，声明了软件包的版本。

第8和9行，声明了tarball（建议使用xz压缩包）的名称以及在Web上的下载地址。Buildroot会自动从该地址下载tarball。

第10行，告诉Buildroot为libfoo启用哪些选项。

第11行，声明了libfoo的依赖项。

最后，第13行，调用 `waf-package` 宏，生成实际允许软件包被构建的所有Makefile规则。

### 18.15.2. `waf-package` 参考

Waf软件包基础设施的主要宏是 `waf-package`。它与 `generic-package` 宏类似。

与通用基础设施类似，Waf基础设施通过在调用 `waf-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在Waf基础设施中同样适用。

还可以定义一些Waf基础设施特有的变量：

- `LIBFOO_SUBDIR` 可以包含包内包含主wscript文件的子目录名称。如果主wscript文件不在tarball解压后的根目录下，这会很有用。如果未指定 `HOST_LIBFOO_SUBDIR`，则默认为 `LIBFOO_SUBDIR`。
- `LIBFOO_NEEDS_EXTERNAL_WAF` 可设为 `YES` 或 `NO`，用于指定Buildroot是否使用自带的waf可执行文件。若设为 `NO`（默认），Buildroot将使用包源码树中的waf；若设为 `YES`，Buildroot会下载并安装waf作为host工具并用于构建包。
- `LIBFOO_WAF_OPTS`，用于指定在包构建过程的每一步（配置、构建、安装）传递给waf脚本的额外选项，默认空。
- `LIBFOO_CONF_OPTS`，用于指定配置步骤传递给waf脚本的额外选项，默认空。
- `LIBFOO_BUILD_OPTS`，用于指定构建步骤传递给waf脚本的额外选项，默认空。
- `LIBFOO_INSTALL_STAGING_OPTS`，用于指定staging安装步骤传递给waf脚本的额外选项，默认空。
- `LIBFOO_INSTALL_TARGET_OPTS`，用于指定target安装步骤传递给waf脚本的额外选项，默认空。



## 18.16. 基于Meson的软件包基础设施

### 18.16.1. `meson-package` 教程

[Meson](http://mesonbuild.com/) 是一个开源构建系统，旨在极快且尽可能用户友好。它使用 [Ninja](https://ninja-build.org/) 作为实际构建操作的辅助工具。

下面通过一个例子，看看如何为基于Meson的软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.0
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.gz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-3.0+
11: FOO_LICENSE_FILES = COPYING
12: FOO_INSTALL_STAGING = YES
13:
14: FOO_DEPENDENCIES = host-pkgconf bar
15:
16: ifeq ($(BR2_PACKAGE_BAZ),y)
17: FOO_CONF_OPTS += -Dbaz=true
18: FOO_DEPENDENCIES += baz
19: else
20: FOO_CONF_OPTS += -Dbaz=false
21: endif
22:
23: $(eval $(meson-package))
```

Makefile从第7到11行定义了包声明的标准变量。

第23行，调用 `meson-package` 宏，生成实际允许软件包被构建的所有Makefile规则。

在示例中，`host-pkgconf` 和 `bar` 在第14行被声明为依赖项，因为 `foo` 的Meson构建文件使用 `pkg-config` 来确定包 `bar` 的编译标志和库。

注意，不需要在包的 `FOO_DEPENDENCIES` 变量中添加 `host-meson`，因为Meson基础设施会根据需要自动添加该基本依赖。

如果选择了“baz”包，则通过在第17行向 `FOO_CONF_OPTS` 添加 `-Dbaz=true` 来激活对“baz”特性的支持，并在 `FOO_DEPENDENCIES` 中添加“baz”。如果未选择，则在第20行显式禁用对“baz”的支持。

总之，添加新的基于meson的软件包时，可以直接复制该Makefile示例，然后将所有 `FOO` 替换为新包的大写名，并更新标准变量的值。

### 18.16.2. `meson-package` 参考

Meson软件包基础设施的主要宏是 `meson-package`。它与 `generic-package` 宏类似。也可以通过 `host-meson-package` 宏支持目标和主机包。

与通用基础设施类似，Meson基础设施通过在调用 `meson-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在Meson基础设施中同样适用。

还可以定义一些Meson基础设施特有的变量。它们中的许多只在非常特定的情况下有用，典型的软件包通常只会用到其中的少数几个。

- `FOO_SUBDIR` 可以包含包内包含主 meson.build 文件的子目录名称。如果主 meson.build 文件不在tarball解压后的根目录下，这会很有用。如果未指定 `HOST_FOO_SUBDIR`，则默认为 `FOO_SUBDIR`。
- `FOO_CONF_ENV`，用于指定配置步骤传递给 `meson` 的额外环境变量，默认空。
- `FOO_CONF_OPTS`，用于指定配置步骤传递给 `meson` 的额外选项，默认空。
- `FOO_CFLAGS`，用于指定添加到包专用 `cross-compile.conf` 文件 `c_args` 属性的编译器参数，默认值为 `TARGET_CFLAGS`。
- `FOO_CXXFLAGS`，用于指定添加到包专用 `cross-compile.conf` 文件 `cpp_args` 属性的编译器参数，默认值为 `TARGET_CXXFLAGS`。
- `FOO_LDFLAGS`，用于指定添加到包专用 `cross-compile.conf` 文件 `c_link_args` 和 `cpp_link_args` 属性的编译器参数，默认值为 `TARGET_LDFLAGS`。
- `FOO_MESON_EXTRA_BINARIES`，用于指定要添加到meson `cross-compilation.conf` 配置文件 `[binaries]` 部分的程序列表，格式为 `program-name='/path/to/program'`，默认空。Buildroot已为 `c`、`cpp`、`ar`、`strip` 和 `pkgconfig` 设置了正确的值。
- `FOO_MESON_EXTRA_PROPERTIES`，用于指定要添加到meson `cross-compilation.conf` 配置文件 `[properties]` 部分的属性列表，格式为 `property-name=<value>`，默认空。Buildroot已为 `needs_exe_wrapper`、`c_args`、`c_link_args`、`cpp_args`、`cpp_link_args`、`sys_root` 和 `pkg_config_libdir` 设置了值。
- `FOO_NINJA_ENV`，用于指定传递给ninja（meson的构建工具）的额外环境变量，默认空。
- `FOO_NINJA_OPTS`，用于指定要构建的目标列表，默认空（构建默认目标）。

## 18.17. 基于Cargo的软件包基础设施

Cargo是Rust编程语言的软件包管理器。它允许用户构建Rust程序或库，并自动下载和管理其依赖项，以确保可重复构建。Cargo包称为“crate”。

### 18.17.1. `cargo-package` 教程

Cargo包foo的 `Config.in` 文件应包含：

```
01: config BR2_PACKAGE_FOO
02:     bool "foo"
03:     depends on BR2_PACKAGE_HOST_RUSTC_TARGET_ARCH_SUPPORTS
04:     select BR2_PACKAGE_HOST_RUSTC
05:     help
06:       这里是对foo的说明注释。
07:
08:       http://foosoftware.org/foo/
```

该包的 `.mk` 文件应包含：

```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.0
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.gz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-3.0+
11: FOO_LICENSE_FILES = COPYING
12:
13: $(eval $(cargo-package))
```

Makefile从第7到11行定义了包声明的标准变量。

第13行，基于 `cargo-package` 基础设施。Cargo会被该基础设施自动调用以构建和安装包。

仍可自定义构建命令或安装命令（即定义 FOO_BUILD_CMDS 和 FOO_INSTALL_TARGET_CMDS），这些会替换cargo基础设施的默认命令。

### 18.17.2. `cargo-package` 参考

Cargo软件包基础设施的主要宏为 `cargo-package`（目标包）和 `host-cargo-package`（主机包）。

与通用基础设施类似，Cargo基础设施通过在调用 `cargo-package` 或 `host-cargo-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在Cargo基础设施中同样适用。

还可以定义一些Cargo基础设施特有的变量。它们中的许多只在非常特定的情况下有用，典型的软件包通常只会用到其中的少数几个。

- `FOO_SUBDIR` 可以包含包内包含Cargo.toml文件的子目录名称。如果Cargo.toml文件不在tarball解压后的根目录下，这会很有用。如果未指定 `HOST_FOO_SUBDIR`，则默认为 `FOO_SUBDIR`。
- `FOO_CARGO_ENV` 可用于在cargo调用时传递额外的环境变量，构建和安装时均适用。
- `FOO_CARGO_BUILD_OPTS` 可用于在构建时向cargo传递额外选项。
- `FOO_CARGO_INSTALL_OPTS` 可用于在安装时向cargo传递额外选项。

crate可以依赖于其Cargo.toml文件中列出的其他库（来自crates.io或git仓库）。Buildroot会自动在使用 `cargo-package` 基础设施的软件包的下载步骤中下载这些依赖项。这些依赖项会与包源码一起保存在Buildroot的 `DL_DIR` 缓存tarball中，因此包tarball的哈希不仅覆盖包本身的源码，也覆盖依赖项源码。这样，依赖项的任何更改都会被哈希检查发现。此外，该机制允许完全离线构建，因为cargo在构建时不会下载任何内容。该机制称为依赖项的vendor化（vendoring）。





## 18.18. 基于Go的软件包基础设施

该基础设施适用于使用标准构建系统和自带依赖的Go包。

### 18.18.1. `golang-package` 教程

首先，让我们通过一个例子，看看如何为Go包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.0
08: FOO_SITE = $(call github,bar,foo,$(FOO_VERSION))
09: FOO_LICENSE = BSD-3-Clause
10: FOO_LICENSE_FILES = LICENSE
11:
12: $(eval $(golang-package))
```

第7行，声明了软件包的版本。

第8行，声明了包的上游位置，这里从Github获取，因为大量Go包托管在Github上。

第9和10行，给出了该包的许可信息。

最后，第12行，调用 `golang-package` 宏，生成实际允许软件包被构建的所有Makefile规则。

### 18.18.2. `golang-package` 参考

在 `Config.in` 文件中，使用 `golang-package` 基础设施的软件包应依赖 `BR2_PACKAGE_HOST_GO_TARGET_ARCH_SUPPORTS`，因为Buildroot会自动为这些包添加对 `host-go` 的依赖。如果你的包需要CGO支持，必须添加对 `BR2_PACKAGE_HOST_GO_TARGET_CGO_LINKING_SUPPORTS` 的依赖；对于主机包，添加对 `BR2_PACKAGE_HOST_GO_HOST_CGO_LINKING_SUPPORTS` 的依赖。

Go软件包基础设施的主要宏是 `golang-package`，它与 `generic-package` 宏类似。也可以通过 `host-golang-package` 宏支持主机包。主机包应依赖 `BR2_PACKAGE_HOST_GO_HOST_ARCH_SUPPORTS`。

与通用基础设施类似，Go基础设施通过在调用 `golang-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在Go基础设施中同样适用。

注意，不需要在包的 `FOO_DEPENDENCIES` 变量中添加 `host-go`，因为Go基础设施会根据需要自动添加该基本依赖。

还可以根据包的需要选择性地定义一些Go基础设施特有的变量。它们中的许多只在非常特定的情况下有用，典型的软件包通常只会用到其中的少数几个，甚至一个都不用。

- 包必须在 `FOO_GOMOD` 变量中指定其Go模块名。如果未指定，默认值为 `URL-domain/1st-part-of-URL/2nd-part-of-URL`，例如对于 `FOO_SITE = $(call github,bar,foo,$(FOO_VERSION))`，`FOO_GOMOD` 默认为 `github.com/bar/foo`。如果包源码树中没有go.mod文件，Go基础设施会自动生成一个最小的go.mod文件。
- `FOO_LDFLAGS`、`FOO_EXTLDFLAGS` 和 `FOO_TAGS` 可分别用于传递go的 `LDFLAGS`（通过 `-ldflags` 命令行参数）、外部链接器标志 `EXTLDFLAGS`（通过 `-extldflags` 命令行参数）或 `TAGS` 给 `go` 构建命令。
- `FOO_BUILD_TARGETS` 可用于指定应构建的目标列表。如果未指定，默认为 `.`。有两种情况：
  - `FOO_BUILD_TARGETS` 为 `.`，假定只生成一个二进制文件，默认以包名命名。若不合适，可用 `FOO_BIN_NAME` 覆盖。
  - `FOO_BUILD_TARGETS` 非 `.`，则遍历每个目标并生成对应的二进制文件，文件名为目标的非目录部分。例如 `FOO_BUILD_TARGETS = cmd/docker cmd/dockerd`，则生成 `docker` 和 `dockerd`。
- `FOO_INSTALL_BINS` 可用于指定应安装到目标 `/usr/bin` 的二进制文件列表。如果未指定，默认为包名的小写形式。

使用Go基础设施，构建和安装包所需的所有步骤都已定义好，并且对于大多数基于Go的软件包来说都能很好地工作。然而，在需要时，仍然可以自定义某个特定步骤的行为：

- 通过添加后操作钩子（在提取、打补丁、配置、构建或安装之后）。详见[第18.23节，“各构建步骤可用的钩子”](https://buildroot.org/downloads/manual/manual.html#hooks)。
- 通过重写某个步骤。例如，即使使用了Go基础设施，如果包的 `.mk` 文件定义了自己的 `FOO_BUILD_CMDS` 变量，则会使用自定义的而不是默认的Go命令。但这种方法应仅限于非常特殊的情况。一般情况下不要使用。

Go包可以依赖于其go.mod文件中列出的其他Go模块。Buildroot会自动在使用 `golang-package` 基础设施的软件包的下载步骤中下载这些依赖项。这些依赖项会与包源码一起保存在Buildroot的 `DL_DIR` 缓存tarball中，因此包tarball的哈希也包含这些依赖。

该机制确保依赖项的任何更改都会被检测到，并允许完全离线构建。

## 18.19. 基于QMake的软件包基础设施

### 18.19.1. `qmake-package` 教程

首先，让我们通过一个例子，看看如何为基于QMake的软件包编写 `.mk` 文件：

```
01: ################################################################################
02: #
03: # libfoo
04: #
05: ################################################################################
06:
07: LIBFOO_VERSION = 1.0
08: LIBFOO_SOURCE = libfoo-$(LIBFOO_VERSION).tar.gz
09: LIBFOO_SITE = http://www.foosoftware.org/download
10: LIBFOO_CONF_OPTS = QT_CONFIG+=bar QT_CONFIG-=baz
11: LIBFOO_DEPENDENCIES = bar
12:
13: $(eval $(qmake-package))
```

第7行，声明了软件包的版本。

第8和9行，声明了tarball（建议使用xz压缩包）的名称以及在Web上的下载地址。Buildroot会自动从该地址下载tarball。

第10行，告诉Buildroot为libfoo启用哪些选项。

第11行，声明了libfoo的依赖项。

最后，第13行，调用 `qmake-package` 宏，生成实际允许软件包被构建的所有Makefile规则。



### 18.19.2. `qmake-package` 参考

QMake软件包基础设施的主要宏是 `qmake-package`。它与 `generic-package` 宏类似。

与通用基础设施类似，QMake基础设施通过在调用 `qmake-package` 宏前定义一系列变量来工作。

所有在[通用软件包基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)中存在的软件包元数据信息变量，在QMake基础设施中同样适用。

还可以定义一些QMake基础设施特有的变量：

- `LIBFOO_CONF_ENV`，用于指定配置步骤传递给 `qmake` 脚本的额外环境变量，默认空。
- `LIBFOO_CONF_OPTS`，用于指定配置步骤传递给 `qmake` 脚本的额外选项，默认空。
- `LIBFOO_MAKE_ENV`，用于构建和安装步骤传递给 `make` 命令的额外环境变量，默认空。
- `LIBFOO_MAKE_OPTS`，用于构建步骤传递给 `make` 命令的额外目标，默认空。
- `LIBFOO_INSTALL_STAGING_OPTS`，用于staging安装步骤传递给 `make` 命令的额外目标，默认 `install`。
- `LIBFOO_INSTALL_TARGET_OPTS`，用于target安装步骤传递给 `make` 命令的额外目标，默认 `install`。
- `LIBFOO_SYNC_QT_HEADERS`，在qmake前运行syncqt.pl。有些包需要这样做以确保include目录正确填充。

## 18.20. 构建内核模块的软件包基础设施

Buildroot提供了辅助基础设施，便于编写构建和安装Linux内核模块的软件包。有些包只包含内核模块，另一些包还包含程序和库。Buildroot的辅助基础设施支持这两种情况。

### 18.20.1. `kernel-module` 教程

先看一个只构建内核模块（不包含其他组件）的简单包示例：

```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.2.3
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.xz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-2.0
11: FOO_LICENSE_FILES = COPYING
12:
13: $(eval $(kernel-module))
14: $(eval $(generic-package))
```

第7-11行定义了版本、归档名、远程URI、许可信息等元数据。

第13行，调用 `kernel-module` 辅助基础设施，生成构建内核模块的Makefile规则和变量。

第14行，调用 [`generic-package` 基础设施](https://buildroot.org/downloads/manual/manual.html#generic-package-tutorial)。

对 `linux` 的依赖会自动添加，无需在 `FOO_DEPENDENCIES` 中指定。

与其他包基础设施不同，这里需显式调用第二个基础设施。这允许包既构建内核模块，也可用其他包基础设施构建用户态组件（库、可执行文件等）。单独使用 `kernel-module` 不够，必须再用一个 `*-package` 基础设施。

再看一个更复杂的例子：

```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: FOO_VERSION = 1.2.3
08: FOO_SOURCE = foo-$(FOO_VERSION).tar.xz
09: FOO_SITE = http://www.foosoftware.org/download
10: FOO_LICENSE = GPL-2.0
11: FOO_LICENSE_FILES = COPYING
12:
13: FOO_MODULE_SUBDIRS = driver/base
14: FOO_MODULE_MAKE_OPTS = KVERSION=$(LINUX_VERSION_PROBED)
15:
16: ifeq ($(BR2_PACKAGE_LIBBAR),y)
17: FOO_DEPENDENCIES += libbar
18: FOO_CONF_OPTS += --enable-bar
19: FOO_MODULE_SUBDIRS += driver/bar
20: else
21: FOO_CONF_OPTS += --disable-bar
22: endif
23:
24: $(eval $(kernel-module))
26: $(eval $(autotools-package))
```

这里是一个基于autotools的包，同时构建 `driver/base` 子目录下的内核模块，如果启用libbar，还构建 `driver/bar` 下的模块，并通过 `KVERSION` 变量传递内核版本。

### 18.20.2. `kernel-module` 参考

内核模块基础设施的主要宏是 `kernel-module`。与其他包基础设施不同，它不是独立的，必须在其后调用其他 `*-package` 宏。

`kernel-module` 宏定义了post-build和post-target-install钩子以构建内核模块。如果包的 `.mk` 需要访问已构建的内核模块，应在调用 `kernel-module` 后的post-build钩子中操作；如需访问已安装的内核模块，则应在post-install钩子中操作。示例：

```
$(eval $(kernel-module))

define FOO_DO_STUFF_WITH_KERNEL_MODULE
    # 这里对内核模块做一些操作...
endef
FOO_POST_BUILD_HOOKS += FOO_DO_STUFF_WITH_KERNEL_MODULE

$(eval $(generic-package))
```

最后，与其他包基础设施不同，没有 `host-kernel-module` 变体用于构建主机内核模块。

还可定义如下变量进一步配置内核模块的构建：

- `FOO_MODULE_SUBDIRS` 可设为一个或多个子目录（相对于包源码顶层目录），指定内核模块源码位置。若为空或未设，默认源码在包源码树顶层。
- `FOO_MODULE_MAKE_OPTS` 可设为传递给Linux构建系统的额外变量定义。

你还可以引用（但不能设置）如下变量：

- `LINUX_DIR`：Linux内核解压和构建路径
- `LINUX_VERSION`：用户配置的内核版本字符串
- `LINUX_VERSION_PROBED`：通过 `make -C $(LINUX_DIR) kernelrelease` 获取的实际内核版本
- `KERNEL_ARCH`：当前架构名称，如 `arm`、`mips` 等

## 18.21. 基于asciidoc文档的基础设施

你正在阅读的Buildroot手册完全采用 [AsciiDoc](http://asciidoc.org/) 标记语法编写。手册可渲染为多种格式：

- html
- split-html
- pdf
- epub
- text

虽然Buildroot只包含一个asciidoc文档，但也像包一样，提供了渲染asciidoc文档的基础设施。

同样，asciidoc基础设施也可用于 [br2-external树](https://buildroot.org/downloads/manual/manual.html#outside-br-custom)。这样，br2-external树的文档可与Buildroot文档风格一致。

### 18.21.1. `asciidoc-document` 教程

包基础设施以 `-package` 结尾，文档基础设施以 `-document` 结尾。因此，asciidoc基础设施名为 `asciidoc-document`。

下面是渲染简单asciidoc文档的例子：

```
01: ################################################################################
02: #
03: # foo-document
04: #
05: ################################################################################
06:
07: FOO_SOURCES = $(sort $(wildcard $(FOO_DOCDIR)/*))
08: $(eval $(call asciidoc-document))
```

第7行，Makefile声明了文档的源文件。当前仅支持本地源文件，Buildroot不会尝试下载任何内容来渲染文档。通常如上即可。

第8行，调用 `asciidoc-document` 函数，生成渲染文档所需的所有Makefile代码。



### 18.21.2. `asciidoc-document` 参考

可以在 `.mk` 文件中设置如下变量（假设文档名为 `foo`），用于提供元数据信息：

- `FOO_SOURCES`（必需）：定义文档的源文件。
- `FOO_RESOURCES`（可选）：可包含一个或多个资源目录（如CSS或图片）的路径，空格分隔。默认值为空。
- `FOO_DEPENDENCIES`（可选）：构建该文档前必须构建的软件包列表（多为host包）。
- `FOO_TOC_DEPTH`、`FOO_TOC_DEPTH_<FMT>`（可选）：文档目录的深度，可针对指定格式 `<FMT>`（见上文渲染格式列表，全部大写，连字符用下划线替换）单独设置。默认值为 `1`。

还可以设置额外的钩子（详见[第18.23节，“各构建步骤可用的钩子”](https://buildroot.org/downloads/manual/manual.html#hooks)）：

- `FOO_POST_RSYNC_HOOKS`：在Buildroot复制源文件后运行额外命令。例如可用于根据源码树信息生成手册部分内容。Buildroot自身用此钩子生成附录表格。
- `FOO_CHECK_DEPENDENCIES_HOOKS`：对生成文档所需组件进行额外测试。AsciiDoc支持调用过滤器（filter），即对AsciiDoc块进行解析和渲染的程序（如 [ditaa](http://ditaa.sourceforge.net/) 或 [aafigure](https://pythonhosted.org/aafigure/)）。
- `FOO_CHECK_DEPENDENCIES_<FMT>_HOOKS`：对指定格式 `<FMT>` 进行额外测试。

Buildroot会设置如下变量，可在上述定义中使用：

- `$(FOO_DOCDIR)`：类似于 `$(FOO_PKGDIR)`，包含 `foo.mk` 所在目录路径。可用于引用文档源文件，或在钩子中使用，尤其是post-rsync钩子需生成文档部分内容时。
- `$(@D)`：与传统包一样，包含文档被复制和构建的目录路径。

下面是一个使用了所有变量和钩子的完整示例：

```
01: ################################################################################
02: #
03: # foo-document
04: #
05: ################################################################################
06:
07: FOO_SOURCES = $(sort $(wildcard $(FOO_DOCDIR)/*))
08: FOO_RESOURCES = $(sort $(wildcard $(FOO_DOCDIR)/resources))
09:
10: FOO_TOC_DEPTH = 2
11: FOO_TOC_DEPTH_HTML = 1
12: FOO_TOC_DEPTH_SPLIT_HTML = 3
13:
14: define FOO_GEN_EXTRA_DOC
15:     /path/to/generate-script --outdir=$(@D)
16: endef
17: FOO_POST_RSYNC_HOOKS += FOO_GEN_EXTRA_DOC
18:
19: define FOO_CHECK_MY_PROG
20:     if ! which my-prog >/dev/null 2>&1; then \
21:         echo "You need my-prog to generate the foo document"; \
22:         exit 1; \
23:     fi
24: endef
25: FOO_CHECK_DEPENDENCIES_HOOKS += FOO_CHECK_MY_PROG
26:
27: define FOO_CHECK_MY_OTHER_PROG
28:     if ! which my-other-prog >/dev/null 2>&1; then \
29:         echo "You need my-other-prog to generate the foo document as PDF"; \
30:         exit 1; \
31:     fi
32: endef
33: FOO_CHECK_DEPENDENCIES_PDF_HOOKS += FOO_CHECK_MY_OTHER_PROG
34:
35: $(eval $(call asciidoc-document))
```

## 18.22. Linux内核包专用基础设施

Linux内核包可基于包钩子使用一些专用基础设施，用于构建Linux内核工具或扩展。

### 18.22.1. linux-kernel-tools

Buildroot提供了辅助基础设施，用于为目标系统构建Linux内核源码中的部分用户空间工具。由于这些工具的源码属于内核源码，因此有一个特殊包 `linux-tools`，复用目标系统运行的Linux内核源码。

以Linux工具 `foo` 为例。为新工具 `foo` 在现有 `package/linux-tools/Config.in` 中创建菜单项。该文件包含每个内核工具的选项描述，配置工具中会显示。大致如下：

```
01: config BR2_PACKAGE_LINUX_TOOLS_FOO
02:     bool "foo"
03:     select BR2_PACKAGE_LINUX_TOOLS
04:     help
05:       这里是对foo内核工具的说明注释。
06:
07:       http://foosoftware.org/foo/
```

选项名以 `BR2_PACKAGE_LINUX_TOOLS_` 为前缀，后接工具大写名（与包命名方式一致）。

**注意。** 与其他包不同，`linux-tools` 选项出现在 `linux` 内核菜单下的 `Linux Kernel Tools` 子菜单中，而不是 `Target packages` 主菜单。

然后为每个linux工具添加一个名为 `package/linux-tools/linux-tool-foo.mk.in` 的 `.mk.in` 文件，大致如下：

```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: LINUX_TOOLS += foo
08:
09: FOO_DEPENDENCIES = libbbb
10:
11: define FOO_BUILD_CMDS
12:     $(TARGET_MAKE_ENV) $(MAKE) -C $(LINUX_DIR)/tools foo
13: endef
14:
15: define FOO_INSTALL_STAGING_CMDS
16:     $(TARGET_MAKE_ENV) $(MAKE) -C $(LINUX_DIR)/tools \
17:             DESTDIR=$(STAGING_DIR) \
18:             foo_install
19: endef
20:
21: define FOO_INSTALL_TARGET_CMDS
22:     $(TARGET_MAKE_ENV) $(MAKE) -C $(LINUX_DIR)/tools \
23:             DESTDIR=$(TARGET_DIR) \
24:             foo_install
25: endef
```

第7行，将Linux工具 `foo` 注册到可用工具列表。

第9行，指定该工具依赖的包列表。仅当选择了 `foo` 工具时，这些依赖才会被添加到Linux包依赖列表。

其余Makefile（第11-25行）定义了Linux工具构建流程各步骤的操作，类似于[通用包](https://buildroot.org/downloads/manual/manual.html#generic-package-tutorial)。只有选择了 `foo` 工具时才会实际使用。仅支持 `_BUILD_CMDS`、`_INSTALL_STAGING_CMDS` 和 `_INSTALL_TARGET_CMDS` 命令。

**注意。** 不能调用 `$(eval $(generic-package))` 或其他包基础设施！Linux工具不是独立包，而是 `linux-tools` 包的一部分。

### 18.22.2. linux-kernel-extensions

有些包提供新特性，需要修改Linux内核源码树。这可能是以补丁形式应用到内核树，也可能是以新文件形式添加到源码树。Buildroot的Linux内核扩展基础设施提供了简单方案，在内核源码解压后、补丁应用前自动完成。例如Xenomai、RTAI实时扩展和 `fbtft`（一组树外LCD驱动）等。

以添加新内核扩展 `foo` 为例：

首先，创建提供该扩展的包 `foo`，这是一个标准包，负责下载源码、校验哈希、定义许可证信息及构建用户空间工具（如有）。

然后创建*Linux扩展*本体：在现有 `linux/Config.ext.in` 中添加菜单项。该文件包含每个内核扩展的选项描述，配置工具中会显示。大致如下：

```
01: config BR2_LINUX_KERNEL_EXT_FOO
02:     bool "foo"
03:     help
04:       这里是对foo内核扩展的说明注释。
05:
06:       http://foosoftware.org/foo/
```

然后为每个linux扩展添加一个名为 `linux/linux-ext-foo.mk` 的 `.mk` 文件，内容大致如下：

```
01: ################################################################################
02: #
03: # foo
04: #
05: ################################################################################
06:
07: LINUX_EXTENSIONS += foo
08:
09: define FOO_PREPARE_KERNEL
10:     $(FOO_DIR)/prepare-kernel-tree.sh --linux-dir=$(@D)
11: endef
```

第7行，将Linux扩展 `foo` 添加到可用扩展列表。

第9-11行，定义扩展对内核源码树的修改操作；具体内容由扩展决定，可用 `foo` 包定义的变量（如 `$(FOO_DIR)`、`$(FOO_VERSION)`）及所有Linux变量（如 `$(LINUX_VERSION)`、`$(LINUX_VERSION_PROBED)`、`$(KERNEL_ARCH)`）。详见[这些内核变量的定义](https://buildroot.org/downloads/manual/manual.html#kernel-variables)。



## 18.23. 各构建步骤可用的钩子（Hooks）

通用基础架构（generic infrastructure）（以及由其派生的 autotools 和 cmake 基础架构）允许软件包指定钩子。这些钩子定义了在现有步骤之后要执行的进一步操作。大多数钩子对于通用软件包来说并不真正有用，因为 `.mk` 文件已经可以完全控制软件包构建过程中每个步骤的操作。

可用的钩子点如下：

- `LIBFOO_PRE_DOWNLOAD_HOOKS`
- `LIBFOO_POST_DOWNLOAD_HOOKS`
- `LIBFOO_PRE_EXTRACT_HOOKS`
- `LIBFOO_POST_EXTRACT_HOOKS`
- `LIBFOO_PRE_RSYNC_HOOKS`
- `LIBFOO_POST_RSYNC_HOOKS`
- `LIBFOO_PRE_PATCH_HOOKS`
- `LIBFOO_POST_PATCH_HOOKS`
- `LIBFOO_PRE_CONFIGURE_HOOKS`
- `LIBFOO_POST_CONFIGURE_HOOKS`
- `LIBFOO_PRE_BUILD_HOOKS`
- `LIBFOO_POST_BUILD_HOOKS`
- `LIBFOO_PRE_INSTALL_HOOKS`（仅限主机包）
- `LIBFOO_POST_INSTALL_HOOKS`（仅限主机包）
- `LIBFOO_PRE_INSTALL_STAGING_HOOKS`（仅限目标包）
- `LIBFOO_POST_INSTALL_STAGING_HOOKS`（仅限目标包）
- `LIBFOO_PRE_INSTALL_TARGET_HOOKS`（仅限目标包）
- `LIBFOO_POST_INSTALL_TARGET_HOOKS`（仅限目标包）
- `LIBFOO_PRE_INSTALL_IMAGES_HOOKS`
- `LIBFOO_POST_INSTALL_IMAGES_HOOKS`
- `LIBFOO_PRE_LEGAL_INFO_HOOKS`
- `LIBFOO_POST_LEGAL_INFO_HOOKS`
- `LIBFOO_TARGET_FINALIZE_HOOKS`

这些变量是*变量名的列表*，包含在该钩子点要执行的操作。这允许在给定的钩子点注册多个钩子。示例如下：

```
define LIBFOO_POST_PATCH_FIXUP
        action1
        action2
endef

LIBFOO_POST_PATCH_HOOKS += LIBFOO_POST_PATCH_FIXUP
```

### 18.23.1. 使用 `POST_RSYNC` 钩子

`POST_RSYNC` 钩子仅对使用本地源的包运行，无论是通过 `local` 站点方法还是 `OVERRIDE_SRCDIR` 机制。在这种情况下，包源代码会通过 `rsync` 从本地位置复制到 buildroot 构建目录。`rsync` 命令并不会复制源目录中的所有文件。例如，属于版本控制系统的文件，如 `.git`、`.hg` 等目录不会被复制。对于大多数包来说，这已经足够，但特定包可以通过 `POST_RSYNC` 钩子执行额外操作。

原则上，钩子中可以包含你想要的任何命令。一个具体的用例是有意通过 `rsync` 复制版本控制目录。你在钩子中使用的 `rsync` 命令可以使用如下变量：

- `$(SRCDIR)`：被覆盖的源目录路径
- `$(@D)`：构建目录路径

### 18.23.2. Target-finalize 钩子

包还可以在 `LIBFOO_TARGET_FINALIZE_HOOKS` 中注册钩子。这些钩子会在所有包构建完成后、生成文件系统镜像之前运行。它们很少被使用，你的包大概率不需要它们。

## 18.24. Gettext 集成与包的交互

许多支持国际化的包会使用 gettext（gettext）库。该库的依赖关系相当复杂，因此需要一些说明。

*glibc* C 库集成了完整的 *gettext* 实现，支持翻译。因此，*glibc* 内置了本地语言支持（Native Language Support，NLS）。

而 *uClibc* 和 *musl* C 库只提供了 gettext 功能的存根实现（stub implementation），这允许使用 gettext 函数编译库和程序，但不提供完整 gettext 实现的翻译能力。对于这类 C 库，如果需要真正的本地语言支持，可以通过 `gettext` 包的 `libintl`（libintl）库来提供。

因此，为了确保本地语言支持被正确处理，Buildroot 中可以使用 NLS 支持的包应当：

1. 当 `BR2_SYSTEM_ENABLE_NLS=y` 时确保启用 NLS 支持。对于 *autotools* 包会自动完成，因此只需对使用其他包基础架构的包进行处理。
2. 在包的 `<pkg>_DEPENDENCIES` 变量中无条件添加 `$(TARGET_NLS_DEPENDENCIES)`。该变量的值会被核心基础架构自动调整为相关包的列表。如果 NLS 支持被禁用，该变量为空；如果启用，则包含 `host-gettext`，以便主机上可用编译翻译文件所需的工具。此外，如果使用 *uClibc* 或 *musl*，该变量还会包含 `gettext`，以获得完整的 *gettext* 实现。
3. 如有需要，在链接参数中添加 `$(TARGET_NLS_LIBS)`，以便包能与 `libintl` 链接。对于 *autotools* 包通常不需要这样做，因为它们通常能自动检测是否需要链接 `libintl`。但使用其他构建系统的包或有问题的 autotools 包可能需要这样做。`$(TARGET_NLS_LIBS)` 应无条件添加到链接参数中，核心会根据配置自动将其设为空或定义为 `-lintl`。

无需对 `Config.in` 文件做任何更改以支持 NLS。

最后，某些包需要在目标系统上提供一些 gettext 工具，例如 `gettext` 程序本身（允许从命令行检索翻译字符串）。在这种情况下，包应当：

- 在其 `Config.in` 文件中使用 `select BR2_PACKAGE_GETTEXT`，并在上方注释说明这是仅运行时依赖。
- 不要在 `.mk` 文件的 `DEPENDENCIES` 变量中添加任何 `gettext` 依赖。

## 18.25. 技巧与提示

### 18.25.1. 包名、配置项名与 Makefile 变量的关系

在 Buildroot 中，以下三者之间存在一定的关系：

- *包名*，即包目录名（也是 `*.mk` 文件名）；
- 在 `Config.in` 文件中声明的配置项名；
- Makefile 变量前缀。

必须保持这些元素之间的一致性，规则如下：

- 包目录和 `*.mk` 文件名即为*包名*本身（如：`package/foo-bar_boo/foo-bar_boo.mk`）；
- *make* 目标名即为包名本身（如：`foo-bar_boo`）；
- 配置项名为大写包名，将 `.` 和 `-` 替换为 `_`，并加前缀 `BR2_PACKAGE_`（如：`BR2_PACKAGE_FOO_BAR_BOO`）；
- `*.mk` 文件变量前缀为大写包名，将 `.` 和 `-` 替换为 `_`（如：`FOO_BAR_BOO_VERSION`）。

### 18.25.2. 如何检查代码风格

Buildroot 在 `utils/check-package` 提供了一个脚本，用于检查新建或修改的文件的代码风格。它不是完整的语言校验器，但能捕捉到许多常见错误。建议在你创建或修改文件后、提交补丁前运行该脚本。

该脚本可用于包、文件系统 Makefile、Config.in 文件等。它不会检查定义包基础架构的文件及其他包含类似通用代码的文件。

使用方法如下，指定你新建或修改的文件：

```
$ ./utils/check-package package/new-package/*
```

如果你已将 `utils` 目录加入 PATH，也可以这样运行：

```
$ cd package/new-package/
$ check-package *
```

该工具也可用于 br2-external 里的包：

```
$ check-package -b /path/to/br2-ext-tree/package/my-package/*
```

`check-package` 脚本需要你安装 `shellcheck` 以及 Python PyPi 包 `flake8` 和 `python-magic`。Buildroot 代码库当前针对 ShellCheck 0.7.1 版本进行测试。如果你使用不同版本的 ShellCheck，可能会看到额外的、未修复的警告。

如果你有 Docker 或 Podman，可以无需安装依赖直接运行 `check-package`：

```
$ ./utils/docker-run ./utils/check-package
```



### 18.25.3. 如何测试你的软件包

在你添加新软件包后，重要的是要在各种条件下对其进行测试：它能否为所有架构编译？能否与不同的 C 库一起编译？是否需要线程、NPTL？等等。

Buildroot 运行着 [autobuilders](http://autobuild.buildroot.org/)，这些自动构建器会持续测试随机配置。但它们只会构建 git 树的 `master` 分支，而你新添加的软件包还未合并到主线。

Buildroot 在 `utils/test-pkg` 提供了一个脚本，使用与 autobuilders 相同的基础配置，这样你可以在相同条件下测试你的软件包。

首先，创建一个配置片段（config snippet），包含启用你的软件包所需的所有选项，但不包含任何架构或工具链选项。例如，下面创建一个只启用 `libcurl`（libcurl），不带任何 TLS 后端的配置片段：

```
$ cat libcurl.config
BR2_PACKAGE_LIBCURL=y
```

如果你的软件包需要更多配置选项，可以将它们添加到配置片段。例如，下面是如何测试带有 `openssl`（openssl）作为 TLS 后端并启用 `curl` 程序的 `libcurl`：

```
$ cat libcurl.config
BR2_PACKAGE_LIBCURL=y
BR2_PACKAGE_LIBCURL_CURL=y
BR2_PACKAGE_OPENSSL=y
```

然后运行 `test-pkg` 脚本，指定要使用的配置片段和要测试的软件包：

```
$ ./utils/test-pkg -c libcurl.config -p libcurl
```

默认情况下，`test-pkg` 会将你的软件包与 autobuilders 使用的工具链子集进行构建测试，这个子集由 Buildroot 开发者选定，最具代表性。如果你想测试所有工具链，可以加上 `-a` 选项。无论哪种情况，内部工具链都被排除，因为它们构建时间太长。

输出会列出所有被测试的工具链及对应结果（以下为示例，结果为假）：

```
$ ./utils/test-pkg -c libcurl.config -p libcurl
                armv5-ctng-linux-gnueabi [ 1/11]: OK
              armv7-ctng-linux-gnueabihf [ 2/11]: OK
                        br-aarch64-glibc [ 3/11]: SKIPPED
                           br-arcle-hs38 [ 4/11]: SKIPPED
                            br-arm-basic [ 5/11]: FAILED
                  br-arm-cortex-a9-glibc [ 6/11]: OK
                   br-arm-cortex-a9-musl [ 7/11]: FAILED
                   br-arm-cortex-m4-full [ 8/11]: OK
                             br-arm-full [ 9/11]: OK
                    br-arm-full-nothread [10/11]: FAILED
                      br-arm-full-static [11/11]: OK
11 builds, 2 skipped, 2 build failed, 1 legal-info failed
```

结果含义如下：

- `OK`：构建成功。
- `SKIPPED`：配置片段中列出的一个或多个选项未出现在最终配置中。这通常是因为选项有依赖项未被工具链满足，例如某个包 `depends on BR2_USE_MMU`，而工具链为 noMMU。缺失的选项会在输出构建目录（默认 `~/br-test-pkg/TOOLCHAIN_NAME/`）下的 `missing.config` 文件中报告。
- `FAILED`：构建失败。请检查输出构建目录下的 `logfile` 文件，查看出错原因：
  - 实际构建失败，
  - legal-info 检查失败，
  - 前置步骤（下载配置文件、应用配置、为包运行 `dirclean`）失败。

出现失败时，你可以在修复包后用相同选项重新运行脚本；脚本会尝试为所有工具链重新构建指定的 `-p` 包，无需重新构建该包的所有依赖。

`test-pkg` 脚本支持一些选项，可通过运行以下命令获取帮助：

```
$ ./utils/test-pkg -h
```





### 18.25.4. 如何添加 GitHub 上的软件包

GitHub（GitHub）上的软件包通常没有带有发布 tarball 的下载区。但可以直接从 GitHub 仓库下载 tarball。由于 GitHub 过去曾更改过下载机制，建议如下所示使用 *github* 辅助函数：

```
# 使用标签（tag）或完整的提交 ID
FOO_VERSION = 1.0
FOO_SITE = $(call github,<user>,<package>,v$(FOO_VERSION))
```

**注意事项**

- FOO_VERSION 可以是标签（tag）或提交 ID。
- github 生成的 tarball 名称与 Buildroot 默认一致（如：`foo-f6fb6654af62045239caed5950bc6c7971965e60.tar.gz`），因此无需在 `.mk` 文件中指定。
- 如果用提交 ID 作为版本，需使用完整的 40 位十六进制字符。
- 当标签带有前缀（如 `v1.0`），则 `VERSION` 变量只写 `1.0`，`v` 前缀直接加在 `SITE` 变量里，如上例。这保证 `VERSION` 变量可用于 [release-monitoring.org](http://www.release-monitoring.org/) 匹配。

如果你要添加的软件包在 GitHub 上有 release 区，维护者可能上传了 release tarball，或者 release 只是指向由 git tag 自动生成的 tarball。如果有维护者上传的 tarball，建议优先使用，因为它可能有细微差别（如包含 configure 脚本，无需 AUTORECONF）。

你可以在 release 页面判断：

- 如果像上图那样，则是维护者上传的，建议用该链接（如示例中的 *mongrel2-v1.9.2.tar.bz2*）指定 `FOO_SITE`，不要用 *github* 辅助函数。
- 如果只有“Source code”链接，则是自动生成的 tarball，应使用 *github* 辅助函数。

### 18.25.5. 如何添加 Gitlab 上的软件包

与 [18.25.4 节 “如何添加 GitHub 上的软件包”](https://buildroot.org/downloads/manual/manual.html#github-download-url) 中的 `github` 宏类似，Buildroot 也提供了 `gitlab` 宏用于下载 Gitlab（Gitlab）仓库的自动生成 tarball，可用于特定标签或提交：

```
# 使用标签或完整提交 ID
FOO_VERSION = 1.0
FOO_SITE = $(call gitlab,<user>,<package>,v$(FOO_VERSION))
```

默认使用 `.tar.gz`，但 Gitlab 也提供 `.tar.bz2`，可通过添加 `<pkg>_SOURCE` 变量指定：

```
# 使用标签或完整提交 ID
FOO_VERSION = 1.0
FOO_SITE = $(call gitlab,<user>,<package>,v$(FOO_VERSION))
FOO_SOURCE = foo-$(FOO_VERSION).tar.bz2
```

如果上游开发者在 `https://gitlab.com/<project>/releases/` 上传了特定 tarball，不要用该宏，而应直接用 tarball 链接。

### 18.25.6. 为包访问私有仓库

如果你想在 br2-external 树中创建包，且源码在私有仓库（如 gitlab、github、bitbucket 等），需要保证开发者和 CI 都能构建。这带来挑战，因为需要认证。

有两种最实用的方法：

#### 使用 SSH 和 `insteadOf`

将你的私有包配置为用 SSH 访问。

```
FOO_SITE = git@githosting.com:/<group>/<package>.git
```

开发者通常已配置好 ssh key，可以直接访问。唯一限制是如果在 docker 内构建，需确保 ssh key 可被容器访问。可以通过 `-v ~/.ssh:<homedir>/.ssh` 挂载 SSH 目录，或用 ssh-agent 加载私钥并传递 `--mount type=bind,source=$SSH_AUTH_SOCK,target=/ssh-agent --env SSH_AUTH_SOCK=/ssh-agent`。

CI 构建机通常没有能访问其他仓库的 SSH key。此时需生成访问令牌（access token），然后配置 git 用 HTTPS 替换 SSH。CI 的准备步骤如下：

```
git config --global url."https://<token>:x-oauth-basic@githosting.com/<group>/".insteadOf "git@githosting.com:/<group>/"
```

不同 git 托管商和不同类型的 token，HTTPS 认证方式可能不同。请查阅你的托管商文档，了解如何用 token 通过 HTTPS 访问 git。

#### 使用 HTTPS 和 `.netrc`

如果开发者没有 SSH key，更简单的方法是用 HTTPS 认证。每位开发者都需生成有权访问相关仓库的 token。有些 git 托管商有命令行工具生成 token，否则需在网页端生成。token 有有效期，需定期刷新。

为确保 Buildroot 构建时使用 token，将其写入 `~/.netrc`：

```
machine githosting.com
    login <username>
    password <token>
```

不同 git 托管商 `<username>` 和 `<password>` 的用法可能不同。

在 CI 中，作为准备步骤生成 `.netrc` 文件。

将你的私有包配置为用 HTTPS 访问。

```
FOO_SITE = https://githosting.com/<group>/<package>.git
```

wget（https）和 git 都会用 `.netrc` 获取登录信息。这种方式安全性略低，因为 `.netrc` 不能加密。但优点是用户和 CI 用同样的认证方式。

## 18.26. 总结

如你所见，向 Buildroot 添加软件包只需编写一个 Makefile，参考现有示例并根据包的编译流程进行修改即可。

如果你打包的软件对他人有用，别忘了向 Buildroot 邮件列表提交补丁（见 [22.5 节 “提交补丁”](https://buildroot.org/downloads/manual/manual.html#submitting-patches)）！



# 第 19 章. 修补（Patching）软件包

在集成新软件包或更新已有软件包时，可能需要修补（patch）软件源代码，以便在 Buildroot 中进行交叉编译。

Buildroot 提供了自动处理补丁的基础架构。它支持三种应用补丁集的方式：下载补丁、Buildroot 内部自带补丁，以及用户自定义的全局补丁目录。

## 19.1. 提供补丁

### 19.1.1. 下载方式

如果需要应用可下载的补丁，则将其添加到 `<packagename>_PATCH` 变量中。如果条目包含 `://`，Buildroot 会认为它是完整的 URL，并从该位置下载补丁。否则，Buildroot 会认为补丁应从 `<packagename>_SITE` 下载。可以是单个补丁，也可以是包含补丁集的 tarball。

与所有下载一样，应在 `<packagename>.hash` 文件中添加哈希值。

这种方式通常用于 Debian 的软件包。

### 19.1.2. Buildroot 内部补丁

大多数补丁直接放在 Buildroot 的包目录下，这些补丁通常用于修复交叉编译、libc 支持或其他类似问题。

补丁文件应命名为 `<number>-<description>.patch`。

**注意事项**

- Buildroot 自带的补丁文件名不应包含包版本信息。
- 补丁文件名中的 `<number>` 表示*应用顺序*，应从 1 开始，建议用零填充至 4 位，如 *git-format-patch* 所为。例如：`0001-foobar-the-buz.patch`
- 补丁邮件主题前缀不应编号。补丁应通过 `git format-patch -N` 生成，因为该命令会自动为系列补丁添加编号。例如，补丁主题应为 `Subject: [PATCH] foobar the buz`，而不是 `Subject: [PATCH n/m] foobar the buz`。
- 以前要求补丁文件名前缀加包名，如 `<package>-<number>-<description>.patch`，但现在不再要求。已有包会逐步修正。*不要再用包名作为补丁前缀。*
- 以前可以在包目录下添加 `series` 文件（如 quilt 所用），用于定义补丁应用顺序。该做法已废弃，未来会移除。*不要再用 series 文件。*

### 19.1.3. 全局补丁目录

`BR2_GLOBAL_PATCH_DIR` 配置项可用于指定一个或多个包含全局包补丁的目录（以空格分隔）。详见 [9.8.1 节 “提供额外补丁”](https://buildroot.org/downloads/manual/manual.html#customize-patches)。

## 19.2. 补丁的应用方式

1. 如果定义了 `<packagename>_PRE_PATCH_HOOKS`，先运行这些命令；
2. 清理构建目录，移除所有现有的 `*.rej` 文件；
3. 如果定义了 `<packagename>_PATCH`，则应用这些 tarball 中的补丁；
4. 如果包的 Buildroot 目录或其子目录 `<packageversion>` 下有 `*.patch` 文件，则：
   - 如果包目录下有 `series` 文件，则按 `series` 文件顺序应用补丁；
   - 否则，按字母顺序应用所有 `*.patch` 文件。为确保顺序正确，强烈建议补丁文件命名为 `<number>-<description>.patch`，其中 `<number>` 表示*应用顺序*。
5. 如果定义了 `BR2_GLOBAL_PATCH_DIR`，则按指定顺序遍历这些目录，补丁应用方式同上一步。
6. 如果定义了 `<packagename>_POST_PATCH_HOOKS`，则运行这些命令。

如果第 3 或 4 步出错，构建会失败。



## 19.3. 补丁的格式与许可

补丁的发布遵循其所修补软件的相同许可证（详见 [13.2 节 “遵守 Buildroot 许可证”](https://buildroot.org/downloads/manual/manual.html#legal-info-buildroot)）。

应在补丁头部注释中添加说明，解释补丁的作用及其必要性。

你应在每个补丁头部添加 `Signed-off-by` 声明，以便追踪变更并证明补丁遵循被修改软件的相同许可证。

如果软件在版本控制系统下，建议用上游 SCM 工具生成补丁集。

否则，将补丁头部与 `diff -purN package-version.orig/ package-version/` 命令的输出拼接。

如果你更新了已有补丁（如升级包版本时），请确保保留原有的 From 头和 Signed-off-by 标签，并在适当时更新补丁注释的其他部分。

最终补丁应如下所示：

```
configure.ac: add C++ support test

Signed-off-by: John Doe <john.doe@noname.org>

--- configure.ac.orig
+++ configure.ac
@@ -40,2 +40,12 @@

AC_PROG_MAKE_SET
+
+AC_CACHE_CHECK([whether the C++ compiler works],
+               [rw_cv_prog_cxx_works],
+               [AC_LANG_PUSH([C++])
+                AC_LINK_IFELSE([AC_LANG_PROGRAM([], [])],
+                               [rw_cv_prog_cxx_works=yes],
+                               [rw_cv_prog_cxx_works=no])
+                AC_LANG_POP([C++])])
+
+AM_CONDITIONAL([CXX_WORKS], [test "x$rw_cv_prog_cxx_works" = "xyes"])
```

## 19.4. 补丁的额外文档

理想情况下，所有补丁都应通过 `Upstream` trailer 记录上游补丁或补丁提交信息。

如果回溯应用了已被主线接受的上游补丁，建议引用该提交的 URL：

```
Upstream: <上游提交的 URL>
```

如果在 Buildroot 发现新问题，且上游也受影响（不是 Buildroot 特有问题），应向上游提交补丁，并尽可能提供提交链接：

```
Upstream: <上游邮件列表提交或合并请求的 URL>
```

如果补丁已提交但被上游拒绝，应注明原因，并说明为何仍需使用该补丁。

注意：在上述任一场景下，如对补丁做了必要修改，也应简要说明。

如果补丁无法应用到上游，应加注释说明：

```
Upstream: N/A <补丁为 Buildroot 专用的原因说明>
```

添加这些文档有助于在包版本更新时简化补丁审核流程。

# 第 20 章. 下载基础架构

TODO

# 第 21 章. 调试 Buildroot

可以对 Buildroot 构建包的各步骤进行插桩（instrumentation）。将变量 `BR2_INSTRUMENTATION_SCRIPTS` 定义为一个或多个脚本（或其他可执行文件）的路径（以空格分隔），这些脚本会在每个步骤前后被调用。脚本按顺序调用，带有三个参数：

- `start` 或 `end`，表示步骤开始或结束；
- 即将开始或刚结束的步骤名称；
- 包名称。

例如：

```
make BR2_INSTRUMENTATION_SCRIPTS="/path/to/my/script1 /path/to/my/script2"
```

步骤列表如下：

- `extract`
- `patch`
- `configure`
- `build`
- `install-host`，主机包安装到 `$(HOST_DIR)` 时
- `install-target`，目标包安装到 `$(TARGET_DIR)` 时
- `install-staging`，目标包安装到 `$(STAGING_DIR)` 时
- `install-image`，目标包安装文件到 `$(BINARIES_DIR)` 时

脚本可访问以下变量：

- `BR2_CONFIG`：Buildroot .config 文件路径
- `HOST_DIR`、`STAGING_DIR`、`TARGET_DIR`：见 [18.6.2 节 “generic-package 参考”](https://buildroot.org/downloads/manual/manual.html#generic-package-reference)
- `BUILD_DIR`：包解压和构建目录
- `BINARIES_DIR`：所有二进制文件（即镜像）存放位置
- `BASE_DIR`：输出基础目录
- `PARALLEL_JOBS`：并行进程数



# 第 22 章 参与 Buildroot 贡献

你可以通过多种方式为 Buildroot（Buildroot）做出贡献：分析和修复 bug（漏洞）、分析和修复 autobuilders（自动构建器）检测到的软件包构建失败、测试和评审其他开发者提交的补丁、处理我们的 TODO（待办事项）列表中的条目，以及向 Buildroot 或其手册提交你自己的改进。以下各节将对这些内容做进一步说明。

如果你有兴趣为 Buildroot 做贡献，首先应该订阅 Buildroot 邮件列表（mailing list）。该列表是与其他 Buildroot 开发者互动和提交贡献的主要方式。如果你还没有订阅，请参考[第五章，社区资源（Community resources）](https://buildroot.org/downloads/manual/manual.html#community-resources)获取订阅链接。

如果你打算修改代码，强烈建议你使用 Buildroot 的 git（Git）仓库，而不是直接从源码压缩包（tarball）开始。Git 是最便捷的开发方式，并且可以直接将你的补丁发送到邮件列表。关于如何获取 Buildroot git 树，请参考[第三章，获取 Buildroot（Getting Buildroot）](https://buildroot.org/downloads/manual/manual.html#getting-buildroot)。

## 22.1 复现、分析和修复 bug（漏洞）

参与贡献的第一种方式是查看 [Buildroot bug 跟踪器（bug tracker）](https://gitlab.com/buildroot.org/buildroot/-/issues) 上的未解决 bug 报告。我们努力保持 bug 数量尽可能少，因此欢迎大家协助复现、分析和修复已报告的 bug。即使你还没有完全弄清楚问题，也请不要犹豫，欢迎在 bug 报告下添加你的发现。

## 22.2 分析和修复自动构建失败

Buildroot 自动构建器（autobuilders）是一组持续运行 Buildroot 构建任务的构建机器，基于随机配置进行构建。它们会针对 Buildroot 支持的所有架构、使用不同的工具链（toolchain），并随机选择软件包。由于 Buildroot 的提交活动非常频繁，这些自动构建器有助于在提交后第一时间发现问题。

所有构建结果可在 [http://autobuild.buildroot.org](http://autobuild.buildroot.org/) 查看，统计信息见 http://autobuild.buildroot.org/stats.php。每天，所有失败软件包的概览会发送到邮件列表。

发现问题固然重要，但更重要的是要修复这些问题。你的贡献在这里非常受欢迎！主要可以做两件事：

- 分析问题。每日汇总邮件不会包含实际失败的详细信息：要了解具体情况，你需要打开构建日志（build log），查看最后的输出。有人为邮件中的所有软件包做这项工作，对其他开发者非常有帮助，因为他们可以基于这些输出做初步分析。
- 修复问题。修复自动构建失败时，你应遵循以下步骤：
  1. 检查你是否可以通过相同配置复现问题。你可以手动操作，也可以使用 [br-reproduce-build](http://git.buildroot.org/buildroot-test/tree/utils/br-reproduce-build) 脚本，该脚本会自动克隆 Buildroot git 仓库、检出正确的版本、下载并设置正确的配置，然后启动构建。
  2. 分析问题并创建修复方案。
  3. 从干净的 Buildroot 树开始，仅应用你的修复，验证问题确实被修复。
  4. 将修复补丁发送到 Buildroot 邮件列表（见[22.5节，提交补丁（Submitting patches）](https://buildroot.org/downloads/manual/manual.html#submitting-patches)）。如果你对软件包源码做了补丁，也应将补丁提交到上游（upstream），以便后续版本修复该问题，Buildroot 中的补丁可以移除。在修复自动构建失败的补丁提交信息中，请添加构建结果目录的引用，例如：

```
Fixes: http://autobuild.buildroot.org/results/51000a9d4656afe9e0ea6f07b9f8ed374c2e4069
```

## 22.3 评审和测试补丁

每天有大量补丁发送到邮件列表，维护者很难判断哪些补丁可以直接合入，哪些还需要完善。贡献者可以通过评审和测试这些补丁，极大地帮助维护者。

在评审过程中，请大胆回复补丁提交，提出意见、建议或任何有助于大家理解和完善补丁的内容。回复补丁时请使用互联网风格的纯文本邮件。

为了表明对补丁的认可，有三种正式标签用于记录这种认可。要为补丁添加你的标签，请在原作者的 Signed-off-by 行下方回复补丁并添加标签。Patchwork（见[22.3.1节，通过 Patchwork 应用补丁（Applying Patches from Patchwork）](https://buildroot.org/downloads/manual/manual.html#apply-patches-patchwork)）会自动识别这些标签，补丁被接受后，这些标签也会成为提交日志的一部分。

- Tested-by（已测试）

  表示该补丁已被成功测试。建议你说明测试的类型（如在 X 和 Y 架构上编译测试，在 A 目标板上运行测试等）。这些附加信息有助于其他测试者和维护者。

- Reviewed-by（已评审）

  表示你已对补丁进行了代码评审，并尽力发现问题，但你对所涉及领域不够熟悉，无法提供 Acked-by 标签。这意味着补丁中可能仍有问题，需要更有经验的人来发现。如果后续发现问题，你的 Reviewed-by 标签依然有效，你不会因此被指责。

- Acked-by（已确认）

  表示你已对补丁进行了代码评审，并且对所涉及领域足够熟悉，认为补丁可以直接合入（无需额外修改）。如果后续发现补丁有问题，你的 Acked-by 可能会被认为不合适。Acked-by 和 Reviewed-by 的主要区别在于，Acked-by 你愿意为补丁负责，而 Reviewed-by 则不承担责任。

如果你评审了补丁并有意见，请直接回复补丁说明你的意见，无需添加 Reviewed-by 或 Acked-by 标签。只有当你认为补丁已经很好时，才应添加这些标签。

需要注意的是，Reviewed-by 和 Acked-by 并不意味着已经进行了测试。要表示你既评审又测试了补丁，请分别添加两个标签（Reviewed/Acked-by 和 Tested-by）。

另外，*任何开发者*都可以提供 Tested/Reviewed/Acked-by 标签，无一例外，我们鼓励大家这样做。Buildroot 没有明确的“核心”开发者群体，只是有些开发者比其他人更活跃。维护者会根据提交者的历史记录来评估标签的可信度。常规贡献者的标签自然比新人的标签更受信任，但*任何*标签都是有价值的。

Buildroot 的 Patchwork 网站可用于拉取补丁进行测试。更多关于如何使用 Patchwork 应用补丁的信息，请参见[22.3.1节，通过 Patchwork 应用补丁（Applying Patches from Patchwork）](https://buildroot.org/downloads/manual/manual.html#apply-patches-patchwork)。

### 22.3.1 通过 Patchwork 应用补丁

Buildroot Patchwork 网站的主要用途是让开发者将补丁拉取到本地 git 仓库进行测试。

在 Patchwork 管理界面浏览补丁时，页面顶部会有一个 `mbox` 链接。复制该链接地址并运行以下命令：

```
$ git checkout -b <test-branch-name>
$ wget -O - <mbox-url> | git am
```

另一种应用补丁的方法是创建补丁集（bundle）。你可以在 Patchwork 界面将多个补丁分组为一个补丁集。补丁集创建并公开后，可以复制该补丁集的 `mbox` 链接，使用上述命令应用。

## 22.4 处理 TODO（待办事项）列表中的条目

如果你想为 Buildroot 做贡献但不知道从哪里开始，且对上述内容不感兴趣，也可以处理 [Buildroot TODO 列表](http://elinux.org/Buildroot#Todo_list) 中的条目。欢迎先在邮件列表或 IRC 上讨论某个条目。请在 wiki 上编辑，标明你已开始处理某个条目，以避免重复劳动。

## 22.5 提交补丁（patch）

### 注意

*请不要将补丁作为附件提交到 bug（漏洞）报告中，而应发送到邮件列表。*

如果你对 Buildroot 做了修改，想要将其贡献给 Buildroot 项目，请按如下流程操作。

### 22.5.1 补丁格式要求

我们要求补丁采用特定格式。这有助于补丁的评审、便于将补丁应用到 git 仓库、方便追溯历史变更的原因和方式，并能使用 `git bisect` 定位问题来源。

首先，补丁必须有良好的提交信息（commit message）。提交信息应以一行简要的变更摘要开头，并以补丁涉及的领域为前缀。以下是一些好的提交标题示例：

- `package/linuxptp: bump version to 2.0`
- `configs/imx23evk: bump Linux version to 4.19`
- `package/pkg-generic: postpone evaluation of dependency conditions`
- `boot/uboot: needs host-{flex,bison}`
- `support/testing: add python-ubjson tests`

前缀后的描述应以小写字母开头（如上述示例中的 "bump"、"needs"、"postpone"、"add"）。

其次，提交信息正文应描述*为什么*需要此更改，如有必要，还应说明*如何*实现。撰写提交信息时，请考虑评审者的阅读体验，也要考虑几年后你自己回看这次更改时的理解。

第三，补丁本身应只做一项更改，并且要做完整。两个无关或关系不大的更改通常应分为两个补丁。这通常意味着一个补丁只影响一个软件包。如果多个更改相关，通常也可以拆分为多个小补丁并按顺序应用。小补丁便于评审，也便于后续理解更改原因。但每个补丁必须是完整的，不能只应用第一个补丁就导致构建失败，这样才能使用 `git bisect`。

当然，在开发过程中，你可能会在不同软件包间来回修改，提交历史也未必一开始就适合提交。因此大多数开发者会重写提交历史，整理出适合提交的补丁集。为此，你需要使用*交互式变基（interactive rebasing）*。可参考 [Pro Git 书籍](https://git-scm.com/book/en/v2/Git-Tools-Rewriting-History) 了解详情。有时，直接用 `git reset --soft origin/master` 丢弃历史，然后用 `git add -i` 或 `git add -p` 选择性添加更改会更容易。

最后，补丁应签名（signed off）。在提交信息末尾添加 `Signed-off-by: 你的真实姓名 <your@email.address>`。如果配置正确，`git commit -s` 会自动添加。`Signed-off-by` 标签表示你以 Buildroot 许可协议（即 GPL-2.0+，软件包补丁除外，采用上游许可）发布补丁，并且你有权这样做。详情见[开发者认证协议（Developer Certificate of Origin）](http://developercertificate.org/)。

如果要注明补丁由谁赞助或由谁协助上游，可以在 git 身份（即提交作者和邮件 From 字段，以及 Signed-off-by 标签）中使用[邮件子地址（email subaddressing）](https://datatracker.ietf.org/doc/html/rfc5233)；在本地部分后加加号 `+` 和后缀。例如：

- 公司赞助的补丁，后缀用公司名：

  `Your-Name Your-Surname <your-name.your-surname+companyname@mail.com>`

- 个人赞助的补丁，后缀用其姓名：

  `Your-Name Your-Surname <your-name.your-surname+their-name.their-surname@mail.com>`

如果你的邮件服务器不支持子地址，也可以在作者名后加括号注明赞助人，如 "Your Name (Sponsor Name)"。

添加新软件包时，每个软件包应单独提交补丁。补丁应包含对 `package/Config.in` 的更新、软件包的 `Config.in` 文件、`.mk` 文件、`.hash` 文件、任何初始化脚本以及所有软件包补丁。如果软件包有很多子选项，建议分为多个后续补丁。摘要行应为 `<packagename>: new package`。对于简单软件包，提交信息正文可以为空；复杂软件包可写上包描述（如 Config.in 的帮助文本）。如有特殊构建要求，也应在正文中明确说明。

升级软件包版本时，也应为每个软件包单独提交补丁。不要忘记更新 `.hash` 文件，或在不存在时添加。还要检查 `_LICENSE` 和 `_LICENSE_FILES` 是否仍然有效。摘要行应为 `<packagename>: bump to version <new version>`。如果新版本仅包含安全更新，摘要应为 `<packagename>: security bump to version <new version>`，正文应列出修复的 CVE 编号。如果新版本可以移除某些补丁，应明确说明原因，最好附上上游提交 ID。其他必要更改也应明确说明，如不再存在或不再需要的配置选项。

如果你希望在你添加或修改的软件包出现构建失败或后续变更时收到通知，请将自己添加到 DEVELOPERS 文件中。应在创建或修改软件包的同一个补丁中完成。更多信息见 [DEVELOPERS 文件](https://buildroot.org/downloads/manual/manual.html#DEVELOPERS)。

Buildroot 提供了一个名为 `check-package` 的工具，用于检查你创建或修改的文件是否存在常见的代码风格问题，详见[18.25.2节，如何检查代码风格（How to check the coding style）](https://buildroot.org/downloads/manual/manual.html#check-package)。





### 22.5.2 准备补丁集（patch series）

在本地 git（Git）视图中提交更改后，在生成补丁集之前，*rebase*（变基）你的开发分支到上游主线。操作如下：

```
$ git fetch --all --tags
$ git rebase origin/master
```

现在，检查你提交的更改的代码风格：

```
$ utils/docker-run make check-package
```

现在，你可以生成并提交补丁集了。

生成补丁集，运行：

```
$ git format-patch -M -n -s -o outgoing origin/master
```

这将在 `outgoing` 子目录下生成补丁文件，并自动添加 `Signed-off-by` 行。

补丁文件生成后，你可以用自己喜欢的文本编辑器在提交前审查/编辑提交信息。

Buildroot 提供了一个方便的工具 `get-developers`，用于确定补丁应发送给哪些开发者，详见[第二十三章，DEVELOPERS 文件与 get-developers](https://buildroot.org/downloads/manual/manual.html#DEVELOPERS)。该工具会读取你的补丁并输出合适的 `git send-email` 命令：

```
$ ./utils/get-developers outgoing/*
```

使用 `get-developers` 的输出发送补丁：

```
$ git send-email --to buildroot@buildroot.org --cc bob --cc alice outgoing/*
```

另外，也可以直接用 `get-developers -e` 配合 `git send-email` 的 `--cc-cmd` 参数自动 CC 相关开发者：

```
$ git send-email --to buildroot@buildroot.org \
      --cc-cmd './utils/get-developers -e' origin/master
```

你还可以通过如下方式让 git 自动配置这些参数：

```
$ git config sendemail.to buildroot@buildroot.org
$ git config sendemail.ccCmd "$(pwd)/utils/get-developers -e"
```

之后只需：

```
$ git send-email origin/master
```

注意，`git` 需要配置你的邮件账户。配置方法请参见 `man git-send-email` 或 https://git-send-email.io/。

如果你不使用 `git send-email`，请确保***补丁邮件不会被自动换行***，否则补丁将无法被方便地应用。如果遇到此问题，请修正你的邮件客户端，或者更推荐学习使用 `git send-email`。

[https://sr.ht](https://sr.ht/) 也提供了一个轻量级界面用于[准备补丁集](https://man.sr.ht/git.sr.ht/#sending-patches-upstream)，并可帮你发送补丁。该方式有一些缺点，比如无法在 Patchwork 中编辑补丁状态，也无法修改补丁邮件的显示名，但如果你的邮件服务（如 O365）无法用 `git send-email`，这也是一个备选方案。注意，这不是官方推荐的补丁发送方式，仅作补充。

### 22.5.3 封面信（cover letter）

如果你想用单独邮件介绍整个补丁集，在 `git format-patch` 命令中加 `--cover-letter`（详见 `man git-format-patch`）。这会生成一个补丁集介绍邮件的模板。

在以下情况下，*封面信* 很有用：

- 补丁集包含大量提交；
- 变更对项目影响较大；
- RFC（Request for comments，征求意见稿）；
- 或者你觉得有助于介绍你的工作、选择、评审流程等。

### 22.5.4 维护分支的补丁

修复维护分支（maintenance branch）上的 bug 时，应先在 master 分支修复。此类补丁的提交日志可包含一条说明受影响分支的备注：

```
package/foo: fix stuff

Signed-off-by: Your Real Name <your@email.address>
---
Backport to: 2020.02.x, 2020.05.x
(2020.08.x not affected as the version was bumped)
```

这些更改随后会由维护者回合到受影响的分支。

但有些 bug 只影响特定版本（如使用了旧版软件包）。此时，补丁应基于维护分支，并在补丁主题前缀中注明维护分支名（如 "[PATCH 2020.02.x]"）。可用 `git format-patch` 的 `--subject-prefix` 参数实现：

```
$ git format-patch --subject-prefix "PATCH 2020.02.x" \
    -M -s -o outgoing origin/2020.02.x
```

然后用 `git send-email` 发送补丁，如上所述。

### 22.5.5 补丁修订日志（Patch revision changelog）

如有改进建议，每次提交的新版本补丁都应在提交信息中包含本次与上次的修改日志。若补丁集有封面信，可在封面信和各补丁提交信息中分别写修订日志。推荐用交互式变基（interactive rebasing）：`git rebase -i origin/master`。详见 git 手册。

在各补丁提交信息中，修订日志应写在 `Signed-off-by` 之后，`---` 之下。

修订日志会在邮件讨论和 [patchwork](https://patchwork.ozlabs.org/project/buildroot/list/) 中显示，但 `git` 合并补丁时会自动忽略 `---` 之后的内容，这是预期行为：修订日志不应永久保留在项目 git 历史中。

推荐格式如下：

```
Patch title: short explanation, max 72 chars

A paragraph that explains the problem, and how it manifests itself. If
 the problem is complex, it is OK to add more paragraphs. All paragraphs
 should be wrapped at 72 characters.

A paragraph that explains the root cause of the problem. Again, more
 than one paragraph is OK.

Finally, one or more paragraphs that explain how the problem is solved.
Don't hesitate to explain complex solutions in detail.

Signed-off-by: John DOE <john.doe@example.net>

---
Changes v2 -> v3:
  - foo bar  (suggested by Jane)
  - bar buz

Changes v1 -> v2:
  - alpha bravo  (suggested by John)
  - charly delta
```

任何补丁修订都应包含版本号。版本号格式为字母 `v` 加上大于等于 2 的整数（如 "PATCH v2"、"PATCH v3" 等）。

用 `git format-patch` 的 `--subject-prefix` 选项可方便实现：

```
$ git format-patch --subject-prefix "PATCH v4" \
    -M -s -o outgoing origin/master
```

自 git 1.8.1 起，也可用 `-v <n>`（<n> 为版本号）：

```
$ git format-patch -v4 -M -s -o outgoing origin/master
```

提交新版本补丁时，请在 [patchwork](https://patchwork.ozlabs.org/project/buildroot/list/) 标记旧版本为 superseded（已被替代）。你需在 patchwork 注册账号，且注册邮箱需与发送补丁到邮件列表时一致。

你还可以在发送补丁时加 `--in-reply-to=<message-id>` 参数。邮件的 id 可在 [patchwork](https://patchwork.ozlabs.org/project/buildroot/list/) 的 "Message Id" 标签下找到。这样 patchwork 会自动将旧版本补丁标记为 superseded。

## 22.6 报告问题/bug 或寻求帮助

在报告任何问题前，请先在[邮件列表归档](https://buildroot.org/downloads/manual/manual.html#community-resources)中查找是否有人已报告/修复了类似问题。

无论你选择在[bug 跟踪器](https://buildroot.org/downloads/manual/manual.html#community-resources)报告 bug，还是[发邮件到邮件列表](https://buildroot.org/downloads/manual/manual.html#community-resources)寻求帮助，为了方便他人复现和解决问题，请尽量提供以下信息：

- 主机（host）操作系统及版本
- Buildroot 版本
- 构建失败的目标（target）
- 构建失败的软件包（package）
- 失败的命令及其输出
- 你认为可能相关的其他信息

此外，建议附上 `.config` 文件（或如有能力，附上 `defconfig`，见[9.3节，保存 Buildroot 配置（Storing the Buildroot configuration）](https://buildroot.org/downloads/manual/manual.html#customize-store-buildroot-config)）。

如有些信息太大，可使用 pastebin 服务。注意，并非所有 pastebin 服务都能在下载原始内容时保留 Unix 风格换行符。以下 pastebin 服务已知可正常使用：

- https://gist.github.com/
- http://code.bulix.org/



## 22.7 使用运行时测试框架（runtime tests framework）

Buildroot 包含一个基于 Python 脚本和 QEMU 运行时执行的运行时测试框架。该框架的目标如下：

- 构建一个定义明确的 Buildroot 配置
- （可选）验证构建输出的某些属性
- （可选）在 Qemu 下启动构建结果，并验证某个功能是否按预期工作

使用运行时测试框架的入口是 `support/testing/run-tests` 工具，其参数可通过 *-h* 查看帮助文档。常用选项包括设置下载文件夹、输出文件夹、保留构建输出，以及为多个测试用例设置 JLEVEL。

以下是运行测试用例的示例流程：

- 第一步，查看所有测试用例选项。可通过执行 `support/testing/run-tests -l` 列出所有测试用例。这些测试可在测试开发期间单独运行，也可选择性地批量运行。

```
$ support/testing/run-tests -l
List of tests
test_run (tests.utils.test_check_package.TestCheckPackage)
test_run (tests.toolchain.test_external.TestExternalToolchainBuildrootMusl) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainBuildrootuClibc) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainCCache) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainCtngMusl) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainLinaroArm) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainSourceryArmv4) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainSourceryArmv5) ... ok
test_run (tests.toolchain.test_external.TestExternalToolchainSourceryArmv7) ... ok
[省略]
test_run (tests.init.test_systemd.TestInitSystemSystemdRoFull) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRoIfupdown) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRoNetworkd) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRwFull) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRwIfupdown) ... ok
test_run (tests.init.test_systemd.TestInitSystemSystemdRwNetworkd) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRo) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRoNet) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRw) ... ok
test_run (tests.init.test_busybox.TestInitSystemBusyboxRwNet) ... ok

Ran 157 tests in 0.021s

OK
```

- 然后，运行单个测试用例：

```
$ support/testing/run-tests -d dl -o output_folder -k tests.init.test_busybox.TestInitSystemBusyboxRw
15:03:26 TestInitSystemBusyboxRw                  Starting
15:03:28 TestInitSystemBusyboxRw                  Building
15:08:18 TestInitSystemBusyboxRw                  Building done
15:08:27 TestInitSystemBusyboxRw                  Cleaning up
.
Ran 1 test in 301.140s

OK
```

标准输出会显示测试是否成功。默认情况下，测试的输出文件夹会自动删除，除非使用 `-k` 选项***保留***输出目录。

### 22.7.1 创建测试用例

在 Buildroot 仓库中，测试框架在 `support/testing/` 顶层目录下分为 `conf`、`infra` 和 `tests` 文件夹。所有测试用例都在 `tests` 文件夹下，按测试类别分文件夹组织。

熟悉如何创建测试用例的最佳方式是查看一些基础文件系统测试（`support/testing/tests/fs/`）和 init 测试（`support/testing/tests/init/`）脚本。这些测试很好地展示了如何既检查构建结果，又进行运行时测试。还有更高级的用例会用到嵌套的 `br2-external` 文件夹来提供 skeleton 和额外软件包。

创建基础测试用例包括：

- 定义一个继承自 `infra.basetest.BRTest` 的测试类
- 定义测试类的 `config` 成员，指定本测试用例要构建的 Buildroot 配置。可选地，依赖运行时测试基础设施提供的配置片段：`infra.basetest.BASIC_TOOLCHAIN_CONFIG`（获取基础架构/工具链配置）和 `infra.basetest.MINIMAL_CONFIG`（不构建任何文件系统）。使用 `infra.basetest.BASIC_TOOLCHAIN_CONFIG` 的好处是会提供匹配的 Linux 内核镜像，可以直接在 Qemu 启动生成的镜像，无需在测试用例中构建内核镜像，从而大大减少测试用例所需的构建时间。
- 实现 `def test_run(self):` 方法，编写构建完成后要执行的实际测试。可以是验证构建输出的测试（通过 `run_cmd_on_host()` 辅助函数在主机上运行命令），也可以是通过 Qemu 启动系统并在 Qemu 内部运行命令（通过测试用例中的 `self.emulator` 对象）。例如，`self.emulator.boot()` 启动 Qemu，`self.emulator.login()` 登录，`self.emulator.run()` 在 Qemu 内部运行 shell 命令。

创建测试脚本后，请将自己添加到 `DEVELOPERS` 文件，成为该测试用例的维护者。

### 22.7.2 调试测试用例

测试用例运行时，`output_folder` 会包含如下内容：

```
$ ls output_folder/
TestInitSystemBusyboxRw/
TestInitSystemBusyboxRw-build.log
TestInitSystemBusyboxRw-run.log
```

`TestInitSystemBusyboxRw/` 是 Buildroot 输出目录，仅在使用 `-k` 选项时保留。

`TestInitSystemBusyboxRw-build.log` 是 Buildroot 构建日志。

`TestInitSystemBusyboxRw-run.log` 是 Qemu 启动和测试日志。仅当构建成功且测试用例涉及 Qemu 启动时才会生成。

如需手动运行 Qemu 进行调试，可参考 `TestInitSystemBusyboxRw-run.log` 前几行中的 Qemu 命令行。

你还可以在 `output_folder` 内修改当前源码（如调试用），然后重新运行标准 Buildroot make 目标（以重新生成完整镜像），再重新运行测试。

### 22.7.3 运行时测试与 Gitlab CI

所有运行时测试都会定期由 Buildroot 的 Gitlab CI 基础设施执行，详见 .gitlab.yml 和 https://gitlab.com/buildroot.org/buildroot/-/jobs。

你也可以用 Gitlab CI 测试你新增的测试用例，或在修改 Buildroot 后验证现有测试是否仍然通过。

为此，你需要在 Gitlab 上 fork Buildroot 项目，并能向你的 Buildroot fork 推送分支。

你推送的分支名决定是否触发 Gitlab CI pipeline，以及触发哪些测试用例。

以下示例中，<name> 是你自定义的字符串。

- 触发所有 run-test 测试用例作业，推送以 `-runtime-tests` 结尾的分支：

```
 $ git push gitlab HEAD:<name>-runtime-tests
```

- 触发一个或多个测试用例作业，推送以完整测试用例名（如 `tests.init.test_busybox.TestInitSystemBusyboxRo`）或测试类别名（如 `tests.init.test_busybox`）结尾的分支：

```
 $ git push gitlab HEAD:<name>-<test case name>
```

示例，运行单个测试：

```
 $ git push gitlab HEAD:foo-tests.init.test_busybox.TestInitSystemBusyboxRo
```

示例，运行同一组的多个测试：

```
 $ git push gitlab HEAD:foo-tests.init.test_busybox
 $ git push gitlab HEAD:foo-tests.init
```

------

[[4\] ](https://buildroot.org/downloads/manual/manual.html#idm6107)RFC:（Request for comments，变更提案）

# 第 23 章 DEVELOPERS 文件与 get-developers

Buildroot 主目录下有一个名为 `DEVELOPERS` 的文件，列出了参与 Buildroot 各领域的开发者。借助该文件，`get-developers` 工具可以：

- 通过解析补丁并匹配被修改文件与相关开发者，计算补丁应发送给哪些开发者。详见[22.5节，提交补丁（Submitting patches）](https://buildroot.org/downloads/manual/manual.html#submitting-patches)。
- 查找负责某个架构或软件包的开发者，以便在该架构或软件包构建失败时通知他们。这与 Buildroot 的自动构建基础设施配合完成。

我们要求添加新软件包、新板卡或新功能的开发者，在 `DEVELOPERS` 文件中注册自己。例如，贡献新软件包的开发者应在补丁中包含对 `DEVELOPERS` 文件的相应修改。

`DEVELOPERS` 文件的格式在文件内部有详细说明。

`get-developers` 工具位于 `utils/` 目录下，可用于多种任务：

- 命令行传入一个或多个补丁时，`get-developers` 会返回合适的 `git send-email` 命令。如加 `-e` 选项，则只输出适合 `git send-email --cc-cmd` 的邮件地址。
- 用 `-a <arch>` 参数可返回负责指定架构的开发者列表。
- 用 `-p <package>` 参数可返回负责指定软件包的开发者列表。
- 用 `-c` 参数会检查 Buildroot 仓库下所有版本控制文件，列出未被任何开发者负责的文件，便于补全 `DEVELOPERS` 文件。
- 用 `-v` 参数可校验 DEVELOPERS 文件的完整性，并对不匹配项给出警告。

# 第 24 章 发布工程（Release Engineering）

### 24.1 发布（Releases）

Buildroot 项目每季度发布一次正式版，每月发布一次 bug 修复版。每年首个正式版为长期支持版（LTS，Long Term Support）。

- 季度发布：2020.02、2020.05、2020.08、2020.11
- bug 修复发布：2020.02.1、2020.02.2、……
- LTS 发布：2020.02、2021.02、……

每个正式版支持到下一个正式版的首个 bug 修复版发布为止，例如 2020.05.x 在 2020.08.1 发布时停止维护（EOL，End of Life）。

LTS 版支持到下一个 LTS 的首个 bug 修复版发布为止，例如 2020.02.x 支持到 2021.02.1 发布为止。

### 24.2 开发（Development）

每个发布周期包括两个月的 `master` 分支开发和一个月的稳定期（stabilization），之后发布正式版。在稳定期内，`master` 分支不再添加新特性，只接受 bug 修复。

稳定期开始时会打 `-rc1` 标签，之后每周再打一个候选发布（release candidate）标签，直到正式发布。

为在稳定期处理新特性和版本升级，可能会创建 `next` 分支。当前版本发布后，`next` 分支合并到 `master`，下一个发布周期的开发继续在 `master` 进行。

# 第四部分 附录

# 第 25 章 Makedev 语法文档（Makedev syntax documentation）

Makedev 语法在 Buildroot 的多个地方用于定义权限变更、要创建哪些设备文件及如何创建，以避免直接调用 mknod。

该语法源自 makedev 工具，更完整文档见 `package/makedevs/README` 文件。

格式为以空格分隔的字段，每行一个文件；字段如下：

| name（名称） | type（类型） | mode（权限） | uid  | gid  | major | minor | start | inc  | count |
| ------------ | ------------ | ------------ | ---- | ---- | ----- | ----- | ----- | ---- | ----- |
|              |              |              |      |      |       |       |       |      |       |

主要字段说明：

- `name`：要创建/修改的文件路径
- `type`：文件类型，可选：
  - `f`：普通文件，必须已存在
  - `F`：普通文件，若不存在则忽略不创建
  - `d`：目录，若不存在则自动创建及其父目录
  - `r`：递归目录，必须已存在
  - `c`：字符设备文件，父目录必须已存在
  - `b`：块设备文件，父目录必须已存在
  - `p`：命名管道，父目录必须已存在
- `mode`：权限设置（仅允许数字），`d` 类型父目录已存在则权限不变，新建父目录则设置权限；`f`、`F`、`r` 类型可设为 `-1` 表示不变（只改 uid/gid）
- `uid`、`gid`：文件的 UID 和 GID，可为数字或名称
- `major`、`minor`：仅设备文件需设置，其他文件设为 `-`
- `start`、`inc`、`count`：用于批量创建文件，相当于循环，从 `start` 开始，每次递增 `inc`，直到 `count`

示例：更改文件所有权和权限：

```
/usr/bin/foo f 755 0 0 - - - - -
/usr/bin/bar f 755 root root - - - - -
/data/buz f 644 buz-user buz-group - - - - -
/data/baz f -1 baz-user baz-group - - - - -
```

递归更改目录所有权：

```
/usr/share/myapp r -1 foo bar - - - - -
```

创建设备文件 `/dev/hda` 及其 15 个分区：

```
/dev/hda b 640 root root 3 0 0 0 -
/dev/hda b 640 root root 3 1 1 1 15
```

如启用 `BR2_ROOTFS_DEVICE_TABLE_SUPPORTS_EXTENDED_ATTRIBUTES`，可支持扩展属性。只需在文件描述行后加以 `|xattr` 开头的行，目前仅支持 capability：

| \|xattr | capability |
| ------- | ---------- |
|         |            |

- `|xattr`：扩展属性标志
- `capability`：要添加的 capability

为二进制 foo 添加 cap_sys_admin 能力：

```
/usr/bin/foo f 755 root root - - - - -
|xattr cap_sys_admin+eip
```

为同一文件添加多个 capability：

```
/usr/bin/foo f 755 root root - - - - -
|xattr cap_sys_admin+eip
|xattr cap_net_admin+eip
```



# 第 26 章 Makeusers 语法文档（Makeusers syntax documentation）

创建用户的语法借鉴了上文的 makedev 语法，但为 Buildroot 专用。

添加用户的语法为以空格分隔的字段，每行一个用户；字段如下：

| username（用户名） | uid  | group（主组） | gid  | password（密码） | home（家目录） | shell（Shell） | groups（附加组） | comment（备注） |
| ------------------ | ---- | ------------- | ---- | ---------------- | -------------- | -------------- | ---------------- | --------------- |
|                    |      |               |      |                  |                |                |                  |                 |

说明：

- `username`：用户登录名，不能为 `root`，且必须唯一。若为 `-`，则只创建组。
- `uid`：用户 UID，必须唯一且不能为 `0`。若为 `-1` 或 `-2`，Buildroot 会自动分配唯一 UID，`-1` 表示系统 UID（100~999），`-2` 表示普通用户 UID（1000~1999）。
- `group`：主组名，不能为 `root`。若组不存在会自动创建。
- `gid`：主组 GID，必须唯一且不能为 `0`。若为 `-1` 或 `-2` 且组不存在，则 Buildroot 会自动分配唯一 GID，`-1` 表示系统 GID（100~999），`-2` 表示普通用户 GID（1000~1999）。
- `password`：crypt(3) 加密密码。以 `!` 开头则禁用登录；以 `=` 开头则为明文密码，会用 MD5 加密；以 `!=` 开头则明文加密且禁用登录。为 `*` 则禁止登录。为 `-` 则不设置密码。
- `home`：用户家目录。为 `-` 则不创建家目录，用户家目录为 `/`。不能显式设置为 `/`。
- `shell`：用户 shell。为 `-` 则 shell 设为 `/bin/false`。
- `groups`：用户所属附加组，逗号分隔。为 `-` 则无附加组。缺失的组会自动创建。
- `comment`：备注（GECOS 字段），几乎可任意填写。

字段限制：

- 除 `comment` 外，所有字段必填。
- 除 `comment` 外，字段不能包含空格。
- 所有字段不能包含冒号（:）。

如 `home` 不为 `-`，则家目录及其下所有文件归该用户及主组所有。

示例：

```
foo -1 bar -1 !=blabla /home/foo /bin/sh alpha,bravo Foo user
```

将创建如下用户：

- 用户名：`foo`
- UID 由 Buildroot 分配
- 主组：`bar`
- 主组 GID 由 Buildroot 分配
- 明文密码为 `blabla`，会加密且禁用登录
- 家目录为 `/home/foo`
- shell 为 `/bin/sh`
- 附加组为 `alpha` 和 `bravo`
- 备注为 `Foo user`

```
test 8000 wheel -1 = - /bin/sh - Test user
```

将创建如下用户：

- 用户名：`test`
- UID 为 8000
- 主组为 `wheel`
- 主组 GID 由 Buildroot 分配，取 rootfs skeleton 中定义值
- 密码为空（无密码）
- 家目录为 `/`，但不归 `test` 所有
- shell 为 `/bin/sh`
- 无附加组
- 备注为 `Test user`

## 26.1 自动 UID 和 GID 的注意事项

升级 buildroot 或增删配置中的软件包时，自动分配的 UID 和 GID 可能会变化。如果有持久化文件由该用户或组创建，升级后这些文件的所有者会变。

因此建议将自动分配的 ID 固定下来。可通过添加包含已生成 ID 的用户表实现。仅需为实际创建持久化文件（如数据库）的 UID 固定。

# 第 27 章 旧版 Buildroot 迁移指南（Migrating from older Buildroot versions）

部分版本引入了不兼容变更。本节说明这些不兼容及迁移方法。

## 27.1 通用迁移流程

从旧版 Buildroot 迁移，建议如下：

1. 针对所有配置，在旧 Buildroot 环境下构建一次。运行 `make graph-size`，保存 `graphs/file-size-stats.csv` 到其他位置。运行 `make clean` 清理其余内容。
2. 阅读下文具体迁移说明，按需调整外部包和自定义构建脚本。
3. 升级 Buildroot。
4. 从现有 `.config` 开始，运行 `make menuconfig`。
5. 若 Legacy 菜单有启用项，查看帮助说明，取消选择并保存配置。
6. 详细情况可查阅相关软件包的 git 提交信息。进入 `packages` 目录，运行 `git log <old version>..--<your packages>`。
7. 在新 Buildroot 环境下构建。
8. 修复外部包的构建问题（通常因依赖升级）。
9. 运行 `make graph-size`。
10. 比较新旧 `file-size-stats.csv`，确保无必需文件丢失，也无新出现的大型无用文件。
11. 对自定义 overlay 中覆盖 Buildroot 生成文件的配置（及其他）文件，检查 Buildroot 生成文件是否有变更需同步到自定义文件。

## 27.2 迁移到 2016.11

2016.11 之前只能同时使用一个 br2-external 树。2016.11 起可同时用多个（详见[9.2节，Buildroot 外部自定义（Keeping customizations outside of Buildroot）](https://buildroot.org/downloads/manual/manual.html#outside-br-custom)）。

因此旧 br2-external 树不能直接用。需做如下小改动：为 br2-external 树添加名称。

操作如下：

- 在 br2-external 树根目录新建 `external.desc` 文件，内容为一行，定义树名：

  ```
  $ echo 'name: NAME_OF_YOUR_TREE' >external.desc
  ```

  **注意**：名称需唯一，仅可用 `[A-Za-z0-9_]` 字符。

- 替换 br2-external 树中所有 `BR2_EXTERNAL` 为新变量：

  ```
  $ find . -type f | xargs sed -i 's/BR2_EXTERNAL/BR2_EXTERNAL_NAME_OF_YOUR_TREE_PATH/g'
  ```

现在你的 br2-external 树可用于 2016.11 及以后版本。

**注意**：此更改会导致 br2-external 树无法用于 2016.11 之前版本。

## 27.3 迁移到 2017.08

2017.08 之前，host 包安装在 `$(HOST_DIR)/usr`（如 autotools 的 `--prefix=$(HOST_DIR)/usr`）。2017.08 起直接安装到 `$(HOST_DIR)`。

如包安装的可执行文件链接了 `$(HOST_DIR)/lib` 下的库，必须有指向该目录的 RPATH。

RPATH 指向 `$(HOST_DIR)/usr/lib` 不再被接受。

## 27.4 迁移到 2023.11

2023.11 之前，subversion 下载后会无条件获取外部引用（`svn:externals` 属性对象）。2023.11 起默认不再获取，如需请设 `LIBFOO_SVN_EXTERNALS=YES`。这意味着：

- 生成的归档内容可能变化，需相应更新 hash；
- 归档版本后缀更新为 `-br3`，hash 文件需相应更新。

2023.11 之前可用架构特定补丁（如 `0001-some-changes.patch.arm` 仅对该架构生效）。2023.11 起不再支持此机制，此类补丁不会被应用。

如仍需架构特定补丁，可提供[预补丁钩子（pre-patch hook）](https://buildroot.org/downloads/manual/manual.html#hooks)，如：

```
define LIBFOO_ARCH_PATCHES
    $(foreach p,$(wildcard $(LIBFOO_PKGDIR)/*.patch.$(ARCH)), \
        cp -f $(p) $(patsubst %.$(ARCH),%,$(p))
    )
endef
LIBFOO_PRE_PATCH_HOOKS += LIBFOO_ARCH_PATCHES
```

注意 Buildroot 官方包没有架构特定补丁，此类补丁一般不会被接受。

## 27.5 迁移到 2024.05

下载后端有多项扩展：

- 所有本地生成的 tarball 更加可复现。2024.05 前，归档中文件访问权限可能因下载目录 ACL（如 `default` ACL）不同而不一致，影响 git、subversion、cargo、go 包归档。
- git 下载后端现在会正确展开 `export-subst` [git 属性](https://git-scm.com/docs/gitattributes)。
- 归档需用新版 `tar`（1.35），该版本更改了部分字段（`devmajor`、`devminor`）的存储方式，影响归档元数据（文件内容不变）。

因此归档后缀有如下变更：

- git：`-git4`
- subversion：`-svn5`
- cargo（rust）包：`-cargo2`
- go 包：`-go2`

如归档有多个前缀（如 cargo 包用 git 下载），需都加，顺序为下载机制前缀在前，如：`libfoo-1.2.3-git4-cargo2.tar.gz`。

因此自定义包或内核/引导程序的 hash 文件需更新。可用如下 sed 脚本自动重命名（假设 hash 文件用 git 管理）：

```
# git、svn 包，原后缀为 -br2、-br3
sed -r -i -e 's/-br2/-git4/; s/-br3/-svn5/' $(
    git grep -l -E -- '-br2|-br3' -- '*.hash'
)

# go 包，原无后缀
sed -r -i -e 's/(\.tar\.gz)$/-go2\1/' $(
    git grep -l -E '\$\(eval \$\((host-)?golang-package\)\)' -- '*.mk' \
    |sed -r -e 's/\.mk$/.hash/' \
    |sort -u
)

# cargo 包，原无后缀
sed -r -i -e 's/(\.tar\.gz)$/-cargo2\1/' $(
    git grep -l -E '\$\(eval \$\((host-)?cargo-package\)\)' -- '*.mk' \
    |sed -r -e 's/\.mk$/.hash/' \
    |sort -u
)
```

注意 hash *必然*已变，需手动更新。

## 27.6 迁移到 2025.02

Mender 现在要求在 `/var/lib/mender` 放置特殊 bootstrap artifact，替代原 `artifact_info` 文件。该 artifact 用 host-mender-artifact 生成。见 `board/mender/x86_64/post-image-efi.sh` 示例。更多信息见[发布说明](https://docs.mender.io/release-information/release-notes-changelog/mender-client#mender-3-5-0-1)的 features 部分。

## 27.7 迁移到 2025.05

2025.05 起，SYS-V 类系统（busybox、sysvinit、openrc）中 `/etc/resolv.conf` 的符号链接指向 `/run/resolv.conf`，不再指向旧的 `/tmp`。自定义 fstab 的用户需确保 `/run` 在 resolv.conf 创建前可写（通常通过 fstab 条目或启动脚本）。

systemd 系统不受影响：systemd 总会确保 `/run` 可写，且 systemd-resolved 早已将 `/etc/resolv.conf` 指向 `/run`。

Rust 升级到 1.84.0 以上后，Cargo.lock 文件变为强制，且 `.cargo/config` 改为 `.cargo/config.toml`，由 Cargo 获取的包的 tarball 也变了。因此此类 tarball 后缀由 `-cargo2` 改为 `-cargo4`。



