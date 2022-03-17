/*
*    Port scanner with socket
*    
*   author: Victor Milhomem Losada López
*   github: https://github.com/VictorMilhomem
*
*/

#include "core.h"

int main(int argc, char **argv){
    
    int opt;
    int default_ports = 1;
    
    // regular expression for the target ip and for the ports

    const char *re_ipv4 = "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
    const char *re_port = "([0-9]+)-([0-9]+)";
    const char *re_ipv6 = "((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}"; // TODO: accept ipv6 address

    /*
    * the port is regex is a range so the way of usage is
    * example: to scan the ports 12 to 100 -> 12-100
    */
    char *target_ip; // ipv4 target ip
    int min_port = MIN_PORT;
    int max_default_port = DEFAULT_MAX_PORT;
    int max_port = MAX_PORT;

    if (argc < 3) {
        help_menu();
    } 

    while ((opt=getopt(argc, argv, "htpo")) != -1)
    {
        switch (opt)
        {
        case 'h':
            help_menu();
            break;
        case 't':
            if (match(argv[2], re_ipv4)){
                target_ip = argv[2];
            }else{
                printf("\nInvalid IP address\n");
            }
            break;
        case 'p':
            if (match(argv[4], re_port)){
                default_ports = 0;
                char *min;
                char *max;
                min = strtok (argv[4],"-");
                max = strtok (NULL, "-");
                min_port = atoi(min);
                max_port = atoi(max);
                if (min_port > max_port){
                    printf("\nInvalid port range\n");
                    help_menu();
                }
            }else{
                help_menu();
            }
            break;

        default:
            break;
        }
    }

    Target target = {target_ip, min_port, max_default_port, max_port};
    
    port_scanner(&target, default_ports);

    return EXIT_SUCCESS;
}

