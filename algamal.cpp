#include <bits/stdc++.h>
using namespace std;

long long modExp(long long b,long long e,long long m){
    long long r=1;
    while(e){
        if(e&1) r=(r*b)%m;
        b=(b*b)%m;
        e>>=1;
    }
    return r;
}

long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}

long long modInv(long long a,long long m){
    long long m0=m,t,q,x0=0,x1=1;
    while(a>1){
        q=a/m;
        t=m; m=a%m; a=t;
        t=x0; x0=x1-q*x0; x1=t;
    }
    if(x1<0) x1+=m0;
    return x1;
}

long long hashF(string s){
    long long h=0;
    for(char c:s) h+=c;
    return h;
}

int main(){
    long long p,g,x,k;
    cout<<"Enter p g x k:\n";
    cin>>p>>g>>x>>k;

    if(gcd(k,p-1)!=1){ cout<<"Invalid k"; return 0; }

    long long y=modExp(g,x,p);
    cout<<"\nPublic key y = "<<y<<"\n";

    string msg;
    cout<<"\nEnter message:\n";
    cin.ignore();
    getline(cin,msg);

    long long H=hashF(msg);
    cout<<"Hash = "<<H<<"\n";

    long long r=modExp(g,k,p);
    long long s=(modInv(k,p-1)*(H - x*r))%(p-1);
    if(s<0) s+=(p-1);

    cout<<"\nSignature (r,s): "<<r<<" , "<<s<<"\n";

    long long v1=modExp(g,H,p);
    long long v2=(modExp(y,r,p)*modExp(r,s,p))%p;

    cout<<"\nVerify:\n";
    cout<<"v1 = "<<v1<<"\n";
    cout<<"v2 = "<<v2<<"\n";

    if(v1==v2) cout<<"RESULT: VERIFIED ✅";
    else cout<<"RESULT: FAILED ❌";
}