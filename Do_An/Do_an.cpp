
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string>

using std::string;
using namespace std;

struct BigInt
{
	int a[4];
};
BigInt Subtraction(BigInt a, BigInt b);	
BigInt operator-(BigInt a,BigInt b );
BigInt operator+(BigInt a,BigInt b );
bool operator<(BigInt a, BigInt b);
bool operator>(BigInt a, BigInt b);
bool operator==(BigInt a, BigInt b);

string Div2(string x)		
{
	char t[100];
	int j=0;
	int temp, du=0;
	int n=x.length();
	if(x[n-1]=='1') 
		x[n-1]='0';
	int k=0;				
	if(x[0]=='1')
	{
		k=1;
		du=1;
	}
	for(int i=k; i<n; i++)
	{
		int so=x[i]-'0';
		if(so!=1||du!=0)
		{
			temp=so+10*du;
			t[j++]=temp/2+'0';
			du=temp%2;
		}
		else
		{
			t[j++]='0';
			du=1;
		}
	}
	string kq(t,j); 
	return kq;
}
void SetBit(BigInt &X, int bit, int i)
{
	int vt = i / 32;
	int j = i % 32;
	int t = bit << (31 - j);
	X.a[vt] = X.a[vt]^t;
}
void strtoBigint(string X, BigInt &a)
{
	int i = 127; 
	while (X != "0")
	{
		int du = (X[X.length() - 1] - 48 ) % 2;
		SetBit(a,du,i);
		X = Div2(X);
		i--;

	}
}
string Tongchuoi(string a, string b)
{
	if(a.length()<b.length())
	{
		string p=a;
		a=b;
		b=p;
	}
	int lena= a.length();
	int lenb= b.length();
	char * kq = new char[lena];
	int du = 0;
	for(int i =lena -1 ; i>=0; i--)
	{
		int dva = a[i] - 48;
		int dvb = i-(lena-lenb)>=0?b[i - (lena - lenb)] - 48:0;
		int s = dva + dvb + du;
		if(s >= 10)
		{
			kq[i] = s % 10 + 48;
			du = 1;
		}
		else
		{
			kq[i] = s + 48;
			du = 0;
		}
	}
	char * kq1;
	if ( du == 1)
	{
		kq1 = new char[lena + 1];
		kq1[0] = 49;
		for(int i = 0; i< lena; i++)
			kq1[i+1] = kq[i];
		string rs(kq1,lena +1);
		return rs;
	}
	else
	{
		string rs(kq, lena);
		return rs;
	}
}
void ScanBigInt(BigInt &a)
{
	string x,x1;
	cin>>x;
	if(x[0]=='-')
	{
		int k=0;
		char * x1 = new char[x.length()-1];
		for(int i=0; i<x.length()-1;i++)
		{
			x1[i] = x[i+1];
		}
		x1[x.length()-1]=NULL;
		SetBit(a,1,0);
		strtoBigint(x1,a);
		return;
	}
	strtoBigint(x,a);
}
string Tinh2Mu(int mu)
{
	string kq = "1";
	if (mu == 0)
		return  "1";
	for(int i = 0; i < mu; i++)
		kq = Tongchuoi(kq,kq);
	return kq;
}
bool GetBit(BigInt x, int i)			
{
	return (x.a[i/32]>>(31-i%32))&1;
}
void PrintBigInt(BigInt X)
{
	string kq="0";
	
	for (int i= 1; i < 128; i++)
	{
		int bit = GetBit(X,i);
		if(bit == 1)
		{
			string t = Tinh2Mu(128 - i - 1 );
			kq = Tongchuoi(kq,t);
		}
	}
	if(GetBit(X,0)==1)
	{
		char * x1 = new char[kq.length()+1];
		for(int i=1;i<=kq.length();i++ )
		{
			x1[i]=kq[i-1];
		}
		x1[0]='-';
		string t(x1,kq.length()+1);
		cout<<t;
	}
	else
	cout << kq;
}
void DecToBin(BigInt a)
{
	for(int i=0;i<128;i++)
		cout<<GetBit(a,i);
}
bool operator<(BigInt a, BigInt b)//Phép bé hơn
{
	for(int i=1;i<=127;i++)
	{
		if(GetBit(a,i)<GetBit(b,i))
			return true;
		if(GetBit(a,i)>GetBit(b,i))
			return false;
	}
	return false;
}
bool operator>(BigInt a, BigInt b)//Phép lớn hơn	
{
	for(int i=1;i<=127;i++)
	{
		if(GetBit(a,i)>GetBit(b,i))
			return true;
		if(GetBit(a,i)<GetBit(b,i))
			return false;
	}
	return false;
}
bool operator==(BigInt a, BigInt b)// phép ss bằng
{
	for(int i=1;i<=127;i++)
	{
		if(GetBit(a,i)!=GetBit(b,i))
			return false;
	}
	return true;
}

BigInt Addition(BigInt a,BigInt b)// Phép cộng 2 số dương 
{
	
	BigInt c={0};
	int temp =0;
	int du = 0;
	for(int i=127; i>1; i--)
	{
		int Temp1=GetBit(a,i);
		int Temp2=GetBit(b,i);

		int kq= Temp1+(Temp2+du);
		if(kq==0 || kq == 1)
		{
			SetBit(c,kq,i);
			du = 0;
		}
		if(kq==2)
		{
			SetBit(c,0,i);
			du = 1;
		}
		if(kq == 3)
		{
			SetBit(c,1,i);
			du = 1;
		}
	}
	return c;
	
}
BigInt operator+(BigInt a,BigInt b )
{
	BigInt c={0};
	if(GetBit(a,0)==0 && GetBit(b,0)==1)
	{
		if(a>b)	
			c=Subtraction( a,b);
		if(a<b)		
		{
			c=Subtraction( b,a);
			SetBit(c,1,0);
		}	
		if(a==b)
			c=Subtraction( a,b);
	}	 
	if(GetBit(a,0)==1 && GetBit(b,0)==0)
	{
			if(a>b)		
			{
				c=Subtraction( a,b);
				SetBit(c,1,0);
			}
			if(a<b)
				c=Subtraction( b,a);
			if(a==b)
				Subtraction( a,b);
	}
	if(GetBit(a,0)==1 && GetBit(b,0)==1)
	{
		c=Addition(a,b);
		
		SetBit(c,1,0);
	}
	if(GetBit(a,0)==0 && GetBit(b,0)==0)
	{
		c=Addition(a,b);
	}

	return c;
}
BigInt operator-(BigInt a,BigInt b )
{
	BigInt c={0};
	if(GetBit(a,0)==0 && GetBit(b,0)==0)
	{
		if(a<b)
		{
			c=Subtraction(b,a);
			SetBit(c,1,0);
		}
		if(a>b)
			c=Subtraction(a,b);
		if(a==b)
			c=Subtraction(a,b);
	}
	if(GetBit(a,0)==0 && GetBit(b,0)==1)
	{
		c=Addition(a,b);
		SetBit(c,0,0);
	}
	if(GetBit(a,0)==1 && GetBit(b,0)==0)
	{
		c=Addition(a,b);
		SetBit(c,1,0);
	}
	if(GetBit(a,0)==1 && GetBit(b,0)==1)
	{
		if(a>b)
		{
			c=Subtraction(a,b);
			SetBit(c,1,0);
		}
		if(a<b)
		{
			c=Subtraction(b,a);
			SetBit(c,0,0);
		}
		if(a==b)
			c=Subtraction(a,b);
	}
	return c;
}
BigInt Subtraction(BigInt a, BigInt b)// Phép trừ 2 số dương
{

	BigInt c={0};
	int temp =0;
	int nho = 0;
	for(int i=127; i>1; i--)
	{
		int Temp1=GetBit(a,i);
		int Temp2=GetBit(b,i);

		int kq= Temp1-(Temp2+nho);
		if(kq==0 || kq == 1)
		{
			SetBit(c,kq,i);
			nho = 0;
		}
		if(kq==-1)
		{
			SetBit(c,1,i);
			nho = 1;
		}
	}
	return c;
}
BigInt operator<<(BigInt &a, int n)
{
	BigInt d={0};
	char b[128];//Tạo mảng b để lưu các bit trong BigInt a.
	char c[128];//Tạo mảng c để lưu các bit sau khi dịch 
	int k=1;
	for(int i=127; i>=0;i--)
	{
		b[i]=GetBit(a,i);// gán từng bit vào vào mảng b
	}
	a=d;//BigInt a=0;
	for(int j=n+1;j<=127;j++)
		c[k++]=b[j];//Gán từ phần từ thứ n+1 của mảng b cho phần tử thứ 2 của mảng c cho đến phần tử cuối cùng của mảng b
	for(k;k<=127;k++)
		c[k]=0;// gán 0 vào những phần tử còn lại của mảng c trừ phần tử c[0](bit dấu)
	c[0]=b[0];// gán bit dấu của mảng b cho mảng c
	for(int i1=127; i1>=0;i1--)
	{
		SetBit(a,c[i1],i1);// Tạo giá trị bit cho kiểu dữ liệu BigInt
	}
	return a;
}
BigInt operator>>(BigInt &a, int n)
{
	BigInt d={0};
	char b[128];//Tạo mảng b để lưu các bit trong BigInt a.
	char c[128];//Tạo mảng c để lưu các bit sau khi dịch 
	int k=n+1;
	for(int i=0; i<=127;i++)
	{
		b[i]=GetBit(a,i);// gán từng bit vào vào mảng b
	}
	a=d;//BigInt a=0
	for(int j=1;j<=127-n;j++)
		c[k++]=b[j];//gán phần tử thứ hai của mảng b vào phần tử thứ n+1 của mảng c, gán cho phần tử thứ 127-n của mảng b
	for(k=n+1;k>=1;k--)
		c[k]=0;// gán 0 vào những phần tử còn lại của mảng c trừ phần tử c[0](bit dấu) 
	c[0]=b[0];// gán bit dấu của mảng b cho mảng c
	for(int i1=127; i1>=0;i1--)
	{
		SetBit(a,c[i1],i1);// Tạo giá trị bit cho kiểu dữ liệu BigInt
	}
	return a;
}
BigInt Multiplication(BigInt a,BigInt b)
{
	BigInt c={0};
	
	for(int i=127; i>=1;i--)
	{
		if(GetBit(b,i)==1)
		{
			c=Addition(c,a);
			a<<1;
		}
		else
		{
			a<<1;
		}
	}
	return c;
}
BigInt operator*(BigInt a,BigInt b)
{
	
	BigInt c={0};
	if((GetBit(a,0)==1 && GetBit(b,0)==0) || (GetBit(a,0)==0 && GetBit(b,0)==1))
	{
		c=Multiplication(a,b);
		SetBit(c,1,0);

	}
	if((GetBit(a,0)==1 && GetBit(b,0)==1) || (GetBit(a,0)==0 && GetBit(b,0)==0))
	{
		c=Multiplication(a,b);
		SetBit(c,0,0);
	}
	return c;
}
BigInt Division(BigInt a, BigInt b)
{
	BigInt e={1};
	BigInt q={0};
	BigInt r={0};
	SetBit(r,1,127);
	if((!(a==q) && b==q) || (a==q && b==q))
		return e;
	while(a>b || a==b)
	{
		a=Subtraction(a,b);
		q=Addition(q,r);
	}
	
	return q;

}
BigInt operator/(BigInt a, BigInt b)
{
	BigInt e={1};
	BigInt q={0};
	BigInt r={0};
	SetBit(r,1,127);
	if((!(a==q) && b==q) || (a==q && b==q))
		return e;
	
	if((GetBit(a,0)==1 && GetBit(b,0)==0) || (GetBit(a,0)==0 && GetBit(b,0)==1))
	{
		q=Division(a,b);
		SetBit(q,1,0);
	}
	if((GetBit(a,0)==1 && GetBit(b,0)==1) || (GetBit(a,0)==0 && GetBit(b,0)==0))
	{
		q=Division(a,b);
		SetBit(q,0,0);

	}
	return q;

}



void main()
{
	int x;
	BigInt q={1};
	BigInt a={0};
	BigInt b={0};
	BigInt c={0};
	cout<<"Nhap BigInt a: ";
	ScanBigInt(a);
	cout<<endl;
	cout<<"Nhap BigInt b: ";
	ScanBigInt(b);
 	cout<<endl;

	cout<<"-----------------------------MENU-----------------------------"<<endl;
	do
	{
		cout<<"1. Xuat a va b "<<endl;
		cout<<"2. Xem day bit a va b"<<endl;
		cout<<"3. Tong a va b"<<endl;
		cout<<"4. Hieu a va b"<<endl;
		cout<<"5. Thuong a va b"<<endl;
		cout<<"6. Tich a va b"<<endl;
		cout<<"7. Dich trai a"<<endl;
		cout<<"8. Dich phai b"<<endl;
		cout<<"--------------------------------------------------------------"<<endl;
		cout<<"Chon: ";
		cin>>x;
		switch(x)
             {
                               case 1:
                                    {
										cout<<"Ket qua: ";cout<<endl;
										cout<<"a = ";PrintBigInt(a);cout<<endl;
										cout<<"b = ";PrintBigInt(b);cout<<endl;
                                        break;       
                                    }
                               case 2:
                                    {
										cout<<"Ket qua: ";cout<<endl;
										cout<<"Day nhi phan cua ";PrintBigInt(a);cout<<" :";DecToBin(a);cout<<endl;
										cout<<"Day nhi phan cua ";PrintBigInt(a);cout<<" :";DecToBin(b);cout<<endl;
                                        getch();
                                        break;    
                                    }
                               case 3:
                                    {
										c=a+b;
										cout<<"Ket qua: ";
										PrintBigInt(c);cout<<endl;
										getch();
										break;    
                                    }
                               case 4:
                                    {
                                        c=a-b;
										cout<<"Ket qua: ";
										PrintBigInt(c);cout<<endl;
                                        getch();
										break;
                                    }
								case 5:
                                    {
                                        c=a/b;
										cout<<"Ket qua: ";
										if(c==q)
											cout<<"Khong thuc hien duoc phep tinh";
										else
											PrintBigInt(c);cout<<endl;
                                        getch();
										break;
                                    }
								case 6:
                                    {
                                        c=a*b;
										cout<<"Ket qua: ";	
										PrintBigInt(c);cout<<endl;
                                        getch();
										break;
                                    }
								case 7:
                                    {
										int n;
										cout<<"Vui long nhap so bit can dich chuyen: ";
										cin>>n;
                                        a<<n;
										cout<<"Ket qua: ";
										DecToBin(a);cout<<endl;
										cout<<"So thap phan sau khi dich chuyen la: ";PrintBigInt(a);
                                        getch();
										break;
                                    }
								case 8:
                                    {
                                       int m;
										cout<<"Vui long nhap so bit can dich chuyen: ";
										cin>>m;
                                        b>>m;
										cout<<"Ket qua: ";
										DecToBin(b);cout<<endl;
                                        getch();
										break;
                                    }
								
								
                               default: break;
                                    
             }
	}while(x==0);
	
	
 }
