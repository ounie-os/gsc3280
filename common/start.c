#include <stdio.h>
#include <serial.h>

int start_test(void)
{
    init_serial();
    serial_set(115200);
    mdelay(2000);

    printf("\nSystem start......\n");

    main_loop();
    return 0;
}
