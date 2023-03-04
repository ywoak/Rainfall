int main(inc ac, char **av)
{
  // sub esp, 0x40
  char buff[40]; // esp+0x14
  int atoi_ret; // esp+0x3c

  atoi_ret = atoi(av[1]);
  if (atoi_ret < 10) {
    memcpy(buff, av[2], atoi_ret * 4);
    // Win block
    if (atoi_ret == 0x574f4c46) { // FLOW in ascii
      execl("/bin/sh", sh, 0);
    }
    return 0;
  }
  else {
    return 1;
  }
  return 0;
}
