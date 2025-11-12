#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<dirent.h>

void options(int argc,char **argv);
void mode(int);
void file(char *);
void time_stamp(time_t *);

struct stat s;
int r=0;
char option[10]={'\0'};
char name[100];
char file_name[100];
char hold[100];
char colour=0;

int main(int argc,char **argv){
	
  DIR *dir=0;
  struct dirent *dir_data=0;
  char *ret=0;

	if(argc < 2){
		printf("useage: ./a.out filename[options]/dir\n");
		return 1;
	}
	
	options(argc,argv);

	r=stat(name,&s);
	if(r==-1){
		perror("stat");
		return 1;
	}

	//check:	file/directory
	if(S_ISDIR(s.st_mode)) {	 //directory
		
		dir=opendir(name);
		if(dir==0){
			perror("opendir");
			return 1;
		}

		while(dir_data=readdir(dir)){
			
		        strcpy(hold,name);

			int len=strlen(name);
			if(name[len-1]!='/'){
				strcat(hold,"/");
			}
			strcat(hold,dir_data->d_name);//filename with path
			
			ret=strrchr(hold,'/');
			if(ret){
				strcpy(file_name,ret+1);//only filename
			}

			file(hold);
		}

		closedir(dir);
	}
	else {	//file
		strcpy(file_name,name);	   
		file(file_name);	//filename with path
	}

   return 0;
}
void file(char *filename){
  char *r=0;
  int ret=0;
  struct stat s;

  	ret=stat(filename,&s);
	if(ret==-1){
		perror("STAT");
		return;
	}
  	
	r=strchr(option,'s');
	if(r){	//(option=='s')
		printf("%lu\t",s.st_blocks/2);	//blocks in 1024 each one
	}

	r=strchr(option,'i');
	if(r){  //(option=='i') 
		printf("%lu ",s.st_ino);	//inode
	}

	r=strchr(option,'l');
	if(r){   //(option=='l')
		mode(s.st_mode);		//mode permissions
		printf("\t");
		printf("%lu\t",s.st_nlink);	//hard links
		printf("%u\t",s.st_uid);	//UID
		printf("%u\t",s.st_gid);	//GID
		printf("%lu\t",s.st_size);	//no.of bytes used in file
		time_stamp((time_t *)&s.st_mtime);		//modification time
	}

	if(colour=='g')
		printf("\033[32m%s\n",file_name);
	else
		printf("%s\n",file_name);

	printf("\033[0m");
	colour='0';

}

void options(int argc,char **argv){

	int i=0;
	char *r=0;

	for(i=1;i<argc;i++){
		r=strchr(argv[i],'-');
		if(r){// option
			strcat(option,r+1);
		}
		else{// name file/dir
			strcpy(name,argv[i]);
		}
	}
}


void mode(int m){
	   if(S_ISREG(m))//  is it a regular file?
		printf("-");
 	   else if(S_ISDIR(m)){//  directory?
		printf("d");
		colour='g';
	   }
           
	   else if(S_ISCHR(m))//  character device?
		printf("c");

	   else if(S_ISBLK(m))//  block device?
		printf("b");

	   else if(S_ISFIFO(m))// FIFO (named pipe)?
		printf("p");

	   else if(S_ISLNK(m))//  symbolic link?  (Not in POSIX.1-1996.)
		printf("l");

	   else if(S_ISSOCK(m))// socket?  (Not in POSIX.1-1996.)
		printf("s");

	   for(int i=8;i>=0;i--){
		
		if((m>>i)&1){
		      if(i==8 || i==5 || i==2)// 8 7 6 	 5 4 3 	2 1 0
			printf("r");
		      else if(i==7 || i==4 || i==1)
			printf("w");
		      else
			printf("x");
		}
		else{
			printf("-");
		}

	   }
}
void time_stamp(time_t *t){
 char *time=0;
	time=ctime(t);
	time[16]='\0';
	printf("%s\t",&time[4]);
}
