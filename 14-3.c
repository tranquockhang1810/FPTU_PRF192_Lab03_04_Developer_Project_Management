#include<stdio.h>
#include<string.h>
#include<ctype.h>
char* ltrim(char s[]) {
	int i = 0 ;
	while(s[i]==' ') i++ ;
	strcpy(&s[0], &s[i]);
	return 0 ;
}
char* rtrim(char s[]) {
	int i = strlen(s)-1;
	while(s[i]== ' ') i-- ;
	s[i+1]='\0';
}
char* trim(char s[]) {
	rtrim(s);
	ltrim(s);
	char *prt=strstr(s, "  ");
	while(prt != NULL) {
		strcpy(prt, prt+1);
		prt = strstr(s, "  ");
	}
	return s ;
}
char *nameString(char s[]){
	trim(s);
	strlwr(s);
	int i ;
	for(i = 0 ; i < strlen(s) ; i++){
		if(i == 0  || (i >0 && s[i - 1] == ' '))
		s[i] = toupper(s[i]); 
	}
	return s ;
}
int countWord(char s[]){
	int count = 0 , i ; 
	for(i = 0 ; i < strlen(s) ; i++){
		if(s[i] != ' ' &&(i == 0)||s[i-1]==' ' )
		count++ ;
	}
	return count ; 
}
int countDigit(char s[] )
{
		int count = 0 , i ; 
	for(i = 0 ; i < strlen(s) ; i++){
		if(s[i] = isdigit(s[i]) )
		count++ ;
	}
	return count ; 
}
int countSo(char s[] )
{
		int count = 0 , i ; 
	for(i = 0 ; i < strlen(s) ; i++){
		if(isdigit(s[i]) != 0 && isdigit(s[i-1]) == 0 )
		count++ ;
	}
	return count ; 
}
int CountSubString(char s1[], char s2[]){
	int count = 0 ;
	char *ptr=strstr(s1 , s2 );
	while(ptr != NULL){
		count ++ ;
		ptr ++ ;
		ptr = strstr(ptr , s2);
	}
	return count ;
}


int main() {
	char  s1[30] ;
	gets(s1);
	trim(s1);
	nameString(s1);
	countDigit(s1);
	
	countSo(s1);
	puts(s1);
	return 0 ;
}