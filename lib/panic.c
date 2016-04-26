void panic(char *msg)
{
    printf("PANIC:%s", msg);
    while(1);
}

void bios_msg(char *msg)
{
    printf("%s", msg);
}
