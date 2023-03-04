int main(int ac, char **av) {
    char  buff[16];
    file  fd;

    fd = fopen("/home/user/end/.pass", 0x80486f0);
    bzero(buff, 0x21)
    if (ac == 2) {
        fread(buff, 1, 0x42, fd);
        buff[atoi(av[1])] = 0;
        fread(somewhere, 1, 0x41, fd);
        fclose(fd);
        if (!strcmp(buff, av[1]))
            execl("/bin/sh", "sh", 0);
        else
            puts("whatever");
        return 0
    }
    return -1;
}
