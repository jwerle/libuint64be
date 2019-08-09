#include <stdio.h>
#include <ok/ok.h>

#include <uint64be/uint64be.h>

#ifndef OK_EXPECTED
#define OK_EXPECTED 0
#endif

void
printb(unsigned char *bytes, unsigned long n) {
  for (int i = 0; i < n; ++i) {
    printf("%02x", bytes[i]);
    if (i + 1 < n) { printf(" "); }
  }
  printf("\n");
}

int
main(void) {
  ok_expect(OK_EXPECTED);

  unsigned char encoded[16] = { 0 };
  unsigned long long offset = 8;
  unsigned long long value = 0xdeadbeef;

  if (8 == uint64be_encode(encoded + offset, value)) {
    for (int i = 0 ; i < 8; ++i) {
      int j = i + offset;
      switch (i) {
        case 0: if (0x00 == encoded[j]) { ok("encoded[%d]", j); } break;
        case 1: if (0x00 == encoded[j]) { ok("encoded[%d]", j); } break;
        case 2: if (0x00 == encoded[j]) { ok("encoded[%d]", j); } break;
        case 3: if (0x00 == encoded[j]) { ok("encoded[%d]", j); } break;
        case 4: if (0xde == encoded[j]) { ok("encoded[%d]", j); } break;
        case 5: if (0xad == encoded[j]) { ok("encoded[%d]", j); } break;
        case 6: if (0xbe == encoded[j]) { ok("encoded[%d]", j); } break;
        case 7: if (0xef == encoded[j]) { ok("encoded[%d]", j); } break;
      }
    }

    ok("uint64be_encode");
  }

  unsigned long long decoded = uint64be_decode(encoded, offset);

  if (value == decoded) {
    ok("uint64be_decode");
  }

  //printb(encoded + offset, 8);
  printf("%s\n", uint64be_version_string());
  ok_done();
  return ok_expected() - ok_count();
}
