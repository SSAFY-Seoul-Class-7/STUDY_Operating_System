  1  public class InliningChains
  2  {
  3      public static void main(String[] args)
  4      {
  5          new InliningChains();
  6      }
  7  
  8      public InliningChains()
  9      {
 10          long count = 0;
 11  
 12          for (int i = 0; i < 100_000; i++)
 13          {
 14              count = chainA1(count);
 15              count = chainB1(count);
 16          }
 17  
 18          System.out.println("InliningChains: " + count);
 19      }
 20  
 21      private long chainA1(long count)
 22      {
 23          return 1 + chainA2(count);
 24      }
 25  
 26      private long chainA2(long count)
 27      {
 28          return 2 + chainA3(count);
 29      }
 30  
 31      private long chainA3(long count)
 32      {
 33          return 3 + chainA4(count);
 34      }
 35  
 36      private long chainA4(long count)
 37      {
 38          // last link will not be inlined
 39          return bigMethod(count, 4);
 40      }
 41  
 42      private long chainB1(long count)
 43      {
 44          return chainB2(count) - 1;
 45      }
 46  
 47      private long chainB2(long count)
 48      {
 49          return chainB3(count) - 2;
 50      }
 51  
 52      private long chainB3(long count)
 53      {
 54          return count - 3;
 55      }
 56  
 57      private long bigMethod(long count, int i)
 58      {
 59          long a, b, c, d, e, f, g;
 60  
 61          a = count;
 62          b = count;
 63          c = count;
 64          d = count;
 65          e = count;
 66          f = count;
 67          g = count;
 68  
 69          a += i;
 70          b += i;
 71          c += i;
 72          d += i;
 73          e += i;
 74          f += i;
 75          g += i;
 76  
 77          a += 1;
 78          b += 2;
 79          c += 3;
 80          d += 4;
 81          e += 5;
 82          f += 6;
 83          g += 7;
 84  
 85          a += i;
 86          b += i;
 87          c += i;
 88          d += i;
 89          e += i;
 90          f += i;
 91          g += i;
 92  
 93          a -= 7;
 94          b -= 6;
 95          c -= 5;
 96          d -= 4;
 97          e -= 3;
 98          f -= 2;
 99          g -= 1;
100  
101          a++;
102          b++;
103          c++;
104          d++;
105          e++;
106          f++;
107          g++;
108  
109          a /= 2;
110          b /= 2;
111          c /= 2;
112          d /= 2;
113          e /= 2;
114          f /= 2;
115          g /= 2;
116  
117          long result = a + b + c + d + e + f + g;
118  
119          return result;
120      }
121  }
