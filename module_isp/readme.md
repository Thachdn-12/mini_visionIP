Input:
  - Camera / video

Output:
  - frame_gray (t-1, t)


+------------------+
| Camera / Video   |
+--------+---------+
         ↓
+------------------+
|  ISP (software)  |
| - grayscale      |
| - resize         |
| - blur           |
+--------+---------+
         ↓
   Frame(t-1), Frame(t)