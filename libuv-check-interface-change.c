#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <netinet/in.h>
#include <net/if.h>
#include <uv.h>


int OpenIfNotifySocket(int *pFD)
{
    int err = 0;
    struct sockaddr_nl snl;
    int sock;
    int ret;

    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0)
        return errno;

    // Configure read to be non-blocking because inbound msg size is not known in advance
    (void) fcntl(sock, F_SETFL, O_NONBLOCK);

    memset(&snl, 0, sizeof(snl));
    snl.nl_family = AF_NETLINK;
    // snl.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR;
    snl.nl_groups = RTMGRP_IPV4_IFADDR;
    ret = bind(sock, (struct sockaddr *) &snl, sizeof snl);
    if (0 == ret)
        *pFD = sock;
    else
        err = errno;

    return err;
}

void pollCallback(uv_poll_t* handle, int status, int events) {
    char buffer[4096];
    struct nlmsghdr *nlh;
    if (events == UV_READABLE) {
        nlh = (struct nlmsghdr *)buffer;
        int sock = *((int*)handle->data);
        int len;
        while ((len = recv(sock, nlh, 4096, 0)) > 0) {
            while ((NLMSG_OK(nlh, len)) && (nlh->nlmsg_type != NLMSG_DONE)) {          
                if (nlh->nlmsg_type == RTM_NEWADDR) {
                    printf("interface add address\n");
                    struct ifaddrmsg *ifa = (struct ifaddrmsg *) NLMSG_DATA(nlh);
                    struct rtattr *rth = IFA_RTA(ifa);
                    int rtl = IFA_PAYLOAD(nlh);

                    while (rtl && RTA_OK(rth, rtl)) {
                        if (rth->rta_type == IFA_LOCAL) {
                            uint32_t ipaddr = htonl(*((uint32_t *)RTA_DATA(rth)));
                            char name[512];
                            if_indextoname(ifa->ifa_index, name);
                            printf("%s is now %d.%d.%d.%d\n",
                                name,
                                (ipaddr >> 24) & 0xff,
                                (ipaddr >> 16) & 0xff,
                                (ipaddr >> 8) & 0xff,
                                ipaddr & 0xff);
                        }
                        rth = RTA_NEXT(rth, rtl);
                    }
                }
                else if (nlh->nlmsg_type == RTM_DELADDR) {
                    printf("interface remove address\n");
                }
                nlh = NLMSG_NEXT(nlh, len);
            }
        }
    }
}

int main(int argc, char **argv) {
    uv_loop_t *loop = uv_default_loop();

    int netChangeFd;
    int err = OpenIfNotifySocket(&netChangeFd);
    if (err) {
        perror("open interface notify socket error");
        exit(1);
    }

    uv_poll_t poll;
    poll.data = &netChangeFd;
    uv_poll_init(loop, &poll, netChangeFd);
    uv_poll_start(&poll, UV_READABLE, pollCallback);
    uv_run(loop, UV_RUN_DEFAULT);
    uv_poll_stop(&poll);

    return 0;
}
