/* 
 * CS:APP Data Lab 
 * 
 * Mount-B / 25300680098
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* 1 左移 31 位即为最高位为 1 的掩码 */
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	/* 用德摩根律把异或写成只用 ~ 和 & 的形式：x^y = ~(~(x&~y) & ~(~x&y)) */
	return ~(~(x & ~y) & ~(~x & y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* 算术右移得到符号掩码（负数全 1，非负全 0），再与 -x 相与 */
  int sign = x >> 31;
  return (~x + 1) & sign;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* 取出 src 字节，清空 dst 字节对应的位，再把取出的字节放进去 */
  int s = src << 3;
  int d = dst << 3;
  int byte = (x >> s) & 0xFF;
  int mask = ~(0xFF << d);
  return (x & mask) | (byte << d);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* 算术右移后用掩码把高 n 位抹掉：~(1<<31>>n<<1) 的低 32-n 位为 1 */
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* 先构造 0x0F0F0F0F 掩码，再把低半字节左移 4 位、高半字节右移 4 位后合并 */
  int mask = 0x0F | (0x0F << 8);
  mask = mask | (mask << 16);
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* ~x & (x+1) 取最低的 0 位；把它补成 1 后再取一次最低的 0 位即为次低的 0 位 */
  int low = ~x & (x + 1);
  int y = x | low;
  return ~y & (y + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* 逐步折半异或，最终最低位是全部位的异或（即 1 的个数的奇偶性），再取反 */
  int a = x ^ (x >> 16);
  int b = a ^ (a >> 8);
  int c = b ^ (b >> 4);
  int d = c ^ (c >> 2);
  int e = d ^ (d >> 1);
  return ~e & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* n 对 32 取模；右移部分必须用掩码去掉算术右移带进来的符号位，
     再把低位移出的部分用左移 (32-n) 位补到高位 */
  int m = n & 31;
  int s = (33 + ~m) & 31;
  int mask = ~(((1 << 31) >> m) << 1);
  return (x << s) | ((x >> m) & mask);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* 加 (2^(n-1) - 1) 再按“商的奇偶性”决定是否进位，实现四舍六入五成双 */
  int q = x >> n;
  int odd = q & 1;
  int half = 1 << (n + ~0);
  return ((x + half + ~0 + odd) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* floor 用 (x&y)+((x^y)>>1) 精确计算；只有和为奇数时才需要判断往哪边取整，
     此时用带溢出修正的符号判断 x 与 y 的大小 */
  int xy = x ^ y;
  int fl = (x & y) + (xy >> 1);
  int d = x + ~y + 1;
  int sx = x >> 31;
  int sy = y >> 31;
  int sd = d >> 31;
  int of = (sx ^ sy) & (sx ^ sd);
  int gt = ~(sd ^ of) & 1;
  return fl + (gt & (xy & 1));
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* 先用带溢出修正的符号比较求出 min/max，再判断 x 是否落在 [lo, hi] 内 */
  int su = a >> 31;
  int sv = b >> 31;
  int d = a + ~b + 1;
  int sd = d >> 31;
  int of = (su ^ sv) & (su ^ sd);
  int lt = sd ^ of;
  int ab = a ^ b;
  int lo = b ^ (ab & lt);
  int hi = a ^ (ab & lt);
  int sx = x >> 31;
  int slo = lo >> 31;
  int d1 = x + ~lo + 1;
  int sd1 = d1 >> 31;
  int of1 = (sx ^ slo) & (sx ^ sd1);
  int t1 = (sd1 ^ of1) & 1;
  int shi = hi >> 31;
  int d2 = hi + ~x + 1;
  int sd2 = d2 >> 31;
  int of2 = (shi ^ sx) & (shi ^ sd2);
  int t2 = (sd2 ^ of2) & 1;
  return !(t1 | t2);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /* x*5 = (x<<2)+x，两步分别判断是否溢出（左移 2 位丢位 / 加法同号异号），
     溢出时按 x 的符号饱和到 INT_MAX 或 INT_MIN */
  int t = x << 2;
  int r = t + x;
  int no1 = !((t >> 2) ^ x);
  int no2 = !(((t ^ r) & (x ^ r)) >> 31);
  int ovf = !(no1 & no2);
  int sg = x >> 31;
  int sat = ~(1 << 31) + (sg & 1);
  int msk = ~ovf + 1;
  return (sat & msk) | (r & ~msk);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* 把结果表示为 32 位回绕值 + 进位个数*2^32：分两次做加法，各自记录进位
     (+1/0/-1)，总进位为 0 说明落在 int 范围内，为正说明上溢，为负说明下溢 */
  int r1 = x + y;
  int ovf1 = ((x ^ r1) & (y ^ r1)) >> 31;
  int m1 = ovf1 & 1;
  int sg1 = x >> 31;
  int cp1 = m1 & (~sg1 & 1);
  int cn1 = m1 & sg1 & 1;
  int c1 = cp1 + ~cn1 + 1;
  int r2 = r1 + z;
  int ovf2 = ((r1 ^ r2) & (z ^ r2)) >> 31;
  int m2 = ovf2 & 1;
  int sg2 = r1 >> 31;
  int cp2 = m2 & (~sg2 & 1);
  int cn2 = m2 & sg2 & 1;
  int c2 = cp2 + ~cn2 + 1;
  int c = c1 + c2;
  int nz = !!c;
  int neg = c >> 31;
  int pos = ~neg & nz;
  int negr = neg & nz;
  return pos + (~negr + 1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /* 把 |f| 写成 M*2^(E-150)（M 为 24 位有效数字整数），乘 3/2 后即 P*2^(E-151)，
     其中 P=3M；再按结果是否为规格化数分别做 round-to-nearest-even 的规格化 */
  unsigned s = uf & 0x80000000;
  unsigned e = (uf >> 23) & 0xFF;
  unsigned f = uf & 0x7FFFFF;
  unsigned M, E, P, sh, q, rem, half, Er;
  if (e == 0xFF) return uf;                  /* NaN / Inf */
  if ((e | f) == 0) return uf;               /* ±0 */
  M = f | (e ? 0x800000 : 0);
  E = e ? e : 1;
  P = M + (M << 1);
  if (P < 0x1000000) {                       /* 结果是非规格化数 */
    q = (P + ((P >> 1) & 1)) >> 1;           /* 除以 2 并 round-half-even */
    if (q == 0x800000) return s | 0x800000;  /* 进位成最小规格化数 */
    return s | q;
  }
  sh = (P >= 0x2000000) ? 2 : 1;
  q = P >> sh;
  rem = P & ((1 << sh) - 1);
  half = 1 << (sh - 1);
  if (rem > half) q = q + 1;
  else if (rem == half && (q & 1)) q = q + 1;
  Er = E + sh - 1;
  if (q == 0x1000000) { q = 0x800000; Er = Er + 1; }
  if (Er >= 255) return s | 0x7F800000;      /* 溢出为无穷 */
  return s | (Er << 23) | (q & 0x7FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /* 先取符号/阶码/尾数：非规格化数与零一律舍入为 ±0；阶码 >=150 时本身就是整数；
     否则把隐含 1 补上后右移 (150-e) 位，对移出的部分做 round-half-even，
     最后把得到的整数（<=2^24）规格化成浮点表示 */
  unsigned s = uf & 0x80000000;
  unsigned e = (uf >> 23) & 0xFF;
  unsigned f = uf & 0x7FFFFF;
  unsigned M, shift, Q, rem, half, E;
  if (e == 0xFF) return uf;                  /* NaN / Inf */
  if (e == 0) return s;                      /* |v| < 2^-126，舍入为 ±0 */
  if (e >= 150) return uf;                   /* 已经是整数 */
  M = f | 0x800000;
  shift = 150 - e;
  if (shift >= 25) return s;                 /* 小于 0.5，舍入为 ±0 */
  Q = M >> shift;
  rem = M & ((1 << shift) - 1);
  half = 1 << (shift - 1);
  if (rem > half) Q = Q + 1;
  else if (rem == half && (Q & 1)) Q = Q + 1;
  if (Q == 0) return s;
  if (Q == 0x1000000) Q = 0x800000;
  E = 150;
  while (!(Q & 0x800000)) { Q = Q << 1; E = E - 1; }
  return s | (E << 23) | (Q & 0x7FFFFF);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /* 取绝对值（负数用补码取反加一得到幅值），左移规格化到最高位为 1，
     记录移动次数 t 得到阶码 158-t，再对低 8 位做 round-half-even */
  unsigned s = 0;
  unsigned u = x;
  unsigned E, m, rem;
  int t = 0;
  if (u == 0) return 0;
  if (x < 0) { s = 0x80000000; u = ~u + 1; }
  while (!(u & 0x80000000)) { u = u << 1; t = t + 1; }
  E = 158 - t;
  m = u >> 8;
  rem = u & 0xFF;
  if (rem > 0x80) m = m + 1;
  else if (rem == 0x80 && (m & 1)) m = m + 1;
  if (m == 0x1000000) { m = 0x800000; E = E + 1; }
  return s | (E << 23) | (m & 0x7FFFFF);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 分治统计：用掩码把相邻 1/2/4/8/16 位的计数逐层合并，
     每一步都要把计数限制回各自的字段内（所以 8 位那步也要与掩码） */
  int m1 = 0x55 | (0x55 << 8);
  int m2 = 0x33 | (0x33 << 8);
  int m4 = 0x0F | (0x0F << 8);
  int m8 = 0xFF | (0xFF << 16);
  int m16 = 0xFF | (0xFF << 8);
  int r;
  m1 = m1 | (m1 << 16);
  m2 = m2 | (m2 << 16);
  m4 = m4 | (m4 << 16);
  r = (x & m1) + ((x >> 1) & m1);
  r = (r & m2) + ((r >> 2) & m2);
  r = (r + (r >> 4)) & m4;
  r = (r + (r >> 8)) & m8;
  r = (r + (r >> 16)) & m16;
  return r;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /* 逐层交换：相邻位 -> 相邻 2 位 -> 半字节 -> 字节 -> 16 位半字。
     四个掩码由 0x00FF00FF 逐级推出（0x0F0F = 0xFF ^ 0xFF0，0x33 = 0x0F ^ 0x3C，
     0x55 = 0x33 ^ 0x66）以节省操作数；最后一步的右移同样要掩码去掉符号位 */
  int m8 = 0xFF | (0xFF << 16);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);
  int m16 = (m8 >> 8) | 0xFF;
  x = ((x >> 1) & m1) | ((x & m1) << 1);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 8) & m8) | ((x & m8) << 8);
  x = (x << 16) | ((x >> 16) & m16);
  return x;
}
