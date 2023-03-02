void p(char *s, char c) {
  // sub esp, 0x1018
  char buf[4104];

  puts(c);
  read(stdin, &buf, 4096);
  *(strchr(&buf, '\n')) = 0;
  strncpy(s, &buf, 20);
  return;
}

void pp(char *buff) {
  // sub esp, 0x50
  char s2[28];  //  ebp-0x1c
  char s[20];   //  ebp-0x30

  p(s, '-');  //  Put 20 first read in s, null terminated
  p(s2, '-'); //  Put 20 first read in s2, but it can only
  strcpy(buff, s);
  buff[strlen(buff) - 1] = ' ';
  strcat(buff, s2);
  return ;
}

void main(void) {
  //sub esp, 0x40
  char buff[42]; // esp + 0x16

  pp(buff);
  puts(buff);
  return 0;
}
