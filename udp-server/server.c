/*
 * server.c
 *
 *  Created on: Feb 5, 2016
 *      Author: wing
 */
#define ALSA_PCM_NEW_HW_PARAMS_API
#include <alsa/asoundlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
	/*创建socket*/
	int sockfd;
	struct sockaddr_in s_addr;
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("%s","create sock failed!\n");
		return -1;
	}
	else
		printf("create sock success!\n");
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=htons(7000);
	if(argc!=2)
	{
		printf("用法：./voiceserver 客户端的IP地址.\n");
		return -1;
	}
	else
		s_addr.sin_addr.s_addr=inet_addr(argv[1]);
	bzero(&(s_addr.sin_zero),sizeof(s_addr.sin_zero));
	/*打开音频设备*/
	int rc;
	int size;
	snd_pcm_t *handle;
	snd_pcm_hw_params_t *params;
	unsigned int val;
	int dir;
	snd_pcm_uframes_t frames;
	char *buffer;
	rc = snd_pcm_open(&handle, "default",SND_PCM_STREAM_CAPTURE,0);
	if (rc < 0)
	{
		printf("unable to open pcm device: %s\n",snd_strerror(rc));
		return -1;
	}
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(handle, params);
	snd_pcm_hw_params_set_access(handle, params,SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(handle, params,SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_channels(handle, params, 2);
	val = 44100;
	snd_pcm_hw_params_set_rate_near(handle, params,&val, &dir);
	frames = 32;
	snd_pcm_hw_params_set_period_size_near(handle,params, &frames, &dir);
	rc = snd_pcm_hw_params(handle, params);
	if (rc < 0)
	{
		printf("unable to set hw parameters: %s\n",snd_strerror(rc));
		return -1;
	}
	snd_pcm_hw_params_get_period_size(params,&frames, &dir);
	size = frames * 4; /* 2 bytes/sample, 2 channels */
	buffer = (char *) malloc(size);
	while (1)
	{
		rc = snd_pcm_readi(handle, buffer, frames);
		if (rc == -EPIPE)
		{
			printf("overrun occurred\n");
			snd_pcm_prepare(handle);
		}
		else
			if (rc < 0)
				printf("error from read: %s\n",snd_strerror(rc));
			else
				if (rc != (int)frames)
					printf("short read, read %d frames\n", rc);
		sendto(sockfd,buffer,rc,0,(struct sockaddr *)&s_addr,sizeof(struct sockaddr));
	}
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
	free(buffer);
	return 0;
}
