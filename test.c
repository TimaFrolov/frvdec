
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frvdec.h"

static int test(uint32_t inst_raw, const char* exp_fmt) {
  FrvInst inst;
  char fmt[128];
  int retval = frv_decode(sizeof inst_raw, (unsigned char*) &inst_raw, &inst);
  if (retval == FRV_PARTIAL)
    strcpy(fmt, "PARTIAL");
  else if (retval == FRV_UNDEF)
    strcpy(fmt, "UNDEF");
  else
    frv_format(&inst, sizeof fmt, fmt);
  if ((retval < 0 || (unsigned) retval == sizeof inst_raw) && !strcmp(fmt, exp_fmt))
    return 0;
  printf("Failed case: %08" PRIx32, inst_raw);
  printf("\n  Exp (%2zu): %s", sizeof inst_raw, exp_fmt);
  printf("\n  Got (%2d): %s\n", retval, fmt);
  return -1;
}

int main(void) {
  unsigned failed = 0;
  failed |= test(0x00000000, "UNDEF");
  failed |= test(0x00054703, "lbu r14 r10");
  failed |= test(0xfe043783, "ld r15 r8 -32");
  failed |= test(0xfe043023, "sd r8 r0 -32");
  failed |= test(0x00d71463, "bne r14 r13 8");
  failed |= test(0xfe0718e3, "bne r14 r0 -16");
  failed |= test(0x0ff67613, "andi r12 r12 255");
  failed |= test(0x0007879b, "addiw r15 r15");
  failed |= test(0x00008067, "jalr r0 r1");
  failed |= test(0x0700006f, "jal r0 112");
  failed |= test(0x20a93c27, "fsd r18 r10 536");
  failed |= test(0xe20505d3, "fmv.x.d r11 r10");
  failed |= test(0xd2287553, "fcvt.d.l r10 r16");
  failed |= test(0x02957553, "fadd.d r10 r10 r9");

  puts(failed ? "Some tests FAILED" : "All tests PASSED");
  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
