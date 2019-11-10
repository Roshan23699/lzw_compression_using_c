#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
void adddic(char p[], char dicstring[][100], uint16_t code[], uint16_t len);
void initdic(char dicstring[][100], uint16_t code[], uint16_t len);
void builddic(char *file, char *out);
int main(int argc, char *argv[]){
    char *p, *q;
    if(argc < 2){
        return -1;
    }
    p = argv[1];
    q = argv[2];
    builddic(p, q);
    return 0;
}
void builddic(char *file, char *out){
	char dicstring[65536][100];
	uint16_t code[65536];
	uint16_t len, in;
	uint16_t code1;
	len = 256;
	initdic(dicstring, code , len);
	int fd, i, fdw, j;
	fd = open(file, O_RDONLY, S_IRUSR);
	uint16_t old, new;
	read(fd, &old, sizeof(old));
	//printf("%s", dicstring[old]);
	int y = strlen(dicstring[old]), t;
	fdw = open(out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	for(j = 0; j < y; j++)
		write(fdw, &dicstring[old][t], sizeof(char));			
	//FILE *fw;
	//fw = fopen(out, "w");
	char olds[100], c, s[100], r[2];
	while(read(fd, &new, sizeof(new))){
		//printf("%d", new);
		if(new >= len)
		{
			strcpy(s, dicstring[old]);
			strcat(s, r);
			//printf("%s", s);
		}
		else
		{
			strcpy(s, dicstring[new]);
		}
		//printf("%s", s);
		int l = strlen(s);
		for(int k = 0; k < l; k++) 
			write(fdw, &s[k], sizeof(char));			
		c = s[0];
		r[0] = c;
		r[1] = '\0';
		strcpy(olds, dicstring[old]);
		strcat(olds, r);
		adddic(olds, dicstring, code, len);
		len++;
		old = new;
	}
	char ch = '\n';
	write(fdw, &ch, sizeof(char));
	close(fdw);
	close(fd);
}
void initdic(char dicstring[][100], uint16_t code[], uint16_t len){
	int i;	
	for(i = 0; i < len; i++)
	{
		dicstring[i][0] = i;
		dicstring[i][1] = '\0';
		code[i] = i;
		//prefix[i] = i;
	}
}
void adddic(char p[], char dicstring[][100], uint16_t code[], uint16_t len){
	strcpy(dicstring[len], p);
	code[len] = len;
	//printf("\n%s-%d\n", dicstring[len], code[len]);
	//prefix[len] = code1;
}

