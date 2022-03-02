#pragma once

#include "lib.h"

enum {
  VM_OPCODE_EXIT = 0,
  VM_OPCODE_REG = 1,
  VM_OPCODE_BB = 2,
  VM_OPCODE_INT = 3,
  VM_OPCODE_JUMP = 4,
  VM_OPCODE_FUNC = 5,
  VM_OPCODE_ADD = 6,
  VM_OPCODE_SUB = 7,
  VM_OPCODE_MUL = 8,
  VM_OPCODE_DIV = 9,
  VM_OPCODE_MOD = 10,
  VM_OPCODE_POW = 11,
  VM_OPCODE_CALL = 12,
  VM_OPCODE_RETURN = 13,
  VM_OPCODE_PUTCHAR = 14,
  VM_OPCODE_STRING = 15,
  VM_OPCODE_LENGTH = 16,
  VM_OPCODE_GET = 17,
  VM_OPCODE_SET = 18,
  VM_OPCODE_DUMP = 19,
  VM_OPCODE_READ = 20,
  VM_OPCODE_WRITE = 21,
  VM_OPCODE_ARRAY = 22,
  VM_OPCODE_CAT = 23,
  VM_OPCODE_BEQ = 24,
  VM_OPCODE_BLT = 25,
  VM_OPCODE_ADDI = 26,
  VM_OPCDOE_SUBI = 27,
  VM_OPCDOE_MULI = 28,
  VM_OPCODE_DIVI = 29,
  VM_OPCODE_MODI = 30,
  VM_OPCODE_CALL0 = 31,
  VM_OPCODE_CALL1 = 32,
  VM_OPCODE_CALL2 = 33,
  VM_OPCODE_CALL3 = 34,
  VM_OPCODE_GETI = 35,
  VM_OPCODE_SETI = 36,
  VM_OPCODE_BEQI = 37,
  VM_OPCODE_BLTI = 38,
  VM_OPCODE_BLTEI = 39,
  VM_OPCODE_MAX1,
};

static inline const char *vm_opcode_format(int opcode) {
  switch (opcode) {
  default:
    return "?";
  case VM_OPCODE_EXIT:
    return "";
  case VM_OPCODE_REG:
    return "rr";
  case VM_OPCODE_BB:
    return "rll";
  case VM_OPCODE_INT:
    return "ri";
  case VM_OPCODE_JUMP:
    return "l";
  case VM_OPCODE_FUNC:
    return "lsif";
  case VM_OPCODE_ADD:
    return "rrr";
  case VM_OPCODE_SUB:
    return "rrr";
  case VM_OPCODE_MUL:
    return "rrr";
  case VM_OPCODE_DIV:
    return "rrr";
  case VM_OPCODE_MOD:
    return "rrr";
  case VM_OPCODE_POW:
    return "rrr";
  case VM_OPCODE_CALL:
    return "rlc";
  case VM_OPCODE_RETURN:
    return "r";
  case VM_OPCODE_PUTCHAR:
    return "r";
  case VM_OPCODE_STRING:
    return "rs";
  case VM_OPCODE_LENGTH:
    return "rr";
  case VM_OPCODE_GET:
    return "rrr";
  case VM_OPCODE_SET:
    return "rrr";
  case VM_OPCODE_DUMP:
    return "rr";
  case VM_OPCODE_READ:
    return "rr";
  case VM_OPCODE_WRITE:
    return "rr";
  case VM_OPCODE_ARRAY:
    return "rc";
  case VM_OPCODE_CAT:
    return "rrr";
  case VM_OPCODE_BEQ:
    return "rrll";
  case VM_OPCODE_BLT:
    return "rrll";
  case VM_OPCODE_ADDI:
    return "rrll";
  case VM_OPCDOE_SUBI:
    return "rri";
  case VM_OPCDOE_MULI:
    return "rri";
  case VM_OPCODE_DIVI:
    return "rri";
  case VM_OPCODE_MODI:
    return "rri";
  case VM_OPCODE_CALL0:
    return "rl";
  case VM_OPCODE_CALL1:
    return "rlr";
  case VM_OPCODE_CALL2:
    return "rlrr";
  case VM_OPCODE_CALL3:
    return "rlrrr";
  case VM_OPCODE_GETI:
    return "rri";
  case VM_OPCODE_SETI:
    return "rir";
  case VM_OPCODE_BEQI:
    return "rill";
  case VM_OPCODE_BLTI:
    return "rill";
  case VM_OPCODE_BLTEI:
    return "rill";
  }
}

static inline const char *vm_opcode_name(int opcode) {
  switch (opcode) {
  default:
    return "?";
  case VM_OPCODE_EXIT:
    return "exit";
  case VM_OPCODE_REG:
    return "reg";
  case VM_OPCODE_BB:
    return "bb";
  case VM_OPCODE_INT:
    return "int";
  case VM_OPCODE_JUMP:
    return "jump";
  case VM_OPCODE_FUNC:
    return "func";
  case VM_OPCODE_ADD:
    return "add";
  case VM_OPCODE_SUB:
    return "sub";
  case VM_OPCODE_MUL:
    return "mul";
  case VM_OPCODE_DIV:
    return "div";
  case VM_OPCODE_MOD:
    return "mod";
  case VM_OPCODE_POW:
    return "pow";
  case VM_OPCODE_CALL:
    return "call";
  case VM_OPCODE_RETURN:
    return "return";
  case VM_OPCODE_PUTCHAR:
    return "putchar";
  case VM_OPCODE_STRING:
    return "string";
  case VM_OPCODE_LENGTH:
    return "length";
  case VM_OPCODE_GET:
    return "get";
  case VM_OPCODE_SET:
    return "set";
  case VM_OPCODE_DUMP:
    return "dump";
  case VM_OPCODE_READ:
    return "read";
  case VM_OPCODE_WRITE:
    return "write";
  case VM_OPCODE_ARRAY:
    return "array";
  case VM_OPCODE_CAT:
    return "cat";
  case VM_OPCODE_BEQ:
    return "beq";
  case VM_OPCODE_BLT:
    return "blt";
  case VM_OPCODE_ADDI:
    return "addi";
  case VM_OPCDOE_SUBI:
    return "subi";
  case VM_OPCDOE_MULI:
    return "muli";
  case VM_OPCODE_DIVI:
    return "divi";
  case VM_OPCODE_MODI:
    return "modi";
  case VM_OPCODE_CALL0:
    return "call0";
  case VM_OPCODE_CALL1:
    return "call1";
  case VM_OPCODE_CALL2:
    return "call2";
  case VM_OPCODE_CALL3:
    return "call3";
  case VM_OPCODE_GETI:
    return "geti";
  case VM_OPCODE_SETI:
    return "seti";
  case VM_OPCODE_BEQI:
    return "beqi";
  case VM_OPCODE_BLTI:
    return "blti";
  case VM_OPCODE_BLTEI:
    return "bltei";
  }
}
