int language = 0;

void greetuser(int dest_0x50) {
  // sub esp, 0x58        ;   88
  char s1_ebp_0x48[0x48]; //  72

  // Or a switch case idk but doesnt matter
  // The tree block do the same thing, i think its strcpy done weirdly
  if (language == 1) {
    strcpy(s1_ebp_0x48, "Hyvää päivää "); // utf8
  }
  else if (language == 2) {
    s1_ebp_0x48 = "Goedemiddag! ";
  }
  else if (language == 0) {
    s1_ebp_0x48 = "HELLO ";
  }
  strcat(&s1_ebp_0x48, &dest_0x50);
  puts(&s1_ebp_0x48);
  return;
}

int main(int ac, int av) {
  // and esp, 0xfffffff0
  // sub esp, 0xa0    ;   160
  char dest_0x50[80]; //  ?vi 0xa0 - 0x50 = 80

  if (ac == 3) {
    memset(dest_0x50, 0, 0x13); // 19
    strncpy(dest_0x50, av[1], 0x28); // 40
    strncpy(dest_0x50[0x28], av[2], 0x20); // 32
    if (getenv("LANG")) {
      if (!memcmp(s1_0x9c, "fi", 2)) {
        language = 1;
      } else if (!memcmp(s1_0x9c, "nl", 2)) {
        language = 2;
      }
    }
    greetuser(strncpy(_, dest_0x50, 0x13)); // _ -> Pseudo anonymous, strncpy ret dst, asm -> rep movsd
  }
  return ;
}

