//
// Created by 翟亚南 on 2019-01-23.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../src/sds.h"


int main(int argc, char *argv[])
{
    sds sds1 = sdsnew("addadf");

    printf("%s\n", sds1);
    printf("%d", sdsavail(sds1));
    printf("%d",sizeof(struct sdshdr8));

}