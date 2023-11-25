#include <stdio.h>
#include <time.h>
#include <unistd.h>
void main() {
  // p1: child write byte to father
  // p2: father write byte to child
  int p1[2];
  int p2[2];
  char *buf1;
  char *buf2;

  pipe(p1);
  pipe(p2);
  if (fork() == 0) {
    write(p1[1], "2", 1);
    while (1) {
      if (read(p2[0], buf1, 1)) {
        write(p1[1], buf1, 1);
      }
    }
  } else {
    while (1) {
      if (read(p1[0], buf2, 1)) {
        write(p2[1], buf2, 1);
      }
    }
  }
}
