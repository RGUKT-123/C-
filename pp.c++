
//Bankers(6-115)-Fits(121-383)-Disk(387-887)-pga(889-1109)-scheduling(rest)
//1.BANKSER'S ALGORITHM


#include<bits/stdc++.h>
using namespace std;
int main(){
	cout<<"Enter no of Processes :";
	int p;
	cin>>p;
	cout<<"Enter no of Resources :";
	int r;
	cin>>r;
	int Allocation[p][r];
	cout<<"Enter no of Allocation :";
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			cin>>Allocation[i][j];
		}
	}
	int MAXAllocation[p][r];
	cout<<"Enter no of MAX Allocation :";
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			cin>>MAXAllocation[i][j];
		}
	}
	int Finish[p];
	int index=0;
	int Result[p];
	int Availability[r];
	cout<<"Enter the Availability :";
	for(int i=0;i<r;i++){
		cin>>Availability[i];
	}
	for(int i=0;i<p;i++){
		Finish[i]=0;
	}
	int Need[p][r];
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			Need[i][j]=MAXAllocation[i][j]-Allocation[i][j];
		}
	}
	
	int flag1;
	for(int k=0;k<p;k++){
		for(int i=0;i<p;i++){
			if(Finish[i]==0){
				flag1=1;
				for(int j=0;j<r;j++){
					if(Need[i][j] > Availability[j]){
						flag1=0;
						break;
					}
				}
				if(flag1==1){
					Result[index++]=i;//index++
					for(int y=0;y<r;y++){
						Availability[y]=Allocation[i][y]+Availability[y];
						Finish[i]=1;
					}
				}
			}
		}
	}
	cout<<"The Need Matrix : ";
	for(int i=0;i<p;i++){
		for(int j=0;j<r;j++){
			cout<<Need[i][j]<<" ";
		}
		cout<<""<<endl;
	}
	int flag2=1;
	for(int i=0;i<p;i++){
		if(Finish[i]!=1){
			flag2=0;
			cout<<"The Sequence is NOT safe."<<endl;
			break;
		}
	}
	if(flag2==1){
		cout<<"The Sequence is safe. Sequnece:"<<endl;
		for(int i=0;i<p-1;i++){
			cout<<"P"<<Result[i]+1<<"-> ";
		}
		cout<<"P"<<Result[p-1]+1<<endl;
	}
	
	return 0;
	
}


Enter no of Processes :5
Enter no of Resources :3
Enter no of Allocation :0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter no of MAX Allocation :7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter the Availability :3 3 2
The Need Matrix : 7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 
The Sequence is safe. Sequnece:
P2-> P4-> P5-> P1-> P3





//2.BestFit Algorithm

#include<bits/stdc++.h>
using namespace std;

void BestFit(int p,int b,int process[],int block[],int add){
	int Allocation[p];
	int Internal[p];
	int External=0;
	for(int i=0;i<p;i++){
		Internal[i]=0;
		Allocation[i]=-1;
	}
	int sum=0;
	for(int i=0;i<p;i++){
		int bf=-1;
		for(int j=0;j<b;j++){
			if(block[j] >= process[i]){
				if(bf==-1){
					bf=j;
				}
				else if(block[j] < block[bf]){
					bf=j;
				}
			}
		}
		if(bf!=-1){
			Allocation[i]=bf;
			Internal[i]=block[bf]-process[i];
			sum=sum+block[bf];
			block[bf]=0;
		}
	}
	External=add-sum;
	cout<<"ProcessID \t ProcessSize \t BlockAllocation \t InternalFrag"<<endl;
	for(int i=0;i<p;i++){
		cout<<i+1<<"\t\t";
		cout<<process[i]<<"\t\t";
		if(Allocation[i]!=-1){
			cout<<Allocation[i]+1<<"\t\t";
		}
		else{
			cout<<"Not Allocated"<<"\t";
		}
		cout<<Internal[i]<<"\t\t"<<endl;
	}
	if(External > 0){
		cout<<"External Fragmentation is Present :"<<External<<endl;
	}
	else{
		cout<<"External Fragmentation is NOT Present."<<endl;
	}
	
}

int main(){
	cout<<"Enter no of Processes :";
	int p;
	cin>>p;
	cout<<"Enter Processes :";
	int process[p];
	for(int i=0;i<p;i++){
		cin>>process[i];
	}
	cout<<"Enter no of Blocks :";
	int b;
	cin>>b;
	cout<<"Enter Blocks :";
	int block[b];
	int add=0;
	for(int i=0;i<b;i++){
		cin>>block[i];
		add=add+block[i];
	}
	BestFit(p,b,process,block,add);
	return 0;
}


Enter no of Processes :4
20 30 40 50 
Enter no of Blocks :5
10 20 30 10 20 
ProcessID 	 ProcessSize 	 BlockAllocation 	 InternalFrag
1		20		2	0		
2		30		3	0		
3		40		Not Allocated 0		
4		50		Not Allocated 0		
External Fragmentation is Present :40



//3.WorstFit Algorithm

#include<bits/stdc++.h>
using namespace std;

void WorstFit(int p,int b,int process[],int block[],int add){
	int Allocation[p];
	int Internal[p];
	int External=0;
	for(int i=0;i<p;i++){
		Internal[i]=0;
		Allocation[i]=-1;
	}
	int sum=0;
	for(int i=0;i<p;i++){
		int bf=-1;
		for(int j=0;j<b;j++){
			if(block[j] >= process[i]){
				if(bf==-1){
					bf=j;
				}
				else if(block[j] > block[bf]){
					bf=j;
				}
			}
		}
		if(bf!=-1){
			Allocation[i]=bf;
			Internal[i]=block[bf]-process[i];
			sum=sum+block[bf];
			block[bf]=0;
		}
	}
	External=add-sum;
	cout<<"ProcessID \t ProcessSize \t BlockAllocation \t InternalFrag"<<endl;
	for(int i=0;i<p;i++){
		cout<<i+1<<"\t\t";
		cout<<process[i]<<"\t\t";
		if(Allocation[i]!=-1){
			cout<<Allocation[i]+1<<"\t\t";
		}
		else{
			cout<<"Not Allocated"<<"\t";
		}
		cout<<Internal[i]<<"\t\t"<<endl;
	}
	if(External > 0){
		cout<<"External Fragmentation is Present :"<<External<<endl;
	}
	else{
		cout<<"External Fragmentation is NOT Present."<<endl;
	}
	
}

int main(){
	cout<<"Enter no of Processes :";
	int p;
	cin>>p;
	cout<<"Enter Processes :";
	int process[p];
	for(int i=0;i<p;i++){
		cin>>process[i];
	}
	cout<<"Enter no of Blocks :";
	int b;
	cin>>b;
	cout<<"Enter Blocks :";
	int block[b];
	int add=0;
	for(int i=0;i<b;i++){
		cin>>block[i];
		add=add+block[i];
	}
	WorstFit(p,b,process,block,add);
	return 0;
}

Enter no of Processes :4
Enter Processes :20 30 40 50
Enter no of Blocks :5
Enter Blocks :10 20 30 10 20
ProcessID 	 ProcessSize 	 BlockAllocation 	 InternalFrag
1		20		3		10		
2		30		Not Allocated	0		
3		40		Not Allocated	0		
4		50		Not Allocated	0		
External Fragmentation is Present :60



//4.FirstFit Algorithm

#include<bits/stdc++.h>
using namespace std;

void FirstFit(int p,int b,int process[],int block[],int add){
	int Allocation[p];
	int Internal[p];
	int External=0;
	for(int i=0;i<p;i++){
		Internal[i]=0;
		Allocation[i]=-1;
	}
	int sum=0;
	for(int i=0;i<p;i++){
		for(int j=0;j<b;j++){
			if(block[j] >= process[i]){
				Allocation[i]=j;
				Internal[i]=block[j]-process[i];
				sum=sum+block[j];
				block[j]=0;
				break;
			}
		}
	}
	External=add-sum;
	cout<<"ProcessID \t ProcessSize \t BlockAllocation \t InternalFrag"<<endl;
	for(int i=0;i<p;i++){
		cout<<i+1<<"\t\t";
		cout<<process[i]<<"\t\t";
		if(Allocation[i]!=-1){
			cout<<Allocation[i]+1<<"\t\t";
		}
		else{
			cout<<"Not Allocated"<<"\t";
		}
		cout<<Internal[i]<<"\t\t"<<endl;
	}
	if(External > 0){
		cout<<"External Fragmentation is Present :"<<External<<endl;
	}
	else{
		cout<<"External Fragmentation is NOT Present."<<endl;
	}
	
}

int main(){
	cout<<"Enter no of Processes :";
	int p;
	cin>>p;
	cout<<"Enter Processes :";
	int process[p];
	for(int i=0;i<p;i++){
		cin>>process[i];
	}
	cout<<"Enter no of Blocks :";
	int b;
	cin>>b;
	cout<<"Enter Blocks :";
	int block[b];
	int add=0;
	for(int i=0;i<b;i++){
		cin>>block[i];
		add=add+block[i];
	}
	FirstFit(p,b,process,block,add);
	return 0;
}

Enter no of Processes :4
Enter Processes :212 417 112 426
Enter no of Blocks :5
Enter Blocks :100 500 200 300 600
ProcessID 	 ProcessSize 	 BlockAllocation 	 InternalFrag
1		212		2		288		
2		417		5		183		
3		112		3		88		
4		426		Not Allocated	0		
External Fragmentation is Present :400



//5.Disk FCFS Algorithm

#include<bits/stdc++.h>
using namespace std;

void DiskFcfs(int n,int seq[],int Head){
	int Distance=0;
	int Current;
	int Seek=0;
	for(int i=0;i<n;i++){
		Current=seq[i];
		Distance=abs(Current-Head);
		Seek=Seek+Distance;
		Head=Current;
	}
	cout<<"The Total Operations are : "<<Seek<<endl;
	cout<<"The Sequence :"<<endl;
	for(int i=0;i<n;i++){
		cout<<seq[i]<<" ";
	}
	cout<<""<<endl;
}
int main(){
	int n;
	cout<<"Enter no of Sequence :";
	cin>>n;
	cout<<"Enter Sequence :";
	int seq[n];
	for(int i=0;i<n;i++){
		cin>>seq[i];
	}
	cout<<"Enter Head:";
	int Head;
	cin>>Head;
	DiskFcfs(n,seq,Head);
	return 0;
}


Enter no of Sequence :8
Enter Sequence :176 79 34 60 92 11 41 114
Enter Head:50
The Total Operations are : 510
The Sequence :
176 79 34 60 92 11 41 114 



//6.Disk SHORTEST Seek Time First


#include<bits/stdc++.h>
using namespace std;

void FindDist(int n,int req[],int Head,int Distance[][2]){
	for(int i=0;i<n;i++){
		Distance[i][0]=abs(Head-req[i]);
	}
}

int Findmin(int Distance[][2],int n){
	int index=-1;
	int min=1e9;
	for(int i=0;i<n;i++){
		if(!Distance[i][1] && Distance[i][0]<min){
			min=Distance[i][0];
			index=i;
		}
	}
	return index;
}

void DiskSstf(int n,int req[],int Head){//two req and seq
	if(n==0){
		return;//main
	}
	int Distance[n][2]={{0,0}};//imp
	int seq[n+1]={0};
	int Seek=0;
	for(int i=0;i<n;i++){
		seq[i]=Head;
		FindDist(n,req,Head,Distance);
		int index=Findmin(Distance,n);//index
		Distance[index][1]=1;
		Seek=Seek+Distance[index][0];
		Head=req[index];
	}
	seq[n]=Head;
	cout<<"The Total Operations are : "<<Seek<<endl;
	cout<<"The Sequence :"<<endl;
	for(int i=0;i<=n;i++){
		cout<<seq[i]<<" ";
	}
	cout<<""<<endl;
}
int main(){
	int n;
	cout<<"Enter no of Sequence :";
	cin>>n;
	cout<<"Enter Sequence :";
	int req[n];
	for(int i=0;i<n;i++){
		cin>>req[i];
	}
	cout<<"Enter Head:";
	int Head;
	cin>>Head;
	DiskSstf(n,req,Head);
	return 0;
}

Enter no of Sequence :8
Enter Sequence :176 79 34 60 92 11 41 114
Enter Head:50
The Total Operations are : 204
The Sequence :
50 41 34 11 60 79 92 114 176 



//7.Disk Scan Algorithm

#include<bits/stdc++.h>
using namespace std;

void DiskScan(int n,int req[],int Head,string Direction,int DiskSize){
	vector<int>left,right;
	vector<int>seq;
	if(Direction=="Left"){
		left.push_back(0);
	}
	else if(Direction=="Right"){
		right.push_back(DiskSize-1);
	}
	for(int i=0;i<n;i++){//imp
		if(req[i]<Head){
			left.push_back(req[i]);//imp
		}
		if(req[i]>Head){
			right.push_back(req[i]);
		}
	}
	std::sort(left.begin(),left.end());
	std::sort(right.begin(),right.end());
	int run=2;
	int Seek=0;
	int Current;
	int Distance;
	while(run--){	
		if(Direction=="Right"){
			for(int i=0;i<right.size();i++){
				Current=right[i];
				seq.push_back(right[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Direction="Left";
		}
		else if(Direction=="Left"){
			for(int i=left.size()-1;i!=-1;i--){
				Current=left[i];
				seq.push_back(left[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Direction="Right";
		}
	}
	cout<<"Total Seq Operations :"<<Seek<<endl;
	cout<<"Sequence :"<<endl;
	for(int i=0;i<seq.size();i++){
		cout<<seq[i]<<" "; 
	}
}

int main(){
	int n;
	cout<<"Enter no of Sequence :";
	cin>>n;
	cout<<"Enter Sequence :";
	int req[n];
	for(int i=0;i<n;i++){
		cin>>req[i];
	}
	cout<<"Enter Head:";
	int Head;
	cin>>Head;
	cout<<"Enter Direction:";
	string Direction;
	cin>>Direction;
	cout<<"Enter DiskSize:";
	int DiskSize;
	cin>>DiskSize;
	DiskScan(n,req,Head,Direction,DiskSize);
	return 0;
}


Enter no of Sequence :8
Enter Sequence :176 79 34 60 92 11 41 114
Enter Head:50
Enter Direction:Left
Enter DiskSize:200
Total Seq Operations :226
Sequence :
41 34 11 0 60 79 92 114 176



//8.Disk Look Algorithm

#include<bits/stdc++.h>
using namespace std;

void DiskLook(int n,int req[],int Head,string Direction,int DiskSize){
	vector<int>left,right;
	vector<int>seq;
	for(int i=0;i<n;i++){//imp
		if(req[i]<Head){
			left.push_back(req[i]);//imp
		}
		if(req[i]>Head){
			right.push_back(req[i]);
		}
	}
	std::sort(left.begin(),left.end());
	std::sort(right.begin(),right.end());
	int run=2;
	int Seek=0;
	int Current;
	int Distance;
	while(run--){	
		if(Direction=="Right"){
			for(int i=0;i<right.size();i++){
				Current=right[i];
				seq.push_back(right[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Direction="Left";
		}
		else if(Direction=="Left"){
			for(int i=left.size()-1;i!=-1;i--){
				Current=left[i];
				seq.push_back(left[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Direction="Right";
		}
	}
	cout<<"Total Seq Operations :"<<Seek<<endl;
	cout<<"Sequence :"<<endl;
	for(int i=0;i<seq.size();i++){
		cout<<seq[i]<<" "; 
	}
}

int main(){
	int n;
	cout<<"Enter no of Sequence :";
	cin>>n;
	cout<<"Enter Sequence :";
	int req[n];
	for(int i=0;i<n;i++){
		cin>>req[i];
	}
	cout<<"Enter Head:";
	int Head;
	cin>>Head;
	cout<<"Enter Direction:";
	string Direction;
	cin>>Direction;
	cout<<"Enter DiskSize:";
	int DiskSize;
	cin>>DiskSize;
	DiskLook(n,req,Head,Direction,DiskSize);
	return 0;
}

Enter no of Sequence :8
Enter Sequence :176 79 34 60 92 11 41 114
Enter Head:50
Enter Direction:Right
Enter DiskSize:200
Total Seq Operations :291
Sequence :
60 79 92 114 176 41 34 11




//9. Disk Circular Scan Algorithm

#include<bits/stdc++.h>
using namespace std;

void DiskScan(int n,int req[],int Head,string Direction,int DiskSize){
	vector<int>left,right;
	vector<int>seq;
	
	left.push_back(0);
	right.push_back(DiskSize-1);
	
	for(int i=0;i<n;i++){//imp
		if(req[i]<Head){
			left.push_back(req[i]);//imp
		}
		if(req[i]>Head){
			right.push_back(req[i]);
		}
	}
	std::sort(left.begin(),left.end());
	std::sort(right.begin(),right.end());
	
	int Seek=0;
	int Current;
	int Distance;
	
		if(Direction=="Left"){
			for(int i=left.size()-1;i!=-1;i--){//imp
				Current=left[i];
				seq.push_back(left[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Seek=Seek+DiskSize-1;
			Head=DiskSize-1;
				
			for(int i=right.size()-1;i!=-1;i--){//imp
				Current=right[i];
				seq.push_back(right[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
		}
		else if(Direction=="Right"){
			for(int i=0;i<right.size();i++){
				Current=right[i];
				seq.push_back(Current);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Seek=Seek+DiskSize-1;
			Head=0;
			for(int i=0;i<left.size();i++){
				Current=left[i];
				seq.push_back(Current);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
		}
	
	cout<<"Total Seq Operations :"<<Seek<<endl;
	cout<<"Sequence :"<<endl;
	for(int i=0;i<seq.size();i++){
		cout<<seq[i]<<" "; 
	}
}

int main(){
	int n;
	cout<<"Enter no of Sequence :";
	cin>>n;
	cout<<"Enter Sequence :";
	int req[n];
	for(int i=0;i<n;i++){
		cin>>req[i];
	}
	cout<<"Enter Head:";
	int Head;
	cin>>Head;
	cout<<"Enter Direction:";
	string Direction;
	cin>>Direction;
	cout<<"Enter DiskSize:";
	int DiskSize;
	cin>>DiskSize;
	DiskScan(n,req,Head,Direction,DiskSize);
	return 0;
}

Enter no of Sequence :8
Enter Sequence :176 79 34 60 92 11 41 114
Enter Head:50
Enter Direction:Right
Enter DiskSize:200
Total Seq Operations :389
Sequence :
60 79 92 114 176 199 0 11 34 41



//10. Disk Circular Look Algorithm

#include<bits/stdc++.h>
using namespace std;

void DiskCLook(int n,int req[],int Head,string Direction,int DiskSize){
	vector<int>left,right;
	vector<int>seq;
	
	
	for(int i=0;i<n;i++){//imp
		if(req[i]<Head){
			left.push_back(req[i]);//imp
		}
		if(req[i]>Head){
			right.push_back(req[i]);
		}
	}
	std::sort(left.begin(),left.end());
	std::sort(right.begin(),right.end());
	
	int Seek=0;
	int Current;
	int Distance;
	
		if(Direction=="Left"){
			for(int i=left.size()-1;i!=-1;i--){//imp
				Current=left[i];
				seq.push_back(left[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Seek=Seek+abs(Head-right[right.size()-1]);
			Head=right[right.size()-1];
				
			for(int i=right.size()-1;i!=-1;i--){//imp
				Current=right[i];
				seq.push_back(right[i]);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
		}
		else if(Direction=="Right"){
			for(int i=0;i<right.size();i++){
				Current=right[i];
				seq.push_back(Current);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
			Seek=Seek+abs(Head-left[0]);
			Head=left[0];
			for(int i=0;i<left.size();i++){
				Current=left[i];
				seq.push_back(Current);
				Distance=abs(Current-Head);
				Seek=Seek+Distance;
				Head=Current;
			}
		}
	
	cout<<"Total Seq Operations :"<<Seek<<endl;
	cout<<"Sequence :"<<endl;
	for(int i=0;i<seq.size();i++){
		cout<<seq[i]<<" "; 
	}
}

int main(){
	int n;
	cout<<"Enter no of Sequence :";
	cin>>n;
	cout<<"Enter Sequence :";
	int req[n];
	for(int i=0;i<n;i++){
		cin>>req[i];
	}
	cout<<"Enter Head:";
	int Head;
	cin>>Head;
	cout<<"Enter Direction:";
	string Direction;
	cin>>Direction;
	cout<<"Enter DiskSize:";
	int DiskSize;
	cin>>DiskSize;
	DiskCLook(n,req,Head,Direction,DiskSize);
	return 0;
}

Enter no of Sequence :8
Enter Sequence :176 79 34 60 92 11 41 114
Enter Head:50
Enter Direction:Left
Enter DiskSize:200
Total Seq Operations :320
Sequence :
41 34 11 176 114 92 79 60

//11.Page Replacement FIFO

#include<bits/stdc++.h>
using namespace std;

void PgFifo(int p,int pg[],int f){
	unordered_set<int>s;
	queue<int>q;
	int PageHits=0;
	int PageFaults=0;
	for(int i=0;i<p;i++){
		if(s.size()<f){
				if(s.find(pg[i])==s.end()){
					s.insert(pg[i]);
					q.push(pg[i]);
					PageFaults++;
				}
			}
			else{
				if(s.find(pg[i])==s.end()){
					int val=q.front();
					q.pop();
					s.erase(val);
					s.insert(pg[i]);
					q.push(pg[i]);
					PageFaults++;
				}
				else{
					PageHits++;
				}
			}
		}
		float HitRatio=float(PageHits)/p;
		cout<<"No of PageHits : "<<PageHits<<endl;
		cout<<"No of PageFaults : "<<PageFaults<<endl;
		cout<<"HitRatio : "<<fixed<<setprecision(2)<<HitRatio<<endl;
	}


int main(){
	int p;
	cout<<"Enter no of Pages :";
	cin>>p;
	int pg[p];
	cout<<"Enter Pages : ";
	for(int i=0;i<p;i++){
		cin>>pg[i];
	}
	cout<<"Enter no of Frames : ";
	int f;
	cin>>f;
	PgFifo(p,pg,f);
	return 0;
}

Enter no of Pages :13
Enter Pages : 7 0 1 2 0 3 0 4 2 3 0 3 2
Enter no of Frames : 4
No of PageHits : 6
No of PageFaults : 7
HitRatio : 0.46



//12.Page Replacement Least Recent

#include<bits/stdc++.h>
using namespace std;

void PgLru(int p,int pg[],int f){
	unordered_set<int>s;
	unordered_map<int,int>m;
	int PageHits=0;
	int PageFaults=0;
	for(int i=0;i<p;i++){
		if(s.size()<f){
			if(s.find(pg[i])==s.end()){
				s.insert(pg[i]);
				PageFaults++;
			}
			m[pg[i]]=i;
		}
		else{
			if(s.find(pg[i])==s.end()){
				int lru=INT_MAX;int val;
				for(auto it=s.begin();it!=s.end();it++){//imp
					if(m[*it] < lru){
						val=*it;
						lru=m[*it];
					}
				}//do after for loop
					s.erase(val);
					s.insert(pg[i]);
					PageFaults++;
			}
			else{
				PageHits++;
			}
			m[pg[i]]=i;
		}
		
	}
	
	float HitRatio=float(PageHits)/p;
		cout<<"No of PageHits : "<<PageHits<<endl;
		cout<<"No of PageFaults : "<<PageFaults<<endl;
		cout<<"HitRatio : "<<fixed<<setprecision(2)<<HitRatio<<endl; 
}

int main(){
	int p;
	cout<<"Enter no of Pages :";
	cin>>p;
	int pg[p];
	cout<<"Enter Pages : ";
	for(int i=0;i<p;i++){
		cin>>pg[i];
	}
	cout<<"Enter no of Frames : ";
	int f;
	cin>>f;
	PgLru(p,pg,f);
	return 0;
}

Enter no of Pages :14
Enter Pages : 7 0 1 2 0 3 0 4 2 3 0 3 2 3     
Enter no of Frames : 4
No of PageHits : 8
No of PageFaults : 6
HitRatio : 0.57



//13. Page Replacement Optimal

#include<bits/stdc++.h>
using namespace std;

void PgOptimal(int p,int pg[],int f){
	int PageHits=0;
	int fn[f];
	for(int i=0;i<f;i++){
		fn[i]=-1;
	}
	for(int i=0;i<p;i++){//rem entire loop
		bool found=false;
		for(int j=0;j<f;j++){
			if(fn[j]==pg[i]){//i with j
				PageHits++;
				found=true;
				break;
			}
		}
	
	if(found){
			continue;
		}
	bool emptyspaces=false;
	for(int j=0;j<f;j++){
		if(fn[j]==-1){
			fn[j]=pg[i];
			emptyspaces=true;
			break;
		}
	}
	if(emptyspaces){
		continue;
	}
	int far=-1;
	int replace=-1;
	for(int j=0;j<f;j++){
		int k;//imp
		for(k=i+1;k<p;k++){//remk=i+1
			if(fn[j]==pg[k]){
				if(k>far){
					far=k;
					replace=j;
				}
				break;
			}
			}//imp
			if(k==p){//imp
			replace=j;
			break;
		}
		
	}
		fn[replace]=pg[i];//remeber
	}
	int PageFaults=p-PageHits;
		float HitRatio=float(PageHits)/p;
		cout<<"No of PageHits : "<<PageHits<<endl;
		cout<<"No of PageFaults : "<<PageFaults<<endl;
		cout<<"HitRatio : "<<fixed<<setprecision(2)<<HitRatio<<endl; 
}

int main(){
	int p;
	cout<<"Enter no of Pages :";
	cin>>p;
	int pg[p];
	cout<<"Enter Pages : ";
	for(int i=0;i<p;i++){
		cin>>pg[i];
	}
	cout<<"Enter no of Frames : ";
	int f;
	cin>>f;
	PgOptimal(p,pg,f);
	return 0;
}

Enter no of Pages :13
Enter Pages :  7 0 1 2 0 3 0 4 2 3 0 3 2 
Enter no of Frames : 4
No of PageHits : 7
No of PageFaults : 6
HitRatio : 0.54



//14.Scheduling Algorithm FCFS

#include<bits/stdc++.h>
using namespace std;

struct job{
    int pt;
    int at;
    int bt;
    int ct;
    int rt;
    int wt;
    int tat;
};

void sort(struct job a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i].at > a[j].at) {
                int temp = a[i].at;
                a[i].at = a[j].at;
                a[j].at = temp;
                temp = a[i].bt;
                a[i].bt = a[j].bt;
                a[j].bt = temp;
                temp = a[i].pt;
                a[i].pt = a[j].pt;
                a[j].pt = temp;
            }
        }
    }
}

void complete(struct job a[], int n, vector<pair<int, int>>& ganttChart) {
    int sum = 0;
    sum = sum + a[0].at;
    for (int i = 0; i < n; i++) {
        sum = sum + a[i].bt;
        a[i].ct = sum;
        a[i].tat = a[i].ct - a[i].at;
        a[i].wt = a[i].tat - a[i].bt;
        a[i].rt = a[i].wt;
        if (sum < a[i + 1].at) {
            sum = a[i + 1].at;
        }
        ganttChart.push_back({sum - a[i].bt, a[i].pt});
    }
}

void print(struct job a[], int n) {
    cout << "P.T\t A.T\t B.T\t C.T\t T.A.T\t W.T\t R.T \n";
    for (int i = 0; i < n; i++) {
        cout << a[i].pt << " \t " << a[i].at << " \t " << a[i].bt << " \t " << a[i].ct << " \t " << a[i].tat << " \t " << a[i].wt << " \t " << a[i].rt << "\n";
    }
}

void avg(struct job a[], int n) {
    int wtSum = 0;
    int tatSum = 0;
    for (int i = 0; i < n; i++) {
        wtSum = wtSum + a[i].wt;
        tatSum = tatSum + a[i].tat;
    }
    float wtAvg = (float)wtSum / n;
    float tatAvg = (float)tatSum / n;
    cout << "Average Waiting Time : " << wtAvg << "\n";
    cout << "Average TurnAround Time : " << tatAvg << "\n";
}

void printGanttChart(const vector<pair<int, int>>& ganttChart) {
    cout << "\nGantt Chart:\n";
    for (const auto& entry : ganttChart) {
        cout << "P" << entry.second << " | ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter n : ";
    cin >> n;
    job a[n];
    vector<pair<int, int>> ganttChart;

    cout << "Enter Arrival Time : \n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].at;
        a[i].pt = i + 1;
    }

    cout << "Enter Burst Time : \n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].bt;
    }

    sort(a, n);
    complete(a, n, ganttChart);
    print(a, n);
    avg(a, n);
    printGanttChart(ganttChart);

    return 0;
}



Enter n : 5
Enter Arrival Time : 
2 0 2 3 4
Enter Burst Time : 
2 1 3 5 4
P.T	 A.T	 B.T	 C.T	 T.A.T	 W.T	 R.T 
2 	 0 	 1 	 1 	 1 	 0 	 0
1 	 2 	 2 	 4 	 2 	 0 	 0
3 	 2 	 3 	 7 	 5 	 2 	 2
4 	 3 	 5 	 12 	 9 	 4 	 4
5 	 4 	 4 	 16 	 12 	 8 	 8
Average Waiting Time : 2.8
Average TurnAround Time : 5.8

Gantt Chart:
P2 | P1 | P3 | P4 | P5 | 


//15.Scheduling SJF

#include<iostream>
#include<algorithm>
using namespace std;

int min_at(int v[], int at[], int n) {
    int i, min = 999, min_i;
    for (i = 1; i <= n; i++) {
        if (v[i] != 1 && min > at[i]) {
            min = at[i];
            min_i = i;
        }
    }
    return min_i;
}

void sort1(int p[], int at[], int bt[], int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (bt[i] > bt[j]) {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int min_bt(int bt[], int at[], int t, int n, int v[]) {
    int i;
    for (i = 1; i <= n; i++) {
        if (v[i] != 1 && at[i] <= t) {
            return i;
        }
    }
    return 0;
}

void chart(int p[], int at[], int bt[], int n) {
    int k = 0, t = 0, x, c = 0, v[20], i;
    int ct[20], tat[20], wt[20], rt[20];
    for (i = 1; i <= n; i++) {
        v[i] = 0;
    }
    x = min_at(v, at, n);
    if (at[x] != 0) {
        cout << "| idle";
        t = at[x];
    }
    else {
        cout << "| p" << p[x];
        t = at[x] + bt[x];
        v[x] = 1;
        c++;
        ct[x] = t;
        tat[x] = ct[x] - at[x];
        wt[x] = tat[x] - bt[x];
        rt[x] = wt[x]; // Response time is the same as waiting time
    }
    while (c < n) {
        x = min_bt(bt, at, t, n, v);
        if (x == 0) {
            x = min_at(v, at, n);
            cout << "| idle";
            t = at[x];
        }
        else {
            cout << "| p" << p[x];
            t = t + bt[x];
            v[x] = 1;
            c++;
            ct[x] = t;
            tat[x] = ct[x] - at[x];
            wt[x] = tat[x] - bt[x];
            rt[x] = wt[x]; // Response time is the same as waiting time
        }
    }
    cout << endl;
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    cout << "-----------------------------------------------\n";
    for (i = 1; i <= n; i++) {
        cout << p[i] << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\t" << rt[i] << "\n";
    }
    float sum = 0, sum1 = 0;
    for (i = 1; i <= n; i++) {
        sum = sum + tat[i];
        sum1 = sum1 + wt[i];
    }
    cout << "\n";
    cout << "Avg TAT:" << sum / n << "\n";
    cout << "Avg WT:" << sum1 / n << "\n";
}

int main() {
    int p[20], at[20], bt[20], n, i;
    cout << "enter no. of processes\n";
    cin >> n;
    cout << "enter arrival times and burst times\n";
    for (i = 1; i <= n; i++) {
        p[i] = i;
        cin >> at[i] >> bt[i];
    }
    sort1(p, at, bt, n);
    chart(p, at, bt, n);
    return 0;
}


enter no. of processes
5
enter arrival times and burst times
2 1
1 5
4 1
0 6
2 3
| p4| p1| p3| p5| p2

P	AT	BT	CT	TAT	WT	RT
-----------------------------------------------
1	2	1	7	5	4	4
3	4	1	8	4	3	3
5	2	3	11	9	6	6
2	1	5	16	15	10	10
4	0	6	6	6	0	0

Avg TAT:7.8
Avg WT:4.6


//16.Scheduling Shortesr Remaining Time First

#include<bits/stdc++.h>
using namespace std;

struct job {
    int pt;
    int at;
    int bt;
    int dbt;
    int ct;
    int rt;
    int wt;
    int tat;
    int ft;
};

void complete(struct job a[], int n, vector<pair<int, int>>& ganttChart) {
    int currentTime = 0;
    int process = 0;
    int shortestBurstIndex = 0;
    int shortestBurst = INT_MAX;
    int finishTime;
    bool check = false;

    while (process != n) {

        for (int i = 0; i < n; i++) {
            if (a[i].dbt > 0 && a[i].dbt < shortestBurst && a[i].at <= currentTime) {
                shortestBurstIndex = i;
                shortestBurst = a[i].dbt;
                check = true;
            }
        }
        if (check == false) {
            currentTime++;
            continue;
        }
        else {
            if (a[shortestBurstIndex].ft == -1) {
                a[shortestBurstIndex].ft = currentTime;
            }
        }
        a[shortestBurstIndex].dbt--;

        ganttChart.push_back({currentTime, a[shortestBurstIndex].pt});

        shortestBurst = a[shortestBurstIndex].dbt;
        if (shortestBurst == 0) {
            shortestBurst = INT_MAX;
        }
        if (a[shortestBurstIndex].dbt == 0) {
            process++;
            check = false;
            finishTime = currentTime + 1;

            a[shortestBurstIndex].ct = finishTime;
            a[shortestBurstIndex].tat = a[shortestBurstIndex].ct - a[shortestBurstIndex].at;
            a[shortestBurstIndex].wt = a[shortestBurstIndex].tat - a[shortestBurstIndex].bt;
            a[shortestBurstIndex].rt = a[shortestBurstIndex].ft - a[shortestBurstIndex].at;
        }
        currentTime++;
    }
}

void print(struct job a[], int n) {
    cout << "P.T\t A.T\t B.T\t C.T\t T.A.T\t W.T\t R.T \n";
    for (int i = 0; i < n; i++) {
        cout << a[i].pt << " \t " << a[i].at << " \t " << a[i].bt << " \t " << a[i].ct << " \t " << a[i].tat << " \t " << a[i].wt << " \t " << a[i].rt << "\n";
    }
}

void avg(struct job a[], int n) {
    int wtSum = 0;
    int tatSum = 0;
    for (int i = 0; i < n; i++) {
        wtSum = wtSum + a[i].wt;
        tatSum = tatSum + a[i].tat;
    }
    float wtAvg = (float)wtSum / n;
    float tatAvg = (float)tatSum / n;
    cout << "Average Waiting Time : " << wtAvg << "\n";
    cout << "Average TurnAround Time : " << tatAvg << "\n";
}

void printGanttChart(const vector<pair<int, int>>& ganttChart) {
    cout << "\nGantt Chart:\n";
    for (const auto& entry : ganttChart) {
        cout << " P" << entry.second << " | ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter n : ";
    cin >> n;
    job a[n];
    vector<pair<int, int>> ganttChart;

    cout << "Enter Arrival Time : \n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].at;
        a[i].pt = i + 1;
        a[i].ft = -1;
    }

    cout << "Enter Burst Time : \n";
    for (int j = 0; j < n; j++) {
        cin >> a[j].bt;
        a[j].dbt = a[j].bt;
    }

    complete(a, n, ganttChart);
    print(a, n);
    avg(a, n);
    printGanttChart(ganttChart);

    return 0;
}


Enter n : 5
Enter Arrival Time : 
2 1 4 0 2
Enter Burst Time : 
1 5 1 6 3
P.T	 A.T	 B.T	 C.T	 T.A.T	 W.T	 R.T 
1 	 2 	 1 	 3 	 1 	 0 	 0
2 	 1 	 5 	 16 	 15 	 10 	 10
3 	 4 	 1 	 5 	 1 	 0 	 0
4 	 0 	 6 	 11 	 11 	 5 	 0
5 	 2 	 3 	 7 	 5 	 2 	 1
Average Waiting Time : 3.4
Average TurnAround Time : 6.6

Gantt Chart:
 P4 |  P4 |  P1 |  P5 |  P3 |  P5 |  P5 |  P4 |  P4 |  P4 |  P4 |  P2 |  P2 |  P2 |  P2 |  P2 |


//17.Rounds Robin

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int burstTimeRemaining;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    bool isComplete;
    bool inQueue;
};

void checkForNewArrivals(Process processes[], const int n, const int currentTime, queue<int> &readyQueue)
{
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrivalTime <= currentTime && !processes[i].inQueue && !processes[i].isComplete)
        {
            processes[i].inQueue = true;
            readyQueue.push(i);
        }
    }
}

void updateQueue(Process processes[], const int n, const int quantum, queue<int> &readyQueue, int &currentTime, int &programsExecuted, vector<pair<int, int>> &ganttChart)
{
    int i = readyQueue.front();
    readyQueue.pop();

    if (processes[i].burstTimeRemaining <= quantum)
    {
        processes[i].isComplete = true;
        currentTime += processes[i].burstTimeRemaining;
        processes[i].completionTime = currentTime;
        processes[i].waitingTime = max(0, processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime);
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

        processes[i].burstTimeRemaining = 0;
        ganttChart.push_back({currentTime - processes[i].burstTimeRemaining, processes[i].pid});
        
        if (programsExecuted != n)
        {
            checkForNewArrivals(processes, n, currentTime, readyQueue);
        }
    }
    else
    {
        processes[i].burstTimeRemaining -= quantum;
        currentTime += quantum;

        ganttChart.push_back({currentTime - quantum, processes[i].pid});

        if (programsExecuted != n)
        {
            checkForNewArrivals(processes, n, currentTime, readyQueue);
        }
        readyQueue.push(i);
    }
}

void printTitle(const string &title)
{
    cout << title << endl;
}

void outputTableHeader()
{
    cout << "Pid\tAT\tBT\tCT\tTAT\tWT" << endl;
}

void outputProcess(const Process &p)
{
    cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
         << p.completionTime << "\t" << p.turnaroundTime << "\t" << p.waitingTime << endl;
}

void printAverages(const double avgWaitingTime, const double avgTurnaroundTime)
{
    cout << "Average Waiting time=" << avgWaitingTime << endl;
    cout << "Average Turn Around Time=" << avgTurnaroundTime << endl;
}

void printGanttChart(const vector<pair<int, int>> &ganttChart)
{
    cout << "Gantt Chart: ";
    for (const auto &entry : ganttChart)
    {
        cout << "P" << entry.second << " ";
    }
    cout << endl;
}

void roundRobin(Process processes[], int n, int quantum)
{
    queue<int> readyQueue;
    readyQueue.push(0);
    processes[0].inQueue = true;

    int currentTime = 0;
    int programsExecuted = 0;
    vector<pair<int, int>> ganttChart;

    while (!readyQueue.empty())
    {
        updateQueue(processes, n, quantum, readyQueue, currentTime, programsExecuted, ganttChart);
    }

    printGanttChart(ganttChart);
}

int main()
{
    int n, quantum;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;

    Process processes[n + 1];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and burst time for P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].burstTimeRemaining = processes[i].burstTime;
        processes[i].pid = i + 1;
    }

    sort(processes, processes + n, [](const Process &p1, const Process &p2)
         { return p1.arrivalTime < p2.arrivalTime; });

    roundRobin(processes, n, quantum);

    printTitle("Process Execution Order");
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].pid << " ";
    }
    cout << endl;

    outputTableHeader();
    for (int i = 0; i < n; i++)
    {
        outputProcess(processes[i]);
    }

    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;

    for (int i = 0; i < n; i++)
    {
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }

    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    printAverages(avgWaitingTime, avgTurnaroundTime);

    return 0;
}

//18.Premitive Priority

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct job {
    int pt;
    int at;
    int bt;
    int dbt;
    int ct;
    int rt;
    int wt;
    int tat;
    int ft;
    int priority;
};

void complete(struct job a[], int n, vector<pair<int, int>>& ganttChart) {
    int currentTime = 0;
    int process = 0;
    int shortestPriorityIndex = 0;
    int shortestPriority = INT_MAX;
    int finishTime;
    bool check = false;

    while (process != n) {
        shortestPriority = INT_MAX; // Reset the shortestPriority for each iteration

        for (int i = 0; i < n; i++) {
            if (a[i].dbt > 0 && a[i].priority < shortestPriority && a[i].at <= currentTime) {
                shortestPriorityIndex = i;
                shortestPriority = a[i].priority;
                check = true;
            }
        }

        if (check == false) {
            currentTime++;
            continue;
        } else {
            if (a[shortestPriorityIndex].ft == -1) {
                a[shortestPriorityIndex].ft = currentTime;
            }
        }

        ganttChart.push_back({a[shortestPriorityIndex].pt, currentTime});

        a[shortestPriorityIndex].dbt--;

        if (a[shortestPriorityIndex].dbt == 0) {
            process++;
            check = false;
            finishTime = currentTime + 1;

            a[shortestPriorityIndex].ct = finishTime;
            a[shortestPriorityIndex].wt = finishTime - a[shortestPriorityIndex].bt - a[shortestPriorityIndex].at;
            a[shortestPriorityIndex].tat = a[shortestPriorityIndex].bt + a[shortestPriorityIndex].wt;
            a[shortestPriorityIndex].rt = a[shortestPriorityIndex].ft - a[shortestPriorityIndex].at;
            if (a[shortestPriorityIndex].wt < 0) {
                a[shortestPriorityIndex].wt = 0;
            }
        }
        currentTime++;
    }
}

void print(struct job a[], int n) {
    cout << "P.T\t PR.T\t A.T\t B.T\t C.T\t T.A.T\t W.T\t R.T \n";
    for (int i = 0; i < n; i++) {
        cout << a[i].pt << " \t " << a[i].priority << "\t" << a[i].at << " \t " << a[i].bt << " \t " << a[i].ct << " \t "
             << a[i].tat << " \t " << a[i].wt << " \t " << a[i].rt << "\n";
    }
}

void avg(struct job a[], int n) {
    int wtSum = 0;
    int tatSum = 0;
    for (int i = 0; i < n; i++) {
        wtSum += a[i].wt;
        tatSum += a[i].tat;
    }
    float wtAvg = (float)wtSum / n;
    float tatAvg = (float)tatSum / n;
    cout << "Average Waiting Time : " << wtAvg << "\n";
    cout << "Average TurnAround Time : " << tatAvg << "\n";
}

void printGanttChart(const vector<pair<int, int>>& ganttChart) {
    cout << "\nGantt Chart:\n";
    for (const auto& entry : ganttChart) {
        cout << "| P" << entry.first << " ";
    }
    cout << "|\n";
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    job a[n];
    cout << "Enter Arrival Time:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].at;
        a[i].pt = i + 1;
        a[i].ft = -1;
    }
    cout << "Enter Burst Time:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].bt;
        a[i].dbt = a[i].bt;
    }
    cout << "Enter Priority:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].priority;
    }

    vector<pair<int, int>> ganttChart;
    complete(a, n, ganttChart);
    print(a, n);
    avg(a, n);
    printGanttChart(ganttChart);

    return 0;
}




Enter n: 7
Enter Arrival Time:
0 1 3 4 5 6 10
Enter Burst Time:
8 2 4 1 6 5 1
Enter Priority:
3 4 4 5 2 6 1
P.T	 PR.T	 A.T	 B.T	 C.T	 T.A.T	 W.T	 R.T 
1 	 3	0 	 8 	 15 	 15 	 7 	 0
2 	 4	1 	 2 	 17 	 16 	 14 	 14
3 	 4	3 	 4 	 21 	 18 	 14 	 14
4 	 5	4 	 1 	 22 	 18 	 17 	 17
5 	 2	5 	 6 	 12 	 7 	 1 	 0
6 	 6	6 	 5 	 27 	 21 	 16 	 16
7 	 1	10 	 1 	 11 	 1 	 0 	 0
Average Waiting Time : 9.85714
Average TurnAround Time : 13.7143

Gantt Chart:
| P1 | P1 | P1 | P1 | P1 | P5 | P5 | P5 | P5 | P5 | P7 | P5 | P1 | P1 | P1 | P2 | P2 | P3 | P3 | P3 | P3 | P4 | P6 | P6 | P6 | P6 | P6 |


//19.Non Preemitive Priority

#include <bits/stdc++.h>
using namespace std;

struct job {
    int pt;
    int at;
    int bt;
    int ct;
    int rt;
    int wt;
    int tat;
    int cmp;
    int priority;
};

int checkZero(struct job a[], int n, int currentTime) {
    int shortestPriority = INT_MAX;
    int shortestPriorityIndex = -1;
    int arrivalCheck = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!a[i].cmp && a[i].priority <= shortestPriority && a[i].at <= currentTime) {
            if (a[i].priority == shortestPriority) {
                if (arrivalCheck > a[i].at) {
                    arrivalCheck = a[i].at;
                    shortestPriority = a[i].priority;
                    shortestPriorityIndex = i;
                } else {
                    continue;
                }
            } else {
                arrivalCheck = a[i].at;
                shortestPriority = a[i].priority;
                shortestPriorityIndex = i;
            }
        }
    }
    return shortestPriorityIndex;
}

int check(struct job a[], int n) {
    int shortestPriority = INT_MAX;
    int shortestPriorityIndex = -1;
    int arrivalCheck = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!a[i].cmp && a[i].priority <= shortestPriority) {
            if (a[i].priority == shortestPriority) {
                if (arrivalCheck > a[i].at) {
                    arrivalCheck = a[i].at;
                    shortestPriority = a[i].priority;
                    shortestPriorityIndex = i;
                } else {
                    continue;
                }
            } else {
                arrivalCheck = a[i].at;
                shortestPriority = a[i].priority;
                shortestPriorityIndex = i;
            }
        }
    }
    return shortestPriorityIndex;
}

void complete(struct job a[], int n, vector<pair<int, int>>& ganttChart) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        int shortestPriorityIndex = checkZero(a, n, currentTime);
        if (shortestPriorityIndex == -1) {
            shortestPriorityIndex = check(a, n);
            if (currentTime <= a[shortestPriorityIndex].at) {
                currentTime = a[shortestPriorityIndex].at;
            }
        }

        ganttChart.push_back({a[shortestPriorityIndex].pt, currentTime});

        a[shortestPriorityIndex].ct = currentTime + a[shortestPriorityIndex].bt;
        a[shortestPriorityIndex].tat = a[shortestPriorityIndex].ct - a[shortestPriorityIndex].at;
        a[shortestPriorityIndex].wt = a[shortestPriorityIndex].tat - a[shortestPriorityIndex].bt;
        a[shortestPriorityIndex].rt = currentTime;
        a[shortestPriorityIndex].cmp = true;
        currentTime = a[shortestPriorityIndex].ct;
    }
}

void print(struct job a[], int n) {
    cout << "P.T\t PR.T\t A.T\t B.T\t C.T\t T.A.T\t W.T\t R.T \n";
    for (int i = 0; i < n; i++) {
        cout << a[i].pt << " \t " << a[i].priority << "\t" << a[i].at << " \t " << a[i].bt << " \t " << a[i].ct << " \t "
             << a[i].tat << " \t " << a[i].wt << " \t " << a[i].rt << "\n";
    }
}

void avg(struct job a[], int n) {
    int wtSum = 0;
    int tatSum = 0;
    for (int i = 0; i < n; i++) {
        wtSum += a[i].wt;
        tatSum += a[i].tat;
    }
    float wtAvg = (float)wtSum / n;
    float tatAvg = (float)tatSum / n;
    cout << "Average Waiting Time : " << wtAvg << "\n";
    cout << "Average TurnAround Time : " << tatAvg << "\n";
}

void printGanttChart(const vector<pair<int, int>>& ganttChart) {
    cout << "\nGantt Chart:\n";
    for (const auto& entry : ganttChart) {
        cout << "| P" << entry.first << " ";
    }
    cout << "|\n";
}

int main() {
    int n;
    cout << "Enter n : ";
    cin >> n;
    job a[n];
    cout << "Enter Arrival Time : \n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].at;
        a[i].pt = i + 1;
        a[i].cmp = false;
    }
    cout << "Enter Burst Time : \n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].bt;
    }
    cout << "Enter Priority : \n";
    for (int i = 0; i < n; i++) {
        cin >> a[i].priority;
    }

    vector<pair<int, int>> ganttChart;
    complete(a, n, ganttChart);
    print(a, n);
    avg(a, n);
    printGanttChart(ganttChart);
    return 0;
}



Enter n : 7
Enter Arrival Time : 
0 1 3 4 5 6 10
Enter Burst Time : 
8 2 4 1 6 5 1
Enter Priority : 
3 4 4 5 2 6 1
P.T	 PR.T	 A.T	 B.T	 C.T	 T.A.T	 W.T	 R.T 
1 	 3	0 	 8 	 8 	 8 	 0 	 0
2 	 4	1 	 2 	 17 	 16 	 14 	 15
3 	 4	3 	 4 	 21 	 18 	 14 	 17
4 	 5	4 	 1 	 22 	 18 	 17 	 21
5 	 2	5 	 6 	 14 	 9 	 3 	 8
6 	 6	6 	 5 	 27 	 21 	 16 	 22
7 	 1	10 	 1 	 15 	 5 	 4 	 14
Average Waiting Time : 9.71429
Average TurnAround Time : 13.5714

Gantt Chart:
| P1 | P5 | P7 | P2 | P3 | P4 | P6 |


