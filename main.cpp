#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Account
{
	char username[100];
	char password[100];

	struct Account * next;
};
typedef struct Account Account;

Account * head=NULL;
Account * tail=NULL;

Account * curAccount=NULL;

//找到返回1，找不到返回0
int findAccount(Account a)
{
	Account * curP=head;
	while(curP!=NULL)
	{
		if((strcmp(curP->username,a.username)==0)&&(strcmp(curP->password,a.password)==0))
		{
			curAccount = curP;
			return 1;
		}
		curP=curP->next;
	}
	return 0;
}

void updatePassword()
{
	char oldPassword[100]={'\0'};
	printf("请输入旧密码：\n");
	
	scanf("%s",oldPassword);
	if(strcmp(oldPassword,curAccount->password)==0)
	{
		printf("请输入新密码：\n");
		scanf("%s",curAccount->password);
	}
	else
	{
		printf("密码错误，不能修改！\n");
	}

}

void showMenu()
{
	system("cls");
	printf("修改密码请按1：\n");

	updatePassword();
}

void signIn()
{
	Account a;
	printf("请输入账号：");
	scanf("%s",a.username);

	printf("请输入密码：");
	scanf("%s",a.password);

	if(findAccount(a))
	{
		printf("登录成功\n");
		showMenu();
	}
	else
	{
		printf("登录失败！\n");
	}
}

//加载成功返回1，加载失败返回0
int loadData()
{
	FILE* fp=fopen("D:\\atm.txt","r");
	if(fp==NULL)
	{
		return 0;
	}
	else
	{
		while(!feof(fp))
		{
			//创建结点(堆)
			Account * newNode=(Account *)malloc(sizeof(Account));
			//结点初始化
			newNode->next=NULL;
			fscanf(fp,"%s %s\n",newNode->username,newNode->password);

			//添加结点到链表
			if(head==NULL)
			{
				head=newNode;
				tail=newNode;
			}
			else
			{
				tail->next=newNode;
				tail=newNode;
			}
		}
		fclose(fp);
		return 1;
	}
}

void printLinkedList()
{
	Account * curP=head;
	while(curP!=NULL)
	{
		printf("%s\t%s\n",curP->username,curP->password);
		curP=curP->next;
	}
}


int main()
{
	int status=loadData();
	if(status==1)
	{
		printf("加载成功!\n");
	}
	else
	{
		printf("加载失败!\n");
	}

	printLinkedList();

	signIn();

	return 0;
}