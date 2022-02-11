#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/epoll.h>

#define SERVER_PORT (7788)
#define EPOLL_MAX_NUM (2048)


int main(int argc, char** argv)
{
    int listen_fd = 0;
//    int client_fd = 0;

    struct sockaddr_in server_addr;
//    struct sockaddr_in client_addr;

    socklen_t client_len;

  //  int epfd = 0;
    struct epoll_event event, *my_events;

    int epfd = 0;

    listen_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);
    bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(listen_fd, 10);

    epfd = epoll_create(EPOLL_MAX_NUM);
    if (epfd < 0) {
        perror("epoll create");
        goto END;
    }

    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &event) < 0) {
        perror("epoll ctl add listen_fd");
        goto END;
    }

    my_events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * EPOLL_MAX_NUM);

    while (1) {
        int active_fds_cnt = epoll_wait(epfd, my_events, EPOLL_MAX_NUM, -1);
        printf("active fds cnt is %d\n", active_fds_cnt);
    }

END:
    close(epfd);
    close(listen_fd);
    return 0;
    

}

