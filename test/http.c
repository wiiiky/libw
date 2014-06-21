#include <libw.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    WHttpHeaders *hdrs = w_http_headers_new();

    w_http_headers_append(hdrs, "Content-Type", "text/html");

    printf("Content-Type: %s\n", w_http_headers_get(hdrs, "content-type"));

    w_http_headers_append(hdrs, "content-type", "text/*");

    printf("Content-Type: %s\n", w_http_headers_get(hdrs, "content-Type"));

    w_http_headers_append(hdrs, "Content-type", "text/*");
    w_http_headers_free(hdrs);
    return 0;
}
