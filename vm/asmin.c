#include "lib.h"
#include "opcode.h"

#define vm_asm_strip(src_)                                                     \
  ({                                                                           \
    while (*src_ == ' ' || *src_ == '\t') {                                    \
      src_++;                                                                  \
    }                                                                          \
  })

#define vm_asm_stripln(src_)                                                   \
  ({                                                                           \
    while (*src_ == ' ' || *src_ == '\t' || *src_ == '\n' || *src_ == ';') {   \
      src_++;                                                                  \
    }                                                                          \
  })

int vm_asm_stars_with(const char *prefix, const char *within) {
  while (*prefix != '\0') {
    if (*within != *prefix) {
      return 0;
    }
    prefix++;
    within++;
  }
  return 1;
}

int vm_asm_opcode(const char *str) {
  for (int opcode = 0; opcode < VM_OPCODE_MAX1; opcode++) {
    const char *name = vm_opcode_name(opcode);
    int len = strlen(name);
    if (vm_asm_stars_with(name, str) && str[len] == ' ' || str[len] == '\n' || str[len] == ';' || str[len] == '\0') {
      return opcode;
    }
  }
  return -1;
}

int vm_asm_str(const char *src, vm_file_opcode_t **ops_out, size_t *nops_out) {
  size_t index = 0;
  size_t alloc = 16;
  vm_file_opcode_t *ops = malloc(sizeof(vm_file_opcode_t) * alloc);
  for (;;) {
    vm_asm_stripln(src);
    if (*src == '\0') {
      break;
    }
    int op = vm_asm_opcode(src);
    if (op == -1) {
      printf("unknown opcode\n");
      printf("%s\n", src);
      return 1;
    }
    src += strlen(vm_opcode_name(op));
    if (index + 4 >= alloc) {
      alloc = alloc * 4 + 8;
      ops = realloc(ops, sizeof(vm_file_opcode_t) * alloc);
    }
    ops[index++] = op;
    const char *format = vm_opcode_format(op);
    for (const char *head = format; *head != '\0'; head++) {
      vm_asm_strip(src);
      printf("%c\n", *head);
      switch (*head) {
      case 'r': {
        src++;
        size_t regno = 0;
        while ('0' <= *src && *src <= '9') {
          regno *= 10;
          regno += *src - '0';
          src++;
        }
        if (index + 4 >= alloc) {
          alloc = alloc * 4 + 8;
          ops = realloc(ops, sizeof(vm_file_opcode_t) * alloc);
        }
        ops[index++] = regno;
        break;
      }
      case 'i': {
        size_t num = 0;
        while ('0' <= *src && *src <= '9') {
          num *= 10;
          num += *src - '0';
          src++;
        }
        if (index + 4 >= alloc) {
          alloc = alloc * 4 + 8;
          ops = realloc(ops, sizeof(vm_file_opcode_t) * alloc);
        }
        ops[index++] = num;
        break;
      }
      case 's': {
        size_t outn = index;
        if (index + 4 >= alloc) {
          alloc = alloc * 4 + 8;
          ops = realloc(ops, sizeof(vm_file_opcode_t) * alloc);
        }
        ops[index++] = 0;
        if (*src != '"') {
          printf("expected quote\n");
          return 3;
        }
        vm_asm_strip(src);
        src++;
        while (*src != '"') {
          if (*src == '\0') {
            printf("file ended in string\n");
            return 4;
          }
          if (index + 4 >= alloc) {
            alloc = alloc * 4 + 8;
            ops = realloc(ops, sizeof(vm_file_opcode_t) * alloc);
          }
          if (*src == '\\') {
            src++;
            switch (*src) {
            case 'n':
              ops[index++] = (vm_file_opcode_t)'\n';
              break;
            case 't':
              src++;
              ops[index++] = (vm_file_opcode_t)'\t';
              break;
            case 'r':
              src++;
              ops[index++] = (vm_file_opcode_t)'\r';
              break;
            default:
              printf("unknown escape\n");
              return 5;
            }
            src++;
          } else {
            ops[index++] = (vm_file_opcode_t)*src;
            src++;
          }
          vm_asm_strip(src);
        }
        src++;
        ops[outn] = index - outn;
        break;
      }
      default:
        return 2;
      }
    }
  }
  *ops_out = ops;
  *nops_out = index;
  return 0;
}

int main(int argc, const char **argv) {
  if (argc <= 2) {
    return 1;
  }
  FILE *file = fopen(argv[2], "r");
  if (file == (void *)0) {
    return 2;
  }
  size_t nalloc = 256;
  size_t srclen = 0;
  char *src = malloc(sizeof(char) * nalloc);
  for (;;) {
    char chr = 0;
    size_t size = fread(&chr, sizeof(char), 1, file);
    if (size == 0) {
      break;
    }
    if (srclen + 4 >= nalloc) {
      nalloc = nalloc * 4 + 8;
      src = realloc(src, sizeof(char) * nalloc);
    }
    src[srclen++] = chr;
  }
  src[srclen] = '\0';
  fclose(file);
  vm_file_opcode_t *ops;
  size_t nops = 0;
  if (vm_asm_str(src, &ops, &nops)) {
    free(src);
    return 3;
  }
  free(src);
  FILE *out = fopen(argv[1], "wb");
  fwrite(ops, sizeof(vm_file_opcode_t), nops, out);
  fclose(out);
  free(ops);
  return 0;
}
