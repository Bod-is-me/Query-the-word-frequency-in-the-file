#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

#define ID  5  //�ڼ��ε���
#define PASH  "G:\\2.txt" //����
#define BIAOJI 10    //������ǰ����ǳ���

#define OUT_size 150   //����ǰ ���� λ
#define MAX 500000   //�ɷ�����󵥴�

typedef struct Word
{
	char arr[30];   //��ŵ���  '\0'����
	int count;    //��ǰ���ʵĸ���
}Word;//�洢ÿ������

typedef struct Num
{
	Word *brr;//ָ��ĳһ�����ʵĽṹ��
	int length;//�ܵ�����
	int listsize;//�ɷ�����󵥴�
}N;//�ܵ�������  //12�ֽ�

bool Is_Alpha(char p) 
{
	if(p >= 'a' && p <= 'z' 
		|| p >= 'A' && p <= 'Z')
	{//��Сд �� �� ��д
		return true;
	}
	else if(p == '\'' 
		|| p == '��' 
		|| p == '��' 
		|| p == '-' 
		|| p == '��' 
		|| p == '\'')
	{//��'\'' ��'��' ��'��' 
		//�� '-' �� '��'�� '\''
		return true;
	}
	return false;
}

//�õ��ļ����е��ֽ���
int file_size(char* path)  
{  
	assert (path != NULL);//����

	FILE *fp = fopen (path, "r");//���ļ�
	assert (fp != NULL);//����
	/*int size = 0;//�ļ���С����size
	char ch;
	while ( fread(&ch,sizeof(char),1,fp) != -1 )
	{
		size++;
	}*/
	fseek(fp,0,2);  //fseek(fp,0,2)�����е�2����SEEK_END
    int size=ftell(fp);//size�����ļ�ftell��ʹλ��ָ���ַ��ָ����ļ���С

	fclose(fp);//�ر��ļ�
	fp = NULL;//ָ��ָNULL

	return size;//���� �ļ���С
}

//�������ܣ���ÿһ�����ʴ�ŵ���Ӧ��word�ṹ�嵱��
void Chul(char *str,N *temp,int size)
{
	assert(str != NULL && temp !=NULL);//����
	int size_i = 0;//���ڱ��ⳬ���ļ����ȵ��±�
	int i = 0;//���ڱ�ʾ��(*temp).brr[i]�±�
	int j = 0;//����(*temp).brr[i].arr[j]���±�
	for (; size_i<size ;size_i++)
	{  
		if(Is_Alpha(str[size_i]))//�ж��ǲ�����ĸ
		{//��
			//���ļ�str[size_i])����ĸ  ����(*temp).brr[i].arr[j]
			(*temp).brr[i].arr[j] = str[size_i];
			j++;//��ֵ�󵥴�arr[]�����±�+1
			if(Is_Alpha(str[size_i]) && ! Is_Alpha(str[size_i+1]))
			{//�ж�str[size_i+1]�ǲ�����ĸ      //����
				(*temp).brr[i].arr[j] = '\0';//����'\0'������
				temp->length++;//����  �ӵ�����+1
				i++;//(*temp).brr[i]�е�i++;      ָ����һ������
				j= 0;//��arr[j]���±�Ϊ0����ͷ��ʼ
			}
		}
	}
}

//len�����ܹ����ʵĸ���
void Cshcount(N *temp,int len)
{
	assert(temp !=NULL);//����
	int i = 0;//���ڱ��ⳬ���ܵ��������ȵ��±�
	for (; i<len ;i++)
	{
		(*temp).brr[i].count = 1;//���ʴ��� ��Ϊ1
	}
}

//len�����ܹ����ʵĸ���
void Mycompare(N *temp, int len)
{
	assert(temp !=NULL);//����
	int i = 0;//���ڱ��ⳬ���ļ����ȵ��±�
	for (; i<len ;i++)
	{
		if((*temp).brr[i].count > 0)//�鿴���ʳ������Ƿ����0
		{//��
			int j= i +1;//���ڲ鿴��һ�����ʵ��±�
			for(;j<len;j++)//���ⳬ���ļ�����
			{
				if((*temp).brr[j].count > 0)//�鿴���ʳ������Ƿ����0
				{
					if(strcmp((*temp).brr[i].arr,(*temp).brr[j].arr) == 0)
					{//�鿴���������Ƿ�һ��
						(*temp).brr[i].count++;//ǰһ��++
						(*temp).brr[j].count = 0;//��һ����Ϊ0
					}
				}
			}
		}
	}
}

void Myprint(N *temp,int len)
{
	assert(temp !=NULL);//����
	//FILE *fw = fopen(PASH,"w");//�������ĵ�
	//assert(fw !=NULL);//����
	//fprintf(fw,"\n��%d�ε�����%d�����ʣ�������ǰ%d����\n\n",ID,(*temp).length, OUT_size);//����ܵ��鵥�ʸ���
	//fprintf(fw,"----------------------------------------------------------\n");
	
	printf("\n��%d�ε�����%d�����ʣ�������ǰ%d����\n\n",ID,(*temp).length, OUT_size);//����ܵ��鵥�ʸ���
	printf("----------------------------------------------------------\n");

	int i = 1;//���ڱ��ⳬ���������
	int tmp_big = 0;//���ڼ�¼���������ֵ��ʵĴ���
	int big = 0;//���ڼ�¼���������ֵ��ʵĴ����� ���ʵ��±�
	for (; i<= OUT_size ;i++)
	{
		int j = 0;//���ڱ��ⳬ���ܵ��������ȵ��±�  ������ʵ���
		for(; j<len ;j++)
		{
			if ( (*temp).brr[j].count > tmp_big)//�� �ַ��ʵĵ����Ƿ���� ֮ǰ�����ֵ��ʵĴ���
			{//��
				tmp_big = (*temp).brr[j].count;//ʹtmp_big  ��������
				big = j;//��¼���������ֵ��ʵĴ����� ���ʵ��±�
			}
		}
		if(0 == tmp_big)//��ֹ����������  ���ڼ�¼���������ֵ��ʵĴ���=0 �������
		{
			return ;
		}
		(*temp).brr[big].count = 0;//ʹ��¼�����ֵ��ʵĴ��� ��Ϊ0

		//fprintf(fw,"    ��%4d��",i );
		//fprintf (fw,"%15s",(*temp).brr[big].arr);//�������
		//fprintf (fw,"%7d",tmp_big);//�������
		//fprintf (fw,"%7.2lf%%",(float)tmp_big*100/(float)temp->length);//�������
		//BIAOJI == i ? fprintf(fw,"\n----------------------------------------------------------\n" ) : fprintf(fw,"\n" );
		
		printf("    ��%4d��",i );
		printf ("%15s",(*temp).brr[big].arr);//�������
		printf ("%7d",tmp_big);//�������
		printf ("%7.2lf%%",(float)tmp_big*100/(float)temp->length);//�������
		BIAOJI == i ? printf("\n----------------------------------------------------------\n" ) : printf("\n" );
		
		tmp_big = 0;//���ڼ�¼���������ֵ��ʵĴ��� ��Ϊ0
		big = 0;//���ڼ�¼���������ֵ��ʵĴ����� ���ʵ��±� ��Ϊ0
	}
	//fclose(fw);//�ر��ļ�
	//fw = NULL;//ָ��ָNULL
}

int main()
{
	N temp;//�����ܽṹ��
	temp.brr = (Word*)malloc(MAX*sizeof(Word));//���õ��ʽṹ��������ڴ�
	temp.length = 0;//��¼�ܵ��ʸ���
	temp.listsize = MAX;//���ɷ��ܵ��ʸ������޶���
	char *path = "G:\\1.txt";//�ļ�����λ��
	FILE *fr = fopen(path, "r");//���ļ�
	assert (fr != NULL);//����

	int size = file_size(path);//�ж��ٸ��ֽ�
	//str���þ���  �������ļ��ڵ����� ����str����
	char *str =(char *)malloc(size*sizeof(char));
	
	//���ļ����е������ֽ�ȫ��Ų����str��������
	for(int i=0;i<size;i++)
	{
		str[i] = fgetc(fr);//���ļ������ֽ�ȫ��Ų����str����
	}
	
	//��str�����ȡ���ĵ��ʣ����������Ӧ��world�ṹ�嵱��
	Chul(str,&temp,size);

	//�����еĵ��ʸ�����Ϊ1��
	Cshcount(&temp,temp.length);

	//�����еĽṹ�嵱�еĵ��ʣ�����һ�ζԱȣ���ͬ��һ����Ϊ0
	Mycompare(&temp,temp.length);
	//printf ("%d \n\n\n\n\n",sizeof(N));
	//������а�ǰOUT_size�����ʵ� ���� �� ����
	Myprint(&temp,temp.length);

	free(temp.brr);//�ͷŵ�����ռ�ڴ�
	free(str);//�ͷ�str����
	
	return 0;
}
