#include <bits/stdc++.h>
using namespace std;
//input in the form: p q x k example: 23 11 6 3 hello
long long modExp(long long b,long long e,long long m){
    long long r=1;
    while(e){
        if(e&1) r=(r*b)%m;
        b=(b*b)%m;
        e>>=1;
    }
    return r;
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

long long findG(long long p,long long q){
    long long e=(p-1)/q;
    for(long long h=2;h<p;h++){
        long long g=modExp(h,e,p);
        if(g>1) return g;
    }
    return -1;
}

int main(){
    long long p,q,x,k;
    cout<<"Enter p, q, private key x, random k:\n";
    cin>>p>>q>>x>>k;

    string msg;
    cout<<"Enter message:\n";
    cin.ignore();
    getline(cin,msg);

    long long g=findG(p,q);
    long long y=modExp(g,x,p);

    cout<<"\n--- Key Generation ---\n";
    cout<<"g = "<<g<<"\n";
    cout<<"Public key y = "<<y<<"\n";

    long long H=hashF(msg)%q;
    cout<<"\nHash H(m) mod q = "<<H<<"\n";

    long long r=modExp(g,k,p)%q;
    long long s=(modInv(k,q)*(H + x*r % q))%q;

    cout<<"\n--- Signature ---\n";
    cout<<"r = "<<r<<"\n";
    cout<<"s = "<<s<<"\n";

    long long w=modInv(s,q);
    long long u1=(H*w)%q;
    long long u2=(r*w)%q;

    long long v=(modExp(g,u1,p)*modExp(y,u2,p)%p)%q;

    cout<<"\n--- Verification ---\n";
    cout<<"w = "<<w<<"\n";
    cout<<"u1 = "<<u1<<" , u2 = "<<u2<<"\n";
    cout<<"v = "<<v<<"\n";

    if(v==r) cout<<"\nRESULT: SIGNATURE VERIFIED ✅\n";
    else cout<<"\nRESULT: SIGNATURE FAILED ❌\n";

    return 0;
}