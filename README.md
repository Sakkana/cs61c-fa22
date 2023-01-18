# CS61C 学习笔记


## Discussion

### 1: Number Representation

#### 1 Pre-Check

**Depending on the context, the same sequence of bits may represent different things.**

正确。同一位模式可能代表不同的含义，比如补码下的负数会和无符号数编码相同，如四位编码下的 `1111` 可能代表 -1，也可能代表 15。而浮点数按照 IEEE 754 编码也有他自己的解释方式。



**It is possible to get an overflow error in Two’s Complement when adding numbers of opposite signs.**

错误。在补码模式下正数和负数相加并不会溢出。

补码下，数值的取值范围是 [-2<sup>n - 1</sup>, 2<sup>n - 1</sup> - 1$]。只有在上界做加法，下界做减法才会溢出。



**If you interpret a N bit Two’s complement number as an unsigned number, negative numbers would be smaller than positive numbers.**

错误。正数的范围是 [0, 2<sup>n - 1</sup> - 1]，位模式是 [`0`000...0000, `0`111...111]。

而负数的取值是 [2<sup>n - 1</sup>, -1]，位模式是 [`1`000...0000, `1`111...1111]。

因此将一个用补码表示的负数强转成 `unsigned` 之后会比正数大。



**If you interpret an N bit Bias notation number as an unsigned number (assume there are negative numbers for the given bias), negative numbers would be smaller than positive numbers.**

正确。一般这个偏置会选择 2<sup>n</sup>。如此一来，最小的负数 -2<sup>n</sup> 会被编码成全 0，相当于整个数轴都向右移动 2<sup>n</sup> 位（十进制）。

因此，整个域都被平移到了[0, +∞]。可以直接比较两个数的大小，而不用考虑符号。



**We can represent fractions and decimals in our given number representation formats (unsigned, biased, and Two’s Complement).**

错误。这些编码只规定了定点整数的编码方式。后面会用浮点数的表示方式来表示分数。



#### 2 Unsigned Integers

###### 2.1 binary, decimal, and hex 相互转化。

1、

b: 0b1001_0011

h: 0x93

d: 9 * 16 + 3 = 147



2、

d: 63

b: 0b0100_0000 - 1 = 0x0011_1111

h: 0x3f



3、

b: 0b0010_0100

h: 0x24

d: 2 * 16 + 4 = 36



4、

d: 0

b: 0b0

h: 0x0



5、

d: 437

h: 437 = 1 * 16 * 16 + 11 * 16 + 5 = 0x1b5

b: 0b0001_1011_0101



6、

h: 0x0123

b: 0b0000_0001_0010_0011

d: 1 * 256 + 2 * 16 + 3 = 291



7、

0xD3AD = 0b1101_0011_1010_1101

0xB33F = 0b1011_0011_0011_1111

0x7EC4 = 0b0111_1110_1010_0100



##### 2.2 IEC prefixing system


![](https://pic.imgdb.cn/item/63c6c9a7be43e0d30eca760a.jpg)

(a)

2<sup>16</sup> = 64 K

2<sup>27</sup> = 128 M

2<sup>43</sup> = 8 T

2<sup>36</sup> = 64 G

2<sup>34</sup> = 16 G

2<sup>61</sup> = 2 E

2<sup>47</sup> = 128 T

2<sup>59</sup> = 512 P



(b)

2 K = 2<sup>11</sup>

512 K = 2<sup>19</sup>

16 M = 2<sup>24</sup>

256 P = 2<sup>58</sup>

64 G = 2<sup>36</sup>

128 = 2<sup>67</sup>



##### 3 Signed Integers

我发现国外的移码和国内的表示不太一样，我是按照 hust 谭志虎的教材来写的。

![](https://pic.imgdb.cn/item/63c6cb9abe43e0d30ece8703.jpg)



![](https://pic.imgdb.cn/item/63c6cbb1be43e0d30ecebc9c.jpg)



(a) What is the largest integer? What is the result of adding one to that number? 

1. Unsigned?	 2<sup>n</sup> - 1 = 2<sup>8</sup> - 1 = 255, 0
2. Biased?  [-128, 127], max: 127, -128
3. Two’s Complement? 2<sup>n - 1</sup> - 1, 127, -128



 (b) How would you represent the numbers 0, 1, and -1? 

1. Unsigned?	`0000...0000`, `0000...0001`, ×
2. Biased?  `1000...0000`, `1000...0001`, `0111...1111`
3. Two’s Complement?  `0000...0000`, `0000...0001`, `1111...1111`



(c) How would you represent 17 and -17? 

1. Unsigned?  `01_0001`, `11_0001`
2. Biased?  `11_0001`, `00_1111`

3. Two’s Complement? `01_0001`,  `10_1111`



##### 4 Arithmetic and Counting

![](https://pic.imgdb.cn/item/63c6d7eabe43e0d30ee79795.jpg)



(a) Compute the decimal result of the following arithmetic expressions involving `6-bit Two’s Complement numbers` as they would be calculated on a computer. Do any of these result in an overflow? Are all these operations possible? 

6 位补码能表示的范围是 [-64, 63]

1. 0b01_1001 − 0b01_0111 = 0b00_0010 = 18 不会溢出
2. 0b10_0011 + 0b11_1010  = 0b101_1101 = 93 会溢出 -> 0b01_1101 = 29
3. 0x3B + 0x06 = 0x41 = 65 会溢出 -> 0x41 = 0b0100_0001 -> 0b00_0001 = 1 = (-5 + 6)
4. 0xFF − 0xAA = 0x55 = 85 会溢出 -> 0b101_0101 -> 0b01_0101 = 21，大意了没有闪，这是不可能的，因为 ff 需要 8 位，但是最多只有 6 位...
5. 0b00_0100 − 0b00_1000 = 0b11_1100 = -4 不会溢出



(b) What is the least number of bits needed to represent the following ranges using any number representation scheme? 

1. 0 to 256：2<sup>8</sup> = 256，但实际上 8 位只能表示 [0, 257]，因此需要 9 位
2. -7 to 56 ：2<sup>6</sup> = 64，-7 ~ 56 一共 64 个数字
3. 64 to 127 and -64 to -127：一共  128 个数字，需要 7 位
4. Address every byte of a 12 TiB chunk of memory，1 T = 10<sup>40</sup> ，12 需要 4 位，因此需要 44 位



(c) How many distinct numbers can the following schemes represent? How many distinct positive numbers?

1. 10-bit unsigned ：2<sup>10</sup> = 1024，一共可以表示 1024 个状态，范围是[0, 1023]，最大数字是 1023
2. 8-bit Two’s Complement ：[-128, 127]，可以表示 2<sup>8</sup> = 256 个状态，最大数字是 127
3. 8-bit One’s Complement ：[-127， 127]，除了符号位逐位取反，和原码的表示范围一样，能表示 256 种状态，最大数字是 127
4. 6-bit biased, with a bias of -30 ：6-bit  可以表示 64 种状态，[0, 63]，偏移 30 后，范围是 [-34, 33]，最大数字是 33，这是用 00_0000 来表示 -34，用 11_1111 来表示 33。
5. 10-bit sign-magnitude：[10_0000_0000, 01_1111_1111]，2<sup>10</sup> 可以表示 1024 种状态，但是实际上有两个 0，因此只能表示 1023 个数字，最大值为 511



在学 LEC 08 Data Transfer 的时候最后放了两个题目。

1. What is in x12 ?

> addi x11, x0, 0x93F5
>
> sw x11, 0(x5)
>
> lb x12, 1(x15)

首先，将 0x93f5 和恒零寄存器中的 0 相加，存储到 x11 中。

然后将 x11 中的这个数字存储到 [x5] 起始的地址处。

于是，就有了这样的内存布局：

| 0x00  | 0x00  | 0x93  |     0xf5     |
| :---: | :---: | :---: | :----------: |
| addr3 | addr2 | addr1 | addr0 ([x5]) |

从 x15 起始的地址开始，偏移 1 byte，可以拿到 0x93，放入 x12 的低 8 bits 处。

由于 0x93 是 0b1001_0011，最高位是 1，因此符号扩展像刷酱一样将 x12 的高 3 byte 都刷成 1.

于是 x12 存储的是 0xffffff93。



2. translate `*x = *y` to risc-v assembly. x in x3, y in x5, tempory x8.

我是这么考虑的，The memory access instructions transfer data between a register and a memory location，因此必然要先把数据从 y 指向的内存读入到寄存器中，因此要使用 lw。然后再存储到 x 指向的内存，需要使用 sw0。

>ld x8, 0(x5)
>
>sw x8, 0(x3)

不知道对不对。
对了。



### Discussion 3: Floating Point

#### 1 Pre-Check

##### Memory sectors are defined by the hardware, and cannot be altered.

错误。

硬件提供一个可以擦写的 DRAM 作为内存，对于 CPU 来说他只是一个 value = f(address) 或者 f(address) = value 的读写映射。

内存中的地址分配，区域分配（stack, heap, free, garbage）等是由操作系统统一管理的，其每个块的解释是可变的。



##### For large recursive functions, you should store your data on the heap over the stack.

正确。

大型的递归调用会将许多上下文（返回地址，函数参数，局部变量等）放置在栈上，大量的递归会引起堆栈溢出的问题。

❌

大然居然是错误。

他说如果要不同的函数调用之间通信用堆比较好，但是如果递归函数使用堆很容易导致 malloc 大量内存和内存不足。



##### The goals of floating point are to have a large range of values, a low amount of precision, and real arithmetic results.

正确。

浮点数的阶码 Exponent 可以在很大的范围内伸缩，扩大或者缩小尾数的增长步长，并且可以表示 +∞，-∞以及 NaN。

他会尽最大可能保留精度，可以精确到小数点后很多位，但是不能完全准确表示一个数字。

我也不知道为什么答案说这是正确的，浮点数不是存在精度问题吗，虽然可以精确逼近，但是不能完全一样？



##### The distance between floating point numbers increases as the absolute value of the numbers increase.

正确。

> LSB: Least Significant Bit
>
> MSB: MOst Significant Bit

浮点数的增长是阶码来决定。

浮点数分为规格化数和非规格化数。

非规格化数字可以表示很精细的粒度。

尾数有 23 位数，每一位的权重是 [2<sup>-1</sup>, 2<sup>-22</sup>]。

因此如果 E = 0，那么这个浮点数的增长步长为 2^-23。但是答案说这里是-22，先存疑。



##### Floating Point addition is associative.

没看懂。

错误。浮点数加法不满足结合律。

浮点数是近似某个数字，因为每个浮点数都有自己的 Exponent，他们的步长间隔是不一样的。



#### 2 Memory Management

C 语言内存分为两个 static 区域和两个 dynamic 区域。

static: Stack, Heap

dynamic: data, text



##### For each part, choose one or more of the following memory segments where the data could be located: code, static, heap, stack.

(a) Static variables -> data

(b) Local variables -> stack

(c) Global variables -> data

(d) Constants -> data，答案上还有 stack 和 code

像这种情况，y = 5 可以被直接编译进指令中，因此存放在 code 里面

```c
1 #define y 5
2
3 int plus_y(int x) {
4 	x = x + y;
5 	return x;
6 }
```



而这种全局定义的常量会放在 static data 里面

```c
const int x = 1;
```



(e) Machine Instructions -> code

(f) Result of Dynamic Memory Allocation(malloc or calloc) -> heap

(g) String Literals -> data



##### Write the code necessary to allocate memory on the heap in the following scenarios

(a) An array arr of `k` integers

```c
int *arr = (int*)malloc(sizeof(int) * k);
```



(b) A string `str` containing `p` characters 

```c
char *str = (char*)malloc(sizeof(char) * (p + 1));	// 最后要放 \0
```



(c) An `n × m` matrix mat of integers initialized to zero.

```c
// 1
int *matrix = (int*)malloc(sizeof(int) * n * m);
for (int i = 0; i < m * n; ++ i) {
    matrix[i] = 0;
}

// 2
int *matrix = (int*)calloc(m, sizeof(int*));	// 先创建 m 个 row 指针
for (int i = 0; i < m; ++ i) {
    matrix[i] = (int*)calloc(n, sizeof(int));	// 每个 row 都创建一个长度为 n 的数组
}
```



##### Compare the following two implementations of a function which duplicates a string. Is either one correct? Which one runs faster? 

![](https://pic.imgdb.cn/item/63c7e3d3be43e0d30eabf52e.jpg)



第一个没有进行初始化，因此最后一个字节不一定是 \0。

修复：

```c
new_str[n + 1] = '\0';
```

第一个更快，因为 calloc 还要进行初始化为 0 的操作。第一个是 O(1)，只需要标记分配返回就可以了。第二个是 O(n)，他要遍历每一个元素去赋值为 0.



##### What’s the main issue with the code snippet seen here? (Hint: gets() is a function that reads in user input and stores it in the array given in the argument.)

![](https://pic.imgdb.cn/item/63c7e46bbe43e0d30ead1eec.jpg)



gets 是个危险函数，他不会检查用户输入的长度。

64 个字节大小的 buffer 只能写入 63 个字符，最后一个设置为 \0。

如果用户的输入大于 63，会造成缓冲区溢出。

而且不推荐在栈上面创建数组，一方面是可能引用已经无效的野指针，一方面是数组太长会导致后面栈溢出。



> 3 是链表 跳过了



#### 4 Floating Point

##### Convert the following single-precision floating point numbers from binary to decimal or from decimal to binary. You may leave your answer as an expression.

<img src="https://pic.imgdb.cn/item/63c7eddbbe43e0d30ebc4310.jpg" style="zoom:50%;" />



<img src="https://pic.imgdb.cn/item/63c7edecbe43e0d30ebc63d8.jpg" style="zoom:50%;" />



#### 5 More Floating Point Representation

##### What is the next smallest number larger than 2 that can be represented completely?

首先，尾数代表了小数点后的有效值。

因此，这个数值必然是 1.M x 2<sup>E - 127</sup> 的形式。

既然要接近 2，那么这个指数必然不能特别大，但是要大于 0，这样才会大于 1.M，更加接近2.

假如指数是 0，那么正好就是 1.M。

加入指数是 1，那么这个数字就是 1.M x 2 = 2.M + 0.M。

这个应该就是最最近 2 的数字了。

因此，只要找到最小的 M，就可以满足 2.M + M > 2 并且最接近 2。

最小的 M 是取 23 位尾数的 LSB = 1，该位的权重是 2<sup>-23</sup>。

因此最终答案是 2 + 2<sup>-23</sup> + 2<sup>-23</sup>= 2 + 2<sup>-22</sup>。



##### What is the next smallest number larger than 4 that can be represented completely?

>  同上，要找到一个数字小于 4，但是最接近 4。
>
> 1.M x 2<sup>2</sup> = 4 + 0.M x 4。这超出了 4，因此指数只能是 1。
>
> 因此，这个数字必然是 1.M x 2 的形式，也就是和上面一样，2.M + M。
>
> 这么一加起来必然是 3.X，这样子才能更加接近 4。
>
> 因此，我们选定了 E - 127 = 1，E = 128，剩下的就是在 M 上做功夫了。
>
> 直接取 M = 全 1。

呃呃呃看错题目了，还是得求大于 4 的。

1.M x 2<sup>2</sup> = 4 + 0.M x 4。这超出了 4，因此只要找个最小的 0.M，这样子 0.M x 4 就不会偏移太多。

还是取 M = 2<sup>-23</sup>，最终的答案就是 4 + 2<sup>-23</sup> x 4 = 4 + 2<sup>-21</sup>。



##### What is the largest odd number that we can represent? Hint: Try applying the step size technique covered in lecture?

最大的奇数，就是最大的偶数 - 1.

偶数，就是 2 的倍数。

想要以步长为 2 增长，就需要 2<sup>-23</sup> x 2<sup>E - 127</sup> = 2，满足步长为 2，后面都是以 2 为步长增长了。

因此，E - 150 = 1, E = 151。

于是得到了该模式下的伸缩因子，也就是阶码。

可以知道，最大的奇数便是 2<sup>24</sup> - 1。


### Lab





### Homework





### Project
