#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "webfiles.h"

int getIndex(struct Webfile **indexfilePtr)
{
    int indexfileFd;
    struct Webfile *wfp;

    indexfileFd = open("index.html", O_RDONLY);
    if (indexfileFd > 0) {
        printf("Opened index.html.\n");
    }
    else {
        printf("Failed to open index.html.\n");

        return 1;
    }

    struct stat statbuf;
    if (fstat(indexfileFd, &statbuf) == 0) {
        printf("Size of index.html: %d\n", (int)statbuf.st_size);
    }
    else {
        printf("Failed to get size of index.html.\n");

        return 1;
    }
    
    wfp = (struct Webfile *)malloc(sizeof (struct Webfile));
    wfp->content = (char *)malloc((size_t)statbuf.st_size);

    if (read(indexfileFd, (void *)wfp->content, (size_t)statbuf.st_size) >= 0) {
        printf("Read index.html.\n");
    }
    else {
        printf("Failed to read index.html.\n");

        return 1;
    }

    wfp->len = (int)statbuf.st_size;

    *indexfilePtr = wfp;

    return 0;
}
