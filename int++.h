#ifndef INT++_H
#define INT++_H

#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
using namespace std;

class BigInt{
	private:
		vector<char> v;
		int size;
		
		void init(){
			v=vector<char>();
			size=1;
			v.push_back('0');
			v.push_back('0');
		}
		void init(string x){
			v=vector<char>();
			char st='0';
			int r=0;
			if(x[0]=='-'){
				if(x.size()<2){
					init(BigInt());
					return;
				}
				r=1;
				if(x[1]!='0'){
					st='1';
				}
			}
			v.push_back(st);
			int t=r;
			for(;t<x.size()-1;t++){
				if(x[t]!='0'){
					break;
				}
			}
			x=x.substr(t);
			size=x.size();
			for(int i=x.size()-1;i>=0;i--){
				if(x[i]<'0'||x[i]>'9'){
					init();
					return;
				}
				v.push_back(x[i]);
			}
		}
		void init(BigInt x){
			size=x.size;
			v=x.v;
		}
		
		bool isEqual(BigInt x){
			if(size!=x.size){
				return 0;
			}
			for(int i=0;i<=size;i++){
				if(v[i]!=x.v[i]){
					return 0;
				}
			}
			return 1;
		}
		bool isSmaller(BigInt x){
			if(v[0]=='1'&&x.v[0]=='0'){
				return 1;
			}
			if(v[0]=='0'&&x.v[0]=='1'){
				return 0;
			}
			for(int i=max(size,x.size);i>=1;i--){
				int a=0,b=0;
				if(i<=size){
					a=v[i]-'0';
				}
				if(i<=x.size){
					b=x.v[i]-'0';
				}
				if(a<b){
					return 1;
				}
				if(a>b){
					return 0;
				}
			}
			return 0;
		}
		bool isBigger(BigInt x){
			if(v[0]=='1'&&x.v[0]=='0'){
				return 0;
			}
			if(v[0]=='0'&&x.v[0]=='1'){
				return 1;
			}
			for(int i=max(size,x.size);i>=1;i--){
				int a=0,b=0;
				if(i<=size){
					a=v[i]-'0';
				}
				if(i<=x.size){
					b=x.v[i]-'0';
				}
				if(a<b){
					return 0;
				}
				if(a>b){
					return 1;
				}
			}
			return 0;
		}
			
		BigInt add(BigInt x){
			BigInt ret;
			int k=0;
			for(int i=1;i<=max(size,x.size);i++){
				int a=0,b=0;
				if(i<=size){
					a=v[i]-'0';
				}
				if(i<=x.size){
					b=x.v[i]-'0';
				}
				int t=a+b+k;
				k=t/10;
				t%=10;
				if(i>ret.size){
					ret.size++;
					ret.v.push_back('0');
				}
				ret.v[i]=t+'0';
			}
			while(k){
				ret.size++;
				ret.v.push_back(k%10+'0');
				k/=10;
			}
			return ret;
		}
		BigInt minus(BigInt x){
			BigInt ret;
			int k=0;
			for(int i=1;i<=size;i++){
				int a=0,b=0;
				if(i<=size){
					a=(v[i]-'0');
				}
				if(i<=x.size){
					b=(x.v[i]-'0');
				}
				int t=a-b-k;
				if(t<0){
					t+=10;
					k=1;
				}
				else{
					k=0;
				}
				if(i>ret.size){
					ret.size++;
					ret.v.push_back('0');
				}
				ret.v[i]=t+'0';
			}
			while(ret.v[ret.size]=='0'&&ret.size>1){
				ret.size--;
				ret.v.pop_back();
			}
			return ret;
		}
		BigInt negative(){
			BigInt ret=*this;
			if(ret.v[0]=='0'){
				ret.v[0]='1';
			}
			else{
				ret.v[0]='0';
			}
			return ret;
		}
		BigInt mul(BigInt x){
			BigInt ret;
			if(v[0]!=x.v[0]){
				ret.v[0]='1';
			}
			for(int i=1;i<=size;i++){
				int k=0;
				for(int j=1;j<=x.size;j++){
					int pos=i+j-1;
					if(pos>ret.size){
						ret.size++;
						ret.v.push_back('0');
					}
					int t=(ret.v[pos]-'0')+(v[i]-'0')*(x.v[j]-'0')+k;
					k=t/10;
					t%=10;
					ret.v[pos]=t+'0';
				}
				ret.size++;
				ret.v.push_back(k+'0');
			}
			while(ret.v[ret.size]=='0'&&ret.size>1){
				ret.size--;
				ret.v.pop_back();
			}
			return ret;
		}
		BigInt div(BigInt x){
			BigInt ret;
			if(v[0]!=x.v[0]){
				ret.v[0]='1';
			}
			if(absolute()<x.absolute()||*this==0){
				return BigInt();
			}
			x=x.absolute();
			for(int i=1;i<size;i++){
				ret.size++;
				ret.v.push_back('0');
			}
			BigInt t;
			for(int i=size;i>size-x.size+1;i--){
				t=t+(v[i]-'0');
				if(i>size-x.size+2){
					t*=10;
				}
			}
			for(int i=size-x.size+1;i>=1;i--){
				t=t*10+(v[i]-'0');
				int cnt=0;
				while(t>=x){
					t-=x;
					cnt++;
				}
				ret.v[i]=cnt+'0';
			}
			while(ret.v[ret.size]=='0'&&ret.size>1){
				ret.size--;
				ret.v.pop_back();
			}
			return ret;
		}
		BigInt absolute(){
			BigInt ret=*this;
			ret.v[0]='0';
			return ret;
		}
		
		void input(){
			string s;
			cin>>s;
			init(s);
		}
		void print(){
			if(v[0]=='1'){
				printf("-");
			}
			for(int i=size;i>=1;i--){
				printf("%c",v[i]);
			}
		}
		int get(int index){
			int pos;
			if(index==0||index>size){
				pos=0;
			}
			else if(index<0){
				pos=abs(index);
				if(pos>size){
					pos=0;
				}
			}
			else{
				pos=size-index+1;
			}
			return v[pos]-'0';
		}
	public:
		BigInt(){
			init();
		}
		BigInt(string x){
			init(x);
		}
		BigInt(long long x){
			init(to_string(x));
		}
		BigInt operator=(string x){
			init(x);
			return *this;
		}
		BigInt operator=(long long x){
			init(to_string(x));
			return *this;
		}
		
		int operator[](int index){
			return get(index);
		}
		bool operator==(BigInt x){
			return isEqual(x);
		}
		bool operator==(long long x){
			return *this==BigInt(x);
		}
		bool operator!=(BigInt x){
			return !(*this==x);
		}
		bool operator!=(long long x){
			return *this!=BigInt(x);
		}
		bool operator<(BigInt x){
			if(v[0]=='1'&&x.v[0]=='1'){
				return absolute()>x.absolute();
			}
			else{
				return isSmaller(x);
			}
		}
		bool operator<(long long x){
			return *this<BigInt(x);
		}
		bool operator>(BigInt x){
			if(v[0]=='1'&&x.v[0]=='1'){
				return absolute()<x.absolute();
			}
			else{
				return isBigger(x);
			}
		}
		bool operator>(long long x){
			return *this>BigInt(x);
		}
		bool operator<=(BigInt x){
			return *this<x||*this==x;
		}
		bool operator<=(long long x){
			return *this<=BigInt(x);
		}
		bool operator>=(BigInt x){
			return *this>x||*this==x;
		}
		bool operator>=(long long x){
			return *this>=BigInt(x);
		}
		BigInt operator+(BigInt x){
			if(x<0){
				return *this-x.absolute();
			}
			else if(*this<0){
				return x-absolute();
			}
			else{
				return add(x);
			}
		}
		BigInt operator+(long long x){
			return *this+BigInt(x);
		}
		BigInt operator+=(BigInt x){
			BigInt ret=*this+x;
			init(ret);
			return ret;
		}
		BigInt operator+=(long long x){
			return *this+=BigInt(x);
		}
		BigInt operator++(int x){
			return (*this+=1);
		}
		BigInt operator-(){
			return negative();
		}
		BigInt operator-(BigInt x){
			if(x<0){
				return *this+x.absolute();
			}
			else if(*this<0){
				return -(absolute()+x);
			}
			else if(x>*this){
				return -(x-*this);
			}
			else{
				return minus(x);
			}
		}
		BigInt operator-(long long x){
			return *this-BigInt(x);
		}
		BigInt operator-=(BigInt x){
			BigInt ret=*this-x;
			init(ret);
			return ret;
		}
		BigInt operator-=(long long x){
			return *this-=BigInt(x);
		}
		BigInt operator--(int x){
			return (*this-=1);
		}
		BigInt operator*(BigInt x){
			return mul(x);
		}
		BigInt operator*(long long x){
			return (*this)*BigInt(x);
		}
		BigInt operator*=(BigInt x){
			BigInt ret=(*this)*x;
			init(ret);
			return ret;
		}
		BigInt operator*=(long long x){
			return (*this)*=BigInt(x);
		}
		BigInt operator/(BigInt x){
			return div(x);
		}
		BigInt operator/(long long x){
			return (*this)/BigInt(x);
		}
		BigInt operator/=(BigInt x){
			BigInt ret=(*this)/x;
			init(ret);
			return ret;
		}
		BigInt operator/=(long long x){
			return (*this)/=BigInt(x);
		} 
		BigInt operator%(BigInt x){
			return *this-(*this)/x*x;
		}
		BigInt operator%(long long x){
			return (*this)%BigInt(x);
		}
		BigInt operator%=(BigInt x){
			BigInt ret=(*this)%x;
			init(ret);
			return ret;
		}
		BigInt operator%=(long long x){
			return (*this)%=BigInt(x);
		}
		
		friend ostream& operator<<(ostream& os,BigInt x);
		friend istream& operator>>(istream& os,BigInt& x);
		
		int length(){
			return size;
		}
		long long toInt(){
			long long ret=0;
			for(int i=size;i>=1;i--){
				ret=(ret+(v[i]-'0'))*10;
			}
			ret/=10;
			if(v[0]=='1'){
				ret=-ret;
			}
			return ret;
		}
		string toString(){
			string ret="";
			if(v[0]=='1'){
				ret+="-";
			}
			for(int i=size;i>=1;i--){
				ret+=v[i];
			}
			return ret;
		}
};

class BigFloat{
	private:
		BigInt intv;
		vector<char> floatv;
		int float_size;
		int output_count;
		int accuracy;
		bool r;
		bool neg;
		
		void init(){
			output_count=1;
			accuracy=6;
			r=0;
			neg=0;
			intv=BigInt();
			floatv=vector<char>();
			float_size=1;
			floatv.push_back('0');
			floatv.push_back('0');
		}
		void init(string x){
			accuracy=6;
			r=0;
			neg=0;
			intv=BigInt();
			floatv=vector<char>();
			floatv.push_back('0');
			int st=(x[0]=='-');
			bool f=0;
			for(int i=st;i<x.size();i++){
				if(x[i]=='.'){
					f=1;
					intv=BigInt(x.substr(st,i-st));
					float_size=x.size()-i-1;
					for(int j=i+1;j<x.size();j++){
						floatv.push_back(x[j]);
					}
					while(floatv[float_size]=='0'&&float_size>1){
						float_size--;
						floatv.pop_back();
					}
					break;
				}
				else if(x[i]<'0'||x[i]>'9'){
					init();
					return;
				}
			}
			if(!f){
				intv=BigInt(x.substr(st));
				float_size=1;
				floatv.push_back('0');
			}
			if(x[0]=='-'){
				if(!(intv==0&&floatv[1]=='0'&&float_size==1)){
					neg=1;
				}
			}
			output_count=float_size;
		}
		void init(BigFloat x){
			float_size=x.float_size;
			output_count=x.output_count;
			accuracy=x.accuracy;
			r=x.r;
			neg=x.neg;
			intv=x.intv;
			floatv=x.floatv;
		}
		
		bool isEqual(BigFloat x){
			if(float_size!=x.float_size||neg!=x.neg){
				return 0;
			}
			if(intv!=x.intv){
				return 0;
			}
			for(int i=1;i<=float_size;i++){
				if(floatv[i]!=x.floatv[i]){
					return 0;
				}
			}
			return 1;
		}
		bool isSmaller(BigFloat x){
			if(neg==0&&x.neg==1){
				return 0;
			}
			if(neg==1&&x.neg==0){
				return 1;
			}
			if(intv!=x.intv){
				return intv<x.intv;
			}
			for(int i=1;i<=max(float_size,x.float_size);i++){
				int a=0,b=0;
				if(i<=float_size){
					a=floatv[i]-'0';
				}
				if(i<=x.float_size){
					b=x.floatv[i]-'0';
				}
				if(a>b){
					return 0;
				}
				if(a<b){
					return 1;
				}
			}
			return 0;
		}
		bool isBigger(BigFloat x){
			if(neg==0&&x.neg==1){
				return 1;
			}
			if(neg==1&&x.neg==0){
				return 0;
			}
			if(intv!=x.intv){
				return intv>x.intv;
			}
			for(int i=1;i<=max(float_size,x.float_size);i++){
				int a=0,b=0;
				if(i<=float_size){
					a=floatv[i]-'0';
				}
				if(i<=x.float_size){
					b=x.floatv[i]-'0';
				}
				if(a>b){
					return 1;
				}
				if(a<b){
					return 0;
				}
			}
			return 0;
		}
		BigFloat add(BigFloat x){
			BigFloat ret;
			ret.float_size=max(float_size,x.float_size);
			for(int i=1;i<ret.float_size;i++){
				ret.floatv.push_back('0');
			}
			int k=0;
			for(int i=ret.float_size;i>=1;i--){
				int a=0,b=0;
				if(i<=float_size){
					a=floatv[i]-'0';
				}
				if(i<=x.float_size){
					b=x.floatv[i]-'0';
				}
				int t=a+b+k;
				k=t/10;
				t%=10;
				ret.floatv[i]=t+'0';
			}
			ret.intv=intv+x.intv+k;
			while(ret.floatv[ret.float_size]=='0'&&ret.float_size>1){
				ret.float_size--;
				ret.floatv.pop_back();
			}
			ret.round(output_count,r);
			return ret;
		}
		BigFloat minus(BigFloat x){
			BigFloat ret;
			ret.float_size=max(float_size,x.float_size);
			for(int i=1;i<ret.float_size;i++){
				ret.floatv.push_back('0');
			}
			int k=0;
			for(int i=ret.float_size;i>=1;i--){
				int a=0,b=0;
				if(i<=float_size){
					a=floatv[i]-'0';
				}
				if(i<=x.float_size){
					b=x.floatv[i]-'0';
				}
				int t=a-b-k;
				if(t<0){
					t+=10;
					k=1;
				}
				else{
					k=0;
				}
				ret.floatv[i]=t+'0';
			}
			ret.intv=intv-x.intv-k;
			while(ret.floatv[ret.float_size]=='0'&&ret.float_size>1){
				ret.float_size--;
				ret.floatv.pop_back();
			}
			ret.round(output_count,r);
			return ret;
		}
		BigFloat negative(){
			BigFloat ret=*this;
			ret.neg=!ret.neg;
			return ret;
		}
		BigFloat mul(BigFloat x){
			BigInt a(intToString()+floatToString());
			BigInt b(x.intToString()+x.floatToString());
			string t=(a*b).toString();
			BigFloat ret(t.substr(0,t.size()-(float_size+x.float_size))+'.'+t.substr(t.size()-(float_size+x.float_size)));
			while(ret.floatv[ret.float_size]=='0'&&ret.float_size>1){
				ret.float_size--;
				ret.floatv.pop_back();
			}
			ret.round(output_count,r);
			if(neg!=x.neg){
				ret.neg=1;
			}
			return ret;
		}
		BigFloat div(BigFloat x){
			string s1=intToString()+floatToString();
			string s2=x.intToString()+x.floatToString();
			for(int i=1;i<=max(float_size,x.float_size)-float_size;i++){
				s1+='0';
			}
			for(int i=1;i<=max(float_size,x.float_size)-x.float_size;i++){
				s2+='0';
			}
			BigInt a(s1),b(s2);
			BigFloat ret;
			ret.intv=a/b;
			BigInt t=a%b;
			for(int i=1;i<=accuracy;i++){
				t*=10;
				ret.floatv[i]=(t/b).toInt()+'0';
				ret.float_size++;
				ret.floatv.push_back('0');
				t=t%b;
				if(t==0){
					break;
				}
			}
			while(ret.floatv[ret.float_size]=='0'&&ret.float_size>1){
				ret.float_size--;
				ret.floatv.pop_back();
			}
			ret.round(output_count,r);
			if(neg!=x.neg){
				ret.neg=1;
			}
			return ret;
		}
		BigFloat absolute(){
			BigFloat ret=*this;
			ret.neg=0;
			return ret;
		}
		
		void input(){
			string s;
			cin>>s;
			init(s);
		}
		void print(){
			if(!r){
				if(neg){
					printf("-");
				}
				cout<<intv;
				if(output_count>0){
					printf(".");
					for(int i=1;i<=output_count;i++){
						if(i<=float_size){
							printf("%c",floatv[i]);
						}
						else{
							printf("0");
						}
					}
				}
			}
			else{
				BigFloat t;
				t.neg=neg;
				t.intv=intv;
				char mid=neg+'4';
				if(output_count>0){
					string s="0.";
					for(int i=1;i<=output_count;i++){
						char c='0';
						if(i<=float_size){
							c=floatv[i];
						}
						t.floatv[i]=c;
						if(i<output_count){
							t.float_size++;
							t.floatv.push_back('0');
							s+='0';
						}
					}
					s+='1';
					if(output_count+1<=float_size&&floatv[output_count+1]>mid){
						t+=BigFloat(s);
					}
					while(t.floatv[t.float_size]=='0'&&t.float_size>1){
						t.float_size--;
						t.floatv.pop_back();
					}
					t.round(output_count,0);
				}
				else{
					t+=(floatv[1]>mid);
					t.round(0,0);
				}
				t.print();
			}
		}
	public:
		BigFloat(){
			init();
		}
		BigFloat(string x){
			init(x);
		}
		BigFloat(double x){
			init(to_string(x));
		}
		
		BigFloat operator=(string x){
			init(x);
			return *this;
		}
		BigFloat operator=(double x){
			init(to_string(x));
			return *this;
		}
		bool operator==(BigFloat x){
			return isEqual(x);
		}
		bool operator==(double x){
			return *this==BigFloat(x);
		}
		bool operator!=(BigFloat x){
			return !(*this==x);
		}
		bool operator!=(double x){
			return *this!=BigFloat(x);
		}
		bool operator<(BigFloat x){
			if(neg&&x.neg){
				return absolute()>x.absolute();
			}
			else{
				return isSmaller(x);
			}
		}
		bool operator<(double x){
			return *this<BigFloat(x);
		}
		bool operator>(BigFloat x){
			if(neg&&x.neg){
				return absolute()<x.absolute();
			}
			else{
				return isBigger(x);
			}
		}
		bool operator>(double x){
			return *this>BigFloat(x);
		}
		bool operator<=(BigFloat x){
			return *this<x||*this==x;
		}
		bool operator<=(double x){
			return *this<=BigFloat(x);
		}
		bool operator>=(BigFloat x){
			return *this>x||*this==x;
		}
		bool operator>=(double x){
			return *this>=BigFloat(x);
		}
		BigFloat operator+(BigFloat x){
			if(x<0){
				return *this-x.absolute();
			}
			else if(*this<0){
				x.output_count=output_count;
				x.r=r;
				return x-absolute();
			}
			else{
				return add(x);
			}
		}
		BigFloat operator+(double x){
			return *this+BigFloat(x);
		}
		BigFloat operator+=(BigFloat x){
			BigFloat ret=*this+x;
			init(ret);
			return ret;
		}	
		BigFloat operator+=(double x){
			return *this+=BigFloat(x);
		}
		BigFloat operator++(int x){
			return *this+=1;
		}
		BigFloat operator-(){
			return negative();
		}
		
		BigFloat operator-(BigFloat x){
			if(x<0){
				return *this+x.absolute();
			}
			else if(*this<0){
				return -(absolute()+x);
			}
			else if(x>*this){
				x.output_count=output_count;
				x.r=r;
				return -(x-*this);
			}
			else{
				return minus(x);
			}
		}
		BigFloat operator-(double x){
			return *this-BigFloat(x);
		}
		BigFloat operator-=(BigFloat x){
			BigFloat ret=*this-x;
			init(ret);
			return ret;
		}	
		BigFloat operator-=(double x){
			return *this-=BigFloat(x);
		}
		BigFloat operator--(int x){
			return *this-=1;
		}
		BigFloat operator*(BigFloat x){
			return mul(x);
		}
		BigFloat operator*(double x){
			return (*this)*BigFloat(x);
		}
		BigFloat operator*=(BigFloat x){
			BigFloat ret=(*this)*x;
			init(ret);
			return ret;
		}	
		BigFloat operator*=(double x){
			return (*this)*=BigFloat(x);
		}
		BigFloat operator/(BigFloat x){
			return div(x);
		}
		BigFloat operator/(double x){
			return (*this)/BigFloat(x);
		}
		BigFloat operator/=(BigFloat x){
			BigFloat ret=(*this)/x;
			init(ret);
			return ret;
		}
		BigFloat operator/=(double x){
			return (*this)/=BigFloat(x);
		}
				
		friend ostream& operator<<(ostream& os,BigFloat x);
		friend istream& operator>>(istream& os,BigFloat& x);
		
		int floatLength(){
			return float_size;
		}
		int intLength(){
			return intv.length();
		}
		int length(){
			return intLength()+floatLength();
		}
		void round(int x,bool r=1){
			output_count=x;
			this->r=r;
		}
		void setAccuracy(int x){
			accuracy=x;
		}
		string intToString(){
			return intv.toString();
		}
		string floatToString(){
			string ret="";
			for(int i=1;i<=float_size;i++){
				ret+=floatv[i];
			}
			return ret;
		}
		string toString(){
			string ret="";
			if(neg){
				ret+='-';
			}
			ret=ret+intToString()+'.'+floatToString();
			return ret;
		}
};

ostream& operator<<(ostream& os,BigInt x){
	x.print();
	return os;
}
istream& operator>>(istream& os,BigInt& x){
	x.input();
	return os;
}
ostream& operator<<(ostream& os,BigFloat x){
	x.print();
	return os;
}
istream& operator>>(istream& os,BigFloat& x){
	x.input();
	return os;
}

#endif
