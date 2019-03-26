#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

#define ID  5  //第几次调查
#define PASH  "G:\\2.txt" //存入
#define BIAOJI 10    //是排名前几标记出来

#define OUT_size 150   //排名前 多少 位
#define MAX 500000   //可放入最大单词

typedef struct Word
{
	char arr[30];   //存放单词  '\0'结束
	int count;    //当前单词的个数
}Word;//存储每个单词

typedef struct Num
{
	Word *brr;//指向某一个单词的结构体
	int length;//总单词数
	int listsize;//可放入最大单词
}N;//总单词数量  //12字节

bool Is_Alpha(char p) 
{
	if(p >= 'a' && p <= 'z' 
		|| p >= 'A' && p <= 'Z')
	{//是小写 或 是 大写
		return true;
	}
	else if(p == '\'' 
		|| p == '’' 
		|| p == '‘' 
		|| p == '-' 
		|| p == '—' 
		|| p == '\'')
	{//是'\'' 或'’' 或'‘' 
		//或 '-' 或 '—'或 '\''
		return true;
	}
	return false;
}

//得到文件当中的字节数
int file_size(char* path)  
{  
	assert (path != NULL);//断言

	FILE *fp = fopen (path, "r");//打开文件
	assert (fp != NULL);//断言
	/*int size = 0;//文件大小赋给size
	char ch;
	while ( fread(&ch,sizeof(char),1,fp) != -1 )
	{
		size++;
	}*/
	fseek(fp,0,2);  //fseek(fp,0,2)；其中的2就是SEEK_END
    int size=ftell(fp);//size接收文件ftell（使位置指针地址）指令后，文件大小

	fclose(fp);//关闭文件
	fp = NULL;//指针指NULL

	return size;//返回 文件大小
}

//函数功能：把每一个单词存放到对应的word结构体当中
void Chul(char *str,N *temp,int size)
{
	assert(str != NULL && temp !=NULL);//断言
	int size_i = 0;//用于避免超过文件长度的下标
	int i = 0;//用于表示的(*temp).brr[i]下标
	int j = 0;//用于(*temp).brr[i].arr[j]的下标
	for (; size_i<size ;size_i++)
	{  
		if(Is_Alpha(str[size_i]))//判断是不是字母
		{//是
			//将文件str[size_i])的字母  赋给(*temp).brr[i].arr[j]
			(*temp).brr[i].arr[j] = str[size_i];
			j++;//赋值后单词arr[]数组下标+1
			if(Is_Alpha(str[size_i]) && ! Is_Alpha(str[size_i+1]))
			{//判断str[size_i+1]是不是字母      //不是
				(*temp).brr[i].arr[j] = '\0';//加入'\0'给单词
				temp->length++;//文章  从单词数+1
				i++;//(*temp).brr[i]中的i++;      指向下一个单词
				j= 0;//是arr[j]的下标为0，从头开始
			}
		}
	}
}

//len代表总共单词的个数
void Cshcount(N *temp,int len)
{
	assert(temp !=NULL);//断言
	int i = 0;//用于避免超过总单词数长度的下标
	for (; i<len ;i++)
	{
		(*temp).brr[i].count = 1;//单词次数 改为1
	}
}

//len代表总共单词的个数
void Mycompare(N *temp, int len)
{
	assert(temp !=NULL);//断言
	int i = 0;//用于避免超过文件长度的下标
	for (; i<len ;i++)
	{
		if((*temp).brr[i].count > 0)//查看单词出现数是否大于0
		{//是
			int j= i +1;//用于查看下一个单词的下标
			for(;j<len;j++)//避免超过文件长度
			{
				if((*temp).brr[j].count > 0)//查看单词出现数是否大于0
				{
					if(strcmp((*temp).brr[i].arr,(*temp).brr[j].arr) == 0)
					{//查看两个单词是否一样
						(*temp).brr[i].count++;//前一个++
						(*temp).brr[j].count = 0;//后一个改为0
					}
				}
			}
		}
	}
}

void Myprint(N *temp,int len)
{
	assert(temp !=NULL);//断言
	//FILE *fw = fopen(PASH,"w");//存入新文档
	//assert(fw !=NULL);//断言
	//fprintf(fw,"\n第%d次调查了%d个单词：（其中前%d名）\n\n",ID,(*temp).length, OUT_size);//输出总调查单词个数
	//fprintf(fw,"----------------------------------------------------------\n");
	
	printf("\n第%d次调查了%d个单词：（其中前%d名）\n\n",ID,(*temp).length, OUT_size);//输出总调查单词个数
	printf("----------------------------------------------------------\n");

	int i = 1;//用于避免超过输出排行
	int tmp_big = 0;//用于记录现在最大出现单词的次数
	int big = 0;//用于记录现在最大出现单词的次数的 单词的下标
	for (; i<= OUT_size ;i++)
	{
		int j = 0;//用于避免超过总单词数长度的下标  逐个访问单词
		for(; j<len ;j++)
		{
			if ( (*temp).brr[j].count > tmp_big)//看 现访问的单词是否大于 之前最大出现单词的次数
			{//是
				tmp_big = (*temp).brr[j].count;//使tmp_big  还是最大的
				big = j;//记录现在最大出现单词的次数的 单词的下标
			}
		}
		if(0 == tmp_big)//防止单词输出完后  用于记录现在最大出现单词的次数=0 还在输出
		{
			return ;
		}
		(*temp).brr[big].count = 0;//使记录最大出现单词的次数 变为0

		//fprintf(fw,"    第%4d：",i );
		//fprintf (fw,"%15s",(*temp).brr[big].arr);//输出单词
		//fprintf (fw,"%7d",tmp_big);//输出次数
		//fprintf (fw,"%7.2lf%%",(float)tmp_big*100/(float)temp->length);//输出单词
		//BIAOJI == i ? fprintf(fw,"\n----------------------------------------------------------\n" ) : fprintf(fw,"\n" );
		
		printf("    第%4d：",i );
		printf ("%15s",(*temp).brr[big].arr);//输出单词
		printf ("%7d",tmp_big);//输出次数
		printf ("%7.2lf%%",(float)tmp_big*100/(float)temp->length);//输出单词
		BIAOJI == i ? printf("\n----------------------------------------------------------\n" ) : printf("\n" );
		
		tmp_big = 0;//用于记录现在最大出现单词的次数 变为0
		big = 0;//用于记录现在最大出现单词的次数的 单词的下标 变为0
	}
	//fclose(fw);//关闭文件
	//fw = NULL;//指针指NULL
}

int main()
{
	N temp;//建立总结构体
	temp.brr = (Word*)malloc(MAX*sizeof(Word));//设置单词结构体个数和内存
	temp.length = 0;//记录总单词个数
	temp.listsize = MAX;//最大可放总单词个数（限定）
	char *path = "G:\\1.txt";//文件所在位置
	FILE *fr = fopen(path, "r");//打开文件
	assert (fr != NULL);//断言

	int size = file_size(path);//有多少个字节
	//str作用就是  将来把文件内的数据 读到str里面
	char *str =(char *)malloc(size*sizeof(char));
	
	//把文件当中的所有字节全部挪到了str数组里面
	for(int i=0;i<size;i++)
	{
		str[i] = fgetc(fr);//将文件所有字节全部挪到了str数组
	}
	
	//把str里面读取到的单词，挨个放入对应的world结构体当中
	Chul(str,&temp,size);

	//把所有的单词个数置为1了
	Cshcount(&temp,temp.length);

	//将所有的结构体当中的单词，进行一次对比，相同另一个置为0
	Mycompare(&temp,temp.length);
	//printf ("%d \n\n\n\n\n",sizeof(N));
	//输出排行榜前OUT_size个单词的 单词 和 次数
	Myprint(&temp,temp.length);

	free(temp.brr);//释放单词所占内存
	free(str);//释放str数组
	
	return 0;
}
