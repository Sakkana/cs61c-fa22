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



### Lab





### Homework





### Project
