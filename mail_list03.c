#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <getch.h>
#include <stdlib.h>


typedef struct Mail
{
  char name[20];
  char sex;
  char tel[12];

}Mail;

Mail* mails;//定义结构类型指针名为mails
char get_cmd(char start,char end)
{
	char cmd = 0;
	for(;;)
	{
	  cmd = getch();
      if(start <= cmd && cmd <= end)
	  {
		  printf("%c\n",cmd);
		  break;
	  }
	}
	return cmd;
}

char* get_str(char* str,int size)
{
	fgets(str,size,stdin);//会在末尾处产生一个\n
	int len = strlen(str);
	if('\n' == str[len-1])
	{
		str[len-1] = '\0';
	}
	else
	{
         stdin->_IO_read_ptr =stdin->_IO_read_end;
	}
	return str;
}

void add_mail(void)
{
     printf("\n%s\n",__func__);//作用：编译时会替换__func__为该语句所在的函数名
	 //找到一个空位置
	 int index = 0;
	 while(mails[index].sex)
	 {
		 index++;
	 }
	 printf("请输入姓名:");
	 get_str(mails[index].name,20);

	 printf("请输入性别(m男/w女):");
     mails[index].sex = getch();
	 printf("%c\n",mails[index].sex);

	 printf("请输入电话号码:");
	 get_str(mails[index].tel,12);
	 puts("添加联系人成功!");


}

void del_mail(void)
{
     printf("\n%s\n",__func__);
	 char str[20] = {};
	 printf("请输入你想要删除的联系人姓名:");
	 get_str(str,20);
	 for(int i = 0;i < 100;i++)
	 {
		 if(mails[i].sex && 0 == strcmp(str,mails[i].name))
		 {
			 mails[i].sex = 0;
			 puts("删除联系人成功!");
			 return;
		 }
		 
	 }
	 puts("此联系人不存在,请重新输入");

}

void modify_mail(void)
{
     printf("\n%s\n",__func__);
	 char str[20] = {};
	 printf("请输入你想要修改的联系人姓名:");
	 get_str(str,20);
	 for(int i = 0;i < 100;i++)
	 {
		 if(mails[i].sex && 0 == strcmp(str,mails[i].name))
		 {
			 printf("请重新输入姓名:");
			 get_str(mails[i].name,20);

			 printf("请重新输入性别(m男/w女):");
			 mails[i].sex = getch();
			 printf("%c\n",mails[i].sex);

			 printf("请重新输入电话号码:");
			 get_str(mails[i].tel,12);
			 puts("修改联系人成功!");
			 return;
			 
		 }
		 
	 }
	 puts("要修改的联系人不存在,请重新输入");

}

void find_mail(void)
{
     printf("\n%s\n",__func__);
	 char str[20] = {};
	 printf("请输入要查找的联系人姓名或电话:");
	 get_str(str,20);
	 for(int i = 0; i < 100; i++)
	 {
		 if(mails[i].sex && 0 == strcmp(str,mails[i].name) || 0 == strcmp(str,mails[i].tel))
		 {
		 	 printf("%s %c %s\n",mails[i].name,mails[i].sex,mails[i].tel);
		 }
	 }

}

void all_mail(void)
{
     printf("\n%s\n",__func__);
	 for(int i = 0;i < 100;i++)
	 {
		 mails[i].sex && printf("%s %c %s\n",mails[i].name,mails[i].sex,mails[i].tel);
	 }

}

void start_mail(void)
{
	/*sex = malloc(100);
	bzero(sex,100);
	for(int i = 0;i <100;i++)
	{
		name[i] = malloc(20);
		bzero(name[i],20);
		tel[i] = malloc(20);
		bzero(tel[i],12);
	}*/

	mails = malloc(sizeof(Mail)*100);//相当于把要了100份Mail结构表
	bzero(mails,sizeof(Mail)*100);//置0
	//把数据从文件加载到内存储存
	//FILE* frp = fopen("mail.txt","r");文本形式
	FILE* frp = fopen("mail.bin","r");//二进制形式
	if(NULL == frp)
	{
		puts("加载文件失败!\n");
		return;
	}
	int index = 0;
	do{
		//fscanf(frp,"%s %c %s",mails[index].name,&mails[index].sex,mails[index].tel);
		fread(mails+index,1,sizeof(Mail),frp);
		index++;
	}while(!feof(frp));
	fclose(frp);
	
}

void exit_mail(void)
{
	/*free(sex);
	sex = NULL;
	for(int i = 0;i < 100;i++)
	{
		free(name[i]);//释放
		free(tel[i]);
	}
	bzero(name,sizeof(name));//置0
	bzero(tel,sizeof(tel));*/

	//保存数据到文件
	//FILE* fwp = fopen("mail.txt","w");
	FILE* fwp = fopen("mail.bin","w");
	if(NULL == fwp)
	{
		puts("文件保存失败!");
		
	}
	else
	{
		for(int i = 0;i < 100;i++)
		{
			//mails[i].sex && fprintf(fwp,"%s %c %s\n",mails[i].name,mails[i].sex,mails[i].tel);
			mails[i].sex && fwrite(mails+i,1,sizeof(Mail),fwp);
		}
	}
		fclose(fwp);
		free(mails);//释放
	    mails = NULL;//指针置空
}


int main()
{
	start_mail();
	while(true)
	{
		system("clear");
		puts("*****欢迎使用指针通讯录*****");
		puts("1、添加联系人");
		puts("2、删除联系人");
		puts("3、修改联系人");
		puts("4、查找联系人");
		puts("5、显示所有联系人");
		puts("6、退出通讯录");
		printf("请输入指令:\n");
		switch(get_cmd('1','6'))
		{
			case '1': add_mail();break;
			case '2': del_mail();break;
			case '3': modify_mail();break;
			case '4': find_mail();break;
			case '5': all_mail();break;
			case '6': exit_mail(); return 0;
            default:
			        puts("输入的指令有误!\n");
		
		}
		sleep(1);
	}
}
