//�ļ�����test.cpp
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS	99999999

pthread_t threads[NUM_THREADS];
int indexes[NUM_THREADS];//������������i��ֵ

void *Killer(void *threadid){
	int killer[40000];
	int i = 0;
	//�Դ���Ĳ�������ǿ������ת������������ָ���Ϊ������ָ�룬Ȼ���ٶ�ȡ
	while(true){
		int tid = *((int*)threadid);
		cout<<"Kill, ID: "<<tid<<endl;
		cout<<"main(), �����߳�: "<<i<<endl;
		indexes[i] = i;
		killer[i] = pthread_create(&threads[i], NULL, Killer, (void *)&(indexes[i]));
		if(killer[i]){
			cout<<"Error: �޷������߳�  "<<killer[i]<<endl;
			exit(-1);
		}
		i++;
	}
}

int main(){
	char x;
	cout<<"ʹ��˵����"<<endl; 
	cout<<"    1.�����򽫻ᴴ�������̣߳���ע����԰�ȫ"<<endl; 
	cout<<"    2.��ιۿ�Ч��----�������������ѡ�� ���� -> CPU���鿴\"�߳�\"&\"���\""<<endl; 
	cout<<"    3.ʵ��R5 3500U 4C8T ��ʱԼ20s�ﵽ100000���������Ȼ������������"<<endl; 
	cout<<"          i5 6267U 2C4T ��ʱԼ10s�ﵽ100000���������ʼ�俨"<<endl; 
	cout<<"    4.��ѱ�������ӿ���������[����]"<<endl; 
	cout<<"���Ƿ�Ҫ��ʼ���������������ַ���ʼ������\"n\"��رմ����˳�����"<<endl; 
	cin>>x;
	if(x == 'n')
		return 0;
	int rc;
	int i = 0;
	while(true)
	{
		cout<<"main(), �����߳�: "<<i<<endl;
		indexes[i] = i; //�ȱ���i��ֵ
		//�����ʱ�����ǿ��ת��Ϊvoid* ���ͣ���������ָ��
		rc = pthread_create(&threads[i], NULL, Killer, (void *)&(indexes[i]));
		if(rc){
			cout<<"Error: �޷������߳�  "<<rc<<endl;
			exit(-1);
		}
		i++;
	}
	
}
