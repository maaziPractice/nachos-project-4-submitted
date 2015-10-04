/* testfiles.c
 *	Simple program to test the file handling system calls
 */

#include "syscall.h"

int main() {
  OpenFileId fd;
  int bytesread;
  char buf[20];

  Exec("../test/matmult",15);
  Exec("../test/sort",12);

}
