#include<iostream>
#include<vector>
using namespace std;

vector<int>computeFailFunction(const string& pattern)
{
	vector<int>fail(pattern.size());
	fail[0]=0;
	int m=pattern.size();
	int j=0;
	int i=1;
	while(i<m)
	{
		if(pattern[j]==pattern[i])
		{
			fail[i]=j+1; 
			i++;j++;
		}
		else if(j>0) 
			j=fail[j-1];
		else
		{
			fail[i]=0;
			i++;
		}
	}
return fail;
}

int KMPmatch(const string& text, const string& pattern)
{
	int n=text.size();
	int m=pattern.size();
	vector<int>fail=computeFailFunction(pattern);
	int i=0; 
	int j=0; 
	while(i<n)
	{
		if(pattern[j]==text[i])
		{
			if(j==m-1)
			return i-m+1; 
			i++;j++;
		}
		else if(j>0)
			j=fail[j-1];
		else i++;
	}
	return -1; 
}

int main()
{
	string text;
	cout<<"Enter text : ";cin>>text;
	string pattern;
	cout<<"Enter pattern : ";cin>>pattern;
	
	int result=KMPmatch(text,pattern);
	
	if(result!=-1)
		cout<<"Pattern found at index: "<<result;
	else
		cout<<"Pattern not found";
}
