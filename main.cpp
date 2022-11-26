// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <cstdlib>
#include <unistd.h>
#include <string>

const std::string HTML_PAGE =
        "<!DOCTYPE html>\n"
        "<html>"
            "<head>"
                "<title>OS</title>"
            "</head>"
            "<body>"
                "<b>I love <span style='color:red;'>Operating Systems</span> because:</b>"
                "<ol>"
                    "<li>Multitasking</li>"
                    "<li>Multiuser</li>"
                    "<li>CLI/GUI interface</li>"
                    "<li>Share of resources</li>"
                    "<li>Isolation of processes</li>"
                "</ol>"
            "</body>"
        "</html>";


const std::string PAYLOAD =
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Content-Length: " + std::to_string(HTML_PAGE.size()) + "\n"
        "\n"
        + HTML_PAGE;

const int PORT = 1337;

/**
 * Write buffer to file descriptor
 * @param fd - file descriptor
 * @param buf - buffer to write
 * @param n - size of buffer in bytes
 * @return -1 on error, 0 on success
 */
int write_wrapper(int fd, const void *buf, size_t n) {
    int num_written;
    while (num_written = write(fd, buf, n)) {
        if (num_written == -1) {
            if (errno != EINTR) {
                perror("write");
                return -1;
            }
        } else {
            buf = static_cast<const char *>(buf) + num_written;
            n -= num_written;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int tcp_socket;
    if ((tcp_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }

    sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(tcp_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr_in)) == -1) {
        perror("bind");
        return EXIT_FAILURE;
    }

    if (listen(tcp_socket, 0) == -1) {
        perror("listen");
        return EXIT_FAILURE;
    }

    while (true) {
        int client_fd;
        if ((client_fd = accept(tcp_socket, nullptr, 0)) == -1) {
            perror("accept");
            continue;
        }

        write_wrapper(client_fd, PAYLOAD.data(), PAYLOAD.size());

        if (close(client_fd)) {
            perror("close");
        }
    }

    return 0;
}
