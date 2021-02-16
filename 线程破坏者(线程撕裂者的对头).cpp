//文件名：test.cpp
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define NUM_THREADS	99999999

pthread_t threads[NUM_THREADS];
int indexes[NUM_THREADS];//用数组来保存i的值

void *Killer(void *threadid){
	int killer[40000];
	int i = 0;
	//对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
	while(true){
		int tid = *((int*)threadid);
		cout<<"Kill, ID: "<<tid<<endl;
		cout<<"main(), 创建线程: "<<i<<endl;
		indexes[i] = i;
		killer[i] = pthread_create(&threads[i], NULL, Killer, (void *)&(indexes[i]));
		if(killer[i]){
			cout<<"Error: 无法创建线程  "<<killer[i]<<endl;
			exit(-1);
		}
		i++;
	}
}

int main(){
	char x;
	cout<<"使用说明："<<endl; 
	cout<<"    1.本程序将会创建大量线程，请注意电脑安全"<<endl; 
	cout<<"    2.如何观看效果----打开任务管理器，选择 性能 -> CPU，查看\"线程\"&\"句柄\""<<endl; 
	cout<<"    3.实测R5 3500U 4C8T 用时约20s达到100000个句柄，仍然可以正常工作"<<endl; 
	cout<<"          i5 6267U 2C4T 用时约10s达到100000个句柄，开始变卡"<<endl; 
	cout<<"    4.请把本程序添加开机启动项[滑稽]"<<endl; 
	cout<<"您是否要开始本程序？输入任意字符开始，输入\"n\"或关闭窗口退出程序"<<endl; 
	cin>>x;
	if(x == 'n')
		return 0;
	int rc;
	int i = 0;
	while(true)
	{
		cout<<"main(), 创建线程: "<<i<<endl;
		indexes[i] = i; //先保存i的值
		//传入的时候必须强制转换为void* 类型，即无类型指针
		rc = pthread_create(&threads[i], NULL, Killer, (void *)&(indexes[i]));
		if(rc){
			cout<<"Error: 无法创建线程  "<<rc<<endl;
			exit(-1);
		}
		i++;
	}
	
}
