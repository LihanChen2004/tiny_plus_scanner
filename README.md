# 实验二 词法分析程序设计

## 1. 实验内容

- TINY 语言的词法由 [TINY_Syntax_ch.md](./tiny_Syntax_ch.md) 描述

- TINY 语言的词法分析器由 [tiny](https://github.com/ejacky/tiny) 的 C 语言代码实现

- TINY+ 语言的词法由 [TINY_plus_Syntax_ch.md](./tiny_plus_Syntax_ch.md) 描述

### 2.1 任务

理解 TINY 语言的词法及词法分析器的实现，并基于该词法分析器，实现拓展语言 TINY+ 的词法分析器。

### 2.2 要求

1. TINY+ 词法分析器以 TINY+ 源代码为输入，输出为识别出的 token 序列

2. 词法分析器以最长匹配为原则，例如 `:=` 应识别为赋值符号而非单独的 `:` 及 `=`

3. Token 以（种别码，属性值）表示，包含以下类型的种别码：

    1. KEY 为关键字

    2. SYM 为系统特殊字符

    3. ID 为变量

    4. NUM 为数值常量

    5. STR 为字符串常量

4. 识别词法错误。词法分析器可以给出词法错误的行号并打印出对应的出错消息，主要包含以下类型的词法错误：

    1. 非法字符。即不属于 TINY+ 字母表的字符，比如 `$` 就是一个非法字符

    2. 字符串匹配错误，比如右部引号丢失，如 `'scanner`

    3. 注释的右部括号丢失或匹配错误，如 `{this is an example`

## 2. 实验要求

- 完成 TINY+ 词法分析程序的编写及测试（使用提供的测试代码或自己编写测试文件）；

- 使用实验所提供的模板撰写实验报告，要求内容详实，有具体的设计、思路描述，关键代码片段及其注释，及实验输入输出屏幕截图；

- 在截止日期前将代码、实验报告、测试文件（如有）等所有实验相关文件都放在一个文件夹下面，并压缩到一个压缩包“学号_姓名_实验二.rar”上传至指定网站。如果提交了多次，请在文件后面加上“更新1，更新2…”

## 3. 本仓库使用说明

在 Ubuntu 22.04 中使用 CMake 构建项目。

1. 编译

    ```zsh
    mkdir build
    cd build
    cmake ..
    make
    ```

2. 运行

    注意修改测试文件的路径

    ```zsh
    ./tiny_plus_scanner /home/lihanchen/compilation_principle/exp_2/tiny_plus_scanner/test/tiny_plus/test1.txt
    ```

实验报告详见：<https://flowus.cn/lihanchen/adb3e04c-3044-4c79-8442-345889580754>
