# TINY+

我们在这里定义了一种名为 TINY+ 的编程语言，它是 TINY 的超集，包含声明、if 语句、do-while 语句、字符串类型等。

## 1. TINY+ 的词法约定

1. 语言的关键字如下：

    ```txt
    true false or  and  not 
    int  bool float double  string
    do  while if  then else end  repeat until read write
    ```

   所有关键字都是保留字，必须用小写字母书写。

2. 特殊符号如下：

    ```txt
    >  <=  >=  != , '  
    { } ; := + - * / ( ) < =
    ```

3. 其他标记是 ID、NUM 和 STRING，它们由以下正则表达式定义：

   - ID = letter (letter | digit)

    标识符是以字母开头，后跟字母和数字

   - NUM = digit digit*

   - STRING = ' any character except ' '

    字符串用单引号括起来，除了单引号外的任何字符都可以出现在字符串中。字符串不能跨行定义。

   - letter = a | ... | z | A | ... | Z

   - digit = 0 | ... | 9

   大小写字母是区分的。

4. 空白字符包括空格、换行符和制表符。空白字符被忽略，但必须分隔 ID、NUM 和关键字。

5. 注释用花括号 {…} 括起来，不能嵌套。注释可以包含多行。

## 2. TINY+ 示例程序

```tiny
string str;
int x, fact;
str := 'sample program in TINY+ language- computes factorial';
read x;
if x > 0 and x < 100 then { don’t compute if x <= 0 }
    fact := 1;
    do
        fact := fact * x;
        x := x - 1;
    while x > 0;
write fact;
end
```
