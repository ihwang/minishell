/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wait4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:14:43 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/04 15:16:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
 
 void ViewRUsage(pid_t pid, struct rusage *pru)
{
    printf("\n=== pid rusage info ===\n");
    struct timeval *tv = &(pru->ru_utime);
    printf("user CPU time used [%ld]sec [%d]usec\n", tv->tv_sec,tv->tv_usec );
    tv = &(pru->ru_stime);
    printf("system CPU time used [%ld]sec [%d]usec\n", tv->tv_sec,tv->tv_usec );

	pid = 0;
}

int main()
{
    pid_t cpid = fork();
 
    if(cpid == -1)
    {
        perror("error fork");
        return 0;
    }
 
    if(cpid>0)
    {
        printf("<parent> fork child pid:%u\n",cpid);
        int rvalue = 0;
        struct rusage ru;
        pid_t wpid = wait3(&rvalue,0, &ru);
        ViewRUsage(wpid, &ru);
    }
    else
    {
        printf("<child> pid:%d \n",getpid());
        int i = 0;
        for(i = 0; i < 100000 ; i++)
        {
            fprintf(stderr,".");
        }
    }
    return 0;
}
