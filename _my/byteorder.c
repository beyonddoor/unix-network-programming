#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// #define MACTOSTR(X) #X

#define BEGIN_TEST(name) void name() { \
printf("test " #name "\n");
#define END_TEST }

BEGIN_TEST(byteorder)
    uint16_t i16 = 0x1234;
    uint32_t i32 = 0x12345678;

    uint16_t n16;
    uint32_t n32;

    n16 = htons(i16);
    n32 = htonl(i32);
    printf("%x=>%x, %x=>%x\n", i16, n16, i32, n32);
END_TEST

BEGIN_TEST(test_addr)
    // struct inaddr
    char buf[1024];
    const char* str = "inet_ntoa(0x12345678)";
    in_addr_t i = inet_addr("123.34.56.9");
    struct in_addr addr = {0x08070605};

    printf("%s, %d\n", str, i);

    inet_ntop(AF_INET, &addr, buf, 1024);
    printf("addr: %s\n", buf);
END_TEST

int main()
{
    byteorder();
    test_addr();
}