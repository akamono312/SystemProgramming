#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#define MAX_LEN 10000
#define MAX_LIST_SIZE 10000

struct stat_list {
	struct stat info;
	char filename[MAX_LEN];
};


void do_ls(char[], int);	// code) default: 0, time: 1, size: 2
void dostat(char*, int, struct stat_list*);
void show_file_info(char*, struct stat*);
void mode_to_letters(int, char[]);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);
void bubble_sort(int, int);


struct stat_list info_list[MAX_LIST_SIZE];
int cnt;


int main(int argc, char* argv[]) {
	if(argc == 1) do_ls(".", 0);
	else if(argv[1][0] == '-') {
		if(!strcmp(argv[1], "-t")) {	// sort by time - code 1
			if(argc == 2) do_ls(".", 1);
			else {
				*++argv;
				while((--argc) - 1 != 0) {
					printf("%s:\n", *++argv);
					do_ls(*argv, 1);
				}
			}
			printf("sort by time\n");
		} else if(!strcmp(argv[1], "-b")) {	// sort by size - code 2
			if(argc == 2) do_ls(".", 2);
			else {
				*++argv;
				while((--argc) - 1 != 0) {
					printf("%s:\n", *++argv);
					do_ls(*argv, 2);
				}
				printf("sort by size(byte)\n");
			}
		} else {
			fprintf(stderr, "\"-t\" to sort by time or \"-b\" to sort by size\n");
		}
	}
	else {
		while(--argc) { // code 0
			printf("%s:\n", *++argv);
			do_ls(*argv, 0);
		}
	}
}


void do_ls(char dirname[], int code) {
	DIR* dirptr;
	struct dirent* direntp;
	char pathname[MAX_LEN];
	int i;
	long sum;

	dirptr = opendir(dirname);

	if(dirptr == NULL) fprintf(stderr, "ls3: cannot open %s\n", dirname);
	else {
		cnt = -1;
		while((direntp = readdir(dirptr)) != NULL) {
			strcpy(pathname, dirname);
		       	strcat(pathname, "/");
			strcat(pathname, direntp->d_name);
			strcpy(info_list[++cnt].filename, direntp->d_name);
			dostat(pathname, code, info_list);
		}
		if(code) {
			bubble_sort(cnt, code);
			int i;
			for(i = 0; i <= cnt; i++) {
				show_file_info(info_list[i].filename, &(info_list[i].info));
			}
		}
		sum = 0;
		for(i = 0; i <= cnt; i++) sum += info_list[i].info.st_size;
		printf("number of files: %d, size total: %ld\n", cnt + 1, sum);
		closedir(dirptr);
	}
}

void dostat(char* pathname, int code, struct stat_list* info_list) {
	if(stat(pathname, &(info_list[cnt].info)) == -1) perror(info_list[cnt].filename);
	else {
		if(!code) show_file_info(info_list[cnt].filename, &(info_list[cnt].info));
	}
}

void show_file_info(char* filename, struct stat* info_p) {
	char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void mode_to_letters();
	char modestr[20];

	
	mode_to_letters(info_p->st_mode, modestr);
	printf("%s ", modestr);
	printf("%4d ", (int)info_p->st_nlink);
	printf("%-8s ", uid_to_name(info_p->st_uid));
	printf("%-8s ", gid_to_name(info_p->st_gid));
	printf("%-8ld ", (long)info_p->st_size); //size
	printf("%.12s ", 4+ctime(&info_p->st_mtime)); //date
	printf("%s \n", filename);
}


void mode_to_letters(int mode, char str[]) {
	strcpy(str, "------------");

	if(S_ISDIR(mode)) str[0] = 'd';
	if(S_ISCHR(mode)) str[0] = 'c';
	if(S_ISBLK(mode)) str[0] = 'b';

	if(mode & S_IRUSR) str[1] = 'r';
	if(mode & S_IWUSR) str[2] = 'w';
	if(mode & S_IXUSR) str[3] = 'x';

	if(mode & S_IRGRP) str[4] = 'r';	
	if(mode & S_IWGRP) str[5] = 'w';
	if(mode & S_IXGRP) str[6] = 'x';

	if(mode & S_IROTH) str[7] = 'r';	
	if(mode & S_IWOTH) str[8] = 'w';
	if(mode & S_IXOTH) str[9] = 'x';
}


char* uid_to_name(uid_t uid) {
	struct passwd *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL) {
		sprintf(numstr, "%d", uid);
		return numstr;
	} else 	return pw_ptr->pw_name;
}


char* gid_to_name(gid_t gid){
	struct group *getgrid(), *grp_ptr;
	static char numstr[10];
	if((grp_ptr = getgrgid(gid)) == NULL) {
		sprintf(numstr, "%d", gid);
		return numstr;
	} else return grp_ptr->gr_name;
}

void bubble_sort(int cnt, int code) {
	int i, j;
	struct stat_list temp;
	for(i = 0; i <= cnt - 1; i++) {
		for(j = 0; j <= cnt - i - 1; j++) {
			if(code == 1) { 		// sort by time
				//printf("debug sort by time\n");
				if(info_list[j].info.st_mtime > info_list[j + 1].info.st_mtime) {
					//printf("debug bubble sort\n");
					temp = info_list[j];
					info_list[j] = info_list[j + 1];
					info_list[j + 1] = temp;
				}
			} else if(code == 2) {	// sort by size
				//printf("debug sort by size\n");
				if(info_list[j].info.st_size > info_list[j + 1].info.st_size) {
					temp = info_list[j];
					info_list[j] = info_list[j + 1];
					info_list[j + 1] = temp;
				}
			}
		}
	}
}