#include<stdio.h>
#include<string.h>
FILE *curfile;
char c[100];
int board[9][9]; /* Declaration of my chess board Positions from 1*1 to 8*8 are used in the program.*/
/*Declaration of coins 
        Here in the program I give integer number to coins of each type for easier retrival
     1 - Black Soldier            11 - White Soldier
	 2 - Black Rook               12 - White Rook
	 3 - Black Knight             13 - White Knight
	 4 - Black Bishop             14 - White Bishop
	 5 - Black Queen              15 - White Queen
	 6 - Black King               16 - White King
	 
	 The difference between Black and White coins is a difference of 10,  Hence the one's digit gives us the coin types and ten's digit gives me the colour of the coin
	 Ten's digit 0 - Black
	 Ten's digit 1 - White
*/
char coinName[][10]={"","B_(P)","B_R","B_N","B_B","B_Q","B_K","","","","","W_(P)","W_R","W_N","W_B","W_Q","W_K"};
int getInput(int player);
int checkRowColumn(int movei[],int movej[],int i,int j,int mi);
int checkDiagonals(int movei[],int movej[],int i,int j,int mi);
int queen(int i,int j,int color);
int bishop(int i,int j,int color);
int knight(int i,int j,int color);
int rook(int i,int j,int color);
int soldier(int i,int j,int color);
int king(int i,int j,int color);
int printMoves(int i,int j,int coin,int color);
void printHeader();
void print();
void initialize()
{
	/*This function is called only once to initialize my chess board*/	
	/* All the Board values are initialized to -1 to indicate that there is no coin*/
	int i,j;
	for(i=0;i<=8;i++)
	{
		for(j=0;j<=8;j++)
			board[i][j]=-1;
	}

	/*Initial Declaration of my Chess Board*/

	/*           White                           Black*/
 	board[8][1]=12;						board[1][1]=2;                   
 	board[8][2]=13;                     board[1][2]=3;
 	board[8][3]=14;						board[1][3]=4;
 	board[8][4]=16;						board[1][4]=6;
 	board[8][5]=15;						board[1][5]=5;
 	board[8][6]=14;						board[1][6]=4;
 	board[8][7]=13;						board[1][7]=3;
 	board[8][8]=12;						board[1][8]=2;
 
 	/* Second Row From Top is for Black Soldier */
 	for(i=1;i<=8;i++)
 		board[2][i]=1;
	/* Second Row From Bottom is for White Soldier */
	for(i=1;i<=8;i++)
 		board[7][i]=11;	
}
void print()
{
	/*This Function prints the Chess Board*/
	printf("           a           b           c           d           e           f           g           h\n\n");
	int i,j;
	for(i=1;i<=8;i++)
	{
		printf("%d",i);
		for(j=1;j<=8;j++)
		{
			/* Top Row */
			if(board[i][j]==-1)
				printf("%12s","");
			else
				printf("%12s",coinName[board[i][j]]);
		}
		printf("\n\n");
	}
}

void printHeader()
{
	printf("                                      Welcome to game of chess\n\n");
	printf("                            Player 1 - White");
	printf("              Player 2 - Black\n\n\n");
}
int printMoves(int i,int j,int coin,int color)
{
	/* This function Prints all the Valid Moves of the Given Coin */
	/*
	   i  -  Row Index
	   j  -  Column Index
	   coin - Coin Type
	   color - Color of The coin
	*/
	int moves;
	switch(coin)
	{
		case 1 : moves=soldier(i,j,color);break;
		case 2 : moves=rook(i,j,color);break;
		case 3 : moves=knight(i,j,color);break;
		case 4 : moves=bishop(i,j,color);break;
		case 5 : moves=queen(i,j,color);break;
		case 6 : moves=king(i,j,color);break;
	}
	return (moves==0)?0:1;
		
}
int soldier(int i,int j,int color)
{
	int ti,movei[10],movej[10],mi=0,choice;
	if(color==1)
	{
		if(i-1>=1 && board[i-1][j]==-1){
			movei[mi]=i-1;movej[mi]=j;
			mi++;
		}
		if(i==7 && i-2>=1 && board[i-2][j]==-1){
			movei[mi]=i-2;movej[mi]=j;
			mi++;
		}
		if(i-1>=1 && j-1>=1 && board[i-1][j-1]!=-1 && board[i-1][j-1]/10==0){
			movei[mi]=i-1;movej[mi]=j-1;
			mi++;
		}
		if(i-1>=1 && j+1<=8 && board[i-1][j+1]!=-1 &&board[i-1][j+1]/10==0){
			movei[mi]=i-1;movej[mi]=j+1;
			mi++;
		}
	}
	else
	{
		if(i+1<=8 && board[i+1][j]==-1){
			movei[mi]=i+1;movej[mi]=j;
			mi++;
		}
		if(i==2 && i+2<=8 && board[i+2][j]==-1){
			movei[mi]=i+2;movej[mi]=j;
			mi++;
		}
		if(i+1<=8 && j+1<=8 && board[i+1][j+1]/10==1){
			movei[mi]=i+1;movej[mi]=j+1;
			mi++;
		}
		if(i+1<=8 && j-1>=1 && board[i+1][j-1]/10==1){
			movei[mi]=i+1;movej[mi]=j-1;
			mi++;
		}
	}
	if(mi==0)
		return 0;
	printf("Your Valid Moves  :\n");
	for(ti=0;ti<mi;ti++)
		printf("%d .  %c%d\n\n",ti+1,movej[ti]+'a'-1,movei[ti]);
	printf("\nEnter Your Choice  From 1 to %d  (Number) :",mi);
	scanf("%d",&choice);
	printf("%d  %d\n",movei[choice-1],movej[choice-1]);
	curfile=fopen(c,"a");
	fprintf(curfile,"%c%d --- > %c%d    %s\n",j+96,i,movej[choice-1]+96,movei[choice-1],coinName[board[i][j]]);
	fclose(curfile);
	board[movei[choice-1]][movej[choice-1]]=board[i][j];
	board[i][j]=-1;
	print();
	return 1;
}
int rook(int i,int j,int color)
{
	int ti,movei[100],movej[100],mi=0,choice;
	mi=checkRowColumn(movei,movej,i,j,mi);
	if(mi==0)
		return 0;
	for(ti=0;ti<mi;ti++)
		printf("%d .  %c%d\n\n",ti+1,movej[ti]+'a'-1,movei[ti]);
	printf("\nEnter Your Choice  From 1 to %d  (Number) :",mi);
	scanf("%d",&choice);
	printf("%d  %d\n",movei[choice-1],movej[choice-1]);
	curfile=fopen(c,"a");
	fprintf(curfile,"%c%d --- > %c%d    %s\n",j+96,i,movej[choice-1]+96,movei[choice-1],coinName[board[i][j]]);
	fclose(curfile);
	board[movei[choice-1]][movej[choice-1]]=board[i][j];
	board[i][j]=-1;
	print();
	return 1;
}
int knight(int i,int j,int color)
{
	int ti,ii,a[]={2,2,-2,-2,1,1,-1,-1};
	int       b[]={-1,1,1,-1,2,-2,2,-2};
	int movei[100],movej[100],mi=0,choice;
	for(ii=0;ii<8;ii++)
	{
		int tempi=i+a[ii],tempj=j+b[ii];
		if(tempi>=1 && tempi<=8 && tempj>=1 && tempj<=8 && (board[tempi][tempj]==-1 || board[tempi][tempj]/10!=color))
		{
			movei[mi]=tempi;movej[mi]=tempj;
			mi++;
		}
	}
	if(mi==0)
		return 0;
	for(ti=0;ti<mi;ti++)
		printf("%d .  %c%d\n\n",ti+1,movej[ti]+'a'-1,movei[ti]);
	printf("\nEnter Your Choice  From 1 to %d  (Number) :",mi);
	scanf("%d",&choice);
	printf("%d  %d\n",movei[choice-1],movej[choice-1]);
	curfile=fopen(c,"a");
	fprintf(curfile,"%c%d --- > %c%d    %s\n",j+96,i,movej[choice-1]+96,movei[choice-1],coinName[board[i][j]]);
	fclose(curfile);
	board[movei[choice-1]][movej[choice-1]]=board[i][j];
	board[i][j]=-1;
	print();
	return 1;
}
int king(int i,int j,int color)
{
	int ti,ii,a[]={1,-1,0,0};
	int b[]={0,0,1,-1};
	int movei[100],movej[100],mi=0,choice;
	for(ii=0;ii<4;ii++)
	{
		int tempi=i+a[ii],tempj=j+b[ii];
		if(tempi>=1 && tempi<=8 && tempj>=1 && tempj<=8 && (board[tempi][tempj]==-1 || board[tempi][tempj]/10!=color))
		{
			movei[mi]=tempi;movej[mi]=tempj;
			mi++;
		}
	}
	if(mi==0)
		return 0;
	for(ti=0;ti<mi;ti++)
		printf("%d .  %c%d\n\n",ti+1,movej[ti]+'a'-1,movei[ti]);
	printf("\nEnter Your Choice  From 1 to %d  (Number) :",mi);
	scanf("%d",&choice);
	printf("%d  %d\n",movei[choice-1],movej[choice-1]);
	curfile=fopen(c,"a");
	fprintf(curfile,"%c%d --- > %c%d    %s\n",j+96,i,movej[choice-1]+96,movei[choice-1],coinName[board[i][j]]);
	fclose(curfile);
	board[movei[choice-1]][movej[choice-1]]=board[i][j];
	board[i][j]=-1;
	print();
	return 1;
}
int bishop(int i,int j,int color)
{
	int ti,movei[100],movej[100],mi=0,choice;
	mi=checkDiagonals(movei,movej,i,j,mi);
	if(mi==0)
		return 0;
	for(ti=0;ti<mi;ti++)
		printf("%d .  %c%d\n\n",ti+1,movej[ti]+'a'-1,movei[ti]);
	printf("\nEnter Your Choice  From 1 to %d  (Number) :",mi);
	scanf("%d",&choice);
	printf("%d  %d\n",movei[choice-1],movej[choice-1]);
	curfile=fopen(c,"a");
	fprintf(curfile,"%c%d --- > %c%d    %s\n",j+96,i,movej[choice-1]+96,movei[choice-1],coinName[board[i][j]]);
	fclose(curfile);
	board[movei[choice-1]][movej[choice-1]]=board[i][j];
	board[i][j]=-1;
	print();
	return 1;
}
int queen(int i,int j,int color)
{
	int ti,movei[100],movej[100],mi=0,choice;
	mi=checkDiagonals(movei,movej,i,j,mi);
	mi=checkRowColumn(movei,movej,i,j,mi);
	if(mi==0)
		return 0;
	for(ti=0;ti<mi;ti++)
		printf("%d .  %c%d\n\n",ti+1,movej[ti]+'a'-1,movei[ti]);
	printf("\nEnter Your Choice  From 1 to %d  (Number) :",mi);
	scanf("%d",&choice);
	printf("%d  %d\n",movei[choice-1],movej[choice-1]);
	curfile=fopen(c,"a");
	fprintf(curfile,"%c%d --- > %c%d    %s\n",j+96,i,movej[choice-1]+96,movei[choice-1],coinName[board[i][j]]);
	fclose(curfile);
	board[movei[choice-1]][movej[choice-1]]=board[i][j];
	board[i][j]=-1;
	print();
	return 1;
}
int checkDiagonals(int movei[],int movej[],int i,int j,int mi)
{
	int choice,tempi=i,tempj=j;
	while(tempi-1>=1 && tempj-1>=1 && board[tempi-1][tempj-1]==-1){
		movei[mi]=tempi-1;movej[mi]=tempj-1;mi++;
		tempi--;tempj--;
	}
	if(tempi-1>=1 && tempj-1<=8 && board[tempi-1][tempj-1]/10!=board[i][j]/10){
		movei[mi]=tempi-1;movej[mi]=tempj-1;mi++;
		tempi--;tempj--;
	}
	tempi=i;tempj=j;
	while(tempi+1<=8 && tempj+1<=8 && board[tempi+1][tempj+1]==-1){
		movei[mi]=tempi+1;movej[mi]=tempj+1;mi++;
		tempi++;tempj++;
	}
	if(tempi+1<=8 && tempj+1<=8 && board[tempi+1][tempj+1]/10!=board[i][j]/10){
		movei[mi]=tempi+1;movej[mi]=tempj+1;mi++;
		tempi++;tempj++;
	}
	tempi=i;tempj=j;
	while(tempj-1>=1 && tempi+1<=8 && board[tempi+1][tempj-1]==-1){
		movei[mi]=tempi+1;movej[mi]=tempj-1;mi++;
		tempj--;tempi++;
	}
	if(tempj-1>=1 && tempi+1<=8 && board[tempi+1][tempj-1]/10!=board[i][j]/10){
		movei[mi]=tempi+1;movej[mi]=tempj-1;mi++;
		tempj--;tempi++;
	}
	tempi=i;tempj=j;
	while(tempj+1<=8 && tempi-1>=1 && board[tempi-1][tempj+1]==-1){
		movei[mi]=tempi-1;movej[mi]=tempj+1;mi++;
		tempj++;tempi--;
	}
	if(tempj+1<=8 && tempi-1>=1 && board[tempi-1][tempj+1]/10!=board[i][j]/10){
		movei[mi]=tempi-1;movej[mi]=tempj+1;mi++;
		tempj++;tempi--;
	}
	return mi;
}
int checkRowColumn(int movei[],int movej[],int i,int j,int mi)
{
	int choice,tempi=i,tempj=j;
	while(tempi-1>=1 && board[tempi-1][tempj]==-1){
		movei[mi]=tempi-1;movej[mi]=tempj;mi++;
		tempi--;
	}
	if(tempi-1>=1 && board[tempi-1][tempj]/10!=board[i][j]/10){
		movei[mi]=tempi-1;movej[mi]=tempj;mi++;
		tempi--;
	}
	tempi=i;tempj=j;
	while(tempi+1<=8 && board[tempi+1][tempj]==-1){
		movei[mi]=tempi+1;movej[mi]=tempj;mi++;
		tempi++;
	}
	if(tempi+1<=8 && board[tempi+1][tempj]/10!=board[i][j]/10){
		movei[mi]=tempi+1;movej[mi]=tempj;mi++;
		tempi++;
	}
	tempi=i;tempj=j;
	while(tempj-1>=1 && board[tempi][tempj-1]==-1){
		movei[mi]=tempi;movej[mi]=tempj-1;mi++;
		tempj--;
	}
	if(tempj-1>=1 && board[tempi][tempj-1]/10!=board[i][j]/10){
		movei[mi]=tempi;movej[mi]=tempj-1;mi++;
		tempj--;
	}
	tempi=i;tempj=j;
	while(tempj+1<=8 && board[tempi][tempj+1]==-1){
		movei[mi]=tempi;movej[mi]=tempj+1;mi++;
		tempj++;
	}
	if(tempj+1<=8 && board[tempi][tempj+1]/10!=board[i][j]/10){
		movei[mi]=tempi;movej[mi]=tempj+1;mi++;
		tempj++;
	}
	return mi;
}
int getInput(int player)
{
	int ii,jj;
	while(1)
	{
			/* Taking Input Until the player Enters a valid coin Type */
			char input[10];
			scanf("%s",input);
			ii=(int)input[1]-'0';
			jj=(int)input[0]-96;
			if(!(player&1) && board[ii][jj]>=11 && board[ii][jj]<=16)	
				break;
			
			if((player&1) && board[ii][jj]>=1 && board[ii][jj]<=6)
				break;
			printf("You Entered an Invalid Input\nEnter the Correct Input key\n\n");
	}
	int success=printMoves(ii,jj,board[ii][jj]%10,board[ii][jj]/10);
	return (success)?1:0;
}
int convertToNumber(char c[])
{
	int i,l=strlen(c),num=0,temp=1;
	for(i=l-1;i>=0;i--)
	{
		num+=((int)(c[i]-'0'))*temp;
		temp*=10;
	}	
	return num;
}
void convertToString(char ct[],int num)
{
	int size=0;
	while(num>0)
	{
		ct[size++]=(num%10)+'0';
		num/=10;
	}
	int i=0,j=size-1;
	while(i<j)
	{
		char cc=ct[i];
		ct[i]=ct[j];
		ct[j]=cc;i++;j--;
	}
	ct[size++]='.';
	ct[size++]='t';
	ct[size++]='x';
	ct[size++]='t';
	ct[size]='\0';
}
int main()
{
	printHeader();
	initialize();
	print();
	int i=0,count;
	FILE *f1=fopen("count.txt","r");
	fscanf(f1,"%s",c);
	fclose(f1);
	count=convertToNumber(c);
	FILE *f2=fopen("count.txt","w");
	fprintf(f2,"%d",count+1);
	fclose(f2);
	convertToString(c,count);
	while(1)
	{
		/* If i is even -  Move for Player - 1
		   else if i is odd Move for Player - 2 */
		if(i&1)
			printf("Enter Your Move - Player 2\n"); 
		else
			printf("Enter Your Move - Player 1\n");
		while(1)
		{
			int moves=getInput(i);
			if(moves==0)
				printf("There are No valid Moves for your Given Coin.\nEnter another Coin\n\n");
			else
				break;
		}
		i++;
	}
	return 0;
}
