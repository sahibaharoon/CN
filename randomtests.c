//prime
int prime(int n){
    for(int i=2;i*i<=n;i++){
        if(n%i==0) return 0;
    }
    return n>1;
}
//amstrong
int ams(int n){
    int digits=0,sum=0,i;
    int temp=n;
    for(i=temp;i>0;i/=10){
        digits++;
    }
    for(i=temp;i>0;i/=10){
        sum+=pow(i%10,digits);
    }
    return sum==n;
}

//event or odd
sprintf(buf, "%d is %s", n, (n % 2 == 0) ? "Even" : "Odd");
//fibonacci
void fib(int n, char* res){
    int a=0,b=1,c;
    char temp[20];
    sprintf(res,"%d %d",a,b);
    for(int i=2;i<n;i++){
        c=a+b;
        sprintf(temp,"%d ",c);
        strcat(res,temp);
        a=b;
        b=c;
    }
}
//palindrome number
int palindrome(int n){
    int rev=0;
    int ori=n;
    for(;n>0;n/=10){
        rev=rev*10 + n %10;
    }
    return ori==rev;
}
//palindrome string
int palindrome(char* str){
    int l=0,r=strlen(str)-1;
    while(l<r){
        if(str[l]!=str[r])
            return 0;
        l++;r--;
    }
    return 1;
}
