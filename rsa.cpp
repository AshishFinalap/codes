#include <bits/stdc++.h>
using namespace std;

int gcd(int a,int b){ return b==0?a:gcd(b,a%b); }

long long modExp(long long b,long long e,long long m){
    long long r=1;
    while(e){
        if(e&1) r=(r*b)%m;
        b=(b*b)%m;
        e>>=1;
    }
    return r;
}

int modInv(int e,int phi){
    for(int d=1;d<phi;d++) if((e*d)%phi==1) return d;
    return -1;
}

int hashF(string s){
    int h=0;
    for(char c:s) h+=c;
    return h;
}

int main(){
    int p,q,e;
    cout<<"Enter p q e:\n";
    cin>>p>>q>>e;

    int n=p*q, phi=(p-1)*(q-1);
    if(gcd(e,phi)!=1){ cout<<"Invalid e"; return 0; }

    int d=modInv(e,phi);

    cout<<"\nPublic Key: ("<<e<<","<<n<<")";
    cout<<"\nPrivate Key: ("<<d<<","<<n<<")\n";

    string msg;
    cout<<"\nEnter message:\n";
    cin.ignore();
    getline(cin,msg);

    int h=hashF(msg);
    long long sign=modExp(h,d,n);
    long long verify=modExp(sign,e,n);

    cout<<"\nHash = "<<h;
    cout<<"\nSignature = "<<sign;
    cout<<"\nVerified Hash = "<<verify<<"\n";

    if(verify==h%n) cout<<"RESULT: VERIFIED ✅";
    else cout<<"RESULT: FAILED ❌";
}