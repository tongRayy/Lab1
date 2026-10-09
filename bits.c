/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 杨睿童 25800190030 
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
	return ~(~x & ~y) & ~(x & y);
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
  return (x >> 31) & (~x + 1);
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
  int src_byte = x >> (src << 3) & 0xFF;
  int dst_byte = ~(0xFF << (dst << 3)) & x;
  return dst_byte | src_byte << (dst << 3);
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
  int mask = ~(((1 << 31) >> n) << 1);
  return mask & (x >> n);
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
  int mask = 0xFF ^ (0xFF << 4);
  mask = mask | mask << 16;
  x = (x & m) << 4 | (x & ~m) >> 4;
  return x;
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
  int first = ~x & (x + 1);
  x = x | first;
  int second = ~x & (x + 1);
  return x;
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
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return ~x & 1;
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
  n = n & 31;
  int mask = ~(((1 << 31) >> n) >> 1);
  int right = x >> n & mask;
  int left = x << (~n + 1) & 31;
  return left | right;
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
  int pow2 = 1 << n;
  int low_mask = pow2 + ~0;
  int r = x & low_mask;
  int half = pow2 >> 1;
  int is_half = !(r ^ half);
  int y = x >> n;
  int y_odd = y & 1;
  int adjust = is_half & !y_odd;
  int y_prime = (x + half) >> n;
  int result_y = y_prime + (~adjust + 1);
  return result_y << n;
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
  int mid = (x & y) + ((x ^ y) >> 1);
  int is_odd = (x ^ y) & 1;

  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int diff_sign = sign_x ^ sign_y;

  int x_minus_y = x + ~y + 1;
  int same_sign_ge = !(x_minus_y >> 31);
  int diff_sign_ge = !sign_x;

  int x_ge_y = (diff_sign & diff_sign_ge) | (~diff_sign & same_sign_ge);

  return mid + (is_odd & x_ge_y);
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
  int sign = 1 << 31;
  int xp = x ^ sign;
  int ap = a ^ sign;
  int bp = b ^ sign;

  // a <= x
  int diff_ax = ap + ~xp + 1;
  int lt_ax = (diff_ax >> 31) & 1;
  int eq_ax = !(a ^ x);
  int le_ax = lt_ax | eq_ax;

  // x <= b
  int diff_xb = xp + ~bp + 1;
  int lt_xb = (diff_xb >> 31) & 1;
  int eq_xb = !(x ^ b);
  int le_xb = lt_xb | eq_xb;

  // b <= x
  int diff_bx = bp + ~xp + 1;
  int lt_bx = (diff_bx >> 31) & 1;
  int eq_bx = !(b ^ x);
  int le_bx = lt_bx | eq_bx;

  // x <= a
  int diff_xa = xp + ~ap + 1;
  int lt_xa = (diff_xa >> 31) & 1;
  int eq_xa = !(x ^ a);
  int le_xa = lt_xa | eq_xa;

  int cond1 = le_ax & le_xb;
  int cond2 = le_bx & le_xa;
  return cond1 | cond2;
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
  int sign = x >> 31;
  int abs_x = (x + sign) ^ sign;
  int thresh = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | 0x99; // 0x19999999
  int diff = abs_x + ~thresh + 1;
  int overflow = !((diff >> 31) | (!diff));

  int sign_bit = 1 << 31;
  int max = ~sign_bit;
  int min = sign_bit;
  int sat = (sign & min) | (~sign & max);

  int result = (x << 2) + x;
  int ov_mask = ~overflow + 1;
  return (ov_mask & sat) | (~ov_mask & result);
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
  int kx = (x >> 31) & 1;
  int ky = (y >> 31) & 1;
  int kz = (z >> 31) & 1;
  int K = kx + ky + kz;

  int s1 = x + y;
  int c1 = ((x & y) | ((x | y) & ~s1)) >> 31 & 1;
  int s2 = s1 + z;
  int c2 = ((s1 & z) | ((s1 | z) & ~s2)) >> 31 & 1;
  int C = c1 + c2;

  int D = C + (~K + 1);
  int D_neg = D >> 31;
  int D_zero = !D;
  int D_pos = !D_neg & !D_zero;

  int s2_sign = (s2 >> 31) & 1;

  int pos = D_pos | (D_zero & s2_sign);
  int D_plus_1 = D + 1;
  int D_is_minus_1 = !D_plus_1;
  int D_le_minus_2 = D_neg & !D_is_minus_1;
  int neg = D_le_minus_2 | (D_is_minus_1 & !s2_sign);

  return pos + (~neg + 1);
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
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 255) {
        return uf;
    }

    if (exp == 0 && frac == 0) {
        return uf;
    }

    unsigned mant;
    int E;
    if (exp == 0) {
        mant = frac;
        E = -126;
    } else {
        mant = (1 << 23) | frac;
        E = exp - 127;
    }

    unsigned V = mant * 3;

    int p = 31;
    while (p >= 0 && !(V & (1u << p))) {
        p--;
    }

    int E_new = E + p - 24;
    int exp_new = E_new + 127;

    if (exp_new >= 255) {
        return sign | 0x7F800000;
    }

    unsigned frac_new;
    if (exp_new > 0) {
        int shift = p - 23;
        unsigned high = V >> shift;
        frac_new = high & 0x7FFFFF;

        if (shift > 0) {
            unsigned dropped = V & ((1u << shift) - 1);
            unsigned half = 1u << (shift - 1);
            if (dropped > half || (dropped == half && (frac_new & 1))) {
                frac_new++;
                if (frac_new == 0x800000) {
                    frac_new = 0;
                    exp_new++;
                    if (exp_new >= 255) {
                        return sign | 0x7F800000;
                    }
                }
            }
        }
    } else {
        frac_new = (V >> 1) + ((V & 1) & ((V >> 1) & 1));
        exp_new = 0;
    }

    return sign | (exp_new << 23) | frac_new;
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
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 255) return uf;
    if (exp == 0 && frac == 0) return uf;

    if (exp < 127) {
        if (exp < 126) {
            return sign;
        } else {
            if (frac == 0) {
                return sign;
            } else {
                return sign | 0x3F800000;
            }
        }
    }

    int E = exp - 127;
    if (E >= 23) return uf;

    unsigned M = (1 << 23) | frac;
    int shift = 23 - E;
    unsigned I = M >> shift;
    unsigned F = M & ((1 << shift) - 1);
    unsigned half = 1 << (shift - 1);

    if (F > half || (F == half && (I & 1))) {
        I++;
    }

    int p = 31;
    while (p >= 0 && !(I & (1u << p))) {
        p--;
    }

    if (p == 23) {
        return sign | (150 << 23);
    } else {
        unsigned new_exp = 127 + p;
        unsigned new_frac = (I << (23 - p)) & 0x7FFFFF;
        return sign | (new_exp << 23) | new_frac;
    }
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
  if (x == 0) return 0;

  unsigned sign = x & 0x80000000;
  unsigned abs_x;
  if (x < 0) {
    abs_x = -((unsigned)x);
  } else {
    abs_x = (unsigned)x;
  }

  int e = 0;
  unsigned temp = abs_x;
  while (temp > 1) {
    temp >>= 1;
    e++;
  }

  unsigned exp = e + 127;
  unsigned mantissa;

  if (e <= 23) {
    mantissa = (abs_x << (23 - e)) & 0x7FFFFF;
  } else {
    int shift = e - 23;
    unsigned high = abs_x >> shift;
    unsigned m = high & 0x7FFFFF;
    unsigned mask = (1 << shift) - 1;
    unsigned dropped = abs_x & mask;
    unsigned half = 1 << (shift - 1);

    if (dropped > half || (dropped == half && (m & 1))) {
      m++;
      if (m == 0x800000) {
        m = 0;
        exp++;
      }
    }
    mantissa = m;
  }

  return sign | (exp << 23) | mantissa;
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
  int m1 = 0x55 | (0x55 << 8);      // 0x00005555
  m1 = m1 | (m1 << 16);             // 0x55555555

  int m2 = 0x33 | (0x33 << 8);      // 0x00003333
  m2 = m2 | (m2 << 16);             // 0x33333333

  int m4 = 0x0F | (0x0F << 8);      // 0x00000F0F
  m4 = m4 | (m4 << 16);             // 0x0F0F0F0F

  int m8 = 0xFF | (0xFF << 16);     // 0x00FF00FF
  int m16 = 0xFF | (0xFF << 8);     // 0x0000FFFF

  int count = (x & m1) + ((x >> 1) & m1);
  count = (count & m2) + ((count >> 2) & m2);
  count = (count + (count >> 4)) & m4;
  count = (count + (count >> 8)) & m8;
  count = (count + (count >> 16)) & m16;
  return count;
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
int bitReverse(int x)
{
  int mask = (0xFF << 8) | 0xFF;

  x = ((x >> 16) & mask) | (x << 16);

  mask = mask ^ (mask << 8);
  x = ((x >> 8) & mask) | ((x & mask) << 8);

  mask = mask ^ (mask << 4);
  x = ((x >> 4) & mask) | ((x & mask) << 4);

  mask = mask ^ (mask << 2);
  x = ((x >> 2) & mask) | ((x & mask) << 2);

  mask = mask ^ (mask << 1);
  x = ((x >> 1) & mask) | ((x & mask) << 1);

  return x;
}
}
