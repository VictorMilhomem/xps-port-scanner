#include "core.h"

void help_menu(){
    printf("Usage: xps [Options]\n");
    printf("\t-t:\tTarget ip address\n\t-p:\tSpecify the ports range to scan <lower>-<upper>\n");
    exit(EXIT_SUCCESS);
}

int match(const char *string, const char *pattern)
{
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;
    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (status != 0) return 0;
    return 1;
}

int port_scanner(Target *target, int default_ports){
    struct sockaddr_in sa;
    int sockfd, err, max_port, min_port;
    
    strncpy((char*)&sa , "" , sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(target->ip);

   // for test we will use the defult maximum port

    min_port = target->min_port;
    max_port = target->max_default_port;
    if (default_ports == 0)
    {
        max_port = target->max_port;
    }

    printf("\nStarting scanning %s ...\n", target->ip);

    for (int i = min_port; i <= max_port; i++){
        sa.sin_port = htons(i);
        sockfd = socket(AF_INET , SOCK_STREAM , 0);

        if (sockfd < 0 ){
            perror("\nSocket failure\n");
			exit(EXIT_FAILURE);
        }
        
        //Connect using that socket and sockaddr structure
		err = connect(sockfd , (struct sockaddr*)&sa , sizeof sa);
		
		//not connected
		if( err < 0 )
		{
            //printf("Not connected");
            continue;
			fflush(stdout);
		}
		//connected
		else
		{
			printf("%-5d open\n",  i);
		}
		close(sockfd);
    }
    
    printf("\r");
	fflush(stdout);

    return EXIT_SUCCESS;
}


