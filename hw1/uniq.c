#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1024];
char temp[1024];
char store[1024];
int isC,isD,isI;


int isSameLine(){
	int sameline, pointerJ;
	sameline = 1;
	pointerJ = 0;
	while(temp[pointerJ]!='\0'){
		if(isI){//ingnore case senstive
			int c0,ca,cT;
			c0 = (int) temp[pointerJ];
			if(c0>=65 && c0<=90){//upper case
				ca = c0+32;
			}else if(c0>=97 && c0<=122){//lower case
				ca = c0-32;
			}else{
				ca = c0;
			}
			cT = (int)store[pointerJ];
			
			if(cT!=c0&&
				cT!=ca){
				sameline = 0;
			}
				
		}else{
			if(temp[pointerJ]!=store[pointerJ])
				sameline = 0;
		}
		pointerJ++;
	}
	return sameline;
}

void storeTemp(){
	
	memset(store,'\0',sizeof(store));
	int k = 0;
	while(temp[k]!='\0' && k<sizeof(store)){		
		store[k] = temp[k];
		k++;
	}
	memset(temp,'\0',sizeof(temp));
}

void printStore(int totalLine){
	
	if(isC){
		if(!(isD&&totalLine<=1)) printf(1,"\t%d %s",totalLine,store);
	}else{
		if(!(isD&&totalLine<=1)) printf(1,"%s",store);
	}
	
}


void
uniq(int fd, char *name){
	int i,n,tempPointer,currentLineSum, firstline;


	memset(store,'\0',sizeof(store));
	memset(temp,'\0',sizeof(temp));


	tempPointer = 0;
	currentLineSum = firstline = 1;

	
	while((n = read(fd, buf, sizeof(buf))) > 0){
		for(i=0;i<n;i++){
			
			temp[tempPointer] = buf[i];
			
			if(buf[i]=='\n'){
				tempPointer = 0;
				int isSame = 0;
				//compare temp to store
				isSame = isSameLine();

				if(isSame){//if same line
					currentLineSum ++;//add line count
					memset(temp,'\0',sizeof(temp));
				}else{//if not same line
					if(firstline){
						storeTemp();
						firstline = 0;
					}else{
						printStore(currentLineSum);
						storeTemp();
					}
					currentLineSum = 1;//reset line count
				}

				if(i+1>=n){//last line
					printStore(currentLineSum);
				}	
				
			}else{
				tempPointer ++;
			}
		}
	}

	
	if(n<0){
		printf(1,"uniq: read error\n");
		exit();
	}
}



int
main(int argc, char *argv[])
{
  int fd, i;
  
  if(argc <= 1){ 
    uniq(0, "");
    exit();
  }

  isC = isD = isI = 0;

  for(i = 1; i < argc; i++){
    if(*argv[i] == '-') {

	char *t = argv[i];
	t += 1;

	if(*t == 'c') isC = 1;
	if(*t == 'd') isD = 1;
	if(*t == 'i') isI = 1;

	}else if((fd = open(argv[i], 0)) < 0){	
      printf(1, "uniq: cannot open %s\n", argv[i]);
      exit();
    }else{
	uniq(fd, argv[i]);
    }
    close(fd);
  }
  exit();
}
