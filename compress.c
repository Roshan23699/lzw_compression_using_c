#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
void adddic(char p[], char dicstring[][100], uint16_t code[], uint16_t prefix[], uint16_t code1, uint16_t len);
int search(char p[], char dicstring[][100],uint16_t len);
void initdic(char dicstring[][100], uint16_t code[], uint16_t prefix[], uint16_t len);
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
	char dicstring[65536][100], ch, p[100];
	uint16_t code[65536];
	uint16_t prefix[65536];
	uint16_t len;
	uint16_t code1;
	len = 256;
	initdic(dicstring, code , prefix, len);
	int fd, i, r, fdw;
	//FILE *fw;
	fd = open(file, O_RDONLY, S_IRUSR);
	fdw = open(out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	//fw = fopen(out, "w");
	char pre[100];
	while(read(fd, &ch, sizeof(ch))){
		//printf("%c", ch);
		strcpy(pre, p);
		p[i] = ch;
		p[++i] = '\0';
		//printf("\n%s\n", p);
		r = search(p, dicstring, len);
		if(r)
		{			
			//printf("%d", i);
			//printf("%s", p);
			code1 = prefix[r-1];
		}
		else
		{
			adddic(p, dicstring, code, prefix, code1, len);
			len++;
			//printf("%s", pre);			
			int j = search(pre, dicstring, len);
			//printf("/%d/", code[j-1]);
			//fwrite(&code[j-1], sizeof(code[j-1]), 1, fw);
			write(fdw, &code[j-1], sizeof(uint16_t));
			int l = strlen(p);
			char c = p[l-1];
			strcpy(p, "\0");
			p[0] = c;
			p[1] = '\0';
			i = 1;
		}
	}
	close(fd);
	close(fdw);
}
void initdic(char dicstring[][100], uint16_t code[], uint16_t prefix[], uint16_t len){
	int i;	
	for(i = 0; i < len; i++)
	{
		dicstring[i][0] = i;
		dicstring[i][1] = '\0';
		code[i] = i;
		prefix[i] = i;
	}
}
int search(char p[], char dicstring[][100],uint16_t len){
	int i;
	for(i = 0; i < len; i++)
	{
		if(!strcmp(p, dicstring[i]))
		{
			//printf("\nsearch- %d -%s--%s\n", i, dicstring[i], p);		
			return i + 1;
		}
	}
	return 0;
}
void adddic(char p[], char dicstring[][100], uint16_t code[], uint16_t prefix[], uint16_t code1, uint16_t len){
	strcpy(dicstring[len], p);
	code[len] = len;
	prefix[len] = code1;
}
